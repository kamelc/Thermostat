/*
 * Thermostat_test.cpp
 *
 *  Created on: Mar 29, 2023
 *      Author: chaouche
 */

#include <gtest/gtest.h>
#include "Thermostat.h"

class Thermostat_test: public Thermostat {
public:
	Thermostat_test(){};
	Thermostat_test(float min, float max): temperature(0),Thermostat(min, max){
	};
	virtual ~Thermostat_test(){};
	virtual float readTempSensor() { return temperature; }; //overloads the parent function works as a stub to the real reasTempSensor

	void setFakeTemperature(float t) {
		temperature = t;
		setCurrentTemperature(t);
	};

	void testStartHeating() {
		startHeating();
	};

	void testStartCooling() {
		startCooling();
	}

	void testStopHeating() {
		stopHeating();
	}

	void testStopCooling() {
		stopCooling();
	}

	void testCheckTemperature() {
		checkTemperature();
	}

private:
	float temperature;
};

TEST(Thermostat, MinMaxTemperature) {
	Thermostat_test th(10.0, 20.0);
    ASSERT_EQ(10.0, th.getMinTemperature());
    ASSERT_EQ(20.0, th.getMaxTemperature());
}

TEST(Thermostat, AmbientTemperature) {
	Thermostat_test th(10.0, 20.0);
	th.setAmbientTemperature(25.0);
	ASSERT_EQ(25.0, th.getMinTemperature());
    ASSERT_EQ(25.0, th.getMaxTemperature());
}

TEST(Thermostat, HeatingCoolingState) {
	Thermostat_test th(10.0, 20.0);
	ASSERT_EQ(Thermostat::state::stopped, th.getHeatingState());
    ASSERT_EQ(Thermostat::state::stopped, th.getCoolingState());
}

TEST(Thermostat, StartHeating) {
	Thermostat_test th(10.0, 20.0);
	th.testStartHeating();
	ASSERT_EQ(Thermostat::state::started, th.getHeatingState());
    ASSERT_EQ(Thermostat::state::stopped, th.getCoolingState());
}

TEST(Thermostat, StartCooling) {
	Thermostat_test th(10.0, 20.0);
	th.testStartCooling();
	ASSERT_EQ(Thermostat::state::stopped, th.getHeatingState());
    ASSERT_EQ(Thermostat::state::started, th.getCoolingState());
}

TEST(Thermostat, StopHeating) {
	Thermostat_test th(10.0, 20.0);
	th.testStartHeating();
	th.testStopHeating();
	ASSERT_EQ(Thermostat::state::stopped, th.getHeatingState());
}

TEST(Thermostat, StopCooling) {
	Thermostat_test th(10.0, 20.0);
	th.testStartCooling();
	th.testStopCooling();
    ASSERT_EQ(Thermostat::state::stopped, th.getCoolingState());
}

TEST(Thermostat, checkTemperatureStartHeating) {
	Thermostat_test th(10.0, 20.0);
	th.setFakeTemperature(0);
	th.testCheckTemperature();
	ASSERT_EQ(Thermostat::state::started, th.getHeatingState());
    ASSERT_EQ(Thermostat::state::stopped, th.getCoolingState());
}

TEST(Thermostat, checkTemperatureStartStopHeating) {
	Thermostat_test th(10.0, 20.0);
	th.setFakeTemperature(0);
	th.testCheckTemperature();
	th.setFakeTemperature(9.98);
	th.testCheckTemperature();
	ASSERT_EQ(Thermostat::state::stopped, th.getHeatingState());
    ASSERT_EQ(Thermostat::state::stopped, th.getCoolingState());
}

TEST(Thermostat, checkTemperatureStartCooling) {
	Thermostat_test th(10.0, 20.0);
	th.setFakeTemperature(35);
	th.testCheckTemperature();
	ASSERT_EQ(Thermostat::state::stopped, th.getHeatingState());
    ASSERT_EQ(Thermostat::state::started, th.getCoolingState());
}

TEST(Thermostat, checkTemperatureStartStopCooling) {
	Thermostat_test th(10.0, 20.0);
	th.setFakeTemperature(35);
	th.testCheckTemperature();
	th.setFakeTemperature(20.01);
	th.testCheckTemperature();
	ASSERT_EQ(Thermostat::state::stopped, th.getHeatingState());
    ASSERT_EQ(Thermostat::state::stopped, th.getCoolingState());
}

TEST(Thermostat, CurrentTemperature) {
	Thermostat_test th;
	th.setFakeTemperature(35.0);
    ASSERT_EQ(35.0, th.getCurrentTemperature());
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
