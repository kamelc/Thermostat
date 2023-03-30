/*
 * Thermostat.h
 *
 *  Created on: Mar 29, 2023
 *      Author: chaouche
 */

#ifndef THERMOSTAT_H_
#define THERMOSTAT_H_
#include <thread>

#define TEMPERATURE_PRECISION 0.01f

class Thermostat {
public:
	enum state {
		started = true,
		stopped = false
	};

	Thermostat();
	Thermostat(float, float);
	virtual ~Thermostat();
	void setMinMaxTemperature(float minT, float maxT);
	void setAmbientTemperature(float temperture);
	float getMinTemperature();
	float getMaxTemperature();
	state getHeatingState();
	state getCoolingState();
	float getCurrentTemperature();
	void start();
	void stop();

protected:
	std::thread process;
	bool heatingState { false };
	bool coolingState { false };
	bool stopThermostat { false };
	float minTemperature { 15.0f };
	float maxTemperature { 25.0f };
	float currentTemperature;
	unsigned int temperatureCheckInterval { 1000U }; // in milliseconds
	void run();
	void startHeating();
	void stopHeating();
	void startCooling();
	void stopCooling();
	void checkTemperature();
	void setCurrentTemperature(float t);
	virtual float readTempSensor();

};

#endif /* THERMOSTAT_H_ */
