#include "tcp_list.h"

typedef struct ip_list_node{
    unsigned long int ip_addr;
    struct iphdr *ip_header;
    struct ip_list_node* next;
    struct tcp_segment *first;
}ip_datagram;

void insert_in_ip_list(struct ip_list_node*, struct iphdr*);
int check_if_ip_exists(struct ip_list_node*,unsigned long int);