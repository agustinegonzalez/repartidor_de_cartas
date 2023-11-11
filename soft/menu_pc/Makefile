CC = gcc
CFLAGS = -Wall
LIBS = -ludev

SRCS = termset.c menu_pc.c
OBJS = $(SRCS:.c=.o)
TARGET = repartidor_app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

