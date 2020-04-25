#include "header_files.h"

typedef struct tcp_segment{
    unsigned int port;
    int syn;
    int ack;
    int syn_ack;
    struct tcp_segment *next;
}tcp_segment;