#ifndef DEBUG_H_
#define DEBUG_H_

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