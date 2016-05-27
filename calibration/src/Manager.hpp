#include "../../imove/src/calibration/Calibration.hpp"

class CalibrationManager {
	public:
		CalibrationManager(Calibration* calibration);
		
		// runs the calibration using windows and camera as input and sets values in calibration
		bool run();

	protected:
		Calibration* calibration;
};
