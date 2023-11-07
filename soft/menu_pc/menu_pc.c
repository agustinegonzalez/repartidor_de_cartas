#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "termset.h"



int main(int argc, int argv[])
{
	int file_descriptor;
	struct termios oldtty, newtty;

	file_descriptor = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);

	if(file_descritor == -1)
	{
		printf("ERROR: no se pudo abrir el dispositivo.\n");
		exit(1);	
	}

	if(termset(file_descritor, 9600, &oldtty, &newtty) == -1)
	{
		printf("ERROR: no se pudo configurar el tty.\n");
		exit(2);
	}
	
	tcflush(file_descritor, TCIOFLUSH);

	for(;;)
	{

		write(file_descritor, "UNO", 1);
		tcdrain(file_descritor);
		sleep(1);
	}

	close(file_descriptor);

	return 0;

}
