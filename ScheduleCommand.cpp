#include "ScheduleCommand.h"

void generateHTMLSchedule(WebServer &server, bool showSuccess)
{
    P(htmlHead1) =
        "<html>"
        "<head>"
        "<title>Schedule Events</title>"
        "</head>"
        "<body>"
        "<form method=\"post\">"
        "Alarm Day Of Week"
        "<div>"
        "S <input type=\"checkbox\" name=\"day0\">"
        "M <input type=\"checkbox\" name=\"day1\">"
        "T <input type=\"checkbox\" name=\"day2\">"
        "W <input type=\"checkbox\" name=\"day3\">"
        "T <input type=\"checkbox\" name=\"day4\">"
        "F <input type=\"checkbox\" name=\"day5\">"
        "S <input type=\"checkbox\" name=\"day6\">"
        "</div> "
        "<br />"
        "Repeating? <input type=\"checkbox\" name=\"repeating\"> <br/> <br/>"
        "Time <input type=\"time\" name=\"time\" step=\"1\" value=\""
    ;

    P(htmlhead2) = 
        "\"> <br /> <br/>"
        "Select Outlet "
        "<div>"
    ;

    P(htmlEnd) = 
        "</div>"
        "<br />"
        "<input type=\"submit\">"

        "</form>"
        "</body>"
        "</html>"
    ;

    P(pinEntry1) = 
        "&nbsp;&nbsp;&nbsp;"
        "On <input type=\"radio\" name=\"pin"
    ;

    P(pinEntry2) = 
        "\" value=\"1\">"
        "Off <input type=\"radio\" name=\"pin"
    ;

    P(pinEntry3) = 
        "\" value=\"0\">"
        "Nothing <input type=\"radio\" name=\"pin"
    ;

    P(pinEntry4) = 
        "\" value=\"-1\" checked>"
        "<br />"
    ;

    server.httpSuccess();
    server.printP(htmlHead1);

    //set time element to now
    if (hour() < 10) server << '0';
    server << hour();
    server << ':';

    if (minute() < 10) server << '0';
    server << minute();
    server << ':';

    if (second() < 10) server << '0';
    server << second();

    server.printP(htmlhead2);

    for (int i = 0; i < OUTLETS; i++)
    {
        //label, correct for 0-based index
        server << (i + 1);
        server.printP(pinEntry1);
        server << i;
        server.printP(pinEntry2);
        server << i;
        server.printP(pinEntry3);
        server << i;
        server.printP(pinEntry4);
    }

    server.printP(htmlEnd);
}

void scheduleForm(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
    bool showSuccess = false;
    if (type == WebServer::POST)
    {
        int buf_size = 16;
        bool repeat;
        char name[buf_size], value[buf_size];
        //need 7 binary values (bits), one for each day
        //holds whether that day was selected
        unsigned char daysToAdd = 0;

        //need array of pins that were selected to be on or off
        //store results while parsing params to ensure all params 
        //were read in before processing
        int* pinsToAdd = (int*)malloc(OUTLETS * sizeof(int));

        tmElements_t entered_time;
        bool alarmIsRepeat = false;
        do
        {
            repeat = server.readPOSTparam(name, buf_size, value, buf_size);
            /* valid names for inputs (x means any number):
            * dayx
            * pinx
            * time
            * repeating
            */

            switch(name[0])
            {
                //pin
                case 'p':
                {
                    int pinIndex = strtoul(name + 3, NULL, 10);

                    //convert value string to number representation
                    //e.g. "-1" -> -1 (int)
                    int val = atoi(value);
                    pinsToAdd[pinIndex] = val;
                }
                    break;

                //day
                case 'd':
                    //build up a byte with this mapping
                    //a 1 means to include that day
                    //MSB         LSB
                    //0 0 0 0 0 0 0 0
                    //0 S F T W T M S
                    daysToAdd |= 1 << strtoul(name + 3, NULL, 10);
                    break;

                //time
                case 't':
                    entered_time = readTime(value);
                    break;

                //repeating
                case 'r':
                    //if repeating is sent in form, it was checked. HTML standard.
                    //no processing necessary
                    alarmIsRepeat = true;
                    break;

                default: 
                    break;
            }
        } while (repeat);

        addAlarmsForSelectedTimes(daysToAdd, pinsToAdd, entered_time, alarmIsRepeat);
        showSuccess = true;

    }
    generateHTMLSchedule(server, showSuccess);

}

tmElements_t readTime(char* value)
{
    tmElements_t timeVals;
    timeVals.Hour = atoi(value);
    timeVals.Minute = atoi(value + 3);
    timeVals.Second = atoi(value + 6);
    return timeVals;
}

void addAlarmsForSelectedTimes(unsigned char daysToAdd, int* pinsToAdd, tmElements_t entered_time, bool alarmIsRepeat)
{
    AlarmID_t newAlarmId;
    //allocate only once. Don't need a reference to this (managed internally by class)
    //but constructors dont seem to want to be called without this

    if (!daysToAdd) 
    {
        if (alarmIsRepeat)
        {
            newAlarmId = Alarm.alarmRepeat(entered_time.Hour, entered_time.Minute, entered_time.Second, &(AlarmCallbackHandler::alarmTriggered));
        }
        else
        {
            newAlarmId = Alarm.alarmOnce(entered_time.Hour, entered_time.Minute, entered_time.Second, &(AlarmCallbackHandler::alarmTriggered));
        }
        AlarmCallbackHandler::registerNewAlarm(newAlarmId, pinsToAdd);
    }
    else
    {
        timeDayOfWeek_t days[] = {dowSunday, dowMonday, dowTuesday, dowWednesday, dowThursday, dowFriday, dowSaturday} ;
        unsigned short count = 0;
        unsigned char currentDay;
        while (daysToAdd && count < 8)
        {
            currentDay = daysToAdd & 1;
            daysToAdd >>= 1;
            if (currentDay)
            {
                if (alarmIsRepeat)
                {
                    newAlarmId = Alarm.alarmRepeat(days[count], entered_time.Hour, entered_time.Minute, entered_time.Second, &(AlarmCallbackHandler::alarmTriggered));
                }
                else
                {
                    newAlarmId = Alarm.alarmOnce(days[count], entered_time.Hour, entered_time.Minute, entered_time.Second, &(AlarmCallbackHandler::alarmTriggered));
                }
                
                AlarmCallbackHandler::registerNewAlarm(newAlarmId, pinsToAdd);
            }
            count++;
        }
    }

}