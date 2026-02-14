int L1 = LOW, l2 = LOW;
unsigned long T1 = 0, T2=0;

void setup(){
  pinMode(3, OUTPUT)
  pinMode(2, OUTPUT);
}

void loop(){
  //digitalWrite(2, HIGH);
  //delay(200);
  //digitalWrite(2, LOW);
  //delay(100);
  

  // ahora usando milis en lugar de delay
  if((milis()-T1)>=100)
  {
    T1=milis();
    if(L1==HIGH)
    {
      digitalWrite(2,LOW);
      L1 = LOW;
    } else{
      digitalWrite(2, HIGH);
      l1 = HIGH;
    }
  }

  // y repicamos lo mismo para el segundo LED...
}
