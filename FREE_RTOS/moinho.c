
#include "moinho.h"




// definicao das variaveis
// definicao das variaveis
extern CPU_INT08U motor   = 0,                                        // estado do motor - 1: ligado / 0: desligado
                  emerg   = 0,                                        // var. para monitorar estado de emergem
                  rearme  = 1,                                        // var. para monitorar estado de rearme
                  alerta  = 0;                                        // var. para monitorar estado de alerta - sensores de monitoramento

extern float      tempM = 0,                                          // var. para temperatura do motor
                  tempQ = 0;                                          // var. para temperatura do quadro



void statusMotor(CPU_INT08U op){
    
    if(op){
        ct_motor_Write(LIGA);  // liga contator
        si_liga_Write(LIGA);   // liga sinaleira motor liga
        si_desl_Write(DESL);   // desl sinaleira motor desl
               
    }
    else{
        ct_motor_Write(DESL);   // desl contator
        si_liga_Write(DESL);    // desl sinaleira motor liga
        si_desl_Write(LIGA);    // liga sinaleira motor desl
        
    }
    
}

void statusRearme(CPU_INT08U op){
    
    if(op){
        si_rearme_Write(LIGA);  // liga sinaleira rearme
        rearme = 1;
        
    }
    else{
        si_rearme_Write(DESL);  // desl sinaleira rearme
        rearme = 0;
    }
    
}

void statusEmerg(CPU_INT08U op){
    
    if(op){
        si_emerg_Write(LIGA);   // liga sinaleira emerg
        emerg = 1;
        
    }
    else{        
        si_emerg_Write(DESL);   // desl sinaleira rearme
        emerg = 0;
        
    }
    
}

void statusAlerta(CPU_INT08U op){
    
    if(op){
        si_alerta_Write(LIGA);   // liga sinaleira alerta
        alerta = 1;
        
    }
    else{        
        si_alerta_Write(DESL);   // desl sinaleira alerta
        alerta = 0;
        
    }
    
}
