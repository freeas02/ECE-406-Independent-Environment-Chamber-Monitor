/*******************************************************************************
* File Name: ThermocoupleCalculator.h
* Version 1.20
*
* Description:
*  This file provides constants and parameter values for the ThermocoupleCalculator
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2012-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_THERMOCOUPLE_CALC_ThermocoupleCalculator_H)
#define CY_THERMOCOUPLE_CALC_ThermocoupleCalculator_H

#include "CyLib.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/


/***************************************
*       Enum Types
***************************************/

/* ThermocoupleTypes constants  */
#define ThermocoupleCalculator__B 0
#define ThermocoupleCalculator__E 1
#define ThermocoupleCalculator__J 2
#define ThermocoupleCalculator__K 3
#define ThermocoupleCalculator__N 4
#define ThermocoupleCalculator__R 5
#define ThermocoupleCalculator__S 6
#define ThermocoupleCalculator__T 7
             

/* CalcErrorType constants  */
#define ThermocoupleCalculator__ERR_0_1 0
#define ThermocoupleCalculator__ERR_0_5 1
#define ThermocoupleCalculator__ERR_1 2
                 

/* PolynomialOrderType constants  */
#define ThermocoupleCalculator__NIST 0
#define ThermocoupleCalculator__ORDER_7 1
#define ThermocoupleCalculator__ORDER_5 2
           


/***************************************
*        Constants
***************************************/

#define     ThermocoupleCalculator_INIT                       (0)
#define     ThermocoupleCalculator_FIRST_EL_MAS               (0u)
#define     ThermocoupleCalculator_RANGE_MAS_0                (0u)
#define     ThermocoupleCalculator_RANGE_MAS_1                (1u)
#define     ThermocoupleCalculator_RANGE_MAS_2                (2u)
#define     ThermocoupleCalculator_RANGE_MAS_3                (3u)
#define     ThermocoupleCalculator_THREE                      (3u)
#define     ThermocoupleCalculator_IN_NORMALIZATION_VT        (24)
#define     ThermocoupleCalculator_IN_NORMALIZATION_TV        (24u)
#define     ThermocoupleCalculator_24BIT_SHIFTING             (24u)
#define     ThermocoupleCalculator_16BIT_SHIFTING             (16u)
#define     ThermocoupleCalculator_8BIT_SHIFTING              (8u)
#define     ThermocoupleCalculator_24BIT_CUTTING              (0xFFFFFFlu)
#define     ThermocoupleCalculator_16BIT_CUTTING              (0xFFFFu)
#define     ThermocoupleCalculator_8BIT_CUTTING               (0xFFu)
#define     ThermocoupleCalculator_V_IN_FLOAT_NORMALIZATION   (1000u)
#define     ThermocoupleCalculator_V_OUT_FLOAT_NORMALIZATION  (100u)
#define     ThermocoupleCalculator_T_IN_FLOAT_NORMALIZATION   (100u)
#define     ThermocoupleCalculator_T_OUT_FLOAT_NORMALIZATION  (1000u)


/***************************************
*  Customizer Generated Defines
***************************************/

#define     ThermocoupleCalculator_ORDER_TV   (0x09u)
#define     ThermocoupleCalculator_ORDER_VT   (0x06u)
#define     ThermocoupleCalculator_VT_RANGE_LEN   (0x02u)
#define     ThermocoupleCalculator_X_SCALE_TV   (0x0Fu)
#define     ThermocoupleCalculator_COEF_SCALE_TV   (0x05u)


/***************************************
*        Function Prototypes
***************************************/

int32 ThermocoupleCalculator_GetTemperature(int32 voltage) ;
int32 ThermocoupleCalculator_GetVoltage(int32 temperature) ;

#if (!CY_PSOC3)
    int32 ThermocoupleCalculator_MultShift24(int32 op1, int32 op2) ;
#endif /* (!CY_PSOC3) */

#endif /* CY_THERMOCOUPLE_CALC_ThermocoupleCalculator_H */

/* [] END OF FILE */
