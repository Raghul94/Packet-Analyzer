#include "pcap_helper.h"
#include <malloc.h>
void pcap_callback (unsigned char * arg, const struct pcap_pkthdr *pkthdr, const unsigned char * packet){
    //ethernet_header *eptr;
    ip_header *ip_hdr;
    tcp_header *tcp_hdr;
    //unsigned char* ptr;
    struct in_addr ipaddr;
    item *tmp = (struct item *)arg;
    tmp->packet_header= (struct pcap_pkthdr *) malloc(sizeof(struct pcap_pkthdr));
    tmp->full_packet= (char *)malloc((pkthdr->caplen));
    //eptr= (ethernet_header *) tmp;
    ip_hdr = (ip_header *)(tmp + sizeof(ethernet_header));
    ipaddr.s_addr = (unsigned long int)ip_hdr->saddr;
    printf("Source IP addr: %s\n",inet_ntoa(ipaddr)); //Print Source IP
    ipaddr.s_addr = (unsigned long int)ip_hdr->daddr;
    printf("Destination IP addr:%s \n",inet_ntoa(ipaddr)); //Print Destination IP
    tcp_hdr = (tcp_header *)(tmp + sizeof(ethernet_header) + sizeof(ip_header));
    printf("TCP Source : %u\n",tcp_hdr->source); //Print TCP Source
    printf("TCP Destination : %u\n",tcp_hdr->dest); //Print TCP Source
    printf("TCP SYN: %d TCP ACK: %d\n",tcp_hdr->syn,tcp_hdr->ack);
    printf("\n\n\n\n\n\n");

}
