/*
Restricciones: No se puede usar WiFi porque estos 
pines estan usando para otros propositos en este circuito:
ADC2_CH0 (GPIO 4)
ADC2_CH1 (GPIO 0)
ADC2_CH2 (GPIO 2)
ADC2_CH3 (GPIO 15)
ADC2_CH4 (GPIO 13)
ADC2_CH5 (GPIO 12)
ADC2_CH6 (GPIO 14)
ADC2_CH7 (GPIO 27)
ADC2_CH8 (GPIO 25)
ADC2_CH9 (GPIO 26)

Pines de conexion

ESP32S        Joystick
3.3V          VCC
GND           GND
GPIO 34       VRx
GPIO 35       VRy
GPIO 13       SW

              Buzzer
GPIO 25       VCC
GND           GND

              Touch
GPIO 14       Aluminio

              Motor Stepper X
GPIO 32       step
GPIO 33       dir

              Motor Stepper Y
GPIO 26       step
GPIO 27       dir

              HC-SR04
GPIO 4        Trigger1
GPIO 39       Echo1

GPIO 0        Trigger2
GPIO 36       Echo2

GPIO 2        Trigger3
GPIO 15       Echo3

              Finales de carrera
GPIO 19       switchX
GPIO 18       switchY

              Tira led
GPIO 12       Resistencia de base

              Servo
GPIO 5        Signal
5V            VCC
GND           GND

              LCD I2C
GPIO 21       SDA
GPIO 22       SCL

              ESP32CAM
GPIO 1/17     RX
GPIO 3/16     TX
*/

#include <LiquidCrystal_I2C.h>
#include <Servo.h>

/* Definir pines */
/* Joystick */
const uint8_t xPot = 34;
const uint8_t yPot = 35;
const uint8_t button = 13;

/* Buzzer */
const uint8_t buzzer = 25;

/* Touch */
const uint8_t touch = T6; // GPIO 14

/* Stepper X y Y*/
const uint8_t stepperStepX = 32;
const uint8_t stepperDirX = 33;

const uint8_t stepperStepY = 26;
const uint8_t stepperDirY = 27;

/* Ultrasonicos */
const uint8_t echo1 = 39;
const uint8_t echo2 = 36;
const uint8_t echo3 = 15;
const uint8_t trigger1 = 4;
const uint8_t trigger2 = 0;
const uint8_t trigger3 = 2;

/* Final de carrera */
const uint8_t switchX = 19;
const uint8_t switchY = 18;

/* Tira led */
const uint8_t tiraLed = 23;

/* Servo */
const uint8_t servoPin = 5;

/* Servo */
Servo servo;

/*********************************************************/
/* Definir variables globales */
/* Valores de control joystick ejes X y Y*/
int xVal = 0;
int yVal = 0;
int buttonVal = 0;

/* Valor del touch */
int touchVal = 0;
int touchUmbral = 20;

/* Distancia */
double distancia;

char lectura;

/* Crear objetos */
LiquidCrystal_I2C lcd(0x27, 16, 2);
HardwareSerial serialPort1(2);


/*********************************************************/
/* Configuración */
void setup() {
  /* Definir estradas digitales */
  pinMode(button, INPUT_PULLUP);
  
  pinMode(switchX, INPUT_PULLUP);
  pinMode(switchY, INPUT_PULLUP);
  
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(echo3, INPUT);
  
  /* Definir salidas digitales */
  pinMode(stepperStepX, OUTPUT);
  pinMode(stepperDirX, OUTPUT);

  pinMode(stepperStepY, OUTPUT);
  pinMode(stepperDirY, OUTPUT);

  pinMode(trigger1, OUTPUT);
  pinMode(trigger2, OUTPUT);
  pinMode(trigger3, OUTPUT);

  pinMode(tiraLed, OUTPUT);

  /* Código inicial */
  Serial.begin(115200);
  serialPort1.begin(115200);

  servo.attach(servoPin, 550, 2550);
  
  lcd.init();
  lcd.clear();
  lcd.backlight();

  digitalWrite(stepperStepX, LOW);
  digitalWrite(stepperDirX, LOW);

  digitalWrite(stepperStepY, LOW);
  digitalWrite(stepperDirY, LOW);

  digitalWrite(trigger1, LOW);
  digitalWrite(trigger2, LOW);
  digitalWrite(trigger3, LOW);

  digitalWrite(tiraLed, LOW);

  
}

/*********************************************************/
/* Código principal */
void loop() {
  /******************************************************/
  if(Serial.available() > 0){
    lectura = Serial.read();
    
    if(lectura == 'a'){
    lcd.noBacklight();
    }
  
    if(lectura == 'b') {
      lcd.backlight();
    }
  }

  
  
  distancia = calcularDistancia(trigger1, echo1);
  lcd.setCursor(0, 0);
  lcd.print("Distancia: " + String(distancia));

  delay(500);
  
  /******************************************************/
  /*                Prueba de Touch                     
  touchVal = touchRead(touch);
  if(touchVal <= touchUmbral){
    Serial.println("Umbral alcanzado!");
  }

  else {
    Serial.println("Esperando toque :3");
  }

  delay(100);
  */

  
}

double calcularDistancia(uint8_t trigger, uint8_t echo) {
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  double duracion = pulseIn(echo, HIGH);
  double distancia = (duracion/2)/29;

  return distancia;
}
