#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "termset.h"
#include <stdint.h>
#include <string.h>
#include "libudev.h"

#define FALSE 0
#define TRUE 1

const char *encontrarPuertoSerieArduino() {
	
	struct udev *udev = udev_new();
	
	if (!udev) {
		fprintf(stderr, "Error al inicializar udev\n");
	return NULL;
	}

	struct udev_enumerate *enumerate = udev_enumerate_new(udev); 
	udev_enumerate_add_match_subsystem(enumerate, "tty"); 
	udev_enumerate_scan_devices(enumerate);

	struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
	struct udev_list_entry *entry;

	const char *nombrePuertoSerie = NULL;

	udev_list_entry_foreach(entry, devices) { 
		const char *path = udev_list_entry_get_name(entry); 
		struct udev_device *device = udev_device_new_from_syspath(udev, path); 
		const char *devnode = udev_device_get_devnode(device); 
		if (devnode) {
			if (strstr(devnode, "ttyACM") || strstr(devnode, "ttyUSB")) {
				nombrePuertoSerie = devnode;
				break; 
			}
		}

		udev_device_unref(device);
	}

	udev_enumerate_unref(enumerate);
	udev_unref(udev);

	return nombrePuertoSerie;
}


int main(int argc, char *argv[])
{
	int file_descriptor;
	uint8_t opcion = 0;
	struct termios oldtty, newtty;
	const char *puerto = encontrarPuertoSerieArduino();
	
	
	file_descriptor = open(puerto, O_RDWR | O_NOCTTY | O_NDELAY);
	
	if(file_descriptor == -1)
	{
		printf("ERROR: no se pudo abrir el dispositivo.\n");
		exit(1);	
	}

	if(termset(file_descriptor, 9600, &oldtty, &newtty) == -1) /*configuro el terminal serie con una velocidad de 9600 baudios*/
	{
		printf("ERROR: no se pudo configurar el tty.\n");
		exit(2);
	}
	
	tcflush(file_descriptor, TCIOFLUSH); /*Vacío el buffer de entrada y salida del terminal serie*/
	
	for (;;) {
		printf("\tR E P A R T I D O R    D E    C A R T A S\n");
		printf("1. Obtener puntuación\n");
		printf("2. Salir\n");
		
		scanf("%hhu", &opcion);
		
		if (opcion == 2)
			break; 		
		switch(opcion)
		{
			case 1:
				write(file_descriptor, "a", 1);
				continue;
			default:
				continue;

		}	
			tcdrain(file_descriptor); /* espera a que todos los datos pendientes de escritura en el descriptor de archivo del terminal (file_descriptor) se hayan transmitido físicamente al dispositivo antes de continuar*/
		sleep(1); /*Pausa la ejecucion del programa durante 1seg*/
	}
	close(file_descriptor);

	return 0;
}
