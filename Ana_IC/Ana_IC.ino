#include "stuff.h"

Motores rodasEsquerdas = {4,3, 2};
Motores rodasDireitas = {8,7, 6};

void setup() {
  // motores esquerdos
  pinMode(rodasEsquerdas.potencia, OUTPUT);
  pinMode(rodasEsquerdas.sentidoHorario, OUTPUT);
  pinMode(rodasEsquerdas.sentidoAntiHorario, OUTPUT);
  
  // motores direitos
  pinMode(rodasDireitas.potencia, OUTPUT);
  pinMode(rodasDireitas.sentidoHorario, OUTPUT);
  pinMode(rodasDireitas.sentidoAntiHorario, OUTPUT);

  
  // initialize serial for debugging
  Serial.begin(9600);
  while (!Serial) {
    /*** Aguardando o estabelecimento da conexão ***/
  }
  
}

void loop() {
    if(Serial.available()) {
      char leitura = Serial.read();
      Serial.print(leitura);

      if(leitura == 'F'){ 
        Serial.println("EM_FRENTE");
        //F-(Forward)=(direito=horario && esquerdo=anti-horario) 
        girar(rodasDireitas, SENTIDO_HORARIO);
        girar(rodasEsquerdas, SENTIDO_ANTI_HORARIO);
      
      }else if(leitura == 'T'){
        Serial.println("PARA_TRAS");
        //B-(Backward)=(direito=anti-horario && esquerdo=horario)
        girar(rodasDireitas, SENTIDO_ANTI_HORARIO);
        girar(rodasEsquerdas, SENTIDO_HORARIO);
    
        
      }else if(leitura == 'E'){
        Serial.println("GIRAR_ESQUERDA");
        //L-(Left)=(direito=anti-horario && esquerdo=anti-horario)  
        girar(rodasDireitas, SENTIDO_ANTI_HORARIO);
        girar(rodasEsquerdas, SENTIDO_ANTI_HORARIO);
        
      }else if(leitura == 'D'){ 
        Serial.println("GIRAR_DIREITA");
        //L-(Left)=(direito=anti-horario && esquerdo=anti-horario)  
        girar(rodasDireitas, SENTIDO_HORARIO);
        girar(rodasEsquerdas, SENTIDO_ANTI_HORARIO);
        
      }

      delay(200);
    }
    
    desligaMotores(rodasEsquerdas);
    desligaMotores(rodasDireitas);   
    
}

void girar(struct Motores motores, String sentido){
  if(motores.potencia != 0)
    analogWrite(motores.potencia, POTENCIA_ROTACAO);
  //verifica para qual sentido é ara girar o motor
  if(sentido == SENTIDO_HORARIO){ 
    digitalWrite(motores.sentidoHorario, HIGH);
    digitalWrite(motores.sentidoAntiHorario, LOW);
  }else{
    digitalWrite(motores.sentidoHorario, LOW);
    digitalWrite(motores.sentidoAntiHorario, HIGH);
  }
}

void desligaMotores(struct Motores motores){
  digitalWrite(motores.sentidoHorario, LOW);
  digitalWrite(motores.sentidoAntiHorario, LOW);
}
