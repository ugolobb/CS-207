
const long s = 10; //size of Array
long buf[s];
long f=0, b=0;
long aux = 0;
long aux1=0;



void enqueue(long num){
  long nf = (f+1)%s;
  if(nf != b){
    f = nf;
    buf[f] = num;
    aux += num;
    Serial.print("Average: ");
    Serial.println(aux/s);
    aux1 += 1; 
  } else {
    //Serial.println("Full");
    long val = dequeue();
    //Serial.print("Dequeue: ");
    //Serial.println(val);
    
    //Serial.print("Average: ");
    //Serial.println(aux/aux1);
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


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  if(random(2) > 0){
    enqueue(analogRead(A0));
  } else {
    long val = dequeue();
    Serial.print("Dequeue: ");
    Serial.println(val);
  }*/
  enqueue(analogRead(A0));
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
  Serial.println("");
  //Serial.println(analogRead(sensorPin));
  delay(500);
  //Serial.println(analogRead(A0));

  
}
