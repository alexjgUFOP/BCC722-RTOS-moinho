/*******************************************************************************
* File Name: ProbeUART.c
* Version 2.50
*
* Description:
*  This file provides all API functionality of the UART component
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ProbeUART.h"
#if (ProbeUART_INTERNAL_CLOCK_USED)
    #include "ProbeUART_IntClock.h"
#endif /* End ProbeUART_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 ProbeUART_initVar = 0u;

#if (ProbeUART_TX_INTERRUPT_ENABLED && ProbeUART_TX_ENABLED)
    volatile uint8 ProbeUART_txBuffer[ProbeUART_TX_BUFFER_SIZE];
    volatile uint8 ProbeUART_txBufferRead = 0u;
    uint8 ProbeUART_txBufferWrite = 0u;
#endif /* (ProbeUART_TX_INTERRUPT_ENABLED && ProbeUART_TX_ENABLED) */

#if (ProbeUART_RX_INTERRUPT_ENABLED && (ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED))
    uint8 ProbeUART_errorStatus = 0u;
    volatile uint8 ProbeUART_rxBuffer[ProbeUART_RX_BUFFER_SIZE];
    volatile uint8 ProbeUART_rxBufferRead  = 0u;
    volatile uint8 ProbeUART_rxBufferWrite = 0u;
    volatile uint8 ProbeUART_rxBufferLoopDetect = 0u;
    volatile uint8 ProbeUART_rxBufferOverflow   = 0u;
    #if (ProbeUART_RXHW_ADDRESS_ENABLED)
        volatile uint8 ProbeUART_rxAddressMode = ProbeUART_RX_ADDRESS_MODE;
        volatile uint8 ProbeUART_rxAddressDetected = 0u;
    #endif /* (ProbeUART_RXHW_ADDRESS_ENABLED) */
#endif /* (ProbeUART_RX_INTERRUPT_ENABLED && (ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED)) */


/*******************************************************************************
* Function Name: ProbeUART_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  ProbeUART_Start() sets the initVar variable, calls the
*  ProbeUART_Init() function, and then calls the
*  ProbeUART_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The ProbeUART_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time ProbeUART_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the ProbeUART_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ProbeUART_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(ProbeUART_initVar == 0u)
    {
        ProbeUART_Init();
        ProbeUART_initVar = 1u;
    }

    ProbeUART_Enable();
}


/*******************************************************************************
* Function Name: ProbeUART_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call ProbeUART_Init() because
*  the ProbeUART_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ProbeUART_Init(void) 
{
    #if(ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED)

        #if (ProbeUART_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(ProbeUART_RX_VECT_NUM, &ProbeUART_RXISR);
            CyIntSetPriority(ProbeUART_RX_VECT_NUM, ProbeUART_RX_PRIOR_NUM);
            ProbeUART_errorStatus = 0u;
        #endif /* (ProbeUART_RX_INTERRUPT_ENABLED) */

        #if (ProbeUART_RXHW_ADDRESS_ENABLED)
            ProbeUART_SetRxAddressMode(ProbeUART_RX_ADDRESS_MODE);
            ProbeUART_SetRxAddress1(ProbeUART_RX_HW_ADDRESS1);
            ProbeUART_SetRxAddress2(ProbeUART_RX_HW_ADDRESS2);
        #endif /* End ProbeUART_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        ProbeUART_RXBITCTR_PERIOD_REG = ProbeUART_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        ProbeUART_RXSTATUS_MASK_REG  = ProbeUART_INIT_RX_INTERRUPTS_MASK;
    #endif /* End ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED*/

    #if(ProbeUART_TX_ENABLED)
        #if (ProbeUART_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(ProbeUART_TX_VECT_NUM, &ProbeUART_TXISR);
            CyIntSetPriority(ProbeUART_TX_VECT_NUM, ProbeUART_TX_PRIOR_NUM);
        #endif /* (ProbeUART_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (ProbeUART_TXCLKGEN_DP)
            ProbeUART_TXBITCLKGEN_CTR_REG = ProbeUART_BIT_CENTER;
            ProbeUART_TXBITCLKTX_COMPLETE_REG = ((ProbeUART_NUMBER_OF_DATA_BITS +
                        ProbeUART_NUMBER_OF_START_BIT) * ProbeUART_OVER_SAMPLE_COUNT) - 1u;
        #else
            ProbeUART_TXBITCTR_PERIOD_REG = ((ProbeUART_NUMBER_OF_DATA_BITS +
                        ProbeUART_NUMBER_OF_START_BIT) * ProbeUART_OVER_SAMPLE_8) - 1u;
        #endif /* End ProbeUART_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (ProbeUART_TX_INTERRUPT_ENABLED)
            ProbeUART_TXSTATUS_MASK_REG = ProbeUART_TX_STS_FIFO_EMPTY;
        #else
            ProbeUART_TXSTATUS_MASK_REG = ProbeUART_INIT_TX_INTERRUPTS_MASK;
        #endif /*End ProbeUART_TX_INTERRUPT_ENABLED*/

    #endif /* End ProbeUART_TX_ENABLED */

    #if(ProbeUART_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        ProbeUART_WriteControlRegister( \
            (ProbeUART_ReadControlRegister() & (uint8)~ProbeUART_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(ProbeUART_PARITY_TYPE << ProbeUART_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End ProbeUART_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: ProbeUART_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call ProbeUART_Enable() because the ProbeUART_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ProbeUART_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void ProbeUART_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        ProbeUART_RXBITCTR_CONTROL_REG |= ProbeUART_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        ProbeUART_RXSTATUS_ACTL_REG  |= ProbeUART_INT_ENABLE;

        #if (ProbeUART_RX_INTERRUPT_ENABLED)
            ProbeUART_EnableRxInt();

            #if (ProbeUART_RXHW_ADDRESS_ENABLED)
                ProbeUART_rxAddressDetected = 0u;
            #endif /* (ProbeUART_RXHW_ADDRESS_ENABLED) */
        #endif /* (ProbeUART_RX_INTERRUPT_ENABLED) */
    #endif /* (ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED) */

    #if(ProbeUART_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!ProbeUART_TXCLKGEN_DP)
            ProbeUART_TXBITCTR_CONTROL_REG |= ProbeUART_CNTR_ENABLE;
        #endif /* End ProbeUART_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        ProbeUART_TXSTATUS_ACTL_REG |= ProbeUART_INT_ENABLE;
        #if (ProbeUART_TX_INTERRUPT_ENABLED)
            ProbeUART_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            ProbeUART_EnableTxInt();
        #endif /* (ProbeUART_TX_INTERRUPT_ENABLED) */
     #endif /* (ProbeUART_TX_INTERRUPT_ENABLED) */

    #if (ProbeUART_INTERNAL_CLOCK_USED)
        ProbeUART_IntClock_Start();  /* Enable the clock */
    #endif /* (ProbeUART_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ProbeUART_Stop
********************************************************************************
*
* Summary:
*  Disables the UART operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ProbeUART_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED)
        ProbeUART_RXBITCTR_CONTROL_REG &= (uint8) ~ProbeUART_CNTR_ENABLE;
    #endif /* (ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED) */

    #if (ProbeUART_TX_ENABLED)
        #if(!ProbeUART_TXCLKGEN_DP)
            ProbeUART_TXBITCTR_CONTROL_REG &= (uint8) ~ProbeUART_CNTR_ENABLE;
        #endif /* (!ProbeUART_TXCLKGEN_DP) */
    #endif /* (ProbeUART_TX_ENABLED) */

    #if (ProbeUART_INTERNAL_CLOCK_USED)
        ProbeUART_IntClock_Stop();   /* Disable the clock */
    #endif /* (ProbeUART_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED)
        ProbeUART_RXSTATUS_ACTL_REG  &= (uint8) ~ProbeUART_INT_ENABLE;

        #if (ProbeUART_RX_INTERRUPT_ENABLED)
            ProbeUART_DisableRxInt();
        #endif /* (ProbeUART_RX_INTERRUPT_ENABLED) */
    #endif /* (ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED) */

    #if (ProbeUART_TX_ENABLED)
        ProbeUART_TXSTATUS_ACTL_REG &= (uint8) ~ProbeUART_INT_ENABLE;

        #if (ProbeUART_TX_INTERRUPT_ENABLED)
            ProbeUART_DisableTxInt();
        #endif /* (ProbeUART_TX_INTERRUPT_ENABLED) */
    #endif /* (ProbeUART_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ProbeUART_ReadControlRegister
********************************************************************************
*
* Summary:
*  Returns the current value of the control register.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the control register.
*
*******************************************************************************/
uint8 ProbeUART_ReadControlRegister(void) 
{
    #if (ProbeUART_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(ProbeUART_CONTROL_REG);
    #endif /* (ProbeUART_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: ProbeUART_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  ProbeUART_WriteControlRegister(uint8 control) 
{
    #if (ProbeUART_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       ProbeUART_CONTROL_REG = control;
    #endif /* (ProbeUART_CONTROL_REG_REMOVED) */
}


#if(ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED)
    /*******************************************************************************
    * Function Name: ProbeUART_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      ProbeUART_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      ProbeUART_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      ProbeUART_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      ProbeUART_RX_STS_BREAK            Interrupt on break.
    *      ProbeUART_RX_STS_OVERRUN          Interrupt on overrun error.
    *      ProbeUART_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      ProbeUART_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void ProbeUART_SetRxInterruptMode(uint8 intSrc) 
    {
        ProbeUART_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: ProbeUART_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns the next byte of received data. This function returns data without
    *  checking the status. You must check the status separately.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  ProbeUART_rxBuffer - RAM buffer pointer for save received data.
    *  ProbeUART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  ProbeUART_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  ProbeUART_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 ProbeUART_ReadRxData(void) 
    {
        uint8 rxData;

    #if (ProbeUART_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        ProbeUART_DisableRxInt();

        locRxBufferRead  = ProbeUART_rxBufferRead;
        locRxBufferWrite = ProbeUART_rxBufferWrite;

        if( (ProbeUART_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = ProbeUART_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= ProbeUART_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            ProbeUART_rxBufferRead = locRxBufferRead;

            if(ProbeUART_rxBufferLoopDetect != 0u)
            {
                ProbeUART_rxBufferLoopDetect = 0u;
                #if ((ProbeUART_RX_INTERRUPT_ENABLED) && (ProbeUART_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( ProbeUART_HD_ENABLED )
                        if((ProbeUART_CONTROL_REG & ProbeUART_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            ProbeUART_RXSTATUS_MASK_REG  |= ProbeUART_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        ProbeUART_RXSTATUS_MASK_REG  |= ProbeUART_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end ProbeUART_HD_ENABLED */
                #endif /* ((ProbeUART_RX_INTERRUPT_ENABLED) && (ProbeUART_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = ProbeUART_RXDATA_REG;
        }

        ProbeUART_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = ProbeUART_RXDATA_REG;

    #endif /* (ProbeUART_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: ProbeUART_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the receiver status register and the software
    *  buffer overflow status.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Side Effect:
    *  All status register bits are clear-on-read except
    *  ProbeUART_RX_STS_FIFO_NOTEMPTY.
    *  ProbeUART_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  ProbeUART_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   ProbeUART_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   ProbeUART_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 ProbeUART_ReadRxStatus(void) 
    {
        uint8 status;

        status = ProbeUART_RXSTATUS_REG & ProbeUART_RX_HW_MASK;

    #if (ProbeUART_RX_INTERRUPT_ENABLED)
        if(ProbeUART_rxBufferOverflow != 0u)
        {
            status |= ProbeUART_RX_STS_SOFT_BUFF_OVER;
            ProbeUART_rxBufferOverflow = 0u;
        }
    #endif /* (ProbeUART_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: ProbeUART_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. ProbeUART_GetChar() is
    *  designed for ASCII characters and returns a uint8 where 1 to 255 are values
    *  for valid characters and 0 indicates an error occurred or no data is present.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  ProbeUART_rxBuffer - RAM buffer pointer for save received data.
    *  ProbeUART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  ProbeUART_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  ProbeUART_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 ProbeUART_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (ProbeUART_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        ProbeUART_DisableRxInt();

        locRxBufferRead  = ProbeUART_rxBufferRead;
        locRxBufferWrite = ProbeUART_rxBufferWrite;

        if( (ProbeUART_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = ProbeUART_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= ProbeUART_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            ProbeUART_rxBufferRead = locRxBufferRead;

            if(ProbeUART_rxBufferLoopDetect != 0u)
            {
                ProbeUART_rxBufferLoopDetect = 0u;
                #if( (ProbeUART_RX_INTERRUPT_ENABLED) && (ProbeUART_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( ProbeUART_HD_ENABLED )
                        if((ProbeUART_CONTROL_REG & ProbeUART_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            ProbeUART_RXSTATUS_MASK_REG |= ProbeUART_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        ProbeUART_RXSTATUS_MASK_REG |= ProbeUART_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end ProbeUART_HD_ENABLED */
                #endif /* ProbeUART_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = ProbeUART_RXSTATUS_REG;
            if((rxStatus & ProbeUART_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = ProbeUART_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (ProbeUART_RX_STS_BREAK | ProbeUART_RX_STS_PAR_ERROR |
                                ProbeUART_RX_STS_STOP_ERROR | ProbeUART_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        ProbeUART_EnableRxInt();

    #else

        rxStatus =ProbeUART_RXSTATUS_REG;
        if((rxStatus & ProbeUART_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = ProbeUART_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (ProbeUART_RX_STS_BREAK | ProbeUART_RX_STS_PAR_ERROR |
                            ProbeUART_RX_STS_STOP_ERROR | ProbeUART_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (ProbeUART_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: ProbeUART_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, returns received character and error
    *  condition.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains status and LSB contains UART RX data. If the MSB is nonzero,
    *  an error has occurred.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 ProbeUART_GetByte(void) 
    {
        
    #if (ProbeUART_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        ProbeUART_DisableRxInt();
        locErrorStatus = (uint16)ProbeUART_errorStatus;
        ProbeUART_errorStatus = 0u;
        ProbeUART_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | ProbeUART_ReadRxData() );
    #else
        return ( ((uint16)ProbeUART_ReadRxStatus() << 8u) | ProbeUART_ReadRxData() );
    #endif /* ProbeUART_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: ProbeUART_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received bytes available in the RX buffer.
    *  * RX software buffer is disabled (RX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty RX FIFO or 1 for not empty RX FIFO.
    *  * RX software buffer is enabled: returns the number of bytes available in 
    *    the RX software buffer. Bytes available in the RX FIFO do not take to 
    *    account.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Number of bytes in the RX buffer. 
    *    Return value type depends on RX Buffer Size parameter.
    *
    * Global Variables:
    *  ProbeUART_rxBufferWrite - used to calculate left bytes.
    *  ProbeUART_rxBufferRead - used to calculate left bytes.
    *  ProbeUART_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 ProbeUART_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (ProbeUART_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        ProbeUART_DisableRxInt();

        if(ProbeUART_rxBufferRead == ProbeUART_rxBufferWrite)
        {
            if(ProbeUART_rxBufferLoopDetect != 0u)
            {
                size = ProbeUART_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(ProbeUART_rxBufferRead < ProbeUART_rxBufferWrite)
        {
            size = (ProbeUART_rxBufferWrite - ProbeUART_rxBufferRead);
        }
        else
        {
            size = (ProbeUART_RX_BUFFER_SIZE - ProbeUART_rxBufferRead) + ProbeUART_rxBufferWrite;
        }

        ProbeUART_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((ProbeUART_RXSTATUS_REG & ProbeUART_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (ProbeUART_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: ProbeUART_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receiver memory buffer and hardware RX FIFO of all received data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  ProbeUART_rxBufferWrite - cleared to zero.
    *  ProbeUART_rxBufferRead - cleared to zero.
    *  ProbeUART_rxBufferLoopDetect - cleared to zero.
    *  ProbeUART_rxBufferOverflow - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM or FIFO buffer will be lost.
    *
    *******************************************************************************/
    void ProbeUART_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        ProbeUART_RXDATA_AUX_CTL_REG |= (uint8)  ProbeUART_RX_FIFO_CLR;
        ProbeUART_RXDATA_AUX_CTL_REG &= (uint8) ~ProbeUART_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (ProbeUART_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        ProbeUART_DisableRxInt();

        ProbeUART_rxBufferRead = 0u;
        ProbeUART_rxBufferWrite = 0u;
        ProbeUART_rxBufferLoopDetect = 0u;
        ProbeUART_rxBufferOverflow = 0u;

        ProbeUART_EnableRxInt();

    #endif /* (ProbeUART_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: ProbeUART_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  ProbeUART__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  ProbeUART__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  ProbeUART__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  ProbeUART__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  ProbeUART__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  ProbeUART_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  ProbeUART_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void ProbeUART_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(ProbeUART_RXHW_ADDRESS_ENABLED)
            #if(ProbeUART_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* ProbeUART_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = ProbeUART_CONTROL_REG & (uint8)~ProbeUART_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << ProbeUART_CTRL_RXADDR_MODE0_SHIFT);
                ProbeUART_CONTROL_REG = tmpCtrl;

                #if(ProbeUART_RX_INTERRUPT_ENABLED && \
                   (ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH) )
                    ProbeUART_rxAddressMode = addressMode;
                    ProbeUART_rxAddressDetected = 0u;
                #endif /* End ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH*/
            #endif /* End ProbeUART_CONTROL_REG_REMOVED */
        #else /* ProbeUART_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End ProbeUART_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: ProbeUART_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Sets the first of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #1 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void ProbeUART_SetRxAddress1(uint8 address) 
    {
        ProbeUART_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: ProbeUART_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Sets the second of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #2 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void ProbeUART_SetRxAddress2(uint8 address) 
    {
        ProbeUART_RXADDRESS2_REG = address;
    }

#endif  /* ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED*/


#if( (ProbeUART_TX_ENABLED) || (ProbeUART_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: ProbeUART_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   ProbeUART_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   ProbeUART_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   ProbeUART_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   ProbeUART_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void ProbeUART_SetTxInterruptMode(uint8 intSrc) 
    {
        ProbeUART_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: ProbeUART_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data into the transmit buffer to be sent when the bus is
    *  available without checking the TX status register. You must check status
    *  separately.
    *
    * Parameters:
    *  txDataByte: data byte
    *
    * Return:
    * None.
    *
    * Global Variables:
    *  ProbeUART_txBuffer - RAM buffer pointer for save data for transmission
    *  ProbeUART_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  ProbeUART_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  ProbeUART_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void ProbeUART_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(ProbeUART_initVar != 0u)
        {
        #if (ProbeUART_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            ProbeUART_DisableTxInt();

            if( (ProbeUART_txBufferRead == ProbeUART_txBufferWrite) &&
                ((ProbeUART_TXSTATUS_REG & ProbeUART_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                ProbeUART_TXDATA_REG = txDataByte;
            }
            else
            {
                if(ProbeUART_txBufferWrite >= ProbeUART_TX_BUFFER_SIZE)
                {
                    ProbeUART_txBufferWrite = 0u;
                }

                ProbeUART_txBuffer[ProbeUART_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                ProbeUART_txBufferWrite++;
            }

            ProbeUART_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            ProbeUART_TXDATA_REG = txDataByte;

        #endif /*(ProbeUART_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: ProbeUART_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Reads the status register for the TX portion of the UART.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the TX status register, which is cleared on read.
    *  It is up to the user to handle all bits in this return value accordingly,
    *  even if the bit was not enabled as an interrupt source the event happened
    *  and must be handled accordingly.
    *
    *******************************************************************************/
    uint8 ProbeUART_ReadTxStatus(void) 
    {
        return(ProbeUART_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: ProbeUART_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Puts a byte of data into the transmit buffer to be sent when the bus is
    *  available. This is a blocking API that waits until the TX buffer has room to
    *  hold the data.
    *
    * Parameters:
    *  txDataByte: Byte containing the data to transmit
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  ProbeUART_txBuffer - RAM buffer pointer for save data for transmission
    *  ProbeUART_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  ProbeUART_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  ProbeUART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void ProbeUART_PutChar(uint8 txDataByte) 
    {
    #if (ProbeUART_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((ProbeUART_TX_BUFFER_SIZE > ProbeUART_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            ProbeUART_DisableTxInt();
        #endif /* (ProbeUART_TX_BUFFER_SIZE > ProbeUART_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = ProbeUART_txBufferWrite;
            locTxBufferRead  = ProbeUART_txBufferRead;

        #if ((ProbeUART_TX_BUFFER_SIZE > ProbeUART_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            ProbeUART_EnableTxInt();
        #endif /* (ProbeUART_TX_BUFFER_SIZE > ProbeUART_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(ProbeUART_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((ProbeUART_TXSTATUS_REG & ProbeUART_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            ProbeUART_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= ProbeUART_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            ProbeUART_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((ProbeUART_TX_BUFFER_SIZE > ProbeUART_MAX_BYTE_VALUE) && (CY_PSOC3))
            ProbeUART_DisableTxInt();
        #endif /* (ProbeUART_TX_BUFFER_SIZE > ProbeUART_MAX_BYTE_VALUE) && (CY_PSOC3) */

            ProbeUART_txBufferWrite = locTxBufferWrite;

        #if ((ProbeUART_TX_BUFFER_SIZE > ProbeUART_MAX_BYTE_VALUE) && (CY_PSOC3))
            ProbeUART_EnableTxInt();
        #endif /* (ProbeUART_TX_BUFFER_SIZE > ProbeUART_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (ProbeUART_TXSTATUS_REG & ProbeUART_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                ProbeUART_SetPendingTxInt();
            }
        }

    #else

        while((ProbeUART_TXSTATUS_REG & ProbeUART_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        ProbeUART_TXDATA_REG = txDataByte;

    #endif /* ProbeUART_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: ProbeUART_PutString
    ********************************************************************************
    *
    * Summary:
    *  Sends a NULL terminated string to the TX buffer for transmission.
    *
    * Parameters:
    *  string[]: Pointer to the null terminated string array residing in RAM or ROM
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  ProbeUART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void ProbeUART_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(ProbeUART_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                ProbeUART_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: ProbeUART_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Places N bytes of data from a memory array into the TX buffer for
    *  transmission.
    *
    * Parameters:
    *  string[]: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of bytes to be transmitted. The type depends on TX Buffer
    *             Size parameter.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  ProbeUART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void ProbeUART_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(ProbeUART_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                ProbeUART_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: ProbeUART_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Writes a byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) to the transmit buffer.
    *
    * Parameters:
    *  txDataByte: Data byte to transmit before the carriage return and line feed.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  ProbeUART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void ProbeUART_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(ProbeUART_initVar != 0u)
        {
            ProbeUART_PutChar(txDataByte);
            ProbeUART_PutChar(0x0Du);
            ProbeUART_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: ProbeUART_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of bytes in the TX buffer which are waiting to be 
    *  transmitted.
    *  * TX software buffer is disabled (TX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty TX FIFO, 1 for not full TX FIFO or 4 for full TX FIFO.
    *  * TX software buffer is enabled: returns the number of bytes in the TX 
    *    software buffer which are waiting to be transmitted. Bytes available in the
    *    TX FIFO do not count.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Number of bytes used in the TX buffer. Return value type depends on the TX 
    *  Buffer Size parameter.
    *
    * Global Variables:
    *  ProbeUART_txBufferWrite - used to calculate left space.
    *  ProbeUART_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 ProbeUART_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (ProbeUART_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        ProbeUART_DisableTxInt();

        if(ProbeUART_txBufferRead == ProbeUART_txBufferWrite)
        {
            size = 0u;
        }
        else if(ProbeUART_txBufferRead < ProbeUART_txBufferWrite)
        {
            size = (ProbeUART_txBufferWrite - ProbeUART_txBufferRead);
        }
        else
        {
            size = (ProbeUART_TX_BUFFER_SIZE - ProbeUART_txBufferRead) +
                    ProbeUART_txBufferWrite;
        }

        ProbeUART_EnableTxInt();

    #else

        size = ProbeUART_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & ProbeUART_TX_STS_FIFO_FULL) != 0u)
        {
            size = ProbeUART_FIFO_LENGTH;
        }
        else if((size & ProbeUART_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (ProbeUART_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: ProbeUART_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears all data from the TX buffer and hardware TX FIFO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  ProbeUART_txBufferWrite - cleared to zero.
    *  ProbeUART_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Data waiting in the transmit buffer is not sent; a byte that is currently
    *  transmitting finishes transmitting.
    *
    *******************************************************************************/
    void ProbeUART_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        ProbeUART_TXDATA_AUX_CTL_REG |= (uint8)  ProbeUART_TX_FIFO_CLR;
        ProbeUART_TXDATA_AUX_CTL_REG &= (uint8) ~ProbeUART_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (ProbeUART_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        ProbeUART_DisableTxInt();

        ProbeUART_txBufferRead = 0u;
        ProbeUART_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        ProbeUART_EnableTxInt();

    #endif /* (ProbeUART_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: ProbeUART_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   ProbeUART_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   ProbeUART_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   ProbeUART_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   ProbeUART_SEND_WAIT_REINIT - Performs both options: 
    *      ProbeUART_SEND_BREAK and ProbeUART_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  ProbeUART_initVar - checked to identify that the component has been
    *     initialized.
    *  txPeriod - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  There are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Function will block CPU until transmission
    *     complete.
    *  2) User may want to use blocking time if UART configured to the low speed
    *     operation
    *     Example for this case:
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to initialize and use the interrupt to
    *     complete break operation.
    *     Example for this case:
    *     Initialize TX interrupt with "TX - On TX Complete" parameter
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     When interrupt appear with ProbeUART_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The ProbeUART_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void ProbeUART_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(ProbeUART_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(ProbeUART_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == ProbeUART_SEND_BREAK) ||
                (retMode == ProbeUART_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                ProbeUART_WriteControlRegister(ProbeUART_ReadControlRegister() |
                                                      ProbeUART_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                ProbeUART_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = ProbeUART_TXSTATUS_REG;
                }
                while((tmpStat & ProbeUART_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == ProbeUART_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == ProbeUART_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = ProbeUART_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & ProbeUART_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == ProbeUART_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == ProbeUART_REINIT) ||
                (retMode == ProbeUART_SEND_WAIT_REINIT) )
            {
                ProbeUART_WriteControlRegister(ProbeUART_ReadControlRegister() &
                                              (uint8)~ProbeUART_CTRL_HD_SEND_BREAK);
            }

        #else /* ProbeUART_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == ProbeUART_SEND_BREAK) ||
                (retMode == ProbeUART_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (ProbeUART_PARITY_TYPE != ProbeUART__B_UART__NONE_REVB) || \
                                    (ProbeUART_PARITY_TYPE_SW != 0u) )
                    ProbeUART_WriteControlRegister(ProbeUART_ReadControlRegister() |
                                                          ProbeUART_CTRL_HD_SEND_BREAK);
                #endif /* End ProbeUART_PARITY_TYPE != ProbeUART__B_UART__NONE_REVB  */

                #if(ProbeUART_TXCLKGEN_DP)
                    txPeriod = ProbeUART_TXBITCLKTX_COMPLETE_REG;
                    ProbeUART_TXBITCLKTX_COMPLETE_REG = ProbeUART_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = ProbeUART_TXBITCTR_PERIOD_REG;
                    ProbeUART_TXBITCTR_PERIOD_REG = ProbeUART_TXBITCTR_BREAKBITS8X;
                #endif /* End ProbeUART_TXCLKGEN_DP */

                /* Send zeros */
                ProbeUART_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = ProbeUART_TXSTATUS_REG;
                }
                while((tmpStat & ProbeUART_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == ProbeUART_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == ProbeUART_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = ProbeUART_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & ProbeUART_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == ProbeUART_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == ProbeUART_REINIT) ||
                (retMode == ProbeUART_SEND_WAIT_REINIT) )
            {

            #if(ProbeUART_TXCLKGEN_DP)
                ProbeUART_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                ProbeUART_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End ProbeUART_TXCLKGEN_DP */

            #if( (ProbeUART_PARITY_TYPE != ProbeUART__B_UART__NONE_REVB) || \
                 (ProbeUART_PARITY_TYPE_SW != 0u) )
                ProbeUART_WriteControlRegister(ProbeUART_ReadControlRegister() &
                                                      (uint8) ~ProbeUART_CTRL_HD_SEND_BREAK);
            #endif /* End ProbeUART_PARITY_TYPE != NONE */
            }
        #endif    /* End ProbeUART_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: ProbeUART_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       ProbeUART_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       ProbeUART_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears ProbeUART_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void ProbeUART_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( ProbeUART_CONTROL_REG_REMOVED == 0u )
            ProbeUART_WriteControlRegister(ProbeUART_ReadControlRegister() |
                                                  ProbeUART_CTRL_MARK);
        #endif /* End ProbeUART_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( ProbeUART_CONTROL_REG_REMOVED == 0u )
            ProbeUART_WriteControlRegister(ProbeUART_ReadControlRegister() &
                                                  (uint8) ~ProbeUART_CTRL_MARK);
        #endif /* End ProbeUART_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndProbeUART_TX_ENABLED */

#if(ProbeUART_HD_ENABLED)


    /*******************************************************************************
    * Function Name: ProbeUART_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the receiver configuration in half duplex mode. After calling this
    *  function, the UART is ready to receive data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the transmitter
    *  configuration.
    *
    *******************************************************************************/
    void ProbeUART_LoadRxConfig(void) 
    {
        ProbeUART_WriteControlRegister(ProbeUART_ReadControlRegister() &
                                                (uint8)~ProbeUART_CTRL_HD_SEND);
        ProbeUART_RXBITCTR_PERIOD_REG = ProbeUART_HD_RXBITCTR_INIT;

    #if (ProbeUART_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        ProbeUART_SetRxInterruptMode(ProbeUART_INIT_RX_INTERRUPTS_MASK);
    #endif /* (ProbeUART_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: ProbeUART_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the transmitter configuration in half duplex mode. After calling this
    *  function, the UART is ready to transmit data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the receiver configuration.
    *
    *******************************************************************************/
    void ProbeUART_LoadTxConfig(void) 
    {
    #if (ProbeUART_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        ProbeUART_SetRxInterruptMode(0u);
    #endif /* (ProbeUART_RX_INTERRUPT_ENABLED) */

        ProbeUART_WriteControlRegister(ProbeUART_ReadControlRegister() | ProbeUART_CTRL_HD_SEND);
        ProbeUART_RXBITCTR_PERIOD_REG = ProbeUART_HD_TXBITCTR_INIT;
    }

#endif  /* ProbeUART_HD_ENABLED */


/* [] END OF FILE */
