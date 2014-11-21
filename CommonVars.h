#ifndef COMMON_VARS_H
#define COMMON_VARS_H

#define WEBDUINO_NO_IMPLEMENTATION

#include <Ethernet.h>
#include <EthernetUdp.h>
#include "WebServer.h"

// no-cost stream operator as described at 
// http://sundial.org/arduino/?page_id=119
template<class T>
inline Print &operator <<(Print &obj, T arg)
{ obj.print(arg); return obj; }

byte mac[] = { 
    0xDE, 0xAD, 0xBE, 0xAF, 0xFE, 0xED };
IPAddress ip(192,168,0,210);
IPAddress gateway(192,168,0,1);
IPAddress subnet (255,255,255,0);

#define PREFIX ""
#define OUTLETS 3

WebServer webserver(PREFIX, 8088);

int pins[] = {5, 6, 7};
bool *pinVals;

#endif