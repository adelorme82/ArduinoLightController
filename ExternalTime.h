#include <Arduino.h> //needed for Serial.println
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <WebServer.h>
#include "Time.h" 


/*
* http://playground.arduino.cc//Code/Webclient
*/
void setTimeFromWeb(EthernetClient &client)
{

    int hour = 8;
    int minute = 00;
    setTime(hour,minute,00,16,11,2014); // set time to Sunday 8:00:00am Nov 16 2014


    // Just choose any reasonably busy web server, the load is really low
    if (EXTERNAL_INTERNET && client.connect("www.google.com", 80))
    {
        // Make an HTTP 1.1 request which is missing a Host: header
        // compliant servers are required to answer with an error that includes
        // a Date: header.
        client.print(F("GET / HTTP/1.1 \r\n\r\n"));

        char buf[5];            // temporary buffer for characters
        client.setTimeout(5000);
        if (client.find((char *)"\r\nDate: ") // look for Date: header
        && client.readBytes(buf, 5) == 5) // discard
        {
            unsigned day = client.parseInt();      // day
            client.readBytes(buf, 1);      // discard, space after day
            client.readBytes(buf, 3);      // month
            int year = client.parseInt();      // year
            byte hour = client.parseInt();   // hour
            byte minute = client.parseInt(); // minute
            byte second = client.parseInt(); // second

            int month;
            switch (buf[0])
            {
                case 'F': month = 2; break; // Feb
                case 'S': month = 9; break; // Sep
                case 'O': month = 10; break; // Oct
                case 'N': month = 11; break; // Nov
                case 'D': month = 12; break; // Dec
                default:
                    if (buf[0] == 'J' && buf[1] == 'a')
                        month = 1;       // Jan
                    else if (buf[0] == 'A' && buf[1] == 'p')
                        month = 4;      // Apr
                    else switch (buf[2])
                    {
                        case 'r': month = 3; break; // Mar
                        case 'y': month = 5; break; // May
                        case 'n': month = 6; break; // Jun
                        case 'l': month = 7; break; // Jul
                        default: // add a default label here to avoid compiler warning
                        case 'g': month = 8; break; // Aug
                    }
            }

            bool hourWrap = hour < 7;
            hour = hourWrap ? (hour + 24 - 7) : (hour - 7);

            //wrapped to previous day
            if (hourWrap)
            {   
                //                J   F   M   A   M   J   J   A   S   O   N   D   
                byte monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

                //leap year
                if (year % 4 == 0) monthDays[1] = 29;

                //new years, wrap to december
                if (day == 1 && month == 1) month = 12;

                //first of month, wrap day to previous month's last day
                if (day == 1) day = monthDays[(month - 2) % 12];
                else day--;

            }
            debug("hour", hour);
            debug("minute", minute);
            debug("second", second);
            debug("day", day);
            debug("month", month);
            debug("year", year);
            setTime(hour,minute,second,day,month,year); // set time to Saturday 8:29:00am Jan 1 2011

        }
    }
    delay(10);
    client.flush();
    client.stop();

}
