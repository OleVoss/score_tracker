#define __AVR_ATmega329P__
#define F_CPU 8000000UL

#include <stdio.h>
#include <avr/io.h>

#include "libs/lcd/lcdpcf8574/lcdpcf8574.h"
#include "libs/lcd/custom_chars.h"

int hole = 0;

int btn_pressed = 0;

int main(void)
{

    pin_setup();

    lcd_init(LCD_DISP_ON);
    //lcd_bigfont_setup();

    lcd_home();
    lcd_led(0);

    // lcd_puts("   Hole: ");
    // lcd_gotoxy(0, 1);
    // lcd_puts("Strokes: ");

    big_1(10, 0);
    big_0(13, 0);

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

void lcd_bigfont_setup()
{
    lcd_create_custom_char(0, LT);
    lcd_create_custom_char(1, UB);
    lcd_create_custom_char(2, RT);
    lcd_create_custom_char(3, LL);
    lcd_create_custom_char(4, LB);
    lcd_create_custom_char(5, LR);
    lcd_create_custom_char(6, UMB);
    lcd_create_custom_char(7, LMB);
}

void big_0(x, y)
{
    lcd_gotoxy(x, y);
    lcd_putc(0);
    lcd_putc(1);
    lcd_putc(2);
    lcd_gotoxy(x, y + 1);
    lcd_putc(3);
    lcd_putc(4);
    lcd_putc(5);
}

void big_1(x, y)
{
    lcd_gotoxy(x, y);
    lcd_putc(1);
    lcd_putc(2);
    lcd_gotoxy(x + 1, y + 1);
    lcd_putc(255);
}