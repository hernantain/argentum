#ifndef QUEUE_EXCEPTION
#define QUEUE_EXCEPTION

#include <iostream>
#include <exception>


/**
 * Excepcion lanzada por la Blocking Queue
 * cuando la misma recibio el mensaje de que deje de operar.
 */
struct QueueNotOperatingException : public std::exception {
    const char* what() const throw() {
    	return "Queue has stopped operation.";
    }
};

#endif
