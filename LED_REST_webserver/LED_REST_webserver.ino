/*
 Created by Rui Santos
 Visit: http://randomnerdtutorials.com for more arduino projects

 Arduino with Ethernet Shield
 */

#include <SPI.h>
#include <Ethernet.h>
#define NUMCOLORS 6
#define DEBUG
#define DHCP


typedef struct {
  String ColorTag;
  String ButtonText;
  byte RedValue;
  byte GreenValue;
  byte BlueValue;
} RGBColor;

// RGBColor Colors[NUMCOLORS];

RGBColor Colors[] = {
                      {"zwart", "Uit", 0, 0, 0},
                      {"wit", "Wit", 255, 255, 255},
                      {"rood", "Rood", 255, 0, 0},
                      {"geel", "Geel", 255, 255, 0},
                      {"groen", "Groen", 0, 255, 0},
                      {"blauw", "Blauw", 0, 0, 255}
                     };

int led = 2;
int ledRedPin = 3;
int ledGreenPin = 5;
int ledBluePin = 6;


int pos = 0; 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0x00, 0x00, 0x01 };   //physical mac address

// only used if DHCP is inactive
byte ip[] = { 192, 168, 0, 178 };                      // ip in lan (that's what you need to use in your browser. ("192.168.1.178")
byte gateway[] = { 192, 168, 0, 1 };                   // internet access via router
byte subnet[] = { 255, 255, 255, 0 };                  //subnet mask

EthernetServer server(80);                             //server port     
String readString;


void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode(led, OUTPUT);
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);  

// Set default color (index 0, black)
  SetColor(0);

#ifdef DHCP
  Ethernet.begin(mac);
#else
  Ethernet.begin(mac, ip, gateway, subnet);
#endif  
  server.begin();

#ifdef DEBUG
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  for(int i=0; i<NUMCOLORS; i++) { Serial.println(Colors[i].ButtonText); };
#endif


}

void SetColor(int ColorIndex) 
{
#ifdef DEBUG
  Serial.print("Setting Color = ");
  Serial.println(ColorIndex);
#endif
  if ((ColorIndex >= 0) && (ColorIndex < NUMCOLORS)) 
  {
#ifdef DEBUG
    Serial.print("Red  =");
    Serial.println(Colors[ColorIndex].RedValue);
    Serial.print("Green=");
    Serial.println(Colors[ColorIndex].GreenValue);
    Serial.print("BlueG=");
    Serial.println(Colors[ColorIndex].BlueValue);
#endif
    analogWrite(ledRedPin, Colors[ColorIndex].RedValue);
    analogWrite(ledGreenPin, Colors[ColorIndex].GreenValue);
    analogWrite(ledBluePin, Colors[ColorIndex].BlueValue);        
  }
}

void loop() {
  // Create a client connection
  EthernetClient client = server.available();

  String Response;
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
        //read char by char HTTP request
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
          //Serial.print(c);
         }

         //if HTTP request has ended
         if (c == '\n') {          
 #ifdef DEBUG
           Serial.println(readString); //print to serial monitor for debuging
 #endif
           client.println("HTTP/1.1 200 OK"); //send new page
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");
           client.println("<HEAD>");
           client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
           client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
           client.println("<link rel='stylesheet' type='text/css' href='http://doethet.nl/css/ledcontrol.css' />");
           client.println("<TITLE>Verlichting Werktafel</TITLE>");
           client.println("</HEAD>");
           client.println("<BODY>");
           client.println("<H1>Verlichting Werktafel</H1>");
           client.println("<hr />");
           client.println("<br />");  
           client.println("<H2>Arduino with Ethernet Shield</H2>");
           client.println("<br />");  

           for(int i=0; i<NUMCOLORS; i++) 
           {
            client.print("<a href=\"/?");
            client.print(Colors[i].ColorTag);
            client.print("\"\>");
            client.print(Colors[i].ButtonText);
            client.println("</a>");
           }

           client.println("<br />"); 
           client.println("</BODY>");
           client.println("</HTML>");
     
   //        delay(1);
           //stopping client
           client.stop();
           //controls the Arduino if you press the buttons

           Response = readString;

           for (int i=0; i<NUMCOLORS; i++) 
           {              
              if(Response.indexOf(Colors[i].ColorTag)>0)
              {
                SetColor(i);
              }
           }
             
           //clearing string for next read
           readString="";  
           
         }
       }
    }
}
}
