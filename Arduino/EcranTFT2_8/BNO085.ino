void setReports(long report_interval) //
////////////////////////////////////////
{
  Serial.println("Setting desired reports");
  if (!bno08x.enableReport(SH2_ROTATION_VECTOR, report_interval)) 
  {
    Serial.println("Could not enable rotation vector");
  }
}

float getHeading() //
/////////////////////
{
  // This heading is relative to magnetic North. Add the local declination for True North.
  // Returns degrees East of North.
  if (yaw > -90 && yaw < 180) 
  { // Quadrants I,II,IV
    return (90 - yaw);
  } 
  else 
  {                      // Quadrant III
    return -(yaw + 270);
  }
}
