/*******************************************************************************
* File Name: ProbeUART_INT.c
* Version 2.20
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "ProbeUART.h"
#include "CyLib.h"


/***************************************
* Custom Declratations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if( (ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED) && \
     (ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH))

    extern volatile uint8 ProbeUART_rxBuffer[];
    extern volatile uint8 ProbeUART_rxBufferRead;
    extern volatile uint8 ProbeUART_rxBufferWrite;
    extern volatile uint8 ProbeUART_rxBufferLoopDetect;
    extern volatile uint8 ProbeUART_rxBufferOverflow;
    #if (ProbeUART_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 ProbeUART_rxAddressMode;
        extern volatile uint8 ProbeUART_rxAddressDetected;
    #endif /* End EnableHWAddress */    

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
        uint8 increment_pointer = 0u;

        /* User code required at start of ISR */
        /* `#START ProbeUART_RXISR_START` */

        /* `#END` */

        readData = ProbeUART_RXSTATUS_REG;

        if((readData & (ProbeUART_RX_STS_BREAK | ProbeUART_RX_STS_PAR_ERROR |
                        ProbeUART_RX_STS_STOP_ERROR | ProbeUART_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            /* `#START ProbeUART_RXISR_ERROR` */

            /* `#END` */
        }

        while(readData & ProbeUART_RX_STS_FIFO_NOTEMPTY)
        {
            
            #if (ProbeUART_RXHW_ADDRESS_ENABLED)
                if(ProbeUART_rxAddressMode == ProbeUART__B_UART__AM_SW_DETECT_TO_BUFFER) 
                {
                    if((readData & ProbeUART_RX_STS_MRKSPC) != 0u)
                    {  
                        if ((readData & ProbeUART_RX_STS_ADDR_MATCH) != 0u)
                        {
                            ProbeUART_rxAddressDetected = 1u;
                        }
                        else
                        {
                            ProbeUART_rxAddressDetected = 0u;
                        }
                    }

                    readData = ProbeUART_RXDATA_REG;
                    if(ProbeUART_rxAddressDetected != 0u)
                    {   /* store only addressed data */
                        ProbeUART_rxBuffer[ProbeUART_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* without software addressing */
                {
                    ProbeUART_rxBuffer[ProbeUART_rxBufferWrite] = ProbeUART_RXDATA_REG;
                    increment_pointer = 1u;
                }
            #else  /* without addressing */
                ProbeUART_rxBuffer[ProbeUART_rxBufferWrite] = ProbeUART_RXDATA_REG;
                increment_pointer = 1u;
            #endif /* End SW_DETECT_TO_BUFFER */
            
            /* do not increment buffer pointer when skip not adderessed data */
            if( increment_pointer != 0u )
            {
                if(ProbeUART_rxBufferLoopDetect)
                {   /* Set Software Buffer status Overflow */
                    ProbeUART_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                ProbeUART_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(ProbeUART_rxBufferWrite >= ProbeUART_RXBUFFERSIZE)
                {
                    ProbeUART_rxBufferWrite = 0u;
                }
                /* Detect pre-overload condition and set flag */
                if(ProbeUART_rxBufferWrite == ProbeUART_rxBufferRead)
                {
                    ProbeUART_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if(ProbeUART_FLOW_CONTROL != 0u)
                    /* Disable RX interrupt mask, it will be enabled when user read data from the buffer using APIs */
                        ProbeUART_RXSTATUS_MASK_REG  &= ~ProbeUART_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(ProbeUART_RX_VECT_NUM); 
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* End ProbeUART_FLOW_CONTROL != 0 */    
                }
            }

            /* Check again if there is data. */
            readData = ProbeUART_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START ProbeUART_RXISR_END` */

        /* `#END` */

    }

#endif /* End ProbeUART_RX_ENABLED && (ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH) */


#if(ProbeUART_TX_ENABLED && (ProbeUART_TXBUFFERSIZE > ProbeUART_FIFO_LENGTH))

    extern volatile uint8 ProbeUART_txBuffer[];
    extern volatile uint8 ProbeUART_txBufferRead;
    extern uint8 ProbeUART_txBufferWrite;


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
    *     from txBuffer, increments after each transmited byte.
    *  ProbeUART_rxBufferWrite - cyclic index for write to txBuffer, 
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(ProbeUART_TXISR)
    {

        /* User code required at start of ISR */
        /* `#START ProbeUART_TXISR_START` */

        /* `#END` */

        while((ProbeUART_txBufferRead != ProbeUART_txBufferWrite) && \
             !(ProbeUART_TXSTATUS_REG & ProbeUART_TX_STS_FIFO_FULL))
        {
            /* Check pointer. */
            if(ProbeUART_txBufferRead >= ProbeUART_TXBUFFERSIZE)
            {
                ProbeUART_txBufferRead = 0u;
            }

            ProbeUART_TXDATA_REG = ProbeUART_txBuffer[ProbeUART_txBufferRead];

            /* Set next pointer. */
            ProbeUART_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START ProbeUART_TXISR_END` */

        /* `#END` */
        
    }

#endif /* End ProbeUART_TX_ENABLED && (ProbeUART_TXBUFFERSIZE > ProbeUART_FIFO_LENGTH) */


/* [] END OF FILE */
