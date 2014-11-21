/*
* Includes some debug statements, as well as common operators
*/
#ifndef COMMON_H
#define COMMON_H

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

#endif