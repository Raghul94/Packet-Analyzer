CC= gcc
CFLAGS= -g -Wall #-DDEBUG
INCLUDES= -I. -I/usr/include/pcap/ #make sure you got the right path of pcap.h on your machine
#LIBS= -L/usr/local/lib -lpcap #again, this is usually -lpcap unless you installed it under different name
#if the linker gives an error (or a whole bunch of them) then you probably
#don't have libpcap.so to fix the problem make the above line
LIBS= /usr/local/lib/libpcap.a

OBJS = pcap_helper.o connections.o
EXEC= myprog

all: pcap_helper.o connections.o main.c Makefile
	$(CC) $(CFLAGS) $(INCLUDES) main.c  $(OBJS) $(LIBS) -o $(EXEC)

pcap_helper.o: pcap_helper.h pcap_helper.c Makefile
	$(CC) $(CFLAGS) $(INCLUDES) -c pcap_helper.c

connections.o: connections.h connections.c Makefile
	$(CC) $(CFLAGS) $(INCLUDES) -c connections.c

#tcp_list.o: tcp_list.h tcp_list.c Makefile
	#$(CC) $(CFLAGS) $(INCLUDES) -c tcp_list.c

#ip_list.o: ip_list.h ip_list.c Makefile
	#$(CC) $(CFLAGS) $(INCLUDES) -c ip_list.c

clean:
	rm -rf *.o *~ $(EXEC) core
