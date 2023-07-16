#include <WiFi.h>
#include <WebServer.h>
#include "Main_Page.h"

IPAddress actual_ip;
IPAddress page_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
IPAddress ip;

WebServer server(80);

const char* WIFI_NAME = "NAME";
const char* WIFI_PASSWORD = "PASS";

char xml_buffer[2048]; // buffer for XML operations
char buffer[64]; // buffer to make operations (add stuff to the XML)

void setup() {
  Serial.begin(9600);
 
	WiFi.begin(WIFI_NAME,WIFI_PASSWORD);

	while(WiFi.status() != WL_CONNECTED) {} // while it's not connected to wifi, try to connect to it. We don't need to do nothin' inside this loop 'cause we don't do this process manually!

  Serial.print("Go to: ");
  Serial.println(WiFi.localIP());

  actual_ip = WiFi.localIP();

  server.on("/", send_website);

  server.begin();
}

void loop() {
  server.handleClient();  
}

void send_website() {
  Serial.println("Sending HTML");

  server.send(200, "text/html", MAIN_PAGE);
}

void send_xml() {}
