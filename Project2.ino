const long s = 10; //size of Array
long buf[s];
long f=0, b=0;
long aux = 0;

void enqueue(long num){
  long nf = (f+1)%s;
  if(nf != b){
    f = nf;
    buf[f] = num;
    aux += num;
  } else {
    Serial.println("Full");
    dequeue();
  }
}

int dequeue(){
  if(b != f){
    long retval = buf[b];
    buf[b] = 0;
    b = (b+1)%s;
    aux -= retval;
    return retval;
  }
  else {
    Serial.println("EMPTY");
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
  }
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
  Serial.println(aux/s);
  delay(1000);*/
  Serial.println(analogRead(A0));

  
}
