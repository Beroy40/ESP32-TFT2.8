#ifndef DEFINES_H
#define DEFINES_H

//#include <Adafruit_MCP23X17.h>

#define MOSI  23
#define MISO  19
#define CLK 18

#define TOUCH_IRQ 35
#define TOUCH_CS  5
#define TFT_RST 4
#define TFT_DC  2
#define TFT_CS  15
#define SD_CS 13
#define TFT_BL  32
#define BL_ON  digitalWrite(TFT_BL,HIGH)
#define BL_OFF  digitalWrite(TFT_BL,LOW)
#define EN_VCC  12
#define VCC_ON  digitalWrite(EN_VCC,LOW)
#define VCC_OFF  digitalWrite(EN_VCC,HIGH)
#define I2C_SDA 21
#define I2C_SCL 22

#define FREQ_I2C  400000

#define TIME_SURVEILLANCE_BATTERIE  5000

#define DECLINAISON_MAGNETIQUE  3.5


#endif
