//Declaración de variables universales <= esto es un comentario 

#include <rtttl.h>

//RingTone que se va a reproducir
const char song_P[] PROGMEM = "Tetris:d=4,o=5,b=200:e6,8b,8c6,8d6,16e6,16d6,8c6,8b,a,8a,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,2a,8p,d6,8f6,a6,8g6,8f6,e6,8e6,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,a";

ProgmemPlayer player(A0); //Pin Al que está conectado el buzzer (bocina)

//Las siguientes variables son de tipo ENTERO

int led_ardu = 13; //LED integrado en la tarjeta de Arduino, conectado al pin 13
int led = 3; //LED conectado el pin 3

int ledr = 11;
int ledv = 10;
int leda = 9;

int botonI = A2; //Push button conectado al pin A2
int botonD = A3;

int pot = A7;
int foto = A6;

int bocina = A1;

int motorA = 6;
int motorB = 5;

int estado = LOW; //iniciamos con el led apagado
    long anterior = 0; //iniciamos en 0 milisegundos
    long pausa = 1000; // Definimoas la pausa que queremos en milisegundos

//Función para inicializar entradas o salidas del Arduino
void setup(){
  pinMode(led_ardu, OUTPUT); //DECLARO EL PIN 13 COMO SALIDA
  pinMode(led, OUTPUT);//DECLARO EL PIN 3 COMO SALIDA

  pinMode(ledr, OUTPUT);
  pinMode(ledv, OUTPUT);
  pinMode(leda, OUTPUT);
  
  pinMode(botonI, INPUT_PULLUP); //Declaro como ENTRADA el pin A2, además de activar la resistencia pull-up interna del arduino
  pinMode(botonD, INPUT_PULLUP);

  pinMode(pot, INPUT);
  pinMode(foto, INPUT);

  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);

  Serial.begin(9600);// Inicializa comunicación serial

  player.setSong(song_P);
}


/*=========================== PROGRAMA PRINCIPAL ===========================*/

void loop(){

//player.finishSong(); //ejecuta TODA la canción

/*while(player.stepSong()){ // Ejecuta por NOTAS
    parpadeo();
}*/

while(player.pollSong()){
    blink_sin_delay();
  }



}



//========================= DECLARACIÓN DE FUNCIONES =========================//

void parpadeo(){
    int pausa = 20;
    
    digitalWrite(led,HIGH);//El LED se enciende
    delay(pausa); //pausa de 1 segundo
    digitalWrite(led,LOW);//El LED se apaga
    delay(pausa);
}

void blink_sin_delay(){
    
    unsigned long actual = millis(); //esta función regresa los milisegundos desde que enciende el Arduino
     
      if(actual - anterior == pausa) { //Preguntamos si ha pasado el intervalo de tiempo entre cada parpadeo                                
        anterior = actual; //Ahora la variable ANTERIOR toma el valor de la variable ACTUAL  
    
        if (estado == LOW)
          estado = HIGH;// encendemos el LED
        else
          estado = LOW; // Si el led esta prendido lo apaga
      }
        digitalWrite(led, estado);
}

void boton(){
    int estado;

    estado = digitalRead(botonI); //Leemos el valor que entrega la entrada digital y la almacenamos en en la variable estado

        if(estado == 0){ //Preguntamos si el botón se encuetra presionado
            digitalWrite(led, HIGH); // Si el botón está presionado el led se enciende
        }else{
            digitalWrite(led, LOW); //En caso contrario el led permanece apagado
        }
}

void boton2(){ //Realiza la misma tarea que la función anterior (encender un led al presionar un botón)
    int estado = digitalRead(botonD);
    digitalWrite(led, !estado); //negación de la variable estado -> 0 = 1
}

void boton3(){ //Otra forma de resolver la misma tarea (encender un led al presionar un botón)
    int estado = digitalRead(botonI);
        
        if (estado == 0) // No es necesario agregar { } si la condicional EJECUTA UNA SOLA INSTRUCCIÓN
            digitalWrite(led, HIGH); //El LED se enciende si en botón está presionado

        digitalWrite(led, LOW); //El LED se mantiene apagado si no se presiona el botón
}

void hola_mundo(){
    Serial.println("Hola mundo"); //Imprime la frase Hola mundo en el monitor serial de Arduino (botón de la esquina superior derecha)
    delay(1000);
}

void analog_serial(){
    int velocidad = 50;
    int estado = analogRead(foto); //obtenemos los valores que entraga la entrada analógica y los almacenamos en la variable estado
    Serial.println(estado); //Imprimimos los valores que entrega el potenciometro (0 a 1023)
    delay(velocidad);
}

void serial_volt(){
    float estado = analogRead(pot);
    float valor;
    
    valor = (estado * 5.0) / 1023.0; 
    
    Serial.print("Voltaje = ");
    Serial.println(valor);
    delay(10);
}

void voltaje(){
    int x;
    int estado = analogRead(pot);

    x = map (estado, 0, 1023, 0,5);
    Serial.println(x);
    delay(10);
}

void fade(){
    int velocidad = 5; //modificar esta variable para aumentar o disminuir la velocidad con la que enciende y apaga el LED
    
    for(int x = 0; x <= 255; x++){
        analogWrite(led,x);
        delay(velocidad);
    }

    for(int x = 254; x >= 0; x--){
        analogWrite(led,x);
        delay(velocidad);
    }
}

void pot_fade(){ //Controla la intensidad con la que enciende el LED a través del potenciometro
    int x = analogRead(pot);
    int y = map(x,0,1023,0,255);
    analogWrite(led,y);
}

void pot_parpadeo(){ //Controla la velocidad de parpadeo del LED

    int  volt = analogRead(pot);
  
    digitalWrite(led,HIGH);
    delay(volt); 
    digitalWrite(led,LOW);
    delay(volt); 
}

void luz(){
    int x = analogRead(foto);

    if(x <= 45){ //Valor que entrega la fotoresistencia al NO recibir luz
        digitalWrite(led, HIGH);
    }else{
        digitalWrite(led, LOW);
    }
}

void rgb(int red,int green,int blue){ //control de led RGB
    
    analogWrite(ledr, red);
    analogWrite(ledv, green);
    analogWrite(leda, blue);
}

/*ejemplo:
rgb(0, 255, 255);
delay(2000);
rgb(255, 0, 255);
delay(2000);
rgb(255, 255, 0);
delay(2000);
rgb(0, 0, 255);
delay(2000);
rgb(175, 255, 175);
delay(2000);
rgb(255, 0, 0);
delay(2000); 

Puedes encontar el código hexadecimal de colores en el siguiente link:
http://html-color-codes.info/codigos-de-colores-hexadecimales/

ejemplo:
color = #4B0082
rgb(0x4B, 0x00, 0x82);
*/

void fade_rgb(){ // Visualización de colores con LED RGB
    unsigned int LedRGB[3] = {255, 0, 0}; //inicia con el rojo encendido
    int incColor;
    int decColor;

    for (decColor = 0; decColor < 3; decColor += 1) {
    //selecciona dos leds del rgb
    
        if (decColor == 2) {
            incColor = 0;
        } else {
            incColor = decColor +1;
        }
     
    // incrementa un led y decremenata el otro
        for(int i = 0; i < 255; i ++) {
        LedRGB[incColor] += 1;
        LedRGB[decColor] -= 1;
        
        rgb(LedRGB[0], LedRGB[1], LedRGB[2]);
        delay(15);
        }
    }
}

void luz_sonido(){// dependiendo de la cantidad de luz que reciba la fotoresistencia de generara un sonido en la bocina/buzzer

    int sensor = analogRead(foto);
    Serial.println(sensor); //Leemos los valores que entrega la fotoresistencia
    
    // Rango de entrada analógica (min - max desde el fotoresistor)
    // Rango del tono de salida (120 - 1500Hz)
    // Cambiar los valor máximo y minimo de la entrada analógica dependiendo de lo que se vea en el monitor serial
    
    int pitch = map(sensor, 20, 395, 1500, 120);
    
    // reproducir tono
    tone(bocina, pitch, 10); //https://www.arduino.cc/en/Reference/Tone
    delay(1);
}


void motor_avanza(){
    digitalWrite(motorA, LOW);
    digitalWrite(motorB, HIGH); 
}

void motor_retrocede(){
    digitalWrite(motorA, HIGH);
    digitalWrite(motorB, LOW); 
}

void motor_stop(){
    digitalWrite(motorA, LOW);
    digitalWrite(motorB, LOW); 
}

void motor_pwm(){
    
    //Almacenamos el valor del potenciómetro en la variable
    int valorpot=analogRead(pot);
    
    int pwm1 = map(valorpot, 0, 1023, 0, 255);
    int pwm2 = map(valorpot, 0, 1023, 255, 0); //El PWM 2 esta invertido respecto al PWM 1
    
    //Sacamos el PWM de las dos salidas usando analogWrite(pin,valor)
    analogWrite(motorA,pwm1);
    analogWrite(motorB,pwm2);
}