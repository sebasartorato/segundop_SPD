#include <LiquidCrystal.h> // Para el LCD
#include <IRremote.h> // Para el Control IR
#include <Servo.h>

#define SENSOR_TEMPERATURA A0
#define LED_1 12
#define LED_2 13 
#define CONTROL_IR 11
#define SERVOMOTOR 9
#define limiteTemperatura 50 

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); 
IRrecv irRecibidor(CONTROL_IR);
decode_results irDato; 
Servo servoMotor; 

int temperatura; 
bool estado = false;
String estacion; 

void setup()
{
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);

  int temperaturaLeida = analogRead(SENSOR_TEMPERATURA); // Recibe un valor de 0 a 1023
  // Mapea el ese valor a un rango de -40 a 125, que son los limites del sensor de temperatura
  temperatura = map(temperaturaLeida, 20, 350, -40, 125); 

  lcd.begin(16, 2); // Inicializa el LCD con 16 columnas y 2 filas
  servoMotor.attach(SERVOMOTOR); // Inicializa el ServoMotor
  irRecibidor.begin(CONTROL_IR, DISABLE_LED_FEEDBACK); // Inicializa el Control IR
}

void loop()
{
  controlRemotoIR(); // Controla el sistema con el control remoto  
  estacionAnio(temperatura); // Indica la estacion del año segun la temperatura

  if (estado ) 
  {
    alarmaIncendio(temperatura);
    imprimirTemperatura(temperatura);
  } 
  else 
  {
    lcd.clear();
  }
}

void controlRemotoIR()
{
  if (irRecibidor.decode()) {
    switch (irRecibidor.decodedIRData.decodedRawData) {
      case 0xFF00BF00: // Boton de encendido
        estado = !estado;

        break;

      case 0xF50ABF00: //Boton de subir (y prendo primer led)
        temperatura += 5;
      	prendeApagaLed(LED_1, LED_2);
        break;

      case 0xF708BF00: //Boton de Bajar (y prendo segundo led)
        temperatura -= 5;
      	prendeApagaLed(LED_2, LED_1);
        break;

      default:
        break;
    }
    irRecibidor.resume(); // Recibe el siguiente dato
  }
  delay(100); // Evitar rebotes
}

void estacionAnio(int temp)
{
  if (temp >= 25 && temp <= limiteTemperatura){
    estacion = "Verano";
  } else if (temp >= 18 and temp < 25){
    estacion = "Primavera";
  } else if (temp >= 13 and temp < 17){
    estacion = "Otonio";
  } else if (temp >= -5 and temp < 13){
    estacion = "Invierno";
  }
  else {
    estacion = "";
  }
}

void imprimirTemperatura(int temp)// Funcion que imprime la temperatura y la estación del año en el LCD.
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print(estacion);
  delay(600);
}

void prendeApagaLed(int led_1, int led_2) // Función que enciende un LED y apaga el otro.
{
  digitalWrite(led_1, HIGH);
  digitalWrite(led_2, LOW);
}

void encenderServo(int tiempo)// Funcion que enciende el servo motor
{
  servoMotor.write(90); // Gira el servo motor 90 grados 
  delay(tiempo);
  servoMotor.write(0); // Gira el servo motor a su posicion inicial
  delay(tiempo);
}


void alarmaIncendio(int temp)//Funcion que activa el mecanismo en caso de sobrepasar la temperatura limite
{
  if (temp >= limiteTemperatura) {
    lcd.clear();
    lcd.print("I N C E N D I O");
	titilarLeds(LED_1, LED_2);
    encenderServo(600);
  }
}

void titilarLeds (int led_1, int led_2) //Funcion que titila los Leds una vez que hay incendio
{
    digitalWrite(led_1, HIGH);
  	digitalWrite(led_2, HIGH);
  	delay(200);
  	digitalWrite(led_1, LOW);
  	digitalWrite(led_2, LOW);
}
