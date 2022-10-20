/*******************************************************************************
* File Name: main.c
*
* Version: 1.0
*
* Description:
*  This is a source code of the example project  
*  for PSoC 5LP ADC SAR Sequencer component.
*
*  Parameters used:
*   Resolution:      12 bit
*   Clock Frequency: 1.1 MHz
*   Sample Mode:     Free Running
*   Clock Source:    External
*   Input Range:     Vssa to Vdda (Single Ended)
*   Reference:       Internal Vref, bypassed
*   Channels:        4
*
*  
*  The project is configured to use with the 5V voltage, 
*  therefore switch SW3 (VDD SELECT) to the 5V state. 
*  If you want to use different input voltage, please, 
*  change VDDA in the System Tab (.cydwr file) appropriately. 
*  Four VDACs are used as input voltage sources for the component.
*  Initial settings for channels (from 1 to 4) are: 0.2, 0.4, 0.6, 0.8 Volts.
*  Actual converted initial voltages are displayed on the LCD to demonstrate 
*  that they coincide with each VDAC initial voltage settings.
*  VDAC APIs are used to subsequently increment each of four voltages in range 
*  from 0 to DAC Range (4 Volts). 
*  Converted voltages are displayed on the LCD.
*
********************************************************************************/

#include <project.h>
#include <stdio.h>

#if defined (__GNUC__)
    /* Add an explicit reference to the floating point printf library */
    /* to allow the usage of floating point conversion specifiers. */
    /* This is not linked in by default with the newlib-nano library. */
    asm (".global _printf_float");
#endif


int main()
{
    /* Declaration of all required variables */
    uint16 i = 0u;
    uint8 j = 0u;
    uint8 k = 0u;
    uint8 l = 0u; 
    uint8 count = 0u;
    uint8 flag = 0u;
    int16 result1 = 0u;
    int16 result2 = 0u;
    int16 result3 = 0u;
    int16 result4 = 0u;
    float res1 = 0u;
    float res2 = 0u;
    float res3 = 0u;
    float res4 = 0u;
    char8 resultStr1[16u];
    char8 resultStr2[16u];
    char8 resultStr3[16u];
    char8 resultStr4[16u];
    
    /* Start of all components */
    LCD_Start();
    LCD_ClearDisplay();
    VDAC8_1_Start();
    VDAC8_2_Start();
    VDAC8_3_Start();
    VDAC8_4_Start();
    ADC_SAR_Seq_Start();
    
    /* StartConvert() must be called to initiate 
       conversion in Free Running Mode
    */
    ADC_SAR_Seq_StartConvert();

    
    for(;;)
    {   
        /* Display initial VDAC voltages */
        if(flag == 0u)
        {
            LCD_Position(0u,0u);
            LCD_PrintString("Initial");
            LCD_Position(1u,0u);
            LCD_PrintString("VDAC settings:");
            ADC_SAR_Seq_IsEndConversion(ADC_SAR_Seq_WAIT_FOR_RESULT);
            result1 = ADC_SAR_Seq_GetResult16(0u);
            result2 = ADC_SAR_Seq_GetResult16(1u);
            result3 = ADC_SAR_Seq_GetResult16(2u);
            result4 = ADC_SAR_Seq_GetResult16(3u);
            
            res1 = ADC_SAR_Seq_CountsTo_Volts(result1);
            res2 = ADC_SAR_Seq_CountsTo_Volts(result2);
            res3 = ADC_SAR_Seq_CountsTo_Volts(result3);
            res4 = ADC_SAR_Seq_CountsTo_Volts(result4);
            
            CyDelay(2500u);
            LCD_ClearDisplay();
            LCD_Position(0u,0u); 
            LCD_PrintString("C1");
            sprintf((char *)resultStr1,"%+1.2f",res1);
            LCD_PrintString(resultStr1);
        
            LCD_PrintString(" C2");
            sprintf((char *)resultStr2,"%+1.2f",res2);
            LCD_PrintString(resultStr2);
            
            LCD_Position(1u,0u); 
            LCD_PrintString("C3");
            sprintf((char *)resultStr3,"%+1.2f",res3);
            LCD_PrintString(resultStr3);
        
            LCD_PrintString(" C4");
            sprintf((char *)resultStr4,"%+1.2f",res4);
            LCD_PrintString(resultStr4);
            CyDelay(10000u);
            flag = 1u;
            LCD_ClearDisplay();
            LCD_Position(0u,0u);
            LCD_PrintString("Start");
            LCD_Position(1u,0u);
            LCD_PrintString("incrementing.. ");
            CyDelay(2000u);
            
        }
    
        /* Start subsequent voltage incrementing for each channel */
        if(count < 20u)
        {
            VDAC8_1_SetValue(i);
            i += 10u;
            if(i > 255u)
            i = 0u;
         }
        else if((count > 20u) && (count < 40u))
        {
            VDAC8_2_SetValue(j);
            j += 10u;
            if(i > 255u)
            j = 0u;
        }
        else if((count > 40u) && (count < 60u))
        {
            VDAC8_3_SetValue(k);
            k += 10u;
            if(i > 255u)
            k = 0u;
        }
        
        else if((count > 60u) && (count < 80u))
        {
            VDAC8_4_SetValue(l);
            l += 10u;
            if(i > 255u)
            l = 0u;
        }
        
        count += 1u;
        if(count > 80u)
        count = 0u;
        
        CyDelay(200u); 
        result1 = ADC_SAR_Seq_finalArray[0u];
        result2 = ADC_SAR_Seq_finalArray[1u];
        result3 = ADC_SAR_Seq_finalArray[2u];
        result4 = ADC_SAR_Seq_finalArray[3u];
        
        res1 = ADC_SAR_Seq_CountsTo_Volts(result1);
        res2 = ADC_SAR_Seq_CountsTo_Volts(result2);
        res3 = ADC_SAR_Seq_CountsTo_Volts(result3);
        res4 = ADC_SAR_Seq_CountsTo_Volts(result4);
        
        LCD_ClearDisplay();
        LCD_Position(0u,0u); 
        LCD_PrintString("C1");
        sprintf((char *)resultStr1,"%+1.2f",res4);
        LCD_PrintString(resultStr1);
    
        LCD_PrintString(" C2");
        sprintf((char *)resultStr2,"%+1.2f",res3);
        LCD_PrintString(resultStr2);
        
        LCD_Position(1u,0u); 
        LCD_PrintString("C3");
        sprintf((char *)resultStr3,"%+1.2f",res2);
        LCD_PrintString(resultStr3);
    
        LCD_PrintString(" C4");
        sprintf((char *)resultStr4,"%+1.2f",res1);
        LCD_PrintString(resultStr4);
    }
}

/* [] END OF FILE */
