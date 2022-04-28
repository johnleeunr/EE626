#include <Wire.h> 

// I2C address of the GY-521 
const int MPU_addr=0x68; 
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int16_t TestX, TestY, TestZ, TestA;
int16_t XA_Test, YA_Test, ZA_Test, XG_Test, YG_Test, ZG_Test;
float temp;
void setup(){ 
  Wire.begin(); 

  Wire.beginTransmission(MPU_addr); 
  // PWR_MGMT_1 register 
  Wire.write(0x6B); 
  // set to zero (wakes up the GY-521) 
  Wire.write(0x00); 
  Wire.endTransmission(true); 
  Serial.begin(9600); 
} 
void loop(){ 
//////////////////////////////////////////
//int bytes_to_read = 1;
//int powerByte;
//
//Wire.beginTransmission(MPU_addr);
//Wire.write(0x6B);
//Wire.endTransmission(false);
//
//Wire.requestFrom(MPU_addr,bytes_to_read,true);
//powerByte = Wire.read();
//Wire.endTransmission(true);
//
//Serial.print("Power Register = "); Serial.println(powerByte); 

//////////////////////////////////////////
//  Wire.beginTransmission(MPU_addr); 
//  Wire.write(0x0D);
//  Wire.endTransmission(false);
//  
//  Wire.requestFrom(MPU_addr,4,true); 
//  TestX=Wire.read();
//  TestY=Wire.read();
//  TestZ=Wire.read();
//  TestA=Wire.read();
//  Serial.print("Register 0x0D = "); Serial.print(TestX, BIN); 
//  Serial.print(" Register 0x0E = "); Serial.print(TestY, BIN); 
//  Serial.print(" Register 0x0F = "); Serial.print(TestZ, BIN); 
//  Serial.print(" Register 0x10 = "); Serial.println(TestA, BIN);
//
//  XA_Test = ((TestX & 0b11100000) >> 3) | ((TestA & 0b00110000) >> 4);
//  YA_Test = ((TestY & 0b11100000) >> 3) | ((TestA & 0b00001100) >> 2);
//  ZA_Test = ((TestZ & 0b11100000) >> 3) | (TestA & 0b00000011);
//
//  XG_Test = (TestX & 0b00011111);
//  YG_Test = (TestY & 0b00011111);
//  ZG_Test = (TestZ & 0b00011111);
//  
//  Serial.print("X Accel Test = "); Serial.print(XA_Test); 
//  Serial.print(" Y Accel Test = "); Serial.print(YA_Test); 
//  Serial.print(" Z Accel Test = "); Serial.println(ZA_Test); 
//  Serial.print("X Gyro Test = "); Serial.print(XG_Test); 
//  Serial.print(" Y Gyro Test = "); Serial.print(YG_Test); 
//  Serial.print(" Z Gyro Test = "); Serial.println(ZG_Test); 

//////////////////////////////////////////////////

   Wire.beginTransmission(MPU_addr); 
  // starting with register 0x3B (ACCEL_XOUT_H) 
  Wire.write(0x6B); 
  Wire.write(0x40); 
  Wire.endTransmission(true); 

  Wire.beginTransmission(MPU_addr); 
  // starting with register 0x3B (ACCEL_XOUT_H) 
  Wire.write(0x3B); 
  Wire.endTransmission(false); 
  // request a total of 14 registers 
  Wire.requestFrom(MPU_addr,14,true); 
  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L) 
  AcX=Wire.read()<<8|Wire.read(); 
  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L) 
  AcY=Wire.read()<<8|Wire.read(); 
  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  AcZ=Wire.read()<<8|Wire.read(); 
  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L) 
  Tmp=Wire.read()<<8|Wire.read(); 
  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L) 
  GyX=Wire.read()<<8|Wire.read(); 
  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L) 
  GyY=Wire.read()<<8|Wire.read(); 
  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L) 
  GyZ=Wire.read()<<8|Wire.read(); 
  
  temp = (float) AcX / 16384;
  
  Serial.print("AcX = "); Serial.print(temp); 
  temp = (float) AcY / 16384;
  
  Serial.print(" | AcY = "); Serial.print(temp); 

  temp = (float) (AcZ - 800) / 16384 ;
  Serial.print(" | AcZ = "); Serial.print(temp);
  
  //equation for temperature in degrees C from datasheet 
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53); 

  temp = GyX / 131;
  Serial.print(" | GyX = "); Serial.print(temp);
  
  temp = GyY / 131;
  Serial.print(" | GyY = "); Serial.print(temp); 
  
  temp = GyZ / 131;
  Serial.print(" | GyZ = "); Serial.println(temp);
  Serial.println();
  delay(333); 
} 
