#include <SPI.h>
#include "DirectControl.h"
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "WebServer.h"
#include "external_time.h"
#include "Time.h"
// #include "TimeTrigger.h"
#include "debug.h"
#include "CommonVars.h"

void startServer()
{
    Serial.println("Trying to get an IP Address using DHCP");
    if (!Ethernet.begin(mac))
    {
        Serial.println("failed to configure Ethernet using DHCP");
        Ethernet.begin(mac, ip, gateway, subnet);
    }
    Serial.println("End getting IP Address");
    // // start the Ethernet connection and the server:
    // Ethernet.begin(mac, ip);

    webserver.begin();
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());

    // webserver.setDefaultCommand(&formCmd);
}

void setup() 
{

    Serial.begin(9600);
     while (!Serial) {
        ; // wait for serial port to connect. Needed for Leonardo only
    }
    Serial.println("InteravtiveServer.ino"); //keep track of what is on arduino

    pinVals = (bool*)malloc(SIZE(pins) * sizeof(bool));

    // startServer();
    // EthernetClient client = webserver.getClient();
    // setClient(client);
}


void loop() 
{
    // webserver.processConnection();
}