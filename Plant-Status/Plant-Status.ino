#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <ESPmDNS.h>
#include "Main_Page.h"

#define SENSOR_PIN 36
#define WIFI_NAME "HOMERSIMPSON"
#define WIFI_PASSWORD "4D2A1BC2"

WebServer server(80);
HTTPClient http;

char xml[1024]; // buffer for XML operations
char buffer[64]; // buffer to make operations

int soil_moisture = 0;
int processed_moisture = 0;

// values to calibrate the sensor
const int air_value = 2753;
const int water_value = 3111;

// path and parameters to send to MySQL Database
// there's no way to concatenate char* that I know of, so.. strings must do
const String server_path = "http://192.168.1.109/";		// must be a server
const String script_path = "plant-status/enviar.php";	// location of the script that will send to MySQL "query_string"

void setup() {
	Serial.begin(9600);

	init_wifi();
	init_mdns();
	init_routes();

	server.begin();
}

void loop() {
	//  soil_moisture = analogread(sensor_pin);
	//  processed_moisture = map(soil_moisture, air_value, water_value, 0, 100);

	http.begin(server_path + script_path);
	http.addHeader("content-type", "application/x-www-form-urlencoded");

	http.POST("umidade="+string(soil_moisture)); // sends the moisture
	//http.post("umidade="+string(processed_moisture)); // sends the moisture

	//Serial.println(http.getstring());    //print response, debug

	server.handleclient();
	http.end();  // closes connection

	delay(1500);
}

void init_wifi() {
	WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

	while(WiFi.status() != WL_CONNECTED) {} // while it's not connected to wifi, try to connect to it.
}

void init_routes() {
	server.on("/", send_website);
	server.on("/xml", send_xml);
	server.on("/update_moisture", update_moisture);
}

void init_mdns() {
	if(!MDNS.begin("plant")) {
		Serial.println("Error starting mDNS");
	}
}

void send_website() {
	server.send(200, "text/html", MAIN_PAGE);
}

void send_xml() {
	strcpy(xml, "<?xml version = '1.0'?>\n<Data>\n"); // xml header

	sprintf(buffer, "<Moisture>%d</Moisture>", processed_moisture);
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
