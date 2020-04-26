#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "pcap_helper.h"
#include <time.h>
int main(int argc, char ** argv)
{
    FILE *fp;
    pcap_t *pcap_handle;
    time_t start, end;
    /* Sanity check */
    if(argc < 2){
        printf("Usage: ./myprog \"pcapfile\" no_of_packets");
        exit(0);
    }
    if((fp  = fopen(argv[1],"r"))== NULL){
        printf("Error opening trace file\n");
        exit(-1);
    }
    int no_of_packets;
    if(argc < 3 )
        no_of_packets = -1;
    else
        no_of_packets  = atoi(argv[2]); 
    char errbuf[PCAP_ERRBUF_SIZE];
    if((pcap_handle = pcap_fopen_offline(fp,errbuf)) == NULL){//Handle to the pcap file
        printf("Error while creating the handle for the trace file\n");
        exit(-1);
    }
    time(&start);
    pcap_loop(pcap_handle,no_of_packets,pcap_callback,NULL);//Function that "sniffs" packets
    time(&end);
    printf("Time taken to process packets: %f\n",difftime(end,start));
    fclose(fp);
    return 0;
}
