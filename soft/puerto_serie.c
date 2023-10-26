#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>




int main(int argc, int argv[])
{
	int file_descriptor;

	file_descriptor = open("/dev/ttyUSB0", O_RDONLY);

	if(file_descritor == -1)
	{
		exit(1);	
	}

	close(file_descriptor);

	return 0;

}
