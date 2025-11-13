
#include "main.h"

int main()
{
	t_data data;

	init_data(&data);
	pthread_t barcode_thread, nfc_thread; //, API_socket;
	if (pthread_create(&barcode_thread, NULL, (void *)loop_barcode_scan, (void *)&data) != 0 || \
		pthread_create(&nfc_thread, NULL, (void *)detectCards, (void *)&data) != 0 )
		// pthread_create(&API_socket, NULL, (void *)API_communicate, (void *)&data != 0))
	{
		printf("Failed to create barcode scanning thread\n");
		return -1;
	}

	pthread_join(barcode_thread, NULL);
	pthread_join(nfc_thread, NULL);
	// pthread_join(API_socket, NULL);
	
    return 0;
}