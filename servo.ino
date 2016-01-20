/*
 * small test connecting servo to MQTT using a spark photon
 */
#include "MQTT.h"

Servo myservo;

int led1 = D7; // Instead of writing D0 over and over again, we'll write led1
int mdelay = 5000;

void callback(char* topic, byte* payload, unsigned int length);

MQTT client("iot.eclipse.org", 1883, callback);

// recieve message
void callback(char* topic, byte* payload, unsigned int length) {
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;
    String message(p);

    int degree = atoi(message);
    myservo.write(degree);
}

void setup() {
    pinMode(led1, OUTPUT);
    myservo.attach(D0);
    myservo.write(40);

     // connect to the server
    client.connect("servoclient");

    if (client.isConnected()) {
         client.subscribe("/moxdlab/particle/servo");
    }
}

void loop() {
    if (client.isConnected())
        client.loop();
}
