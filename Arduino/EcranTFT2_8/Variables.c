#include "Variables.h"

char  Buffer[255],
      Tampon[255];

int i,
    PourcentageBatterie,
    acc_status,
    Echelle;


uint16_t  X_Touch, 
          Y_Touch,
          Z_Touch;
float Angle,
      TensionBatterie,
      yaw,
      pitch,
      roll,
      accuracy,
      DeclinaisonMagnetique;

TIME Time;
POINT Point[3][3],
      CentreRotation;

euler_t ypr;
