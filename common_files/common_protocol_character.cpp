
#include <iostream>
#include <utility>
#include "common_protocol_character.h"



ProtocolCharacter::ProtocolCharacter() {}



// ProtocolCharacter::ProtocolCharacter(ProtocolCharacter&& other) {
//     // std::cout << "Constructor por movimiento" << std::endl;
//     this->id = std::move(other.id);
//     this->id_race = std::move(other.id_race);
//     this->id_class = std::move(other.id_class);
//     this->bodyPosX = std::move(other.bodyPosX);
//     this->bodyPosY = std::move(other.bodyPosY);
//     this->helmetId = std::move(other.helmetId);
//     this->armorId = std::move(other.armorId);
// }


// ProtocolCharacter& ProtocolCharacter::operator=(ProtocolCharacter&& other) {
//     // std::cout << "Asignando por movimiento" << std::endl;
//     this->id = std::move(other.id);
//     this->id_race = std::move(other.id_race);
//     this->id_class = std::move(other.id_class);
//     this->bodyPosX = std::move(other.bodyPosX);
//     this->bodyPosY = std::move(other.bodyPosY);
//     this->helmetId = std::move(other.helmetId);
//     this->armorId = std::move(other.armorId);
//     return *this;
// }
    
