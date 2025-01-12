/*
function rotate (M, O, angle) {
    var xM, yM, x, y;
    angle *= Math.PI / 180;
    xM = M.x - O.x;
    yM = M.y - O.y;
    x = xM * Math.cos (angle) + yM * Math.sin (angle) + O.x;
    y = - xM * Math.sin (angle) + yM * Math.cos (angle) + O.y;
    return ({x:Math.round (x), y:Math.round (y)});
}
*/

void AffichageCercle() //
/////////////////////////
{
  tft.drawCircle(120, 120,119,TFT_WHITE);
  //tft.drawCircle(120, 120,100,TFT_WHITE);
  tft.drawCircle(120, 120,80,TFT_WHITE);
  //tft.drawCircle(120, 120,60,TFT_WHITE);
  tft.drawCircle(120, 120,40,TFT_WHITE);
  //tft.drawCircle(120, 120,20,TFT_WHITE);
  tft.drawFastVLine(120, 0, 240, TFT_WHITE);
  tft.drawFastHLine(0, 120, 240, TFT_WHITE);
  // repere x y
  //tft.drawRect(0, 0, 100, 50, TFT_BLUE);
}

void AffichageNord(float A) //
//////////////////////////////
{
  POINT PR;
  PR=Rotation(Point[0][0],A);
  Point[1][0].x=PR.x;
  Point[1][0].y=PR.y;
 
  PR=Rotation(Point[0][1],A);
  Point[1][1].x=PR.x;
  Point[1][1].y=PR.y;

  PR=Rotation(Point[0][2],A);
  Point[1][2].x=PR.x;
  Point[1][2].y=PR.y;
 
/*
  Serial.print("X0 : ");Serial.println(Point[0][0].x);
  Serial.print("Y0 : ");Serial.println(Point[0][0].y);
  Serial.println();
  Serial.print("X1 : ");Serial.println(Point[0][1].x);
  Serial.print("Y1 : ");Serial.println(Point[0][1].y);
  Serial.println();
  Serial.print("X2 : ");Serial.println(Point[0][2].x);
  Serial.print("Y2 : ");Serial.println(Point[0][2].y);
  Serial.println();

  Serial.print("X10 : ");Serial.println(Point[1][0].x);
  Serial.print("Y10 : ");Serial.println(Point[1][0].y);
  Serial.println();
  Serial.print("X11 : ");Serial.println(Point[1][1].x);
  Serial.print("Y11 : ");Serial.println(Point[1][1].y);
  Serial.println();
  Serial.print("X12 : ");Serial.println(Point[1][2].x);
  Serial.print("Y12 : ");Serial.println(Point[1][2].y);
  Serial.println("-----------------------------------");
  Serial.println();
  Serial.println();
  */

  //tft.fillRect(0, 0, 240, 240, TFT_BLACK);
  tft.fillTriangle(Point[2][0].x,Point[2][0].y,Point[2][1].x,Point[2][1].y,Point[2][2].x,Point[2][2].y, TFT_BLACK);
  tft.drawLine(CentreRotation.x, CentreRotation.y,Point[2][0].x ,Point[2][0].y, TFT_BLACK),
  AffichageCercle();
  //tft.drawCircle(120, 120,119,TFT_WHITE);
  //tft.drawFastVLine(120, 0, 240, TFT_WHITE);
  //tft.drawFastHLine(0, 120, 240, TFT_WHITE);
  tft.drawLine(CentreRotation.x, CentreRotation.y,Point[1][0].x ,Point[1][0].y, TFT_RED),
  tft.fillTriangle(Point[1][0].x,Point[1][0].y,Point[1][1].x,Point[1][1].y,Point[1][2].x,Point[1][2].y, TFT_RED);
  Point[2][0]=Point[1][0];
  Point[2][1]=Point[1][1];
  Point[2][2]=Point[1][2];
}

POINT Rotation(POINT P,float Alpha) //
//////////////////////////////////////
{
  POINT Pt;
  
  Alpha*=(PI/180);
  //Pt1.x=P.x-CentreRotation.x;
  P.x-=CentreRotation.x;
  //Pt1.y=P.y-CentreRotation.y;
  P.y-=CentreRotation.y;
  
  Pt.x=P.x*cos(Alpha)+P.y*sin(Alpha)+CentreRotation.x;
  Pt.y=P.y*cos(Alpha)-P.x*sin(Alpha)+CentreRotation.y;
  return Pt;
}

void AffichageTensionbatterie() //
//////////////////////////////////
{
  TensionBatterie=Mcp3221.read();
  TensionBatterie*=3.3;
  TensionBatterie/=4095;
  TensionBatterie*=2;
  //Serial.print("Tension Batterie (v) : ");Serial.println(TensionBatterie);

  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  strcpy(Tampon,"V Batt : ");
  tft.drawString(Tampon, 245, 5 , 2);

  /*
  tft.setTextColor(TFT_RED,TFT_BLACK);
  if (TensionBatterie>3.5)
    tft.setTextColor(TFT_CYAN,TFT_BLACK);
  if (TensionBatterie>3.7)
    tft.setTextColor(TFT_GREEN,TFT_BLACK);
  */
  dtostrf(TensionBatterie, 5, 2, Buffer);
  strcpy(Tampon,Buffer);
  strcat(Tampon," v");

  if (TensionBatterie<=3.0)
    {
      tft.setTextColor(TFT_RED,TFT_BLACK);
      PourcentageBatterie=1;
    }
  
  if (TensionBatterie>=3.0 && TensionBatterie<3.4)
  {
    tft.setTextColor(TFT_RED,TFT_BLACK);
    PourcentageBatterie=10;
  }

  if (TensionBatterie>=3.4 && TensionBatterie<3.5)
  {
    tft.setTextColor(TFT_RED,TFT_BLACK);
    PourcentageBatterie=20;
  }

  if (TensionBatterie>=3.5 && TensionBatterie<3.6)
  {
    tft.setTextColor(TFT_YELLOW,TFT_BLACK);
    PourcentageBatterie=30;
  }

  if (TensionBatterie>=3.6 && TensionBatterie<3.7)
  {
    tft.setTextColor(TFT_YELLOW,TFT_BLACK);
    PourcentageBatterie=50;
  }
  
  if (TensionBatterie>=3.7 && TensionBatterie<3.8)
  {
    tft.setTextColor(TFT_GREEN,TFT_BLACK);
    PourcentageBatterie=60;
  }

  if (TensionBatterie>=3.8 && TensionBatterie<4.0)
  {
    tft.setTextColor(TFT_GREEN,TFT_BLACK);
    PourcentageBatterie=80;
  }

  if (TensionBatterie>=4.0 && TensionBatterie<4.1)
  {
    tft.setTextColor(TFT_GREEN,TFT_BLACK);
    PourcentageBatterie=90;
  }

  if (TensionBatterie>=4.1)
  {
    tft.setTextColor(TFT_GREEN,TFT_BLACK);
    PourcentageBatterie=100;
  }

  tft.drawString(Tampon, 290, 5 , 2);

  itoa(PourcentageBatterie,Tampon,10);
  strcat(Tampon," %");
  tft.fillRoundRect(260, 12, SCREEN_WIDTH-260,15,0, TFT_BLACK);
  tft.drawString(Tampon, 290, 20 , 2);
}

void AffichageEchelle() //
//////////////////////////
{
  itoa(Echelle,Tampon,10);
  //strcpy(Tampon,Echelle);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.drawString("Echelle :", 290, 60 , 2);
/*
  itoa(PourcentageBatterie,Tampon,10);
  strcat(Tampon," %");
  tft.fillRoundRect(260, 12, SCREEN_WIDTH-260,15,0, TFT_BLACK);
  tft.drawString(Tampon, 290, 20 , 2);
  */
}
