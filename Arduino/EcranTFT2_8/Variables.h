#ifndef VARIABLES_H
#define VARIABLES_H

#include <Arduino.h>

extern char Buffer[],
            Tampon[];

// Touchscreen coordinates: (x, y) and pressure (z)
extern uint16_t X_Touch, 
                Y_Touch,
                Z_Touch;

extern int  i,
            PourcentageBatterie,
            acc_status,
            Echelle;
                            
extern float  Angle,
              TensionBatterie,
              yaw,
              pitch,
              roll,
              accuracy,
              DeclinaisonMagnetique;


typedef struct
{
  unsigned long WithoutAction,
                Scann,
                Fade,
                SurveillanceBatterie,
                reportIntervalUs;
} TIME;

extern TIME Time;

typedef struct
{
  int x,
      y;
} POINT;

extern POINT  Point[3][3],
              CentreRotation;


typedef struct
{
  float yaw;
  float pitch;
  float roll;
} euler_t;

extern euler_t ypr;

// Vars to hold most recent report values
//float yaw, pitch, roll, accuracy;
//int acc_status;

#endif
