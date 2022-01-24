#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress apIP(55, 55, 55, 55);

const char* ssid = "GilCohenFan"; //my network name
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
  int way;
  // if the get is "timeVal" at the html
  if (server.hasArg("fanway")) {
    way = server.arg("fanway").toInt(); // get the integer from the get
    setFanByStatus(way);
    delay(50);
  }
  
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
  strcat(html, ".block{margin-top: 15px;}");
  strcat(html, ".on{display: flex;flex-wrap: wrap;justify-content: center;align-items: center;}");
  strcat(html, ".on button{width: 45%; height: 50px;}");
  strcat(html, "button{font-weight:bold}");
  strcat(html, "#stop{margin: 0 auto; display: flex; justify-content: center; margin-top: 20px;}");
  strcat(html, "#stop button{width: 90%; height: 50px; margin-left: 5%; background-color: brown;}");
  strcat(html, "#fwd{background-color: blue}");
  strcat(html, "#bwd{background-color: yellow}");
  strcat(html, ".block *{margin-left: 15px;}");
  strcat(html, "h1{text-align: center;}");
  strcat(html, "</style>");
  strcat(html, "</head>");
  strcat(html, "<body>");
  strcat(html, "<div id=\"wrapper\">");
  strcat(html, "<h1>My Smart Fan</h1>");
  strcat(html, "<form method=\"get\">");
  strcat(html, "<div class=\"block\">");
  strcat(html, "<div class=\"on\">");
  strcat(html, "<button id=\"fwd\" name=\"fanway\" value=\"1\">Forwords</button>");
  strcat(html, "<button id=\"bwd\" name=\"fanway\" value=\"2\">Backwords</button>");
  strcat(html, "</div>");
  strcat(html, "<div id=\"stop\">");
  strcat(html, "<button name=\"fanway\" value=\"0\">Stop</button>");
  strcat(html, "</div>");
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
