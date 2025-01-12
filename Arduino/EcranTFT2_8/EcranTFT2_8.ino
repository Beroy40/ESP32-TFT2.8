
/*
 * CONGIGURATION IDE
 * 
 * Board : ESP32 Dev Module
 * CPU Frequency : 240MHZ
 * Flash Mode : DIO
 * Flash Size ; 4MB (32Mb)
 * Partition Scheme : Default 4MB with spiffs (1.2MB APP/1.5MB SPIFFS)
 * PSRAM : Disabled
 * Arduino runs on: Core1
 * Events run on: Core1
 * 
 */

 
#include "Defines.h"
#include "Variables.h"
#include <Wire.h>
#include "MCP3X21.h"

MCP3221 Mcp3221(0x48);

#include <SPI.h>
#include <FS.h>
#include <LittleFS.h>
#include <TFT_eSPI.h>

// Install the "XPT2046_Touchscreen" library by Paul Stoffregen to use the Touchscreen - https://github.com/PaulStoffregen/XPT2046_Touchscreen
// Note: this library doesn't require further configuration
#include <XPT2046_Touchscreen.h>

#include <Adafruit_BNO08x.h>
#define BNO08X_RESET -1

Adafruit_BNO08x bno08x(BNO08X_RESET);
sh2_SensorValue_t sensorValue;

TFT_eSPI tft = TFT_eSPI();
#define CALIBRATION_FILE "/TouchCalData1"
#define REPEAT_CAL false

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define FONT_SIZE 2

void quaternionToEuler(float qr, float qi, float qj, float qk, euler_t* ypr, bool degrees = false) //
/////////////////////////////////////////////////////////////////////////////////////////////////////
{
  float sqr = sq(qr);
  float sqi = sq(qi);
  float sqj = sq(qj);
  float sqk = sq(qk);

  ypr->yaw =  atan2( 2.0 * (qi * qj + qk * qr),  (sqi - sqj - sqk + sqr));
  ypr->pitch = asin(-2.0 * (qi * qk - qj * qr) / (sqi + sqj + sqk + sqr));
  ypr->roll = atan2( 2.0 * (qj * qk + qi * qr), (-sqi - sqj + sqk + sqr));

  if (degrees) 
  {
    ypr->yaw   *= RAD_TO_DEG;
    ypr->pitch *= RAD_TO_DEG;
    ypr->roll  *= RAD_TO_DEG;
  }
}
void quaternionToEulerRV(sh2_RotationVectorWAcc_t* rotational_vector, euler_t* ypr, bool degrees = false) //
////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
  quaternionToEuler(rotational_vector->real, rotational_vector->i, rotational_vector->j, rotational_vector->k, ypr, degrees);
}








// Print Touchscreen info about X, Y and Pressure (Z) on the Serial Monitor
void printTouchToSerial(int touchX, int touchY, int touchZ) 
{
  Serial.print("X = ");
  Serial.print(touchX);
  Serial.print(" | Y = ");
  Serial.print(touchY);
  Serial.print(" | Pressure = ");
  Serial.print(touchZ);
  Serial.println();
}

void setup() 
{
  Serial.begin(115200);
  delay(100);
  Serial.println();
  Serial.println("START");
  Wire.begin(I2C_SDA, I2C_SCL); //21,22);
  Wire.setClock(FREQ_I2C);
  Initialisation();
  VCC_ON;
  BL_ON;
  delay(1000);
  //Serial.println("VCC ON");
  Mcp3221.init(&Wire);

    // Try to initialize!
  if (!bno08x.begin_I2C()) 
  {
    Serial.println("Failed to find BNO08x chip");
    while (1) 
    {
      delay(10);
    }
  }
  Serial.println("BNO08x Found!");

  setReports(Time.reportIntervalUs);


  tft.init();
  tft.setRotation(3);
 
 
       // Initiaisation COM1
  touch_calibrate();
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(CC_DATUM);
  /*tft.setTextColor(TFT_BLACK, BackGroundColor,false);
  tft.drawString("Numero batiment",tft.width()/2,20,4);
  tft.setTextColor(TFT_BLACK, BackGroundColor,false);
  tft.drawNumber(NumeroBatiment,X_TextNumBat,Y_TextNumBat);
  */
  ledcSetup(0, 1000,8);
  ledcAttachPin(TFT_BL,0);
  ledcWrite(0, 255);
  AffichageCercle();
  AffichageNord(Angle);
  AffichageEchelle();
  Time.SurveillanceBatterie=millis()-TIME_SURVEILLANCE_BATTERIE;
}



void loop() 
{
  if ((millis()-Time.SurveillanceBatterie)>TIME_SURVEILLANCE_BATTERIE)
  {
    Time.SurveillanceBatterie=millis();
    AffichageTensionbatterie();
  }
  
  if (millis() - Time.Scann >= 100) 
  {
    if (bno08x.wasReset()) 
    {
      Serial.print("sensor was reset ");
      setReports(Time.reportIntervalUs);
    }

    if (bno08x.getSensorEvent(&sensorValue)) 
    {
      acc_status = sensorValue.status;
      quaternionToEulerRV(&sensorValue.un.rotationVector, &ypr, true); // degrees
      yaw = ypr.yaw;
      pitch = ypr.pitch;
      roll = ypr.roll;
      accuracy = sensorValue.un.rotationVector.accuracy;
    }

    float currentHeading = getHeading();
    Serial.print("Heading (deg): "); Serial.println(currentHeading);
    
    Time.Scann = millis();
    /*Angle+=1.0;
    if (Angle>=360)
      Angle=0;
      */
    currentHeading+=180;
    currentHeading-=DECLINAISON_MAGNETIQUE;
    AffichageNord(currentHeading);
    
    //Serial.print("Angle : ");Serial.println(Angle);
    /*bool pressed = tft.getTouch(&X_Touch, &Y_Touch,600);
    
    if (pressed==true)
    {
      Serial.println("Pressed");
      Serial.print("X : ");Serial.println(X_Touch);
      Serial.print("Y : ");Serial.println(Y_Touch);
      Time.WithoutAction=millis();
      /*Time.Fade=millis();
      
      ledcSetup(0, 1000,8);
      ledcAttachPin(TFT_BL,0);
      ledcWrite(0, 255);
      IndicePWM=255;
      //Flag.Fade=false;
      //Flag.RetroEclairage=true;
      delay(500);
      */
    //}
  }
}
