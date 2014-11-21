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

EthernetClient timeClient;

//For use in using the client that is hidden behind the webserver
void setClient(EthernetClient &client)
{
    timeClient = client;
}

/*
* http://playground.arduino.cc//Code/Webclient
*/
void setTimeFromWeb()
{

    int hour = 8;
    int minute = 00;
    setTime(hour,minute,00,16,11,2014); // set time to Sunday 8:00:00am Nov 16 2014


    // unsigned long time = 0;
    // Serial.println(1);
    // // Just choose any reasonably busy web server, the load is really low
    // if (timeClient.connect("www.google.com", 80))
    // {
    //     // Make an HTTP 1.1 request which is missing a Host: header
    //     // compliant servers are required to answer with an error that includes
    //     // a Date: header.
    //     timeClient.print(F("GET / HTTP/1.1 \r\n\r\n"));
    //     Serial.println(2);

    //     char buf[5];            // temporary buffer for characters
    //     timeClient.setTimeout(5000);
    //     Serial.println(3);
    //     if (timeClient.find((char *)"\r\nDate: ") // look for Date: header
    //     && timeClient.readBytes(buf, 5) == 5) // discard
    //     {
    //         Serial.println(4);
    //         unsigned day = timeClient.parseInt();      // day
    //         timeClient.readBytes(buf, 1);      // discard
    //         timeClient.readBytes(buf, 3);      // month
    //         int year = timeClient.parseInt();      // year
    //         byte hour = timeClient.parseInt();   // hour
    //         byte minute = timeClient.parseInt(); // minute
    //         byte second = timeClient.parseInt(); // second
    //         Serial.println(5);

    //         int month;
    //         switch (buf[0])
    //         {
    //             case 'F': month = 2; break; // Feb
    //             case 'S': month = 9; break; // Sep
    //             case 'O': month = 10; break; // Oct
    //             case 'N': month = 11; break; // Nov
    //             case 'D': month = 12; break; // Dec
    //             default:
    //                 if (buf[0] == 'J' && buf[1] == 'a')
    //                     month = 1;       // Jan
    //                 else if (buf[0] == 'A' && buf[1] == 'p')
    //                     month = 4;      // Apr
    //                 else switch (buf[2])
    //                 {
    //                     case 'r': month = 3; break; // Mar
    //                     case 'y': month = 5; break; // May
    //                     case 'n': month = 6; break; // Jun
    //                     case 'l': month = 7; break; // Jul
    //                     default: // add a default label here to avoid compiler warning
    //                     case 'g': month = 8; break; // Aug
    //                 }
    //         }

    //         Serial.println(6);
    //         Serial.print("year: ");
    //         Serial.println(year);
    //         Serial.print("month: ");
    //         Serial.println(month);
    //         Serial.print("day: ");
    //         Serial.println(day);
    //         Serial.print("hour: ");
    //         Serial.println(hour);
    //         Serial.print("minute: ");
    //         Serial.println(minute);
    //         Serial.print("second: ");
    //         Serial.println(second);
    //         setTime(hour,minute,second,day,month,year); // set time to Saturday 8:29:00am Jan 1 2011

    //         // // This code will not work after February 2100
    //         // // because it does not account for 2100 not being a leap year and because
    //         // // we use the day variable as accumulator, which would overflow in 2149
    //         // day += (year - 1970) * 365; // days from 1970 to the whole past year
    //         // day += (year - 1969) >> 2;  // plus one day per leap year 
    //         // day += daysInPrevMonths;    // plus days for previous months this year
    //         // if (daysInPrevMonths >= 59  // if we are past February
    //         //     && ((year & 3) == 0))   // and this is a leap year
    //         //         day += 1;           // add one day
    //         // // Remove today, add hours, minutes and seconds this month
    //         // Serial.println(7);
    //         // time = (((day-1ul) * 24 + hour) * 60 + minute) * 60 + second;
    //     }
    // }
    // Serial.println(8);
    // delay(10);
    // timeClient.flush();
    // Serial.println(9);
    // timeClient.stop();
    // Serial.println(10);

}
