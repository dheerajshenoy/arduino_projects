
int ir_inp = 9;
int sp = 4; 

void setup() {
pinMode(ir_inp, INPUT);
pinMode(sp, OUTPUT);
}

void loop() {

if(digitalRead(ir_inp) == LOW)
  digitalWrite(sp, HIGH);
  delay(500);
  digitalWrite(sp, LOW);
}
