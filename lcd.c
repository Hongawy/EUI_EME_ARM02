#include "data_types.h"
#include "lcd.h"



void lcd_data(unsigned char data)
{
    //    STEPS:
    Printdata(data);                        //     1.Pass the 8-bit data to the datalines of LCD.
    CLEAR_BIT(GPIO_PORTA_DATA_R,3);         //     * 2.Turn off the R/W to select WRITE mode on the LCD
    SET_BIT(GPIO_PORTA_DATA_R,2);           //     * 3.Turn on the RS to select DATA mode on the LCD
    SET_BIT(GPIO_PORTA_DATA_R,4);           //     * 4.Turn on the EN pin on the LCD
    delay_ms(5);                            //     * 5.Wait for 5ms.
    CLEAR_BIT(GPIO_PORTA_DATA_R,4);         //     * 6.Turn off the EN pin on the LCD
}

void lcd_cmd(unsigned char cmd)
{
    //    STEPS:
    Printdata(cmd);                        //     1.Pass the 8-bit data to the datalines of LCD.
    CLEAR_BIT(GPIO_PORTA_DATA_R,3);         //     * 2.Turn off the R/W to select WRITE mode on the LCD
    CLEAR_BIT(GPIO_PORTA_DATA_R,2);           //     * 3.Turn off the RS to select COMMAND mode on the LCD
    SET_BIT(GPIO_PORTA_DATA_R,4);           //     * 4.Turn on the EN pin on the LCD
    delay_ms(5);                            //     * 5.Wait for 5ms.
    CLEAR_BIT(GPIO_PORTA_DATA_R,4);         //     * 6.Turn off the EN pin on the LCD
}

void lcd_string(unsigned char *str)
{
    char i;
    for(i=0;str[i]!=0;i++){
        lcd_data(str[i]);
    }
}

void lcd_init(void)
{
    lcd_cmd(0x38);    //    8-bit mode using 16x2 LCD
    delay_ms(20);
    lcd_cmd(0x06);   //    Auto-incrementing the cursor when the LCD prints the data
    delay_ms(20);
    lcd_cmd(0x0F);    //    cursor on, blinking on, and display on.
    delay_ms(20);
    lcd_cmd(0x01);    //    clear screen
}
void lcd_moveCursor(uint8_t x,uint8_t y)
{
    lcd_cmd(0x80 + x + (y*40));
}

void Printdata(unsigned char data) /*data = 8-bit hexadecimal data*/
{

    /*zeroth bit = D0 = PA7*/
    if((data&0x01)==0x01)   {GPIO_PORTA_DATA_R  |= (1<<7);}
    else                    {GPIO_PORTA_DATA_R &=~(1<<7);}
    /*first bit = D1 = PA6*/
    if((data&0x02)==0x02)   {GPIO_PORTA_DATA_R  |= (1<<6);}
    else                    {GPIO_PORTA_DATA_R &=~(1<<6);}
    /*second bit = D2 = PA5*/
    if((data&0x04)==0x04)   {GPIO_PORTA_DATA_R  |= (1<<5);}
    else                    {GPIO_PORTA_DATA_R &=~(1<<5);}
    /*third bit = D3 = PB4*/
    if((data&0x08)==0x08)   {GPIO_PORTB_DATA_R  |= (1<<4);}
    else                    {GPIO_PORTB_DATA_R &=~(1<<4);}
    /*fourth bit = D4 = PE5*/
    if((data&0x10)==0x10)   {GPIO_PORTE_DATA_R  |= (1<<5);}
    else                    {GPIO_PORTE_DATA_R &=~(1<<5);}
    /*fifth bit = D5 = PE4*/
    if((data&0x20)==0x20)   {GPIO_PORTE_DATA_R  |= (1<<4);}
    else                    {GPIO_PORTE_DATA_R &=~(1<<4);}
    /*sixth bit = D6 = PB1*/
    if((data&0x40)==0x40)   {GPIO_PORTB_DATA_R  |= (1<<1);}
    else                    {GPIO_PORTB_DATA_R &=~(1<<1);}
    /*seventh bit = D7 = PB0*/
    if((data&0x80)==0x80)   {GPIO_PORTB_DATA_R  |= (1<<0);}
    else                    {GPIO_PORTB_DATA_R &=~(1<<0);}
}


unsigned char* integer_to_string(int a){
    static unsigned char myString[20]={0};
    if(a<=9){
        myString[1]=0;
    }
    uint8_t i=0,temp=0;
    while(a!=0){
        myString[i]=(a%10)+48;
        a/=10;
        ++i;
    }
    unsigned char length=strlen(myString);//get the length of the string
    /*Reverse my string to the correct order*/
    for(int j=0;j<(length/2);j++){
        temp=myString[j];
        myString[j]=myString[length-j-1];
        myString[length-j-1]=temp;
    }
    return myString;
}
void lcd_printLong(long a){
    unsigned char* buffer=0;  // Buffer to store the string representation of the integer
    buffer=integer_to_string(a);  // Convert integer to string.
    lcd_string(buffer);  // Print the string representation on the LCD
}



void lcd_clearScreen(void){
    lcd_cmd(0x01);/*Clear the screen*/
}

void delay_ms(unsigned int n)
{
    int i,j;
    for(i=0;i<n;i++){for(j=0;j<3180;j++);}
}

void delay_us( unsigned int n)
{
    int i,j;
    for(i=0;i<n;i++){for(j=0;j<3;j++);}
}

