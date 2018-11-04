#include <bcm2835.h>
#define PIN RPI_V2_GPIO_PI_12
#define SHORT_TIME 300
#define LONG_TIME 1000

int main(int argc, char** argv)
{
	//! Инициализация библиотеки.
	if ( !bcm2835_init() ) { return 1; }
	
	//! Установка порта в режим вывода.
	bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
	
	for ( int i = 0; i < 4; i++ ) {
		//! Короткое включение.
		bcm2835_gpio_write(PIN, HIGH);
		bcm2835_delay(SHORT_TIME);
		
		//! Длинное выключение.
		bcm2835_gpio_write(PIN, LOW);
		bcm2835_delay(LONG_TIME);
		
		//! Длинное включение.
		bcm2835_gpio_write(PIN, HIGH);
		bcm2835_delay(LONG_TIME);
		
		//! Короткое выключение.
		bcm2835_gpio_write(PIN, LOW);
		bcm2835_delay(SHORT_TIME);
	}
	
	return 0;
}