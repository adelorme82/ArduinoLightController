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
#include "ReviewAlarms.h"

//==========START GLOBAL VARIABLE DECLARATION==============
extern byte mac[6] = { 0xDE, 0xAD, 0xBE, 0xAF, 0xFE, 0xED };
extern IPAddress ip(192,168,0,210);
extern IPAddress gateway(192,168,0,1);
extern IPAddress subnet (255,255,255,0);

#define PREFIX ""

extern WebServer webserver(PREFIX, 80);

//allow on-the-fly redifinition of which physical pin controls 
//functions, which assume a 0-based, single incrementing pin scheme
//two arrays needed. 
//To turn off outlet, send high to pin in PINS_OFF
//To turn on outlet, send high to pin in PINS_ON
extern const int PINS_ON[]  = {3, 7, 11};
extern const int PINS_OFF[] = {5, 9, 13};
extern bool *pinVals = NULL;

extern char* DOW_MAP[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

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

    //set functions to call when pages are visited
    //file type doesnt matter (.html), I chose it because it's familiar
    webserver.setDefaultCommand(&directControlForm);
    
    webserver.addCommand("direct", &directControlForm);
    webserver.addCommand("direct.html", &directControlForm);
    webserver.addCommand("control", &directControlForm);
    webserver.addCommand("control.html", &directControlForm);

    webserver.addCommand("schedule", &scheduleForm);
    webserver.addCommand("schedule.html", &scheduleForm);

    webserver.addCommand("view", &generateReviewHTML);
    webserver.addCommand("view.html", &generateReviewHTML);
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
        pinVals[pinIndex] = false;

        int arduinoPinNumber = PINS_ON[pinIndex];
        pinMode(arduinoPinNumber, OUTPUT);
        digitalWrite(arduinoPinNumber, LOW);

        arduinoPinNumber = PINS_OFF[pinIndex];
        pinMode(arduinoPinNumber, OUTPUT);
        digitalWrite(arduinoPinNumber, HIGH);

    }

    startServer();

    //---Borrow client from webserver to make request to
    //---External server to get time
    EthernetClient client = webserver.getClient();
    setTimeFromWeb(client);
}


void loop() 
{
    webserver.processConnection();
    
    //service the registered alarms
    Alarm.delay(0);

}