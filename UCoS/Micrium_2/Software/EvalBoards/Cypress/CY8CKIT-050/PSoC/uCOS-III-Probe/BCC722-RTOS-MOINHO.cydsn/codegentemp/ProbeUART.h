/*******************************************************************************
* File Name: ProbeUART.h
* Version 2.50
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_ProbeUART_H)
#define CY_UART_ProbeUART_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define ProbeUART_RX_ENABLED                     (1u)
#define ProbeUART_TX_ENABLED                     (1u)
#define ProbeUART_HD_ENABLED                     (0u)
#define ProbeUART_RX_INTERRUPT_ENABLED           (0u)
#define ProbeUART_TX_INTERRUPT_ENABLED           (0u)
#define ProbeUART_INTERNAL_CLOCK_USED            (1u)
#define ProbeUART_RXHW_ADDRESS_ENABLED           (0u)
#define ProbeUART_OVER_SAMPLE_COUNT              (8u)
#define ProbeUART_PARITY_TYPE                    (0u)
#define ProbeUART_PARITY_TYPE_SW                 (0u)
#define ProbeUART_BREAK_DETECT                   (0u)
#define ProbeUART_BREAK_BITS_TX                  (13u)
#define ProbeUART_BREAK_BITS_RX                  (13u)
#define ProbeUART_TXCLKGEN_DP                    (1u)
#define ProbeUART_USE23POLLING                   (1u)
#define ProbeUART_FLOW_CONTROL                   (0u)
#define ProbeUART_CLK_FREQ                       (0u)
#define ProbeUART_TX_BUFFER_SIZE                 (4u)
#define ProbeUART_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(ProbeUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define ProbeUART_CONTROL_REG_REMOVED            (0u)
#else
    #define ProbeUART_CONTROL_REG_REMOVED            (1u)
#endif /* End ProbeUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct ProbeUART_backupStruct_
{
    uint8 enableState;

    #if(ProbeUART_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End ProbeUART_CONTROL_REG_REMOVED */

} ProbeUART_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void ProbeUART_Start(void) ;
void ProbeUART_Stop(void) ;
uint8 ProbeUART_ReadControlRegister(void) ;
void ProbeUART_WriteControlRegister(uint8 control) ;

void ProbeUART_Init(void) ;
void ProbeUART_Enable(void) ;
void ProbeUART_SaveConfig(void) ;
void ProbeUART_RestoreConfig(void) ;
void ProbeUART_Sleep(void) ;
void ProbeUART_Wakeup(void) ;

/* Only if RX is enabled */
#if( (ProbeUART_RX_ENABLED) || (ProbeUART_HD_ENABLED) )

    #if (ProbeUART_RX_INTERRUPT_ENABLED)
        #define ProbeUART_EnableRxInt()  CyIntEnable (ProbeUART_RX_VECT_NUM)
        #define ProbeUART_DisableRxInt() CyIntDisable(ProbeUART_RX_VECT_NUM)
        CY_ISR_PROTO(ProbeUART_RXISR);
    #endif /* ProbeUART_RX_INTERRUPT_ENABLED */

    void ProbeUART_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void ProbeUART_SetRxAddress1(uint8 address) ;
    void ProbeUART_SetRxAddress2(uint8 address) ;

    void  ProbeUART_SetRxInterruptMode(uint8 intSrc) ;
    uint8 ProbeUART_ReadRxData(void) ;
    uint8 ProbeUART_ReadRxStatus(void) ;
    uint8 ProbeUART_GetChar(void) ;
    uint16 ProbeUART_GetByte(void) ;
    uint8 ProbeUART_GetRxBufferSize(void)
                                                            ;
    void ProbeUART_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define ProbeUART_GetRxInterruptSource   ProbeUART_ReadRxStatus

#endif /* End (ProbeUART_RX_ENABLED) || (ProbeUART_HD_ENABLED) */

/* Only if TX is enabled */
#if(ProbeUART_TX_ENABLED || ProbeUART_HD_ENABLED)

    #if(ProbeUART_TX_INTERRUPT_ENABLED)
        #define ProbeUART_EnableTxInt()  CyIntEnable (ProbeUART_TX_VECT_NUM)
        #define ProbeUART_DisableTxInt() CyIntDisable(ProbeUART_TX_VECT_NUM)
        #define ProbeUART_SetPendingTxInt() CyIntSetPending(ProbeUART_TX_VECT_NUM)
        #define ProbeUART_ClearPendingTxInt() CyIntClearPending(ProbeUART_TX_VECT_NUM)
        CY_ISR_PROTO(ProbeUART_TXISR);
    #endif /* ProbeUART_TX_INTERRUPT_ENABLED */

    void ProbeUART_SetTxInterruptMode(uint8 intSrc) ;
    void ProbeUART_WriteTxData(uint8 txDataByte) ;
    uint8 ProbeUART_ReadTxStatus(void) ;
    void ProbeUART_PutChar(uint8 txDataByte) ;
    void ProbeUART_PutString(const char8 string[]) ;
    void ProbeUART_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void ProbeUART_PutCRLF(uint8 txDataByte) ;
    void ProbeUART_ClearTxBuffer(void) ;
    void ProbeUART_SetTxAddressMode(uint8 addressMode) ;
    void ProbeUART_SendBreak(uint8 retMode) ;
    uint8 ProbeUART_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define ProbeUART_PutStringConst         ProbeUART_PutString
    #define ProbeUART_PutArrayConst          ProbeUART_PutArray
    #define ProbeUART_GetTxInterruptSource   ProbeUART_ReadTxStatus

#endif /* End ProbeUART_TX_ENABLED || ProbeUART_HD_ENABLED */

#if(ProbeUART_HD_ENABLED)
    void ProbeUART_LoadRxConfig(void) ;
    void ProbeUART_LoadTxConfig(void) ;
#endif /* End ProbeUART_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ProbeUART) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    ProbeUART_CyBtldrCommStart(void) CYSMALL ;
    void    ProbeUART_CyBtldrCommStop(void) CYSMALL ;
    void    ProbeUART_CyBtldrCommReset(void) CYSMALL ;
    cystatus ProbeUART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus ProbeUART_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ProbeUART)
        #define CyBtldrCommStart    ProbeUART_CyBtldrCommStart
        #define CyBtldrCommStop     ProbeUART_CyBtldrCommStop
        #define CyBtldrCommReset    ProbeUART_CyBtldrCommReset
        #define CyBtldrCommWrite    ProbeUART_CyBtldrCommWrite
        #define CyBtldrCommRead     ProbeUART_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ProbeUART) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define ProbeUART_BYTE2BYTE_TIME_OUT (25u)
    #define ProbeUART_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define ProbeUART_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define ProbeUART_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define ProbeUART_SET_SPACE      (0x00u)
#define ProbeUART_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (ProbeUART_TX_ENABLED) || (ProbeUART_HD_ENABLED) )
    #if(ProbeUART_TX_INTERRUPT_ENABLED)
        #define ProbeUART_TX_VECT_NUM            (uint8)ProbeUART_TXInternalInterrupt__INTC_NUMBER
        #define ProbeUART_TX_PRIOR_NUM           (uint8)ProbeUART_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* ProbeUART_TX_INTERRUPT_ENABLED */

    #define ProbeUART_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define ProbeUART_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define ProbeUART_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(ProbeUART_TX_ENABLED)
        #define ProbeUART_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (ProbeUART_HD_ENABLED) */
        #define ProbeUART_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (ProbeUART_TX_ENABLED) */

    #define ProbeUART_TX_STS_COMPLETE            (uint8)(0x01u << ProbeUART_TX_STS_COMPLETE_SHIFT)
    #define ProbeUART_TX_STS_FIFO_EMPTY          (uint8)(0x01u << ProbeUART_TX_STS_FIFO_EMPTY_SHIFT)
    #define ProbeUART_TX_STS_FIFO_FULL           (uint8)(0x01u << ProbeUART_TX_STS_FIFO_FULL_SHIFT)
    #define ProbeUART_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << ProbeUART_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (ProbeUART_TX_ENABLED) || (ProbeUART_HD_ENABLED)*/

#if( (ProbeUART_RX_ENABLED) || (ProbeUART_HD_ENABLED) )
    #if(ProbeUART_RX_INTERRUPT_ENABLED)
        #define ProbeUART_RX_VECT_NUM            (uint8)ProbeUART_RXInternalInterrupt__INTC_NUMBER
        #define ProbeUART_RX_PRIOR_NUM           (uint8)ProbeUART_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* ProbeUART_RX_INTERRUPT_ENABLED */
    #define ProbeUART_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define ProbeUART_RX_STS_BREAK_SHIFT             (0x01u)
    #define ProbeUART_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define ProbeUART_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define ProbeUART_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define ProbeUART_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define ProbeUART_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define ProbeUART_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define ProbeUART_RX_STS_MRKSPC           (uint8)(0x01u << ProbeUART_RX_STS_MRKSPC_SHIFT)
    #define ProbeUART_RX_STS_BREAK            (uint8)(0x01u << ProbeUART_RX_STS_BREAK_SHIFT)
    #define ProbeUART_RX_STS_PAR_ERROR        (uint8)(0x01u << ProbeUART_RX_STS_PAR_ERROR_SHIFT)
    #define ProbeUART_RX_STS_STOP_ERROR       (uint8)(0x01u << ProbeUART_RX_STS_STOP_ERROR_SHIFT)
    #define ProbeUART_RX_STS_OVERRUN          (uint8)(0x01u << ProbeUART_RX_STS_OVERRUN_SHIFT)
    #define ProbeUART_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << ProbeUART_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define ProbeUART_RX_STS_ADDR_MATCH       (uint8)(0x01u << ProbeUART_RX_STS_ADDR_MATCH_SHIFT)
    #define ProbeUART_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << ProbeUART_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define ProbeUART_RX_HW_MASK                     (0x7Fu)
#endif /* End (ProbeUART_RX_ENABLED) || (ProbeUART_HD_ENABLED) */

/* Control Register definitions */
#define ProbeUART_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define ProbeUART_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define ProbeUART_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define ProbeUART_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define ProbeUART_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define ProbeUART_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define ProbeUART_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define ProbeUART_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define ProbeUART_CTRL_HD_SEND               (uint8)(0x01u << ProbeUART_CTRL_HD_SEND_SHIFT)
#define ProbeUART_CTRL_HD_SEND_BREAK         (uint8)(0x01u << ProbeUART_CTRL_HD_SEND_BREAK_SHIFT)
#define ProbeUART_CTRL_MARK                  (uint8)(0x01u << ProbeUART_CTRL_MARK_SHIFT)
#define ProbeUART_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << ProbeUART_CTRL_PARITY_TYPE0_SHIFT)
#define ProbeUART_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << ProbeUART_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define ProbeUART_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define ProbeUART_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define ProbeUART_SEND_BREAK                         (0x00u)
#define ProbeUART_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define ProbeUART_REINIT                             (0x02u)
#define ProbeUART_SEND_WAIT_REINIT                   (0x03u)

#define ProbeUART_OVER_SAMPLE_8                      (8u)
#define ProbeUART_OVER_SAMPLE_16                     (16u)

#define ProbeUART_BIT_CENTER                         (ProbeUART_OVER_SAMPLE_COUNT - 2u)

#define ProbeUART_FIFO_LENGTH                        (4u)
#define ProbeUART_NUMBER_OF_START_BIT                (1u)
#define ProbeUART_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define ProbeUART_TXBITCTR_BREAKBITS8X   ((ProbeUART_BREAK_BITS_TX * ProbeUART_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define ProbeUART_TXBITCTR_BREAKBITS ((ProbeUART_BREAK_BITS_TX * ProbeUART_OVER_SAMPLE_COUNT) - 1u)

#define ProbeUART_HALF_BIT_COUNT   \
                            (((ProbeUART_OVER_SAMPLE_COUNT / 2u) + (ProbeUART_USE23POLLING * 1u)) - 2u)
#if (ProbeUART_OVER_SAMPLE_COUNT == ProbeUART_OVER_SAMPLE_8)
    #define ProbeUART_HD_TXBITCTR_INIT   (((ProbeUART_BREAK_BITS_TX + \
                            ProbeUART_NUMBER_OF_START_BIT) * ProbeUART_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define ProbeUART_RXBITCTR_INIT  ((((ProbeUART_BREAK_BITS_RX + ProbeUART_NUMBER_OF_START_BIT) \
                            * ProbeUART_OVER_SAMPLE_COUNT) + ProbeUART_HALF_BIT_COUNT) - 1u)

#else /* ProbeUART_OVER_SAMPLE_COUNT == ProbeUART_OVER_SAMPLE_16 */
    #define ProbeUART_HD_TXBITCTR_INIT   ((8u * ProbeUART_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define ProbeUART_RXBITCTR_INIT      (((7u * ProbeUART_OVER_SAMPLE_COUNT) - 1u) + \
                                                      ProbeUART_HALF_BIT_COUNT)
#endif /* End ProbeUART_OVER_SAMPLE_COUNT */

#define ProbeUART_HD_RXBITCTR_INIT                   ProbeUART_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 ProbeUART_initVar;
#if (ProbeUART_TX_INTERRUPT_ENABLED && ProbeUART_TX_ENABLED)
    extern volatile uint8 ProbeUART_txBuffer[ProbeUART_TX_BUFFER_SIZE];
    extern volatile uint8 ProbeUART_txBufferRead;
    extern uint8 ProbeUART_txBufferWrite;
#endif /* (ProbeUART_TX_INTERRUPT_ENABLED && ProbeUART_TX_ENABLED) */
#if (ProbeUART_RX_INTERRUPT_ENABLED && (ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED))
    extern uint8 ProbeUART_errorStatus;
    extern volatile uint8 ProbeUART_rxBuffer[ProbeUART_RX_BUFFER_SIZE];
    extern volatile uint8 ProbeUART_rxBufferRead;
    extern volatile uint8 ProbeUART_rxBufferWrite;
    extern volatile uint8 ProbeUART_rxBufferLoopDetect;
    extern volatile uint8 ProbeUART_rxBufferOverflow;
    #if (ProbeUART_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 ProbeUART_rxAddressMode;
        extern volatile uint8 ProbeUART_rxAddressDetected;
    #endif /* (ProbeUART_RXHW_ADDRESS_ENABLED) */
#endif /* (ProbeUART_RX_INTERRUPT_ENABLED && (ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define ProbeUART__B_UART__AM_SW_BYTE_BYTE 1
#define ProbeUART__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define ProbeUART__B_UART__AM_HW_BYTE_BY_BYTE 3
#define ProbeUART__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define ProbeUART__B_UART__AM_NONE 0

#define ProbeUART__B_UART__NONE_REVB 0
#define ProbeUART__B_UART__EVEN_REVB 1
#define ProbeUART__B_UART__ODD_REVB 2
#define ProbeUART__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define ProbeUART_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define ProbeUART_NUMBER_OF_STOP_BITS    (1u)

#if (ProbeUART_RXHW_ADDRESS_ENABLED)
    #define ProbeUART_RX_ADDRESS_MODE    (0u)
    #define ProbeUART_RX_HW_ADDRESS1     (0u)
    #define ProbeUART_RX_HW_ADDRESS2     (0u)
#endif /* (ProbeUART_RXHW_ADDRESS_ENABLED) */

#define ProbeUART_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << ProbeUART_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << ProbeUART_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << ProbeUART_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << ProbeUART_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << ProbeUART_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << ProbeUART_RX_STS_BREAK_SHIFT) \
                                        | (0 << ProbeUART_RX_STS_OVERRUN_SHIFT))

#define ProbeUART_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((1 << ProbeUART_TX_STS_COMPLETE_SHIFT) \
                                        | (1 << ProbeUART_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << ProbeUART_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << ProbeUART_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef ProbeUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define ProbeUART_CONTROL_REG \
                            (* (reg8 *) ProbeUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define ProbeUART_CONTROL_PTR \
                            (  (reg8 *) ProbeUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End ProbeUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(ProbeUART_TX_ENABLED)
    #define ProbeUART_TXDATA_REG          (* (reg8 *) ProbeUART_BUART_sTX_TxShifter_u0__F0_REG)
    #define ProbeUART_TXDATA_PTR          (  (reg8 *) ProbeUART_BUART_sTX_TxShifter_u0__F0_REG)
    #define ProbeUART_TXDATA_AUX_CTL_REG  (* (reg8 *) ProbeUART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define ProbeUART_TXDATA_AUX_CTL_PTR  (  (reg8 *) ProbeUART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define ProbeUART_TXSTATUS_REG        (* (reg8 *) ProbeUART_BUART_sTX_TxSts__STATUS_REG)
    #define ProbeUART_TXSTATUS_PTR        (  (reg8 *) ProbeUART_BUART_sTX_TxSts__STATUS_REG)
    #define ProbeUART_TXSTATUS_MASK_REG   (* (reg8 *) ProbeUART_BUART_sTX_TxSts__MASK_REG)
    #define ProbeUART_TXSTATUS_MASK_PTR   (  (reg8 *) ProbeUART_BUART_sTX_TxSts__MASK_REG)
    #define ProbeUART_TXSTATUS_ACTL_REG   (* (reg8 *) ProbeUART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define ProbeUART_TXSTATUS_ACTL_PTR   (  (reg8 *) ProbeUART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(ProbeUART_TXCLKGEN_DP)
        #define ProbeUART_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) ProbeUART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define ProbeUART_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) ProbeUART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define ProbeUART_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) ProbeUART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define ProbeUART_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) ProbeUART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define ProbeUART_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) ProbeUART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define ProbeUART_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) ProbeUART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define ProbeUART_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) ProbeUART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define ProbeUART_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) ProbeUART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define ProbeUART_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) ProbeUART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define ProbeUART_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) ProbeUART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* ProbeUART_TXCLKGEN_DP */

#endif /* End ProbeUART_TX_ENABLED */

#if(ProbeUART_HD_ENABLED)

    #define ProbeUART_TXDATA_REG             (* (reg8 *) ProbeUART_BUART_sRX_RxShifter_u0__F1_REG )
    #define ProbeUART_TXDATA_PTR             (  (reg8 *) ProbeUART_BUART_sRX_RxShifter_u0__F1_REG )
    #define ProbeUART_TXDATA_AUX_CTL_REG     (* (reg8 *) ProbeUART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define ProbeUART_TXDATA_AUX_CTL_PTR     (  (reg8 *) ProbeUART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define ProbeUART_TXSTATUS_REG           (* (reg8 *) ProbeUART_BUART_sRX_RxSts__STATUS_REG )
    #define ProbeUART_TXSTATUS_PTR           (  (reg8 *) ProbeUART_BUART_sRX_RxSts__STATUS_REG )
    #define ProbeUART_TXSTATUS_MASK_REG      (* (reg8 *) ProbeUART_BUART_sRX_RxSts__MASK_REG )
    #define ProbeUART_TXSTATUS_MASK_PTR      (  (reg8 *) ProbeUART_BUART_sRX_RxSts__MASK_REG )
    #define ProbeUART_TXSTATUS_ACTL_REG      (* (reg8 *) ProbeUART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define ProbeUART_TXSTATUS_ACTL_PTR      (  (reg8 *) ProbeUART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End ProbeUART_HD_ENABLED */

#if( (ProbeUART_RX_ENABLED) || (ProbeUART_HD_ENABLED) )
    #define ProbeUART_RXDATA_REG             (* (reg8 *) ProbeUART_BUART_sRX_RxShifter_u0__F0_REG )
    #define ProbeUART_RXDATA_PTR             (  (reg8 *) ProbeUART_BUART_sRX_RxShifter_u0__F0_REG )
    #define ProbeUART_RXADDRESS1_REG         (* (reg8 *) ProbeUART_BUART_sRX_RxShifter_u0__D0_REG )
    #define ProbeUART_RXADDRESS1_PTR         (  (reg8 *) ProbeUART_BUART_sRX_RxShifter_u0__D0_REG )
    #define ProbeUART_RXADDRESS2_REG         (* (reg8 *) ProbeUART_BUART_sRX_RxShifter_u0__D1_REG )
    #define ProbeUART_RXADDRESS2_PTR         (  (reg8 *) ProbeUART_BUART_sRX_RxShifter_u0__D1_REG )
    #define ProbeUART_RXDATA_AUX_CTL_REG     (* (reg8 *) ProbeUART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define ProbeUART_RXBITCTR_PERIOD_REG    (* (reg8 *) ProbeUART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define ProbeUART_RXBITCTR_PERIOD_PTR    (  (reg8 *) ProbeUART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define ProbeUART_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) ProbeUART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define ProbeUART_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) ProbeUART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define ProbeUART_RXBITCTR_COUNTER_REG   (* (reg8 *) ProbeUART_BUART_sRX_RxBitCounter__COUNT_REG )
    #define ProbeUART_RXBITCTR_COUNTER_PTR   (  (reg8 *) ProbeUART_BUART_sRX_RxBitCounter__COUNT_REG )

    #define ProbeUART_RXSTATUS_REG           (* (reg8 *) ProbeUART_BUART_sRX_RxSts__STATUS_REG )
    #define ProbeUART_RXSTATUS_PTR           (  (reg8 *) ProbeUART_BUART_sRX_RxSts__STATUS_REG )
    #define ProbeUART_RXSTATUS_MASK_REG      (* (reg8 *) ProbeUART_BUART_sRX_RxSts__MASK_REG )
    #define ProbeUART_RXSTATUS_MASK_PTR      (  (reg8 *) ProbeUART_BUART_sRX_RxSts__MASK_REG )
    #define ProbeUART_RXSTATUS_ACTL_REG      (* (reg8 *) ProbeUART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define ProbeUART_RXSTATUS_ACTL_PTR      (  (reg8 *) ProbeUART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (ProbeUART_RX_ENABLED) || (ProbeUART_HD_ENABLED) */

#if(ProbeUART_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define ProbeUART_INTCLOCK_CLKEN_REG     (* (reg8 *) ProbeUART_IntClock__PM_ACT_CFG)
    #define ProbeUART_INTCLOCK_CLKEN_PTR     (  (reg8 *) ProbeUART_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define ProbeUART_INTCLOCK_CLKEN_MASK    ProbeUART_IntClock__PM_ACT_MSK
#endif /* End ProbeUART_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(ProbeUART_TX_ENABLED)
    #define ProbeUART_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End ProbeUART_TX_ENABLED */

#if(ProbeUART_HD_ENABLED)
    #define ProbeUART_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End ProbeUART_HD_ENABLED */

#if( (ProbeUART_RX_ENABLED) || (ProbeUART_HD_ENABLED) )
    #define ProbeUART_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (ProbeUART_RX_ENABLED) || (ProbeUART_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define ProbeUART_WAIT_1_MS      ProbeUART_BL_CHK_DELAY_MS   

#define ProbeUART_TXBUFFERSIZE   ProbeUART_TX_BUFFER_SIZE
#define ProbeUART_RXBUFFERSIZE   ProbeUART_RX_BUFFER_SIZE

#if (ProbeUART_RXHW_ADDRESS_ENABLED)
    #define ProbeUART_RXADDRESSMODE  ProbeUART_RX_ADDRESS_MODE
    #define ProbeUART_RXHWADDRESS1   ProbeUART_RX_HW_ADDRESS1
    #define ProbeUART_RXHWADDRESS2   ProbeUART_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define ProbeUART_RXAddressMode  ProbeUART_RXADDRESSMODE
#endif /* (ProbeUART_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define ProbeUART_initvar                    ProbeUART_initVar

#define ProbeUART_RX_Enabled                 ProbeUART_RX_ENABLED
#define ProbeUART_TX_Enabled                 ProbeUART_TX_ENABLED
#define ProbeUART_HD_Enabled                 ProbeUART_HD_ENABLED
#define ProbeUART_RX_IntInterruptEnabled     ProbeUART_RX_INTERRUPT_ENABLED
#define ProbeUART_TX_IntInterruptEnabled     ProbeUART_TX_INTERRUPT_ENABLED
#define ProbeUART_InternalClockUsed          ProbeUART_INTERNAL_CLOCK_USED
#define ProbeUART_RXHW_Address_Enabled       ProbeUART_RXHW_ADDRESS_ENABLED
#define ProbeUART_OverSampleCount            ProbeUART_OVER_SAMPLE_COUNT
#define ProbeUART_ParityType                 ProbeUART_PARITY_TYPE

#if( ProbeUART_TX_ENABLED && (ProbeUART_TXBUFFERSIZE > ProbeUART_FIFO_LENGTH))
    #define ProbeUART_TXBUFFER               ProbeUART_txBuffer
    #define ProbeUART_TXBUFFERREAD           ProbeUART_txBufferRead
    #define ProbeUART_TXBUFFERWRITE          ProbeUART_txBufferWrite
#endif /* End ProbeUART_TX_ENABLED */
#if( ( ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED ) && \
     (ProbeUART_RXBUFFERSIZE > ProbeUART_FIFO_LENGTH) )
    #define ProbeUART_RXBUFFER               ProbeUART_rxBuffer
    #define ProbeUART_RXBUFFERREAD           ProbeUART_rxBufferRead
    #define ProbeUART_RXBUFFERWRITE          ProbeUART_rxBufferWrite
    #define ProbeUART_RXBUFFERLOOPDETECT     ProbeUART_rxBufferLoopDetect
    #define ProbeUART_RXBUFFER_OVERFLOW      ProbeUART_rxBufferOverflow
#endif /* End ProbeUART_RX_ENABLED */

#ifdef ProbeUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define ProbeUART_CONTROL                ProbeUART_CONTROL_REG
#endif /* End ProbeUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(ProbeUART_TX_ENABLED)
    #define ProbeUART_TXDATA                 ProbeUART_TXDATA_REG
    #define ProbeUART_TXSTATUS               ProbeUART_TXSTATUS_REG
    #define ProbeUART_TXSTATUS_MASK          ProbeUART_TXSTATUS_MASK_REG
    #define ProbeUART_TXSTATUS_ACTL          ProbeUART_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(ProbeUART_TXCLKGEN_DP)
        #define ProbeUART_TXBITCLKGEN_CTR        ProbeUART_TXBITCLKGEN_CTR_REG
        #define ProbeUART_TXBITCLKTX_COMPLETE    ProbeUART_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define ProbeUART_TXBITCTR_PERIOD        ProbeUART_TXBITCTR_PERIOD_REG
        #define ProbeUART_TXBITCTR_CONTROL       ProbeUART_TXBITCTR_CONTROL_REG
        #define ProbeUART_TXBITCTR_COUNTER       ProbeUART_TXBITCTR_COUNTER_REG
    #endif /* ProbeUART_TXCLKGEN_DP */
#endif /* End ProbeUART_TX_ENABLED */

#if(ProbeUART_HD_ENABLED)
    #define ProbeUART_TXDATA                 ProbeUART_TXDATA_REG
    #define ProbeUART_TXSTATUS               ProbeUART_TXSTATUS_REG
    #define ProbeUART_TXSTATUS_MASK          ProbeUART_TXSTATUS_MASK_REG
    #define ProbeUART_TXSTATUS_ACTL          ProbeUART_TXSTATUS_ACTL_REG
#endif /* End ProbeUART_HD_ENABLED */

#if( (ProbeUART_RX_ENABLED) || (ProbeUART_HD_ENABLED) )
    #define ProbeUART_RXDATA                 ProbeUART_RXDATA_REG
    #define ProbeUART_RXADDRESS1             ProbeUART_RXADDRESS1_REG
    #define ProbeUART_RXADDRESS2             ProbeUART_RXADDRESS2_REG
    #define ProbeUART_RXBITCTR_PERIOD        ProbeUART_RXBITCTR_PERIOD_REG
    #define ProbeUART_RXBITCTR_CONTROL       ProbeUART_RXBITCTR_CONTROL_REG
    #define ProbeUART_RXBITCTR_COUNTER       ProbeUART_RXBITCTR_COUNTER_REG
    #define ProbeUART_RXSTATUS               ProbeUART_RXSTATUS_REG
    #define ProbeUART_RXSTATUS_MASK          ProbeUART_RXSTATUS_MASK_REG
    #define ProbeUART_RXSTATUS_ACTL          ProbeUART_RXSTATUS_ACTL_REG
#endif /* End  (ProbeUART_RX_ENABLED) || (ProbeUART_HD_ENABLED) */

#if(ProbeUART_INTERNAL_CLOCK_USED)
    #define ProbeUART_INTCLOCK_CLKEN         ProbeUART_INTCLOCK_CLKEN_REG
#endif /* End ProbeUART_INTERNAL_CLOCK_USED */

#define ProbeUART_WAIT_FOR_COMLETE_REINIT    ProbeUART_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_ProbeUART_H */


/* [] END OF FILE */
