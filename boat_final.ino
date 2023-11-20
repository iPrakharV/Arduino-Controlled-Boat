#include <Servo.h>
#include <PS2X_lib.h>  //for v1.6
 Servo esc;
 Servo myservo;
int val;
int val1;
/******************************************************************
 * set pins connected to PS2 controller:
 *   - 1e column: original 
 *   - 2e colmun: Stef?
 * replace pin numbers by the ones you use
 ******************************************************************/
#define PS2_DAT        8//14    
#define PS2_CMD        9 //15
#define PS2_SEL        10 //16
#define PS2_CLK       11 //17

/******************************************************************
 * select modes of PS2 controller:
 *   - pressures = analog reading of push-butttons 
 *   - rumble    = motor rumbling
 * uncomment 1 of the lines for each mode selection
 ******************************************************************/
//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

PS2X ps2x; // create PS2 Controller Class
 int error = 0;
byte type = 0;
byte vibrate = 0;

 void setup(){
 Serial.begin(57600);
 
  delay(300);  //added delay to give wireless ps2 module some time to startup, before configuring it
   
  //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  
  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT);
  
  if(error == 0){
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
  if (pressures)
    Serial.println("true ");
  else
    Serial.println("false");
  Serial.print("rumble = ");
  if (rumble)
    Serial.println("true)");
  else
    Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }  
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  
//  Serial.print(ps2x.Analog(1), HEX);
  
  type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
  case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
   }
   esc.attach(4);
   myservo.attach(5);
}
void loop() {
  // put your main code here, to run repeatedly:
if(error == 1) //skip loop if no controller found
    return; 
    
  else { //DualShock Controller
    ps2x.read_gamepad(false, vibrate); 
  
  int thrust=(ps2x.Analog(PSS_RY));
  int throttle=map(thrust,127 , 0, 0,255 );
esc.write(throttle);
 
  

if(ps2x.Analog(PSS_LX)>129){
   val=(ps2x.Analog(PSS_LX));
  // val1=map(val,128,255,60,90);
   myservo.write(28);
   Serial.println(ps2x.Analog(PSS_LX));
 }
else if(ps2x.Analog(PSS_LX)<127){

  val=(ps2x.Analog(PSS_LX));
   //val1=map(val,0,128,90,120);
   myservo.write(152);
   Serial.println(ps2x.Analog(PSS_LX));
}
else 
{
  myservo.write(100);
  Serial.println(ps2x.Analog(PSS_LX));
}
    }

  delay(50);  
}
