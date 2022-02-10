
// Hi, this is not complete code. You still need to enter code to display the data!
// you need to use a minimum 16 bit ADC to read out the MUX, like ADS1115 

// ADS1115 Library
#include <Adafruit_ADS1015.h>
// 16Ch Multiplexer
#include <CD74HC4067.h>

// MUX
float CHvoltage[16];
float stringvoltage[16];
byte vc=0;
byte vi;
float lowestSV=0;
float highestSV=0;
float lowestSnbr=1;
float highestSnbr=1;
float delta;
byte vt;
CD74HC4067 my_mux(42, 43, 44, 46);  // s0 s1 s2 s3   create a new CD74HC4067 object with its four control pins
const int SnumReadings=5;          // how many values are part of MA
float S1readings[SnumReadings];
float S2readings[SnumReadings];
float S3readings[SnumReadings];
float S4readings[SnumReadings];
float S5readings[SnumReadings];
float S6readings[SnumReadings];
float S7readings[SnumReadings];
float S8readings[SnumReadings];
float S9readings[SnumReadings];
float S10readings[SnumReadings];
float S11readings[SnumReadings];
float S12readings[SnumReadings];
float S13readings[SnumReadings];
float S14readings[SnumReadings];
float S15readings[SnumReadings];
float S16readings[SnumReadings];
int SreadIndex=0;              
float totalSV[16];
byte Scounter=0;

unsigned long loopstartmillis;
unsigned long loopinterval=1000;         // start certain modes every ... milliseconds

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  my_mux.channel(vc);

  // ADS1115
   ads.setGain(GAIN_TWOTHIRDS);   // +/- 6.144V  1 bit =  0.1875mV (default)
   ADSGain=0.0001875;
  // ads.setGain(GAIN_ONE);       // +/- 4.096V  1 bit =  0.125mV
  // ADSGain=0.000125;
   ads.begin();
   
  loopstartmillis=millis();
}

void loop() {
  // put your main code here, to run repeatedly:

 if (millis()>=(loopstartmillis+loopinterval)){
  loopstartmillis=millis();

  getStringvoltage(); 

 
 }

}

void getStringvoltage(){

   int CHVread;
   float CHvolttemp;

   CHvoltage[vc]=0;
   CHvolttemp=0;

   for  (vt = 0; vt <=4; vt++) {
    CHVread=ads.readADC_SingleEnded(2);
    CHvolttemp=CHvolttemp+CHVread;
    delay(10);
   }

    CHvoltage[vc]=CHvolttemp/5.0;
    
    voltagecorrection();
    
    vc++;
    if (vc>15){
      vc=0;
      calculatestringV();
    }
    
    my_mux.channel(vc);
    
}


 void voltagecorrection(){

 if (vc==0){
   CHvoltage[vc]=CHvoltage[vc]*0.0001259;      // here is where you need to calibrate for every step
 }
 if (vc==1){
   CHvoltage[vc]=CHvoltage[vc]*0.0002509;
 }
 if (vc==2){
   CHvoltage[vc]=CHvoltage[vc]*0.0003772;
 }
 if (vc==3){
   CHvoltage[vc]=CHvoltage[vc]*0.0004979;
 }
 if (vc==4){
   CHvoltage[vc]=CHvoltage[vc]*0.0006152;
 }
  if (vc==5){
   CHvoltage[vc]=CHvoltage[vc]*0.0007663;
 }
 if (vc==6){
   CHvoltage[vc]=CHvoltage[vc]*0.0009077;
 }
  if (vc==7){
   CHvoltage[vc]=CHvoltage[vc]*0.0009811;
 }
 if (vc==8){
   CHvoltage[vc]=CHvoltage[vc]*0.0011558;
 }
 if (vc==9){
   CHvoltage[vc]=CHvoltage[vc]*0.0012700;
 }
 if (vc==10){
   CHvoltage[vc]=CHvoltage[vc]*0.0013756;
 }
 if (vc==11){
   CHvoltage[vc]=CHvoltage[vc]*0.0015126;
 }
  if (vc==12){
   CHvoltage[vc]=CHvoltage[vc]*0.0015133;
 }
 if (vc==13){
   CHvoltage[vc]=CHvoltage[vc]*0.0017635;
 }
  if (vc==14){
   CHvoltage[vc]=CHvoltage[vc]*0.0017689;
 }
 if (vc==15){
   CHvoltage[vc]=CHvoltage[vc]*0.0019981;
 }

  
 }


void  calculatestringV(){

  float tempstringvoltage[16];

  tempstringvoltage[0]=CHvoltage[0];
  tempstringvoltage[1]=CHvoltage[1]-CHvoltage[0];
  tempstringvoltage[2]=CHvoltage[2]-CHvoltage[1]; 
  tempstringvoltage[3]=CHvoltage[3]-CHvoltage[2];
  tempstringvoltage[4]=CHvoltage[4]-CHvoltage[3];
  tempstringvoltage[5]=CHvoltage[5]-CHvoltage[4]; 
  tempstringvoltage[6]=CHvoltage[6]-CHvoltage[5];
  tempstringvoltage[7]=CHvoltage[7]-CHvoltage[6];
  tempstringvoltage[8]=CHvoltage[8]-CHvoltage[7]; 
  tempstringvoltage[9]=CHvoltage[9]-CHvoltage[8];
  tempstringvoltage[10]=CHvoltage[10]-CHvoltage[9];
  tempstringvoltage[11]=CHvoltage[11]-CHvoltage[10]; 
  tempstringvoltage[12]=CHvoltage[12]-CHvoltage[11];
  tempstringvoltage[13]=CHvoltage[13]-CHvoltage[12];
  tempstringvoltage[14]=CHvoltage[14]-CHvoltage[13]; 
  tempstringvoltage[15]=CHvoltage[15]-CHvoltage[14];


  // Moving Average
   totalSV[0] = totalSV[0]-S1readings[SreadIndex];
   S1readings[SreadIndex]=tempstringvoltage[0];
   totalSV[0] = totalSV[0]+S1readings[SreadIndex];
   totalSV[1] = totalSV[1]-S2readings[SreadIndex];
   S2readings[SreadIndex]=tempstringvoltage[1];
   totalSV[1] = totalSV[1]+S2readings[SreadIndex];
   totalSV[2] = totalSV[2]-S3readings[SreadIndex];
   S3readings[SreadIndex]=tempstringvoltage[2];
   totalSV[2] = totalSV[2]+S3readings[SreadIndex];
   totalSV[3] = totalSV[3]-S4readings[SreadIndex];
   S4readings[SreadIndex]=tempstringvoltage[3];
   totalSV[3] = totalSV[3]+S4readings[SreadIndex];
   totalSV[4] = totalSV[4]-S5readings[SreadIndex];
   S5readings[SreadIndex]=tempstringvoltage[4];
   totalSV[4] = totalSV[4]+S5readings[SreadIndex];
   totalSV[5] = totalSV[5]-S6readings[SreadIndex];
   S6readings[SreadIndex]=tempstringvoltage[5];
   totalSV[5] = totalSV[5]+S6readings[SreadIndex];
   totalSV[6] = totalSV[6]-S7readings[SreadIndex];
   S7readings[SreadIndex]=tempstringvoltage[6];
   totalSV[6] = totalSV[6]+S7readings[SreadIndex];
   totalSV[7] = totalSV[7]-S8readings[SreadIndex];
   S8readings[SreadIndex]=tempstringvoltage[7];
   totalSV[7] = totalSV[7]+S8readings[SreadIndex];
   totalSV[8] = totalSV[8]-S9readings[SreadIndex];
   S9readings[SreadIndex]=tempstringvoltage[8];
   totalSV[8] = totalSV[8]+S9readings[SreadIndex];
   totalSV[9] = totalSV[9]-S10readings[SreadIndex];
   S10readings[SreadIndex]=tempstringvoltage[9];
   totalSV[9] = totalSV[9]+S10readings[SreadIndex];
   totalSV[10] = totalSV[10]-S11readings[SreadIndex];
   S11readings[SreadIndex]=tempstringvoltage[10];
   totalSV[10] = totalSV[10]+S11readings[SreadIndex];
   totalSV[11] = totalSV[11]-S12readings[SreadIndex];
   S12readings[SreadIndex]=tempstringvoltage[11];
   totalSV[11] = totalSV[11]+S12readings[SreadIndex];
   totalSV[12] = totalSV[12]-S13readings[SreadIndex];
   S13readings[SreadIndex]=tempstringvoltage[12];
   totalSV[12] = totalSV[12]+S13readings[SreadIndex];
   totalSV[13] = totalSV[13]-S14readings[SreadIndex];
   S14readings[SreadIndex]=tempstringvoltage[13];
   totalSV[13] = totalSV[13]+S14readings[SreadIndex];
   totalSV[14] = totalSV[14]-S15readings[SreadIndex];
   S15readings[SreadIndex]=tempstringvoltage[14];
   totalSV[14] = totalSV[14]+S15readings[SreadIndex];
   totalSV[15] = totalSV[15]-S16readings[SreadIndex];
   S16readings[SreadIndex]=tempstringvoltage[15];
   totalSV[15] = totalSV[15]+S16readings[SreadIndex];

   
   SreadIndex++;

   if (SreadIndex>=SnumReadings){
     SreadIndex = 0;
   }

    stringvoltage[0] = totalSV[0]/SnumReadings;
    stringvoltage[1] = totalSV[1]/SnumReadings;
    stringvoltage[2] = totalSV[2]/SnumReadings;
    stringvoltage[3] = totalSV[3]/SnumReadings;
    stringvoltage[4] = totalSV[4]/SnumReadings;
    stringvoltage[5] = totalSV[5]/SnumReadings;
    stringvoltage[6] = totalSV[6]/SnumReadings;
    stringvoltage[7] = totalSV[7]/SnumReadings;
    stringvoltage[8] = totalSV[8]/SnumReadings;
    stringvoltage[9] = totalSV[9]/SnumReadings;
    stringvoltage[10] = totalSV[10]/SnumReadings;
    stringvoltage[11] = totalSV[11]/SnumReadings;
    stringvoltage[12] = totalSV[12]/SnumReadings;
    stringvoltage[13] = totalSV[13]/SnumReadings;
    stringvoltage[14] = totalSV[14]/SnumReadings;
    stringvoltage[15] = totalSV[15]/SnumReadings;


  lowestSV=stringvoltage[0];
  highestSV=stringvoltage[0];

  for (vi = 0; vi <= 15; vi++) {
      if(stringvoltage[vi]<lowestSV){
        lowestSV=stringvoltage[vi];
        lowestSnbr=vi+1;      
      }
      if(stringvoltage[vi]>highestSV){
        highestSV=stringvoltage[vi];
        highestSnbr=vi+1;     
      }
   }

    delta=highestSV-lowestSV; 

}
