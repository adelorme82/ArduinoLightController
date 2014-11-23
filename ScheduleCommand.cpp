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
        "Time <input type=\"time\" name=\"time\" value=\""
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
    debug("hour()", hour());
    debug("minute()", minute());
    debug("second()", second());
    debug("isAM()", isAM());

    if (hour() < 10) server << '0';
    server << hour();
    server << ':';

    if (minute() < 10) server << '0';
    server << minute();
    server << ':';

    if (second() < 10) server << '0';
    server << second();

    server.printP(htmlhead2);

    debug("showSuccess", showSuccess);
    debug("OUTLETS", OUTLETS);
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
        debug("===============about to process params====================");
        do
        {
            repeat = server.readPOSTparam(name, buf_size, value, buf_size);
            debug("name", name);
            debug("value", value);
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
                    int pinIndex = strtoul(name + 4, NULL, 10);
                    debug("pinIndex", pinIndex);

                    //convert value string to number representation
                    //e.g. "-1" -> -1 (int)
                    int val = atoi(value);
                    debug("val", val);
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
            debug("======================");
        } while (repeat);
        debug("===============finish process params====================");

        addAlarmsForSelectedTimes(daysToAdd, pinsToAdd, entered_time, alarmIsRepeat);
        showSuccess = true;

    }
    generateHTMLSchedule(server, showSuccess);

}

tmElements_t readTime(char* value)
{
    tmElements_t timeVals;

    return timeVals;
}

void addAlarmsForSelectedTimes(char daysToAdd, int* pinsToAdd, tmElements_t entered_time, bool alarmIsRepeat)
{

}