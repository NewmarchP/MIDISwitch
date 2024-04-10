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
int gndPin = 10;    // set to LOW and connect GND to the midi circuit here. (no need to disconnect midi devices for sketch upload)
int powerPin = 11;  // set to HIGH and connect power to the midi circuit here. (no need to disconnect midi devices for sketch upload)

// ##################### Pins for Buttons ####################
OneButton SwitchA(2, true);  // Setup a new OneButton
OneButton SwitchB(3, true);  // Setup a new OneButton
OneButton SwitchC(4, true);
OneButton SwitchD(5, true);
OneButton SwitchE(6, true);
OneButton SwitchF(7, true);

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

const long interval = 300;
unsigned long previousMillis = 0;

int Bank1A;
int Bank1B;
int Bank1C;
int Bank1D;

int Bank2A;
int Bank2B;
int Bank2C;
int Bank2D;

int Bank3A;
int Bank3B;
int Bank3C;
int Bank3D;

int Bank4A;
int Bank4B;
int Bank4C;
int Bank4D;

int Bank5A;
int Bank5B;
int Bank5C;
int Bank5D;

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
  display.println("Pete");
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
}

void loop() {
  // ********************Monitor the Buttons***************
  SwitchA.tick();
  SwitchB.tick();
  SwitchC.tick();
  SwitchD.tick();
  SwitchE.tick();
  SwitchF.tick();

  Bank1A = VinClean;

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
    VinClean;
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
  PrintBankName();
  }
}

void SwitchAlongPressStop(){
  BankHasChanged = true;
}

//****** BBBB ************ BBBB ************ BBBB ************ BBBB ************ BBBB ************ BBBB ************ BBBB ************ BBBB ******
void SwitchBclick() {
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(3);
    display.println("Poop");
    show();
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
  PrintBankName();
}
}

void SwitchBlongPressStop(){
  BankHasChanged = true;
}

void SwitchCclick(){
  ;
}

void SwitchDclick(){
  ;
}

void SwitchEclick(){
  ;
}

void SwitchFclick(){
  ;
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