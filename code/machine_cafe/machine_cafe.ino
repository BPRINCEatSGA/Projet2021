const int bouton1 = 2; //le bouton petit café est connecté à la broche 2 de la carte Adruino
const int bouton2 = 3; //le bouton grand café 
const int chauffage = 6; 
const int pompe = 7;
int etatBouton1;
int etatBouton2;
long unsigned lastDebounceTime = 0;
long unsigned lastDebounceTime1 = 1000;
long unsigned lastDebounceTime2 = 0;
long unsigned lastDebounceTime3 = 8000;
long unsigned debounceDelay  = 3000;  
long unsigned debounceDelay1  = 5000; 
int etat_machine = 0; // 0 en attente, 1 en fonctionnement

void cafe_court()

   {
   digitalWrite(chauffage, HIGH); // on active le chauffage
   delay(300);
   etat_machine = 1;
   digitalWrite(pompe, HIGH); // on active la pompe
   Serial.println("café court en cour"); 
   
        
    }

void cafe_long()
{
   
   digitalWrite(chauffage, HIGH); // on active le chauffage
   delay(300);
   etat_machine = 2;
   digitalWrite(pompe, HIGH); // on active la pompe
   Serial.println("café long en court"); 
   
}


void interruption1()
{ 
  Serial.println("bouton1"); 
    if (etat_machine == 0)
   {  lastDebounceTime = millis();
      cafe_court();}
   

else 

{ Serial.println ("interrution");
  if ((millis() - lastDebounceTime) > lastDebounceTime1 )
{ lastDebounceTime2 = millis ;    
  etat_machine = 3;
  Serial.println("interruption1");  
  digitalWrite(pompe, LOW);
  digitalWrite(chauffage, LOW);
  Serial.println ("interrompu");
 }
           
      else 
{ Serial.println ("rebond");}
      }}
      


void interruption2()
{
  Serial.println("bouton2"); 
   delay(100);
  if (etat_machine == 0)
{ lastDebounceTime = millis(); 
   cafe_long();
  }

else 

{  if ((millis() - lastDebounceTime) > lastDebounceTime1 )
{   lastDebounceTime2 = millis ; 
    etat_machine = 3;
    Serial.println("interruption2");  
     digitalWrite(pompe, LOW);
    digitalWrite(chauffage, LOW);
    Serial.println ("interrompu");
    
   
}}}


void setup()
{
    pinMode(chauffage, OUTPUT); // le chauffage est une sortie
    pinMode(pompe, OUTPUT);
    pinMode(bouton1, INPUT_PULLUP); // le bouton est une entrée
    pinMode(bouton2, INPUT_PULLUP); 
    Serial.begin(9600); 

    etat_machine = 0;
    //etatBouton1 = HIGH; // on initialise l'état du bouton comme "relaché"
    //etatBouton2 = HIGH;
}

void loop()
{ 
    attachInterrupt(0, interruption1, FALLING);
    attachInterrupt(1, interruption2, FALLING);
    if (etat_machine==1)
    { if ((millis() - lastDebounceTime) > debounceDelay)
        {digitalWrite(pompe, LOW);
         digitalWrite(chauffage, LOW);
         Serial.println ("fait cour");
         delay(100);//attendre un petit temps et ne pas remettre imediatement les boutons en marche
          etat_machine=0; 
  }}
  
   if (etat_machine==2)
    { if ((millis() - lastDebounceTime) > debounceDelay1)
        {digitalWrite(pompe, LOW);
         digitalWrite(chauffage, LOW);
         Serial.println ("fait long");
         delay(100);//attendre un petit temps et ne pas remettre imediatement les boutons en marche
          etat_machine=0; 
  }}

  if (etat_machine==3)
    { if ((millis() - lastDebounceTime2) > lastDebounceTime3 )
        { Serial.println ("debloquage");
        etat_machine = 0;
           
  }
  else 
  {Serial.println ("anti rebond interuption");
  
  }}
    
 }   
