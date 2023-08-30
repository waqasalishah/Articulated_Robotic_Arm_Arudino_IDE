#include <dummy.h>
#include <WiFi.h>    
#include <HTTPClient.h>
#include <UrlEncode.h>
#include <MPU9250_asukiaaa.h>
#include "Flex.h"

//Pins Definition
#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#define FLEX_3V3_PIN_SIG_1	33
#define FLEX_3V3_PIN_SIG_2	25
#endif

// Variables Definition
const char* ssid = "MUHAMMAD";
const char* password = "12345678";
String MobileNumber = "923330204672";
String APIKey = "2852122";
String Text_1[10];
int resultA,resultG;
int counter=0;
float SensorData[10];

// Pin assignment
Flex flex_3v3_1(FLEX_3V3_PIN_SIG_1);
Flex flex_3v3_2(FLEX_3V3_PIN_SIG_2);

MPU9250_asukiaaa mySensor;
float aX[10], aY[10], aZ[10], aSqrt, gX[10], gY[10], gZ[10], mDirection, mX, mY, mZ;
float AX,AY,AZ,GX,GY,GZ;

void setup() {

  // Start Serial Monitor
  Serial.begin(115200);
  while(!Serial);
  Serial.println("started");

// Connect to the Wifi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("Your Local IP address is: ");
  Serial.println(WiFi.localIP());
  delay(1000);
  sendMessage("Wifi Connected and sending a Test Message");


#ifdef _ESP32_HAL_I2C_H_ // For ESP32
  Wire.begin(SDA_PIN, SCL_PIN);
  mySensor.setWire(&Wire);
#endif
  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag();
}










void loop() {
// Read the IMU daya
 float s_Data=update_IMU();

// Read the Flex sensor Data
SensorData[6]=flex_3v3_1.read();
SensorData[7]=flex_3v3_2.read();


// Print the data
Serial.print(s_Data[0]);
Serial.print(" ");
Serial.print(s_Data[1]);
Serial.print(" ");
Serial.print(s_Data[2]);
Serial.print(" ");
Serial.print(s_Data[3]);
Serial.print(" ");
Serial.print(s_Data[4]);
Serial.print(" ");
Serial.print(s_Data[5]);
Serial.print(" ");
Serial.print(SensorData[6]);
Serial.print(" ");
Serial.println(SensorData[7]);


// Print the data
Serial.print(SensorData[0]);
Serial.print(" ");
Serial.print(SensorData[1]);
Serial.print(" ");
Serial.print(SensorData[2]);
Serial.print(" ");
Serial.print(SensorData[3]);
Serial.print(" ");
Serial.print(SensorData[4]);
Serial.print(" ");
Serial.print(SensorData[5]);
Serial.print(" ");
Serial.print(SensorData[6]);
Serial.print(" ");
Serial.println(SensorData[7]);

  delay(1000);


counter++;


//Serial.println(message);
if (counter==100){
  Text_1[0] = Text_conversion(SensorData);
  counter==0;
//sendMessage(Text_1[0]);

}


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
String Text_conversion(float Data[]){
  String Text_converted;
  Text_converted="The Accelerometer Reading is: AX= "+String(Data[0])+", AY= "+String(Data[1])+", AZ= "+String(Data[2])+"\n";
  Text_converted=Text_converted+"The Gyro Reading is : GX:"+String(Data[3])+", GY= "+String(Data[4])+", GZ= "+String(Data[5])+"\n";
  Text_converted=Text_converted+"The Flex_1 Sensor Reading is: Flex:"+String(Data[6])+"\n";
  Text_converted=Text_converted+"The Flex_2 Sensor Reading is: Flex:"+String(Data[7]);
  //  Serial.println(Text_converted);
  return Text_converted;
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

float update_IMU(){
// Define a local variable
float SensorData_local[10];

 resultA = mySensor.accelUpdate();
  if (resultA == 0) {
    //Get 5 values and then take average to remove the error
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
    Serial.println("Cannot read value of accel " + String(resultA));
  }

  resultG = mySensor.gyroUpdate();
  if (resultG==0) {
//Get 5 values and then take average to remove the error
    for (int i=0;i<2;i++){
    gX[i] = mySensor.gyroX();
    gY[i] = mySensor.gyroY();
    gZ[i] = mySensor.gyroZ();
    delay(20);
      }
      GX=calculateAverage(gX,2);
      GY=calculateAverage(gY,2);
      GZ=calculateAverage(gZ,2);
  } else {
    Serial.println("Cannod read value of gyro " + String(resultG));
  }
  // Store All data into one array
SensorData_local[0]=AX;
SensorData_local[1]=AY;
SensorData_local[2]=AZ;
SensorData_local[3]=GX;
SensorData_local[4]=GY;
SensorData_local[5]=GZ;

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
Serial.println(GZ);

return SensorData_local[10];
  }
