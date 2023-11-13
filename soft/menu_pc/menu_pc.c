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


int main(int argc, char *argv[])
{
	int file_descriptor;
	struct termios oldtty, newtty;
	uint8_t opcion = 0;
	uint8_t juego = 0;
	const char *puerto = encontrarPuertoSerieArduino();
	char cadena[1];
	char cadena_rec[3];

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
		printf("3. Leer juegos cargados\n");
		printf("4. Salir\n");
		
		scanf("%hhu", &opcion);
		
		if (opcion == 4) {
			break;  // Salir del bucle cuando se ingresa "4"
		}
		switch(opcion)
		{
			case 1:
				do{
				printf("Seleccione el juego que desea cargar:\n");
				printf("1. UNO\n2. RUMI\n3. CHANCHO\n");
				scanf("%hhu",  &juego);
				}while(juego < 1 || juego > 3);

				if(juego == 1){
					cadena[0] =  'u';
				} else if(juego == 2){
					cadena[0] = 'r';
				} else if(juego == 3){
					cadena[0] = 'c';
				}
				
				write(file_descriptor, cadena, 1);
				printf("*********************************************************\n");
				printf("Juego cargado con éxito. Volviendo al menú......\n");
				printf("*********************************************************\n");
				
				continue;
			case 2:
				do{
				printf("Seleccione el juego que desea borrar:\n");
				printf("1. UNO\n2. RUMI\n3. CHANCHO\n");
				scanf("%hhu",  &juego);
				}while(juego < 1 || juego > 3);

				if(juego == 1){
					cadena[0] = 'U';
				} else if(juego == 2){
					cadena[0] = 'R';
				} else if(juego == 3){
					cadena[0] = 'C';
				}

				write(file_descriptor, cadena, 1);
				printf("*********************************************************\n");
				printf("Juego borrado con éxito. Volviendo al menú......\n");
				printf("*********************************************************\n");
				continue;
			case 3:
				cadena[0]='$';
				write(file_descriptor, cadena, 1);
				read(file_descriptor,cadena_rec,3);
				printf("Los juegos cargados son:\n");
				if(cadena_rec[0] == 'u' || cadena_rec[1] == 'u' || cadena_rec[2] == 'u'){
					printf("UNO\n");
				}else if(cadena_rec[0] == 'r' || cadena_rec[1] == 'r' || cadena_rec[2] == 'r'){
					printf("RUMI\n");
				}else if(cadena_rec[0] == 'c' || cadena_rec[1] == 'c' || cadena_rec[2] == 'c'){
					printf("CHANCHO\n");
				}else
					printf("0 juegos cargados\n");
				
			default:
				continue;

		}	
			tcdrain(file_descriptor);
		sleep(1);
	}
	close(file_descriptor);

	return 0;
}
