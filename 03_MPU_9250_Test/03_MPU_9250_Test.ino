#include <dummy.h>
#include <WiFi.h>    
#include <HTTPClient.h>
#include <UrlEncode.h>

#include <MPU9250_asukiaaa.h>
#include "Flex.h"

#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#define FLEX_3V3_PIN_SIG	33
#endif

const char* ssid = "MUHAMMAD";
const char* password = "12345678";
String MobileNumber = "923330204672";
String APIKey = "2852122";


// Pin Definitions
Flex flex_3v3(FLEX_3V3_PIN_SIG);

MPU9250_asukiaaa mySensor;
float aX[10], aY[10], aZ[10], aSqrt, gX[10], gY[10], gZ[10], mDirection, mX, mY, mZ;
float AX,AY,AZ,GX,GY,GZ;
void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("started");

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("Your Local IP address is: ");
  Serial.println(WiFi.localIP());
  delay(1000);
  sendMessage("Test Message");


#ifdef _ESP32_HAL_I2C_H_ // For ESP32
  Wire.begin(SDA_PIN, SCL_PIN);
  mySensor.setWire(&Wire);
#endif

  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag();

 
}

void loop() {
 
 int resultA,resultG;
 int flex_3v3Val = flex_3v3.read();

 resultA = mySensor.accelUpdate();
  if (resultA == 0) {

    for (int i=0;i<2;i++){
    aX[i] = mySensor.accelX();
    aY[i] = mySensor.accelY();
    aZ[i] = mySensor.accelZ();
    aSqrt = mySensor.accelSqrt();
    delay(10);
    }

      AX=calculateAverage(aX,2);
      AY=calculateAverage(aY,2);
      AZ=calculateAverage(aZ,2);
  } else {
    Serial.println("Cannod read value of accel " + String(resultA));
  }

  resultG = mySensor.gyroUpdate();
  if (resultG==0) {

    for (int i=0;i<2;i++){
    gX[i] = mySensor.gyroX();
    gY[i] = mySensor.gyroY();
    gZ[i] = mySensor.gyroZ();
    delay(20);
      }
      GX=calculateAverage(gX,2);
      GY=calculateAverage(gY,2);
      GZ=calculateAverage(gZ,2);
     
Serial.print(AX);
Serial.print(" ");
Serial.print(AY);
Serial.print(" ");
Serial.print(AZ);
Serial.print(" ");
Serial.print(GX);
Serial.print(" ");
Serial.print(GY);
Serial.print(" ");
Serial.print(GZ);
Serial.print(" ");
Serial.println(flex_3v3Val);


  } else {
    Serial.println("Cannod read value of gyro " + String(resultG));
  }
  delay(500);


}


// Functions
float calculateAverage(float arr[], int size) {
  float sum = 0;
  for (int i = 0; i < size; i++) {
    sum += arr[i];
  }
  float average = (float)sum / size;
  return average;
}


void sendMessage(String message){
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + MobileNumber + "&apikey=" + APIKey + "&text=" + urlEncode(message);    
  HTTPClient http;
  http.begin(url);

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200){
    Serial.print("Message sent successfully");
  }
  else{
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}
