#include <stdio.h>
#include "rooms.h"
#include "character.h"
#include "items.h"

//Constructor
struct Room* room(char* name,struct Room *North, struct Room *South, struct Room *East, struct Room *West, struct Item *itemList, struct Character* character){
    struct Room* r = (struct Room*) malloc(sizeof(struct Room));
    strcpy(r->name, name);
    r->North = North;
    r->South = South;
    r->East = East;
    r->West = West;
    r->itemList = itemList;
    r->character = character;
    
    return r;
}

//To get the name of the room
char* getRoomName(struct Room *room){
    return room->name;
}

//To get the room in a inputted cardinal direction
struct Room* getRoom(struct Room* room, char* direction[5]){
    if(strcmp(direction, "NORTH") == 0){
        return room->North;
    }
    else if(strcmp(direction, "SOUTH") == 0){
        return room->South;
    }
    else if(strcmp(direction, "EAST") == 0){
        return room->East;
    }
    else if(strcmp(direction, "WEST") == 0){
        return room->West;
    }
    else{
        printf("Invalid Room");
        exit(-1);
    }
}


//To get the linked list of items in the room
struct Item* getRoomItemList(struct Room *room){
    return room->itemList;
}

//To get a list of characters in the room
struct Character* getCharacterList(struct Room *room){
    return room->character;
}

//To add a character to the room
void addCharacterToRoom(struct Room* room, struct Character* newCharacter){
    
    struct Character* charIterator = room->character;
    if(charIterator == NULL){
        room->character = newCharacter;
    }
    else{
        while(getNextCharacter(charIterator) != NULL){
            charIterator = getNextCharacter(charIterator);
        }
    
        setNextCharacter(charIterator, newCharacter);
    }
    
    
    changeCharacterRoom(newCharacter,room);
}

//To remove a character from the room
void removeCharacterFromRoom(struct Room* room, struct Character* removeCharacter){
    struct Character* charIterator = getPrevCharacter(removeCharacter);
    if(charIterator == NULL){
        room->character = removeCharacter->nextCharacter;
    }
    else{
        setNextCharacter(getPrevCharacter(removeCharacter), removeCharacter->nextCharacter);
    }
}

//To add an item to the room
void addItemToRoom(struct Room* room, struct Item* newItem){
    room->itemList = newItem;
    setItemCurrentRoom(newItem, room);
}

//To remove an item from the room
void removeItemFromRoom(struct Room* room, struct Item* itemToRemove){
    struct Item* pItem = getPrevItem(itemToRemove);
    if(pItem == NULL){
        room->itemList = getNextItem(itemToRemove);
    }
    else{
        setNextItem(pItem, getNextItem(itemToRemove));
    }
}

//To set the room North of current room
void setNorthRoom(struct Room *room, struct Room *northRoom){
    room->North = northRoom;
    northRoom->South = room;
}

//To set the room South of current room
void setSouthRoom(struct Room *room, struct Room *southRoom){
    room->South = southRoom;
    southRoom->North = room;
}

//To set the room East of current room
void setEastRoom(struct Room *room, struct Room *eastRoom){
    room->East = eastRoom;
    eastRoom->West = room;
}

//To set the room West of current room
void setWestRoom(struct Room *room, struct Room *westRoom){
    room->West = westRoom;
    westRoom->East = room;
}