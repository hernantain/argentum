#ifndef _QUEUE_EXCEPTION
#define _QUEUE_EXCEPTION

#include <iostream>
#include <exception>


struct QueueNotOperatingException : public std::exception {
    const char* what() const throw() {
    	return "Queue has stopped operation.";
    }
};

#endif
