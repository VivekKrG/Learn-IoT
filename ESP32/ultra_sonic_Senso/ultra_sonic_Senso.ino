
// utlrasonic pinout
#define ULTRASONIC_TRIG_PIN     16   // pin TRIG 
#define ULTRASONIC_ECHO_PIN     17 // pin ECHO 
void setup(){
  
  // open serial
  Serial.begin(115200);
  pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);
  
}


void loop(){


  // measure distance 
  long duration, distance;
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
  duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1;
 
  Serial.print(distance);
  Serial.println(" cm");

    Serial.println("********** End ");
    Serial.println("*****************************************************");
  
  delay(500);    // delay
}
