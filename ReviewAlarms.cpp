#include "ReviewAlarms.h"

void generateReviewHTML(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
	P(htmlHead) =
        "<html>"
        "<head>"
        "<title>View Scheduled Events</title>"
        "</head>"
        "<body>"
    ;

    P(siteMap) = HEADER_LINKS;

    P(viewTableheader) = 
		"<br />"
		"<table>"
		"<tr>"
		"<th>"
		"Day of Week"
		"</th>"
		"<th>"
		"Time of day"
		"</th>"
		"<th>"
		"AM/PM"
		"</th>"
		"<th>"
		"Repeating?"
		"</th>"
	;

    server.printP(htmlHead);
    server.printP(siteMap);
	server.printP(viewTableheader);

	for (int i = 0; i < OUTLETS; i++)
	{
		server << "<th>";
		server << "Outlet " << (i + 1) << " value";
		server << "</th>";
	}
	server << "</tr>";

	for (int i = 0; i < dtNBR_ALARMS; i++)
	{
		time_t alarmTriggerTime = Alarm.read(i);
		bool repeating = Alarm.readRepeating(i);

		if (alarmTriggerTime || repeating)
		{
			int* pinValues = AlarmCallbackHandler::getNewPinValuesForAlarm(i);
			
			//sunday is day 1, so subtract for 0-index
			int dow = weekday(alarmTriggerTime) - 1;
			int hr = hour(alarmTriggerTime);
			int min = minute(alarmTriggerTime);
			int sec = second(alarmTriggerTime);
			bool am = isAM(alarmTriggerTime);
			hr = am ? hr : hr - 12;
			server << "<tr>";
			server << 	"<td>";
			server << 		DOW_MAP[dow];
			server << 	"</td>";
			server << 	"<td>";
			server << 	       (hr  < FIRST_TWO_DIGIT_NUMBER ? "0" : "") << hr;
			server << 	':' << (min < FIRST_TWO_DIGIT_NUMBER ? "0" : "") << min;
			server << 	':' << (sec < FIRST_TWO_DIGIT_NUMBER ? "0" : "") << sec;
			server << 	"</td>";
			server << 	"<td>";
			server << 		(am ? "AM" : "PM");
			server << 	"</td>";
			server << 	"<td>";
			server << 		(repeating ? "Yes" : "No");
			server << 	"</td>";

			for (int pinNum = 0; pinNum < OUTLETS; pinNum++)
			{
				server << "<td>";
				if (pinValues[pinNum] >= 0) server << (pinValues[pinNum] ? "On" : "Off");
				else server << "N/A";

				server << "</td>";
			}

			server << "</tr>";
		}
	}
	server << "</table></body></html>";
}
