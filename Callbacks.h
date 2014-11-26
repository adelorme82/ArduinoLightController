#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "Common.h"
#include <TimeAlarms.h>

extern const int PINS_ON[];
extern const int PINS_OFF[];
extern bool *pinVals;


class AlarmCallbackHandler
{
	static AlarmCallbackHandler registeredAlarms[];
	AlarmCallbackHandler();
public:
	//this method is the one method that is registered as the callback for all alarms
	//it gets the alarmid of the alarm being serviced, uses that to index registeredAlarms
	//to get the correct handler, then uses the pins and pinValues properties
	//of that handler to set the pins properly
	static void alarmTriggered();
	
	//static method, so that ref to new object is not returned
	//so that users do not have direct access, and can just call alarmTriggered
	static void registerNewAlarm(AlarmID_t newAlarmId, int* pinsToAdd); 

	static int* getNewPinValuesForAlarm(AlarmID_t alarmId);

	void updatePins();


	//for each entry
	//-1 means do not change
	//0 meanas set to false/off
	//1 means set to true/on
	int* newPinValues;
};



#endif