#define __AVR_ATmega329P__
#define F_CPU 8000000UL

#include <stdio.h>
#include <avr/io.h>

#include "libs/lcd/lcdpcf8574/lcdpcf8574.h";

int hole = 0;

int btn_pressed = 0;

int main(void)
{

    pin_setup();

    lcd_init(LCD_DISP_ON);
    lcd_home();

    lcd_led(0);

    lcd_puts("   Hole: ");
    lcd_gotoxy(0, 1);
    lcd_puts("Strokes: ");

    while (1)
    {
        if (((PIND & (1 << PD5)) >> PD5) == 0)
        {
            if (btn_pressed == 0)
            {
                PORTB ^= (1 << PB0);
                hole++;
                print_hole();
            }
            btn_pressed = 1;
        }
        else if (((PIND & (1 << PD6)) >> PD6) == 0)
        {
            if (btn_pressed == 0)
            {
                PORTB ^= (1 << PB0);
                hole--;
                print_hole();
            }
            btn_pressed = 1;
        }
        else
        {
            btn_pressed = 0;
        }
    }

    return 0;
}

void print_hole()
{
    lcd_gotoxy(9, 0);
    lcd_puts("   "); // clear number
    char buf[10];
    itoa(hole, buf, 10);
    lcd_gotoxy(9, 0);
    lcd_puts(buf);
}

void pin_setup()
{
    // Button pins
    DDRB &= ~(1 << DDB6); // Up
    PORTB |= (1 << DDB6);

    DDRB &= ~(1 << DDB7); // Down
    PORTB |= (1 << DDB7);

    DDRD &= ~(1 << DDD5); // Right
    PORTD |= (1 << DDD5);

    DDRD &= ~(1 << DDD6); // Left
    PORTD |= (1 << DDD6);

    DDRD &= ~(1 << DDD7); // Reset/Power?
    PORTD |= (1 << DDD7);

    // Status led
    DDRB |= (1 << DDB0);
}