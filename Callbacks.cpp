#include "Callbacks.h"

AlarmCallbackHandler AlarmCallbackHandler::registeredAlarms[dtNBR_ALARMS] = {};
AlarmCallbackHandler::AlarmCallbackHandler() {}

void AlarmCallbackHandler::alarmTriggered()
{
	AlarmID_t triggeredAlarmId = Alarm.getTriggeredAlarmId();
	
	AlarmCallbackHandler handler = registeredAlarms[triggeredAlarmId];
	handler.updatePins();

}

void AlarmCallbackHandler::registerNewAlarm(AlarmID_t newAlarmId, int* pinsToAdd)
{
	AlarmCallbackHandler newHandler;
	newHandler.newPinValues = pinsToAdd;
	registeredAlarms[newAlarmId] = newHandler;
}

void AlarmCallbackHandler::updatePins()
{
	for (int pinIndex = 0; pinIndex < OUTLETS; pinIndex++)
	{
		int newPinVal = newPinValues[pinIndex];
		if (newPinVal >= 0)
		{
			int arduinoPinNumberOn = PINS_ON[pinIndex];
            int arduinoPinNumberOff = PINS_OFF[pinIndex];

            digitalWrite(arduinoPinNumberOn, newPinVal);
            digitalWrite(arduinoPinNumberOff, !newPinVal);

            pinVals[pinIndex] = newPinVal;
		}
	}
}

int* AlarmCallbackHandler::getNewPinValuesForAlarm(AlarmID_t alarmId)
{
	return registeredAlarms[alarmId].newPinValues; 
}

