#include "main.h"

int	safe_thread_printf(t_data *data, const char *format, ...)
{
	va_list args;
	int ret;

	pthread_mutex_lock(&data->mutex);
	va_start(args, format);
	ret = vprintf(format, args);
	va_end(args);
	pthread_mutex_unlock(&data->mutex);
	return ret;
}

int safe_thread_perrror(t_data *data, const char *message)
{
	int errnum = errno;
	pthread_mutex_lock(&data->mutex);
	perror(message);
	pthread_mutex_unlock(&data->mutex);
	errno = errnum;
	return -1;
}

void init_data(t_data *data)
{
	data->program_running = 1;
	
	if ( (data->NFCReader_hdev = usbRFIDreader_init()) == -1)
	{
		perror("Failed to initialize USB RFID reader\n");
		exit(-1);
	}
	if ( (data->barcode_scanner = init_barcode_scanner()) == NULL)
	{
		perror("Failed to initialize barcode scanner\n");
		exit(-1);
	}
	if (pthread_mutex_init(&data->mutex, NULL) != 0)
	{
		perror("Failed to initialize mutex\n");
		close_barcode_scanner(data->barcode_scanner);
		exit(-1);
	}
}
