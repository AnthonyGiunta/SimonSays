/* Simon Says game, with sound effects.
Anthony Giunta
10/22/2019 
*/

#include "Tone.h"
#include <LiquidCrystal.h>
Tone speaker;
byte speakerPin = 12;
LiquidCrystal lcd(2, 3, 7, 6, 5, 4);
int starttune[] = {NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_G4};
int mary[] = {NOTE_B2, NOTE_A2, NOTE_G2, NOTE_A2, NOTE_B2, NOTE_B2, NOTE_B2, NOTE_A2, NOTE_A2, NOTE_A2, NOTE_B2, NOTE_D2, NOTE_D2, NOTE_B2, NOTE_A2, NOTE_G2, NOTE_A2, NOTE_B2, NOTE_B2, NOTE_B2, NOTE_B2, NOTE_A2, NOTE_A2, NOTE_B2, NOTE_A2, NOTE_G2};
int ring[] = {NOTE_A2, NOTE_A2, NOTE_F2, NOTE_C2, NOTE_A2, NOTE_F2, NOTE_F2, NOTE_A2, NOTE_A2, NOTE_F2, NOTE_B2, NOTE_A2, NOTE_F2, NOTE_A2, NOTE_F2, NOTE_A2, NOTE_F2, NOTE_F2, NOTE_D2};
int london[] = {NOTE_C2, NOTE_D2, NOTE_C2, NOTE_B2, NOTE_A2, NOTE_B2, NOTE_C2, NOTE_G2, NOTE_A2, NOTE_B2, NOTE_A2, NOTE_B2, NOTE_C2, NOTE_C2, NOTE_D2, NOTE_C2, NOTE_B2, NOTE_A2, NOTE_B2, NOTE_C2, NOTE_G2, NOTE_C2, NOTE_A2, NOTE_F2};
int frere[] = {NOTE_G2, NOTE_A2, NOTE_B2, NOTE_G2, NOTE_G2, NOTE_A2, NOTE_B2, NOTE_G2, NOTE_B2, NOTE_C2, NOTE_D2, NOTE_B2, NOTE_C2, NOTE_D2, NOTE_D2, NOTE_E2, NOTE_D2, NOTE_C2, NOTE_B2, NOTE_G2, NOTE_D2, NOTE_E2, NOTE_D2, NOTE_C2, NOTE_B2, NOTE_G2, NOTE_G2, NOTE_D2, NOTE_G2, NOTE_G2, NOTE_D2, NOTE_G2};


int duration2[] = {100, 200, 100, 200, 100, 400, 100, 100, 100, 100, 200, 100, 500};

// Durations for playing each song
int marydur[] = {200, 200, 200, 200, 200, 200, 400, 200, 200, 400, 200, 200, 400, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 800};
int ringdur[] = {266, 134, 266, 134, 400, 266, 134, 266, 134, 266, 134, 400, 400, 400, 400, 400, 266, 134, 400, 400, 400};
int londondur[] = {200, 200, 200, 200, 200, 200, 400, 200, 200, 400, 200, 200, 400, 200, 200, 200, 200, 200, 200, 400, 400, 400, 200, 200, 400};
int freredur[] = {200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 400, 200, 200, 400, 100, 100, 100, 100, 200, 200, 100, 100, 100, 100, 200, 200, 200, 200, 400, 200, 200, 400};

// Notes for playing each song
int maryhadaNotes[] = {NOTE_B2, NOTE_A2, NOTE_G2, NOTE_D2, NOTE_B2, NOTE_A2, NOTE_G2, NOTE_D2};
int ringrosieNotes[] = {NOTE_A2, NOTE_F2, NOTE_C2, NOTE_B2, NOTE_D2, NOTE_F2, NOTE_C2, NOTE_B2};
int londonblondonNotes[] = {0};

// Button lists for LEDs during play and for checking user input
int marybtn[] = {1, 2, 3, 2, 1, 1, 1, 2, 2, 2, 1, 4, 4, 1, 2, 3, 2, 1, 1, 1, 1, 2, 2, 1, 2, 3};
int ringbtn[] = {1, 1, 2, 3, 1, 2, 2, 1, 1, 2, 4, 1, 2, 1, 2, 1, 2, 2, 1};
int londonbtn[] = {1, 2, 1, 3, 4, 3, 1, 3, 4, 3, 4, 3, 1, 1, 2, 1, 3, 4, 3, 1, 3, 1, 4, 2};
int frerebtn[] = {1, 2, 3, 1, 1, 2, 3, 1, 3, 4, 2, 3, 4, 2, 2, 4, 2, 4, 3, 1, 2, 4, 2, 1, 2, 1, 1, 2, 1};


int songSizes[] = {sizeof(marydur)/sizeof(marydur[0]), sizeof(ringdur)/sizeof(ringdur[0]), sizeof(londondur)/sizeof(londondur[0])};
// For making choices

int choice = 0;

int currnote = 0;
int currbtn = 0;
int totalplayed = 0;

int topScores[] = {0, 0 ,0, 0};
int score = 0;
int highscore = 0;

int stars = 0;

bool start = false;
bool alive = true;
bool maxscore = false;

int totalmeasures = 0;

int cheer[] = {NOTE_C4, NOTE_C4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5};
int btnNote[] = {NOTE_G3, NOTE_A3, NOTE_B3, NOTE_C4};
int duration[] = {100, 100, 100, 300, 100, 300};
int button[] = {14, 15, 16, 17, 18}; //The four button input pins
int ledpin[] = {8, 9, 10, 11};  // LED pins
int turn = 0;  // turn counter
int buttonstate = 0;  // button state checker
int randomArray[100]; //Intentionally long to store up to 100 inputs (doubtful anyone will get this far)
int inputArray[100];

// ===================================================
void setup()
{
  int note;
  int btnnum;
  
  Serial.begin(9600);
  lcd.begin(16,2);  
  speaker.begin(speakerPin);
  updateLCDMenu(0, 0, 0, stars);
        // LED pins are outputs
  for (int x = 0; x < 4; x++) 
  {
    pinMode(ledpin[x], OUTPUT);
    pinMode(button[x], INPUT);  // button pins are inputs
    digitalWrite(button[x], HIGH);  // enable internal pullup; buttons start in high position; logic reversed
  }
  pinMode(button[4], INPUT);
  digitalWrite(button[4], HIGH);
        // Plays theme song
  for (int thisNote = 0; thisNote < 13; thisNote ++) {
    // play the next note
    note = starttune[thisNote];
    speaker.play(note);
    if (note == NOTE_C4)      digitalWrite(ledpin[0], HIGH);
    else if (note == NOTE_F4) digitalWrite(ledpin[1], HIGH);
    else if (note == NOTE_G4) digitalWrite(ledpin[2], HIGH);
    else if (note == NOTE_E4) digitalWrite(ledpin[3], HIGH);

    // hold the note:
    delay(duration2[thisNote]);
    // stop for the next note:
    speaker.stop();
    allLEDs(LOW);
    delay(25);  
    

  }
  allLEDs(HIGH);

}

// ========================================================
void loop()  // This 'loop' is automatically ran repeatedly
{
// put in random number for cypher
//speaker.stop();
start = false;
alive = true;
maxscore = false;
score = 0;
highscore = topScores[choice];
lcd.clear();
allLEDs(HIGH);
updateLCDMenu(choice, score, highscore, stars);
         // Makes user press a button before starting allowing time to make a selection 
while (! start){
  for (int y = 0; y < 5; y++){
    buttonstate = digitalRead(button[y]);
    byte btn = y + 1; // logical button # (1-4)
        if (buttonstate == LOW){  //Checking for button push
     
          if (y == 4){ // When y == 4 the selection button was pressed
            allLEDs(LOW);
            speaker.play(NOTE_C2, 100);
            delay(100);  // insures minimum LED illumination
            wait_BtnRelease();  
            allLEDs(HIGH);
            if (choice == 3){ // Change these values when more songs are added
              choice = 0;
              highscore = topScores[choice];
              updateLCDMenu(choice, score, highscore, stars);
            }
            else{
              choice++;
              highscore = topScores[choice];
              updateLCDMenu(choice, score, highscore, stars);
            }
          }

          
          else {     
            highscore = topScores[choice];
            start = true;   // Ends while loop
            allLEDs(LOW);
            digitalWrite(ledpin[y], HIGH);
            speaker.play(NOTE_C4, 100);
            delay(100);  // insures minimum LED illumination
            speaker.stop();
            wait_BtnRelease();  
            digitalWrite(ledpin[y], LOW);
            delay(2000);  
          }

      }
  }
}
//    Plays through song
switch(choice+1){
  case 1: game(mary, marybtn, marydur);
  break;
  case 2: game(ring, ringbtn, ringdur);
  break;
  case 3: game(london, londonbtn, londondur);
  break;
  case 4: game(frere, frerebtn, freredur);
  break;
}
updateLCDEnd(choice, score, highscore);
}



// ===================================================
//            local functions

void input(int currMeasure, int btnChoice[], int noteChoice[]) { //Function for allowing user input and checking input against the generated array
  bool btnPushed;
  int inputbtn=0;
  int btnx = 0;
  for (int x = 0; x < (currMeasure+1)*4; x++) // from index 0 to current note 
  { // for each one in the current sequence wait for a button to be pushed 
    // if it is the correct one we keep looping through the sequence
    if (alive == true){
    
    btnPushed = false;
    btnx = btnChoice[x];
    while (! btnPushed) {
      for (int y = 0; y < 4; y++)
      {
        buttonstate = digitalRead(button[y]);
        byte btn = y + 1; // logical button # (1-4)
        inputbtn = y + 1;
        if (buttonstate == LOW)  //Checking for button push
        {
          btnPushed = true;
          if (inputbtn == btnx) { //Checks value input by user and checks it against
            digitalWrite(ledpin[y], HIGH);
            speaker.play(noteChoice[x]);
            delay(100);
            
            wait_BtnRelease();  
            speaker.stop();
            digitalWrite(ledpin[y], LOW);
            score+=200 + 50*choice;
            //the value in the same spot on the generated array
            updateLCD(choice, score, highscore, stars);
            if (x == songSizes[choice]-1){
              maxscore = true;
              alive = false;
            }
            //The fail function is called if it does not match
           
          }
          else {
            fail();
          }
          
        }
      }
      
    }  // end while

    }

  }
  delay(500);
}

// ------------------------------------------------------
void fail() { //Function used if the player fails to match the sequence
  delay(500);
  alive = false; //Resets turn value so the game starts over without need for a reset button
}

// ------------------------------------------------------
void allLEDs(byte state) {
  digitalWrite(ledpin[0], state);
  digitalWrite(ledpin[1], state);
  digitalWrite(ledpin[2], state);
  digitalWrite(ledpin[3], state);

}
// -----------------------------------------------------------------------------------------------------------------
void wait_BtnRelease() {
  bool btnStillDown;
  int debounce=0; // need depends on button used. mine caused some double trips
    while (debounce<2) {
      delay(5);
      btnStillDown = false;
      for (int y = 0; y < 5; y++)
      {
        buttonstate = digitalRead(button[y]);
        if (buttonstate == LOW)  //Checking for button push
          btnStillDown = true;
      }
      if (btnStillDown) debounce=0;
      else debounce++;
    }
}
//---------------------------------------------------------------------------------------------------------
int measures(int duration[]){ // CHECKED only with mary had a little lamb
  int total = 0;
  for (int j = 0; j < songSizes[choice]; j++){
    total += duration[j];
  }
  return total/800;
}
// -----------------------------------------------------------------------------------------------------------------
void updateLCD(int choice, int score, int highscore, int star){ // Formats LCD output CHECKED
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Song:");
  lcd.setCursor(5, 0);
  lcd.print(choice + 1);
  lcd.setCursor(0, 1);
  lcd.print("Score:");
  lcd.setCursor(6, 1);
  lcd.print(score);
  lcd.setCursor(7, 0);
  lcd.print("HS:");
  lcd.setCursor(10, 0);
  lcd.print(highscore);
  
  if (stars != 0){
    lcd.setCursor(13,1);
    lcd.print("*x");
    lcd.setCursor(15,1);
    lcd.print(stars);
  }
 
  
}
// -----------------------------------------------------------------------------------------------------------------
void updateLCDMenu(int choice, int score, int highscore, int star){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("JAMMIN' JUKEBOX!");
  lcd.setCursor(0,1);
  lcd.print("Song:");
  lcd.setCursor(5, 1);
  lcd.print(choice + 1);
  lcd.print(" HS:");
  lcd.setCursor(10, 1);
  lcd.print(highscore);
}
// -----------------------------------------------------------------------------------------------------------------
void duplicate(int choicearr[], int songarr[]){ //Sets choice = song
  for (int k=0; k<sizeof(songarr)/sizeof(songarr[0]); k++){
    choicearr[k] = songarr[k];
  }
}
// -----------------------------------------------------------------------------------------------------------------
void game(int noteChoice[], int btnChoice[], int durChoice[]){
  //while (alive == true){
    totalmeasures = measures(durChoice);
    //lcd.setCursor(0,0);
  // lcd.print(sizeof(durChoice)/sizeof(durChoice[0]));
    for (int currMeasure = 0; currMeasure <= totalmeasures; currMeasure++){
      allLEDs(LOW);
      
   // play  by measure   
   if (alive == true){
   for (int playNote = 0; playNote < ((currMeasure+1)*4); playNote++) {
       // play the next note:
    
    currnote = noteChoice[playNote];
    currbtn = btnChoice[playNote];
    if (currnote == 400){
      delay(150);
    }
    else {
     speaker.play(currnote);
     if (currbtn == 1)      digitalWrite(ledpin[0], HIGH);
     else if (currbtn == 2) digitalWrite(ledpin[1], HIGH);
     else if (currbtn == 3) digitalWrite(ledpin[2], HIGH);
     else if (currbtn == 4) digitalWrite(ledpin[3], HIGH);  
       // hold the note:
    delay(durChoice[playNote]);
       // stop for the next note:
    speaker.stop();
    allLEDs(LOW);
    delay(400);  
   }
  }
  
  //  Checks the measure
  input(currMeasure, btnChoice, noteChoice);
  delay(1000);
  }
 }
  //alive = false;
 //}
}
// -----------------------------------------------------------------------------------------------------------------
void updateLCDEnd(int choicex, int scorex, int highscorex){
  bool wait=false;

  if (maxscore == true){ 
    stars++;
    lcd.setCursor(0,0);
    lcd.print("SONG COMPLETED!!");
    for (int cheerNote = 0; cheerNote < 6; cheerNote ++) {
      // play the next note:
      speaker.play(cheer[cheerNote]);
      // hold the note:
      delay(duration[cheerNote]);
      // stop for the next note:
      speaker.stop();
      delay(25);
    }
   for(int i=0; i<6; i++){
    lcd.setCursor(0,1);
    lcd.print("!*!*!*!*!*!*!*!*");
    lcd.setCursor(6,1);
    lcd.print(scorex);
    delay(500);
    lcd.setCursor(0,1);
    lcd.print("*!*!*!*!*!*!*!*!");
    lcd.setCursor(6,1);
    lcd.print(scorex);
    topScores[choice] = score;
    delay(500);
   }
   
  }
  else{
    for (int i=0; i<5; i++){
     lcd.setCursor(0,0);
     lcd.print("GAME    GAME");
     lcd.setCursor(0,1);
     lcd.print("   OVER    OVER");
     allLEDs(HIGH);
     speaker.play(NOTE_G3, 300);
     delay(200);
     lcd.clear();
     allLEDs(LOW);
     speaker.play(NOTE_C3, 300);
     delay(200);
     
    }
    delay(1500);
    if (score > highscore){
    lcd.setCursor(0,0);
    lcd.print("NEW HIGH SCORE!!");
    lcd.setCursor(0,1);
    lcd.print("#1 ");
    lcd.setCursor(3,1);
    lcd.print(score);
    topScores[choice] = score;
    allLEDs(HIGH);
    for (int cheerNote = 0; cheerNote < 6; cheerNote ++) {
      // play the next note:
      speaker.play(cheer[cheerNote]);
      // hold the note:
      delay(duration[cheerNote]);
      // stop for the next note:
      speaker.stop();
      delay(25);
    }
    
    delay(3000);
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("Score:");
    lcd.setCursor(6,0);
    lcd.print(score);
    delay(3000);
  }
    
  }
  delay(1500);
     
    }
