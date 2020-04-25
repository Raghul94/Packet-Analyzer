#include "connections.h"


int check_if_connection_exists(struct connection * head, const unsigned char* packet){
    //printf("Here\n");
    int size_ethernet,size_ip;//size_tcp;
    struct connection *temp = head->next;
    struct iphdr* ip;
    struct tcphdr *tcp;
    size_ethernet = sizeof(ethernet_header);
    ip = (struct iphdr *)(packet + size_ethernet);
    size_ip = ip->ihl*4;
    tcp = (struct tcphdr *)(packet + size_ethernet + size_ip);
    #ifdef DEBUG
        struct in_addr source_ip,dest_ip;
        source_ip.s_addr = (unsigned long int)ip->saddr;
        dest_ip.s_addr = (unsigned long int)ip->saddr;
        printf("%s %s\n",inet_ntoa(source_ip),inet_ntoa(dest_ip));
    #endif
    if(!temp)
        return -1;
    while(temp != NULL){
        if(temp->saddr){
            if(temp->saddr == ip->saddr && temp->sport == tcp->source && temp->daddr == ip->daddr && temp->dport == tcp->dest)
                return 0;
        }
        temp = temp->next;
    }
    return -1;
}

void add_connection(struct connection* head,const unsigned char *packet){
    struct connection *temp = head;
    int size_ethernet,size_ip;//size_tcp;
    struct iphdr* ip;
    struct tcphdr *tcp;


    size_ethernet = sizeof(ethernet_header);
    ip = (struct iphdr *)(packet + size_ethernet);
    size_ip = ip->ihl*4;
    if(size_ip < 20){
        printf("IP size %d\n",size_ip);
        return;
    }
    if(ip->protocol != IPPROTO_TCP)
        return;
    tcp = (struct tcphdr *)(packet + size_ethernet + size_ip);
    while(temp->next)
        temp = temp->next;
    temp->next = (struct connection *)malloc(sizeof (struct connection));
    if(temp->next == NULL){
        printf("Unable to allocate memory for new packet\n");
        return;
    }
    temp = temp->next;
    temp->saddr     = ip->saddr;
    temp->daddr     = ip->daddr;
    temp->sport     = tcp->source;
    temp->dport     = tcp->dest;
    temp->syn       = tcp->syn;
    temp->ack       = tcp->ack;
    temp->syn_ack   = 0;
    //printf("Connection create\n");
    return;
    
}
void handle_connection(const unsigned char* packet){   
    static int first = 0;
    static int count = 0;
    static struct connection *head;
    if(!first){//Process the first packet in the list
        head = (struct connection *)malloc(sizeof(struct connection));
        first++;
    }
    if(check_if_connection_exists(head,packet)!=0){//Update the connection
    printf("New connection\n");
        add_connection(head,packet);
        count++;
        printf("%d\n",count);
    }
    else{
        //printf("connection exists\n");
        //do something
    }
}