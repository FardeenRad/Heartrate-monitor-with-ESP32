
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

//----------------------------------------

#include "Index.h" //--> Our HTML webpage contents with javascripts

#define ON_Board_LED 2  //--> Defining an On Board LED (GPIO2 = D2), used for indicators when the process of connecting to a wifi router and when there is a client request.

//----------------------------------------SSID and Password of your WiFi router
const char* ssid = "Galaxy A30s0568";  //--> Your wifi name
const char* password = "meem1234"; //--> Your wifi password
//----------------------------------------

int BPM;


WebServer server(80);  //--> Server on port 80












//--------------------------------------------------------------------------------void handleRoot()
// This subroutine is executed when NodeMCU ESP12E IP is opened in the browser.
void handleRoot() {
 String s = MAIN_page; //--> Read HTML contents
 server.send(200, "text/html", s); //--> Send web page
}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------void handleHeartRate()
// This subroutine is executed when there is a request from the browser / client.
// This subroutine will send / display the BPM value to the browser.
void handleHeartRate() {
  digitalWrite(ON_Board_LED, LOW); //--> "ON_Board_LED" will be turned on when the request from the browser / client starts.
  String BPMvalSend = String(BPM); 
  server.send(200, "text/plane", BPMvalSend); //--> Sends BPM value to client request / browser.
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the LED because the client request / browser has been processed.
}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------void GetHeartRate()
// This subroutine is for reading the heart rate and calculating it to get the BPM value.
// To get a BPM value based on a heart rate reading for 10 seconds.
















//--------------------------------------------------------------------------------void setup()
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);
    
  pinMode(ON_Board_LED,OUTPUT); //--> On Board LED port Direction output
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off Led On Board


  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");

  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  //----------------------------------------If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //----------------------------------------

  server.on("/", handleRoot); //--> Which routine to handle at root location. This is display page
  server.on("/getHeartRate", handleHeartRate); //--> This page is called in the javascript code in the Index.h file

  server.begin(); //--> Start server
  Serial.println("HTTP server started");

  Serial.println();
  Serial.println("Please wait 10 seconds to get the BPM Value");
}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------void loop()
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient(); //--> Handle client requests
  BPM= Serial.read(); //Read the serial data and store in var
  
  Serial.println(BPM); //Print data on Serial Monitor
  delay(1000);
}
