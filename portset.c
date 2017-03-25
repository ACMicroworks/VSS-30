

#define F_CPU 1000000UL

/* Library Includes */

#include <avr/io.h>
#include <stdio.h>

/* USART Definitions */

#define TXEN 0x08
#define RXEN 0x10

int
main (int argc, char *argv[])
{

  // U2Xn = 0 sets Asynchronous Normal Mode
  
  /* Enable the Transmitter and Receiver */
  UCSR0B |= TXEN;
  UCSR0B |= RXEN;

  /* Frame Formatting - Parity = None*/
  UCSR0C |= (1 << UPM01);
  UCSR0C |= (1 << UPM00);

  /* Frame Formatting - Stop Bit = 1 */
  UCSR0C &= !(1 << USBS0);

  /* Frame Formatting - Data Bits = 8 */
  UCSR0C |= (1 << UCSZ01);
  UCSR0C |= (1 << UCSZ00);

  /* Frame Formatting - Clock Polarity = 0 for Asynchronous USART */
  UCSR0C &= !(1 << UCPOL0);

  /* Set Asynchronous USART */
  UCSR0C |= (1 << UMSEL01);
  UCSR0C |= (1 << UMSEL00);
  
  /* Set the Baud Rate = 9600 (-8% Error @ 1MHz) */
  UBRR0H = 0x00;
  UBRR0L = 0x33;
  
  return 0;
}
