#include "wires.h"
#include "ee_printf.h"
#include "NOKIA_5110/NOKIA_5110.h"
#include "Display/display-menu.h"

uint8_t _yPos = 0;
NokiaLcd display(LCD_DIN, LCD_CLK, LCD_CE, LCD_DC);
DigitalOut lcd_lgt(LCD_LGT, 1);
void init_lcd()
{
    display.InitLcd();
    display.SetXY(0, 0);
    display.SetContrast(65);
    lcd_lgt = 1;
}

LCDMenu menu(6,
             [](uint8_t *text, bool invert) { 
                          display.SetXY(0, _yPos);
                          if(invert){
                            for(uint8_t i =0;i<14;i++)
                                display.DrawChar(127);
                            display.SetXY(0, _yPos);
                            display.DrawStringNegative((char *)text); 
                          }else 
                              display.DrawString((char *)text);                           
                          _yPos+=1; },
             [] {
                 _yPos = 0;
                 display.ClearLcdMem();
                 display.SetXY(0, 0);
             });

InterruptIn up(SW_UP), down(SW_DOWN), central(SW_CENTRAL);
DigitalOut led1(LED_1), led2(LED_2), led3(LED_3), led4(LED_4), led5(LED_5);

void initWires()
{
    up.rise([] { menu.up(); });
    down.rise([] { menu.down(); });
    central.rise([] {
        switch (menu.getSelectedId())
        {
        case 0:
            led1 = !led1;
            break;
        case 1:
            led2 = !led2;
            break;
        case 2:
            led3 = !led3;
            break;
        case 3:
            led4 = !led4;
            break;
        case 4:
            led5 = !led5;
            break;
        case 5:
            led1 = led2 = led3 = led4 = led5 = 1;
            break;
        case 6:
            led1 = led2 = led3 = led4 = led5 = 0;
            break;
        case 7:
            led2 = led4 = 1;
            break;
        case 8:
            led2 = led4 = 0;
            break;
        case 9:
            led1 = led3 = led5 = 1;
            break;
        case 10:
            led1 = led3 = led5 = 0;
            break;
        }
    });
}

int main()
{
    initWires();
    init_lcd();
    lcd_lgt = 0;
    display.DrawString("HELLO!");
    wait(0.5);
    display.SetXY(0, 0);
    display.DrawString("INIT MENU!");
    for (uint8_t i = 0; i < 3; i++)
    {
        lcd_lgt = 1;
        wait(1);
        lcd_lgt = 0;
        wait(0.25);
    }
    display.ClearLcdMem();
    menu.add((uint8_t *)"TOGGLE 1", (uint8_t *)NULL);
    menu.add((uint8_t *)"TOGGLE 2", (uint8_t *)NULL);
    menu.add((uint8_t *)"TOGGLE 3", (uint8_t *)NULL);
    menu.add((uint8_t *)"TOGGLE 4", (uint8_t *)NULL);
    menu.add((uint8_t *)"TOGGLE 5", (uint8_t *)NULL);
    menu.add((uint8_t *)"ALL On", (uint8_t *)NULL);
    menu.add((uint8_t *)"ALL OFF", (uint8_t *)NULL);
    menu.add((uint8_t *)"EVEN ON", (uint8_t *)NULL);
    menu.add((uint8_t *)"EVEN OFF", (uint8_t *)NULL);
    menu.add((uint8_t *)"ODD ON", (uint8_t *)NULL);
    menu.add((uint8_t *)"ODD OFF", (uint8_t *)NULL);
    menu.render();
    sleep();
}