void Initialisation() //
////////////////////////
{
  pinMode(EN_VCC,OUTPUT);
  pinMode(TFT_BL,OUTPUT);
  //digitalWrite(TFT_BL,HIGH);
  Point[0][0].x=120;
  Point[0][0].y=0;

  Point[0][1].x=Point[0][0].x-5;
  Point[0][1].y=Point[0][0].y+20;

  Point[0][2].x=Point[0][0].x+5;
  Point[0][2].y=Point[0][0].y+20;

  CentreRotation.x=120;
  CentreRotation.y=120;

  Angle=0.0;
  Time.reportIntervalUs = 20000;

  DeclinaisonMagnetique=DECLINAISON_MAGNETIQUE;
  Echelle=200;
  //VCC_ON;

}
