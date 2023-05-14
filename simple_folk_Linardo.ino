/* SIMPLE FOLKRACE CONTROL */
//Dairis Rihards Irbe
//©2023
#include <IRremote.hpp>

const int mot_A[2] = { 6, 5 };
const int mot_B[2] = { 10, 9 };
const int servo = 4;
const int IR_pin = A5;
const int LED = 13;
const int pingPin[2] = { 2, 7 };  // Trigger Pin of Ultrasonic Sensor
const int echoPin[2] = { 3, 8 };  // Echo Pin of Ultrasonic Sensor

/////GLOBAL_PARAM/////
unsigned long loop_timer;
bool state = true;
int i = 0;
int piesk = 1;
int atrums = 150;
float P_gain = 2.0;


void setup() {
  Serial.begin(57600);
  IrReceiver.begin(IR_pin, true);  // Uzsāk IR uztvērēja darbību
  pinMode(servo, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(pingPin[0], OUTPUT);
  pinMode(echoPin[0], INPUT);
  pinMode(pingPin[1], OUTPUT);
  pinMode(echoPin[1], INPUT);
  drive_mot_A(0);
  drive_mot_B(0);
  delay(5000);
}

/////FUNKCIJAS/////
void IR_read() {
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);  // Print "old" raw data
    /* USE NEW 3.x FUNCTIONS */
    //IrReceiver.printIRResultShort(&Serial);  // Print complete received data in one line
    //IrReceiver.printIRSendUsage(&Serial);    // Print the statement required to send this data
    IrReceiver.resume();  // Enable receiving of the next value
    switch (IrReceiver.decodedIRData.decodedRawData) {
      case 0xE619FF00:
        {
          Serial.println("lielaks atrums");
          atrums = atrums + 20;
          delay(100);
          break;
        }
      case 0xE916FF00:
        {
          Serial.println("mazaks atrums");
          atrums = atrums - 20;
          delay(100);
          break;
        }
      case 0xBD3D8000:
        {
          state = !state;
          if (state) {
            Serial.println("ON");
            digitalWrite(LED, HIGH);
            delay(1000);
            digitalWrite(LED, LOW);
            delay(1000);
            digitalWrite(LED, HIGH);
            delay(1000);
            digitalWrite(LED, LOW);
            delay(1000);
            digitalWrite(LED, HIGH);
            delay(1000);
            digitalWrite(LED, LOW);
          } else Serial.println("OFF");
          delay(1000);
          break;
        }
    }
  }
}

void drive_mot_A(int v) {
  if (v > 0) {
    if (v > 255) v = 255;
    analogWrite(mot_A[0], v);
    digitalWrite(mot_A[1], LOW);
  } else if (v < 0) {
    if (v < -255) v = -255;
    analogWrite(mot_A[1], -v);
    digitalWrite(mot_A[0], LOW);
  } else {
    digitalWrite(mot_A[0], LOW);
    digitalWrite(mot_A[1], LOW);
  }
}

void drive_mot_B(int v) {
  if (v > 0) {
    if (v > 255) v = 255;
    analogWrite(mot_B[0], v);
    digitalWrite(mot_B[1], LOW);
  } else if (v < 0) {
    if (v < -255) v = -255;
    analogWrite(mot_B[1], -v);
    digitalWrite(mot_B[0], LOW);
  } else {
    digitalWrite(mot_B[0], LOW);
    digitalWrite(mot_B[1], LOW);
  }
}

void servo_poz(int deg) {  //deg - grādi no 0 lidz 180 (vidus pozīcija 90 deg)
  if (deg > 180) deg = 180;
  if (deg < 0) deg = 0;
  deg = (deg * 5.556) + 820;
  //Serial.println(deg);
  digitalWrite(servo, HIGH);
  delayMicroseconds(deg);
  digitalWrite(servo, LOW);
}

void maintain_frquency(int period) {
  if (micros() - loop_timer > period + 50) digitalWrite(12, HIGH);  //Turn on the LED if the loop time exceeds 4050us.
  while (micros() - loop_timer < period) {
    digitalWrite(2, HIGH);
  }
  loop_timer = micros();  //Set the timer for the next loop.
  digitalWrite(2, LOW);
}

long ultrasonic_distance_cm(int trig, int echo) {
  long duration, cm;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH, 23000);
  cm = microsecondsToCentimeters(duration);
  return cm;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}


///////////////////

void loop() {
  if (!state) {  //standby
    IR_read();
  } else {  //drive
    int delta = ultrasonic_distance_cm(pingPin[0], echoPin[0]) - ultrasonic_distance_cm(pingPin[1], echoPin[1]);
    delta = delta * P_gain;
    if (ultrasonic_distance_cm(pingPin[0], echoPin[0]) == 0 || ultrasonic_distance_cm(pingPin[1], echoPin[1]) == 0) {
      delta = 0;
    }
    //Serial.print(ultrasonic_distance_cm(pingPin[0], echoPin[0]));
    //Serial.print("cm");
    //Serial.print("\t");
    //Serial.print(ultrasonic_distance_cm(pingPin[1], echoPin[1]));
    //Serial.print("cm");
    Serial.print(delta);
    Serial.println();
    drive_mot_A(atrums - delta);
    drive_mot_B(atrums + delta);
  }

  //servo_poz(90);
  //maintain_frquency(4000);  //saglabā konstantu 250 Hz ciklu
}
