//Software: Kippspiegel Gerät
//Autor: Rafal Andrejczuk

#include <EEPROM.h>

#define kippS 5 //Modus 1
#define tastS 4 //Modus 2


#define led_gelb 7   //Widerstand-Wert(gelb): 220 Ohm
#define led_rot 8   //Widerstand-Wert(rot): 220 Ohm
#define led_gruen 6

//Motorsteuerung
#define CLOCK 3       //externer Takt   
#define CW 2          //(eng. clockwise) Drehrichtungssinn   
#define DRIVER_ENABLE   //EIN/AUS Treiber
                        
static int motor_position = 0;
const int motor_referenzpos = 0;

//-------------------------------------------------------------------------------------------------------------------------                      
void setup() {
  
//  Serial.begin(9600); //Kommunikation mit PC via USB
//  
//  while(!Serial){ //Endlosschleife, wartet bis die Komm. aufgebaut ist 
//    }
  
  pinMode(kippS, INPUT_PULLUP);
  pinMode(tastS, INPUT_PULLUP);
  
  pinMode(led_gelb, OUTPUT);
  pinMode(led_rot, OUTPUT);
  pinMode(led_gruen, OUTPUT);
  
  pinMode(CLOCK, OUTPUT);
  pinMode(CW, OUTPUT);

  //Initialisieren
  
  digitalWrite(led_gelb, LOW);
  digitalWrite(led_rot, LOW);
  digitalWrite(led_gruen, LOW);
  
  digitalWrite(CLOCK, LOW);
  digitalWrite(CW, LOW);
  }

//-------------------------------------------------------------------------------------------------------------------------  
void loop(){

  if(kippS_state()){
    dreh_links(5);
    dreh_rechts(5);
  }
  else if(taster_gedrueckt_worden() && !kippS_state()){
    dreh_links(2);
    delay(1000);
    dreh_rechts(2);
  }
}
//-------------------------------------------------------------------------------------------------------------------------
//Parameter int a - Anzahl der Schritte
void dreh_links(int a){
  
    digitalWrite(CW, LOW);
    delay(50);
    digitalWrite(led_gelb, HIGH);
  
  for( int i=0; i<a; i++ ){
    digitalWrite(CLOCK, HIGH);
    digitalWrite(CLOCK, LOW);
    delay(100);
    }

    digitalWrite(led_gelb, LOW);
    
  }
  //Parameter int a - Anzahl der Schritte
  void dreh_rechts(int a){

    digitalWrite(CW, HIGH);
    delay(50);
    digitalWrite(led_rot, HIGH);
    
  for( int i=0; i<a ; i++ ){
    digitalWrite(CLOCK, HIGH);
    digitalWrite(CLOCK, LOW);
    delay(100);
    }

    digitalWrite(led_rot, LOW);
    
  }
  
//Tasterlesen
  boolean taster_gedrueckt_worden(){
    
    boolean tastS_state = digitalRead(tastS);
    unsigned long delta_zeit;
    static byte flag = 0; //gedruckt gehalten
    
    if(tastS_state == LOW){
      static unsigned long zp_alt = millis();
      unsigned long zp_neu = millis();
      delta_zeit = zp_neu - zp_alt;
      int prell_zeit = 500;

      
      if (delta_zeit >= prell_zeit){
        if(flag == 1){
          return false;
          }
        zp_alt = zp_neu;
      }
      else if(delta_zeit == 0){
        flag = 1;
        return true;
      }
      else if(delta_zeit < prell_zeit){
        return false; 
      }
            
      }
      else {
        flag = 0;
        return false;}
    }
//Kippschalter lesen
  boolean kippS_state(){
    
    boolean kippS_state = digitalRead(kippS);
    unsigned long delta_zeit;
    int prell_zeit = 100;
    
    if(kippS_state == LOW){
      static unsigned long zp_alt = millis();
      unsigned long zp_neu = millis();
      delta_zeit = zp_neu - zp_alt;
      
      if (delta_zeit >= prell_zeit){
        zp_alt = zp_neu;
        delta_zeit = 0;
        Serial.println(delta_zeit);
      }
      if(delta_zeit == 0){
        Serial.println(delta_zeit);
        return true;
      }
      else if(delta_zeit < prell_zeit){
        Serial.println(delta_zeit);
        return true; 
      }
            
      }
      else {
        if (delta_zeit == 0){
          return false;
        }
      }    
  }
//Anhand der Position gespeichert im EEPROM wird zuerst in in HOME-Position gefahren
    void home_fahren(){
    }
    
