#include "ip_list.h"

int check_if_ip_exists(struct ip_list_node* header,unsigned long int ip_addr){
    struct ip_list_node* temp = header;
    while(temp != NULL){
        if(temp->ip_addr == ip_addr)
            return 0;
        temp = temp->next;
    }
    return -1;
}

void insert_in_ip_list(struct ip_list_node* header, struct iphdr* ip_hdr){
    unsigned long int ip_addr;
    if(ip_hdr != NULL)
        ip_addr = (unsigned long int)ip_hdr->saddr;
    if(header == NULL){
        fprintf(stdout,"Wrong value in insert_in_ip_list()\n");
        return;
    }
    if(check_if_ip_exists(header,ip_addr)!=0){
        struct ip_list_node* temp = header;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = (struct ip_list_node*)malloc(sizeof(struct ip_list_node));
        temp = temp->next;
        temp->ip_addr = ip_addr;
        temp->ip_header = (struct iphdr *)malloc(sizeof(struct iphdr));
    }
    //code to insert the tcp_segment

}