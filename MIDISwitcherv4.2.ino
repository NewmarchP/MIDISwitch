//####  Pete's MIDI Controller  ####
// Based on the Evening Sun
// Based on the MorningStar MC6

#include <Wire.h>
#include <MIDI.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <OneButton.h>

MIDI_CREATE_DEFAULT_INSTANCE();


// ##################### Power and GND for Midi In and Midi OUT ####################
int gndPin = 11;    // set to LOW and connect GND to the midi circuit here. (no need to disconnect midi devices for sketch upload)
int powerPin = 12;  // set to HIGH and connect power to the midi circuit here. (no need to disconnect midi devices for sketch upload)

// ##################### Pins for Buttons ####################
OneButton SwitchA(7, true);  // Setup a new OneButton
OneButton SwitchB(6, true);  // Setup a new OneButton
OneButton SwitchC(5, true);
OneButton SwitchD(8, true);
OneButton SwitchE(9, true);
OneButton SwitchF(10, true);

//##################### Banks ####################
int bank = 1;
int maxbank = 5;
boolean BankHasChanged = true;
int bankchangedelay = 550;  // determines how fast you can scroll through the banks
String BankName[10] = { "Amp1", "Amp2", "Amp3", "Amp4", "Amp5", "AmpLess1", "Ampless2", "Ampless3", "Ampless4", "Ampless5" };

//##################### Display ####################
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET 4      // Reset pin # (or -1 if sharing Arduino reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const long interval = 450;
unsigned long previousMillis = 0;


void show() {  // Often used sequence - Function to simplify code
  display.display();
  delay(100);
  display.fillScreen(SSD1306_BLACK);
}

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.begin(31250);  //MIDI:31250 // SERIAL MONITOR:9600 OR 115200
  MIDI.begin();

  //Setup Display

  int cw = SSD1306_WHITE;
  int cb = SSD1306_BLACK;

  //Initial Display Scene
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("IT WORKS!");
  show();


  //pins for Midi (including power supply pins, so midi is not screwed up when uploading a new sketch)
  pinMode(powerPin, OUTPUT);
  pinMode(gndPin, OUTPUT);
  digitalWrite(powerPin, HIGH);  // Power up
  digitalWrite(gndPin, LOW);     // Power up

  // link the button functions
  SwitchA.attachClick(SwitchAclick);
  SwitchA.attachDuringLongPress(SwitchAlongPress);
  SwitchA.attachLongPressStop(SwitchAlongPressStop);
  SwitchB.attachClick(SwitchBclick);
  SwitchB.attachDuringLongPress(SwitchBlongPress);
  SwitchB.attachLongPressStop(SwitchBlongPressStop);
  SwitchC.attachClick(SwitchCclick);
  SwitchD.attachClick(SwitchDclick);
  SwitchE.attachClick(SwitchEclick);
  SwitchF.attachClick(SwitchFclick);
  SwitchA.setLongPressIntervalMs(400);
  SwitchB.setLongPressIntervalMs(400);


  delay(2000);

  MIDI.sendProgramChange(0,2);
  MIDI.sendProgramChange(124,1);
}

void loop() {
  // ********************Monitor the Buttons***************
  SwitchA.tick();
  SwitchB.tick();
  SwitchC.tick();
  SwitchD.tick();
  SwitchE.tick();
  SwitchF.tick();


  //*********** Bank Change Actions (Display setup, Midi Events) ******************
  //On a 20x4 Display, each text block can be 6 letters long (with a space between the blocks)

  //**** BANK 1 ****
  if (bank == 1 && BankHasChanged == true) {
    //Display 1
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Bank");
    display.setCursor(0, 36);
    display.setTextSize(4);
    display.println("1");
    show();


    BankHasChanged = false;
  }

  //**** BANK 2 ****
  if (bank == 2 && BankHasChanged == true) {
    //Display 1
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Bank");
    display.setCursor(0, 36);
    display.setTextSize(4);
    display.println("2");
    show();


    BankHasChanged = false;
  }

  //**** BANK 3 ****
  if (bank == 3 && BankHasChanged == true) {
    //Display 1
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Bank");
    display.setCursor(0, 36);
    display.setTextSize(4);
    display.println("3");
    show();


    BankHasChanged = false;
  }

  if (bank == 4 && BankHasChanged == true) {
    //Display 1
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Bank");
    display.setCursor(0, 36);
    display.setTextSize(4);
    display.println("4");
    show();


    BankHasChanged = false;
  }

  if (bank == 5 && BankHasChanged == true) {

    //Display 1
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Bank");
    display.setCursor(0, 36);
    display.setTextSize(4);
    display.println("5");
    show();

    BankHasChanged = false;
  }
}  // Loop

//****** AAAA ************ AAAA ************ AAAA ************ AAAA ************ AAAA ************ AAAA ************ AAAA ************ AAAA ******
void SwitchAclick() {
  switch (bank){
    case 1: //VinClean
    MIDI.sendControlChange(1,0,3);    //Fuzz
    MIDI.sendControlChange(2,0,3);  //Blues Breaker
    MIDI.sendControlChange(3,0,3);    //ZenDrive
    MIDI.sendControlChange(4,0,3);    //Pinnacle
    MIDI.sendControlChange(5,0,3);    //LightSpeed
    MIDI.sendControlChange(6,0,3);    //Empty
    MIDI.sendProgramChange(124,1);
    MIDI.sendProgramChange(0,2);
    break;

    case 2: //Edgy
    MIDI.sendControlChange(1,0,3);    //Fuzz
    MIDI.sendControlChange(2,127,3);  //Blues Breaker
    MIDI.sendControlChange(3,0,3);    //ZenDrive
    MIDI.sendControlChange(4,0,3);    //Pinnacle
    MIDI.sendControlChange(5,0,3);    //LightSpeed
    MIDI.sendControlChange(6,0,3);    //Empty
    MIDI.sendProgramChange(126,1);
    MIDI.sendProgramChange(0,2);
    break;

    case 3: //Wet
    MIDI.sendControlChange(1,0,3);    //Fuzz
    MIDI.sendControlChange(2,127,3);  //Blues Breaker
    MIDI.sendControlChange(3,0,3);    //ZenDrive
    MIDI.sendControlChange(4,0,3);    //Pinnacle
    MIDI.sendControlChange(5,0,3);    //LightSpeed
    MIDI.sendControlChange(6,0,3);    //Empty
    MIDI.sendProgramChange(127,1);
    MIDI.sendProgramChange(0,2);
    break;
}
}
void SwitchAlongPress()  //Switch D longpress will ALWAYS be "Bank Down", so we dont have to distinguish the banks here
{
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
  
  //Count Bank down
    {
    if (bank > 1) {
      bank = bank - 1;
    }else bank = maxbank;
    //    BankHasChanged = true;
  }
  Display1();
  PrintBankName();
  }
}

void SwitchAlongPressStop(){
  BankHasChanged = true;
}

//****** BBBB ************ BBBB ************ BBBB ************ BBBB ************ BBBB ************ BBBB ************ BBBB ************ BBBB ******
void SwitchBclick() {
  switch (bank){
    case 1: //BasicRhythm
    MIDI.sendControlChange(1,0,3);    //Fuzz
    MIDI.sendControlChange(2,127,3);  //Blues Breaker
    MIDI.sendControlChange(3,0,3);    //ZenDrive
    MIDI.sendControlChange(4,0,3);    //Pinnacle
    MIDI.sendControlChange(5,0,3);    //LightSpeed
    MIDI.sendControlChange(6,0,3);    //Empty
    MIDI.sendProgramChange(125,1);
    MIDI.sendProgramChange(0,2);
    break;

    case 2: //Heavier Rhythm
    MIDI.sendControlChange(1,0,3);    //Fuzz
    MIDI.sendControlChange(2,127,3);  //Blues Breaker
    MIDI.sendControlChange(3,127,3);    //ZenDrive
    MIDI.sendControlChange(4,0,3);    //Pinnacle
    MIDI.sendControlChange(5,0,3);    //LightSpeed
    MIDI.sendControlChange(6,0,3);    //Empty
    MIDI.sendProgramChange(125,1);
    MIDI.sendProgramChange(0,2);
    break;
    
    case 3: //Crunchy
    MIDI.sendControlChange(1,0,3);    //Fuzz
    MIDI.sendControlChange(2,0,3);  //Blues Breaker
    MIDI.sendControlChange(3,0,3);    //ZenDrive
    MIDI.sendControlChange(4,127,3);    //Pinnacle
    MIDI.sendControlChange(5,0,3);    //LightSpeed
    MIDI.sendControlChange(6,0,3);    //Empty
    MIDI.sendProgramChange(125,1);
    MIDI.sendProgramChange(0,2);
    break;
  }
}

void SwitchBlongPress()  //Switch D longpress will ALWAYS be "Bank Down", so we dont have to distinguish the banks here
{
    unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
  
  //Count Bank down
    {
    if (bank < maxbank) {
      bank = bank + 1;
    }else bank = 1;
    //    BankHasChanged = true;
  }
  Display1();
  PrintBankName();
}
}

void SwitchBlongPressStop(){
  BankHasChanged = true;
}

void SwitchCclick(){
    MIDI.sendControlChange(5,127,3);    //LightSpeed
}

void SwitchDclick(){
  switch (bank){
    case 1: //Bluesy
    MIDI.sendControlChange(1,0,3);    //Fuzz
    MIDI.sendControlChange(2,0,3);  //Blues Breaker
    MIDI.sendControlChange(3,127,3);    //ZenDrive
    MIDI.sendControlChange(4,0,3);    //Pinnacle
    MIDI.sendControlChange(5,0,3);    //LightSpeed
    MIDI.sendControlChange(6,0,3);    //Empty
    MIDI.sendProgramChange(125,1);
    MIDI.sendProgramChange(0,2);
    break;

    case 2: //Heavier Rhythm
    MIDI.sendControlChange(1,0,3);    //Fuzz
    MIDI.sendControlChange(2,0,3);  //Blues Breaker
    MIDI.sendControlChange(3,0,3);    //ZenDrive
    MIDI.sendControlChange(4,127,3);    //Pinnacle
    MIDI.sendControlChange(5,0,3);    //LightSpeed
    MIDI.sendControlChange(6,0,3);    //Empty
    MIDI.sendProgramChange(125,1);
    MIDI.sendProgramChange(0,2);
    break;
    
    case 3: //Crunchy
    MIDI.sendControlChange(1,0,3);    //Fuzz
    MIDI.sendControlChange(2,127,3);  //Blues Breaker
    MIDI.sendControlChange(3,0,3);    //ZenDrive
    MIDI.sendControlChange(4,127,3);    //Pinnacle
    MIDI.sendControlChange(5,0,3);    //LightSpeed
    MIDI.sendControlChange(6,0,3);    //Empty
    MIDI.sendProgramChange(125,1);
    MIDI.sendProgramChange(0,2);
    break;
  }
}


void SwitchEclick(){
  switch (bank){
    case 1: //Fuzz
    MIDI.sendControlChange(1,127,3);    //Fuzz
    MIDI.sendControlChange(2,127,3);  //Blues Breaker
    MIDI.sendControlChange(3,0,3);    //ZenDrive
    MIDI.sendControlChange(4,0,3);    //Pinnacle
    MIDI.sendControlChange(5,0,3);    //LightSpeed
    MIDI.sendControlChange(6,0,3);    //Empty
    MIDI.sendProgramChange(127,1);
    MIDI.sendProgramChange(0,2);
    break;

    case 2: //Heavier Rhythm
    MIDI.sendControlChange(1,127,3);    //Fuzz
    MIDI.sendControlChange(2,0,3);  //Blues Breaker
    MIDI.sendControlChange(3,127,3);    //ZenDrive
    MIDI.sendControlChange(4,0,3);    //Pinnacle
    MIDI.sendControlChange(5,0,3);    //LightSpeed
    MIDI.sendControlChange(6,0,3);    //Empty
    MIDI.sendProgramChange(125,1);
    MIDI.sendProgramChange(0,2);
    break;
    
    case 3: //Crunchy
    MIDI.sendControlChange(1,127,3);    //Fuzz
    MIDI.sendControlChange(2,0,3);  //Blues Breaker
    MIDI.sendControlChange(3,0,3);    //ZenDrive
    MIDI.sendControlChange(4,127,3);    //Pinnacle
    MIDI.sendControlChange(5,0,3);    //LightSpeed
    MIDI.sendControlChange(6,0,3);    //Empty
    MIDI.sendProgramChange(127,1);
    MIDI.sendProgramChange(0,2);
    break;
  }
}


void SwitchFclick(){
  MIDI.sendControlChange(29,127,2);
}

void PrintBankName(){
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(3);
  display.println("Bank");
  display.setTextSize(4);
  display.setCursor(0,36);
  display.println(bank);
  show();
}

void VinClean(){
  MIDI.sendProgramChange(1,3);
}

void Display1(){
  Wire.beginTransmission(0x70);
  Wire.write(1<<0);
  Wire.endTransmission();
}

void Display2(){
  Wire.beginTransmission(0x70);
  Wire.write(1<<1);
  Wire.endTransmission();
}

void Display3(){
  Wire.beginTransmission(0x70);
  Wire.write(1<<2);
  Wire.endTransmission();
}