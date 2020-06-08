#define _POSIX_C_SOURCE 200112L

#include <msgpack.hpp>
#include <iostream>
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "common_sockets.h"

#define ONE_BYTE 1
#define TWO_BYTES 2
#define FOUR_BYTES 4

Socket::Socket() {}


void Socket::connect_to(const char *host, const char *port) {
    struct addrinfo hints, *results, *rp;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;

	int status = getaddrinfo(host, port,&hints,&results);
	if (status != 0){
		perror("getaddrinfo");
		exit(1);
	}

	for (rp = results; rp != NULL; rp = rp->ai_next) {
		this->fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (this->fd == -1) {
			// printf("Error: %s\n", strerror(errno));
            std::cout << "ERROR" << std::endl;
			continue;
		} 

		if (connect(this->fd, rp->ai_addr, rp->ai_addrlen) != -1)
			break;

		close(this->fd); 
	}
	freeaddrinfo(results);
}


void Socket::turnoff_channel(int mode) {
    shutdown(this->fd, mode);
}


void Socket::bind_and_listen(const char *port) {
    struct addrinfo hints, *results;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	int status = getaddrinfo(NULL, port, &hints, &results);
	if (status != 0) {
		perror("getaddrinfo");
		exit(1);
	}

	if ((this->fd = socket(results->ai_family,results->ai_socktype,0)) < 0){
		perror("creando socket");
		printf("%sn",strerror(errno));
		freeaddrinfo(results);
		exit(1);
	}

	if (bind(this->fd, results->ai_addr, results->ai_addrlen) < 0) {
		perror("bind");
		printf("%sn",strerror(errno));
		freeaddrinfo(results);
		exit(1);
	}

	freeaddrinfo(results);

	if ( listen(this->fd, 10) == -1 ) {
		perror("listen");
		printf("%s\n", strerror(errno));
		exit(1);
	}
}


void Socket::send_message(char *buf, int size) const {
    int sent = 0;
	int s = 0;

	while (sent < size) {
		s = send(this->fd, &buf[sent], size-sent, MSG_NOSIGNAL);
		if (s <= 0) {
			return;
		} else {
			sent += s;
		}
	}

	return;
}


void Socket::receive(char *buf, int size) const {
    int received = 0;
	int s = 0;

	while (received < size) {
		s = recv(this->fd, &buf[received], size-received, MSG_NOSIGNAL);
		if (s <= 0) { 
			return;
		} else {
			received += s;
		}
	}

	return;
}

Socket::Socket(int fd) {
	this->fd = fd;
}


Socket Socket::accept_client() {
    int fd = accept(this->fd, NULL, NULL);
    return std::move(Socket(fd));
}


void Socket::close_socket()  {
	shutdown(this->fd, SHUT_RDWR);
    close(this->fd);
}


void Socket::operator()(uint8_t &com) const {
	this->send_message((char*) &com, ONE_BYTE);	
}


void Socket::operator()(uint16_t &number) const {
	number = htons(number);
	this->send_message((char*) &number, TWO_BYTES);	
}


void Socket::operator()(uint32_t &len) const {
	this->send_message((char*) &len, FOUR_BYTES);	
}

void Socket::operator()(const std::string &message) const {
	uint32_t len = htonl(message.length());
	this->send_message((char*) &len, FOUR_BYTES);
	this->send_message((char*) message.c_str(), (int) message.length());	
}

void Socket::operator()(msgpack::sbuffer &sbuf) const {
	uint16_t size = sbuf.size();
	this->operator()(size);
	this->send_message((char*) sbuf.data(), (int) sbuf.size());
}



void Socket::operator>>(uint8_t &com) const {
	this->receive((char*) &com, ONE_BYTE);
}


void Socket::operator>>(uint16_t &buf) const {
	this->receive((char*) &buf, TWO_BYTES);
	buf = ntohs(buf);
}


void Socket::operator>>(uint32_t &len) const {
	this->receive((char*) &len, FOUR_BYTES);
}

void Socket::operator>>(std::string &message) const {
	uint32_t len;
	this->receive((char*) &len, FOUR_BYTES);
	len = ntohl(len);
	char* tmp = (char*) calloc((len+1), sizeof(char));
	this->receive(tmp, len);
	message = tmp;
	free(tmp);
}


void Socket::operator>>(msgpack::unpacker &pack) const {
	uint16_t size;
	this->operator>>(size);
	pack.reserve_buffer(size);
	this->receive(pack.buffer(), size);
	pack.buffer_consumed(size);
}
