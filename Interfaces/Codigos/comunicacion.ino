void setup(){
  //comentario que no alcanzo a ver :p
  Serial.begin(250000);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  Serial.write(254);
  Serial.write(253);
  Serial.write(8);
  Serial.write(255);
  Serial.print("TEXTO");
}

void loop(){
  // Comentario que no alcanzo a ver
  int x;
  if(Serial.available())
  {
    x=Serial.read();
    if(x==1) digitalWrite(1);
    if(x==2) digitalWrite(2);
    if(x==3) digitalWrite(3);
    if(x==4) digitalWrite(4);
  }
}
