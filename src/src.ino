const int water_sensorDam = 0;
const int water_sensorStream1 = 1;
const int water_sensorStream2 = 2;
const int waterSensor_source1 = 3;
const int waterSensor_source2 = 5;
const int waterSensor_source3 = 6;
const int pump1 = 7;
const int pump2 = 8;
int valDam = 0;
int valStream1 = 0;
int valStream2 = 0;
void sensorTrigger()
{
  digitalWrite(waterSensor_source1, HIGH);
  digitalWrite(waterSensor_source2, HIGH);
  digitalWrite(waterSensor_source3, HIGH);
}
void sensorSleep()
{
  digitalWrite(waterSensor_source1, LOW);
  digitalWrite(waterSensor_source2, LOW);
  digitalWrite(waterSensor_source3, LOW);
}
void pumpState(int pumppin)
{
  while(analogRead(water_sensorStream1) != analogRead(water_sensorStream2) && analogRead(water_sensorDam)>330)
  {
    digitalWrite(pumppin, LOW);
  }
  digitalWrite(pumppin, HIGH);
  if(analogRead(water_sensorDam) > 330)
  {
    int data = analogRead(water_sensorDam)-330;
    while(analogRead(water_sensorDam) > 330+data/2)
    {
      digitalWrite(pump1, LOW);
    }
    digitalWrite(pump1, HIGH);
    while(analogRead(water_sensorDam) >330)
    {
      digitalWrite(pump2, LOW);
    }
    digitalWrite(pump2, HIGH);
  }
}
void setup() {
  // put your setup code here, to run once:
  pinMode(pump1,OUTPUT);
  pinMode(pump2,OUTPUT);
  pinMode(waterSensor_source1,OUTPUT);
  pinMode(waterSensor_source2,OUTPUT);
  pinMode(waterSensor_source3,OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly;
  sensorTrigger();
  valDam = analogRead(water_sensorDam);
  valStream1 = analogRead(water_sensorStream1);
  valStream2 = analogRead(water_sensorStream2);
  Serial.print("The initial level of Dam : ");
  Serial.println(valDam);
  Serial.print("The initial level of water stream 1 : ");
  Serial.println(valStream1);
  Serial.print("The initial level of water stream 2 : ");
  Serial.println(valStream2);  
  if(valDam > 700)
  {
     if(valStream1 > valStream2)
     {
        pumpState(pump2);
     }
     else
     {
        pumpState(pump1);
     }
  }
  Serial.print("The final level of Dam : ");
  Serial.println(analogRead(water_sensorDam));
  Serial.print("The final level of water stream 1 : ");
  Serial.println(analogRead(water_sensorStream1));
  Serial.print("The final level of water stream 2 : ");
  Serial.println(analogRead(water_sensorStream2));
  sensorSleep();
  delay(100);
}
