/*
* Files used to display and handle page for direct control of pins
* Through the use of buttons
*/

#ifndef DIRECT_CONTROL_H
#define DIRECT_CONTROL_H
#define WEBDUINO_NO_IMPLEMENTATION

// #include <Ethernet.h>
// #include <EthernetUdp.h>
#include <WebServer.h>
#include "Common.h"

extern int OUTLETS;
extern int pins[];
extern bool *pinVals;

void generateHTMLDirectControl(WebServer &server);
void directControlForm(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete);

#endif