#include <Arduino.h> 
#include "TimeTrigger.h"
#include "Time.h"

TimeTriggerManager::TimeTriggerManager()
{
	nextTrigger = NULL;
} 

int TimeTrigger::numAlarms = 0;

void TimeTriggerManager::addAlarm(int hr, int min, int sec)
{
	long tempTime = previousMidnight(now());
	debug("tempTime", tempTime);
	tmElements_t timeToAdd;
	timeToAdd.Wday = 0;
	timeToAdd.Day = 1; //setting as 0 will result in bad times
	timeToAdd.Month = 0;
	timeToAdd.Year = 0;
	timeToAdd.Hour = hr;
	debug("hr", hr);
	timeToAdd.Minute = min;
	debug("min", min);
	timeToAdd.Second = sec;
	debug("sec", sec);

	long newTime = makeTime(timeToAdd);
	debug("newTime", newTime);
	tempTime += newTime;
	debug("after tempTime", tempTime);

	TimeTrigger* currentTrigger;
	//put the alarm at the correct place in the list
	if (nextTrigger)
	{
		debug("existing alarm");
		currentTrigger = nextTrigger;
		debug("before currentTrigger->timeTrigger", currentTrigger->timeTrigger);
		debug("currentTrigger->alarmId", currentTrigger->alarmId);
		while (currentTrigger->timeTrigger < tempTime && (currentTrigger = currentTrigger->next));
		debug("after currentTrigger->timeTrigger", currentTrigger->timeTrigger);
	}
	else 
	{
		debug("no alarms");
		currentTrigger = &TimeTrigger(tempTime);
		nextTrigger = currentTrigger;
	}
}

TimeTrigger::TimeTrigger(long time)
{
	debug("new TimeTrigger time", time);
	timeTrigger = time;
	alarmId = ++numAlarms;
	debug("alarmId", alarmId);
	debug("timeTrigger", timeTrigger);
}


//for use in other files - Alarm.method()
TimeTriggerManager Alarm = TimeTriggerManager();
