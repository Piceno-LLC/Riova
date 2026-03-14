#pragma once

class vehicleHandler {
private:
	int vehID = 0;
	double weight = 0.0;

public:
	vehicleHandler(int niVehID);
	~vehicleHandler();

	int getVehID() { return vehID; };
};