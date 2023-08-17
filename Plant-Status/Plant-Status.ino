// code obtained from: https://github.com/KrisKasprzak/ESP32_WebPage and https://how2electronics.com/interface-capacitive-soil-moisture-sensor-arduino/

#include <WiFi.h>
#include <WebServer.h>
#include "Main_Page.h"

#define SENSOR_PIN 36
#define WIFI_NAME "HOMERSIMPSON"
#define WIFI_PASSWORD "4D2A1BC2"
#define NETWORK_NAME "PlantStatusChecker"
#define NETWORK_PASS "plantstatus22"
//#define PRODUCTION

// vars for creating an access point, in last case
IPAddress local_ip(192,168,1,180);
IPAddress gateway(192,168,2,227);
IPAddress subnet(255,255,255,0);

WebServer server(80);

char xml[2048]; // buffer for XML operations
char buffer[64]; // buffer to make operations (add stuff to the XML)

int soil_moisture = 0;

void setup() {
	Serial.begin(9600);

#ifndef PRODUCTION
	init_wifi();
#endif

#ifdef PRODUCTION
	init_ap();
#endif

	init_routes();
	server.begin();
}

void loop() {
	//soil_moisture = analogRead(SENSOR_PIN);
	soil_moisture += 1;

	server.handleClient();
}

void init_wifi() {
	WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

	while(WiFi.status() != WL_CONNECTED) {} // while it's not connected to wifi, try to connect to it.

	Serial.print("\nGo to: ");
	Serial.println(WiFi.localIP());
}

void init_ap() {
	WiFi.softAP(NETWORK_NAME, NETWORK_PASS);
	WiFi.softAPConfig(local_ip, gateway, subnet);

	Serial.println(WiFi.softAPIP());
}

void init_routes() {
	server.on("/", send_website);
	server.on("/xml", send_xml);
	server.on("/update_moisture", update_moisture);
}

void send_website() {
	server.send(200, "text/html", MAIN_PAGE);
}

void send_xml() {
	strcpy(xml, "<?xml version = '1.0'?>\n<Data>\n"); // must keep. xml header.

	// https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm
	sprintf(buffer, "<Moisture>%d</Moisture>", soil_moisture);
	strcat(xml, buffer);

	strcat(xml, "</Data>\n");
	server.send(200, "text/xml", xml);
}

void update_moisture() {
	String moist_state = server.arg("value"); //creates a arg to be used in the URL

	strcpy(buffer, "");
	sprintf(buffer, "%d", soil_moisture);
	sprintf(buffer, buffer);

	server.send(200, "text/plain", buffer);
}
