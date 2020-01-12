//Software: Kippspiegel Gerät
//Autor: Rafal Andrejczuk


#define kippS 7 //Modus 1
#define tastS 4 //Modus 2

#define led_gelb 12
#define led_rot 13

//Motorsteuerung
#define CLOCK           //PIN 5, Schritt wird bei jeder negativen Flanke des Eingangssignales geschalten, Achtung: internen Takt unbedingt abschalten (SW1=OFF)!
#define CW              //PIN 4, Drehrichtung, offener Eingang wird als High-Signal interpretiert, Low-Signal führt zum Richtungswechsel (5V am Pin führt zum Richtungswechsel)
#define DRIVER_ENABLE   //PIN 2, offener Eingang wird als High-Signal interpretiert, bei High-Signal stoppt Motor die Bewegung, Motorphasen sind unbestromt!
                        //bei Low-Signal erfolgt Bestromung, Achtung: vor Benutzung Konfigurationsschalter abschalten (SW3=OFF), sonst immer aktiv (5V am Pin führt zum Einschalten)

                        
void setup() {
  
pinMode(INPUT_PULLUP,kippS);
pinMode(INPUT_PULLUP,tastS);
pinMode(OUTPUT,led_gelb);
pinMode(OUTPUT,led_rot);

//init
digitalWrite(LOW,led_gelb);
digitalWrite(LOW,led_rot);

}

void loop() {


}

boolean tastergedrueckt(){
  
  // 0 GEDRUECKT, 1 NICHT GEDRUECKT
  
  tastS_ist = digitalRead(tastS); //IST-Zustand
  static boolean tastS_war = 1 ; //WAR-Zustand
  
  if(tastS_ist == 0){
    tastS_war = 0;
    erg = 1;
    return erg;
  }
  if(tastS == 1 && tastS_war == 0 ){
    
  }
  
}

boolean schaltergedrueckt(){
  
}
