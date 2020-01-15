//Software: Kippspiegel Gerät
//Autor: Rafal Andrejczuk
//Beendet am 15.01.2020

#include <EEPROM.h>

#define kippS 5 //Modus 1
#define tastS 4 //Modus 2


#define led_gelb 7   //Widerstand-Wert(gelb): 220 Ohm
#define led_rot 8   //Widerstand-Wert(rot): 220 Ohm
#define led_gruen 6

//Motorsteuerung
#define CLOCK 3       //externer Takt   
#define CW 2          //(eng. clockwise) Drehrichtungssinn   
#define DE 9  //EIN/AUS Treiber (DE- Driver Enable)
                        
int adresse = 0; //Adresse in dem EEPROM-Speicher, wo der aktuelle Schritt gespeichert ist

//-------------------------------------------------------------------------------------------------------------------------                      
void setup() {
  
  Serial.begin(9600); //Kommunikation mit PC via USB
  
  while(!Serial){ //Endlosschleife, wartet bis die Komm. aufgebaut ist 
    }
  
  pinMode(kippS, INPUT_PULLUP);
  pinMode(tastS, INPUT_PULLUP);
  
  pinMode(led_gelb, OUTPUT);
  pinMode(led_rot, OUTPUT);
  pinMode(led_gruen, OUTPUT);
  
  pinMode(CLOCK, OUTPUT);
  pinMode(CW, OUTPUT);
  pinMode(DE, OUTPUT);
  
  //Initialisieren
  
  digitalWrite(led_gelb, LOW);
  digitalWrite(led_rot, LOW);
  digitalWrite(led_gruen, LOW);
  
  digitalWrite(CLOCK, LOW);
  digitalWrite(CW, LOW);
  digitalWrite(DE, LOW);

  //EEPROM.put(adresse, 0); //nur einmal mit dieser Zeile laufen lassen
  
  home_position();
  }

//-------------------------------------------------------------------------------------------------------------------------  
void loop(){

  if(kippS_state()){
    
    dreh_rechts(12,100);
    dreh_links(12,100);
    
  }
  else if(taster_gedrueckt_worden() && !kippS_state()){
    
    dreh_rechts(2,100);
    delay(3000);
    dreh_links(2,100);
  }
}
//-------------------------------------------------------------------------------------------------------------------------
//Parameter int a - Anzahl der Schritte
//Parameter int periode - Periode in ms
void dreh_links(int a, int periode){

    
    digitalWrite(led_gelb, HIGH);
    digitalWrite(DE, HIGH);
    digitalWrite(CW, LOW);
    delay(50);
  
  for( int i=0; i<a; i++ ){
    digitalWrite(CLOCK, HIGH);
    EEPROM.put(adresse, EEPROM.read(adresse) - 1);
    Serial.println(EEPROM.read(adresse));
    digitalWrite(CLOCK, LOW);
    delay(periode);
    
    }

    
    digitalWrite(led_gelb, LOW);
    digitalWrite(DE, LOW);
  }
  //Parameter int a - Anzahl der Schritte
  //Parameter int periode - Periode in ms
  void dreh_rechts(int a, int periode){

    digitalWrite(led_rot, HIGH);
    digitalWrite(DE, HIGH);
    digitalWrite(CW, HIGH);
    delay(50);
    
  for( int i=0; i<a ; i++ ){
    digitalWrite(CLOCK, HIGH);
    EEPROM.put(adresse, EEPROM.read(adresse) + 1);
    Serial.println(EEPROM.read(adresse));
    digitalWrite(CLOCK, LOW);
    delay(periode);
    }

    digitalWrite(led_rot, LOW);
    digitalWrite(DE, LOW);
    
  }
  
//Tasterlesen
  boolean taster_gedrueckt_worden(){
    
    boolean tastS_state = digitalRead(tastS);
    unsigned long delta_zeit;
    static byte flag = 0; //gedruckt gehalten flag
    
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
//Referenzlage wird erreicht, wenn der aktuelle Schritt den Wert Null erreicht
    void home_position(){
      
      int akt_schritt = EEPROM.read(adresse);
      
      if(akt_schritt != 0)
      dreh_links(akt_schritt,100);
    }
    
