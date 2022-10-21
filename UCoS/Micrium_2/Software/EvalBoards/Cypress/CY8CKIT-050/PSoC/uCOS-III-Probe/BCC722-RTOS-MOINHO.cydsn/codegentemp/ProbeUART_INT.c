/*******************************************************************************
* File Name: ProbeUARTINT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ProbeUART.h"



/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (ProbeUART_RX_INTERRUPT_ENABLED && (ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED))
    /*******************************************************************************
    * Function Name: ProbeUART_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  ProbeUART_rxBuffer - RAM buffer pointer for save received data.
    *  ProbeUART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  ProbeUART_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  ProbeUART_rxBufferOverflow - software overflow flag. Set to one
    *     when ProbeUART_rxBufferWrite index overtakes
    *     ProbeUART_rxBufferRead index.
    *  ProbeUART_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when ProbeUART_rxBufferWrite is equal to
    *    ProbeUART_rxBufferRead
    *  ProbeUART_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  ProbeUART_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(ProbeUART_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef ProbeUART_RXISR_ENTRY_CALLBACK
        ProbeUART_RXISR_EntryCallback();
    #endif /* ProbeUART_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START ProbeUART_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = ProbeUART_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in ProbeUART_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (ProbeUART_RX_STS_BREAK | 
                            ProbeUART_RX_STS_PAR_ERROR |
                            ProbeUART_RX_STS_STOP_ERROR | 
                            ProbeUART_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                ProbeUART_errorStatus |= readStatus & ( ProbeUART_RX_STS_BREAK | 
                                                            ProbeUART_RX_STS_PAR_ERROR | 
                                                            ProbeUART_RX_STS_STOP_ERROR | 
                                                            ProbeUART_RX_STS_OVERRUN);
                /* `#START ProbeUART_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef ProbeUART_RXISR_ERROR_CALLBACK
                ProbeUART_RXISR_ERROR_Callback();
            #endif /* ProbeUART_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & ProbeUART_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = ProbeUART_RXDATA_REG;
            #if (ProbeUART_RXHW_ADDRESS_ENABLED)
                if(ProbeUART_rxAddressMode == (uint8)ProbeUART__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & ProbeUART_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & ProbeUART_RX_STS_ADDR_MATCH) != 0u)
                        {
                            ProbeUART_rxAddressDetected = 1u;
                        }
                        else
                        {
                            ProbeUART_rxAddressDetected = 0u;
                        }
                    }
                    if(ProbeUART_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        ProbeUART_rxBuffer[ProbeUART_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    ProbeUART_rxBuffer[ProbeUART_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                ProbeUART_rxBuffer[ProbeUART_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (ProbeUART_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(ProbeUART_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        ProbeUART_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    ProbeUART_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(ProbeUART_rxBufferWrite >= ProbeUART_RX_BUFFER_SIZE)
                    {
                        ProbeUART_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(ProbeUART_rxBufferWrite == ProbeUART_rxBufferRead)
                    {
                        ProbeUART_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (ProbeUART_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            ProbeUART_RXSTATUS_MASK_REG  &= (uint8)~ProbeUART_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(ProbeUART_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (ProbeUART_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & ProbeUART_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START ProbeUART_RXISR_END` */

        /* `#END` */

    #ifdef ProbeUART_RXISR_EXIT_CALLBACK
        ProbeUART_RXISR_ExitCallback();
    #endif /* ProbeUART_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (ProbeUART_RX_INTERRUPT_ENABLED && (ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED)) */


#if (ProbeUART_TX_INTERRUPT_ENABLED && ProbeUART_TX_ENABLED)
    /*******************************************************************************
    * Function Name: ProbeUART_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  ProbeUART_txBuffer - RAM buffer pointer for transmit data from.
    *  ProbeUART_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  ProbeUART_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(ProbeUART_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef ProbeUART_TXISR_ENTRY_CALLBACK
        ProbeUART_TXISR_EntryCallback();
    #endif /* ProbeUART_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START ProbeUART_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((ProbeUART_txBufferRead != ProbeUART_txBufferWrite) &&
             ((ProbeUART_TXSTATUS_REG & ProbeUART_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(ProbeUART_txBufferRead >= ProbeUART_TX_BUFFER_SIZE)
            {
                ProbeUART_txBufferRead = 0u;
            }

            ProbeUART_TXDATA_REG = ProbeUART_txBuffer[ProbeUART_txBufferRead];

            /* Set next pointer */
            ProbeUART_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START ProbeUART_TXISR_END` */

        /* `#END` */

    #ifdef ProbeUART_TXISR_EXIT_CALLBACK
        ProbeUART_TXISR_ExitCallback();
    #endif /* ProbeUART_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (ProbeUART_TX_INTERRUPT_ENABLED && ProbeUART_TX_ENABLED) */


/* [] END OF FILE */
