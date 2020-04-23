CC= gcc
CFLAGS= -g -Wall -DDEBUG
INCLUDES= -I. -I/usr/include/pcap/ #make sure you got the right path of pcap.h on your machine
#LIBS= -L/usr/local/lib -lpcap #again, this is usually -lpcap unless you installed it under different name
#if the linker gives an error (or a whole bunch of them) then you probably
#don't have libpcap.so to fix the problem make the above line
LIBS= /usr/local/lib/libpcap.a

OBJS = pcap_helper.o
EXEC= myprog

all: pcap_helper.o main.c Makefile
	$(CC) $(CFLAGS) $(INCLUDES) main.c  $(OBJS) $(LIBS) -o $(EXEC)

buffer.o: pcap_helper.h pcap_helper.c Makefile
	$(CC) $(CFLAGS) $(INCLUDES) -c buffer.c

clean:
	rm -rf *.o *~ $(EXEC) core
