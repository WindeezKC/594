//Code for 8x8 LED matrix game with help from Mirko Pavleski
//@ https://maker.pro/arduino/projects/space-invaders-game-on-8x8-homemade-led-matrix




byte tempMatrix[8][8] = {  
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0} 
};

/*** Level 1 ***/
#define level1_ani { \
  {1, 1, 1, 0, 0, 1, 1, 1}, \
  {1, 1, 0, 0, 0, 1, 1, 1}, \
  {1, 1, 0, 0, 0, 1, 1, 1}, \
  {1, 1, 1, 0, 0, 1, 1, 1}, \
  {1, 1, 1, 0, 0, 1, 1, 1}, \
  {1, 1, 1, 0, 0, 1, 1, 1}, \
  {1, 1, 0, 0, 0, 0, 1, 1}, \
  {1, 1, 0, 0, 0, 0, 1, 1}  \
}
#define level1 { \
  {1, 1, 1, 1, 1, 1, 1, 1}, \
  {1, 1, 1, 0, 0, 1, 1, 1}, \
  {0, 0, 0, 1, 1,0 , 0, 0}, \
  {0, 0, 0, 0, 0, 0, 0, 0}, \
  {0, 0, 0, 0, 0, 0, 0, 0}, \
  {0, 0, 0, 0, 0, 0, 0, 0}, \
  {0, 0, 0, 0, 0, 0, 0, 0}, \
  {0, 0, 0, 0, 0, 0, 0, 0}  \
}

/*** Level 2 ***/
#define level2_ani { \
  {1, 1, 1, 0, 0, 1, 1, 1}, \
  {1, 1, 0, 0, 0, 0, 1, 1}, \
  {1, 1, 0, 1, 1, 0, 0, 1}, \
  {1, 1, 1, 1, 1, 0, 0, 1}, \
  {1, 1, 1, 1, 0, 0, 1, 1}, \
  {1, 1, 1, 0, 0, 1, 1, 1}, \
  {1, 1, 0, 0, 0, 0, 0, 1}, \
  {1, 1, 0, 0, 0, 0, 0, 1}  \
}

#define level2 { \
  {0, 1, 1, 1, 1, 1, 1, 1}, \
  {1, 0, 1, 0, 1, 0, 1, 1}, \
  {0, 1, 0, 1, 0, 1, 0, 1}, \
  {0, 0, 1, 0, 1, 0, 1, 0}, \
  {0, 0, 0, 0, 0, 0, 0, 0}, \
  {0, 0, 0, 0, 0, 0, 0, 0}, \
  {0, 0, 0, 0, 0, 0, 0, 0}, \
  {0, 0, 0, 0, 0, 0, 0, 0}  \
}

/*** Level 3 ***/
#define level3_ani { \
  {1, 1, 1, 0, 0, 0, 1, 1}, \
  {1, 1, 0, 0, 0, 0, 0, 1}, \
  {1, 1, 0, 1, 1, 0, 0, 1}, \
  {1, 1, 1, 1, 0, 0, 1, 1}, \
  {1, 1, 1, 1, 0, 0, 0, 1}, \
  {1, 1, 0, 1, 1, 0, 0, 1}, \
  {1, 1, 0, 0, 0, 0, 0, 1}, \
  {1, 1, 1, 0, 0, 0, 1, 1}  \
}
#define level3 { \
  {1, 0, 1, 1, 1, 1, 0, 1}, \
  {0, 1, 1, 1, 1, 1, 1, 0}, \
  {1, 0, 1, 1, 1, 1, 0, 1}, \
  {1,0, 0, 1, 1, 1, 0, 1}, \
  {0, 0, 0, 0, 0, 0, 0, 0}, \
  {0, 0, 0, 0, 0, 0, 0, 0}, \
  {0, 0, 0, 0, 0, 0, 0, 0}, \
  {0, 0, 0, 0, 0, 0, 0, 0}  \
}

/*** WIN ***/
#define win { \
  {1, 1, 1, 0, 0, 1, 1, 1}, \
  {1, 1, 0, 0, 0, 0, 1, 1}, \
  {1, 0, 1, 0, 0, 1, 0, 1}, \
  {0, 0, 0, 0, 0, 0, 0, 0}, \
  {0, 0, 0, 0, 0, 0, 0, 0}, \
  {1, 0, 1, 0, 0, 1, 0, 1}, \
  {1, 0, 0, 1, 1, 0, 0, 1}, \
  {1, 1, 1, 0, 0, 1, 1, 1}  \
}
const int rows[8] = {   2, 3, 4, 5, 6, 7, 8, 9
 }; 
const int cols[8] = {   10, 11, 12, 13, A0, A1, A2, A3
 }; 

int potPin = A5;
int potVal;
int pixels[8][8];

int Delay =2;
boolean levelAni = true;
boolean levelStart = false; 
boolean levelComplete =false;
//^^^ taken from Mirko to flash LEDS and show what level number in the LEDS you are on
//Displays the numbers 1, 2, and 3, leaving blank LEDS to show the level

int index = 0;
const int lvls = 7; // number of arrays that will be needed to be displayed
byte levels[lvls][8][8]= { 
  level1_ani, level1, level2_ani, level2, level3_ani, level3, win
};

byte initial[lvls][8][8] {
   level1_ani, level1, level2_ani, level2, level3_ani, level3, win
};
//Timers for values of these things
unsigned long animationTime;
unsigned long completeTime;
unsigned long enemyTime;
unsigned long gameOverTime;
long previousMillis = 0;
long interval = 50;

//Player declarations
int bulletRow = 5;
int bulletCol;
byte bulletArray[6];

int bulletDelayCount = 0;
boolean fired = false;
//Enemy delcarations
boolean enemyWon = false;
boolean enemyWaiting = false;
boolean enemyFired = false;
boolean enemyBulletCollision = false;
int enemyAttackSpeed[7] = {0, 80, 0, 50, 0, 10, 0}; //set the  times for the attack speed 
int enemyBulletSpeed[7] = {0, 18, 0, 15, 0, 10, 0}; //set bullet speeds
//the 0's in these are there to turn off the attack speed and bullet speed for when it is playing the animations for 
//in between levels
int enemyBulletRow;
int enemyBulletDelayCount = 0;
int enemyBulletArray[8][2] = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} }; //where bullets can be fired

int enemyBottomCount = 0;
int randomBullet;

void setup(){
  Serial.begin(9600);
  for (int thisPin = 0; thisPin < 8; thisPin++) {
   
    pinMode(cols[thisPin], OUTPUT); 
    pinMode(rows[thisPin], OUTPUT);  

    digitalWrite(cols[thisPin], HIGH);
    digitalWrite(rows[thisPin], HIGH);  
    //initialize the matrix pins, taken from arduino website
  }
      pinMode(potPin, INPUT); //declare input for the potentiometer

    clearLeds();  //clear LED Matrix

   animationTime = millis();  //start level # animation timer
  
}

void loop(){

  for (int i = 0; i < 8; i++) {
    digitalWrite(rows[i], HIGH);  //all rows to high
    digitalWrite(cols[i], LOW);
  }
    digitalWrite(rows[0], LOW);
  delay(Delay);
  digitalWrite(rows[0], HIGH);

  setPattern(index);  //create levels
    /***Row 0***/
  for (int col = 0; col < 8; col++) {
    if (pixels[0][col] == 1) {
      digitalWrite(cols[col], HIGH); 
    } else {
      digitalWrite(cols[col], LOW);
    }
  }
  digitalWrite(rows[0], LOW);
  delay(Delay);
  digitalWrite(rows[0], HIGH);

  setPattern(index);  //create levels
  /***Row 1***/
  for (int col = 0; col < 8; col++) {
    if (pixels[1][col] == 1) {
      digitalWrite(cols[col], HIGH); 
    } else {
      digitalWrite(cols[col], LOW);
    }
  }
  digitalWrite(rows[1], LOW);
  delay(Delay);
  digitalWrite(rows[1], HIGH);
 
  if (levelAni) playLevelAni();  //play animation

//Row 2
for (int col = 0; col < 8; col++){
  if (pixels[2][col] ==1){
   digitalWrite(cols[col], HIGH); 
    } else {
      digitalWrite(cols[col], LOW);
    }
  }
  digitalWrite(rows[2], LOW);
  delay(Delay);
  digitalWrite(rows[2], HIGH);
  
  if (levelStart) readPot();
  //Read pot value and turn that led pixel on to display character but also move him across the board

 for (int col = 0; col < 8; col++) {
    if (pixels[3][col] == 1) {
      digitalWrite(cols[col], HIGH); 
    } else {
      digitalWrite(cols[col], LOW);
    }
  }
  digitalWrite(rows[3], LOW);
  delay(Delay);
  digitalWrite(rows[3], HIGH);
  
  if (levelStart) refreshPlayer(); 
   if (levelStart) continuousFire(); 

  /***Row 4***/
  for (int col = 0; col < 8; col++) {
    if (pixels[4][col] == 1) {
      digitalWrite(cols[col], HIGH); 
    } else {
      digitalWrite(cols[col], LOW);
    }
  }
  digitalWrite(rows[4], LOW);
  delay(Delay);
  digitalWrite(rows[4], HIGH);
 if (levelStart && !enemyWon) readEnemy();
 
  /***Row 5***/
  for (int col = 0; col < 8; col++) {
    if (pixels[5][col] == 1) {
      digitalWrite(cols[col], HIGH); 
    } else {
      digitalWrite(cols[col], LOW);
    }
  }
  digitalWrite(rows[5], LOW);
  delay(Delay);
  digitalWrite(rows[5], HIGH);
  
  if (levelStart && !levelComplete) checkLevelState();  
  //check for if the level is cleared of all pixels
  if (levelComplete) levelFinished();   


  
  /***Row 6***/
  for (int col = 0; col < 8; col++) {
    if (pixels[6][col] == 1) {
      digitalWrite(cols[col], HIGH); 
    } else {
      digitalWrite(cols[col], LOW);
    }
  }
  digitalWrite(rows[6], LOW);
  delay(Delay);
  digitalWrite(rows[6], HIGH);
  
    /***Row 7***/
  for (int col = 0; col < 8; col++) {
    if (pixels[7][col] == 1) {
      digitalWrite(cols[col], HIGH); 
    } else {
      digitalWrite(cols[col], LOW);
    }
  }
  digitalWrite(rows[7], LOW);
  delay(Delay);
  digitalWrite(rows[7], HIGH);
  
  unsigned long currentMillis = millis();
   
  if (enemyWon) gameOver();  //lose if hit by enemy
  updatePixels();  //update all pixels of the LED Matrix 

}



void clearLeds(){
  //function to clear Leds; sets them to 0 to turn them off
  //matrix would be 8x8 of all 0's like in the top of this as the temp matrix
  
 for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      pixels[i][j] = 0;
    }
  }
}

void setPattern(int pattern){
    if (index < 7) {  
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if ( levels[index][i][j] == 1 ) {  //put the 1s in the temp matrix from the level matrices
          tempMatrix[i][j] = levels[index][i][j];  
        }
      }
    }
  } else {
    restart();  //restart if the game has been won
  }
}
 void readPot(){
    //read Potentiometer and map it to a spot on the matrix
potVal = analogRead(potPin);
potVal = map(potVal, 1023, 0,-1, 6); // - 1 to 6 allows full range of motion across the screen
Serial.println(potVal); //to check where pot should be
//allow full movement across the display
//taken from arduino site on how to  control led in a matrix
//https://docs.arduino.cc/built-in-examples/display/RowColumnScanning



  }
  void refreshPlayer(){
    //also looked at the same link above for this
    byte playableRow[2][8] = {
       {0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0}
  };

  if (potVal == -1){
     playableRow[0][potVal +1] =1;
 // playableRow[1][potVal ] =1;
  playableRow[1][potVal +1] =1;      
  playableRow[1][potVal +2] =1;   
    
  }else {
  playableRow[0][potVal +1] =1;
  playableRow[1][potVal ] =1;
  playableRow[1][potVal +1] =1;      
  playableRow[1][potVal +2] =1;    
  }
     for (int i = 6; i < 8; i++) {     //rows 6-7 (where the player is)
    for (int j = 7; j >= 0; j--) {  //update player positions
       if(playableRow[i-6][j] == 1) {  //copy only "ones" to temporary matrix
         tempMatrix[i][j] = playableRow[i-6][j];
       }
    }
  } 
  }


  void continuousFire(){
 //int btnPress = digitalRead(btnPin);  //read button state
  int btnPress = 1;
  fired = 0;
  //btnDown = 0;
  if (btnPress == 1){      //if button is pressed
    bulletCol = potVal+1;      //bullet column value on matrix
   
    fired = true;
  } 
  if (fired == true) {   
    shoot(bulletCol);    //play shoot animation
  } 
}    
  



  void shoot(int _bulletCol) {
  
  if (bulletDelayCount == 2) {    //act as a delay & determines bullet's speed
    bulletRow--;
    
    if (bulletRow < 0) {  //if bullet reaches top (row 0)
      bulletRow = 5;    //reset bullet row position
      fired = false;    //bullet fire done
    } else {
      if (tempMatrix[bulletRow][_bulletCol] == 0) {  
        tempMatrix[bulletRow][_bulletCol] = 1; 
      } else {
        collisionBullet(bulletRow, _bulletCol);  
      }
     }
  } else {
    tempMatrix[bulletRow][_bulletCol] = 1;  
    //make the bullet show up on the display
  }
  bulletDelayCount = (bulletDelayCount+1) % 3;  //bullet speed
  
}
void collisionBullet(int _row, int _col) {

  levels[index][_row][_col] = 0;    //remove 1 pixel that got shot from original level matrix
  tempMatrix[_row][_col] = 0;  //update temp matrix for pixel display
  
  bulletRow = 5;    //set original bullet row position back to 5
  fired = false;    //bullet fire done
}




/*** READ ENEMY ***/
//Taken from marko on his how to make the space invader game
void readEnemy() {
  
  if (!enemyWaiting && !enemyFired && !enemyBulletCollision){  //if enemy isn't doing anything
    enemyTime = millis();  //start timer
    enemyWaiting = true;
  }
  
  if (enemyWaiting) {
    if (millis() - enemyTime > enemyAttackSpeed[index]) {  //attack speed for each level according to array 
      
      int _row = 3;   //temp row value
      boolean dobreak = false;    //for double break;
      
      //loop to get the enemy's pixels of highest row (closest to the player) 
      for (int i = 3; !dobreak && i >= 0; i--) {  //backwards loop to get highest row
        for (int j = 0; j < 8; j++) {
            if(levels[index][i][j] == 1) {  //if a "one" is found in the row
              _row = i;          //save row index
              enemyBulletRow = _row + 1;  //value to put enemy bullet 1 row below enemy
              dobreak = true;    //double break;
              break;
            }
         }  
      }
      
      enemyBottomCount = 0; //counter for number of "one" pixels in highest row (closest to the player) 
      for (int c = 0; c < 8; c++) {  //loop through highest row
        if(levels[index][_row][c] == 1) {   //check if column contains "one" 
          enemyBulletArray[enemyBottomCount][0] = _row;  
          enemyBulletArray[enemyBottomCount][1] = c;
          enemyBottomCount++;  
        }
      }
       
      enemyWaiting = false;
      enemyFired = true;  //fire enemy bullet
      randomBullet = random(enemyBottomCount);  //randomly select one of the column pixels
    }
  }
  
  if (enemyFired) {
    if (enemyBulletDelayCount == (enemyBulletSpeed[index]-1)) {  //enemy bullet speed (higher value = slower)
      enemyBulletArray[randomBullet][0]++;  //row + 1
      if  (enemyBulletArray[randomBullet][0] > 7) {  //if bullet reaches bottom
        enemyBulletDelayCount = 0;  //reset and remove bullet
        enemyFired = false;
      } else {
        if (tempMatrix[enemyBulletArray[randomBullet][0]] [enemyBulletArray[randomBullet][1]] == 0) {  //if next row is empty
          tempMatrix[enemyBulletArray[randomBullet][0]] [enemyBulletArray[randomBullet][1]] = 1;  //bullet claims row
        } else {  //bullet hit something!!
          if (!levelComplete) {
            enemyBulletDelayCount = 0;  
            enemyFired = false;
            enemyBulletCollision = true;
          }
        }
      }
    } else {
      tempMatrix[enemyBulletArray[randomBullet][0]][enemyBulletArray[randomBullet][1]] = 1;
    }
    enemyBulletDelayCount = (enemyBulletDelayCount+1) % enemyBulletSpeed[index];  //enemy bullet speed
  }
  
  if (enemyBulletCollision) {
    if (enemyBulletArray[randomBullet][0] == 6 || enemyBulletArray[randomBullet][0] == 7) {  //check if enemy's bullet hit player
//      digitalWrite(13, HIGH);
      Serial.println("HIT!");
      enemyWon = true;
      gameOverTime = millis();
    }
    enemyBulletCollision = false;
  }
}
  
void playLevelAni() {
  
  
  if (millis() - animationTime < 3000) {  //wait 3 seconds

  } else {
    levelAni = false;  
    //end the animation
    levelStart = true;
    index++;
    clearLeds(); //clear matrix
    
  }
}



void checkLevelState() {  //check if all level pixels (enemies) are dead
  int _countLevelPixels = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 8; j++) {
      if(levels[index][i][j] == 1){
        _countLevelPixels++;  //count the number of "one" pixels
      }
    }  
  }
  if((_countLevelPixels) == 0){  //if nothing left, congratz! you beat the level!
//    digitalWrite(13, HIGH);
//    Serial.println("COMPLETE!");
    completeTime = millis();
    levelComplete = true;
  }  
}


void levelFinished() { 
  
  if (millis() - completeTime > 2000) {  //time before transitioning to next level
  
    //reset all booleans
    enemyWaiting = false;
    enemyFired = false;
    enemyBulletCollision = false;

    levelStart = false;  
    levelComplete = false;
    levelAni = true;
    animationTime = millis();
    index++;
  }
}
void updatePixels() {
  //Use temporary 8x8 matrix to update actual matrix to prevent any bugs
  //Tends to get buggy when apply values straight to pixels[] matrix 
  //Instead, storing all matrix values in a temp and apply values to pixels[] at once is more stable
  
  //copy all temp matrix values to actual display matrix
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      pixels[i][j] = tempMatrix[i][j]; 
    }
  }
  
  //reset all values for temp matrix
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      tempMatrix[i][j] = 0;
    }
  }
}


void gameOver() {
  

  
  if (millis() - gameOverTime < 3000) {  //time before restarting
    delay(250);
  } else {
    restart();  
  }
  

}

void restart() {
  //reset all booleans
  enemyWon = false;
  enemyWaiting = false;
  enemyFired = false;
  enemyBulletCollision = false;
  
  levelAni = true;
  levelStart = false;  
  levelComplete = false;
  index = 0;
  

  
  //reset all levels
  for (int level = 0; level<lvls; level++) {
     for (int x = 0; x<8; x++) {
       for (int y = 0; y<8; y++) {
         levels[level][x][y] = initial[level][x][y];
       }
     }
   }

  animationTime = millis();  //run level 1 animation 
}
