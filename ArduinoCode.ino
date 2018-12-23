
#define LeftMotorForward 3
#define LeftMotorBackward 4
#define RightMotorForward 5
#define RightMotorBackward 6
#define USTrigger 8
#define USEcho 9
#define MaxDistance 100
#include <Servo.h> 
#include <NewPing.h> 



NewPing sonar(USTrigger, USEcho, MaxDistance);


unsigned int duration;
unsigned int distance;
unsigned int FrontDistance;
unsigned int LeftDistance;
unsigned int RightDistance;
unsigned int Time;
Servo myservo;
void setup()                                            
{
  Serial.begin(9600);                             
  myservo.attach(12); 

  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
    
}
void loop() {
  for(int pos = 0; pos<160; pos+=32)     
  {                                  
    myservo.write(pos);              
        
     scan();
     FrontDistance = distance;                           
  if(FrontDistance > 50 || FrontDistance == 0)        
  {
   moveForward();                                     
  } 
  else                                                
  {
    
    moveStop();                                       
    navigate();
  }
  } 
for(int pos=160; pos>=0; pos-=32)
  {                                
    myservo.write(pos);              
                         
     scan();
     FrontDistance = distance;     
     delay(30);
  if(FrontDistance > 50 || FrontDistance == 0)        
  {
   moveForward();                                   
  } 
  else                                                
  {
    
    moveStop();                                       
    navigate();
  }
  } 
} 
void moveForward()                                 
{
  Serial.println("");
  Serial.println("Moving forward");
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(RightMotorForward, HIGH);
}

void moveBackward()                             
{
  Serial.println("");
  Serial.println("Moving backward");
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
}

void moveLeft()                                  
{
  Serial.println("");
  Serial.println("Moving left");
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(RightMotorForward, HIGH);
  
}

void moveRight()  
{                                
  Serial.println("");
  Serial.println("Moving right");
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
}

void moveStop()                                     
{
  Serial.println("");
  Serial.println("Stopping");
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
void scan()                                         
{
  Serial.println("");
  Serial.println("Scanning");
  Time = sonar.ping(); 
  distance = Time / US_ROUNDTRIP_CM;
  delay(300);
}
void navigate()                                   
{
    Serial.println("There's an obstacle!");  
    moveStop();                                      
    delay(30);
    scan();                                           
    delay(30);
    LeftDistance = distance;                         
    Serial.println("Left distance = ");
    Serial.print(distance);                                   
    moveStop();                                        
    delay(30);
    scan();                                          
    delay(30);
    RightDistance = distance;                         
    Serial.println("Right distance = ");
    Serial.print(distance);
    if(abs(RightDistance - LeftDistance) < 5)        
    {
      moveBackward();                                  
      delay(300);                                      
    }
    else if(RightDistance < LeftDistance)                 
    {
     moveLeft();                                      
     delay(300);                                      
    }
    else if(LeftDistance < RightDistance)             
    {
     moveRight();                                    
     delay(300);                                      
    }
}
