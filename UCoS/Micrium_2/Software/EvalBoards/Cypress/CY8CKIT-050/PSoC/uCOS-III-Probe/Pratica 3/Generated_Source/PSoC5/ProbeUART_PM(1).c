/*******************************************************************************
* File Name: ProbeUART_PM.c
* Version 2.20
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
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


/***************************************
* Local data allocation
***************************************/

static ProbeUART_BACKUP_STRUCT  ProbeUART_backup =
{
    /* enableState - disabled */
    0u,
};        



/*******************************************************************************
* Function Name: ProbeUART_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ProbeUART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ProbeUART_SaveConfig(void)
{
    #if (CY_UDB_V0)

        #if(ProbeUART_CONTROL_REG_REMOVED == 0u)
            ProbeUART_backup.cr = ProbeUART_CONTROL_REG;
        #endif /* End ProbeUART_CONTROL_REG_REMOVED */

        #if( (ProbeUART_RX_ENABLED) || (ProbeUART_HD_ENABLED) )
            ProbeUART_backup.rx_period = ProbeUART_RXBITCTR_PERIOD_REG;
            ProbeUART_backup.rx_mask = ProbeUART_RXSTATUS_MASK_REG;
            #if (ProbeUART_RXHW_ADDRESS_ENABLED)
                ProbeUART_backup.rx_addr1 = ProbeUART_RXADDRESS1_REG;
                ProbeUART_backup.rx_addr2 = ProbeUART_RXADDRESS2_REG;
            #endif /* End ProbeUART_RXHW_ADDRESS_ENABLED */
        #endif /* End ProbeUART_RX_ENABLED | ProbeUART_HD_ENABLED*/

        #if(ProbeUART_TX_ENABLED)
            #if(ProbeUART_TXCLKGEN_DP)
                ProbeUART_backup.tx_clk_ctr = ProbeUART_TXBITCLKGEN_CTR_REG;
                ProbeUART_backup.tx_clk_compl = ProbeUART_TXBITCLKTX_COMPLETE_REG;
            #else
                ProbeUART_backup.tx_period = ProbeUART_TXBITCTR_PERIOD_REG;
            #endif /*End ProbeUART_TXCLKGEN_DP */
            ProbeUART_backup.tx_mask = ProbeUART_TXSTATUS_MASK_REG;
        #endif /*End ProbeUART_TX_ENABLED */

    
    #else /* CY_UDB_V1 */

        #if(ProbeUART_CONTROL_REG_REMOVED == 0u)
            ProbeUART_backup.cr = ProbeUART_CONTROL_REG;
        #endif /* End ProbeUART_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: ProbeUART_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ProbeUART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ProbeUART_RestoreConfig(void)
{

    #if (CY_UDB_V0)

        #if(ProbeUART_CONTROL_REG_REMOVED == 0u)
            ProbeUART_CONTROL_REG = ProbeUART_backup.cr;
        #endif /* End ProbeUART_CONTROL_REG_REMOVED */

        #if( (ProbeUART_RX_ENABLED) || (ProbeUART_HD_ENABLED) )
            ProbeUART_RXBITCTR_PERIOD_REG = ProbeUART_backup.rx_period;
            ProbeUART_RXSTATUS_MASK_REG = ProbeUART_backup.rx_mask;
            #if (ProbeUART_RXHW_ADDRESS_ENABLED)
                ProbeUART_RXADDRESS1_REG = ProbeUART_backup.rx_addr1;
                ProbeUART_RXADDRESS2_REG = ProbeUART_backup.rx_addr2;
            #endif /* End ProbeUART_RXHW_ADDRESS_ENABLED */
        #endif  /* End (ProbeUART_RX_ENABLED) || (ProbeUART_HD_ENABLED) */

        #if(ProbeUART_TX_ENABLED)
            #if(ProbeUART_TXCLKGEN_DP)
                ProbeUART_TXBITCLKGEN_CTR_REG = ProbeUART_backup.tx_clk_ctr;
                ProbeUART_TXBITCLKTX_COMPLETE_REG = ProbeUART_backup.tx_clk_compl;
            #else
                ProbeUART_TXBITCTR_PERIOD_REG = ProbeUART_backup.tx_period;
            #endif /*End ProbeUART_TXCLKGEN_DP */
            ProbeUART_TXSTATUS_MASK_REG = ProbeUART_backup.tx_mask;
        #endif /*End ProbeUART_TX_ENABLED */

    #else /* CY_UDB_V1 */

        #if(ProbeUART_CONTROL_REG_REMOVED == 0u)
            ProbeUART_CONTROL_REG = ProbeUART_backup.cr;
        #endif /* End ProbeUART_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: ProbeUART_Sleep
********************************************************************************
*
* Summary:
*  Stops and saves the user configuration. Should be called 
*  just prior to entering sleep.
*  
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ProbeUART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ProbeUART_Sleep(void)
{

    #if(ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED)
        if((ProbeUART_RXSTATUS_ACTL_REG  & ProbeUART_INT_ENABLE) != 0u) 
        {
            ProbeUART_backup.enableState = 1u;
        }
        else
        {
            ProbeUART_backup.enableState = 0u;
        }
    #else
        if((ProbeUART_TXSTATUS_ACTL_REG  & ProbeUART_INT_ENABLE) !=0u)
        {
            ProbeUART_backup.enableState = 1u;
        }
        else
        {
            ProbeUART_backup.enableState = 0u;
        }
    #endif /* End ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED*/

    ProbeUART_Stop();
    ProbeUART_SaveConfig();
}


/*******************************************************************************
* Function Name: ProbeUART_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ProbeUART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ProbeUART_Wakeup(void)
{
    ProbeUART_RestoreConfig();
    #if( (ProbeUART_RX_ENABLED) || (ProbeUART_HD_ENABLED) )
        ProbeUART_ClearRxBuffer();
    #endif /* End (ProbeUART_RX_ENABLED) || (ProbeUART_HD_ENABLED) */
    #if(ProbeUART_TX_ENABLED || ProbeUART_HD_ENABLED)
        ProbeUART_ClearTxBuffer();
    #endif /* End ProbeUART_TX_ENABLED || ProbeUART_HD_ENABLED */

    if(ProbeUART_backup.enableState != 0u)
    {
        ProbeUART_Enable();
    } 
}


/* [] END OF FILE */
