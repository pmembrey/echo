/*
 *  Author: Peter Membrey
 *  Date: 20/06/2015
 *  
 *  Simple implementation of RFC862 UDP echo client
 *
 *  Inspired by:
 *
 *  http://www.cs.ucsb.edu/~almeroth/classes/W01.176B/hw2/examples/
 */


#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int sockfd, n;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[1000];

    // Check we have the right number of arguments
    if (argc != 4) {
        printf("usage: %s <IP Address> <Port> <Message>\n", argv[0]);
        exit(1);
    }

    // Create a basic UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Initialize the memory
    memset(&servaddr, sizeof(servaddr), 0);
    // We want to use the Internet Address Family
    servaddr.sin_family = AF_INET;
    // Here we set the IP address
    // Note: we call inet_addr to convert the string representation into an integer representation
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    // Do something similar with the port - but we also need it in Big Endian format
    servaddr.sin_port = htons(atoi(argv[2]));

    // Let's send our data!
    sendto(sockfd, argv[3], strlen(argv[3]), 0, (struct sockaddr *) &servaddr, sizeof(servaddr));

    // Now let's see if we got a reply...
    n = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
    // Ensure we have a valid c string by NULL terminating the response
    buffer[n] = '\0';
    // Write out the reply
    printf("Response received: %s\n", buffer);

}

