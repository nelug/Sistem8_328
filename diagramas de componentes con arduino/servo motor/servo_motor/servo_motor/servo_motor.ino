// Controlando la posición de un servo usando un potenciómetro (resistencia variable)
// Por Michal Rinott

#include <Servo.h> // Carga la librería Servo.h que contiene métodos para trabajar con servos

Servo myservo;  // Crea un objeto servo para controlar el servomotor
int potpin = 0; // Pin analógico usado para conectar el potenciómetro
int val;        // variable para leer el valor del pin analógico

void setup()
{
myservo.attach(9); // asocia el servo al pin 9
}

void loop()
{
val = analogRead(potpin);  // lee el valor del potenciómetro (valor
                           //entre 0 y 1023)
val = map(val, 0, 1023, 0, 179);  // escala el valor para usarlo con el
                           //servo (valor entre 0 y 180)
myservo.write(val);        // fija la posición del servo de acuerdo
                           //al valor escalado
delay(15);                 // espera a que el servo se posicione
}
