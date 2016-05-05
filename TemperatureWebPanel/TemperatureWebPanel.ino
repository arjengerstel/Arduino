// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
YunServer server;
DHT dht(DHTPIN, DHTTYPE);
String startString;
long hits = 0;
  


void setup() {
  

  Serial.begin(9600);
 
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);

  server.listenOnLocalhost();
  server.begin();

  Process startTime;
  startTime.runShellCommand("date");
  while(startTime.available()) {
    char c = startTime.read();
    startString += c;
  }

  dht.begin();
}

void loop() {
  YunClient client = server.accept();

  if (client) {
    String command = client.readString();
    command.trim();        //kill whitespace
    // Serial.println(command);
    if (command == "temperature") {

      Process time;
      time.runShellCommand("date");
      String timeString = "";
      while(time.available()) {
        char c = time.read();
        timeString += c;
      }
      // Serial.println(timeString);
      float temperature = dht.readTemperature();

      client.print("<h1>Temperature Monitor</h1>");
      client.print("Current time on the Yun: ");
      client.println(timeString);
      client.print("<br>Current temperature: ");
      client.print(temperature);
      client.print(" degrees C");
      client.print("<br>This sketch has been running since ");
      client.print(startString);
      client.print("<br>Hits so far: ");
      client.print(hits);
    }

    client.stop();
    hits++;
  }
  delay(50); // Poll every 50ms
}

  /*
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
} 
*/
