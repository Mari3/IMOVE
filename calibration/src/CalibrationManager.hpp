#include "../../util/src/Calibration.hpp"

/**
 * Uses mouse input to calibrate projection, meter and projection elimination, untill key is pressed which means its done
 *
 **/
class CalibrationManager {
	public:
		CalibrationManager(Calibration* calibration);
		
		// runs the Calibration using windows and camera as input and sets values in Calibration using mouse input untill key pressed meaning its done
		void run();

	protected:
		Calibration* calibration;
};
