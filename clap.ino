int soundSensor=10;
int LED[]={2,3,4,5,6};
int sensorpin = A0;
int counter;

boolean LEDStatus=false;

void setup() {
 pinMode(soundSensor,INPUT);
  Serial.begin (9600);

for(int i=0;i<5;i++){
 pinMode(LED[i],OUTPUT);
}
}

void loop() {
  int delays = 50;
  int diff = 0;
  int soundvalue = analogRead(sensorpin);
  int SensorData=digitalRead(soundSensor); 
 // soundvalue = map(soundvalue, 0, 1023, 0, 255) ; 

 // Serial.println(soundvalue);
  
       // for(int i=0;i<5;i++){
      //  digitalWrite(LED[0],soundvalue);
      // delay(delays);
      // }

  if(SensorData==1){

    if(LEDStatus==false){
        LEDStatus=true;



      
     
        for(int j=0;j<5;j++){
        for(int i=4;i>j;i--){
        digitalWrite(LED[i],HIGH);
        delay(50);
        digitalWrite(LED[i],LOW);
        delay(20);
        }
        digitalWrite(LED[j],HIGH);
        delay(20);
        }
     
      
        

        

    }
   else{
        LEDStatus=false;
        
      for(int i=0;i<5;i++){
       digitalWrite(LED[i],LOW);
        delay(delays);
        }
    }
    }


 } 
