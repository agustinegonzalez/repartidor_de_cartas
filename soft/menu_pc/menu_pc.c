#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "termset.h"
#include <stdint.h>
#include <string.h>
#include "libudev.h"
#include <errno.h>



const char* encontrarPuertoSerieArduino();

int main(int argc, char *argv[])
{
	int file_descriptor;
	uint8_t opcion = 0;
	struct termios oldtty, newtty;
	const char *puerto = encontrarPuertoSerieArduino();
	char *cadena;

	file_descriptor = open(puerto, O_RDWR | O_NOCTTY);
	sleep(1);	
	
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
	
	do{
	printf("\tR E P A R T I D O R    D E    C A R T A S\n");
	printf("1. Obtener puntuación\n");
	printf("2. Salir\n");

	scanf("%hhu", &opcion);
	}while(opcion < 1 || opcion > 2);

	if(opcion == 2)
		return 1;

	if(opcion == 2)
		return 1;
	cadena = "Cargado"; 	
	write(file_descriptor, cadena, strlen(cadena));
	
	tcdrain(file_descriptor); /* espera a que todos los datos pendientes de escritura en el descriptor de archivo del terminal (file_descriptor) se hayan transmitido físicamente al dispositivo antes de continuar*/
	sleep(1); /*Pausa la ejecucion del programa durante 1seg*/
	
	char buff[9];
	int n;
	n = read(file_descriptor, buff, strlen("Recibido"));

	if (n == -1){
   
		switch(errno){
			case EBADF:{
			    printf("Bad file number. Error: %i\n", errno);
			    break;}
			case EINVAL:{
			    printf("Invalid argument. Error: %i\n", errno);
		    	break;}
			case EIO:{
		    		printf("I/O error . Error: %i\n", errno);
		   	 break;}
			case EPERM:
				 printf("Operación no permitida");
				break;
			case EINTR:
				printf("System call interrumpted\n");	
				break;
			case EFBIG:
				printf("File too big");
				break;
			case EFAULT:
				printf("incorrect adress");
				break;
			case EDESTADDRREQ:
				printf("Direccion de destinacion requerida" );
			case EAGAIN:
				printf("try again " );
				break;
		}	
	}else 
		printf("La cadena obtenida es: %s\n", buff);
		
	close(file_descriptor);
	
	return 0;
}


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


