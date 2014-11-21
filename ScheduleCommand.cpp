#include "ScheduleCommand.h"

void generateHTMLSchedule(WebServer &server)
{
    P(htmlHead) =
        "<html>"
        "<head>"
        "<title>Austin's Web Server</title>"
        "</head>"
        "<body>"
        "<script>"
        "function setBox(elementId, value)"
        "{"
        "document.getElementById(elementId).value = value;"
        "}"
        "</script>"
    ;

    server.httpSuccess();
    server.printP(htmlHead);

    P(formHead) = "<form method=\"post\">";
    P(tableFormEnd) = 
        "</table>"
        "</form>"
    ;

    P(inputPart1) = "<input id=\"l";
    // style=\"display:none\"
    P(inputPart2) = "\" name=\"l";

    P(rowPart1) = 
        "<tr>"
        "<td>"
        "<p>Outlet "
    ;

    P(rowPart2) = 
        "</p>"
        "</td>"
        "<td>"
        "<button type=\"submit\" onclick=\"setBox('l"
    ;

    P(rowPart3) = 
        "', 1);\">On</button>"
        "</td>"
        "<td>"
        "<button type=\"submit\" onclick=\"setBox('l"
    ;

    P(rowPart4) = 
        "', 0);\">Off</button>"
        "</td>"
        "</tr>"
        ;


    server.printP(formHead);


    for (int i = 0; i < OUTLETS; i++)
    {
        server.printP(inputPart1);
        server << i;
        server.printP(inputPart2);
        Serial.print("pinVals[pins[i]]: ");
        Serial.println(pinVals[pins[i]]);
        server << i << "\" value=\"" << (pinVals[pins[i]] ? "1" : "0") << "\">";
        
    }

    server << "<table>";

    for (int i = 0; i < OUTLETS; i++)
    {
        server.printP(rowPart1);
        server << i;
        server.printP(rowPart2);
        server << i;
        server.printP(rowPart3);
        server << i;
        server.printP(rowPart4);
    }

    server.printP(tableFormEnd);
}

void scheduleForm(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{

    if (type == WebServer::POST)
    {
        bool repeat;
        char name[16], value[16];
        do
        {
            repeat = server.readPOSTparam(name, 16, value, 16);
            Serial.print("name: ");
            Serial.println(name);
            Serial.print("value: ");
            Serial.println(value);

            if (name[0] == 'l')
            {
                int pinIndex = strtoul(name + 1, NULL, 10);
                Serial.print("pinIndex: ");
                Serial.println(pinIndex);

                int pin = pins[pinIndex];
                Serial.print("pin: ");
                Serial.println(pin);

                bool val = strcmp(value, "1") == 0;

                Serial.print("val: ");
                Serial.println(val);
                digitalWrite(pin, val);
                pinVals[pin] = val;
            }
        } while (repeat);


    }
    generateHTMLSchedule(server);

}