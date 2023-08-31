#include <arpa/inet.h> 
#include <linux/if_packet.h> 
#include <net/if.h> 
#include <netinet/if_ether.h> 
#include <netinet/in.h> 
#include <netinet/ip.h> 
#include <netinet/udp.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define ADDRESS_SERVER "192.168.0.16"
#define ADDRESS_CLIENT "192.168.0.14"
#define PORT_SERVER 9171
#define PORT_CLIENT 7919
#define MAC_LEN 6
#define SIZE_DATA 128

unsigned short csum(unsigned short *ptr, int nbytes)
{
    register long sum = 0;
    unsigned short oddbyte;
    register short answer;

    while(nbytes > 1)
    {
        sum += *ptr++;
	    nbytes -= 2;
	}

	if(nbytes == 1)
    {
		oddbyte = 0;

		*((u_char*)&oddbyte)=*(u_char*)ptr;

		sum+=oddbyte;
    }

    sum = (sum >> 16) + (sum & 0xffff);

	sum = sum + (sum >> 16);

	answer = (short) ~ sum;

	return(answer);
}

int main()
{
    unsigned char mac_server[MAC_LEN] = {0x2c, 0xf0, 0x5d, 0x05, 0x88, 0x26};
    unsigned char mac_client[MAC_LEN] = {0xa8, 0x1e, 0x84, 0x8c, 0xf0, 0xf2};

    char *message_send = calloc(SIZE_DATA, sizeof(char));
    strcpy(message_send, "Hello, I'm client!");

    char *packet = calloc(sizeof(struct ether_header) + sizeof(struct iphdr) + 
            sizeof(struct udphdr) + strlen(message_send), sizeof(char));
    memmove(packet + sizeof(struct ether_header) + sizeof(struct iphdr) + 
            sizeof(struct udphdr), message_send, strlen(message_send));

    struct sockaddr_ll server;
    memset(&server, 0, sizeof(struct sockaddr_ll));
    server.sll_family = AF_PACKET;
    server.sll_protocol = htons(ETH_P_ALL);
    server.sll_ifindex = if_nametoindex("enp37s0");
    server.sll_hatype = 0;
    server.sll_pkttype = 0;
    server.sll_halen = MAC_LEN;
    memmove((void *)(server.sll_addr), (void *)(mac_server), MAC_LEN);

    struct udphdr *udp_header = (struct udphdr *)(packet + 
            sizeof(struct iphdr) + sizeof(struct ether_header));
    memset(udp_header, 0, sizeof(struct udphdr));
    udp_header -> source = htons(PORT_CLIENT);
    udp_header -> dest = htons(PORT_SERVER);
    udp_header -> len = htons(sizeof(struct udphdr) + strlen(message_send));
    udp_header -> check = 0;

    struct iphdr *ip_header = (struct iphdr *)(packet + 
            sizeof(struct ether_header));
    memset(ip_header, 0, sizeof(struct iphdr));
    ip_header -> ihl = 5;
    ip_header -> version = 4;
    ip_header -> tos = 0;
    ip_header -> tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) +
            strlen(message_send));
    ip_header -> id = htons(111);
    ip_header -> frag_off = htons(0);
    ip_header -> ttl = 173;
    ip_header -> check = 0;
    ip_header -> check = csum((unsigned short *) ip_header, ip_header -> ihl *
        4);
    ip_header -> protocol = IPPROTO_UDP;
    ip_header -> saddr = inet_addr(ADDRESS_CLIENT);
    ip_header -> daddr = inet_addr(ADDRESS_SERVER);

    struct ether_header *ether_header = (struct ether_header *)(packet);

    for(int i = 0; i < MAC_LEN; i++)
    {
        ether_header -> ether_shost[i] = mac_server[i];
        ether_header -> ether_dhost[i] = mac_client[i];
    }

    ether_header -> ether_type = htons(ETH_P_IP);

    int socket_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    if(socket_fd == - 1)
    {
        perror("Socket");
        free(message_send);
        free(packet);
        exit(EXIT_FAILURE);
    }

    if(sendto(socket_fd, packet, sizeof(struct udphdr) + strlen(message_send) +
                sizeof(struct iphdr) + sizeof(struct ether_header), 0,
                (const struct sockaddr *) &server,
                sizeof(struct sockaddr_ll)) == -1)
    {
        perror("Sendto");
        free(message_send);
        free(packet);
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    printf("Client send message to server!\n\n");
    printf("Client waiting message from server...\n");

    while(1)
    {
        int size_sockaddr_in = sizeof(struct sockaddr_in);

        if(recvfrom(socket_fd, packet, SIZE_DATA, 0,
                    (struct sockaddr *) &server, &size_sockaddr_in) == -1)
        {
            perror("Recvfrom");
            free(message_send);
            free(packet);
            close(socket_fd);
            exit(EXIT_FAILURE);
        }

        struct iphdr *ip_header = (struct iphdr *)packet;

        udp_header = (struct udphdr *)(packet + sizeof(struct iphdr));

        if(ntohs(udp_header -> dest) == PORT_CLIENT)
        {
            struct in_addr address;
            memset(&address, 0, sizeof(struct in_addr));
            address.s_addr = ip_header -> saddr;

            printf("Server IP: %s\n", inet_ntoa(address));
            printf("Server port: %d\n", ntohs(udp_header -> source));
            printf("Message: %s\n\n", packet + sizeof(struct iphdr) +
                    sizeof(struct udphdr));

            free(message_send);
            free(packet);

            close(socket_fd);

            break;
        }
    }

    exit(EXIT_SUCCESS);
}
