/*******************************************************************************
* File Name: SS4.h  
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

#if !defined(CY_PINS_SS4_H) /* Pins SS4_H */
#define CY_PINS_SS4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SS4_aliases.h"


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
} SS4_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SS4_Read(void);
void    SS4_Write(uint8 value);
uint8   SS4_ReadDataReg(void);
#if defined(SS4__PC) || (CY_PSOC4_4200L) 
    void    SS4_SetDriveMode(uint8 mode);
#endif
void    SS4_SetInterruptMode(uint16 position, uint16 mode);
uint8   SS4_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SS4_Sleep(void); 
void SS4_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SS4__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SS4_DRIVE_MODE_BITS        (3)
    #define SS4_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SS4_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SS4_SetDriveMode() function.
         *  @{
         */
        #define SS4_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SS4_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SS4_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SS4_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SS4_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SS4_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SS4_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SS4_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SS4_MASK               SS4__MASK
#define SS4_SHIFT              SS4__SHIFT
#define SS4_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SS4_SetInterruptMode() function.
     *  @{
     */
        #define SS4_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SS4_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SS4_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SS4_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SS4__SIO)
    #define SS4_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SS4__PC) && (CY_PSOC4_4200L)
    #define SS4_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SS4_USBIO_DISABLE              ((uint32)(~SS4_USBIO_ENABLE))
    #define SS4_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SS4_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SS4_USBIO_ENTER_SLEEP          ((uint32)((1u << SS4_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SS4_USBIO_SUSPEND_DEL_SHIFT)))
    #define SS4_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SS4_USBIO_SUSPEND_SHIFT)))
    #define SS4_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SS4_USBIO_SUSPEND_DEL_SHIFT)))
    #define SS4_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SS4__PC)
    /* Port Configuration */
    #define SS4_PC                 (* (reg32 *) SS4__PC)
#endif
/* Pin State */
#define SS4_PS                     (* (reg32 *) SS4__PS)
/* Data Register */
#define SS4_DR                     (* (reg32 *) SS4__DR)
/* Input Buffer Disable Override */
#define SS4_INP_DIS                (* (reg32 *) SS4__PC2)

/* Interrupt configuration Registers */
#define SS4_INTCFG                 (* (reg32 *) SS4__INTCFG)
#define SS4_INTSTAT                (* (reg32 *) SS4__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SS4_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SS4__SIO)
    #define SS4_SIO_REG            (* (reg32 *) SS4__SIO)
#endif /* (SS4__SIO_CFG) */

/* USBIO registers */
#if !defined(SS4__PC) && (CY_PSOC4_4200L)
    #define SS4_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SS4_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SS4_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SS4_DRIVE_MODE_SHIFT       (0x00u)
#define SS4_DRIVE_MODE_MASK        (0x07u << SS4_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SS4_H */


/* [] END OF FILE */
