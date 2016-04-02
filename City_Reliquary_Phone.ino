
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#include <SoftReset.h>
#include <FatReader.h>
#include <SdReader.h>
#include <avr/pgmspace.h>
#include "WaveUtil.h"
#include "WaveHC.h"
SdReader card;    // This object holds the information for the card
FatVolume vol;    // This holds the information for the partition on the card
FatReader root;   // This holds the information for the filesystem on the card
FatReader f;      // This holds the information for the file we're play
WaveHC wave;      // This is the only wave (audio) object, since we will only play one at a time


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Keypad.h>

int inPin = A1;   // receiver connected to digital pin 7
int val = 0;     // variable to store the read value
const int ledPin =  6;      // the number of the LED pin

// Variables will change:
long previousMillis = 0;        // will store last time LED was updated
long timeInterval = 1000;   
int ledState = LOW;             // ledState used to set the LED

///////KEYPAD
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
{'*','0','#'},
{'7','8','9'},
{'4','5','6'},
{'1','2','3'}
};
byte rowPins[ROWS] = {9, A4, A3, A2}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {A0, 7, 8}; //connect to the column pinouts of the kpd

Keypad keyP = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

unsigned long loopCount;
unsigned long startTimeT;
String msg;

//LED VAR
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
unsigned long currentTime;
unsigned long loopTime;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// this handy function will return the number of bytes currently free in RAM, great for debugging!   
int freeRam(void)
{
  extern int  __bss_end; 
  extern int  *__brkval; 
  int free_memory; 
  if((int)__brkval == 0) {
    free_memory = ((int)&free_memory) - ((int)&__bss_end); 
  }
  else {
    free_memory = ((int)&free_memory) - ((int)__brkval); 
  }
  return free_memory; 
} 

void sdErrorCheck(void)
{
  if (!card.errorCode()) return;
  putstring("\n\rSD I/O error: ");
  Serial.print(card.errorCode(), HEX);
  putstring(", ");
  Serial.println(card.errorData(), HEX);
  while(1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void setup() {
    Serial.begin(9600);
    //LED - HANG UP
    pinMode(inPin, INPUT_PULLUP);      // sets the digital pin 7 as input
    pinMode(ledPin, OUTPUT);  
   
    Serial.println("Wave Shield TEST ");

   //LED SETUP
   currentTime = millis();
    loopTime = currentTime; 



    loopCount = 0;
    startTimeT = millis();
    msg = "";
    
    putstring("Free RAM: ");       
  Serial.println(freeRam());  
  
  // Set the output pins for the DAC control. This pins are defined in the library
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
 
randomSeed(analogRead(0));
  
  if (!card.init()) {         //play with 8 MHz spi (default faster!)  
    putstring_nl("Card init. failed!");  // Something went wrong, lets print out why
    sdErrorCheck();
    while(1);                            // then 'halt' - do nothing!
  }
  
  // enable optimize read - some cards may timeout. Disable if you're having problems
  card.partialBlockRead(true);
 
// Now we will look for a FAT partition!
  uint8_t part;
  for (part = 0; part < 5; part++) {     // we have up to 5 slots to look in
    if (vol.init(card, part)) 
      break;                             // we found one, lets bail
  }
  if (part == 5) {                       // if we ended up not finding one  :(
    putstring_nl("No valid FAT partition!");
    sdErrorCheck();      // Something went wrong, lets print out why
    while(1);                            // then 'halt' - do nothing!
  }
  
  // Lets tell the user about what we found
  putstring("Using partition ");
  Serial.print(part, DEC);
  putstring(", type is FAT");
  Serial.println(vol.fatType(),DEC);     // FAT16 or FAT32?
  
  // Try to open the root directory
  if (!root.openRoot(vol)) {
    putstring_nl("Can't open root dir!"); // Something went wrong,
    while(1);                             // then 'halt' - do nothing!
  }
  
  // Whew! We got past the tough parts.
  putstring_nl("Ready!");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
      unsigned long currentMillis = millis();
      int timeInterval = 1500;
      val = digitalRead(inPin);   // read the input pin

      if (val == 0){ 
      char key = keyP.getKey();

      ledState = HIGH;
      digitalWrite(ledPin, ledState);
         
         while (!wave.isplaying){
            playfile ("tone.WAV");
            }

/* BELOW IS WHERE ALL AUDIOFILES ARE ASSIGNED TO THE KEY PRESSES*/         
        

        if(key == '1') {
          wave.stop();
          //the key tone + phone ring
          playcomplete("press1.WAV");
          //the main audiofile
          playfile("1_key.wav"); 
         }
 
         else if(key == '2') {
          wave.stop(); 
          playcomplete("press2.WAV");
          playfile("2_key.WAV");
         }
 
         else if(key == '3'){  
          wave.stop(); 
          playcomplete("press3.WAV"); 
          playfile("3_key.WAV"); 
         }


         else if(key == '4'){ 
          wave.stop(); 
          playcomplete("press4.WAV"); 
          playfile("4_key.WAV"); 
 
         }

         else if(key == '5'){ 
          wave.stop();  
          playcomplete("press5.WAV"); 
          playfile("5_key.WAV"); 
         }

         else if(key == '6'){ 
          wave.stop(); 
          playcomplete("press6.WAV"); 
          playfile("6_key.WAV"); 
         }

         else if(key == '7'){ 
          wave.stop();  
          playcomplete("press7.WAV"); 
          playfile("7_key.WAV"); 
         }

         else if(key == '8'){ 
          wave.stop(); 
          playcomplete("press8.WAV"); 
          playfile("8_key.WAV"); 
         }

         else if(key == '9'){ 
          wave.stop(); 
          playcomplete("press9.WAV"); 
          playfile("9_key.WAV"); 
         }

         else if(key == '*'){ 
          wave.stop();  
          playcomplete("p_star.WAV"); 
          playfile("star_key.WAV"); 
        }

         else if(key == '0') {
          wave.stop();
          playcomplete("press0.WAV");
          playfile("0_key.WAV"); 
          }

         else if(key == '#'){ 
          wave.stop(); 
          playcomplete("press#.WAV"); 
          playfile("#_key.WAV"); //fix
         }
 
}
 
  
  else if (val == 1) { 
      //stops the audio
      wave.stop(); 
      
      //pulses the led on the phone
      currentTime = millis();
       
      
          if(currentTime >= (loopTime + 20)){  
            analogWrite(6, brightness);    
            // updates the brightness
            brightness = brightness + fadeAmount;
            // fades up or down depending on state

            
              if (brightness == 0 || brightness == 255) {
                fadeAmount = -fadeAmount ; 
              }     
            loopTime = currentTime;  // Updates loopTime
         


            
          
       }
 }
 
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void playcomplete(char *name) {
  playfile(name);
  while (wave.isplaying) {
  //no action
  }
}
    


void playfile(char *name) {

  // look in the root directory and open the file
  if (!f.open(root, name)) {
    putstring("Couldn't open file "); Serial.print(name); return;
  }
  // OK read the file and turn it into a wave object
  if (!wave.create(f)) {
    putstring_nl("Not a valid WAV"); return;
  }
  
  // ok time to play! start playback
  wave.play();
}


  

