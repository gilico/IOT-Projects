#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress apIP(55, 55, 55, 55);

const char* ssid = "GilCohenLed"; //my network name

ESP8266WebServer server(80); // use port 80


void wifi_setup(){
  WiFi.mode(WIFI_AP_STA); // access point - work mode - static timing analisys - validation
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00  - class c   
  WiFi.softAP(ssid); // if password is not needed to log only use the ssid network name
  
  server.on("/", handleRoot); 
  server.onNotFound(handleNotFound); 
  server.begin(); 
}

void handleRoot(){
  String hex;
  char rgb[10] = "";
  // if the get is "color" at the html
  if (server.hasArg("color")) {
    hex = server.arg("color"); // get the integer from the get
    HexToLedRGB(hex); // send the server's argument value to convert it from hex
  }
  
  char html[2000] = "";
  
  strcat(html, "<!DOCTYPE html>");
  strcat(html, "<html lang=\"en\">");
  strcat(html, "<head>");
  strcat(html, "<meta charset=\"UTF-8\">");
  strcat(html, "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
  strcat(html, "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
  strcat(html, "<title>My Smart LED</title>");
  strcat(html, "<style>");
  strcat(html, "#wrapper{width: 50%;margin: 0 auto;}");
  strcat(html, ".block{margin-top: 15px;}");
  strcat(html, "h1{text-align: center;}");
  strcat(html, "form{text-align: center;}");
  strcat(html, "label{display: block; margin-bottom: 50px;}");
  strcat(html, "button{margin-right: 10px}");
  strcat(html, "</style></head><body>");
  strcat(html, "<div id=\"wrapper\">");
  strcat(html, "<h1>My Smart LED</h1>");
  strcat(html, "<form method=\"get\">");
  strcat(html, "<label>choose color: <input type=\"color\" name=\"color\" ></label>");
  strcat(html, "<button value=\"#000000\">Turn off</button>");
  strcat(html, "<button type=\"submit\">submit color</button>");
  strcat(html, "</form></div></body></html>");
  
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
  server.handleClient();
  delay(10);
} 
