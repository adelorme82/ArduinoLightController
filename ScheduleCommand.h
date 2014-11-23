/*
* Files used to display and handle page for scheduling events
*/

#ifndef SCHEDULE_COMMAND_H
#define SCHEDULE_COMMAND_H
#define WEBDUINO_NO_IMPLEMENTATION

#include <WebServer.h>
#include "Common.h"
#include <Time.h>

extern const int OUTLETS;
extern const int PINS[];
extern bool *pinVals;

void generateHTMLSchedule(WebServer &server, bool showSuccess = false);
void scheduleForm(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete);


//helper methods to read params
tmElements_t readTime(char* value);

void addAlarmsForSelectedTimes(char daysToAdd, int* pinsToAdd, tmElements_t entered_time, bool alarmIsRepeat);
#endif