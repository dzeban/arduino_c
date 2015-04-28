#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


/* Initialize SPI slave device */
void spi_init_slave()
{
	/* Configure MISO as output */
	DDRB |= _BV(DDB6);

	/* Enable SPI */
	SPCR |= _BV(SPE);
}

/* Send and receive data. Used in both master and slave. */
unsigned char spi_xfer(unsigned char data)
{
	/* Load data into buffer */
	SPDR = data;

	/* Wait until transmission complete */
	while (!(SPSR & (1 << SPIF)));

	/* Return received data */
	return SPDR;
}

enum {
	BLINK_DELAY_MS = 1000,
};

int main()
{
	spi_init_slave();

	/* set pin 7 of PORTD (Arduino digital I/O pin 7) for output*/
	DDRD |= _BV(DDD7);

	while(1) {
		/* set pin 7 high to turn led on */
		PORTD |= _BV(PD7);
		_delay_ms(BLINK_DELAY_MS);

		/* set pin 7 low to turn led off */
		PORTD &= ~_BV(PD7);
		_delay_ms(BLINK_DELAY_MS);
	}

}
