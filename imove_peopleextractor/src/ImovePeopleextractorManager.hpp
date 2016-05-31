#include "Calibration/Calibration.hpp"
#include "ImageProcessing/PeopleExtractor.h"

// Setups people extractor and Scene, can let the Scene run using constant input of people extractor
class ImovePeopleextractorManager {
	public:
		/**
		 * Setup people extractor and communicate to Scene.
		 * 
		 * @param Calibration              The camera projector Calibration
		 **/
		ImovePeopleextractorManager(Calibration* calibration);

		// Run the people extractor and Scene frame by frame
		void run();

	protected:
		Calibration* calibration;
		PeopleExtractor* people_extractor;
};
