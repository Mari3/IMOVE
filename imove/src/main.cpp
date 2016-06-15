#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <string>

#include "../../scene_interface_sma/src/SharedMemory.hpp"
#include "../../scene_interface_sma/src/PeopleQueue.hpp"
#include "../../peopleextractor_interface_sma/src/SceneframeQueue.hpp"
#include "Running.hpp"

const unsigned int CONFIGURATION_CALIBRATION_ARGN = 1;
const unsigned int CONFIGURATION_LIGHTTRAIL_ARGN = 2;

const unsigned int SIZE_SHAREDMEMORY = 100000000; // 100MB

// setup and run Scene with continous people extraction as input based on configuration given in parameter otherwise show parameters
int main(int argc, char* argv[]) {
	// show parameters if not given 2 parameter
	if (argc != 3) {
		std::cerr << "Usage: <path to configuration file> <path to configuration scene>" << std::endl;
		return EXIT_SUCCESS;
	}

	std::string argv_str(argv[0]);
  std::string base = argv_str.substr(0, argv_str.find_last_of("/"));
	
	// Newly create a new shared memory segment with certain size
	boost::interprocess::shared_memory_object::remove(scene_interface_sma::NAME_SHARED_MEMORY);
	boost::interprocess::managed_shared_memory* segment = new boost::interprocess::managed_shared_memory(boost::interprocess::create_only, scene_interface_sma::NAME_SHARED_MEMORY, SIZE_SHAREDMEMORY);
	// Construct the people extracted queue in shared memory
	const scene_interface_sma::PeopleQueueSMA people_queue_sma(segment->get_segment_manager());
	segment->construct<scene_interface_sma::PeopleQueue>(scene_interface_sma::NAME_PEOPLE_QUEUE)(people_queue_sma);
	const peopleextractor_interface_sma::SceneframeQueueSMA sceneframe_queue_sma(segment->get_segment_manager());
	segment->construct<peopleextractor_interface_sma::SceneframeQueue>(peopleextractor_interface_sma::NAME_SCENEFRAME_QUEUE)(sceneframe_queue_sma);
	boost::interprocess::offset_ptr<Running> running = segment->construct<Running>(NAME_SHARED_MEMORY_RUNNING)();
	
	// while set that it should not shutdown but (re)start
	while (running->reboot_on_shutdown) {
		// fork to create subprocess scene
		pid_t pID_scene = fork();
		if (pID_scene == 0) {
			// replace process with imove_scene process
			std::cout << "Starting Scene" << std::endl;
			system(("\"" + base + "/imove_scene\" " + (std::string)argv[CONFIGURATION_CALIBRATION_ARGN] + " " + (std::string) argv[CONFIGURATION_LIGHTTRAIL_ARGN]).c_str());
			std::cout << "Ended Scene" << std::endl;
			_exit(0);
		} else if (pID_scene < 0) {
			std::cerr << "Failing to create subprocess scene" << std::endl;
		} else {
			// fork to create subprocess peopleextractor
			pid_t pID_peopleextractor = fork();
			if (pID_peopleextractor == 0) {
				std::cout << "Starting Peopleextractor" << std::endl;
				// replace process with imove_peopleextractor process
				system(("\"" + base + "/imove_peopleextractor\" " + (std::string) argv[CONFIGURATION_CALIBRATION_ARGN]).c_str());
				std::cout << "Ended Peopleextractor" << std::endl;
				_exit(0);
			} else if (pID_peopleextractor < 0) {
				std::cerr << "Failing to create subprocess people extractor" << std::endl;
			} else {
				// root process waits untill scene process exists and exits all subprocesses
				wait(NULL);
				running->running = false;
				wait(NULL);
				// remove shared memory segment
				boost::interprocess::shared_memory_object::remove(scene_interface_sma::NAME_SHARED_MEMORY);
			}
		}
	}
	
	return EXIT_SUCCESS;
}
