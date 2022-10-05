/*******************************************************************************
* File Name: ProbeUART.c
* Version 2.20
*
* Description:
*  This file provides all API functionality of the UART component
*
* Note:
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
* Global data allocation
***************************************/

#if( ProbeUART_TX_ENABLED && (ProbeUART_TXBUFFERSIZE > ProbeUART_FIFO_LENGTH))
    volatile uint8 ProbeUART_txBuffer[ProbeUART_TXBUFFERSIZE];
    volatile uint8 ProbeUART_txBufferRead = 0u;
    uint8 ProbeUART_txBufferWrite = 0u;
#endif /* End ProbeUART_TX_ENABLED */
#if( ( ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED ) && \
     (ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH) )
    volatile uint8 ProbeUART_rxBuffer[ProbeUART_RXBUFFERSIZE];
    volatile uint8 ProbeUART_rxBufferRead = 0u;
    volatile uint8 ProbeUART_rxBufferWrite = 0u;
    volatile uint8 ProbeUART_rxBufferLoopDetect = 0u;
    volatile uint8 ProbeUART_rxBufferOverflow = 0u;
    #if (ProbeUART_RXHW_ADDRESS_ENABLED)
        volatile uint8 ProbeUART_rxAddressMode = ProbeUART_RXADDRESSMODE;
        volatile uint8 ProbeUART_rxAddressDetected = 0u;
    #endif /* End EnableHWAddress */    
#endif /* End ProbeUART_RX_ENABLED */


/***************************************
* Local data allocation
***************************************/

uint8 ProbeUART_initVar = 0u;


/*******************************************************************************
* Function Name: ProbeUART_Start
********************************************************************************
*
* Summary:
*  Initialize and Enable the UART component.
*  Enable the clock input to enable operation.
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
*  and set to one (1u) the first time UART_Start() is called. This allows for 
*  component initialization without re-initialization in all subsequent calls 
*  to the ProbeUART_Start() routine. 
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ProbeUART_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
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
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  ProbeUART_Start().
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

        #if(ProbeUART_RX_INTERRUPT_ENABLED && (ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH))
            /* Set the RX Interrupt. */
            CyIntSetVector(ProbeUART_RX_VECT_NUM,   ProbeUART_RXISR);
            CyIntSetPriority(ProbeUART_RX_VECT_NUM, ProbeUART_RX_PRIOR_NUM);
        #endif /* End ProbeUART_RX_INTERRUPT_ENABLED */

        #if (ProbeUART_RXHW_ADDRESS_ENABLED)
            ProbeUART_SetRxAddressMode(ProbeUART_RXAddressMode);
            ProbeUART_SetRxAddress1(ProbeUART_RXHWADDRESS1);
            ProbeUART_SetRxAddress2(ProbeUART_RXHWADDRESS2);
        #endif /* End ProbeUART_RXHW_ADDRESS_ENABLED */

        /* Configure the Initial RX interrupt mask */
        ProbeUART_RXSTATUS_MASK_REG  = ProbeUART_INIT_RX_INTERRUPTS_MASK;
    #endif /* End ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED*/

    #if(ProbeUART_TX_ENABLED)
        #if(ProbeUART_TX_INTERRUPT_ENABLED && (ProbeUART_TXBUFFERSIZE > ProbeUART_FIFO_LENGTH))
            /* Set the TX Interrupt. */
            CyIntSetVector(ProbeUART_TX_VECT_NUM,   ProbeUART_TXISR);
            CyIntSetPriority(ProbeUART_TX_VECT_NUM, ProbeUART_TX_PRIOR_NUM);
        #endif /* End ProbeUART_TX_INTERRUPT_ENABLED */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if(ProbeUART_TXCLKGEN_DP)
            ProbeUART_TXBITCLKGEN_CTR_REG = ProbeUART_BIT_CENTER;
            ProbeUART_TXBITCLKTX_COMPLETE_REG = (ProbeUART_NUMBER_OF_DATA_BITS + \
                                                    ProbeUART_NUMBER_OF_START_BIT) * \
                                                    ProbeUART_OVER_SAMPLE_COUNT;
        #else
            ProbeUART_TXBITCTR_COUNTER_REG = (ProbeUART_NUMBER_OF_DATA_BITS + \
                                                    ProbeUART_NUMBER_OF_START_BIT) * \
                                                    ProbeUART_OVER_SAMPLE_8;
        #endif /* End ProbeUART_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if(ProbeUART_TX_INTERRUPT_ENABLED && (ProbeUART_TXBUFFERSIZE > ProbeUART_FIFO_LENGTH))
            ProbeUART_TXSTATUS_MASK_REG = ProbeUART_TX_STS_FIFO_EMPTY;
        #else
            ProbeUART_TXSTATUS_MASK_REG = ProbeUART_INIT_TX_INTERRUPTS_MASK;
        #endif /*End ProbeUART_TX_INTERRUPT_ENABLED*/
        
    #endif /* End ProbeUART_TX_ENABLED */

    #if(ProbeUART_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        ProbeUART_WriteControlRegister( \
            (ProbeUART_ReadControlRegister() & ~ProbeUART_CTRL_PARITY_TYPE_MASK) | \
            (ProbeUART_PARITY_TYPE << ProbeUART_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End ProbeUART_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: ProbeUART_Enable
********************************************************************************
*
* Summary:
*  Enables the UART block operation
*
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
    
    #if(ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED)
        /*RX Counter (Count7) Enable */
        ProbeUART_RXBITCTR_CONTROL_REG |= ProbeUART_CNTR_ENABLE;
        /* Enable the RX Interrupt. */
        ProbeUART_RXSTATUS_ACTL_REG  |= ProbeUART_INT_ENABLE;
        #if(ProbeUART_RX_INTERRUPT_ENABLED && (ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH))
            CyIntEnable(ProbeUART_RX_VECT_NUM);
            #if (ProbeUART_RXHW_ADDRESS_ENABLED)
                ProbeUART_rxAddressDetected = 0u;
            #endif /* End ProbeUART_RXHW_ADDRESS_ENABLED */
        #endif /* End ProbeUART_RX_INTERRUPT_ENABLED */
    #endif /* End ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED*/

    #if(ProbeUART_TX_ENABLED)
        /*TX Counter (DP/Count7) Enable */
        #if(!ProbeUART_TXCLKGEN_DP)
            ProbeUART_TXBITCTR_CONTROL_REG |= ProbeUART_CNTR_ENABLE;
        #endif /* End ProbeUART_TXCLKGEN_DP */
        /* Enable the TX Interrupt. */
        ProbeUART_TXSTATUS_ACTL_REG |= ProbeUART_INT_ENABLE;
        #if(ProbeUART_TX_INTERRUPT_ENABLED && (ProbeUART_TXBUFFERSIZE > ProbeUART_FIFO_LENGTH))
            CyIntEnable(ProbeUART_TX_VECT_NUM);
        #endif /* End ProbeUART_TX_INTERRUPT_ENABLED*/
     #endif /* End ProbeUART_TX_ENABLED */

    #if(ProbeUART_INTERNAL_CLOCK_USED)
        /* Set the bit to enable the clock. */
        ProbeUART_INTCLOCK_CLKEN_REG |= ProbeUART_INTCLOCK_CLKEN_MASK;
    #endif /* End ProbeUART_INTERNAL_CLOCK_USED */
    
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ProbeUART_Stop
********************************************************************************
*
* Summary:
*  Disable the UART component
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

    /*Write Bit Counter Disable */
    #if(ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED)
        ProbeUART_RXBITCTR_CONTROL_REG &= ~ProbeUART_CNTR_ENABLE;
    #endif /* End ProbeUART_RX_ENABLED */

    #if(ProbeUART_TX_ENABLED)
        #if(!ProbeUART_TXCLKGEN_DP)
            ProbeUART_TXBITCTR_CONTROL_REG &= ~ProbeUART_CNTR_ENABLE;
        #endif /* End ProbeUART_TXCLKGEN_DP */
    #endif /* ProbeUART_TX_ENABLED */

    #if(ProbeUART_INTERNAL_CLOCK_USED)
        /* Clear the bit to enable the clock. */
        ProbeUART_INTCLOCK_CLKEN_REG &= ~ProbeUART_INTCLOCK_CLKEN_MASK;
    #endif /* End ProbeUART_INTERNAL_CLOCK_USED */
    
    /*Disable internal interrupt component*/
    #if(ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED)
        ProbeUART_RXSTATUS_ACTL_REG  &= ~ProbeUART_INT_ENABLE;
        #if(ProbeUART_RX_INTERRUPT_ENABLED && (ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH))
            ProbeUART_DisableRxInt();
        #endif /* End ProbeUART_RX_INTERRUPT_ENABLED */
    #endif /* End ProbeUART_RX_ENABLED */
    
    #if(ProbeUART_TX_ENABLED)
        ProbeUART_TXSTATUS_ACTL_REG &= ~ProbeUART_INT_ENABLE;
        #if(ProbeUART_TX_INTERRUPT_ENABLED && (ProbeUART_TXBUFFERSIZE > ProbeUART_FIFO_LENGTH))
            ProbeUART_DisableTxInt();
        #endif /* End ProbeUART_TX_INTERRUPT_ENABLED */
    #endif /* End ProbeUART_TX_ENABLED */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ProbeUART_ReadControlRegister
********************************************************************************
*
* Summary:
*  Read the current state of the control register
*
* Parameters:
*  None.
*
* Return:
*  Current state of the control register.
*
*******************************************************************************/
uint8 ProbeUART_ReadControlRegister(void) 
{
    #if( ProbeUART_CONTROL_REG_REMOVED )
        return(0u);
    #else
        return(ProbeUART_CONTROL_REG);
    #endif /* End ProbeUART_CONTROL_REG_REMOVED */
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
    #if( ProbeUART_CONTROL_REG_REMOVED )
        control = control;      /* Reassigning to release compiler warning */ 
    #else
       ProbeUART_CONTROL_REG = control;
    #endif /* End ProbeUART_CONTROL_REG_REMOVED */
}


#if(ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED)

    #if(ProbeUART_RX_INTERRUPT_ENABLED)

        /*******************************************************************************
        * Function Name: ProbeUART_EnableRxInt
        ********************************************************************************
        *
        * Summary:
        *  Enable RX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Enable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void ProbeUART_EnableRxInt(void) 
        {
            CyIntEnable(ProbeUART_RX_VECT_NUM);
        }


        /*******************************************************************************
        * Function Name: ProbeUART_DisableRxInt
        ********************************************************************************
        *
        * Summary:
        *  Disable RX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Disable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void ProbeUART_DisableRxInt(void) 
        {
            CyIntDisable(ProbeUART_RX_VECT_NUM);
        }

    #endif /* ProbeUART_RX_INTERRUPT_ENABLED */


    /*******************************************************************************
    * Function Name: ProbeUART_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configure which status bits trigger an interrupt event
    *
    * Parameters:
    *  IntSrc:  An or'd combination of the desired status bit masks (defined in
    *           the header file)
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
    *  Returns data in RX Data register without checking status register to 
    *  determine if data is valid
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
    *  ProbeUART_rxBufferLoopDetect - creared if loop condition was detected
    *     in RX ISR. 
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 ProbeUART_ReadRxData(void) 
    {
        uint8 rxData;

        #if(ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH)

            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(ProbeUART_RX_INTERRUPT_ENABLED)
                ProbeUART_DisableRxInt();
            #endif /* End ProbeUART_RX_INTERRUPT_ENABLED */

            if( (ProbeUART_rxBufferRead != ProbeUART_rxBufferWrite) ||
                (ProbeUART_rxBufferLoopDetect > 0u) )
            {

                rxData = ProbeUART_rxBuffer[ProbeUART_rxBufferRead];

                ProbeUART_rxBufferRead++;

                if(ProbeUART_rxBufferRead >= ProbeUART_RXBUFFERSIZE)
                {
                    ProbeUART_rxBufferRead = 0u;
                }

                if(ProbeUART_rxBufferLoopDetect > 0u )
                {
                    ProbeUART_rxBufferLoopDetect = 0u;
                    #if( (ProbeUART_RX_INTERRUPT_ENABLED) && (ProbeUART_FLOW_CONTROL != 0u) && \
                         (ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH) )
                        /* When Hardware Flow Control selected - return RX mask */
                        #if( ProbeUART_HD_ENABLED )
                            if((ProbeUART_CONTROL_REG & ProbeUART_CTRL_HD_SEND) == 0)
                            {   /* In Half duplex mode return RX mask only in RX 
                                *  configuration set, otherwise 
                                *  mask will be returned in LoadRxConfig() API. 
                                */
                                ProbeUART_RXSTATUS_MASK_REG  |= ProbeUART_RX_STS_FIFO_NOTEMPTY;
                            }
                        #else
                            ProbeUART_RXSTATUS_MASK_REG  |= ProbeUART_RX_STS_FIFO_NOTEMPTY;
                        #endif /* end ProbeUART_HD_ENABLED */
                    #endif /* ProbeUART_RX_INTERRUPT_ENABLED and Hardware flow control*/
                }
            }
            else
            {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
                rxData = ProbeUART_RXDATA_REG;
            }

            /* Enable Rx interrupt. */
            #if(ProbeUART_RX_INTERRUPT_ENABLED)
                ProbeUART_EnableRxInt();
            #endif /* End ProbeUART_RX_INTERRUPT_ENABLED */

        #else /* ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH */

            /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
            rxData = ProbeUART_RXDATA_REG;

        #endif /* ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: ProbeUART_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Read the current state of the status register
    *  And detect software buffer overflow.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Global Variables:
    *  ProbeUART_rxBufferOverflow - used to indicate overload condition. 
    *   It set to one in RX interrupt when there isn?t free space in 
    *   ProbeUART_rxBufferRead to write new data. This condition returned 
    *   and cleared to zero by this API as an 
    *   ProbeUART_RX_STS_SOFT_BUFF_OVER bit along with RX Status register 
    *   bits.
    *
    *******************************************************************************/
    uint8 ProbeUART_ReadRxStatus(void) 
    {
        uint8 status;

        status = ProbeUART_RXSTATUS_REG;
        status &= ProbeUART_RX_HW_MASK;

        #if(ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH)
            if( ProbeUART_rxBufferOverflow )
            {
                status |= ProbeUART_RX_STS_SOFT_BUFF_OVER;
                ProbeUART_rxBufferOverflow = 0u;
            }
        #endif /* ProbeUART_RXBUFFERSIZE */

        return(status);
    }


    /*******************************************************************************
    * Function Name: ProbeUART_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, if data is not available or an error 
    *  condition exists, zero is returned; otherwise, character is read and 
    *  returned.
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
    *  ProbeUART_rxBufferLoopDetect - creared if loop condition was detected
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

        #if(ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH)

            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(ProbeUART_RX_INTERRUPT_ENABLED)
                ProbeUART_DisableRxInt();
            #endif /* ProbeUART_RX_INTERRUPT_ENABLED */

            if( (ProbeUART_rxBufferRead != ProbeUART_rxBufferWrite) ||
                (ProbeUART_rxBufferLoopDetect > 0u) )
            {
                rxData = ProbeUART_rxBuffer[ProbeUART_rxBufferRead];

                ProbeUART_rxBufferRead++;

                if(ProbeUART_rxBufferRead >= ProbeUART_RXBUFFERSIZE)
                {
                    ProbeUART_rxBufferRead = 0u;
                }

                if(ProbeUART_rxBufferLoopDetect > 0u ) 
                {
                    ProbeUART_rxBufferLoopDetect = 0u;
                    #if( (ProbeUART_RX_INTERRUPT_ENABLED) && (ProbeUART_FLOW_CONTROL != 0u) && \
                         (ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH) )
                        /* When Hardware Flow Control selected - return RX mask */
                        #if( ProbeUART_HD_ENABLED )
                            if((ProbeUART_CONTROL_REG & ProbeUART_CTRL_HD_SEND) == 0)
                            {   /* In Half duplex mode return RX mask only if 
                                *  RX configuration set, otherwise 
                                *  mask will be returned in LoadRxConfig() API. 
                                */
                                ProbeUART_RXSTATUS_MASK_REG  |= ProbeUART_RX_STS_FIFO_NOTEMPTY;
                            }
                        #else
                            ProbeUART_RXSTATUS_MASK_REG  |= ProbeUART_RX_STS_FIFO_NOTEMPTY;
                        #endif /* end ProbeUART_HD_ENABLED */
                    #endif /* ProbeUART_RX_INTERRUPT_ENABLED and Hardware flow control*/
                }

            }
            else
            {   rxStatus =ProbeUART_RXSTATUS_REG;
                if(rxStatus & ProbeUART_RX_STS_FIFO_NOTEMPTY)
                {   /* Read received data from FIFO*/
                    rxData = ProbeUART_RXDATA_REG;
                    /*Check status on error*/
                    if(rxStatus & (ProbeUART_RX_STS_BREAK | ProbeUART_RX_STS_PAR_ERROR |
                                   ProbeUART_RX_STS_STOP_ERROR | ProbeUART_RX_STS_OVERRUN))
                    {
                        rxData = 0u;
                    }    
                }
            }

            /* Enable Rx interrupt. */
            #if(ProbeUART_RX_INTERRUPT_ENABLED)
                ProbeUART_EnableRxInt();
            #endif /* ProbeUART_RX_INTERRUPT_ENABLED */

        #else /* ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH */

            rxStatus =ProbeUART_RXSTATUS_REG;
            if(rxStatus & ProbeUART_RX_STS_FIFO_NOTEMPTY)
            {   /* Read received data from FIFO*/
                rxData = ProbeUART_RXDATA_REG;
                /*Check status on error*/
                if(rxStatus & (ProbeUART_RX_STS_BREAK | ProbeUART_RX_STS_PAR_ERROR |
                               ProbeUART_RX_STS_STOP_ERROR | ProbeUART_RX_STS_OVERRUN))
                {
                    rxData = 0u;
                }
            }
        #endif /* ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: ProbeUART_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Grab the next available byte of data from the recieve FIFO
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains Status Register and LSB contains UART RX data
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 ProbeUART_GetByte(void) 
    {
        return ( ((uint16)ProbeUART_ReadRxStatus() << 8u) | ProbeUART_ReadRxData() );
    }


    /*******************************************************************************
    * Function Name: ProbeUART_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Determine the amount of bytes left in the RX buffer and return the count in
    *  bytes
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Integer count of the number of bytes left 
    *  in the RX buffer
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

        #if(ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH)

            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(ProbeUART_RX_INTERRUPT_ENABLED)
                ProbeUART_DisableRxInt();
            #endif /* ProbeUART_RX_INTERRUPT_ENABLED */

            if(ProbeUART_rxBufferRead == ProbeUART_rxBufferWrite)
            {
                if(ProbeUART_rxBufferLoopDetect > 0u)
                {
                    size = ProbeUART_RXBUFFERSIZE;
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
                size = (ProbeUART_RXBUFFERSIZE - ProbeUART_rxBufferRead) + ProbeUART_rxBufferWrite;
            }

            /* Enable Rx interrupt. */
            #if(ProbeUART_RX_INTERRUPT_ENABLED)
                ProbeUART_EnableRxInt();
            #endif /* End ProbeUART_RX_INTERRUPT_ENABLED */

        #else /* ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH */

            /* We can only know if there is data in the fifo. */
            size = (ProbeUART_RXSTATUS_REG & ProbeUART_RX_STS_FIFO_NOTEMPTY) ? 1u : 0u;

        #endif /* End ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH */

        return(size);
    }


    /*******************************************************************************
    * Function Name: ProbeUART_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the RX RAM buffer by setting the read and write pointers both to zero.
    *  Clears hardware RX FIFO.
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
    *******************************************************************************/
    void ProbeUART_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;
        
        /* clear the HW FIFO */
        /* Enter critical section */
        enableInterrupts = CyEnterCriticalSection();        
        ProbeUART_RXDATA_AUX_CTL_REG |=  ProbeUART_RX_FIFO_CLR;
        ProbeUART_RXDATA_AUX_CTL_REG &= ~ProbeUART_RX_FIFO_CLR;
        /* Exit critical section */
        CyExitCriticalSection(enableInterrupts);
        
        #if(ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH)
            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(ProbeUART_RX_INTERRUPT_ENABLED)
                ProbeUART_DisableRxInt();
            #endif /* End ProbeUART_RX_INTERRUPT_ENABLED */

            ProbeUART_rxBufferRead = 0u;
            ProbeUART_rxBufferWrite = 0u;
            ProbeUART_rxBufferLoopDetect = 0u;
            ProbeUART_rxBufferOverflow = 0u;

            /* Enable Rx interrupt. */
            #if(ProbeUART_RX_INTERRUPT_ENABLED)
                ProbeUART_EnableRxInt();
            #endif /* End ProbeUART_RX_INTERRUPT_ENABLED */
        #endif /* End ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH */
        
    }


    /*******************************************************************************
    * Function Name: ProbeUART_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Set the receive addressing mode
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
                addressMode = addressMode;
            #else /* ProbeUART_CONTROL_REG_REMOVED */
                uint8 tmpCtrl = 0u;
                tmpCtrl = ProbeUART_CONTROL_REG & ~ProbeUART_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= ((addressMode << ProbeUART_CTRL_RXADDR_MODE0_SHIFT) & 
                           ProbeUART_CTRL_RXADDR_MODE_MASK);
                ProbeUART_CONTROL_REG = tmpCtrl;
                #if(ProbeUART_RX_INTERRUPT_ENABLED && \
                   (ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH) )
                    ProbeUART_rxAddressMode = addressMode;
                    ProbeUART_rxAddressDetected = 0u;
                #endif /* End ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH*/   
            #endif /* End ProbeUART_CONTROL_REG_REMOVED */
        #else /* ProbeUART_RXHW_ADDRESS_ENABLED */
            addressMode = addressMode;
        #endif /* End ProbeUART_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: ProbeUART_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Set the first hardware address compare value
    *
    * Parameters:
    *  address
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
    *  Set the second hardware address compare value
    *
    * Parameters:
    *  address
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

    #if(ProbeUART_TX_INTERRUPT_ENABLED)

        /*******************************************************************************
        * Function Name: ProbeUART_EnableTxInt
        ********************************************************************************
        *
        * Summary:
        *  Enable TX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Enable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void ProbeUART_EnableTxInt(void) 
        {
            CyIntEnable(ProbeUART_TX_VECT_NUM);
        }


        /*******************************************************************************
        * Function Name: ProbeUART_DisableTxInt
        ********************************************************************************
        *
        * Summary:
        *  Disable TX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Disable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void ProbeUART_DisableTxInt(void) 
        {
            CyIntDisable(ProbeUART_TX_VECT_NUM);
        }

    #endif /* ProbeUART_TX_INTERRUPT_ENABLED */


    /*******************************************************************************
    * Function Name: ProbeUART_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configure which status bits trigger an interrupt event
    *
    * Parameters:
    *  intSrc: An or'd combination of the desired status bit masks (defined in
    *          the header file)
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
    *  Write a byte of data to the Transmit FIFO or TX buffer to be sent when the 
    *  bus is available. WriteTxData sends a byte without checking for buffer room 
    *  or status. It is up to the user to separately check status.    
    *
    * Parameters:
    *  TXDataByte: byte of data to place in the transmit FIFO
    *
    * Return:
    * void
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
            #if(ProbeUART_TXBUFFERSIZE > ProbeUART_FIFO_LENGTH)

                /* Disable Tx interrupt. */
                /* Protect variables that could change on interrupt. */
                #if(ProbeUART_TX_INTERRUPT_ENABLED)
                    ProbeUART_DisableTxInt();
                #endif /* End ProbeUART_TX_INTERRUPT_ENABLED */

                if( (ProbeUART_txBufferRead == ProbeUART_txBufferWrite) &&
                   !(ProbeUART_TXSTATUS_REG & ProbeUART_TX_STS_FIFO_FULL) )
                {
                    /* Add directly to the FIFO. */
                    ProbeUART_TXDATA_REG = txDataByte;
                }
                else
                {
                    if(ProbeUART_txBufferWrite >= ProbeUART_TXBUFFERSIZE)
                    {
                        ProbeUART_txBufferWrite = 0;
                    }

                    ProbeUART_txBuffer[ProbeUART_txBufferWrite] = txDataByte;

                    /* Add to the software buffer. */
                    ProbeUART_txBufferWrite++;

                }

                /* Enable Tx interrupt. */
                #if(ProbeUART_TX_INTERRUPT_ENABLED)
                    ProbeUART_EnableTxInt();
                #endif /* End ProbeUART_TX_INTERRUPT_ENABLED */

            #else /* ProbeUART_TXBUFFERSIZE > ProbeUART_FIFO_LENGTH */

                /* Add directly to the FIFO. */
                ProbeUART_TXDATA_REG = txDataByte;

            #endif /* End ProbeUART_TXBUFFERSIZE > ProbeUART_FIFO_LENGTH */
        }
    }


    /*******************************************************************************
    * Function Name: ProbeUART_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Read the status register for the component
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the status register which is clear on read. It is up to 
    *  the user to handle all bits in this return value accordingly, even if the bit 
    *  was not enabled as an interrupt source the event happened and must be handled
    *  accordingly.    
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
    *  Wait to send byte until TX register or buffer has room.
    *
    * Parameters:
    *  txDataByte: The 8-bit data value to send across the UART.
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
            #if(ProbeUART_TXBUFFERSIZE > ProbeUART_FIFO_LENGTH)

                /* Block if buffer is full, so we dont overwrite. */
                while( ProbeUART_txBufferWrite == (ProbeUART_txBufferRead - 1u) ||
                    (uint8)(ProbeUART_txBufferWrite - ProbeUART_txBufferRead) ==
                    (uint8)(ProbeUART_TXBUFFERSIZE - 1u) )
                {
                    /* Software buffer is full. */
                }
                /* Disable Tx interrupt. */
                /* Protect variables that could change on interrupt. */
                #if(ProbeUART_TX_INTERRUPT_ENABLED)
                    ProbeUART_DisableTxInt();
                #endif /* End ProbeUART_TX_INTERRUPT_ENABLED */

                if( (ProbeUART_txBufferRead == ProbeUART_txBufferWrite) &&
                   !(ProbeUART_TXSTATUS_REG & ProbeUART_TX_STS_FIFO_FULL) )
                {
                    /* Add directly to the FIFO. */
                    ProbeUART_TXDATA_REG = txDataByte;
                }
                else
                {
                    if(ProbeUART_txBufferWrite >= ProbeUART_TXBUFFERSIZE)
                    {
                        ProbeUART_txBufferWrite = 0;
                    }

                    ProbeUART_txBuffer[ProbeUART_txBufferWrite] = txDataByte;

                    /* Add to the software buffer. */
                    ProbeUART_txBufferWrite++;

                }

                /* Enable Rx interrupt. */
                #if(ProbeUART_TX_INTERRUPT_ENABLED)
                    ProbeUART_EnableTxInt();
                #endif /* End ProbeUART_TX_INTERRUPT_ENABLED */

            #else /* ProbeUART_TXBUFFERSIZE > ProbeUART_FIFO_LENGTH */

                /* Block if there isnt room. */
                while(ProbeUART_TXSTATUS_REG & ProbeUART_TX_STS_FIFO_FULL);

                /* Add directly to the FIFO. */
                ProbeUART_TXDATA_REG = txDataByte;

            #endif /* End ProbeUART_TXBUFFERSIZE > ProbeUART_FIFO_LENGTH */
    }


    /*******************************************************************************
    * Function Name: ProbeUART_PutString
    ********************************************************************************
    *
    * Summary:
    *  Write a Sequence of bytes on the Transmit line. Data comes from RAM or ROM.
    *
    * Parameters:
    *  string: char pointer to character string of Data to Send.
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
    *  This function will block if there is not enough memory to place the whole 
    *  string, it will block until the entire string has been written to the 
    *  transmit buffer.
    *
    *******************************************************************************/
    void ProbeUART_PutString(char* string) 
    {
        /* If not Initialized then skip this function*/
        if(ProbeUART_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent*/
            while(*string != 0u)
            {
                ProbeUART_PutChar(*string++);
            }
        }
    }


    /*******************************************************************************
    * Function Name: ProbeUART_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Write a Sequence of bytes on the Transmit line. Data comes from RAM or ROM.
    *
    * Parameters:
    *  string: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of Bytes to be transmitted.
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
    void ProbeUART_PutArray(uint8* string, uint8 byteCount) 
                                                                    
    {
        /* If not Initialized then skip this function*/
        if(ProbeUART_initVar != 0u)
        {
            while(byteCount > 0u)
            {
                ProbeUART_PutChar(*string++);
                byteCount--;
            }
        }
    }


    /*******************************************************************************
    * Function Name: ProbeUART_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Write a character and then carriage return and line feed.
    *
    * Parameters:
    *  txDataByte: uint8 Character to send.
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
        /* If not Initialized then skip this function*/
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
    *  Determine the amount of space left in the TX buffer and return the count in
    *  bytes
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Integer count of the number of bytes left in the TX buffer
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

        #if(ProbeUART_TXBUFFERSIZE > ProbeUART_FIFO_LENGTH)

            /* Disable Tx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(ProbeUART_TX_INTERRUPT_ENABLED)
                ProbeUART_DisableTxInt();
            #endif /* End ProbeUART_TX_INTERRUPT_ENABLED */

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
                size = (ProbeUART_TXBUFFERSIZE - ProbeUART_txBufferRead) + ProbeUART_txBufferWrite;
            }

            /* Enable Tx interrupt. */
            #if(ProbeUART_TX_INTERRUPT_ENABLED)
                ProbeUART_EnableTxInt();
            #endif /* End ProbeUART_TX_INTERRUPT_ENABLED */

        #else /* ProbeUART_TXBUFFERSIZE > ProbeUART_FIFO_LENGTH */

            size = ProbeUART_TXSTATUS_REG;

            /* Is the fifo is full. */
            if(size & ProbeUART_TX_STS_FIFO_FULL)
            {
                size = ProbeUART_FIFO_LENGTH;
            }
            else if(size & ProbeUART_TX_STS_FIFO_EMPTY)
            {
                size = 0u;
            }
            else
            {
                /* We only know there is data in the fifo. */
                size = 1u;
            }

        #endif /* End ProbeUART_TXBUFFERSIZE > ProbeUART_FIFO_LENGTH */

        return(size);
    }


    /*******************************************************************************
    * Function Name: ProbeUART_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the TX RAM buffer by setting the read and write pointers both to zero.
    *  Clears the hardware TX FIFO.  Any data present in the FIFO will not be sent.
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
    *  Any received data not read from the RAM buffer will be lost when overwritten.
    *
    *******************************************************************************/
    void ProbeUART_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;
        
        /* Enter critical section */
        enableInterrupts = CyEnterCriticalSection();        
        /* clear the HW FIFO */
        ProbeUART_TXDATA_AUX_CTL_REG |=  ProbeUART_TX_FIFO_CLR;
        ProbeUART_TXDATA_AUX_CTL_REG &= ~ProbeUART_TX_FIFO_CLR;
        /* Exit critical section */
        CyExitCriticalSection(enableInterrupts);

        #if(ProbeUART_TXBUFFERSIZE > ProbeUART_FIFO_LENGTH)

            /* Disable Tx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(ProbeUART_TX_INTERRUPT_ENABLED)
                ProbeUART_DisableTxInt();
            #endif /* End ProbeUART_TX_INTERRUPT_ENABLED */

            ProbeUART_txBufferRead = 0u;
            ProbeUART_txBufferWrite = 0u;

            /* Enable Tx interrupt. */
            #if(ProbeUART_TX_INTERRUPT_ENABLED)
                ProbeUART_EnableTxInt();
            #endif /* End ProbeUART_TX_INTERRUPT_ENABLED */

        #endif /* End ProbeUART_TXBUFFERSIZE > ProbeUART_FIFO_LENGTH */
    }


    /*******************************************************************************
    * Function Name: ProbeUART_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Write a Break command to the UART
    *
    * Parameters:
    *  uint8 retMode:  Wait mode,
    *   0 - Initialize registers for Break, sends the Break signal and return 
    *       imediately.
    *   1 - Wait until Break sending is complete, reinitialize registers to normal
    *       transmission mode then return.
    *   2 - Reinitialize registers to normal transmission mode then return.
    *   3 - both steps: 0 and 1
    *       init registers for Break, send Break signal
    *       wait until Break sending is complete, reinit registers to normal
    *       transmission mode then return.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  ProbeUART_initVar - checked to identify that the component has been  
    *     initialized.
    *  tx_period - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  Trere are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Funcition will block CPU untill transmition 
    *     complete.
    *  2) User may want to use bloking time if UART configured to the low speed 
    *     operation
    *     Emample for this case:
    *     SendBreak(0);     - init Break signal transmition
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to init and use the interrupt for complete 
    *     break operation.
    *     Example for this case:
    *     Init TX interrupt whith "TX - On TX Complete" parameter
    *     SendBreak(0);     - init Break signal transmition
    *         Add your code here to use CPU time
    *     When interrupt appear with UART_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *   Uses static variable to keep registers configuration.
    *
    *******************************************************************************/
    void ProbeUART_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(ProbeUART_initVar != 0u)
        {
            /*Set the Counter to 13-bits and transmit a 00 byte*/
            /*When that is done then reset the counter value back*/
            uint8 tmpStat;

            #if(ProbeUART_HD_ENABLED) /* Half Duplex mode*/

                if( (retMode == ProbeUART_SEND_BREAK) ||
                    (retMode == ProbeUART_SEND_WAIT_REINIT ) )
                {
                    /* CTRL_HD_SEND_BREAK - sends break bits in HD mode*/
                    ProbeUART_WriteControlRegister(ProbeUART_ReadControlRegister() |
                                                          ProbeUART_CTRL_HD_SEND_BREAK);
                    /* Send zeros*/
                    ProbeUART_TXDATA_REG = 0u;

                    do /*wait until transmit starts*/
                    {
                        tmpStat = ProbeUART_TXSTATUS_REG;
                    }while(tmpStat & ProbeUART_TX_STS_FIFO_EMPTY);
                }

                if( (retMode == ProbeUART_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == ProbeUART_SEND_WAIT_REINIT) )
                {
                    do /*wait until transmit complete*/
                    {
                        tmpStat = ProbeUART_TXSTATUS_REG;
                    }while(~tmpStat & ProbeUART_TX_STS_COMPLETE);
                }

                if( (retMode == ProbeUART_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == ProbeUART_REINIT) ||
                    (retMode == ProbeUART_SEND_WAIT_REINIT) )
                {
                    ProbeUART_WriteControlRegister(ProbeUART_ReadControlRegister() &
                                                         ~ProbeUART_CTRL_HD_SEND_BREAK);
                }

            #else /* ProbeUART_HD_ENABLED Full Duplex mode */

                static uint8 tx_period; 
                
                if( (retMode == ProbeUART_SEND_BREAK) ||
                    (retMode == ProbeUART_SEND_WAIT_REINIT) )
                {
                    /* CTRL_HD_SEND_BREAK - skip to send parity bit @ Break signal in Full Duplex mode*/
                    if( (ProbeUART_PARITY_TYPE != ProbeUART__B_UART__NONE_REVB) ||
                         ProbeUART_PARITY_TYPE_SW )
                    {
                        ProbeUART_WriteControlRegister(ProbeUART_ReadControlRegister() |
                                                              ProbeUART_CTRL_HD_SEND_BREAK);
                    }                                                          

                    #if(ProbeUART_TXCLKGEN_DP)
                        tx_period = ProbeUART_TXBITCLKTX_COMPLETE_REG;
                        ProbeUART_TXBITCLKTX_COMPLETE_REG = ProbeUART_TXBITCTR_BREAKBITS;
                    #else
                        tx_period = ProbeUART_TXBITCTR_PERIOD_REG;
                        ProbeUART_TXBITCTR_PERIOD_REG = ProbeUART_TXBITCTR_BREAKBITS8X;
                    #endif /* End ProbeUART_TXCLKGEN_DP */

                    /* Send zeros*/
                    ProbeUART_TXDATA_REG = 0u;

                    do /*wait until transmit starts*/
                    {
                        tmpStat = ProbeUART_TXSTATUS_REG;
                    }while(tmpStat & ProbeUART_TX_STS_FIFO_EMPTY);
                }

                if( (retMode == ProbeUART_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == ProbeUART_SEND_WAIT_REINIT) )
                {
                    do /*wait until transmit complete*/
                    {
                        tmpStat = ProbeUART_TXSTATUS_REG;
                    }while(~tmpStat & ProbeUART_TX_STS_COMPLETE);
                }

                if( (retMode == ProbeUART_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == ProbeUART_REINIT) ||
                    (retMode == ProbeUART_SEND_WAIT_REINIT) )
                {

                    #if(ProbeUART_TXCLKGEN_DP)
                        ProbeUART_TXBITCLKTX_COMPLETE_REG = tx_period;
                    #else
                        ProbeUART_TXBITCTR_PERIOD_REG = tx_period;
                    #endif /* End ProbeUART_TXCLKGEN_DP */

                    if( (ProbeUART_PARITY_TYPE != ProbeUART__B_UART__NONE_REVB) || 
                         ProbeUART_PARITY_TYPE_SW )
                    {
                        ProbeUART_WriteControlRegister(ProbeUART_ReadControlRegister() &
                                                             ~ProbeUART_CTRL_HD_SEND_BREAK);
                    }                                     
                }
            #endif    /* End ProbeUART_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: ProbeUART_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Set the transmit addressing mode
    *
    * Parameters:
    *  addressMode: 0 -> Space
    *               1 -> Mark
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void ProbeUART_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable*/
        if(addressMode != 0)
        {
            ProbeUART_WriteControlRegister(ProbeUART_ReadControlRegister() | ProbeUART_CTRL_MARK);
        }
        else
        {
            ProbeUART_WriteControlRegister(ProbeUART_ReadControlRegister() & ~ProbeUART_CTRL_MARK);
        }
    }

#endif  /* EndProbeUART_TX_ENABLED */

#if(ProbeUART_HD_ENABLED)


    /*******************************************************************************
    * Function Name: ProbeUART_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Unloads the Rx configuration if required and loads the
    *  Tx configuration. It is the users responsibility to ensure that any
    *  transaction is complete and it is safe to unload the Tx
    *  configuration.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Valid only for half duplex UART. 
    *
    * Side Effects:
    *  Disable RX interrupt mask, when software buffer has been used.
    *
    *******************************************************************************/
    void ProbeUART_LoadTxConfig(void) 
    {
        #if((ProbeUART_RX_INTERRUPT_ENABLED) && (ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH))
            /* Disable RX interrupts before set TX configuration */
            ProbeUART_SetRxInterruptMode(0);
        #endif /* ProbeUART_RX_INTERRUPT_ENABLED */

        ProbeUART_WriteControlRegister(ProbeUART_ReadControlRegister() | ProbeUART_CTRL_HD_SEND);
        ProbeUART_RXBITCTR_PERIOD_REG = ProbeUART_HD_TXBITCTR_INIT;
        #if(CY_UDB_V0) /* Manually clear status register when mode has been changed */
            /* Clear status register */
            CY_GET_REG8(ProbeUART_RXSTATUS_PTR);
        #endif /* CY_UDB_V0 */
    }


    /*******************************************************************************
    * Function Name: ProbeUART_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Unloads the Tx configuration if required and loads the
    *  Rx configuration. It is the users responsibility to ensure that any
    *  transaction is complete and it is safe to unload the Rx
    *  configuration.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Valid only for half duplex UART
    *
    * Side Effects:
    *  Set RX interrupt mask based on customizer settings, when software buffer 
    *  has been used.
    *
    *******************************************************************************/
    void ProbeUART_LoadRxConfig(void) 
    {
        ProbeUART_WriteControlRegister(ProbeUART_ReadControlRegister() & ~ProbeUART_CTRL_HD_SEND);
        ProbeUART_RXBITCTR_PERIOD_REG = ProbeUART_HD_RXBITCTR_INIT;
        #if(CY_UDB_V0) /* Manually clear status register when mode has been changed */
            /* Clear status register */
            CY_GET_REG8(ProbeUART_RXSTATUS_PTR);
        #endif /* CY_UDB_V0 */

        #if((ProbeUART_RX_INTERRUPT_ENABLED) && (ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH))
            /* Enable RX interrupt after set RX configuration */
            ProbeUART_SetRxInterruptMode(ProbeUART_INIT_RX_INTERRUPTS_MASK);    
        #endif /* ProbeUART_RX_INTERRUPT_ENABLED */
    }

#endif  /* ProbeUART_HD_ENABLED */


/* [] END OF FILE */
