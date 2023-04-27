/*******************************************************************************
* File Name: ADC_Power.c  
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
#include "ADC_Power.h"

static ADC_Power_BACKUP_STRUCT  ADC_Power_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: ADC_Power_Sleep
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
*  \snippet ADC_Power_SUT.c usage_ADC_Power_Sleep_Wakeup
*******************************************************************************/
void ADC_Power_Sleep(void)
{
    #if defined(ADC_Power__PC)
        ADC_Power_backup.pcState = ADC_Power_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            ADC_Power_backup.usbState = ADC_Power_CR1_REG;
            ADC_Power_USB_POWER_REG |= ADC_Power_USBIO_ENTER_SLEEP;
            ADC_Power_CR1_REG &= ADC_Power_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(ADC_Power__SIO)
        ADC_Power_backup.sioState = ADC_Power_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        ADC_Power_SIO_REG &= (uint32)(~ADC_Power_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: ADC_Power_Wakeup
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
*  Refer to ADC_Power_Sleep() for an example usage.
*******************************************************************************/
void ADC_Power_Wakeup(void)
{
    #if defined(ADC_Power__PC)
        ADC_Power_PC = ADC_Power_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            ADC_Power_USB_POWER_REG &= ADC_Power_USBIO_EXIT_SLEEP_PH1;
            ADC_Power_CR1_REG = ADC_Power_backup.usbState;
            ADC_Power_USB_POWER_REG &= ADC_Power_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(ADC_Power__SIO)
        ADC_Power_SIO_REG = ADC_Power_backup.sioState;
    #endif
}


/* [] END OF FILE */
