#include "vehicleHandler.h"

// Core Handler
vehicleHandler::vehicleHandler(int ownerID) {

	// Initialize
	setOwnerID(ownerID);

	// Main


}

// Core Handler Destructor
vehicleHandler::~vehicleHandler() {

}

// Enter Vehicle
int vehicleHandler::enterVehicle(int plrID)
{
	// If Someone is Entering, Return 1, Else Return 0
	return 0;
}

// Despan Vehicle
void vehicleHandler::despawnVehicle()
{

}

// Set Vehicle Owner
void vehicleHandler::setOwnerID(int id) {
	ownerID = id;
}