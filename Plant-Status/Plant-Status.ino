#include <WiFi.h>
#include <WebServer.h>
#include "Main_Page.h"

#define SENSOR_PIN 36
#define WIFI_NAME "HOMERSIMPSON"
#define WIFI_PASSWORD "4D2A1BC2"
#define NETWORK_NAME "PlantStatusChecker"
#define NETWORK_PASS "plantstatus22"
//#define PRODUCTION

// variables to create an access point
IPAddress local_ip(192,168,1,112);
IPAddress gateway(192,168,2,227);
IPAddress subnet(255,255,255,0);

WebServer server(80);

char xml[2048]; // buffer for XML operationschar
char buffer[64]; // buffer to make operations

int soil_moisture = 0;
//int processed_moisture = 0;

// values to calibrate the sensor
const int air_value = 2753;
const int water_value = 3111;

void setup() {
	Serial.begin(9600);

// macros to define when testing and when is on production
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
// soil_moisture = analogRead(SENSOR_PIN);
// processed_moisture = map(soil_moisture, air_value, water_value, 0, 100);
	soil_moisture += 1;

  if(soil_moisture >= 100)
    soil_moisture = 0;

	server.handleClient();
}

void init_wifi() {
	// if is not possible to configure an ip address
	if(!WiFi.config(local_ip, gateway, subnet))
		Serial.println("Failure to configurate STA device.");
	
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
	strcpy(xml, "<?xml version = '1.0'?>\n<Data>\n"); // xml header

	sprintf(buffer, "<Moisture>%d</Moisture>", processed_moisture);
	strcat(xml, buffer);strcat(xml, "</Data>\n");
	strcat(xml, buffer);

	strcat(xml, "</Data>\n");

	server.send(200, "text/xml", xml);
}

void update_moisture() {
	String server_arg = server.arg("value"); // argument to be used in the URL

	strcpy(buffer, "");
	sprintf(buffer, "%d", processed_moisture);
	sprintf(buffer, buffer);

	server.send(200, "text/plain", buffer);
}
