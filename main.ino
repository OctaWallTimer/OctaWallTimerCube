#include<Wire.h>

const int MPU_addr=0x68;
int16_t X,Y,Z;

void setup(){

  Serial.begin(9600);

  Wire.begin(15,14);
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}


void loop(){

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // rejestr ACCEL_XOUT_H
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,6,true); //odczytywanie 6 rejestrow
  X=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  Y=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  Z=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  int wall = -1;
  if(X>Z && Z<0 && Y<Z) wall = 1;
  else if(X>Z && Z>0 && Y<0) wall = 2;
  else if(Z > 0 && abs(X) < 2000 && abs(Y) < 2000) wall=3;
  else if(Z>0 && X<Y && Y<0) wall=4;
  else if(Z < 0 && abs(X) < 2000 && abs(Y) < 2000) wall=5;
  else if(Z<0 && X>Y && Y>0) wall=6;
  else if(X>0 && Z>X && Y>Z) wall=7;
  else if(Y>Z && Z>0 && X<0) wall=8;

  Serial.print("Sciana: ");
  Serial.println(wall);
  delay(1000);

}
