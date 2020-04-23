#include <stdio.h>
#include <pcap/pcap.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
typedef struct ether_header ethernet_header;
typedef struct item{

  struct pcap_pkthdr* packet_header;
  char* full_packet;  
  short int garbage; /* marked for collection */
  struct __item* prev; /* item in front */
  struct __item* next; /* next item */

}item;


void pcap_callback (unsigned char * arg, const struct pcap_pkthdr *pkthdr, const unsigned char * packet);
