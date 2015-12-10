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
float raio = 0.03;
float m_s = 0.0;  //velocidade em m/s
float k_h = 0; //velocidade em km/h
float distancia = 0.0;
int credito=0;
//Mostrar a ordem dos valores enviados para o aplicativo:
int ordem_1 = 1;  
int ordem_2 = 2;
int ordem_3 = 3;
int ordem_4 = 4;

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

     if (tempo_uma_rev>3000) // Se a pessoa não estiver pedalando!!!
     {
       tempo_uma_rev = 0;
       rpm= 0;
       m_s=0;
          }
      
      tempo_total = tempo_total + tempo_uma_rev;  //(tempo_uma_rev/3600000); // tempo em horas
      caloria = 7.0 * 70.0 * tempo_total/3600000;  //calculando caloria
      distancia = (2 * 3.1415 * raio) * voltas; //distancia = numero de voltas x 2*pi*R
      credito = distancia/100;
      
     k_h = m_s *3.6; // transformar velocidade para k/h
      
           
      // Enviar os dados para o aplicativo
      Serial.write(ordem_1); //Identificar a ordem dos dados enviados
      Serial.write((int)k_h);
          
      Serial.write(ordem_2);
      Serial.write((int)distancia);
   
      Serial.write(ordem_3); 
      Serial.write((int)credito);
      
      Serial.write(ordem_4);
      Serial.write((int)caloria);
    } 
    
    else {
      // Se o estado atual é LOW passa de ON para OFF 
      // o tempo anterior agora será o tempo atual
      tempo_anterior = tempo_atual;
    }
  }
  // Guarda o estado atual como ultimo estado
  ultimo_estado_sensor = estado_sensor;
}


