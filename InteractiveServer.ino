#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <WebServer.h>
#include "Common.h"

#include "ExternalTime.h"
#include "Time.h"

#include "DirectControl.h"
#include "ScheduleCommand.h"

//==========START GLOBAL VARIABLE DECLARATION==============
extern byte mac[6] = { 0xDE, 0xAD, 0xBE, 0xAF, 0xFE, 0xED };
extern IPAddress ip(192,168,0,210);
extern IPAddress gateway(192,168,0,1);
extern IPAddress subnet (255,255,255,0);

#define PREFIX ""
extern int OUTLETS = 3;

extern WebServer webserver(PREFIX, 8088);

extern int pins[] = {5, 6, 7};
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
    webserver.addCommand("control.html", &directControlForm);
    webserver.addCommand("schedule.html", &scheduleForm);
}

void setup() 
{
    Serial.begin(9600);
     while (!Serial) {
        ; // wait for serial port to connect. Needed for Leonardo only
    }
    Serial.println("InteravtiveServer.ino"); //keep track of what is on arduino

    pinVals = (bool*)malloc(SIZE(pins) * sizeof(bool));

    startServer();
    EthernetClient client = webserver.getClient();
    setClient(client);
}


void loop() 
{
    // webserver.processConnection();
}