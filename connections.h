#include "header_files.h"

typedef struct ether_header ethernet_header;
typedef struct iphdr ip_header;
typedef struct tcphdr tcp_header;

typedef struct connection{
    unsigned long int saddr;
    unsigned long int daddr;
    int sport;
    int dport;
    int syn;
    int ack;
    float syn_ack;
    struct connection* next;
}connection;

int check_if_connection_exists(struct connection *, const unsigned char*);//Check if connection already exists
void handle_connection(const unsigned char*);
void add_connection(struct connection*, const unsigned char *);//add new connection