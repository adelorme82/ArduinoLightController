This program will turn the Arduino into a webserver. It will attempt to get a dynamic IP address using DHCP.
The intent was to control three outlets through the web. The method of control was through the use of radio-controlled outlet controllers, which are plugged into a standard outlet and controlled by a small handhelp controller. Turning these devices on will route power through them to whatever is plugged into them.
Since the controller had separate buttons for turning a particular outlet on or off, each of the outlets in the program are represented by two pins.
It will also set its internal clock by getting the time from an external (namely google.com).
Going to the root directory in a browser will bring up the direct control page, allowing pins to be turned on and off instantly.
Going to the schedule page will allow the user to enter a time, some pins, and optionally a week day and a repeating checkbox. 
----If the weekday is not set, then the alarm will be set for the next time the selected time rolls around (e.g. if 7:30 is selected and it is 8:30, it will be set for 7:30 the next day. If it is 9:30 and the alarm is set for 10:30, it will be set for 10:30 - 60 minutes from when it was set). 
----If the repeating checkbox is selected, the alarm will repeat weekly, on the selected day (same rules apply if no day is selected)
Going to the view page will show the user the alarms that they have registered 
The program currently does not preserve alarms if the arduino is turned off


===========NOTES ON LIBRARIES===========
Three libraries were used:

Webduino
https://github.com/sirleech/Webduino

Arduino Time
https://github.com/PaulStoffregen/Time

TimeAlarm (depends on Time)
http://www.pjrc.com/teensy/td_libs_TimeAlarms.html

Note that I added a method to this library.

TimeAlarms.h
	TimeAlarmsClass
		bool readRepeating(AlarmID_t ID);

TimeAlarms.cpp
	bool TimeAlarmsClass::readRepeating(AlarmID_t ID)
    {
        if(isAllocated(ID))
            return !(Alarm[ID].Mode.isOneShot);
        else    
            return dtNotAllocated;  
    }


