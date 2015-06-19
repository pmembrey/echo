/*
 *  Author: Peter Membrey
 *  Date: 20/06/2015
 *
 *  Simple implementation of RFC862 UDP echo server
 *
 *  Inspired by:
 *
 *  http://www.cs.ucsb.edu/~almeroth/classes/W01.176B/hw2/examples/
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// UDP packets can't be bigger than this
// but we don't want "magic" numbers in our code
#define UDP_MAX_SIZE 65535


int main(int argc, char **argv) {
    int sockfd, n;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    char buffer[UDP_MAX_SIZE];

    // Check we have the right number of arguments
    if (argc != 2) {
        printf("usage: %s <Port>\n", argv[0]);
        exit(1);
    }

    // Crete a basic UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    // Initialize the memory
    memset(&servaddr, sizeof(servaddr), 0);
    // Use the Internet Address Family
    servaddr.sin_family = AF_INET;
    // We want to listen on all IP's
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // We want to listen on the port provided
    servaddr.sin_port = htons(atoi(argv[1]));
    // Bind the socket - actually start listening
    bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    // Infinite loop!
    for (; ;) {
        len = sizeof(cliaddr);
        n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cliaddr, &len);
        sendto(sockfd, buffer, n, 0, (struct sockaddr *) &cliaddr, sizeof(cliaddr));
        printf("-------------------------------------------------------\n");
        buffer[n] = 0;
        printf("Received the following:\n");
        printf("%s", buffer);
        printf("\n-------------------------------------------------------\n");
    }
}

