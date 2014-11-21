#ifndef TIME_TRIGGER_H_
#define TIME_TRIGGER_H_

#include "Time.h" 
#include "debug.h"

class TimeTrigger
{

	static int numAlarms;
public:
	long timeTrigger;
	bool repeating;
	bool weekly; //daily is interpreted as repeating && !weekly
	int alarmId;
	TimeTrigger* next; //creates a linked list, must be sorted by timeTrigger

 	TimeTrigger(long time);
 	
}; 


class TimeTriggerManager 
{
	TimeTrigger* nextTrigger; //pointer to next trigger that needs to run

public:
	TimeTriggerManager();
	void addAlarm(int hr, int min, int sec);
};

extern TimeTriggerManager Alarm;  



#endif