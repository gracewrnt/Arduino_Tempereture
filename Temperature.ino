#include <Wire.h> 
 
int get_temp(){
  byte data = 0xff;
  byte dataH;
  byte dataL;
  int temp;
  Wire.beginTransmission(0x40);
  Wire.write(0x03);     // set pointer to register number 3, CONFIG
  Wire.write(0x11);     // write data to register, set start and temp
  Wire.endTransmission();    
  delay(1000);  
  
  Wire.beginTransmission(0x40);
  Wire.write(0x00);     // set pointer to register number 0, STATUS
  Wire.requestFrom(0x40, 3); // request 3 bytes from slave device #2

  while(Wire.available())  // slave may send less than requested
  {
    data = Wire.read();    // receive a byte as character
    dataH = Wire.read();   // receive a byte as character
    dataL = Wire.read();   // receive a byte as character
  }
  Wire.endTransmission(); 
  
  temp = dataH;
  temp<<=8;
  temp += dataL;
  temp /= 32*4;
  temp -= 50;
  
  return temp;
} 

void setup() 
{ 
  Wire.begin();        // join i2c bus (address optional for master) 
  delay(500);
  Serial.begin(9600);
} 
 
void loop() 
{ 
  int dataHighAddress = 0x01; // register number for temp sense, high
  int dataLowAddress = 0x02; // register number for temp sense, high
  byte data = 0xff;
  byte dataH;
  byte dataL;
  int temp;
  
  temp = get_temp();

  Serial.print( "Temperature = " );
  Serial.println( temp );
  //Serial.println( dataL );
  
  delay(1000);
}

