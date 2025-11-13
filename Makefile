NAME:= nfc_reader
# CC:= aarch64-linux-gnu-gcc -gnu
CC:= gcc
CFLAGS:= -Wall -Wextra -Werror -g

LIB_DIR:= -L./lib
LIBS:= -lcomPro
INCLUDE_DIR:= -I./include

SRCS:=	main.c \
		rfid.c	\
		barcode.c \
		utils.c

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDE_DIR) $^ -o $@ $(LIB_DIR) $(LIBS) $(LDFLAGS)

clean:
	rm -f $(NAME)
