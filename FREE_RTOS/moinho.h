

//#define DEBUG_PSOC
#define DEBUG_ESP32


// constantes
#define LIGA                1u
#define DESL                0u

#define DEBOUNCE            100u                               // tempo de debounce para botoes
#define NTC_B               4275.0                              // constante B do termistor
#define NTC_R0              100000.0                            // R0 = 100k kit grove
#define TEMP_MOTOR_ALERTA   40.0
#define TEMP_QUADRO_ALERTA  40.0




typedef unsigned char CPU_INT08U;
typedef unsigned int CPU_INT16U;



// definicao das variaveis
extern CPU_INT08U motor,                                        // estado do motor - 1: ligado / 0: desligado
                  emerg,                                        // var. para monitorar estado de emergem
                  rearme,                                        // var. para monitorar estado de rearme
                  alerta;                                        // var. para monitorar estado de alerta - sensores de monitoramento

extern float      tempM,                                          // var. para temperatura do motor
                  tempQ;                                          // var. para temperatura do quadro

void statusMotor(CPU_INT08U op);
void statusRearme(CPU_INT08U op);
void statusEmerg(CPU_INT08U op);
void statusAlerta(CPU_INT08U op);
