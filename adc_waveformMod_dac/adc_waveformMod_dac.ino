#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


// GUItool: begin automatically generated code
AudioSynthWaveform       waveform2;      //xy=461.20001220703125,178.1999969482422
AudioSynthWaveform       waveform1;      //xy=467.20001220703125,411.20001220703125
AudioOutputAnalogStereo  dacs1;          //xy=733.1999969482422,290.1999969482422
AudioConnection          patchCord1(waveform1, 0, dacs1, 0);
AudioConnection          patchCord2(waveform2, 0, dacs1, 1);
// GUItool: end automatically generated code

int curr_waveform = 0;
int counter = 0;
float vol_out = 0.0;

void setup() {
  // put your setup code here, to run once:
  // Pins used for ADCs are 37, 38, 39 (pins A18, A19, A20)
  // Pins used for DACs are A21 and A22
  Serial.begin(9600);
  AudioMemory(100);
  waveform1.frequency(440);
  waveform2.frequency(440);
  waveform1.amplitude(vol_out);
  waveform2.amplitude(vol_out);
  curr_waveform = WAVEFORM_TRIANGLE;
  waveform1.begin(curr_waveform);
  waveform2.begin(curr_waveform);
}



void loop() {
  // put your main code here, to run repeatedly:
  // TODO: calculate absolute difference between curr
  // reading and last reading, and only update if larger
  // than a set value
  float purple = (float)analogRead(39);
  // float gray = (float)analogRead(38);
  // float black = (float)analogRead(37);
  if(purple >= 1022.00 || purple <= 1.0){
    if(vol_out != 0.0){
      vol_out = 0.0;
      waveform1.amplitude(vol_out);
      waveform2.amplitude(vol_out);
      Serial.println("vol set to zero!");
    }
  }
  else{
    vol_out = 0.8;
    waveform1.amplitude(vol_out);
    waveform2.amplitude(vol_out);
    Serial.println("vol set to a different value!");
  }
  AudioNoInterrupts();
  if(counter > 10000){
    waveform1.frequency(purple);
    waveform2.frequency(purple);
    
    //waveform2.frequency(100.0 + gray);
  }
  counter += 1;
  //waveform1.amplitude(black);
  //waveform2.amplitude(black);
  //waveform1.begin(curr_waveform);
  //waveform2.begin(curr_waveform);
  AudioInterrupts();
  Serial.println(purple);
}
