//Software: Kippspiegel Gerät
//Autor: Rafal Andrejczuk
#include <Bounce2.h>


#define kippS 4 //Modus 1
#define tastS 2 //Modus 2

#define led_gelb 7   //Widerstand-Wert(gelb): 220 Ohm
#define led_rot 12   //Widerstand-Wert(rot): 220 Ohm

//Motorsteuerung
#define CLOCK           //PIN 5, Schritt wird bei jeder negativen Flanke des Eingangssignales geschalten, Achtung: internen Takt unbedingt abschalten (SW1=OFF)!
#define CW              //PIN 4, Drehrichtung, offener Eingang wird als High-Signal interpretiert, Low-Signal führt zum Richtungswechsel (5V am Pin führt zum Richtungswechsel)
#define DRIVER_ENABLE   //PIN 2, offener Eingang wird als High-Signal interpretiert, bei High-Signal stoppt Motor die Bewegung, Motorphasen sind unbestromt!
                        //bei Low-Signal erfolgt Bestromung, Achtung: vor Benutzung Konfigurationsschalter abschalten (SW3=OFF), sonst immer aktiv (5V am Pin führt zum Einschalten)

// Instanzieren von einem Bounce Objekt
Bounce entpreller1 = Bounce();
Bounce entpreller2 = Bounce();  
                      
void setup() {
  
pinMode(kippS, INPUT_PULLUP);
pinMode(tastS, INPUT_PULLUP);
pinMode(led_gelb, OUTPUT);
pinMode(led_rot, OUTPUT);

//Setup von der Bounce Instanz
entpreller1.attach(tastS);
entpreller1.interval(5); // interval in ms

entpreller2.attach(kippS);
entpreller2.interval(5); // interval in ms

//init
digitalWrite(led_gelb,LOW);
digitalWrite(led_rot,LOW);
}

void loop() {
  
  //Aktualisiere von der Bounce Instanz
  entpreller1.update();
  entpreller2.update();
  
  //lesen des aktualisierten Wertes
  int tastS_state = entpreller1.read();
  int kippS_state = entpreller2.read();
  
  if (tastS_state == LOW){
    digitalWrite(led_rot,HIGH);
  }
  else {
    digitalWrite(led_rot,LOW);  
  }
    if (kippS_state == LOW){
    digitalWrite(led_gelb,HIGH);
  }
  else {
    digitalWrite(led_gelb,LOW);  
  }
  
  
}
