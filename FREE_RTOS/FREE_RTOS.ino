#include "moinho.h"

TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t App_Task_Ihm_TCB;
TaskHandle_t App_Task_Emerg_TCB;
TaskHandle_t App_Task_Sen_Mec_TCB;
TaskHandle_t App_Task_Sen_Temp_TCB;
TaskHandle_t App_Task_Display_TCB;


// O fio de dados é conectado no pino digital 33 no ESP32
#define ONE_WIRE_BUS 33
 
 


void setup() {
  Serial.begin(9600); 

  // Cria uma tarefa que será executada na função Task1code(), com  prioridade 1 e execução no núcleo 0
  xTaskCreatePinnedToCore(
                    App_Task_Ihm_TCB,   /* Função da tarefa */
                    "IHM_Task",  /* nome da tarefa */
                    10000,       /* Tamanho (bytes) */
                    NULL,        /* parâmetro da tarefa */
                    1,           /* prioridade da tarefa */
                    &App_Task_Ihm,      /* observa a tarefa criada */
                    0);          /* tarefa alocada ao núcleo 0 */                  
  delay(500); 

  // Cria uma tarefa que será executada na função Task2code(), com  prioridade 1 e execução no núcleo 1
  xTaskCreatePinnedToCore(
                    App_Task_Emerg_TCB,   /* Função da tarefa */
                    "Emerg_Task",/* nome da tarefa */
                    10000,       /* Tamanho (bytes) */
                    NULL,        /* parâmetro da tarefa */
                    1,           /* prioridade da tarefa */
                    &App_Task_Emerg,      /* observa a tarefa criada */
                    0);          /* tarefa alocada ao núcleo 1 */
    delay(500); 

  // Cria uma tarefa que será executada na função Task2code(), com  prioridade 1 e execução no núcleo 1
  xTaskCreatePinnedToCore(
                    App_Task_Sen_Mec_TCB,   /* Função da tarefa */
                    "Sen_Mec_Task",/* nome da tarefa */
                    10000,       /* Tamanho (bytes) */
                    NULL,        /* parâmetro da tarefa */
                    1,           /* prioridade da tarefa */
                    &App_Task_Sen_Mec,      /* observa a tarefa criada */
                    0);          /* tarefa alocada ao núcleo 1 */
    delay(500); 

      // Cria uma tarefa que será executada na função Task2code(), com  prioridade 1 e execução no núcleo 1
  xTaskCreatePinnedToCore(
                    App_Task_Sen_Mec_TCB,   /* Função da tarefa */
                    "Sen_Temp_Task",/* nome da tarefa */
                    10000,       /* Tamanho (bytes) */
                    NULL,        /* parâmetro da tarefa */
                    1,           /* prioridade da tarefa */
                    &App_Task_Sen_Temp,      /* observa a tarefa criada */
                    0);          /* tarefa alocada ao núcleo 1 */
    delay(500); 
  
}

//Task1code: Lembrete para beber água
void Task1code( void * pvParameters ){
  for(;;){
    //vTaskDelay(5000/portTICK_PERIOD_MS); // Tempo de espera do lembrete (recomendado: 1800000 (30 min))

    Serial.println(rearme);

    //TaskDelay(5000/portTICK_PERIOD_MS);


  } 
}

//Task2code: Controle do ventilador
void Task2code( void * pvParameters ){
    for(;;){ // Loop infinito
      
  }
}

void loop() {
  
}
