#include "pcap_helper.h"
#include <malloc.h>
void pcap_callback (unsigned char * arg, const struct pcap_pkthdr *pkthdr, const unsigned char * packet){
    ethernet_header *eptr;
    unsigned char* ptr;
    item *tmp = (struct item *)arg;
    tmp->packet_header= (struct pcap_pkthdr *) malloc(sizeof(struct pcap_pkthdr));
    tmp->full_packet= (char *)malloc((pkthdr->caplen));
    eptr= (ethernet_header *) tmp;
    ptr = eptr->ether_dhost;
    printf("%x:%x:%x:%x:%x:%x\n",*ptr,*(ptr+1),*(ptr+2),*(ptr+3),*(ptr+4),*(ptr+5));
}
