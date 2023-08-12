//code obtained from: https://github.com/KrisKasprzak/ESP32_WebPage
#include <WiFi.h>
#include <WebServer.h>
#include "Main_Page.h"

//#define SENSOR_PIN 36
#define WIFI_NAME "WIFI"
#define WIFI_PASSWORD "PASS"
#define NETWORK_NAME "NET_NAME"
#define NETWORK_PASS "NET_PASS"
//#define PRODUCTION

IPAddress local_ip(192,168,1,180);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

char xml[2048]; // buffer for XML operations
char buffer[64]; // buffer to make operations (add stuff to the XML)

//char* soil_status = "";
///int soil_moisture = analogRead(SENSOR_PIN);
//int soil_moisture = 413;
//const int bad_soil = 1230;
//const int good_soil = 2460;
//const int very_good_soil = 3690;

void setup() {
	Serial.begin(9600);

	init_wifi();
	init_routes();

	server.begin();
}

void loop() {
	server.handleClient();
}

void init_wifi() {
	// if the macro (those things that starts with "#define") named PRODUCTION does not exist, do this...
	// the checking is done at compile time, by the way:
#ifndef PRODUCTION

	WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

	while(WiFi.status() != WL_CONNECTED) {} // while it's not connected to wifi, try to connect to it.

	Serial.print("\nGo to: ");
	Serial.println(WiFi.localIP());

#endif

	// but if does exist...
#ifdef PRODUCTION

	WiFi.softAP(NETWORK_NAME, NETWORK_PASS);
	WiFi.softAPConfig(local_ip, gateway, subnet);

	Serial.print("Select ");
	Serial.print(NETWORK_NAME);
	Serial.print(" and go to ");
	Serial.println(WiFi.softAPIP());

#endif
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
	String moist_state = server.arg("value"); //creates a arg to use in the URL

	strcpy(buffer, "");
	sprintf(buffer, "%d", soil_moisture);
	sprintf(buffer, buffer);

	server.send(200, "text/plain", buffer);
}
