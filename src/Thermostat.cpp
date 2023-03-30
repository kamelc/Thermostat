/*
 * Thermostat.cpp
 *
 *  Created on: Mar 29, 2023
 *      Author: chaouche
 */

#include "Thermostat.h"
#include <iostream>
#include <unistd.h>

Thermostat::Thermostat() {
}

Thermostat::Thermostat(float minT, float maxT)
	:minTemperature(minT),
	 maxTemperature(maxT) {
}

Thermostat::~Thermostat() {
	stopThermostat = true;
	if(process.joinable())
		process.join();
}

float Thermostat::getMinTemperature(){
	return minTemperature;
}

float Thermostat::getMaxTemperature(){
	return maxTemperature;
}

Thermostat::state Thermostat::getHeatingState(){
	return static_cast<state>(heatingState);
}

Thermostat::state Thermostat::getCoolingState(){
	return static_cast<state>(coolingState);
}

void Thermostat::setAmbientTemperature(float temperture){
	minTemperature = temperture;
	maxTemperature = temperture;
}

void Thermostat::startHeating(){
	std::cout << "Temperature low: Start heating" << std::endl;
	if(coolingState){
		stopCooling();
	}
	heatingState = state::started;
}

void Thermostat::stopHeating(){
	std::cout << "Stop heating" << std::endl;
	heatingState = state::stopped;
}

void Thermostat::startCooling(){
	std::cout << "Temperature high: Start cooling" << std::endl;
	if(heatingState){
		stopHeating();
	}
	coolingState = state::started;
}

void Thermostat::stopCooling(){
	std::cout << "Stop cooling" << std::endl;
	coolingState = state::stopped;
}

float Thermostat::readTempSensor(){
	// The content of this function should be replaced by the right code to read
	// out the right temperature.

	if(coolingState){
		currentTemperature -= 1; // temperature decreasing simulation
	}
	else if(heatingState){
		currentTemperature += 1; // temperature increasing simulation
	}

	std::cout << "Sensor temperature: " << currentTemperature << std::endl;
	return currentTemperature;
}

void Thermostat::setMinMaxTemperature(float minT, float maxT){
	minTemperature = minT;
	maxTemperature = maxT;
}

float Thermostat::getCurrentTemperature(){
	return currentTemperature;
}

void Thermostat::setCurrentTemperature(float t){
	currentTemperature = t;
}

void Thermostat::checkTemperature(){
	std::cout << "checking temperature" << std::endl;
	float temp = readTempSensor();

	if(temp < minTemperature && !heatingState){
		startHeating();
	}
	else if(heatingState &&
			abs(temp - minTemperature) <= TEMPERATURE_PRECISION) {
		stopHeating();
	}
	else if (temp > maxTemperature && !coolingState){
		startCooling();
	}
	else if(coolingState &&
			abs(temp - maxTemperature) <= TEMPERATURE_PRECISION) {
			stopCooling();
	}
}

void Thermostat::run() {
	while (!stopThermostat){
		checkTemperature();
		usleep(temperatureCheckInterval);
	}
}

void Thermostat::start(){
	process = std::thread(&Thermostat::run, this);
}

void Thermostat::stop(){
	stopThermostat = true;
}
