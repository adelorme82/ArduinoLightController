/*
* Includes some debug statements, as well as common operators
*/
#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>

#define OUTLETS 3
#define EXTERNAL_INTERNET 1
#define BASE_TEN 10
#define FIRST_TWO_DIGIT_NUMBER 10
#define OUTLET_TIME_DELAY 1000

#define HEADER_LINKS "<table><tr>" \
"<td><a href=\"/control.html\">Direct Control</a></td>" \
"<td><a href=\"/schedule.html\">Schedule Events</a></td>" \
"<td><a href=\"/view.html\">View Scheduled Events</a></td>" \
"</tr></table>"

// no-cost stream operator as described at 
// http://sundial.org/arduino/?page_id=119
template<class T>
inline Print &operator <<(Print &obj, T arg)
{ obj.print(arg); return obj; }

//=================DEBUGS============
//0 args
static void debug()
{
	Serial.println("-----------------\n");
}

//one arg
template <typename Type>
static void debug(Type msg) { Serial.println(msg); }

//two args, same type
template <typename TypeA>
static void debug(TypeA msg, TypeA label)
{
	Serial.print(msg);
	Serial.print(": ");
	Serial.println(label);
}

//two args, diff types
template <typename TypeA, typename TypeB>
static void debug(TypeA msg, TypeB label)
{
	Serial.print(msg);
	Serial.print(": ");
	Serial.println(label);
}

//two args, diff types, include format
template <typename TypeA, typename TypeB, typename format>
static void debug(TypeA msg, TypeB label, format fmt)
{
	Serial.print(msg);
	Serial.print(": ");
	Serial.println(label, fmt);
}

#endif