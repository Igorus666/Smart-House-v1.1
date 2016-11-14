#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xF8, 0xA9, 0x63, 0x5C, 0xDF, 0x55}; //physical mac address
byte ip[] = { 192, 168, 88, 119 }; // ip in lan
byte gateway[] = { 192, 168, 88, 1 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
EthernetServer server(80); //server port

String readString;

int pin = 9;
boolean ligado = true;

//////////////////////

void setup() {

  pinMode(pin, OUTPUT); //pin selected to control
  //start Ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  //the pin for the servo co
  //enable serial data print
  Serial.begin(9600);
  Serial.println('RoboCore Remote Automation V1.1'); // so I can keep track of what is loaded
}

void loop() {
  // Create a client connection
  EthernetClient client = server.available();
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

          ///////////////////// control arduino pin
          Serial.println(readString); //print to serial monitor for debuging
          if (readString.indexOf('?ligar') > 0) //checks for on
          {
            digitalWrite(pin, HIGH);    // set pin 4 high
            Serial.println('On');
            ligado = false;
          }
          else {
            if (readString.indexOf('?desligar') > 0) //checks for off
            {
              digitalWrite(pin, LOW);    // set pin 4 low
              Serial.println('Off');
              ligado = true;
            }
          }
          //clearing string for next read
          readString = '';


          ///////////////

          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();
          client.println("<html>");
          client.println("<head>");
          client.println("<meta charset='utf-8'>");
          client.println("<meta http-equiv='X-UA-Compatible' content='IE=edge'>");
          client.println("<title>Ardulindo</title>");
          client.println("<link rel='stylesheet' href='resto/CSS.css'>");
          client.println("<script type='text/javascript' src='resto/JavaScript.js'></script>");
          client.println("</head>");
          client.println("<body>");
          client.println("<button type='button' class='la' onclick='lp()'></button>");
          client.println("<button type='button' class='Vent' onclick='vt()'></button>");
          client.println("<button type='button' class='E1' onclick='bt1()'></button>");
          client.println("<button type='button' class='E2' onclick='bt2()'</button>");
          client.println("</body>");
          client.println("</html>");

          delay(1);
          //stopping client
          client.stop();



        }
      }
    }
  }
}


