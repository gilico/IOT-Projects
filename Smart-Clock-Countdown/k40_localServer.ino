#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress apIP(55, 55, 55, 55);

const char* ssid = "GilCohen"; //my network name
const char* password = "Aa1234"; // my network password

ESP8266WebServer server(80); // use port 80


void wifi_setup(){
  WiFi.mode(WIFI_AP_STA); // access point - work mode - static timing analisys - validation
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00  - class c   
  WiFi.softAP(ssid); // if password is not needed to log only use the ssid network name
  //WiFi.softAP(ssid, password); // when password is needed 
  server.on("/", handleRoot); 
  server.onNotFound(handleNotFound); 
  server.begin(); 
}

void handleRoot(){
  int mm;
  // if the get is "timeVal" at the html
  if (server.hasArg("timeVal")) {
    mm = server.arg("timeVal").toInt(); // get the integer from the get
    measureTotalTime += 60 * mm; // set the main second to the timeVal times 60 seconds
  }
  else if(server.hasArg("mm")){
    mm = server.arg("mm").toInt(); 
    measureTotalTime += 60 * mm; 
  }
  char tmp[7] = "";
  char html[2000] = "";
  
  strcat(html, "<!DOCTYPE html>");
  strcat(html, "<html lang=\"en\">");
  strcat(html, "<head>");
  strcat(html, "<meta charset=\"UTF-8\">");
  strcat(html, "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
  strcat(html, "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
  strcat(html, "<title>My IOT Clock</title>");
  strcat(html, "<style>");
  strcat(html, "#wrapper{width: 50%;margin: 0 auto;}");
  strcat(html, ".block{margin-top: 15px;display: flex;flex-wrap: wrap;justify-content: center;align-items: center;}");
  strcat(html, ".block *{margin-left: 15px;}");
  strcat(html, "#submit{border-radius: 50%;height: 50px;width: 70px;}");
  strcat(html, "h1{text-align: center;}");
  strcat(html, "</style>");
  strcat(html, "</head>");
  strcat(html, "<body>");
  strcat(html, "<div id=\"wrapper\">");
  strcat(html, "<h1>Use 7 Segment - Add Time</h1>");
  strcat(html, "<h2>Current Measure Time: </h2>");
  
//  itoa(measureTotalTime, tmp, 10);
  int m = measureTotalTime / 60;
  int s = measureTotalTime % 60;
  char mint[2] = "";
  char secs[2] = "";
  itoa(m, mint, 10);
  itoa(s, secs, 10);
  strcat(tmp, mint);
  strcat(tmp, ":");
  strcat(tmp, secs);
  strcat(html, tmp);

  strcat(html, "<form method=\"get\">");
  strcat(html, "<div class=\"block\">");
  strcat(html, "<button name=\"timeVal\" value=\"1\">1 minutes</button>");
  strcat(html, "<button name=\"timeVal\" value=\"5\">5 minutes</button>");
  strcat(html, "</div>");
  strcat(html, "<hr>");
  strcat(html, "<div class=\"block\">");
  strcat(html, "<label>Enter Minutes: <input type=\"number\"  name=\"mm\"/></label>");
  strcat(html, "<button id=\"submit\">Send</button>");
  strcat(html, "</div>");
  strcat(html, "</form>");
  strcat(html, "</div>");
  strcat(html, "</body>");
  strcat(html, "</html>");
  
  server.send(200, "text/html", html);
}

void handleNotFound(){
  String message = "File Not Foundnn";

  message += "URI: ";
  message += server.uri();
  message += "nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "nArguments: ";
  message += server.args();
  message += "n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "n";
  }
  
  server.send(404, "text/plain", message);
}

void wifi_loop() {
  server.handleClient();//.server is defined at this tab
  delay(10);
} 
