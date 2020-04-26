#include "connections.h"


int check_if_connection_exists(struct ip_source * head, const unsigned char* packet){
    //printf("Here\n");
    int size_ethernet,size_ip;//size_tcp;
    struct ip_source *temp_ip_source = head->next;
    struct ip_dest *temp_ip_dest;
    struct tcp_segment *temp_tcp_segment;
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
    while(temp_ip_source){
        if(temp_ip_source->ip_addr == ip->saddr){
            temp_ip_dest = temp_ip_source->head;
            while(temp_ip_dest){
                if(temp_ip_dest->ip_addr == ip->daddr){
                    temp_tcp_segment = temp_ip_dest->head;
                    while(temp_tcp_segment){
                        if(temp_tcp_segment->src_port == tcp->source && temp_tcp_segment->dest_port == tcp->dest){
                            if(temp_tcp_segment->syn == 1 && temp_tcp_segment->ack != 1){
                                printf("%d\n",temp_tcp_segment->syn);
                                temp_tcp_segment->syn += 1;
                                printf("%d\n",temp_tcp_segment->syn);
                            }
                            return 0;
                        }
                        temp_tcp_segment = temp_tcp_segment->next;
                    }
                    return -1;
                }
                temp_ip_dest = temp_ip_dest->next;
            }

        }
        temp_ip_source = temp_ip_source->next;
    }
    return -1;
}

void add_connection(struct ip_source* head,const unsigned char *packet){
    struct ip_source *temp = head;
    int size_ethernet,size_ip;//size_tcp;
    struct iphdr* ip;
    struct tcphdr *tcp;


    size_ethernet = sizeof(struct ether_header);
    ip = (struct iphdr *)(packet + size_ethernet);
    size_ip = ip->ihl*4;
    tcp = (struct tcphdr *)(packet + size_ethernet + size_ip);
    struct ip_source *prev;
    while(temp){
        prev = temp;
        /*Source IP already exists */
        if(prev->ip_addr == ip->saddr){
            struct ip_dest *temp_ip_dest_1,*temp_ip_dest_2;
            temp_ip_dest_1 = prev->head;
            while(temp_ip_dest_1 != NULL){
                temp_ip_dest_2 = temp_ip_dest_1;
                /*Connection already exists between source and destination IPs. Only establish connection between TCP ports */
                if(temp_ip_dest_2->ip_addr == ip->daddr){
                    struct tcp_segment *temp_tcp = temp_ip_dest_2->head;
                    while(temp_tcp->next)
                        temp_tcp = temp_tcp->next;
                    temp_tcp->next = (struct tcp_segment *)malloc(sizeof(struct tcp_segment));
                    if(temp_tcp->next == NULL){
                        printf("Unable to allocate memory\n");
                        return;
                    }
                    temp_tcp = temp_tcp->next;
                    temp_tcp->src_port = tcp->source;
                    temp_tcp->dest_port = tcp->dest;
                    temp_tcp->syn = tcp->syn;
                    temp_tcp->ack = tcp->ack;
                    temp_tcp->syn_ack = tcp->syn&tcp->ack;
                    return;
                }
                temp_ip_dest_1 = temp_ip_dest_1->next;
            }
            /*Connetion to destination IP does not exist. Create one. */
            temp_ip_dest_2->next = (struct ip_dest *)malloc(sizeof(ip_dest));
            if(temp_ip_dest_2 == NULL){
                printf("Unable to allocate memory\n");
                return;
            }
            temp_ip_dest_2 = temp_ip_dest_2->next;
            temp_ip_dest_2->ip_addr = ip->daddr;
            temp_ip_dest_2->head = (struct tcp_segment *)malloc(sizeof(struct tcp_segment));
            if(temp_ip_dest_2->head == NULL){
                printf("Unable to allocate memory\n");
                return;
            }
            temp_ip_dest_2->head->src_port = tcp->source;
            temp_ip_dest_2->head->dest_port = tcp->dest;
            temp_ip_dest_2->head->syn = tcp->syn;
            temp_ip_dest_2->head->ack = tcp->ack;
            temp_ip_dest_2->head->syn_ack = tcp->syn&tcp->ack;
            return;
        }
        temp = temp->next;
    }
    /*Source IP does not exist. Creating a new node for the source IP */
    prev->next = (struct ip_source *)malloc(sizeof (struct ip_source));
    if(prev->next == NULL){
        printf("Unable to allocate memory for new packet\n");
        return;
    }
    prev = prev->next;
    prev->ip_addr = ip->saddr;
    prev->head = (struct ip_dest *)malloc(sizeof(ip_dest));
    if(prev->head == NULL){
        printf("Unable to allocate memory\n");
        return;
    }
    prev->head->ip_addr = ip->daddr;
    prev->head->head = (struct tcp_segment *)malloc(sizeof(struct tcp_segment));
    prev->head->head->src_port = tcp->source;
    prev->head->head->dest_port = tcp->dest;
    prev->head->head->syn = tcp->syn;
    prev->head->head->ack = tcp->ack;
    prev->head->head->syn_ack = tcp->syn&tcp->ack;
    return;
    
}
void handle_synack_response(struct ip_source* head, const unsigned char* packet){
    int size_ethernet,size_ip;//size_tcp;
    struct iphdr* ip;
    struct tcphdr *tcp;
    size_ethernet = sizeof(struct ether_header);
    ip = (struct iphdr *)(packet + size_ethernet);
    size_ip = ip->ihl*4;
    tcp = (struct tcphdr *)(packet + size_ethernet + size_ip);
    struct ip_source *temp_ip_source;
    struct ip_dest *temp_ip_dest;
    struct tcp_segment *temp_tcp_segment;
    temp_ip_source = head->next;
    struct in_addr ipaddr;
    // ipaddr.s_addr = (unsigned long int)ip->saddr;
    // printf("%s:%d\n",inet_ntoa(ipaddr),ntohs(tcp->source));
    // ipaddr.s_addr = (unsigned long int)ip->daddr;
    // printf("%s:%d\n",inet_ntoa(ipaddr),ntohs(tcp->dest));
    while(temp_ip_source){
        //printf("here\n");
        if(temp_ip_source->ip_addr == ip->daddr){
            ipaddr.s_addr = (unsigned long int)ip->daddr;
            //printf("%s:%d\n",inet_ntoa(ipaddr),ntohs(tcp->dest));
            //printf("Here1\n");
            temp_ip_dest = temp_ip_source->head;
            while(temp_ip_dest){
                if(temp_ip_dest->ip_addr == ip->saddr){
                    //printf("Here2\n");
                    ipaddr.s_addr = (unsigned long int)ip->saddr;
                    //printf("%s:%d\n",inet_ntoa(ipaddr),ntohs(tcp->source));
                    temp_tcp_segment = temp_ip_dest->head;
                    while(temp_tcp_segment){
                        if(temp_tcp_segment->src_port == tcp->dest && temp_tcp_segment->dest_port == tcp->source){
                            temp_tcp_segment->syn_ack+=1;
                            temp_tcp_segment->syn_to_synack = temp_tcp_segment->syn_ack/temp_tcp_segment->syn;
                            if(temp_tcp_segment->syn_to_synack > 3)
                                printf("Warning\n");
                            //printf("%f\n",temp_tcp_segment->syn_to_synack);
                            return;
                        }
                        temp_tcp_segment = temp_tcp_segment->next;
                    }
                    //return;
                }
                temp_ip_dest = temp_ip_dest->next;
            }
           // return;
        }
        temp_ip_source = temp_ip_source->next;
    }
    return;
}
void handle_connection(const unsigned char* packet){   
    static int first = 0;
    static int count = 1;
    static struct ip_source *head;
    int size_ethernet,size_ip;//size_tcp;
    struct iphdr* ip;
    struct tcphdr *tcp;
    size_ethernet = sizeof(struct ether_header);
    ip = (struct iphdr *)(packet + size_ethernet);
    size_ip = ip->ihl*4;
    if(size_ip < 20){ //Improper IP header
        printf("IP size %d\n",size_ip);
        return;
    }
    if(ip->protocol != IPPROTO_TCP) //Handle only TCP Connections
        return;
    tcp = (struct tcphdr *)(packet + size_ethernet + size_ip);
    if(!first){//Process the first packet in the list
        head = (struct ip_source *)malloc(sizeof(struct ip_source));
        first++;
    }
    if(check_if_connection_exists(head,packet)!=0){//Update the connection
        //printf("New connection\n");
        add_connection(head,packet);
        //count++;
        //printf("%d\n",count);
    }
    if(tcp->syn == 1 && tcp->ack==1){
    //call the function to check and update
        handle_synack_response(head,packet);
        //printf("Packet no: %d\n",count); 
    }
    count++;
}