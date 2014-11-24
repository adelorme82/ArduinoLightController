#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <WebServer.h>

//---Global vars, debug methods
#include "Common.h"

//---Code to manage current time, schedule alarms, trigger actions
#include "ExternalTime.h"
#include "Time.h"
#include <TimeAlarms.h>
#include "Callbacks.h"

//---Code to generate and control page actions
#include "DirectControl.h"
#include "ScheduleCommand.h"

//==========START GLOBAL VARIABLE DECLARATION==============
extern byte mac[6] = { 0xDE, 0xAD, 0xBE, 0xAF, 0xFE, 0xED };
extern IPAddress ip(192,168,0,210);
extern IPAddress gateway(192,168,0,1);
extern IPAddress subnet (255,255,255,0);

#define PREFIX ""

extern WebServer webserver(PREFIX, 8088);

//allow on-the-fly redifinition of which physical pin controls 
//functions, which assume a 0-based, single incrementing pin scheme
extern const int PINS[] = {5, 6, 7};
extern bool *pinVals = NULL;
//==========END GLOBAL VARIABLE DECLARATION================

void startServer()
{
    Serial.println("Trying to get an IP Address using DHCP");
    if (!Ethernet.begin(mac))
    {
        Serial.println("failed to configure Ethernet using DHCP");
        Ethernet.begin(mac, ip, gateway, subnet);
    }
    Serial.println("End getting IP Address");

    webserver.begin();
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());

    webserver.setDefaultCommand(&directControlForm);
    webserver.addCommand("control", &directControlForm);
    webserver.addCommand("control.html", &directControlForm);

    webserver.addCommand("schedule", &scheduleForm);
    webserver.addCommand("schedule.html", &scheduleForm);
}

void setup() 
{
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for Leonardo only
    }
    Serial.println("InteravtiveServer.ino"); //keep track of what is on arduino

    //---Setup pins defined in PINS array as output
    pinVals = (bool*)malloc(OUTLETS * sizeof(bool));
    for (int pinIndex = 0; pinIndex < OUTLETS; pinIndex++)
    {
        int arduinoPinNumber = PINS[pinIndex];
        pinMode(arduinoPinNumber, OUTPUT);
    }

    startServer();

    //---Borrow client from webserver to make request to
    //---External server to get time
    EthernetClient client = webserver.getClient();
    // setClientForExternalTime(client);
    setTimeFromWeb(client);
}


void loop() 
{
    webserver.processConnection();
    
    //service the registered alarms
    Alarm.delay(0);

}