#include <WiFi.h>
#include <WebServer.h>
#include "Main_Page.h"

IPAddress actual_ip;
IPAddress page_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
IPAddress ip;

WebServer server(80);

#define WIFI_NAME = "NAME";
#define WIFI_PASSWORD = "PASS";

char xml[2048]; // buffer for XML operations
char buffer[64]; // buffer to make operations (add stuff to the XML)
int soil_moisture = 413; // dummy value

void setup() {
  Serial.begin(9600);
 
	WiFi.begin(WIFI_NAME,WIFI_PASSWORD);

	while(WiFi.status() != WL_CONNECTED) {} // while it's not connected to wifi, try to connect to it. We don't need to do nothin' inside this loop 'cause we don't do this process manually!

  Serial.print("Go to: ");
  Serial.println(WiFi.localIP());

  actual_ip = WiFi.localIP();

  server.on("/", send_website);
  server.on("/xml", send_xml);

  server.begin();
}

void loop() {
  server.handleClient();  
}

void send_website() {
  Serial.println("Sending HTML");

  server.send(200, "text/html", MAIN_PAGE);
}

void send_xml() {
  Serial.println("Sending XML");

  strcpy(xml, "<?xml version = '1.0'?>\n<Data>\n"); // must keep. xml header.

// to send data to the XML you can use those C flags (%d, %i, %c, etc)
// we will need to sprintf what we want to the buffer
// and then strcat from the buffer to the xml buffer
  sprintf(buffer, "<Moisture>%d</Moisture>", soil_moisture);
  strcat(xml, buffer);

  strcat(xml, "</Data>\n");

  server.send(200, "text/xml", xml);
}
