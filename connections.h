#include "header_files.h"

typedef struct ether_header ethernet_header;
typedef struct iphdr ip_header;
typedef struct tcphdr tcp_header;

typedef struct ip_source{
	unsigned long int ip_addr;
	struct ip_source *next;
	struct ip_dest* head;
}ip_source;

typedef struct ip_dest{
	unsigned long int ip_addr;
	struct ip_dest *next;
	struct tcp_segment *head;
}ip_dest;

typedef struct tcp_segment{
	int src_port;
	int dest_port;
	int syn;
	int ack;
	int syn_ack;
	float syn_to_synack;
	struct tcp_segment *next;
}tcp_dest;

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

int check_if_connection_exists(struct ip_source *, const unsigned char*);//Check if connection already exists
void handle_connection(const unsigned char*);
void handle_synack_response(struct ip_source*, const unsigned char*);
void add_connection(struct ip_source *, const unsigned char *);//add new connection
