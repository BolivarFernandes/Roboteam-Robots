#include <HMC5883L.h>

#ifndef __COMPASS_H__
#define degree
#define xHeading
#endif // __COMPASS_H__


void compass(void)
{
  compass = HMC5883L();
  compass.SetScale(1.3);
  compass.SetMeasurementMode(Measurement_Continuous);
  MagnetometerRaw raw = compass.ReadRawAxis();
  MagnetometerScaled scaled = compass.ReadScaledAxis();
  float xHeading = atan2(scaled.YAxis, scaled.XAxis);
  if(xHeading < 0)    xHeading += 2*PI;
  if(xHeading > 2*PI)    xHeading -= 2*PI;
  float degree = xHeading * 180/M_PI;
  return degree;
}
