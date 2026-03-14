#pragma once

class vehicleHandler {
private:

	// Vehicle Properties
	int ownerID = 0;
	double weight = 0.0;

public:
	
	// Constructor and Destructor
	vehicleHandler(int plrID);
	~vehicleHandler();

	// Core Methods
	int enterVehicle(int plrID);
	void despawnVehicle();
	void setOwnerID(int id);

	// Getters
	int getVehID() { return ownerID; };
};