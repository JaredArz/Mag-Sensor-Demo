#include <QMC5883LCompass.h>

QMC5883LCompass compass;

const int N_led  = 5;
const int NE_led = 10;
const int E_led  = 11;
const int SE_led = 12;
const int S_led  = 13;
const int SW_led = 9;
const int W_led  = 8;
const int NW_led = 4;
//int error;

void setup() {
  Serial.begin(9600);
  compass.init();
  //compass.setCalibration(-2128, 2670, -1047, 32767, -16508, 4155);
  //compass.setCalibration(-953, 365, 0, 3846, 0, 1553);
  //compass.setCalibration(-1591, 1797, -4952, 0, -7841, 0);
  //compass.setCalibration(-1220, 895, -4595, 0, -7191, 0);
  // below is outdoor calibration outside pcl
  // compass.setCalibration(-1140, 1770, -1551, 1246, -2875, 228);
  // below is in EER auditorium
  //compass.setCalibration(-1312, 2520, -3143, 1435, -3742, 1098);
  //below is inside PCL 4th floor
  //compass.setCalibration(-2212, 565, -4282, 0, -7922, 0);
  //day of edison
  //compass.setCalibration(-1250, 672, -1390, 548, 0, 1677);
  //11:00am edison
  //compass.setCalibration(-1821, 426, -447, 1745, 0, 3373);
  //girl day
  //compass.setCalibration(-800, 1633, -3721, 0, 0, 2692);
  compass.setCalibration(-1281, 995, -2390, 132, -10530, 0);





  compass.setSmoothing(5,1);
  //compass.setMode(0x01, 0x08, 0x10, 0xC0);  //byte mode, byte odr, byte rng, byte osr
  pinMode(N_led,OUTPUT);
  pinMode(NE_led,OUTPUT);
  pinMode(E_led,OUTPUT);
  pinMode(SE_led,OUTPUT);
  pinMode(S_led,OUTPUT);
  pinMode(SW_led,OUTPUT);
  pinMode(W_led,OUTPUT);
  pinMode(NW_led,OUTPUT);
}

int getBearingJared(int azimuth){
  int bearing_code;

  if(azimuth >= 340 && azimuth <= 20){
      bearing_code =  0;
  }
  else if(azimuth > 20 && azimuth < 70){
      bearing_code = 1;
  }  
  else if(azimuth >= 70 && azimuth <= 110){
      bearing_code = 2;
  }
  else if (azimuth > 110 && azimuth < 160){
      bearing_code = 3;
  }
  else if(azimuth >= 160  && azimuth <= 200){
      bearing_code = 4;
  }
  else if(azimuth > 200 && azimuth < 250){
      bearing_code = 5;
  }
  else if(azimuth >= 250 && azimuth <= 290){
      bearing_code = 6;
  }
  else if(azimuth > 290 && azimuth < 340){
      bearing_code = 7;
  }
  else
    bearing_code = 0;

  return bearing_code;
}

void loop() {

  int x, y, z, a, b, g;
  //char myArray[3];
  char Bearing[2];
  
  compass.read();
  
  //x = compass.getX();
  //y = compass.getY();
  //z = compass.getZ();
  
  a = compass.getAzimuth();
  float declinationAngle = 0.05789;
  a += declinationAngle;
  //a = map(a, 210, 345, 0, 360);

  g = getBearingJared(a);
  
  //b = compass.getBearing(a);

  //compass.getDirection(myArray, a);
  
  //Serial.print(" Azimuth: ");
  //Serial.print(a);

  //Serial.print(" My Az: ");
  //Serial.print(g);

  //Serial.print(" Bearing: ");
  //Serial.print(b);
  
  digitalWrite(N_led,LOW);
  digitalWrite(NE_led,LOW);
  digitalWrite(E_led,LOW);
  digitalWrite(SE_led,LOW);
  digitalWrite(S_led,LOW);
  digitalWrite(SW_led,LOW);
  digitalWrite(W_led,LOW);
  digitalWrite(NW_led,LOW);
  
  

  switch(g){
    case 0: 
      Bearing[0] = 'N';
      Bearing[1] = ' ';
      digitalWrite(N_led,HIGH);
      break;
    case 1: 
      Bearing[0] = 'N';
      Bearing[1] = 'E';
      digitalWrite(NE_led,HIGH);
      break;
    case 2:
      Bearing[0] = 'E';
      Bearing[1] = ' ';
      digitalWrite(E_led,HIGH);
      break;
    case 3: 
      Bearing[0] = 'S';
      Bearing[1] = 'E';
      digitalWrite(SE_led,HIGH);
      break;
    case 4:
      Bearing[0] = 'S';
      Bearing[1] = ' ';
      digitalWrite(S_led,HIGH);
      break;
    case 5:
      Bearing[0] = 'S';
      Bearing[1] = 'W';
      digitalWrite(SW_led,HIGH);
      break;
    case 6:
      Bearing[0] = 'W';
      Bearing[1] = ' ';
      digitalWrite(W_led,HIGH);
      break;
    case 7:
      Bearing[0] = 'N';
      Bearing[1] = 'W';
      digitalWrite(NW_led,HIGH);
      break;
  }

  Serial.print("  My dir: ");
  Serial.print(Bearing[0]);
  Serial.print(Bearing[1]);

  Serial.println();

  delay(66);
}
