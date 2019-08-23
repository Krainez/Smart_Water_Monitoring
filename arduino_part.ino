// defines pins numbers


const int trigPin = 9;
const int echoPin = 10;
const int buzzer=3;
// defines variables
long duration;
int distance;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(buzzer,OUTPUT);
Serial.begin(115200); // Starts the serial communication
}
void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
if (distance > 12 )
{
  tone(buzzer,2000,50);
  
}
if (distance <=3){
  tone(buzzer,4000,50);
}

// Prints the distance on the Serial Monitor
delay(1);

Serial.println(distance);
}
