/*******************************************************************************
* File Name: ADC_Temperature.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_ADC_Temperature_H) /* Pins ADC_Temperature_H */
#define CY_PINS_ADC_Temperature_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ADC_Temperature_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} ADC_Temperature_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   ADC_Temperature_Read(void);
void    ADC_Temperature_Write(uint8 value);
uint8   ADC_Temperature_ReadDataReg(void);
#if defined(ADC_Temperature__PC) || (CY_PSOC4_4200L) 
    void    ADC_Temperature_SetDriveMode(uint8 mode);
#endif
void    ADC_Temperature_SetInterruptMode(uint16 position, uint16 mode);
uint8   ADC_Temperature_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void ADC_Temperature_Sleep(void); 
void ADC_Temperature_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(ADC_Temperature__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define ADC_Temperature_DRIVE_MODE_BITS        (3)
    #define ADC_Temperature_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ADC_Temperature_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the ADC_Temperature_SetDriveMode() function.
         *  @{
         */
        #define ADC_Temperature_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define ADC_Temperature_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define ADC_Temperature_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define ADC_Temperature_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define ADC_Temperature_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define ADC_Temperature_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define ADC_Temperature_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define ADC_Temperature_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define ADC_Temperature_MASK               ADC_Temperature__MASK
#define ADC_Temperature_SHIFT              ADC_Temperature__SHIFT
#define ADC_Temperature_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ADC_Temperature_SetInterruptMode() function.
     *  @{
     */
        #define ADC_Temperature_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define ADC_Temperature_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define ADC_Temperature_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define ADC_Temperature_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(ADC_Temperature__SIO)
    #define ADC_Temperature_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(ADC_Temperature__PC) && (CY_PSOC4_4200L)
    #define ADC_Temperature_USBIO_ENABLE               ((uint32)0x80000000u)
    #define ADC_Temperature_USBIO_DISABLE              ((uint32)(~ADC_Temperature_USBIO_ENABLE))
    #define ADC_Temperature_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define ADC_Temperature_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define ADC_Temperature_USBIO_ENTER_SLEEP          ((uint32)((1u << ADC_Temperature_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << ADC_Temperature_USBIO_SUSPEND_DEL_SHIFT)))
    #define ADC_Temperature_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << ADC_Temperature_USBIO_SUSPEND_SHIFT)))
    #define ADC_Temperature_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << ADC_Temperature_USBIO_SUSPEND_DEL_SHIFT)))
    #define ADC_Temperature_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(ADC_Temperature__PC)
    /* Port Configuration */
    #define ADC_Temperature_PC                 (* (reg32 *) ADC_Temperature__PC)
#endif
/* Pin State */
#define ADC_Temperature_PS                     (* (reg32 *) ADC_Temperature__PS)
/* Data Register */
#define ADC_Temperature_DR                     (* (reg32 *) ADC_Temperature__DR)
/* Input Buffer Disable Override */
#define ADC_Temperature_INP_DIS                (* (reg32 *) ADC_Temperature__PC2)

/* Interrupt configuration Registers */
#define ADC_Temperature_INTCFG                 (* (reg32 *) ADC_Temperature__INTCFG)
#define ADC_Temperature_INTSTAT                (* (reg32 *) ADC_Temperature__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define ADC_Temperature_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(ADC_Temperature__SIO)
    #define ADC_Temperature_SIO_REG            (* (reg32 *) ADC_Temperature__SIO)
#endif /* (ADC_Temperature__SIO_CFG) */

/* USBIO registers */
#if !defined(ADC_Temperature__PC) && (CY_PSOC4_4200L)
    #define ADC_Temperature_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define ADC_Temperature_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define ADC_Temperature_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define ADC_Temperature_DRIVE_MODE_SHIFT       (0x00u)
#define ADC_Temperature_DRIVE_MODE_MASK        (0x07u << ADC_Temperature_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins ADC_Temperature_H */


/* [] END OF FILE */
