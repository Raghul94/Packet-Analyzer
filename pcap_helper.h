#include "header_files.h"
#include "connections.h"
typedef struct ether_header ethernet_header;
typedef struct iphdr ip_header;
typedef struct tcphdr tcp_header;


void pcap_callback (unsigned char * arg, const struct pcap_pkthdr *pkthdr, const unsigned char * packet);
