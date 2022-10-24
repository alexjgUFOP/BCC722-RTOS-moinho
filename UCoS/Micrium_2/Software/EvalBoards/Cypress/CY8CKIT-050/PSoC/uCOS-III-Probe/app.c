/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                             (c) Copyright 2012; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                           EXAMPLE CODE
*
*                                           CYPRESS PSoC5
*                                              with the
*                                     CY8CKIT-050 Development Kit
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : DC
                  
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <includes.h>
#include <project.h>                /* incluindo api do psoc */
//#include <math.h>                   // biblioteca matematica padrao do C - para calc de temperatura

//////////////// comentario teste - apagar
//////////////// outro comentario de teste
/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/

#define  APP_USER_IF_SIGN_ON                        0u
#define  APP_USER_IF_VER_TICK_RATE                  1u
#define  APP_USER_IF_CPU                            2u
#define  APP_USER_IF_CTXSW                          3u
#define  APP_USER_IF_STATE_MAX                      4u

#define LIGA                1u
#define DESL                0u

#define DEBOUNCE            100u                               // tempo de debounce para botoes
#define NTC_B               4275.0                              // constante B do termistor
#define NTC_R0              100000.0                            // R0 = 100k kit grove
#define TEMP_MOTOR_ALERTA   40.0
#define TEMP_QUADRO_ALERTA  40.0


/*
*********************************************************************************************************
*                                            LOCAL VARIABLES
*********************************************************************************************************
*/

static  OS_TCB      App_TaskStartTCB;
static  CPU_STK     App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE];

static  OS_TCB      App_TaskUserIF_TCB;
static  CPU_STK     App_TaskUserIFStk[APP_CFG_TASK_USER_IF_STK_SIZE];

                                                                        // criando as estruras do TCB e STK da task                                       
static  OS_TCB      App_Task_Ihm_TCB;
static  CPU_STK     App_Task_Ihm_Stk[APP_CFG_TASK_IHM_STK_SIZE];

                                                                        // criando as estruras do TCB e STK da task                                       
static  OS_TCB      App_Task_Emerg_TCB;
static  CPU_STK     App_Task_Emerg_Stk[APP_CFG_TASK_EMERG_STK_SIZE];

                                                                        // criando as estruras do TCB e STK da task                                       
static  OS_TCB      App_Task_Sen_Mec_TCB;
static  CPU_STK     App_Task_Sen_Mec_Stk[APP_CFG_TASK_SEN_MEC_STK_SIZE];

                                                                        // criando as estruras do TCB e STK da task                                       
static  OS_TCB      App_Task_Sen_Temp_TCB;
static  CPU_STK     App_Task_Sen_Temp_Stk[APP_CFG_TASK_SEN_TEMP_STK_SIZE];

                                                                        // criando as estruras do TCB e STK da task                                       
static  OS_TCB      App_Task_Display_TCB;
static  CPU_STK     App_Task_Display_Stk[APP_CFG_TASK_DISPLAY_STK_SIZE];


        CPU_INT08U  motor   = 0,                                        // estado do motor - 1: ligado / 0: desligado
                    emerg   = 0,                                        // var. para monitorar estado de emergem
                    rearme  = 1,                                        // var. para monitorar estado de rearme
                    alerta  = 0;                                        // var. para monitorar estado de alerta - sensores de monitoramento
                    

        float       tempM = 0,                                          // var. para temperatura do motor
                    tempQ = 0;                                          // var. para temperatura do quadro

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  App_TaskStart  (void *p_arg);

static  void  App_TaskUserIF (void *p_arg);

static  void  App_TaskCreate (void);
static  void  App_ObjCreate  (void);

static  void  App_Task_Ihm      (void *p_arg);             /* prototipo da funcao que define a task de ihm */
static  void  App_Task_Emerg    (void *p_arg);             /* prototipo da funcao que define a task de emerg*/
static  void  App_Task_Sen_Mec  (void *p_arg);             /* prototipo da funcao que define a task de sen. prot. mec. */
static  void  App_Task_Sen_Temp (void *p_arg);             /* prototipo da funcao que define a task de sen. temp. */
static  void  App_Task_Display  (void *p_arg);             /* prototipo da funcao que define a task de sem. display */

        void  statusMotor    (CPU_INT08U op);
        void  statusRearme   (CPU_INT08U op);
        void  statusEmerg    (CPU_INT08U op);
        void  statusAlerta   (CPU_INT08U op);

        
/*
*********************************************************************************************************
*                                         ISR HANDLERS
*********************************************************************************************************
*/

CY_ISR(se_indut_porta_Handler){                     // implementando rotina de tratamento de interrupção  - interrupt handler 
    
     // tratando debounce do botão
    OSTimeDly(DEBOUNCE,OS_ERR_TIME_DLY_ISR, NULL);
    
                                                    // trata sens. indut da protecao mec. da porta
    statusMotor(DESL);
    statusRearme(LIGA);
    statusAlerta(LIGA);
        
    se_indut_porta_ClearInterrupt();                // limpa flag de interrupçao
    
    
}

CY_ISR(se_indut_motor_Handler){                     // implementando rotina de tratamento de interrupção  - interrupt handler 
  
    // tratando debounce do botão
    OSTimeDly(DEBOUNCE,OS_ERR_TIME_DLY_ISR, NULL);
    
                                                    // trata sens. indut da protecao mec. do motor
    statusMotor(DESL);
    statusRearme(LIGA);
    statusAlerta(LIGA);
    
    se_indut_motor_ClearInterrupt();                // limpa flag de interrupçao
    
}

CY_ISR(bt_emerg_int_Handler){                       // implementando rotina de tratamento de interrupção  - interrupt handler 
    
    
                                                    // tratando debounce do botão
    OSTimeDly(200,OS_ERR_TIME_DLY_ISR, NULL);
    statusMotor(DESL);
    statusRearme(LIGA);
    statusEmerg(LIGA);

    bt_emerg_ClearInterrupt();                      // limpa flag de interrupçao
    
}

 

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : Startup Code.
*
* Note(s)     : none.
*********************************************************************************************************
*/

int  main (void)
{
    

    se_indut_porta_int_StartEx(se_indut_porta_Handler);         // habilita ISR do pino
    se_indut_motor_int_StartEx(se_indut_motor_Handler);         // habilita ISR do pino
    bt_emerg_int_StartEx(bt_emerg_int_Handler);                 // habilita ISR do pino
    
    OS_ERR  os_err;


    BSP_PreInit();                                              /* Perform BSP pre-initialization.                      */

    CPU_Init();                                                 /* Initialize the uC/CPU services                       */

    OSInit(&os_err);                                            /* Init uC/OS-III.                                      */

    OSTaskCreate((OS_TCB      *)&App_TaskStartTCB,              /* Create the start task                                */
                 (CPU_CHAR    *)"Start",
                 (OS_TASK_PTR  )App_TaskStart, 
                 (void        *)0,
                 (OS_PRIO      )APP_CFG_TASK_START_PRIO,
                 (CPU_STK     *)&App_TaskStartStk[0],
                 (CPU_STK_SIZE )APP_CFG_TASK_START_STK_SIZE_LIMIT,
                 (CPU_STK_SIZE )APP_CFG_TASK_START_STK_SIZE,
                 (OS_MSG_QTY   )0u,
                 (OS_TICK      )0u,
                 (void        *)0,
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR      *)&os_err);

    OSStart(&os_err);                                            /* Start multitasking (i.e. give control to uC/OS-III).  */
    
    
    
}


/*
*********************************************************************************************************
*                                          App_TaskStart()
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Argument(s) : p_arg   is the argument passed to 'App_TaskStart()' by 'OSTaskCreate()'.
*
* Return(s)   : none
*
* Note(s)     : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  App_TaskStart (void *p_arg)
{
    OS_ERR       err;
        

   (void)p_arg;
   

    BSP_PostInit();                                               /* Perform BSP post-initialization functions.       */
    
    BSP_CPU_TickInit();                                           /* Perfrom Tick Initialization                      */

#if (OS_CFG_STAT_TASK_EN > 0u)
    OSStatTaskCPUUsageInit(&err);
#endif    

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif      

    App_TaskCreate();                                             /* Create application tasks.                        */

    App_ObjCreate();                                              /* Create kernel objects                            */
    
#if (APP_CFG_PROBE_COM_EN == DEF_ENABLED)
    App_ProbeInit();                                              /* Enabling uC/Probe                                */
#endif
    
    BSP_LED_Off(1);

    while (DEF_TRUE) {                                            /* Task body, always written as an infinite loop.   */
        BSP_LED_Toggle(1);
        OSTimeDlyHMSM(0, 0, 0, 100, 
                      OS_OPT_TIME_HMSM_STRICT, 
                      &err);
    }
}


/*
*********************************************************************************************************
*                                          App_TaskCreate()
*
* Description : Create application tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  App_TaskCreate (void)
{

    OS_ERR  os_err;

    /*
    OSTaskCreate((OS_TCB      *)&App_TaskUserIF_TCB,
                 (CPU_CHAR    *)"Start",
                 (OS_TASK_PTR  )App_TaskUserIF, 
                 (void        *)0,
                 (OS_PRIO      )APP_CFG_TASK_USER_IF_PRIO,
                 (CPU_STK     *)&App_TaskUserIFStk[0],
                 (CPU_STK_SIZE )APP_CFG_TASK_USER_IF_STK_SIZE_LIMIT,
                 (CPU_STK_SIZE )APP_CFG_TASK_USER_IF_STK_SIZE,
                 (OS_MSG_QTY   )0u,
                 (OS_TICK      )0u,
                 (void        *)0,
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR      *)&os_err);
    */
    
    // ======== task IHM  ========
    OSTaskCreate((OS_TCB      *)&App_Task_Ihm_TCB,                              // endereço da task para OS_TCB
                 (CPU_CHAR    *)"IHM_Task",                                     // string com nome da task
                 (OS_TASK_PTR  )App_Task_Ihm,                                   // endereco da funcao sem. veiculo 01 que define comportamento da task
                 (void        *)0,                                              // parametros passados na criacao - sem nenhum valor passado
                 (OS_PRIO      )APP_CFG_TASK_IHM_PRIO,                          // prioridade de execucao da task
                 (CPU_STK     *)&App_Task_Ihm_Stk[0],                           // endereco base da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_IHM_STK_SIZE_LIMIT,                // endereco final da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_IHM_STK_SIZE,                      // tamanho da pilha
                 (OS_MSG_QTY   )0u,                                             // task incapaz de receber mensagens
                 (OS_TICK      )0u,                                             // clock tick default
                 (void        *)0,                                              // sem endereço de memoria local passado
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),    // opcoes especificas da tarefa escolhas - verificacao se pilha pode ser acessada e se precisa ser limpa
                 (OS_ERR      *)&os_err);                                       // ponteiro com erros durante create
 
    // ======== task Emergencia  ========
    OSTaskCreate((OS_TCB      *)&App_Task_Emerg_TCB,                            // endereço da task para OS_TCB
                 (CPU_CHAR    *)"Emerg_Task",                                   // string com nome da task
                 (OS_TASK_PTR  )App_Task_Emerg,                                 // endereco da funcao sem. veiculo 01 que define comportamento da task
                 (void        *)0,                                              // parametros passados na criacao - sem nenhum valor passado
                 (OS_PRIO      )APP_CFG_TASK_EMERG_PRIO,                        // prioridade de execucao da task
                 (CPU_STK     *)&App_Task_Emerg_Stk[0],                         // endereco base da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_EMERG_STK_SIZE_LIMIT,              // endereco final da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_EMERG_STK_SIZE,                    // tamanho da pilha
                 (OS_MSG_QTY   )0u,                                             // task incapaz de receber mensagens
                 (OS_TICK      )0u,                                             // clock tick default
                 (void        *)0,                                              // sem endereço de memoria local passado
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),    // opcoes especificas da tarefa escolhas - verificacao se pilha pode ser acessada e se precisa ser limpa
                 (OS_ERR      *)&os_err);                                       // ponteiro com erros durante create

    // ======== task sen. mec.  ========
    OSTaskCreate((OS_TCB      *)&App_Task_Sen_Mec_TCB,                          // endereço da task para OS_TCB
                 (CPU_CHAR    *)"Sen_Mec_Task",                                 // string com nome da task
                 (OS_TASK_PTR  )App_Task_Sen_Mec,                               // endereco da funcao sem. veiculo 01 que define comportamento da task
                 (void        *)0,                                              // parametros passados na criacao - sem nenhum valor passado
                 (OS_PRIO      )APP_CFG_TASK_SEN_MEC_PRIO,                      // prioridade de execucao da task
                 (CPU_STK     *)&App_Task_Sen_Mec_Stk[0],                       // endereco base da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_SEN_MEC_STK_SIZE_LIMIT,            // endereco final da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_SEN_MEC_STK_SIZE,                  // tamanho da pilha
                 (OS_MSG_QTY   )0u,                                             // task incapaz de receber mensagens
                 (OS_TICK      )0u,                                             // clock tick default
                 (void        *)0,                                              // sem endereço de memoria local passado
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),    // opcoes especificas da tarefa escolhas - verificacao se pilha pode ser acessada e se precisa ser limpa
                 (OS_ERR      *)&os_err);                                       // ponteiro com erros durante create
    
    // ======== task sen. temp.  ========
    OSTaskCreate((OS_TCB      *)&App_Task_Sen_Mec_TCB,                          // endereço da task para OS_TCB
                 (CPU_CHAR    *)"Sen_Temp_Task",                                // string com nome da task
                 (OS_TASK_PTR  )App_Task_Sen_Temp,                              // endereco da funcao sem. veiculo 01 que define comportamento da task
                 (void        *)0,                                              // parametros passados na criacao - sem nenhum valor passado
                 (OS_PRIO      )APP_CFG_TASK_SEN_TEMP_PRIO,                     // prioridade de execucao da task
                 (CPU_STK     *)&App_Task_Sen_Temp_Stk[0],                      // endereco base da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_SEN_TEMP_STK_SIZE_LIMIT,           // endereco final da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_SEN_TEMP_STK_SIZE,                 // tamanho da pilha
                 (OS_MSG_QTY   )0u,                                             // task incapaz de receber mensagens
                 (OS_TICK      )0u,                                             // clock tick default
                 (void        *)0,                                              // sem endereço de memoria local passado
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),    // opcoes especificas da tarefa escolhas - verificacao se pilha pode ser acessada e se precisa ser limpa
                 (OS_ERR      *)&os_err);                                       // ponteiro com erros durante create
    
    
    // ======== task diz play  ========
    OSTaskCreate((OS_TCB      *)&App_Task_Display_TCB,                          // endereço da task para OS_TCB
                 (CPU_CHAR    *)"Display_Task",                                 // string com nome da task
                 (OS_TASK_PTR  )App_TaskUserIF,                                 // endereco da funcao sem. veiculo 01 que define comportamento da task
                 (void        *)0,                                              // parametros passados na criacao - sem nenhum valor passado
                 (OS_PRIO      )APP_CFG_TASK_DISPLAY_PRIO,                      // prioridade de execucao da task
                 (CPU_STK     *)&App_Task_Display_Stk[0],                       // endereco base da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_DISPLAY_STK_SIZE_LIMIT,            // endereco final da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_DISPLAY_STK_SIZE,                  // tamanho da pilha
                 (OS_MSG_QTY   )0u,                                             // task incapaz de receber mensagens
                 (OS_TICK      )0u,                                             // clock tick default
                 (void        *)0,                                              // sem endereço de memoria local passado
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),    // opcoes especificas da tarefa escolhas - verificacao se pilha pode ser acessada e se precisa ser limpa
                 (OS_ERR      *)&os_err);                                       // ponteiro com erros durante create
    
}

static  void  App_Task_Ihm(void *p_arg)
{
    
    OS_ERR          err;                                /* var com os erros do processo */
             
   (void)p_arg;

    while(DEF_ON){
        
                
        if((!bt_liga_Read()) && (!emerg) && (!rearme) && (!alerta)){   // botoeira liga pressionada    
            statusMotor(LIGA);
        }
        
        if(!bt_desl_Read()){                                            // botoeira desliga pressionada
            statusMotor(DESL);
        }
                
        if(!bt_rearme_Read() && (!emerg) && (!rearme) && (!alerta)){    // remocao de rearme se nao cond. adver. / alerta e emerg. ativos   
            statusRearme(DESL);
        }
                               
    }
    
}

static  void  App_Task_Emerg(void *p_arg)
{
    
    OS_ERR          err;                                    /* var com os erros do processo */
         
   (void)p_arg;


    while(DEF_ON){                                          // tratamento de ocorrencia de emergencia
        
        if(bt_emerg_Read()){                                // se o botao foi liberado libera a emergencia
            statusEmerg(DESL);
        }
        
    }
    
}

static  void  App_Task_Sen_Mec(void *p_arg)
{
    
      
    OS_ERR          err;                                            /* var com os erros do processo */
    
   (void)p_arg;

    while(DEF_ON){
            
                                                                    // tratamento de ocorrencia de alerta
        
        if((!se_indut_porta_Read()) || (!se_indut_motor_Read())){   // se sensores de alerta corrigidos
            statusAlerta(DESL);
    
    }
}

static  void  App_Task_Sen_Temp(void *p_arg)
{
     
    OS_ERR          err;                                    // var com os erros do processo 
    CPU_INT08U      tAltaMotor  = TEMP_MOTOR_ALERTA;        // variavel referencia para teste de logica da temperatura
    CPU_INT08U      tAltaQuadro = TEMP_QUADRO_ALERTA;       // variavel referencia para teste de logica da temperatura
    CPU_INT16U      temp1 = 0,                              // var aux com bits da temp. do adc
                    temp2 = 0;                       
    float           R1 = 0, R2 = 0;                         // resistencia em bits 
    
    
   (void)p_arg;

    //Math_Init();
    ADC_SAR_Seq_Start();
    
    // StartConvert() must be called to initiate 
    //   conversion in Free Running Mode
    
    ADC_SAR_Seq_StartConvert();

    while(DEF_ON){
        
        ADC_SAR_Seq_IsEndConversion(ADC_SAR_Seq_WAIT_FOR_RESULT);
        
        // utilizando NTC's do kit Grove
        
        temp1 = ADC_SAR_Seq_GetResult16(0u);
        temp2 = ADC_SAR_Seq_GetResult16(1u);
        
        R1 = (4095.0/temp1)-1.0; // resistencia lida
        R2 = (4095.0/temp2)-1.0; // resistencia lida
        
        R1 = NTC_R0*R1;
        R2 = NTC_R0*R2;
        
        tempM = 1.0/(log(R1/NTC_R0)/NTC_B+1/298.15) -273.15; // convert to temperature via datasheet
        tempQ = 1.0/(log(R2/NTC_R0)/NTC_B+1/298.15) -273.15; // convert to temperature via datasheet
        
        OSTimeDly(100, OS_OPT_TIME_DLY, &err);
        
        if(bt_test_Read()){
            OSTimeDly(100, OS_OPT_TIME_DLY, &err);          // debounce botao de teste
            tAltaMotor  = 10;                               // variavel referencia para teste de logica da temperatura
            tAltaQuadro = 10;     
                        
        }
        else{
            tAltaMotor  = TEMP_MOTOR_ALERTA;                // variavel referencia para teste de logica da temperatura
            tAltaQuadro = TEMP_QUADRO_ALERTA;     
            
        }
            
        
        if(tempM > tAltaMotor || tAltaQuadro){
            statusAlerta(LIGA);
            statusRearme(LIGA);
        }
        else{
            statusAlerta(DESL);
        }
                
        // fonte: https://wiki.seeedstudio.com/Grove-Temperature_Sensor_V1.2/
        // log: adicionando "Libm.a" no projeto https://community.infineon.com/t5/PSoC-Creator-Designer/Using-Thermistor-but-pow-and-log-functions-inaccessible/m-p/228391#M12773
    
    }
     
}

static  void  App_Task_Display (void *p_arg)
{
    CPU_INT32U   val;
    OS_ERR       os_err;
    CPU_CHAR     line_str[17];


    (void)p_arg;
   
    LCD_Disp_Start();                                       /* Initialize the LCD screen.                       */
   
    while(DEF_ON){
        
        LCD_Disp_Position(0u, 0u);                          // limpa o display
        LCD_Disp_PrintString((char *)"                ");
        LCD_Disp_Position(1u, 0u);
        LCD_Disp_PrintString((char *)"                ");
        
                                                            // imprime temperatura do quadro                 
        LCD_Disp_Position(0u, 0u); 
        LCD_Disp_PrintString((char *)"TEMP QUADRO     ");
        sprintf((char *)line_str,"%.2f",tempQ);
        LCD_Disp_PrintString((char *)line_str);
        
                                                            // imprime temperatura do motor
        LCD_Disp_Position(1u, 0u);
        LCD_Disp_PrintString((char *)"TEMP MOTOR      ");
        sprintf((char *)line_str,"%.2f",tempM);
        LCD_Disp_PrintString((char *)line_str);
        
        OSTimeDlyHMSM(0, 0, 0, 100, 
                      OS_OPT_TIME_HMSM_STRICT, 
                      &os_err);

    }
}


/*
*********************************************************************************************************
*                                          App_ObjCreate()
*
* Description : Create application kernel objects tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  App_ObjCreate (void)
{

}


/*
*********************************************************************************************************
*                                          App_TaskUserIF()
*
* Description : User interface task
*
* Argument(s) : p_arg   is the argument passed to 'App_TaskUserIF()' by 'OSTaskCreate()'.
*
* Return(s)   : none
*
* Note(s)     : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/


static  void  App_TaskUserIF (void *p_arg)
{
   CPU_INT32U   val;
   CPU_INT08U   user_if_state_cur;
   CPU_INT08U   user_if_state_prev;   
   CPU_BOOLEAN  pb2_state_cur;
   CPU_BOOLEAN  pb2_state_prev;
   CPU_BOOLEAN  pb3_state_cur;
   CPU_BOOLEAN  pb3_state_prev;
   OS_ERR       os_err;
   CPU_CHAR     line_str[17];
   
   
   (void)p_arg;
   
   LCD_Disp_Start();                                             /* Initialize the LCD screen.                       */
   
   LCD_Disp_Position(0u, 0u);                                    /* Clear LCD screen                                 */
   LCD_Disp_PrintString((uint8 *)"                ");
   LCD_Disp_Position(1u, 0u);
   LCD_Disp_PrintString((uint8 *)"                ");
   
   LCD_Disp_PrintString((uint8 *)"Micrium uC/OS-III");

   user_if_state_cur  = APP_USER_IF_SIGN_ON;
   user_if_state_prev = APP_USER_IF_SIGN_ON;
   pb2_state_cur      = DEF_OFF;
   pb2_state_prev     = DEF_OFF;
   pb3_state_cur      = DEF_OFF;
   pb3_state_prev     = DEF_OFF;
   
   
    while (DEF_TRUE) {    

        if (user_if_state_cur != user_if_state_prev) {
            LCD_Disp_Position(0u, 0u);
            LCD_Disp_PrintString((uint8 *)"                ");
            LCD_Disp_Position(1u, 0u);
            LCD_Disp_PrintString((uint8 *)"                ");
            user_if_state_prev = user_if_state_cur;
        }

        switch (user_if_state_cur) {
            case APP_USER_IF_VER_TICK_RATE:
                 Str_Copy(line_str, "uC/OS-III Vx.yyy");
                 val          = (CPU_INT32U)OSVersion(&os_err);
                 line_str[11] = (val        )  / 1000u + '0';
                 line_str[13] = (val % 1000u)  /  100u + '0';
                 line_str[14] = (val %  100u)  /   10u + '0';
                 line_str[15] = (val %   10u)          + '0';
                 LCD_Disp_Position(0u, 0u);
                 LCD_Disp_PrintString((uint8 *)line_str);

                 Str_Copy(line_str, "TickRate:   xxxx");
                 val = (CPU_INT32U)OSCfg_TickRate_Hz;
                 Str_FmtNbr_Int32U((CPU_INT32U     )val, 
                                   (CPU_INT08U     )4u,
                                   (CPU_INT08U     )10,
                                   (CPU_CHAR       )0,
                                   (CPU_BOOLEAN    )DEF_NO,
                                   (CPU_BOOLEAN    )DEF_YES,
                                   (CPU_CHAR      *)&line_str[12]);
                 LCD_Disp_Position(1u, 0u);
                 LCD_Disp_PrintString((uint8 *)line_str);
                 break;

            case APP_USER_IF_CPU:
                 Str_Copy(line_str, "CPU Usage:xx %  ");
                 val          = (CPU_INT32U)OSStatTaskCPUUsage;
                 line_str[10] = (val / 10u) + '0';
                 line_str[11] = (val % 10u) + '0';
                 LCD_Disp_Position(0u, 0u);
                 LCD_Disp_PrintString((uint8 *)line_str);
                 
                 Str_Copy(line_str, "CPU Speed:xxxMHz");
                 val          = (CPU_INT32U)BSP_CPU_ClkFreq();
                 val         /= 1000000u;
                 line_str[10] = (val       ) / 100u + '0';
                 line_str[11] = (val % 100u) /  10u + '0';
                 line_str[12] = (val % 10u)         + '0';
                 LCD_Disp_Position(1u, 0u);
                 LCD_Disp_PrintString((uint8 *)line_str);
                 break;

            case APP_USER_IF_CTXSW:
                 Str_Copy(line_str, "#Ticks: xxxxxxxx");
                 val = (CPU_INT32U)OSTickCtr;
                 Str_FmtNbr_Int32U((CPU_INT32U     )val, 
                                   (CPU_INT08U     )8u,
                                   (CPU_INT08U     )10,
                                   (CPU_CHAR       )0,
                                   (CPU_BOOLEAN    )DEF_NO,
                                   (CPU_BOOLEAN    )DEF_YES,
                                   (CPU_CHAR      *)&line_str[8]);
                 LCD_Disp_Position(0u, 0u);
                 LCD_Disp_PrintString((uint8 *)line_str);
                 
                 Str_Copy(line_str, "#CtxSw: xxxxxxxx");
                 val          = (CPU_INT32U)OSTaskCtxSwCtr;
                 Str_FmtNbr_Int32U((CPU_INT32U     )val, 
                                   (CPU_INT08U     )8u,
                                   (CPU_INT08U     )10,
                                   (CPU_CHAR       )0,
                                   (CPU_BOOLEAN    )DEF_NO,
                                   (CPU_BOOLEAN    )DEF_YES,
                                   (CPU_CHAR      *)&line_str[8]);
                 LCD_Disp_Position(1u, 0u);
                 LCD_Disp_PrintString((uint8 *)line_str);
                 break;

            case APP_USER_IF_SIGN_ON:
            default:
                 LCD_Disp_Position(0u, 0u);
                 LCD_Disp_PrintString((uint8 *)"=== Micrium === ");
                 LCD_Disp_Position(1u, 0u);
                 LCD_Disp_PrintString((uint8 *)"   uC/OS-III    ");
                 break;
        }

        pb2_state_cur = BSP_PB_StatusGet(2);
        pb3_state_cur = BSP_PB_StatusGet(3);
        if ((pb2_state_cur  == DEF_ON ) &&
            (pb2_state_prev == DEF_OFF)) {     
            user_if_state_cur = (user_if_state_cur + 1u) % APP_USER_IF_STATE_MAX;
        }

        if ((pb3_state_cur  == DEF_ON ) &&
            (pb3_state_prev == DEF_OFF)) { 
            user_if_state_cur = (user_if_state_cur - 1u) % APP_USER_IF_STATE_MAX;
        }

        OSTimeDlyHMSM(0, 0, 0, 100, 
                      OS_OPT_TIME_HMSM_STRICT, 
                      &os_err);

        pb2_state_prev = pb2_state_cur;
        pb3_state_prev = pb3_state_cur;	
    }
}

/* desenvolvimento das funcoes */

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


/*
* https://micrium.atlassian.net/wiki/spaces/osiiidoc/pages/132306/OSTaskQPost
* https://micrium.atlassian.net/wiki/spaces/osiiidoc/pages/132308/OSTaskQPend
*/
