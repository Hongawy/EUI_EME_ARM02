#include "DIO.h"
#include "systick_timer.h"
#include "lcd.h"
uint32_t SEC=0,MIN=0,ST_Current_Val=0;
void PORTF_HANDLER(void){
    delay_us(200);//Debouncing Delay
    /*If SW2 was pressed*/
    if(GPIO_PORTF_RIS_R&0x01){
        if(GET_BIT(NVIC_ST_CTRL_R,0)){//IF THE ENABLE PIN IS HIGH
            /*************PAUSE*****************/
            ST_DeInit();/*Disable the SysTick Timer*/
            ST_Current_Val=NVIC_ST_CURRENT_R;/*Get the Current value and store it*/
        }
        else{
            /************RESUME****************/
            NVIC_ST_CURRENT_R=ST_Current_Val;/*Place the stored value in the Current Register*/
            SET_BIT(NVIC_ST_CTRL_R,0);/*enable the SysTick Timer*/
        }
    }
    /*If SW1 was pressed*/
    else if(GPIO_PORTF_RIS_R&0x10){
        SET_BIT(NVIC_ST_CTRL_R,0);/*enable the SysTick Timer*/
    }
    GPIO_PORTF_ICR_R|=(0x11);//CLEAR THE INTERRUPT FLAG FOR SW1 and SW2
}
void ST_INT_HANDLER(void){
    //    lcd_clearScreen();
    TOGGLE_BIT(GPIO_PORTF_DATA_R,1); /*TOGGLE THE RED LED*/
    SEC++;
}

int main(void)
{
    __asm(" CPSIE I "); /*ENABLES GLOBAL INTERRUPTS*/
    NVIC_EN0_R |= (1<<15); //ENABLES INTERRUPT NUMBER 15 (SYSTICK TIMER)
    NVIC_EN0_R |= (1<<30); //ENABLES INTERRUPT NUMBER 30 (PORTF)
    /*GPIO INITIALIZATION*/
    DIO_Init(PORTA,0xFC,0x00);
    DIO_Init(PORTB,0x13,0x00);
    DIO_Init(PORTE,0x3F,0x00);
    DIO_Init(PORTF,0X0E,0X11);
    GPIO_PORTF_IS_R &=~(0x11);//EDGE SENSITIVE FOR SW1 and SW2
    GPIO_PORTF_IEV_R &=~(0x11);//FALLING EDGE SENSITIVE FOR SW1 and SW2
    GPIO_PORTF_IM_R|=(0x11);//WHEN INTERRUPT IS TRIGGERED, IT GOES TO THE ISR FOR SW1 and SW2
    GPIO_PORTF_ICR_R|=(0x11);//CLEAR THE INTERRUPT FLAG JUST IN CASE FOR SW1 and SW2
    /*LCD INITIALIZATION*/
    lcd_init();
    lcd_moveCursor(0,0);
    /*SYSTICK TIMER INITIALIZATION*/
    ST_SetReloadValue(0XF423FF); /*RELOAD TIME=15999999 clocks = 1 sec*/
    ST_Init();
    lcd_string("00:00");
    while(1){
        if(SEC>=60){
            SEC=0;
            MIN++;
            lcd_clearScreen();
            lcd_string("00:00");
            lcd_moveCursor(0,0);
        }
        if(MIN>9){
            lcd_moveCursor(0,0);
            lcd_printLong(MIN);
        }
        else if(MIN>0 && MIN<=9){
            lcd_moveCursor(1,0);
            lcd_printLong(MIN);
        }

        lcd_moveCursor(2,0);
        lcd_string(":");
        if(SEC>9 && SEC<60){
            lcd_moveCursor(3,0);
            lcd_printLong(SEC);
            lcd_string(" ");
        }
        else if(SEC>0 && SEC<=9){
            lcd_moveCursor(4,0);
            lcd_printLong(SEC);
            lcd_string(" ");
        }
    }
}
