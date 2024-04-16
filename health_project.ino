#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <dht.h>
#include <PulseSensorPlayground.h>
#include <SoftwareSerial.h>
#include <String.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define LED1 10 // blue LED
#define LED2 11 // red LED
#define BUZZ 52

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

dht DHT;
#define DHT11_PIN 5
int const PULSE_SENSOR_PIN= 0;//intialize the heartbeat sensor
int Signal; // variable to store the pulse signals
int Threshold = 530; // maximun threshold


SoftwareSerial SIM800L(6,7);    // Sim module digital pins (rx and tx)
String API_key = "NO8KVXFJGMA7U7OX";  //Thingspeak  API Key
String apn = "MTN Uganda";   // Sim card apn
float heartrate; // heartrate data
float temperatur; //temperatutre data

void setup() {
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(9600);
//----
  // Serial.begin(115200); 
  SIM800L.begin(9600);      
  delay(2000);

//set up the oled display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);

  // display welcome message
  display.setCursor(0, 0);
  display.print("Welcome..");
  display.display();
  delay(2000);
  display.setTextSize(1);
  display.clearDisplay();

  

}

void loop() {
  recordTemperature();

  SetupModule();
  SIM800L.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");
  delay(3000);
  ShowSerialData();
 
  SIM800L.println("AT+CIPSEND");
  delay(2000);
  Serial.println();
  ShowSerialData();
  String str="GET https://api.thingspeak.com/update?api_key="+API_key+"&field1=" + String(temperatur) +"&field2="+String(heartrate);
  Serial.println(str);  delay(2000);
  SIM800L.println(str); delay(4000);
  ShowSerialData();
 
  SIM800L.println((char)26); delay(4000); 
  SIM800L.println();
  ShowSerialData();
  SIM800L.println("AT+CIPSHUT");//close the connection
  delay(500); 
  ShowSerialData();
  str="";
  
  //total delay looping 50s
  delay(1000); //add 10s for 60s total delay looping 



  // sendHeartRateToThingSpeak(heartrate); // Send heart rate data to ThingSpeak
  // delay(15000); // Delay between readings, adjust as needed


}


void recordTemperature(){//read the temperature from the dht and display it to the oled
 DHT.read11(DHT11_PIN);
  // double temperatur = DHT.temperature;
  double hum = DHT.humidity;
  temperatur = DHT.temperature;

  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperatur, 1);
  display.print("°C");

 

  // heart rate sensor

  Signal = analogRead(PULSE_SENSOR_PIN); 
  // int heartRate = map(Signal, 0, 1024, 0, 100);  // process the analoge signal
  heartrate = map(Signal, 0, 1024, 0, 120); 
  
  delay(20);
  display.setCursor(0, 20);
  display.print("Heart Rate: ");
  display.print(heartrate, 1);
  // display.print("%");
  display.display();
  delay(1000);

  display.clearDisplay();

//toggle the led in case the temp is high
  // if (temperatur > 37){
  //   ledToggle();
  // }

// test the heart rate sensor if it toggles
  // if(Signal > Threshold){
  //   ledToggle();
  // }

  // condition for both the heart rate sensor and the temp
  if ((temperatur > 30) ){
    ledToggle();
  }

}

//function to toggle the led
void ledToggle(){
 int i = 0;
 while(i<=20){
  
  digitalWrite(LED1, HIGH);
  delay(100);
  digitalWrite(LED1, LOW);
  
  digitalWrite(LED2, HIGH);
  delay(100);
  digitalWrite(LED2, LOW);
  i++;
}
}


void SetupModule(){  
  if (SIM800L.available())Serial.write(SIM800L.read());
  SIM800L.println("AT"); delay(1000);
  SIM800L.println("AT+CPIN?"); delay(1000);
  SIM800L.println("AT+CREG?"); delay(1000);
  SIM800L.println("AT+CGATT?"); delay(1000);
  SIM800L.println("AT+CIPSHUT");delay(1000);
  SIM800L.println("AT+CIPSTATUS"); delay(2000);
  SIM800L.println("AT+CIPMUX=0");  delay(2000);

 //setting the APN,
  SIM800L.println("AT+CSTT=\""+apn+"\"");delay(1000);
  ShowSerialData();
  SIM800L.println("AT+CIICR");    delay(2000);
  ShowSerialData();
  
  //get local IP adress
  SIM800L.println("AT+CIFSR");    delay(2000);
  ShowSerialData();
  
  SIM800L.println("AT+CIPSPRT=0");delay(2000);
  ShowSerialData();
}

void ShowSerialData(){
  while(SIM800L.available()!=0)
  Serial.write(SIM800L.read());
  delay(2000); 
}





// void sendHeartRateToThingSpeak(int heartRate) {
//   String apiKey = "your_thingspeak_api_key"; // Replace with your ThingSpeak API key
//   String url = "GET https://api.thingspeak.com/update?api_key="+API_key+"&field1=" + String(temperatur) +"&field2="+String(heartrate);


//   Serial.println("Sending data to ThingSpeak...");
//   Serial.print("Heart Rate: ");
//   Serial.println(heartRate);
  
//   // Connect to the GPRS network
//   connectToGPRS();
  
//   // Send HTTP GET request to ThingSpeak
//   SIM800L.println("AT+HTTPINIT");
//   delay(1000);
//   SIM800L.println("AT+HTTPPARA=\"CID\",1");
//   delay(1000);
//   SIM800L.println("AT+HTTPPARA=\"URL\",\"" + url + "\"");
//   delay(1000);
//   SIM800L.println("AT+HTTPACTION=0");
//   delay(5000); // Wait for response
//   SIM800L.println("AT+HTTPTERM"); // Terminate HTTP session
//   delay(1000);
// }

// void connectToGPRS() {
//   SIM800L.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
//   delay(1000);
//   SIM800L.println("AT+SAPBR=3,1,\"APN\",\"" + String(apn) + "\"");
//   delay(1000);
//   SIM800L.println("AT+SAPBR=1,1");
//   delay(3000);
//   SIM800L.println("AT+HTTPINIT");
//   delay(1000);
// }
