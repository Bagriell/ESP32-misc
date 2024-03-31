#include <WiFi.h>

#define port 80

// router id
const char *ssid_Router = "********";
// router pwd
const char *password_Router = "********";
WiFiServer server(port);

void setup()
{
    Serial.begin(115200);
    Serial.printf("\nConnecting to ");
    Serial.println(ssid_Router);
    WiFi.disconnect();
    WiFi.begin(ssid_Router, password_Router);
    delay(1000);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.printf("IP port: %d\n", port);
    server.begin(port);
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);
}

void loop()
{
    // listen for incoming clients
    WiFiClient client = server.available();

    if (client)
    {
        Serial.println("Client connected.");
        while (client.connected())
        {
            // if there's bytes to read from the client
            if (client.available())
            {
                Serial.println(client.readStringUntil('\n'));
                while (client.read() > 0)
                    ; // clear the wifi receive area cache
            }
            if (Serial.available())
            {                                               // if there's bytes to read from the serial monitor,
                client.print(Serial.readStringUntil('\n')); // print it out the client.
                while (Serial.read() > 0)
                    ; // clear the wifi receive area cache
            }
        }
        client.stop();
        Serial.println("Client Disconnected.");
    }
}
