char val;
int LED = 12;
int lowKey = 2250;  
int highKey = 1050;
int lowWord = 600;
int highWord = 950;
void setup()
{
Serial.begin(9600);
pinMode(LED, OUTPUT);
}

void loop()
{
if (Serial.available())
{
val = Serial.read();
if (val == 'W' || val == 'w')
{
    for(int i = 1; i <= 4; i++){
        digitalWrite(LED, HIGH);
        delayMicroseconds( highKey);
        digitalWrite(LED, LOW);
        delayMicroseconds(lowKey);
    }
    for(int i = 1; i <=10; i++){
      digitalWrite(LED, HIGH);
      delayMicroseconds(highWord);
      digitalWrite(LED, LOW);
      delayMicroseconds(lowWord);
    }
}

if ( val == 'S'|| val == 's'){ 
  for(int i = 1; i <= 4; i++){
    digitalWrite(LED, HIGH);
    delayMicroseconds(highKey);
    digitalWrite(LED, LOW);
    delayMicroseconds(lowKey);
  }
  for(int i = 1; i <= 40; i++){
    digitalWrite(LED, HIGH);
    delayMicroseconds(highWord);
    digitalWrite(LED, LOW);
    delayMicroseconds(lowWord);
  }
}
if (val == 'A' || val == 'a'){
   for(int i = 1; i <= 4; i++){
    digitalWrite(LED, HIGH);
    delayMicroseconds(highKey);
    digitalWrite(LED, LOW);
    delayMicroseconds(lowKey);
  }
  for(int i = 1; i <=58; i++){
    digitalWrite(LED, HIGH);
    delayMicroseconds(highWord);
    digitalWrite(LED, LOW);
    delayMicroseconds(lowWord);
  }
}

if (val == 'd' || val == 'D'){
   for(int i = 1; i <= 4; i++){
    digitalWrite(LED, HIGH);
    delayMicroseconds(highKey);
    digitalWrite(LED, LOW);
    delayMicroseconds(lowKey);
  }
  for(int i = 1; i <=64; i++){
    digitalWrite(LED, HIGH);
    delayMicroseconds(highWord);
    digitalWrite(LED, LOW);
    delayMicroseconds(lowWord);
  }
}
}
}
