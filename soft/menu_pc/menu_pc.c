#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "termset.h"
#include <stdint.h>
#include <string.h>
#include <libudev.h>

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
		// Comprueba si el nombre del dispositivo contiene "ttyACM" o "ttyUSB"
			if (strstr(devnode, "ttyACM") || strstr(devnode, "ttyUSB")) {
				nombrePuertoSerie = devnode;
				break; // Se encontró el puerto, salimos del bucle
			}
		}

		udev_device_unref(device);
	}

	udev_enumerate_unref(enumerate);
	udev_unref(udev);

	return nombrePuertoSerie;
}


char* uno()
{
	char *cadena;
	uint8_t cargapositiva = 0;
       	scanf("%hhu", &cargapositiva);
        if (cargapositiva == 1) {
		
	
       
       	}else
		exit(1);

	return (cadena = "CARGAUNO");
}

int main(int argc, char *argv[])
{
	int file_descriptor;
	struct termios oldtty, newtty;
	uint8_t opcion = 0;
	const char *puerto = encontrarPuertoSerieArduino();
	
	printf("%s\n", puerto);
	file_descriptor = open(puerto, O_RDWR | O_NOCTTY | O_NDELAY);
	
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
				write(file_descriptor, cadena, sizeof(cadena));
				continue;
			case 2:
				printf("¿Desea cargar el RUMI?\n1. Sí\n2. No\n");
				continue;
			default:
				continue;

		}	
		printf("*********************************************************\n");
		printf("Juego cargado con éxito. Volviendo al menú......\n");
		printf("*********************************************************\n");

		tcdrain(file_descriptor);
		sleep(1);
	}
	close(file_descriptor);

	return 0;

}
