#ifndef ACTUATORS_H
#define ACTUATORS_H

void initActuators();
void loadPlantParameters();
void controlTemperature(float temp);
void controlPump();
void controlLEDs();
void logSystemState(float temp, float hum);

#endif

