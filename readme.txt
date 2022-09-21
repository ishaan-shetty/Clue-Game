CLUE GAME
CS230

Structure: This game consists of 7 files:
1. adventure.c: Contains the main function of the game
2. rooms.c: Has the structure and function related to the rooms designed
in the game
3. rooms.h: Header file for rooms.c
4. character.c: Has the structure and functions related to the
characters in the game.
5. character.h: Header file for character.c
6. items.c: Has the structure and functions for the items in the fame
7. items.h: Header file for items.h

Setup of game:
1. To compile the game use code gcc -w adventure.c items.c rooms.c
character.c
2. To run the game use code ./a.out or the file name assigned to the
compiled file
3. Typing "HELP" Command can provide a list of commands to navigate the game.
4. Game is Case- sensitive. All commands to be given in Capital Letters only. Name of item and character can be given according to how they appear in the game 

Structs in game: The game has 3 essential structs that create the board
for the game:
1. struct Character{
    char* name[15]; //Stores the name of the character
    struct Room* currentRoom;  //Stores the current room of character
    struct Character* nextCharacter; //Used for linked list of characters in room
    struct Character* prevCharacter;
   };
2. struct Item{
    char* name[20]; //Stores the name of the item
    struct Room* currentRoom; //Stores the current room of the item
    struct Item* nextItem; //Used for linked list of items in the room
    struct Item* prevItem;
   };
3. struct Room{
    char* name[20]; //Stores the name of the room
    struct Room* North; //Pointer to the room North of this room
    struct Room* South; //Pointer to the room South of this room
    struct Room* East; //Pointer to the room East of this room
    struct Room* West; //Pointer to the room West of this room
    struct Item* itemList; //Stores the first element in the linked list of items in the room
    struct Character* character; //Stores the first character in the linked list of characters in the room
  };



