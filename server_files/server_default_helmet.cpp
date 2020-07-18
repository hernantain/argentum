#include "server_default_helmet.h"

#define NO_DEFENSE 0
#define DEFAULT_ID 0

DefaultHelmet::DefaultHelmet() : 
    Helmet(NO_DEFENSE, NO_DEFENSE) {
        this->id = DEFAULT_ID;
        this->name = "Casco default";
    }
