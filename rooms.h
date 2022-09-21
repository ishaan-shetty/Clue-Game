#ifndef ROOMS_H
#define ROOMS_H

#include "character.h"
#include "items.h"

//Structure of the room
struct Room{
    char* name[20];
    struct Room* North;
    struct Room* South;
    struct Room* East;
    struct Room* West;
    struct Item* itemList;
    struct Character* character;
};

//Constructor
struct Room* room(char* name,struct Room* North, struct Room* South, struct Room* East, struct Room* West, struct Item* itemList, struct Character* character);

//Get Functions
char* getRoomName(struct Room *room);

struct Room* getRoom(struct Room *room, char* direction[5]);

struct Item* getRoomItemList(struct Room *room);

struct Character* getCharacterList(struct Room *room);

//Add, Set Functions
void addCharacterToRoom(struct Room* room, struct Character* newCharacter);

void addItemToRoom(struct Room* room, struct Item* newItem);

void removeItemFromRoom(struct Room* room, struct Item* itemToRemove);

void removeCharacterFromRoom(struct Room* room, struct Character* removeCharacter);

void addCharacterToRoom(struct Room* room, struct Character* newCharacter);

void setNorthRoom(struct Room *room, struct Room *northRoom);

void setSouthRoom(struct Room *room, struct Room *southRoom);

void setEastRoom(struct Room *room, struct Room *eastRoom);

void setWestRoom(struct Room *room, struct Room *westRoom);


#endif