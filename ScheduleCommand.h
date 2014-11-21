/*
* Files used to display and handle page for scheduling events
*/

#ifndef SCHEDULE_COMMAND_H
#define SCHEDULE_COMMAND_H
#define WEBDUINO_NO_IMPLEMENTATION

#include <WebServer.h>
#include "Common.h"

extern int OUTLETS;
extern int pins[];
extern bool *pinVals;

void generateHTMLSchedule(WebServer &server);
void scheduleForm(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete);

#endif