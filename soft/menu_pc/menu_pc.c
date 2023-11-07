#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "termset.h"
#include <stdint.h>
#include <string.h>
char* uno()
{
	char *cadena;
	uint8_t cargapositiva = 0;
       	scanf("%hhu", &cargapositiva);
        if (cargapositiva == 1) {
		
	
        }else
		exit(1);

	return (cadena = "UNO");
}

int main(int argc, char *argv[])
{
	int file_descriptor;
	struct termios oldtty, newtty;
	uint8_t opcion = 0;

	file_descriptor = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);

	if(file_descriptor == -1)
	{
		printf("ERROR: no se pudo abrir el dispositivo.\n");
		exit(1);	
	}

	if(termset(file_descriptor, 9600, &oldtty, &newtty) == -1)
	{
		printf("ERROR: no se pudo configurar el tty.\n");
		exit(2);
	}
	
	tcflush(file_descriptor, TCIOFLUSH);
	
	for (;;) {
		printf("\tR E P A R T I D O R    D E    C A R T A S\n");
		printf("1. Cargar juego\n");
		printf("2. Eliminar juego\n");
		printf("3. Cargar puntaje\n");
		printf("4. Salir\n");
		scanf("%hhu", &opcion);
		/*Falta agrega que cuando quiera cargar un juego, lo lleve a elegir entre los juegos posibles*/	
		if (opcion == 4) {
			break;  // Salir del bucle cuando se ingresa "4"
		}
		switch(opcion)
		{
			case 1:
				printf("¿Desea cargar el UNO?\n");		
			        printf("1. Sí\n2. No\n");
				char* cadena = uno();

				printf("*********************************************************\n");
				printf("Juego cargado con éxito. Volviendo al menú......\n");
				printf("*********************************************************\n");
				write(file_descriptor, cadena, strlen(cadena));
				continue;
			case 2:
				printf("¿Desea cargar el RUMI?\n1. Sí\n2. No\n");
				continue;
			default:
				continue;

		}		
		tcdrain(file_descriptor);
		sleep(1);
	}
	close(file_descriptor);

	return 0;

}
