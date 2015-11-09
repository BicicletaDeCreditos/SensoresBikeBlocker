#include <SoftwareSerial.h>  
  
SoftwareSerial mySerial(1, 0); // RX, TX  



const int  SensorReedPin = 2;  
int voltas = 0;
int estado_sensor = 0;         
int ultimo_estado_sensor = 0;   
long tempo_anterior = 0;
long tempo_uma_rev = 0;
unsigned long tempo_atual;
long rpm;
float caloria = 0.0;
float tempo_total;
//float raio = 10;
float raio = 0.03;
float m_s = 0.0;  //velocidade em m/s
float distancia = 0.0;
int credito=0;

void setup() 
{
  pinMode(SensorReedPin, INPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  // Lê o estado do sensor
  estado_sensor = digitalRead(SensorReedPin);
  // Compara o estado do sensor com o estado anterior
  if (estado_sensor != ultimo_estado_sensor) {
    // Se o estado foi alterado, incrementa o contador
    if (estado_sensor == HIGH) 
    {
      voltas++;
      tempo_atual =millis(); //obtem o tempo atual
      tempo_uma_rev = tempo_atual - tempo_anterior; //tempo de uma revolucao 

    
      
      rpm = 60000 / tempo_uma_rev; // 1 minuto = 60000 ms
      m_s = raio * rpm * 0.10472;  //convertendo rpm para m/s

     if (tempo_uma_rev>3000)
     {
       tempo_uma_rev = 0;
       rpm= 0;
       m_s=0;
      //   Serial.println("Pessoa nao esta pedalando!!!!"); 
     }
      
      tempo_total = tempo_total + tempo_uma_rev;  //(tempo_uma_rev/3600000); // tempo em horas
     // if (tempo_uma_rev < 500) // se demorar mais que meio segundo para completar a volta 
     // {
     // tempo_total = tempo_total + tempo_uma_rev;  //(tempo_uma_rev/3600000); // tempo em horas
     // }
     
    
      caloria = 7.0 * 70.0 * tempo_total/3600000;  //calculando caloria
      distancia = (2 * 3.1415 * raio) * voltas; //distancia = numero de voltas x 2*pi*R
      credito = distancia/100;
      //mostra dados calculados na tela
      Serial.println("Sensor ON");  
      Serial.print("voltas: ");
      Serial.println(voltas);
      Serial.print("Tempo por revolucao: ");
      Serial.println(tempo_uma_rev);
      Serial.print("Revolucao por minuto: ");
      Serial.println(rpm);
      Serial.print("Velocidade em m/s: ");
      Serial.println(m_s);
      Serial.print("Distancia em metros: ");
      Serial.println(distancia);
      Serial.print("Creditos: ");
      Serial.println(credito);
      Serial.print("Caloria em kcal: ");
      Serial.println(caloria);
    } 
    else {
      // Se o estado atual é LOW passa de ON para OFF 
      Serial.println("Sensor OFF"); 
      // o tempo anterior agora será o tempo atual
      tempo_anterior = tempo_atual;
    }
  }
  // Guarda o estado atual como ultimo estado
  ultimo_estado_sensor = estado_sensor;

}


