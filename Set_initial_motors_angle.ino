#include <Adafruit_PWMServoDriver.h>                             //Include the PWM Driver library

Adafruit_PWMServoDriver Spider = Adafruit_PWMServoDriver(0x40);    //Create an object of board 1


double NormalMotorPosition[16] = {90, 178, 100, 88,   // front right leg {-, ankle, knee, hip}
                                  90, 5,   88,  90,   // front left leg {-, ankle, knee, hip}
                                  90, 0,   88,  88,   // rear right leg {-, ankle, knee, hip}
                                  90, 178, 88,  92};  // rear left leg {-, ankle, knee, hip}

double CurrentMotorPosition[16] = {90, 178, 100, 88,   // front right leg {-, ankle, knee, hip}
                                   90, 5,   88,  90,   // front left leg {-, ankle, knee, hip}
                                   90, 0,   88,  88,   // rear right leg {-, ankle, knee, hip}
                                   90, 178, 88,  92};  // rear left leg {-, ankle, knee, hip}

double FinalMotorPosition[16] = {90, 178, 100, 88,   // front right leg {-, ankle, knee, hip}
                                 90, 5,   88,  90,   // front left leg {-, ankle, knee, hip}
                                 90, 0,   88,  88,   // rear right leg {-, ankle, knee, hip}
                                 90, 178, 88,  92};  // rear left leg {-, ankle, knee, hip}
double Position[12] = {16.5, 0, 0,
                       16.5, 0, 0,
                       16.5, 0, 0,
                       16.5, 0, 0};
double P[12] = {0, 0, 0,
                0, 0, 0,
                0, 0, 0,
                0, 0, 0};

double a1 = 3, a2 = 5.5, a3 = 8;
double v=8.5, w=9.5, d=6.374, beta=atan(v/w);
double xc=0, yc=0, zc=0;
double a=2, b=3;

void setup()
{
  Serial.begin(9600);
  Spider.begin();      
  Spider.setOscillatorFrequency(27000000);    //Set the PWM oscillator frequency, used for fine calibration
  Spider.setPWMFreq(50);          //Set the servo operating frequency 50Hz
  delay(1000);
  setMotors(FinalMotorPosition);
  delay(2000);
    
}

void loop()
{
 
  String str="";
  if(Serial.available()){
    str=Serial.readStringUntil('\n');

    String data1 = str.substring(0, str.indexOf('/'));
    int x = data1.toInt();
    str.remove(0, str.indexOf('/')+1);
    String data2 = str.substring(0, str.indexOf('/'));
    float y = data2.toFloat();
  
    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);
    
    FinalMotorPosition[x] = y;
    setMotors(FinalMotorPosition);
  }

 
}


void setMotors(double FinalMotorPosition[]){
  for(int t=0; t<=10; t++){
    
    for(int i=0; i<16; i++){
      int angle = CurrentMotorPosition[i] + t*(FinalMotorPosition[i] - CurrentMotorPosition[i])/100;
      int PWM_value = map(angle, 0, 180, 120, 460); // pulse lenght 120 for 0 degree and 460 for 180 degree
      Spider.setPWM(i, 0, PWM_value);
    }
    
  }
  for(int i=0; i<16; i++){
    CurrentMotorPosition[i] = FinalMotorPosition[i];
  }
}


