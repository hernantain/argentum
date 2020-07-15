#include "server_gold.h"

Gold::Gold(int amount) {
    this->id = 20;
    this->amount = amount;
    this->name = "Oro";
}

int Gold::get_gold() const {
    return amount;
}
