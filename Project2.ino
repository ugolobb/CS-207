//#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

const long s = 10; //size of Array
long buf[s];      //Declare the array
long f=0, b=0;   // Front and back indexes for order
long aux = 0;    // Keep the averages in this variable
long aux1=0;     // Auxiliar variable used in the debugging

long avg[s];  // Declare array of averages, same size the input array
long avg1;    // Variable used to express the input
long acum = 0; 
const int PulseSensorPurplePin = 5;
int Threshold = 650; 
PulseSensorPlayground pulseSensor;

void enqueue(long num){ // First function used to control the array. We start to save the input data in the array with this function. Recieves a long datatype as parameter
  long nf = (f+1)%s;  // Makes nf the index in front of f, if f is in the final index of the buffer, goes to the first value
  if(nf != b){ //Checks that nf does not takes position of the back index
    f = nf;
    buf[f] = num;
    aux += num;
    //The previous lines changes the index to keep the same order. First data in, Last out
    
    //Serial.print("Constant Average: ");
    //Serial.println(aux/s); //aux/s is the constant average of the array.

    //The regular EDA data input fluctuates between 0 and 200 (give or take). 
    avg1 = map(aux/s,0,200,200,1000); //We amplify the data in order to make a more understandable plot of this data. 
    Serial.println(avg1); 
    Serial.println("\t");
    
    aux1 += 1; //For debugging purposes
  } else {
    //Serial.println("Full");
    long val = dequeue(); // If the nf index is the same as the back index, then dequeue the last value in the buffer.
    //Serial.print("Dequeue: ");
    //Serial.println(val);
    
    //Serial.print("Average: ");
    //Serial.println(aux/aux1);
  }
}

int dequeue(){ 
  if(b != f){              //Checks if the back index is not the same as the front index. 
    long retval = buf[b];  //Save the last value
    buf[b] = 0;             // Turns the value to 0
    b = (b+1)%s;            
    aux -= retval;          //Substract the value from the total average
    aux1 -= 1;
    return retval;        //Returns the value discarded
  }
  else {
    //Serial.println("EMPTY");
  }
  return -1;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // It must be in this value for the arduino to better handle the I/O of data. 
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(20);
  
  int Signal = analogRead(PulseSensorPurplePin); //Get the reading from the heart rate sensor and save in Signal
  Serial.print(Signal); 
  Serial.print("\t");
  enqueue(analogRead(A0));
  //The code below is left in order for better understanding how the buffer works. 
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
}
