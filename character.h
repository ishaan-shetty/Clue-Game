#ifndef CHARACTER_H
#define CHARACTER_H

#include "rooms.h"
#include "items.h"

//Structure of the character
struct Character{
    char* name[15];
    struct Room* currentRoom;
    struct Character* nextCharacter;
    struct Character* prevCharacter;
};

//Constructor
struct Character* character(char* name,struct Room* currentRoom);

//Get Functions
char* getCharacterName(struct Character* character);

struct Room* getCharacterCurrentRoom(struct Character *character);

//Character Room Modification Function
void changeCharacterRoom(struct Character* character, struct Room* newRoom);

//Linked List
struct Character* nextCharacter(struct Character* c);

struct Character* prevCharacter(struct Character* c);

void setNextCharacter(struct Character *c, struct Character *newChar);

void setPrevCharacter(struct Character* c, struct Character* newChar);

#endif