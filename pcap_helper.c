#include "pcap_helper.h"
void pcap_callback (unsigned char * arg, const struct pcap_pkthdr *pkthdr, const unsigned char * packet){
    ethernet_header *eptr;
    static int count = 0;
    eptr= (ethernet_header *) packet;
    if(ntohs(eptr->ether_type) == ETHERTYPE_IP)
        handle_connection(packet);
    count++;//Number of Packets Processed

}
