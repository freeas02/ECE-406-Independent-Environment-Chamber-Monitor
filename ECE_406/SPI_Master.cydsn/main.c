/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h" 
#define ADC_size 10
#define LINE1	0
#define LINE2	LINE1+0x20
#define LINE3	LINE1+0x40
#define	LINE4 	LINE1+0x60

//Changes the Character length of array in ST7735_sDecOut3()
#define Char_Length 7
//changes the location of the decimal place in sDec2BCD() (10^(-Decimal_Place_Location_signed))
#define Decimal_Place_Location_signed 5
uint8_t UART_IN(char *array, uint16_t size)
{
    uint8_t i =0;
    
    if(UART_1_SpiUartGetRxBufferSize() > 0)
    {
        while(i < size)
        {
            if (array[i-1] != '\r')
            {
                if(array[i-1] != 0x08 )
                {
                    array[i] = UART_1_UartGetChar();
                    if(array[i] == 0)
                    {
                        i--;
                    }
                    else
                    {
                       UART_1_UartPutChar(array[i]); 
                    }
                    i++;
                }
                else
                {
                    i--;
                }
            }
            else
            {
                i--;
                array[i] = '\0';
                UART_1_UartPutChar('\r');
                UART_1_UartPutChar('\n');
                break;
            }
            
        }
    }
    else
    {
        return 0;
    }
    return 1;
}

volatile int32 ADC_Value1;
volatile int32 ADC_Value2;
volatile int32 Temperature_array[10];
int32 Temperature_Avg;
void ADC_Collect()
{
    uint8_t i=0;
   
    ADC_Value2= ADC_Seq_1_GetResult16(1);
    while(i<10)
    {
        ADC_Value1= ADC_Seq_1_GetResult16(0);
        Temperature_array[i] = ADC_Seq_1_CountsTo_mVolts(0,ADC_Value1);
        i++;
    }
    i=0;
    while(i<10)
    {
        Temperature_Avg = Temperature_Avg + Temperature_array[i];
        i++;
    }
    Temperature_Avg = Temperature_Avg/10;
}
void UART_Display(char *array)
{
        int8_t i=0;
        while(array[i] != '\0')
        {
            UART_1_UartPutChar(array[i]);
            i++;
        }
        UART_1_UartPutChar('\r');
        UART_1_UartPutChar('\n');
}
void Display_Temperature(int32 Temperature, char *dec)
{
    int8_t i = 0;//counter (can go negative)
	int32_t current_hex_value = Temperature;//temp var
	int32_t digit = 0;//temp var

		i=Char_Length-1;// start from end of array 
		while(i >= 0 )//loop through dec array
		{
			if(i == Decimal_Place_Location_signed -1)// '.' at **.*** in dec array when i = 2
			{
				dec[i]= '.';
			}
			else if (i == 0)//sign of number
			{
				if (Temperature < 0)//negative sign
				{
					dec[i] = '-';
				}
				else//positive/ no sign
				{
					dec[i] = ' ' ;
				}
			}
			else//fill with values of incoming number hex 
			{
				digit=current_hex_value%10;//taking last digit
				if(digit < 0)
				{
					digit = digit^(0x80000000);
					digit = (digit^0x7FFFFFFF)+1;
				}
				dec[i] = digit + '0';//adds digit to dec[] at location i in terms of ascii
				current_hex_value = current_hex_value/10;//cut digit so can repeat it
			}
			i--;
		}	
    i=0;
    while(i<Char_Length)
    {
        UART_1_UartPutChar(dec[i]);
        i++;
    }
    UART_1_UartPutChar(' ');
    UART_1_UartPutChar('C');
    UART_1_UartPutChar('\r');
    UART_1_UartPutChar('\n');
}
void Integer_ASCII_ADC(uint16_t length, char *array, int16_t Value)
{ 
    
    uint16_t temp =Value;
    int8_t i = length -1;
    uint16_t digit; 
    while(temp > 0)
    {
        digit = temp%10;
        temp = temp/10;
        if(digit < 0)
        {
            digit = -digit;
        }
        array[i] = digit + '0';
        i--;
    }
    if(i>0)
    {
        while(i>=0)
        {
            array[i] = ' ';
            i--;
        }
    }
}



void DOGS164W_A_Write_Data(uint8_t data)
{
    
    while(SPI_SpiUartGetTxBufferSize()){};
    uint8_t array[3];
    array[0] = 0x5F;
    array[1] = (data&0x0F);
    array[2] = ((data>>4)&0x0F);
    SPI_SpiSetActiveSlaveSelect(SPI_SPI_SLAVE_SELECT0);
    SPI_SpiUartPutArray(array,3);
    
    /*
    SPI_SpiUartWriteTxData(0x5F);
    CyDelay(1);
    SPI_SpiUartWriteTxData(data&0x0F);
    CyDelay(1);
    SPI_SpiUartWriteTxData((data>>4)&0x0F);
    CyDelay(1);
    while(SPI_SpiUartGetTxBufferSize()){};
    */
}
void DOGS164W_A_Write_Ins(uint8_t data)
{
    
    while(SPI_SpiUartGetTxBufferSize()){};
    uint8_t array[3];
    array[0] = 0x1F;
    array[1] = (data&0x0F);
    array[2] = ((data>>4)&0x0F);
    SPI_SpiSetActiveSlaveSelect(SPI_SPI_SLAVE_SELECT0);
    SPI_SpiUartPutArray(array,3);
    /*
    SPI_SpiUartWriteTxData(0x1F);
    CyDelay(1);
    SPI_SpiUartWriteTxData(data&0x0F);
    CyDelay(1);
    SPI_SpiUartWriteTxData((data>>4)&0x0F);
    CyDelay(1);
    */
    while(SPI_SpiUartGetTxBufferSize()){};
}
void DOGS164W_A_WriteString(char *str) 
{
    do
	{
		DOGS164W_A_Write_Data(*str++);
	}
	while(*str);
}
void DOGS164W_A_SetPosition(uint8_t pos) {

    DOGS164W_A_Write_Ins(0x80+pos);
}
void DOGS164W_A_Clear(void)
{
	DOGS164W_A_Write_Ins(0x01);
	DOGS164W_A_SetPosition(LINE1);
}

void DOGS164W_A_Init()
{
    CyDelay(2);
    LCD_RST_Write(0);
    CyDelay(5);
    LCD_RST_Write(1);
    CyDelay(100);
    uint8_t initSequence[] = {
        0x0C,
        0x3A, 
        0x09, 
        0x06,   //sets view: top, 0x05 | bottom, 0x06
        0x1E, 
        0x39, 
        0x1B, 
        0x6E,
        0x56,
        0x7A,
        0x38,
        0x61      //testing different values
        
        
    };
     for (uint8_t i = 0; i < sizeof(initSequence); i++) {
        DOGS164W_A_Write_Ins(initSequence[i]);
        CyDelay(1);
    }

}
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    //Variables
    uint32_t i=0;
    uint32_t j=0;
    char dec[Char_Length];
    volatile int32 Temperature;
    char array1[ADC_size];
    char array2[ADC_size];
    char InString[20];
    char TestString[] = {'T','E','S','T'};


    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    //ISR_Start
    ISR_Function_Start();
    
    //Start UART
    UART_1_Start();
    
    //Start SPI 
    SPI_Start();
    SPI_SpiUartClearTxBuffer();
    
    //Start ADC
    ADC_Seq_1_Start();
    ADC_Seq_1_StartConvert();
    ADC_Seq_1_IsEndConversion(ADC_Seq_1_WAIT_FOR_RESULT);
    
    //Start Timer
    //Timer_Start();
    
    LED_1_Write(0);
    LED_2_Write(1);
    ADC_Collect();
    Temperature = ((Temperature_Avg*100 - 1250*100)/5);
    Temperature_Avg =0;
    Display_Temperature(Temperature,dec);
    DOGS164W_A_Init();
    DOGS164W_A_Clear();
    //DOGS164W_A_Write_Ins(0x0C);
    CyDelay(1);
    
    while(i<7)
    {
       DOGS164W_A_Write_Data(dec[i]);
        i++;
    }
    i=0;
    //DOGS164W_A_SetPosition(LINE3);
    //DOGS164W_A_WriteString("test string");
    CyDelay(1);
    
    for(;;)
    { 
        /* Place your application code here. */
        
        if(UART_IN(InString,20))
        {
            if(strcmp(InString, "ON"))
            {
                LED_2_Write(1);
            }
            if(strcmp(InString, "OFF"))
            {
                LED_2_Write(0);
            }
        }
        
        if(i==6)
        {
            
            UART_1_UartPutString("ADC Values: ");
            UART_1_UartPutChar('\r');
            UART_1_UartPutChar('\n');
            ADC_Collect();
            Integer_ASCII_ADC(ADC_size,array1,ADC_Value1);
            Integer_ASCII_ADC(ADC_size,array2,ADC_Value2);
            UART_Display(array1);
            UART_Display(array2);
            UART_1_UartPutString("Temperature Readings: ");
            UART_1_UartPutChar('\r');
            UART_1_UartPutChar('\n');
            
            Temperature = ((Temperature_Avg*100 - 1250*100)/5);
            Temperature_Avg =0;
            Display_Temperature(Temperature,dec);
            DOGS164W_A_Clear();
            DOGS164W_A_WriteString("Temperature: ");
            CyDelay(1);
            DOGS164W_A_SetPosition(LINE2);
            while(j<Char_Length)
            {
                DOGS164W_A_Write_Data(dec[j]);
                j++;
            }
            j=0;
            CyDelay(1);
            i=0;
        }
        
        CyDelay(500);
        
        i++;
    }
}

/* [] END OF FILE */
