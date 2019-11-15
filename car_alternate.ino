//including the libraries
#include <SoftwareSerial.h> // TX RX software library for bluetooth
#include <Servo.h>
const int servo1pin=5;
const int servo2pin=4;
Servo myservo1;
Servo myservo2;


//Initializing pins for bluetooth Module
int bluetoothTx = 2; // bluetooth tx to 2 pin
int bluetoothRx = 3; // bluetooth rx to 3 pinint Motor1_Pin2 = 8;  --

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

//Front Motor Pins  
int Enable1 = 6;
int Motor1_Pin1 = 7;  
int Motor1_Pin2=8;

//Back Motor Pins      
int Motor2_Pin1 = 9; 
int Motor2_Pin2 = 10;
int Enable2 = 11; 

//LEDs
int red_pin=13;
int blue_pin=12;

//turn speed and forward speed and delay for IR mode
int f_l_speed=150;
int f_r_speed=100;
int tf_speed=130;
int t_speed=60;
int t_delay=10;
int b_l_speed=100;
int b_r_speed=70;
int f_li_speed=90;
int f_ri_speed=60;

//IR sensors
int l_sensor=A2;
int r_sensor=A1;
int f_sensor=A3;
int m_sensor=A0;

//IR states
int l_s_state;
int r_s_state;
int f_s_state;
int m_s_state;

char command ; //variable to store the data
int velocity = 0; //Variable to control the speed of motor

void setup() 
{       
  //Set the baud rate of serial communication and bluetooth module at same rate.
  Serial.begin(9600);  
  bluetooth.begin(9600);

  //Setting the L298N, LED and RGB LED pins as output pins.
  pinMode(Motor1_Pin1, OUTPUT);  
  pinMode(Motor1_Pin2, OUTPUT);
  pinMode(Enable1, OUTPUT);
  pinMode(Motor2_Pin1, OUTPUT);  
  pinMode(Motor2_Pin2, OUTPUT);
  pinMode(Enable2, OUTPUT); 
  pinMode(l_sensor, INPUT);
  pinMode(r_sensor, INPUT);
  pinMode(f_sensor, INPUT);
  pinMode(red_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  pinMode(m_sensor, INPUT);
  myservo1.attach(servo1pin,600,2300);
  myservo2.attach(servo2pin,600,2300);
  
}

void loop(){
  if(bluetooth.available() > 0){  //Checking if there is some data available or not
    command = bluetooth.read();   //Storing the data in the 'command' variable
    Serial.println(command);     //Printing it on the serial monitor
    digitalWrite(blue_pin, LOW);
    digitalWrite(red_pin, HIGH);}
    //Change pin mode only if new command is different from previous.   
    switch(command){
    case 'B':  //Moving the Car Backward
      digitalWrite(Motor2_Pin2, HIGH);
      digitalWrite(Motor2_Pin1, LOW);
      digitalWrite(Motor1_Pin1, HIGH);
      digitalWrite(Motor1_Pin2, LOW);
      analogWrite(Enable1,b_l_speed);
      analogWrite(Enable2,b_r_speed);
      //delay(100);
      
      break;
    case 'F':  //Moving the Car Forward
      digitalWrite(Motor2_Pin1, HIGH);
      digitalWrite(Motor2_Pin2, LOW);
      digitalWrite(Motor1_Pin1, LOW);
      digitalWrite(Motor1_Pin2, HIGH);
      analogWrite(Enable1,f_l_speed);
      analogWrite(Enable2,f_r_speed);
      //delay(100);
      break;
    case 'L':  //Moving the Car Left
      digitalWrite(Motor1_Pin1, LOW);
      digitalWrite(Motor1_Pin2, HIGH);
      digitalWrite(Motor2_Pin1, LOW);
      digitalWrite(Motor2_Pin2, HIGH);
      analogWrite(Enable1,tf_speed);
      analogWrite(Enable2,t_speed);
      
      break;
    case 'R':   //Moving the Car Right
      digitalWrite(Motor1_Pin2, LOW);
      digitalWrite(Motor1_Pin1, HIGH);  
      digitalWrite(Motor2_Pin1, HIGH);
      digitalWrite(Motor2_Pin2, LOW);
      analogWrite(Enable1,t_speed);
      analogWrite(Enable2,tf_speed);
      break;
    case 'S':   //Stop
      digitalWrite(Motor2_Pin2, LOW);
      digitalWrite(Motor2_Pin1, LOW);
      digitalWrite(Motor1_Pin2, LOW);
      digitalWrite(Motor1_Pin1, LOW);
      break;
       
    case 'I':
    while(1)
    {
    digitalWrite(red_pin, LOW);
    digitalWrite(blue_pin, HIGH);
      l_s_state=analogRead(l_sensor);
      r_s_state=analogRead(r_sensor);
      f_s_state=analogRead(f_sensor);
      m_s_state=analogRead(m_sensor);
      digitalWrite(Motor2_Pin1, HIGH);
      digitalWrite(Motor2_Pin2, LOW);
      digitalWrite(Motor1_Pin1, LOW);
      digitalWrite(Motor1_Pin2, HIGH);
      analogWrite(Enable1,f_li_speed);
      analogWrite(Enable2,f_ri_speed);

      if(f_s_state<200)
      {
        Serial.println("stop");
      digitalWrite(Motor2_Pin2, LOW);
      digitalWrite(Motor2_Pin1, LOW);
      digitalWrite(Motor1_Pin2, LOW);
      digitalWrite(Motor1_Pin1, LOW);
      break;
      }

      else 
      {
    
           if(r_s_state < 500 && l_s_state > 500)
          {
  Serial.println("turning right");
  
      digitalWrite(Motor1_Pin2, LOW);
      digitalWrite(Motor1_Pin1, HIGH);  
      digitalWrite(Motor2_Pin1, HIGH);
      digitalWrite(Motor2_Pin2, LOW);
      analogWrite(Enable1,t_speed);
      analogWrite(Enable2,tf_speed);
      while(r_s_state < 500 && l_s_state > 500)
      {
      l_s_state=analogRead(l_sensor);
      r_s_state=analogRead(r_sensor);
      }
        }
        else if(r_s_state > 500 && l_s_state < 500)
       {
     Serial.println("turning left");
    digitalWrite(Motor1_Pin1, LOW);
      digitalWrite(Motor1_Pin2, HIGH);
      digitalWrite(Motor2_Pin1, LOW);
      digitalWrite(Motor2_Pin2, HIGH);
     analogWrite(Enable1,tf_speed);
     analogWrite(Enable2,t_speed);
      while(r_s_state > 500 && l_s_state < 500)
      {
      l_s_state=analogRead(l_sensor);
      r_s_state=analogRead(r_sensor);
      }

       }
       else if(m_s_state>500&&(l_s_state<500||r_s_state<500))
      {
         digitalWrite(Motor2_Pin2, HIGH);
      digitalWrite(Motor2_Pin1, LOW);
      digitalWrite(Motor1_Pin1, HIGH);
      digitalWrite(Motor1_Pin2, LOW);
      analogWrite(Enable1,b_l_speed);
      analogWrite(Enable2,b_r_speed);
      while(m_s_state>500&&(l_s_state<500||r_s_state<500))
      {
        m_s_state=analogRead(m_sensor);
        l_s_state=analogRead(l_sensor);
        r_s_state=analogRead(r_sensor);
      }
        
      }
  
 
  }
        }
      break;
    case 'D':
    myservo1.write(180);
    myservo2.write(180);
    break;

    case 'U':
    myservo1.write(50);
    myservo2.write(50);
    break;
    

    default:
    digitalWrite(Motor2_Pin2, LOW);
    digitalWrite(Motor2_Pin1, LOW);
    digitalWrite(Motor1_Pin2, LOW);
    digitalWrite(Motor1_Pin1, LOW);
     
 
      
      }
      delay(50);
      digitalWrite(Motor2_Pin2, LOW);
      digitalWrite(Motor2_Pin1, LOW);
      digitalWrite(Motor1_Pin2, LOW);
      digitalWrite(Motor1_Pin1, LOW);
      
      
    }
     
 
