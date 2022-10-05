/*******************************************************************************
* File Name: temp_conv.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "temp_conv.h"

static temp_conv_BACKUP_STRUCT  temp_conv_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: temp_conv_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet temp_conv_SUT.c usage_temp_conv_Sleep_Wakeup
*******************************************************************************/
void temp_conv_Sleep(void)
{
    #if defined(temp_conv__PC)
        temp_conv_backup.pcState = temp_conv_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            temp_conv_backup.usbState = temp_conv_CR1_REG;
            temp_conv_USB_POWER_REG |= temp_conv_USBIO_ENTER_SLEEP;
            temp_conv_CR1_REG &= temp_conv_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(temp_conv__SIO)
        temp_conv_backup.sioState = temp_conv_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        temp_conv_SIO_REG &= (uint32)(~temp_conv_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: temp_conv_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to temp_conv_Sleep() for an example usage.
*******************************************************************************/
void temp_conv_Wakeup(void)
{
    #if defined(temp_conv__PC)
        temp_conv_PC = temp_conv_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            temp_conv_USB_POWER_REG &= temp_conv_USBIO_EXIT_SLEEP_PH1;
            temp_conv_CR1_REG = temp_conv_backup.usbState;
            temp_conv_USB_POWER_REG &= temp_conv_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(temp_conv__SIO)
        temp_conv_SIO_REG = temp_conv_backup.sioState;
    #endif
}


/* [] END OF FILE */
