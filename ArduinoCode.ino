
#define LeftMotorForward 3
#define LeftMotorBackward 4
#define RightMotorForward 5
#define RightMotorBackward 6
#define USTrigger 8
#define USEcho 9
#define MaxDistance 100
#include <Servo.h> 
#include <NewPing.h> 



NewPing sonar(USTrigger, USEcho, MaxDistance);//Δημιουργούμε 2 αντικείμενα,ενα για τον σερβοκινητήρα και ενα για τον αισθητήρα.

//Παρακάτω δημιουργώ unsigned ακέραιες μεταβλητές που θα χρησιμοποιήθουν αργότερα στον κωδικα.
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
  myservo.attach(12);  // attaches the servo on pin 9 to the servo object 
//Εδώ ορίζουμε τα pinModes.Αφού θα  θα στέλνουμε σήματα απο τα pins τα ορίζουμε ως outputs.
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
      // variable to store the servo position
}
void loop() {
  for(int pos = 0; pos<160; pos+=32)     //to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
          // waits 15ms for the servo to reach the position 
     scan();
     FrontDistance = distance;                           //Ορισε την μεταβλητή FrontDistance όσο ειναι η τιμή της μεταβλητής distance που επέστρεψε από την συνάρτηση scan
  delay(30);
  if(FrontDistance > 50 || FrontDistance == 0)        //Aν δεν υπάρχει τιποτα μπροστα από το ρομπότ σε απόστασ 60cm ή αν η τιμή της distance ειναι μηδέν που σημαίνει οτι δεν γύρισε παλμός τοτε 
  {
   moveForward();                                     //Πήγαινε στην moveForward συνάσρτηση
  } 
  else                                                //Αλλιώς αν  υπάρχει κατι μπροστα απο το ρομπότ σε απόσταση 60cm ή λιγότερα..
  {
    
    moveStop();                                       //Πήγαινε στην moveStop συνάρτηση και μετά στην navigate συνάρτηση
    navigate();
  }
  } 
for(int pos=160; pos>=0; pos-=32)
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
                         // waits 15ms for the servo to reach the position 
     scan();
     FrontDistance = distance;     //Ορισε την μεταβλητή FrontDistance όσο ειναι η τιμή της μεταβλητής distance που επέστρεψε από την συνάρτηση scan
     delay(30);
  if(FrontDistance > 50 || FrontDistance == 0)        //Aν δεν υπάρχει τιποτα μπροστα από το ρομπότ σε απόστασ 60cm ή αν η τιμή της distance ειναι μηδέν που σημαίνει οτι δεν γύρισε παλμός τοτε 
  {
   moveForward();                                     //Πήγαινε στην moveForward συνάσρτηση
  } 
  else                                                //Αλλιώς αν  υπάρχει κατι μπροστα απο το ρομπότ σε απόσταση 60cm ή λιγότερα..
  {
    
    moveStop();                                       //Πήγαινε στην moveStop συνάρτηση και μετά στην navigate συνάρτηση
    navigate();
  }
  } 
} 
void moveForward()                                    //Η συνάρτηση αυτή λεει στο ρομπότ να κουνήθει μπροστά
{
  Serial.println("");
  Serial.println("Moving forward");
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(RightMotorForward, HIGH);
}

void moveBackward()                                  //Η συνάρτηση αυτή λεει στο ρομπότ να κουνήθει πίσω
{
  Serial.println("");
  Serial.println("Moving backward");
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
}

void moveLeft()                                      //Η συνάρτηση αυτή λεει στο ρομπότ να κουνήθει αριστερά
{
  Serial.println("");
  Serial.println("Moving left");
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(RightMotorForward, HIGH);
  
}

void moveRight()                                    //Η συνάρτηση αυτή λεει στο ρομπότ να κουνήθει δεξιά
{
  Serial.println("");
  Serial.println("Moving right");
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
}

void moveStop()                                     //Η συνάρτηση αυτή λεει στο ρομπότ να σταματήσει
{
  Serial.println("");
  Serial.println("Stopping");
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
void scan()                                         //Η συνάρτηση αυτή καθορίζει την απόσταση που βρίσκονται τα ανικείμενα απο τον αισθητήρα υπερήχων
{
  Serial.println("");
  Serial.println("Scanning");
  Time = sonar.ping(); 
  distance = Time / US_ROUNDTRIP_CM;
  delay(300);
}
void navigate()                                     //Η συνάρτηση αυτή πλοηγεί το ρομπότ στον χώρο
{
    Serial.println("There's an obstacle!");  
    moveStop();                                       // Πήγαινε στην movestοp συνάρτηση
    delay(30);
    scan();                                           //Πήγαινε στην scan συνάρτηση
    delay(30);
    LeftDistance = distance;                          //Θέτει την μεταβλήτη LeftDistance όσο ειναι η τιμή της μεταβλητής distance
    Serial.println("Left distance = ");
    Serial.print(distance);                                   
    moveStop();                                        // Πήγαινε στην movestοp συνάρτηση
    delay(30);
    scan();                                           // Πήγαινε στην scan συνάρτηση
    delay(30);
    RightDistance = distance;                         //Θέτει την μεταβλήτη RightDistance όσο ειναι η τιμή της μεταβλητής distance
    Serial.println("Right distance = ");
    Serial.print(distance);
    if(abs(RightDistance - LeftDistance) < 5)        //Aν η απόλυτη τιμή της διαφορας Rightdistance-Leftdistance ειναι μικρότερη απο 5 τοτε
    {
      moveBackward();                                  //Πήγαινε στην movebackward συνάρτηση
      delay(300);                                      
    }
    else if(RightDistance < LeftDistance)                  //Aν η απόσταση από τα αριστέρα ειναι μεγαλύτερη απο την απόσταση απο τα δεξιά τότε
    {
     moveLeft();                                      //Πήγαινε στην moveleft συνάρτηση
     delay(300);                                      
    }
    else if(LeftDistance < RightDistance)             //Αλλιώς Aν η απόσταση από τα δεξιά ειναι μεγαλύτερη απο την απόσταση απο τα αριστερά τότε
    {
     moveRight();                                     //Πήγαινε στην moveright συνάρτηση
     delay(300);                                      
    }
}
