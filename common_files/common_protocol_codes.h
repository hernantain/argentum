#ifndef _COMMON_PROTOCOL_CODES
#define _COMMON_PROTOCOL_CODES

// Received from the client
#define PROTOCOL_ATTACK 2
#define PROTOCOL_EQUIP_HELMET 3
#define PROTOCOL_EQUIP_ARMOR 4
#define PROTOCOL_EQUIP_WEAPON 5
#define PROTOCOL_EQUIP_SHIELD 6
#define PROTOCOL_DROP_ITEM 7
#define PROTOCOL_TAKE_ITEM 8
#define PROTOCOL_MOVE_STOP 9
#define PROTOCOL_MOVE_TOP 10
#define PROTOCOL_MOVE_RIGHT 11
#define PROTOCOL_MOVE_LEFT 12
#define PROTOCOL_MOVE_DOWN 13
#define PROTOCOL_DEPOSIT 14
#define PROTOCOL_WITHDRAW 15
#define PROTOCOL_RESURRECT 16
#define PROTOCOL_MEDITATION 17


// Sending to the client
#define PROTOCOL_MOVE_CONFIRM 20
#define PROTOCOL_DEPOSIT_CONFIRM 21
#define PROTOCOL_WITHDRAW_CONFIRM 22
#define PROTOCOL_RESURRECT_CONFIRM 23
#define PROTOCOL_ATTACK_CONFIRM 25
#define PROTOCOL_KILL_CONFIRM 26
#define PROTOCOL_HELMET_CONFIRM 30
#define PROTOCOL_ARMOR_CONFIRM 31
#define PROTOCOL_WEAPON_CONFIRM 32
#define PROTOCOL_SHIELD_CONFIRM 33
#define PROTOCOL_MEDITATE_CONFIRM 34
#define PROTOCOL_TAKE_ITEM_CONFIRM 35
#define PROTOCOL_DROP_ITEM_CONFIRM 36

// Creation and Destruction
#define PROTOCOL_CREATE_CHARACTER 65
#define PROTOCOL_CREATE_CHARACTER_CONFIRM 66
#define PROTOCOL_LOG_OFF 67
#define PROTOCOL_LOG_OFF_CONFIRM 68

// Received & Sent from the GameLoop
#define PROTOCOL_CREATE_NPC 70
#define PROTOCOL_CREATE_NPC_CONFIRM 71
#define PROTOCOL_UPDATE_NPCS 72
#define PROTOCOL_UPDATE_NPCS_CONFIRM 73
#define PROTOCOL_UPDATE_CHARACTERS 74
#define PROTOCOL_UPDATE_CHARACTERS_CONFIRM 75

#define NOTHING 55

#endif //_COMMON_PROTOCOL_CODES
