#include <Keypad.h> // Libreria para el teclado
#include <LiquidCrystal.h> // Libreria para el LCD

const int rs = A5, en = A4, d4 = A3, d5 = A2, d6 = A1, d7 = A0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const byte Filas = 4;
const byte Columnas = 3;
char Teclas [Filas][Columnas] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte FilasPin[Filas] = {6,7,8,9}; // Pines a los que estan conectadas las filas
byte ColumnasPin[Columnas] = {10,11,12}; // Pines a los que estan conectadas las columnas
Keypad keypad = Keypad(makeKeymap (Teclas), FilasPin, ColumnasPin, Filas, Columnas);

char puls = keypad.getKey();
int i = 0;
int Periodo = 1000;
int Espera = 20000;
unsigned long TiempoAhora = 0;
const int LEDrojo = 4;
const int LEDverde = 3;
const int Inter = 2;
byte InterState = 0;
char contrasena[] = "7532";  // Aquí escribimos la contraseña de 4 dígitos
char codigo[4];            // Cadena donde se guardaran los caracteres de las teclas presionadas
int cont=0;          // variable que se incrementara al presionar las teclas

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);  // Tamaño de la LCD
  pinMode(LEDrojo , OUTPUT);  // Definimos LED como salida
  pinMode(LEDverde , OUTPUT);  // Definimos LED como salida
  pinMode(Inter, INPUT); // Definimos Interruptor como entrada

  lcd.clear();
}

void loop() {

    InterState = digitalRead(Inter);
    char puls = keypad.getKey();
    
   switch (i){
    
   case 0: // Cuando se va a abrir
   
   if (InterState == HIGH){
    if (millis() > TiempoAhora + Periodo){
     TiempoAhora = millis();
     lcd.setCursor(0,0);
     lcd.print("Ingrese  clave");}
   } 
   if (InterState == LOW){
    if (millis() > TiempoAhora + Periodo){
     TiempoAhora = millis();
     lcd.setCursor(0,0);
     lcd.print("Sistema seguro");}
   }
   
    //if (millis() > TiempoAhora + Espera){
     if (puls != NO_KEY){        // Evalúa si se presionó una tecla
      codigo[cont] = puls;          // Guarda caracter por caracter en el arreglo codigo[]
      lcd.setCursor(cont+5,1);
      lcd.println("*");    // Imprime * por cada tecla presionada
      cont = cont + 1;              // Incrementamos la variable cont
        if(cont == 4 ){          // Si ya fueron presionadas 4 teclas  se evalúa si la contraseña es correcta
          if(codigo[0] == contrasena[0] && codigo[1] == contrasena[1] && codigo[2] == contrasena[2] && codigo[3] == contrasena[3]){
          lcd.clear();
          digitalWrite(3,HIGH);        // Si la contraseña es correcta se enciende el led verde
          delay(500);
          lcd.setCursor(0,0);
          lcd.print("BIENVENIDO");
          delay(1000);
          lcd.clear();
          digitalWrite(3,LOW);}
          else {
            lcd.clear();
            digitalWrite(4,HIGH);        // Si la contraseña es incorrecta se enciende led rojo
            delay(500);
            lcd.setCursor(0,0);
            lcd.print("INTRUSO");
            delay(1000);
            lcd.clear();
            digitalWrite(4,LOW);
            }
        cont=0;  // Resetear a 0 la variable cont
         }
      }
    //}
 
      break;
     
   case 1:  // Cuando se va a cerrar
    
    if (digitalRead(2)==1){
     lcd.setCursor(0,0);
     lcd.print("Ingrese clave");
   }
    char puls = keypad.getKey();
    //if (millis() > TiempoAhora + Espera){
     if (puls != NO_KEY){        // Evalúa si se presionó una tecla
      codigo[cont] = puls;          // Guarda caracter por caracter en el arreglo codigo[]
      lcd.setCursor(0,1);
      lcd.println("*");    // Imprime * por cada tecla presionada
      cont = cont + 1;              // Incrementamos la variable cont
        if(cont == 4 ){          // Si ya fueron presionadas 4 teclas  se evalúa si la contraseña es correcta
          if(codigo[0] == contrasena[0] && codigo[1] == contrasena[1] && codigo[2] == contrasena[2] && codigo[3] == contrasena[3]){
            lcd.setCursor(0,0);
            lcd.print("Sistema seguro");    // Si la contraseña es correcta sale este mensaje
            lcd.clear();}
          while(codigo != "7532") {
            lcd.setCursor(0,0);
            lcd.print("Ingrese clave");
            }
        cont=0;  // Resetear a 0 la variable cont
         }
      }
    //}
    
    break;
  }
}
