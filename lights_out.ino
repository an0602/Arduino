//Lights Out Game by Ayaz Noor


#include "LedControl.h"
#include "pitches.h"    //This header file is included as an example in Arduino toneMelody program
#include <Keypad.h>

LedControl lc=LedControl(12,10,11,1);


unsigned long delaytime=100;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
int one_flag = 0;
int two_flag = 0;
int three_flag = 0;
int four_flag = 0;
int five_flag = 0;
int six_flag = 0;
int seven_flag = 0;
int eight_flag = 0;
int nine_flag = 0;
int win_flag = 0;

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad


Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// notes in the melody:
int melody[] = {
  NOTE_CS5, NOTE_G2, NOTE_D2, NOTE_C4, NOTE_CS5, 0, NOTE_CS5, NOTE_D2, NOTE_B0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  2, 4, 4, 3, 1, 4, 4, 3, 1
};

void setup(){
   Serial.begin(9600);
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,0.5);
  /* and clear the display */
  lc.clearDisplay(0);   
  
  intro();
  initialize_board();
   
}
  
void loop(){
  char key = keypad.getKey();
  
  if (key == '1'){
    one_press(key);
  }
  else if (key == '2'){
    two_press(key);
  }
  else if (key == '3'){
    three_press(key);
  }  
  else if (key == '4'){
    four_press(key);
  }
  else if (key == '5'){
    five_press(key);
  }
  else if (key == '6'){
    six_press(key);
  }
  else if (key == '7'){
    seven_press(key);
  }
  else if (key == '8'){
    eight_press(key);
  }
  else if (key == '9'){
    nine_press(key);
  }
  else if(key == '0'){
    reset_board();
  }

  if(win_flag == 0){
    win();
  }
}

void intro(){
  int i;
  for(i = 0; i < 5; i++){
    lc.setLed(0,0,0,true);
    lc.setLed(0,0,1,true);
    lc.setLed(0,0,2,true);
    lc.setLed(0,0,3,true);
    lc.setLed(0,0,4,true);
    lc.setLed(0,0,5,true);
    lc.setLed(0,0,6,true);
    lc.setLed(0,0,7,true);
    lc.setLed(0,1,0,true);
    lc.setLed(0,2,0,true);
    lc.setLed(0,3,0,true);
    lc.setLed(0,4,0,true);
    lc.setLed(0,5,0,true);
    lc.setLed(0,6,0,true);
    lc.setLed(0,7,0,true);
    lc.setLed(0,7,1,true);
    lc.setLed(0,7,2,true);
    lc.setLed(0,7,3,true);
    lc.setLed(0,7,4,true);
    lc.setLed(0,7,5,true);
    lc.setLed(0,7,6,true);
    lc.setLed(0,7,7,true);  
    lc.setLed(0,1,7,true);
    lc.setLed(0,2,7,true); 
    lc.setLed(0,3,7,true);  
    lc.setLed(0,4,7,true);
    lc.setLed(0,5,7,true);
    lc.setLed(0,6,7,true);
    delay(delaytime * 2);
    
    lc.setLed(0,0,0,false);
    lc.setLed(0,0,0,false);
    lc.setLed(0,0,1,false);
    lc.setLed(0,0,2,false);
    lc.setLed(0,0,3,false);
    lc.setLed(0,0,4,false);
    lc.setLed(0,0,5,false);
    lc.setLed(0,0,6,false);
    lc.setLed(0,0,7,false);
    lc.setLed(0,1,0,false);
    lc.setLed(0,2,0,false);
    lc.setLed(0,3,0,false);
    lc.setLed(0,4,0,false);
    lc.setLed(0,5,0,false);
    lc.setLed(0,6,0,false);
    lc.setLed(0,7,0,false);
    lc.setLed(0,7,1,false);
    lc.setLed(0,7,2,false);
    lc.setLed(0,7,3,false);
    lc.setLed(0,7,4,false);
    lc.setLed(0,7,5,false);
    lc.setLed(0,7,6,false);
    lc.setLed(0,7,7,false); 
    lc.setLed(0,1,7,false);
    lc.setLed(0,2,7,false); 
    lc.setLed(0,3,7,false);  
    lc.setLed(0,4,7,false);
    lc.setLed(0,5,7,false);
    lc.setLed(0,6,7,false);
    delay(delaytime * 3);
  }
  lc.setLed(0,0,0,true);
  lc.setLed(0,0,1,true);
  lc.setLed(0,0,2,true);
  lc.setLed(0,0,3,true);
  lc.setLed(0,0,4,true);
  lc.setLed(0,0,5,true);
  lc.setLed(0,0,6,true);
  lc.setLed(0,0,7,true);
  lc.setLed(0,1,0,true);
  lc.setLed(0,2,0,true);
  lc.setLed(0,3,0,true);
  lc.setLed(0,4,0,true);
  lc.setLed(0,5,0,true);
  lc.setLed(0,6,0,true);
  lc.setLed(0,7,0,true);
  lc.setLed(0,7,1,true);
  lc.setLed(0,7,2,true);
  lc.setLed(0,7,3,true);
  lc.setLed(0,7,4,true);
  lc.setLed(0,7,5,true);
  lc.setLed(0,7,6,true);
  lc.setLed(0,7,7,true);  
  lc.setLed(0,1,7,true);
  lc.setLed(0,2,7,true); 
  lc.setLed(0,3,7,true);  
  lc.setLed(0,4,7,true);
  lc.setLed(0,5,7,true);
  lc.setLed(0,6,7,true);  
    
}

void reset_board(){
  clear_board();
  one_flag = 0;
  two_flag = 0;
  three_flag = 0;
  four_flag = 0;
  five_flag = 0;
  six_flag = 0;
  seven_flag = 0;
  eight_flag = 0;
  nine_flag = 0;
  win_flag = 0;

  lc.setLed(0,0,0,true);
  lc.setLed(0,0,1,true);
  lc.setLed(0,0,2,true);
  lc.setLed(0,0,3,true);
  lc.setLed(0,0,4,true);
  lc.setLed(0,0,5,true);
  lc.setLed(0,0,6,true);
  lc.setLed(0,0,7,true);
  lc.setLed(0,1,0,true);
  lc.setLed(0,2,0,true);
  lc.setLed(0,3,0,true);
  lc.setLed(0,4,0,true);
  lc.setLed(0,5,0,true);
  lc.setLed(0,6,0,true);
  lc.setLed(0,7,0,true);
  lc.setLed(0,7,1,true);
  lc.setLed(0,7,2,true);
  lc.setLed(0,7,3,true);
  lc.setLed(0,7,4,true);
  lc.setLed(0,7,5,true);
  lc.setLed(0,7,6,true);
  lc.setLed(0,7,7,true);  
  lc.setLed(0,1,7,true);
  lc.setLed(0,2,7,true); 
  lc.setLed(0,3,7,true);  
  lc.setLed(0,4,7,true);
  lc.setLed(0,5,7,true);
  lc.setLed(0,6,7,true);  
    
  initialize_board();
}

void initialize_board(){
  one_after('1');
  two_after('2');
  four_after('4');
  five_after('5');
  seven_after('7');
}

void clear_board(){
  lc.setLed(0,1,1,false);
  lc.setLed(0,2,1,false);
  lc.setLed(0,1,2,false);
  lc.setLed(0,2,2,false);
        lc.setLed(0,1,3,false);
      lc.setLed(0,2,3,false);
      lc.setLed(0,1,4,false);
      lc.setLed(0,2,4,false);
            lc.setLed(0,1,5,false);
      lc.setLed(0,2,5,false);
      lc.setLed(0,1,6,false);
      lc.setLed(0,2,6,false);
            lc.setLed(0,3,1,false);
      lc.setLed(0,4,1,false);
      lc.setLed(0,3,2,false);
      lc.setLed(0,4,2,false);
            lc.setLed(0,3,3,false);
      lc.setLed(0,4,3,false);
      lc.setLed(0,3,4,false);
      lc.setLed(0,4,4,false);
            lc.setLed(0,3,5,false);
      lc.setLed(0,4,5,false);
      lc.setLed(0,3,6,false);
      lc.setLed(0,4,6,false);
            lc.setLed(0,5,1,false);
      lc.setLed(0,6,1,false);
      lc.setLed(0,5,2,false);
      lc.setLed(0,6,2,false);
            lc.setLed(0,5,3,false);
      lc.setLed(0,6,3,false);
      lc.setLed(0,5,4,false);
      lc.setLed(0,6,4,false);
            lc.setLed(0,5,5,false);
      lc.setLed(0,6,5,false);
      lc.setLed(0,5,6,false);
      lc.setLed(0,6,6,false);
}
void one_press(char key){
  if(one_flag == 0){
      Serial.println(key);
      lc.setLed(0,1,1,true);
      lc.setLed(0,2,1,true);
      lc.setLed(0,1,2,true);
      lc.setLed(0,2,2,true);
      one_flag = 1;
  }
  else{
      Serial.println(key);
      lc.setLed(0,1,1,false);
      lc.setLed(0,2,1,false);
      lc.setLed(0,1,2,false);
      lc.setLed(0,2,2,false);
      one_flag = 0;
  }
  two_after('2');
  four_after('4');
}
void one_after(char key){
    if(one_flag == 0){
      Serial.println(key);
      lc.setLed(0,1,1,true);
      lc.setLed(0,2,1,true);
      lc.setLed(0,1,2,true);
      lc.setLed(0,2,2,true);
      one_flag = 1;
  }
  else{
      Serial.println(key);
      lc.setLed(0,1,1,false);
      lc.setLed(0,2,1,false);
      lc.setLed(0,1,2,false);
      lc.setLed(0,2,2,false);
      one_flag = 0;
  }
}

void two_press(char key){
  if(two_flag == 0){
      Serial.println(key);
      lc.setLed(0,1,3,true);
      lc.setLed(0,2,3,true);
      lc.setLed(0,1,4,true);
      lc.setLed(0,2,4,true);
      two_flag = 1;
  }
  else{
      Serial.println(key);
      lc.setLed(0,1,3,false);
      lc.setLed(0,2,3,false);
      lc.setLed(0,1,4,false);
      lc.setLed(0,2,4,false);
      two_flag = 0;
  }
  one_after('1');
  three_after('3');
  five_after('5');
}

void two_after(char key){
    if(two_flag == 0){
      Serial.println(key);
      lc.setLed(0,1,3,true);
      lc.setLed(0,2,3,true);
      lc.setLed(0,1,4,true);
      lc.setLed(0,2,4,true);
      two_flag = 1;
  }
  else{
      Serial.println(key);
      lc.setLed(0,1,3,false);
      lc.setLed(0,2,3,false);
      lc.setLed(0,1,4,false);
      lc.setLed(0,2,4,false);
      two_flag = 0;
  }
}

void three_press(char key){
  if(three_flag == 0){
      Serial.println(key);
      lc.setLed(0,1,5,true);
      lc.setLed(0,2,5,true);
      lc.setLed(0,1,6,true);
      lc.setLed(0,2,6,true);
      three_flag = 1;
  }
  else{
      Serial.println(key);
      lc.setLed(0,1,5,false);
      lc.setLed(0,2,5,false);
      lc.setLed(0,1,6,false);
      lc.setLed(0,2,6,false);
      three_flag = 0;
  }
  two_after('2');
  six_after('6');
}

void three_after(char key){
    if(three_flag == 0){
      Serial.println(key);
      lc.setLed(0,1,5,true);
      lc.setLed(0,2,5,true);
      lc.setLed(0,1,6,true);
      lc.setLed(0,2,6,true);
      three_flag = 1;
  }
  else{
      Serial.println(key);
      lc.setLed(0,1,5,false);
      lc.setLed(0,2,5,false);
      lc.setLed(0,1,6,false);
      lc.setLed(0,2,6,false);
      three_flag = 0;
  }
}

void four_press(char key){
  if(four_flag == 0){
      Serial.println(key);
      lc.setLed(0,3,1,true);
      lc.setLed(0,4,1,true);
      lc.setLed(0,3,2,true);
      lc.setLed(0,4,2,true);
      four_flag = 1;
  }
  else{
      Serial.println(key);
      lc.setLed(0,3,1,false);
      lc.setLed(0,4,1,false);
      lc.setLed(0,3,2,false);
      lc.setLed(0,4,2,false);
      four_flag = 0;
  }
  one_after('1');
  five_after('5');
  seven_after('7');
}

void four_after(char key){
    if(four_flag == 0){
      Serial.println(key);
      lc.setLed(0,3,1,true);
      lc.setLed(0,4,1,true);
      lc.setLed(0,3,2,true);
      lc.setLed(0,4,2,true);
      four_flag = 1;
  }
  else{
      Serial.println(key);
      lc.setLed(0,3,1,false);
      lc.setLed(0,4,1,false);
      lc.setLed(0,3,2,false);
      lc.setLed(0,4,2,false);
      four_flag = 0;
  }
}

void five_press(char key){
  if(five_flag == 0){
      Serial.println(key);
      lc.setLed(0,3,3,true);
      lc.setLed(0,4,3,true);
      lc.setLed(0,3,4,true);
      lc.setLed(0,4,4,true);
      five_flag = 1;
  }
  else{
      Serial.println(key);
      lc.setLed(0,3,3,false);
      lc.setLed(0,4,3,false);
      lc.setLed(0,3,4,false);
      lc.setLed(0,4,4,false);
      five_flag = 0;
  }
  two_after('2');
  four_after('4');
  six_after('6');
  eight_after('8');
}

void five_after(char key){
    if(five_flag == 0){
      Serial.println(key);
      lc.setLed(0,3,3,true);
      lc.setLed(0,4,3,true);
      lc.setLed(0,3,4,true);
      lc.setLed(0,4,4,true);
      five_flag = 1;
  }
  else{
      Serial.println(key);
      lc.setLed(0,3,3,false);
      lc.setLed(0,4,3,false);
      lc.setLed(0,3,4,false);
      lc.setLed(0,4,4,false);
      five_flag = 0;
  }
}

void six_press(char key){
  if(six_flag == 0){
      Serial.println(key);
      lc.setLed(0,3,5,true);
      lc.setLed(0,4,5,true);
      lc.setLed(0,3,6,true);
      lc.setLed(0,4,6,true);
      six_flag = 1;
  }
  else{
      Serial.println(key);
      lc.setLed(0,3,5,false);
      lc.setLed(0,4,5,false);
      lc.setLed(0,3,6,false);
      lc.setLed(0,4,6,false);
      six_flag = 0;
  }
  three_after('3');
  five_after('5');
  nine_after('9');
}

void six_after(char key){
    if(six_flag == 0){
      Serial.println(key);
      lc.setLed(0,3,5,true);
      lc.setLed(0,4,5,true);
      lc.setLed(0,3,6,true);
      lc.setLed(0,4,6,true);
      six_flag = 1;
  }
  else{
      Serial.println(key);
      lc.setLed(0,3,5,false);
      lc.setLed(0,4,5,false);
      lc.setLed(0,3,6,false);
      lc.setLed(0,4,6,false);
      six_flag = 0;
  }
}

void seven_press(char key){
  if(seven_flag == 0){
      Serial.println(key);
      lc.setLed(0,5,1,true);
      lc.setLed(0,6,1,true);
      lc.setLed(0,5,2,true);
      lc.setLed(0,6,2,true);
      seven_flag = 1;
  }
  else{
      Serial.println(key);
      lc.setLed(0,5,1,false);
      lc.setLed(0,6,1,false);
      lc.setLed(0,5,2,false);
      lc.setLed(0,6,2,false);
      seven_flag = 0;
  }
  four_after('4');
  eight_after('8');
}

void seven_after(char key){
    if(seven_flag == 0){
      Serial.println(key);
      lc.setLed(0,5,1,true);
      lc.setLed(0,6,1,true);
      lc.setLed(0,5,2,true);
      lc.setLed(0,6,2,true);
      seven_flag = 1;
  }
  else{
      Serial.println(key);
      lc.setLed(0,5,1,false);
      lc.setLed(0,6,1,false);
      lc.setLed(0,5,2,false);
      lc.setLed(0,6,2,false);
      seven_flag = 0;
  }
}

void eight_press(char key){
  if(eight_flag == 0){
      Serial.println(key);
      lc.setLed(0,5,3,true);
      lc.setLed(0,6,3,true);
      lc.setLed(0,5,4,true);
      lc.setLed(0,6,4,true);
      eight_flag = 1;
  }
  else{
      Serial.println(key);
      lc.setLed(0,5,3,false);
      lc.setLed(0,6,3,false);
      lc.setLed(0,5,4,false);
      lc.setLed(0,6,4,false);
      eight_flag = 0;
  }
  five_after('5');
  seven_after('7');
  nine_after('9');
}

void eight_after(char key){
    if(eight_flag == 0){
      Serial.println(key);
      lc.setLed(0,5,3,true);
      lc.setLed(0,6,3,true);
      lc.setLed(0,5,4,true);
      lc.setLed(0,6,4,true);
      eight_flag = 1;
  }
  else{
      Serial.println(key);
      lc.setLed(0,5,3,false);
      lc.setLed(0,6,3,false);
      lc.setLed(0,5,4,false);
      lc.setLed(0,6,4,false);
      eight_flag = 0;
  }
}

void nine_press(char key){
  if(nine_flag == 0){
      Serial.println(key);
      lc.setLed(0,5,5,true);
      lc.setLed(0,6,5,true);
      lc.setLed(0,5,6,true);
      lc.setLed(0,6,6,true);
      nine_flag = 1;
  }
  else{
      Serial.println(key);
      lc.setLed(0,5,5,false);
      lc.setLed(0,6,5,false);
      lc.setLed(0,5,6,false);
      lc.setLed(0,6,6,false);
      nine_flag = 0;
  }
  six_after('6');
  eight_after('8');
}

void nine_after(char key){
    if(nine_flag == 0){
      Serial.println(key);
      lc.setLed(0,5,5,true);
      lc.setLed(0,6,5,true);
      lc.setLed(0,5,6,true);
      lc.setLed(0,6,6,true);
      nine_flag = 1;
  }
  else{
      Serial.println(key);
      lc.setLed(0,5,5,false);
      lc.setLed(0,6,5,false);
      lc.setLed(0,5,6,false);
      lc.setLed(0,6,6,false);
      nine_flag = 0;
  }
}

void play_melody(){
    // iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < 9; thisNote++) {

      // to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(13, melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(13);
    }
}

void win(){
  if(one_flag == 0 && two_flag == 0 && three_flag == 0 && four_flag == 0 && five_flag == 0 && six_flag == 0 && seven_flag == 0 && eight_flag == 0 && nine_flag == 0){
    //intro();
    play_melody();
    win_flag = 1;

    lc.setLed(0,0,0,false);
    lc.setLed(0,0,0,false);
    lc.setLed(0,0,1,false);
    lc.setLed(0,0,2,false);
    lc.setLed(0,0,3,false);
    lc.setLed(0,0,4,false);
    lc.setLed(0,0,5,false);
    lc.setLed(0,0,6,false);
    lc.setLed(0,0,7,false);
    lc.setLed(0,1,0,false);
    lc.setLed(0,2,0,false);
    lc.setLed(0,3,0,false);
    lc.setLed(0,4,0,false);
    lc.setLed(0,5,0,false);
    lc.setLed(0,6,0,false);
    lc.setLed(0,7,0,false);
    lc.setLed(0,7,1,false);
    lc.setLed(0,7,2,false);
    lc.setLed(0,7,3,false);
    lc.setLed(0,7,4,false);
    lc.setLed(0,7,5,false);
    lc.setLed(0,7,6,false);
    lc.setLed(0,7,7,false); 
    lc.setLed(0,1,7,false);
    lc.setLed(0,2,7,false); 
    lc.setLed(0,3,7,false);  
    lc.setLed(0,4,7,false);
    lc.setLed(0,5,7,false);
    lc.setLed(0,6,7,false);    
  }
}
