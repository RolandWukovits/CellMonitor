
// Hi, this is not complete code. You still need to enter code to display the data!
// you need to use a minimum 16 bit ADC to read out the MUX, like ADS1115 

// ADS1115 Library
#include <Adafruit_ADS1015.h>
// 16Ch Multiplexer
#include <CD74HC4067.h>

// MUX
float CHvoltage[16];
float stringvoltage[16];
int CHVread;
byte vc=0;
byte vi;
float lowestSV;
float highestSV;
byte lowestSnbr;
byte highestSnbr;
float deltalow;
float deltahigh;
float sendcell;
float CHvolttemp=0;
byte vt;

CD74HC4067 my_mux(42, 43, 44, 46);  // s0 s1 s2 s3   create a new CD74HC4067 object with its four control pins

unsigned long loopstartmillis;
unsigned long loopinterval=1000;         // start certain modes every ... milliseconds

void setup() {
  // put your setup code here, to run once:
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


   for  (vt = 0; vt <= 2; vt++) {
    CHVread=ads.readADC_SingleEnded(0);
    CHvolttemp=CHvolttemp+(CHVread*ADSGain);
   }

    CHvoltage=CHvolttemp/3;
   
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
   CHvoltage[vc]=CHvoltage[vc]*1.0;
 }
 if (vc==1){
   CHvoltage[vc]=CHvoltage[vc]*((10+10)/10)*1.0;
 }
 if (vc==2){
   CHvoltage[vc]=CHvoltage[vc]*((20+10)/10)*1.0;
 }
 if (vc==3){
   CHvoltage[vc]=CHvoltage[vc]*((30+10)/10)*1.0;
 }
 if (vc==4){
   CHvoltage[vc]=CHvoltage[vc]*((39+10)/10)*1.0;
 }
  if (vc==5){
   CHvoltage[vc]=CHvoltage[vc]*((51+10)/10)*1.0;
 }
 if (vc==6){
   CHvoltage[vc]=CHvoltage[vc]*((62+10)/10)*1.0;
 }
  if (vc==7){
   CHvoltage[vc]=CHvoltage[vc]*((68+10)/10)*1.0;
 }
 if (vc==8){
   CHvoltage[vc]=CHvoltage[vc]*((82+10)/10)*1.0;
 }
 if (vc==9){
   CHvoltage[vc]=CHvoltage[vc]*((91+10)/10)*1.0;
 }
 if (vc==10){
   CHvoltage[vc]=CHvoltage[vc]*((100+10)/10)*1.0;
 }
 if (vc==11){
   CHvoltage[vc]=CHvoltage[vc]*((110+10)/10)*1.0;
 }
  if (vc==12){
   CHvoltage[vc]=CHvoltage[vc]*((110+10)/10)*1.0;
 }
 if (vc==13){
   CHvoltage[vc]=CHvoltage[vc]*((130+10)/10)*1.0;
 }
  if (vc==14){
   CHvoltage[vc]=CHvoltage[vc]*((130+10)/10)*1.0;
 }
 if (vc==15){
   CHvoltage[vc]=CHvoltage[vc]*((130+10)/10)*1.0;
 }

  
 }


void  calculatestringV(){

  stringvoltage[0]=CHvoltage[0];
  stringvoltage[1]=CHvoltage[1]-CHvoltage[0];
  stringvoltage[2]=CHvoltage[2]-CHvoltage[1]; 
  stringvoltage[3]=CHvoltage[3]-CHvoltage[2];
  stringvoltage[4]=CHvoltage[4]-CHvoltage[3];
  stringvoltage[5]=CHvoltage[5]-CHvoltage[4]; 
  stringvoltage[6]=CHvoltage[6]-CHvoltage[5];
  stringvoltage[7]=CHvoltage[7]-CHvoltage[6];
  stringvoltage[8]=CHvoltage[8]-CHvoltage[7]; 
  stringvoltage[9]=CHvoltage[9]-CHvoltage[8];
  stringvoltage[10]=CHvoltage[10]-CHvoltage[9];
  stringvoltage[11]=CHvoltage[11]-CHvoltage[10]; 
  stringvoltage[12]=CHvoltage[12]-CHvoltage[11];
  stringvoltage[13]=CHvoltage[13]-CHvoltage[12];
  stringvoltage[14]=CHvoltage[14]-CHvoltage[13]; 
  stringvoltage[15]=CHvoltage[15]-CHvoltage[14];

  lowestSV=stringvoltage[0];
  highestSV=stringvoltage[0];

  for (vi = 0; vi <= 15; vi++) {
      if(stringvoltage[vi]<lowestSV){
        deltalow=lowestSV-stringvoltage[vi];
        lowestSV=stringvoltage[vi];
        lowestSnbr=vi+1;
      }
      if(stringvoltage[vi]>highestSV){
        deltahigh=stringvoltage[vi]-highestSV;
        highestSV=stringvoltage[vi];
        highestSnbr=vi+1;
      }
       
  }

}
