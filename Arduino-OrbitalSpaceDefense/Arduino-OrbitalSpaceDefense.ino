/*
 Get scaled and calibrated output of MPU6050
 */

#include <basicMPU6050.h> 

// Create instance
basicMPU6050<> imu;
float _X, _Y, _Z;

float mapF(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int inPin = 7;   // choose the input pin (for a pushbutton)
int val = 0;     // variable for reading the pin status

void setup() {
  // Set registers - Always required
  imu.setup();

  // Initial calibration of gyro
  imu.setBias();

  // Start console
  Serial.begin(250000);
  
  pinMode(inPin, INPUT);
}

void loop() { 
  // Update gyro calibration 
  imu.updateBias();
   
  //-- Scaled and calibrated output:
  _X = imu.ax();
  _Y = imu.ay();
  _Z = imu.az();
  
  _X = mapF(_X,-1,1,0,359);
  _Y = mapF(_Y,-1,1,0,359);
  _Z = mapF(_Z,-1,1,0,359);

  Serial.print( _X ); // X = Z
  Serial.print( "," );
  Serial.print( _Y ); // Y = Y
  Serial.print( "," );
  Serial.print( _Z );
  Serial.print( "-" );
  val = digitalRead(inPin);  // read input value  
  Serial.print(val);
  Serial.println(); 
  
  delay(20);
}
