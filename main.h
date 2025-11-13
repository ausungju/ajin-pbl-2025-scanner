

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <termios.h>
# include <pthread.h>
# include <stdarg.h>
# include <signal.h>
# include <errno.h>

# include "comPro.h"

# define BAUDRATE 115200
# define BUFFER_SIZE 1024
# define NFC_SERIAL_LEN_MAX 17

# define NFC_LED1 1
# define NFC_LED2 2
# define NFC_LED_ON  1
# define NFC_LED_OFF 0

typedef struct s_data
{
	FILE			*barcode_scanner;
	int				NFCReader_hdev;
	pthread_mutex_t	mutex;
	int				program_running;
}	t_data;

// rfid.c
int usbRFIDreader_init();
// int detectCards(int hdev);
int detectCards(t_data *data);
void test_led(int hdev);

// barcode.c
FILE *init_barcode_scanner();
void loop_barcode_scan(t_data *data);
void close_barcode_scanner(FILE *serial_port);

// utils.c
int	safe_thread_printf(t_data *data, const char *format, ...);
int safe_thread_perrror(t_data *data, const char *message);
void init_data(t_data *data);


#endif /* MAIN_H */
