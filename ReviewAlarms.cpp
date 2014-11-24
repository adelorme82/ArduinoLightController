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
		"</tr>"
	;

    server.printP(htmlHead);
    server.printP(siteMap);
	server.printP(viewTableheader);

	for (int i = 0; i < dtNBR_ALARMS; i++)
	{
		time_t alarmTriggerTime = Alarm.read(i);
		bool repeating = Alarm.readRepeating(i);
		if (alarmTriggerTime || repeating)
		{
			//sunday is day 1, so subtract for 0-index
			int dow = weekday(alarmTriggerTime) - 1;
			int hr = hour(alarmTriggerTime);
			int min = minute(alarmTriggerTime);
			int sec = second(alarmTriggerTime);
			bool am = isAM(alarmTriggerTime);

			server << "<tr>";
			server << 	"<td>";
			server << 		DOW[dow];
			server << 	"</td>";
			server << 	"<td>";
			server << 		hr << ":" << min << ":" << sec;
			server << 	"</td>";
			server << 	"<td>";
			server << 		(am ? "AM" : "PM");
			server << 	"</td>";
			server << 	"<td>";
			server << 		(repeating ? "Yes" : "No");
			server << 	"</td>";
			server << "</tr>";
		}
	}
	server << "</table></body></html>";
}
