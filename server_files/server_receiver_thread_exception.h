#ifndef _RECEIVER_THREAD_EXCEPTION
#define _RECEIVER_THREAD_EXCEPTION

#include <iostream>
#include <exception>


/**
 * Excepcion lanzada por la Blocking Queue
 * cuando la misma recibio el mensaje de que deje de operar.
 */
struct ReceiverThreadException : public std::exception {
    const char* what() const throw() {
    	return "ReceiverThread has stopped operation.";
    }
};

#endif
