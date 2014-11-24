/* 
* Control of page to view all currently registered alarms
* */

#ifndef REVIEW_ALARMS_H 
#define REVIEW_ALARMS_H 
#define WEBDUINO_NO_IMPLEMENTATION

#include <WebServer.h>
#include "Common.h"
#include <Time.h>
#include <TimeAlarms.h>
#include "Callbacks.h"

char* DOW[] = { "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday", "Saturday" };
void generateReviewHTML(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete);




#endif