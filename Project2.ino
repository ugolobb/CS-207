//#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

const long s = 10; //size of Array
long buf[s];
long f=0, b=0;
long aux = 0;
long aux1=0;

long avg[s];
long avg1;
long acum = 0;
const int PulseSensorPurplePin = 5;
int Threshold = 650; 
PulseSensorPlayground pulseSensor;

void average_Averages(){
  for(int i = 0; i < s; i++){
    acum += avg[i];
    if(i == 9){
      i == 0;
      acum = acum / s;
      Serial.print("Average of 10 last averages");
      Serial.println(acum);
      acum = 0;
    } 
  }
}

void enqueue(long num){
  long nf = (f+1)%s;
  if(nf != b){
    f = nf;
    buf[f] = num;
    aux += num;
    
    //Serial.print("Constant Average: ");
    //Serial.println(aux/s);
    avg1 = map(aux/s,0,200,200,1000);
    Serial.println(avg1);
    Serial.println("\t");
    
    /*
     * for(int i = 0; i < s; i++){
      avg[i] = aux/s;
      if (i==9){
        i == 0;
        average_Averages();
      }
    }
    */
    aux1 += 1; 
  } else {
    //Serial.println("Full");
    long val = dequeue();
    //Serial.print("Dequeue: ");
    //Serial.println(val);
    
    Serial.print("Average: ");
    Serial.println(aux/aux1);
  }
}

// long avg(Array buf, )

int dequeue(){
  if(b != f){
    long retval = buf[b];
    buf[b] = 0;
    b = (b+1)%s;
    aux -= retval;
    aux1 -= 1;
    return retval;
  }
  else {
    //Serial.println("EMPTY");
  }
  return -1;
}
const int OUTPUT_TYPE = SERIAL_PLOTTER;
const int PULSE_FADE = 5;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  /*
  pulseSensor.analogInput(PulseSensorPurplePin);
  pulseSensor.blinkOnPulse(13);
  pulseSensor.fadeOnPulse(PULSE_FADE);
  
  pulseSensor.setSerial(Serial);
  pulseSensor.setOutputType(OUTPUT_TYPE);
  pulseSensor.setThreshold(Threshold);

   if (!pulseSensor.begin()) {
    /*
       PulseSensor initialization failed,
       likely because our particular Arduino platform interrupts
       aren't supported yet.

       If your Sketch hangs here, try PulseSensor_BPM_Alternative.ino,
       which doesn't use interrupts.
    
    for(;;) {
      // Flash the led to show things didn't work.
      digitalWrite(13, LOW);
      delay(50);
      digitalWrite(13, HIGH);
      delay(50);
    }
    
  }*/
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(20);
  /*
  int Signal = analogRead(PulseSensorPurplePin);
  Serial.print(Signal);
  Serial.print("\t");
  */
  /*
  if(random(2) > 0){
    enqueue(analogRead(A0));
  } else {
    long val = dequeue();
    Serial.print("Dequeue: ");
    Serial.println(val);
  }*/
  enqueue(analogRead(A0));
  /*
  for(int i = 0; i < s; i++){
    Serial.print(buf[i]);
    Serial.print("\t");
  }
  Serial.println("");
  for(int i=0; i < s; i++){
    if(i == f){
      Serial.print("f");
    }
    if (i == b){
      Serial.print("b");
    }
    Serial.print("\t");
  }
  Serial.println(""); */
  //Serial.println(analogRead(sensorPin));
  
  //delay(100);
  //Serial.println(analogRead(A0));

  
}
