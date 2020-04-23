#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "pcap_helper.h"


//void pcap_callback (unsigned char * arg, const struct pcap_pkthdr *pkthdr, const unsigned char * packet);
int main(int argc, char ** argv)
{
    FILE *fp = fopen(argv[1],"r"); //open the trace file
    /* Sanity check */
    if(argc < 2){
        printf("Usage: ./myprog \"pcapfile\" no_of_packets");
        exit(0);
    }
    if(fp == NULL){
        printf("Error opening trace file\n");
        exit(-1);
    }
    int no_of_packets;
    if(argc < 3 )
        no_of_packets = -1;
    else
        no_of_packets  = atoi(argv[2]); 
    item *packet = (struct item *)malloc(sizeof(struct item)); 
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap_handle = pcap_fopen_offline(fp,errbuf);//Handle to the pcap file
    if(pcap_handle == NULL){
        printf("Error while creating pcap handle\n");
        exit(-1);
    
    pcap_loop(pcap_handle,no_of_packets,pcap_callback,(void *)packet);//Function that "sniffs" packets
    fclose(fp);
    return 0;
}
