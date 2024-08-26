#include "globalInstances.h"

temperatureControl tempCtrl(TEMP_PROBE_PIN, RELAY_PIN, true);
actuatorsControl actuatorsCtrl(MIXING_MOTOR_PIN);