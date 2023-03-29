
#define speaker A5


#include <CapacitiveSensor.h>

//define each key on the piano
CapacitiveSensor key1 = CapacitiveSensor(2,4); //tone up, farthest left key
CapacitiveSensor key2 = CapacitiveSensor(2,5); //tone up, farthest left key
CapacitiveSensor key3 = CapacitiveSensor(2,6); //tone up, farthest left key
CapacitiveSensor key4 = CapacitiveSensor(2,7); //tone up, farthest left key
CapacitiveSensor key5 = CapacitiveSensor(2,8); //tone up, farthest left key
CapacitiveSensor key6 = CapacitiveSensor(2,9); //tone up, farthest left key
CapacitiveSensor key7 = CapacitiveSensor(2,10); //tone up, farthest left key





// Note frequencies, Taken from https://learn.digilentinc.com/Documents/392 to help with the correct note frequencies
//Store all note frequencies for each octave in a 2 dimensional array
 double octaves[7][7] = 
 {  
  //Octave1 Notes:      c1      d1      e1      f1      g1      a1      b1
  /* 1st octave */   {32.703, 36.708, 41.203, 43.654, 48.990, 55.000, 61.735},
 
  //Octave2 Notes:      c2      d2      e2      f2      g2       a2       b2
  /* 2nd octave */   {65.406, 73.416, 82.407, 87.307, 97.999, 110.000, 123.470},
   
  //Octave3 Notes:       c3       d3       e3       f3       g3       a3       b3 
  /* 3rd octave */   {130.810, 146.830, 164.810, 174.610, 196.000, 220.000, 246.940},
    
  //Octave4 Notes:       c4       d4       e4       f4       g4       a4       b4
  /* 4th octave */   {261.630, 293.660, 329.630, 349.230, 392.000, 440.000, 493.880},
   
  //Octave5 Notes:       c5       d5       e5       f5       g5       a5       b5
  /* 5th octave */   {523.250, 587.330, 659.250, 698.460, 783.990, 880.000, 987.770},
 
  //Octave6 Notes:        c6        d6        e6        f6        g6        a6        b6  
  /* 6th octave */   {1046.500, 1174.700, 1318.500, 1396.900, 1568.000, 1760.000, 1979.500},
 
  //Octave7 Notes:        c7        d7        e7        f7        g7        a7        b7  
  /* 7th octave */   {2093.000, 2349.300, 2637.000, 2793.800, 3136.000, 3520.000, 3951.100}    //c7 = higher note, c1 == lower notes
  
 };


int threshold = 75; //just to test, will probably change

CapacitiveSensor btn1 = CapacitiveSensor(A3,3); //tone up, farthest left key
CapacitiveSensor btn2 = CapacitiveSensor(A3,11); //tone down, farthest right key
int numKeys = 7;



void setup(){
//  key1.set_CS_AutocaL_Millis(0xFFFFFFFF);

 Serial.begin(9600);
 


}
void loop(){
  //define all the sensors and their values
  long key1Sensor = key1.capacitiveSensor(30); //note c
  long key2Sensor= key2.capacitiveSensor(30); //note d
  long key3Sensor= key3.capacitiveSensor(30); //note e
  long key4Sensor= key4.capacitiveSensor(30); //note f
  long key5Sensor= key5.capacitiveSensor(30); //note g
  long key6Sensor= key6.capacitiveSensor(30); //note a
  long key7Sensor = key7.capacitiveSensor(30); //note b

  long btn1Sensor = btn1.capacitiveSensor(30); //sharp
  long btn2Sensor = btn2.capacitiveSensor(30); //flat/low

  //Serial.println(key1Sensor);
  Serial.println(btn1Sensor);
  
if (btn1Sensor < 10 && btn2Sensor<10 &&key1Sensor <10&&key2Sensor <10&&key3Sensor <10&&key4Sensor <10&&key5Sensor <10&&key6Sensor <10&&key7Sensor <10) {//if no button is presed, no sound is produced
  
  
    noTone(speaker);
  }
  if(btn1Sensor > 10){ // plays the highest set of frequecies in defined above for the sharp octaves
    
    if(key1Sensor > 10 && btn1Sensor >10){
      tone(speaker,octaves[5][1]);
    }
    if(key2Sensor > 10){
      tone(speaker,octaves[5][2]);
    }
    if(key3Sensor > 10){
      tone(speaker,octaves[5][3]);
    }
    if(key4Sensor > 10){
      tone(speaker,octaves[5][4]);
    }
    if(key5Sensor > 10){
      tone(speaker,octaves[5][5]);
    }
    if(key6Sensor > 10){
      tone(speaker,octaves[5][6]);
    }
    if(key7Sensor > 10){
      tone(speaker,octaves[5][7]);
    }
  } else if(btn1Sensor < 10 && btn2Sensor> 10){ //if right "pedal is pressed"
    
    if(key1Sensor > 10){
      tone(speaker,octaves[3][1]);
    }
     if(key2Sensor > 10){
      tone(speaker,octaves[3][2]);
    }
     if(key3Sensor > 10){
      tone(speaker,octaves[3][3]);
    }
     if(key4Sensor > 10){
      tone(speaker,octaves[3][4]);
    }
     if(key5Sensor > 10){
      tone(speaker,octaves[3][5]);
    }
     if(key6Sensor > 10){
      tone(speaker,octaves[3][6]);
    } if(key7Sensor > 10){
      tone(speaker,octaves[3][7]);
    }
    
    // if none of the pedals are pressed
  } else if(btn1Sensor < 10 && btn2Sensor < 10){
    if(key1Sensor > 10){
      tone(speaker,octaves[4][1]);
    }
    if(key2Sensor > 10){
      tone(speaker,octaves[4][2]);
    }
    if(key3Sensor > 10){
      tone(speaker,octaves[4][3]);
    }
    if(key4Sensor > 10){
      tone(speaker,octaves[4][4]);
    }
    if(key5Sensor > 10){
      tone(speaker,octaves[4][5]);
    }
    if(key6Sensor > 10){
      tone(speaker,octaves[4][6]);
    }if(key7Sensor > 10){
      tone(speaker,octaves[4][7]);
    }
   
  } 

  


}
/*
Pre code to test a single key





  
  long total1 =  btn1.capacitiveSensor(30); //decalre btns to be able to change tones of keys
  long total1 =  btn2.capacitiveSensor(30); //gives us 21 keys with 9 total keys (7 of which are actual keys)


  
  
  long total1 =  key1.capacitiveSensor(30);
  
  
  long start = millis();
   Serial.print(millis() - start); 
     Serial.print("\t");                    // tab character for debug windown spacing

  Serial.print(total1);                  // print sensor output 1
  Serial.print("\t");   
  if (total1 > 0) tone(speaker,131)
  */
