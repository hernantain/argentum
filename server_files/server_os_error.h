#include <exception>
#include <string>

/* Excepcion lanzada cuando los parametros
 * de la llamada al server/client son erroneos.
 */
class OSError : public std::exception {
protected:
    std::string error_message;  

public:
    explicit OSError(const std::string& msg): error_message(msg) {}

    const char* what() const throw() {
        return error_message.c_str();
    }

    ~OSError() throw() {}
};
