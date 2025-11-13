#include "main.h"

FILE *init_barcode_scanner()
{
	char device[] = "/dev/ttyACM0";
	FILE *serial_port;

	serial_port = fopen(device, "r+");
	if (serial_port == NULL) {
		perror("Error opening serial port");
		return NULL;
	}
	tcflush(fileno(serial_port), TCIOFLUSH);
	return serial_port;
}

void loop_barcode_scan(t_data *data)
{
	char buffer[BUFFER_SIZE];

	while (1) {
		if (fgets(buffer, BUFFER_SIZE, data->barcode_scanner) != NULL)
			safe_thread_printf(data, "Scanned Barcode: %s", buffer);
		else 
		{
			safe_thread_perrror(data, "Error reading from barcode scanner");
			break;
		}

		if (!data->program_running)
			return;
		usleep(1000);
	}
}

void close_barcode_scanner(FILE *serial_port)
{
	if (serial_port != NULL) {
		fclose(serial_port);
	}
}