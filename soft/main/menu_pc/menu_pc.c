#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "termset.h"
#include <stdint.h>
#include <string.h>
#include "libudev.h"
/*Se incluyen las bibliotecas estándar de entrada/salida, gestión de archivos, memoria dinámica, manipulación de cadenas, 
 * y las bibliotecas necesarias para interactuar con un dispositivo serie y para la gestión de dispositivos a través de udev*/


#define FALSE 0
#define TRUE 1

volatile int STOP=FALSE;
const char *encontrarPuertoSerieArduino() {
	
	struct udev *udev = udev_new();
	
	if (!udev) {
		fprintf(stderr, "Error al inicializar udev\n");
	return NULL;
	}

	struct udev_enumerate *enumerate = udev_enumerate_new(udev); /*puntero a una estructura udev_enumerate que se utiliza para realizar la enumeración de dispositivos.*/
	udev_enumerate_add_match_subsystem(enumerate, "tty"); /*agregar una regla de coincidencia al enumerador udev. Está indicando que se deben enumerar solo los dispositivos que pertenecen al subsistema especificado.*/
	udev_enumerate_scan_devices(enumerate);

	struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
	struct udev_list_entry *entry;

	const char *nombrePuertoSerie = NULL;

	udev_list_entry_foreach(entry, devices) { /* Recorre cada elemento (entry) en la lista de dispositivos (devices). Dentro de este bucle, se accede a información específica sobre el dispositivo utilizando funciones de la biblioteca libudev. En este caso, se está buscando un dispositivo que cumpla con ciertas condiciones, como pertenecer al subsistema "tty" y tener un nombre de dispositivo que contenga "ttyACM" o "ttyUSB".*/
		const char *path = udev_list_entry_get_name(entry); /*Se obtiene el nombre del syspath para el dispositivo actual en la iteración del bucle.*/ 
		struct udev_device *device = udev_device_new_from_syspath(udev, path); /*Se utiliza el syspath obtenido para crear una nueva instancia de la estructura udev_device*/
		const char *devnode = udev_device_get_devnode(device); /* Se obtiene el nodo de dispositivo (devnode) asociado al dispositivo. El devnode es la interfaz de usuario en el sistema de archivos a través de la cual el dispositivo se puede acceder */

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

typedef union{

	unsigned char uc[4];
	int i;


} int_uchar_t;

int main(int argc, char *argv[])
{
	int file_descriptor;
	uint8_t opcion = 0;
	struct termios oldtty, newtty;
	const char *puerto = encontrarPuertoSerieArduino();
	int_uchar_t i_uc;	
	
	
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
			break;  // Salir del bucle cuando se ingresa "4"
		
		switch(opcion)
		{
			case 1:
				write(file_descriptor, "a", 1);
 			size_t n = read(file_descriptor, &(i_uc.uc[0]), 4);
			       printf("%d\n\n", i_uc.i);
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
