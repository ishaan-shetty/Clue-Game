#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "items.h"
#include "rooms.h"
#include "character.h"


//Universal Variables
struct Room* boardLayout[9]; //Array to store all rooms in the Game
struct Item* itemList[6]; //Array to store all items in the Game
struct Character* characterList[6]; //Array to store all Characters in the Game
struct Character* avatar; //Maintains the user/player'Character
struct Room* avatarRoom; //Stores the current room the user is in
struct Item* avatarItemInventory; //Maintains the inventory of the player/user's Character
struct Character* clueCharacter; //Stores the Answer (Character) to win the Game
struct Item* clueItem; //Stores the Answer (Item) to win the Game
struct Room* clueRoom; //Stores the Answer (Room) to win the Game
char* userResponse[40]; //Stores the commands given by the user
int clueCount; //Stores the number of clue Attempts the user has made
    
//Initializes the board for the game
void boardSetup(){
    //Creating  Rooms for the Game
    struct Room* A = room("Kitchen", NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room* B = room("Ballroom", NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room* C = room("Conservatory", NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room* D = room("Dining Room", NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room* E = room("Billiard Room", NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room* F = room("Library", NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room* G = room("Lounge", NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room* H = room("Hall", NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room* I = room("Study", NULL, NULL, NULL, NULL, NULL, NULL);
    
    //Storing the room in a boardLayout Array
    boardLayout[0] = A; boardLayout[1] = B; boardLayout[2] = C; boardLayout[3] = D;
    boardLayout[4] = E; boardLayout[5] = F; boardLayout[6] = G; boardLayout[7] = H;
    boardLayout[8] = I;

    //Creating Items for the game
    struct Item* candleStick = item("CANDLE", NULL, NULL);
    struct Item* dagger = item("DAGGER", NULL, NULL);
    struct Item* leadPipe = item("PIPE", NULL, NULL);
    struct Item* revolver = item("REVOLVER", NULL, NULL);
    struct Item* rope = item("ROPE", NULL, NULL);
    struct Item* wrench = item("WRENCH", NULL, NULL);
    
    //Storing the items in an itemList Array
    itemList[0] = candleStick; itemList[1] = dagger; itemList[2] = leadPipe;
    itemList[3] = revolver; itemList[4] = rope; itemList[5] = wrench;

     //Creating Character for the game
    struct Character* c1 = character("Miss Scarlet", NULL);
    struct Character* c2 = character("Colonel Mustard", NULL);    
    struct Character* c3 = character("Mrs. White", NULL);
    struct Character* c4 = character("The Reverend Green", NULL);
    struct Character* c5 = character("Mrs. Peacock", NULL);
    struct Character* c6 = character("Professor Plum", NULL);
    
    //Storing the Characters in an characterList Array
    characterList[0] = c1; characterList[1] = c2; characterList[2] = c3;
    characterList[3] = c4; characterList[4] = c5; characterList[5] = c6;

    //Fisher Yates Shuffle (Source: https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/)
    //Used to shuffle the order of the Rooms
    srand (time(NULL));
    for (int i = 8; i > 0; i--){
        int j = rand() % (i+1);

        struct Room* temp = boardLayout[i];
        boardLayout[i] = boardLayout[j];
        boardLayout[j] = temp;
    }

    //Adds the characters and items to the shuffled rooms
    addCharacterToRoom(boardLayout[0],c1);
    addItemToRoom(boardLayout[0], candleStick);
    
    addCharacterToRoom(boardLayout[1],c2);
    addItemToRoom(boardLayout[1], dagger);
    
    addCharacterToRoom(boardLayout[2],c3);
    addItemToRoom(boardLayout[2], leadPipe);
 
    addCharacterToRoom(boardLayout[3],c4);
    addItemToRoom(boardLayout[3], revolver);
    
    addCharacterToRoom(boardLayout[4],c5);
    addItemToRoom(boardLayout[4], rope);
 
    addCharacterToRoom(boardLayout[5],c6);
    addItemToRoom(boardLayout[5], wrench);

    //Setting North, South, East, West Rooms for each Room
    setEastRoom(boardLayout[0], boardLayout[1]);
    setSouthRoom(boardLayout[0], boardLayout[3]);
    setEastRoom(boardLayout[1], boardLayout[2]);
    setSouthRoom(boardLayout[1], boardLayout[4]);
    setSouthRoom(boardLayout[2], boardLayout[5]);
    setEastRoom(boardLayout[3], boardLayout[4]);
    setSouthRoom(boardLayout[3], boardLayout[6]);
    setEastRoom(boardLayout[4], boardLayout[5]);
    setSouthRoom(boardLayout[4], boardLayout[7]);
    setSouthRoom(boardLayout[5], boardLayout[8]);
    setEastRoom(boardLayout[6], boardLayout[7]);
    setEastRoom(boardLayout[7], boardLayout[8]);
    
    //Initializes Avatar Inventory to NULL
    avatarItemInventory = NULL;
    
    //Initializes number of clue attempts to 0
    clueCount = 0;
}


int main(){
    
    boardSetup();
    
    //Sets the avatar and its current Room
    avatar = characterList[rand() % 5];
    avatarRoom = getCharacterCurrentRoom(avatar);

    //Setting the answer for the game
    //While loop ensures that clueCharacter and user's avatar are not the same
    clueCharacter = characterList[rand() % 5];
    while(strcmp(getCharacterName(avatar), getCharacterName(clueCharacter)) == 0){
        clueCharacter = characterList[rand() % 5];
    }
    
    clueRoom = getCharacterCurrentRoom(clueCharacter);
    clueItem = itemList[rand() % 5];
    printf("\n\n");
    printf("##############################################\n");
    printf("##############################################\n");
    printf("Welcome to the Clue Game\n");
    printf("Please provide all commands in Upper Case\n");
    printf("Type 'HELP' to check commands\n");
    
    command();
    
    return 0;
}

//Function to accept user's input(command) and call the correct function according to the command
void command(){
    scanf("%20s", userResponse);
    
    //If-else statements to check the command against options available
    if(strcmp(userResponse, "HELP") == 0){
        helpCommand();
    }
    
    else if(strcmp(userResponse, "LIST") == 0){
        listCommand();
    }
    
    else if(strcmp(userResponse, "LOOK") == 0){
        lookCommand();
    }
    
    else if(strcmp(userResponse, "GO") == 0){
        goCommand();
    }
    
    else if(strcmp(userResponse, "TAKE") == 0){
        takeCommand();
    }
    
    else if(strcmp(userResponse, "DROP") == 0){
        dropCommand();
    }
    
    else if(strcmp(userResponse, "INVENTORY") == 0){
        inventoryCommand();
    }
    
    else if(strcmp(userResponse, "CLUE") == 0){
       clueCommand(); 
    }
    
    //QUIT Statement to stop the game
    else if(strcmp(userResponse, "QUIT") == 0){
        printf("Game Quit\n");
        exit(0);
    }
    
    //Else Statement to handle commands different from the program defined commands
    else{
        printf("Command not recognized\n");
        printf("Type 'HELP' to check commands\n");
        command();
    }
    
}

//Called on getting "HELP" input. Prints a list of possible commands to maneuver the game
void helpCommand(){
    printf("1. LIST: Displays a list of items, characters and rooms in the game\n");
    printf("2. LOOK: Command is used to know your sorroundings. This includes: Rooms around, Characters in room and Items in room\n");
    printf("3. GO: Moves the character to the room in the direction specified after. Directions: NORTH, SOUTH, EAST, WEST\n");
    printf("4. TAKE: Your avatar picks up the item (specified after) and places it in their inventory\n");
    printf("5. DROP: Your avatar drops item (specified after) from their inventory\n");
    printf("6. INVENTORY: Displays the user's inventory\n");
    printf("7. CLUE: Command is used to submit the answer for the game\n");
    printf("8. QUIT: Quit the game\n");
    command();
}

//Called on getting "LOOK" input. Prints details of the room the avatar is currently in
void lookCommand(){
    printf("Current Room: %s\n", getRoomName(avatarRoom));
    printf("Rooms Around: North: %s, South: %s, East: %s, West: %s\n", getRoom(avatarRoom, "NORTH"), getRoom(avatarRoom, "SOUTH"), getRoom(avatarRoom, "EAST"), getRoom(avatarRoom, "WEST"));
    printf("Characters in room:");
    struct Character* charIterator = getCharacterList(avatarRoom); //Iterator variable to iterate through linked list
    
    //Loop for iterating
    while(charIterator != NULL){
        printf("%s, ", getCharacterName(charIterator));
        charIterator = charIterator->nextCharacter;
    }
    printf("\n");
    
    printf("Items in the room: ");
    
    struct Item* roomItem = getRoomItemList(avatarRoom); //Iterator variable to iterate through items linked list
    
    //Loop for iterating
    while(roomItem != NULL){
        printf("%s, ", getItemName(roomItem));
        roomItem = getNextItem(roomItem);
    }
    printf("\n");
    printf("NULL refers to no room/character/item exists\n");
    
    command();
}

//Called on getting "GO" input. Asks user for the direction to go in and changes avatarRoom accordingly
void goCommand(){
    printf("Please enter Direction\n");
    char* direction[5];
    scanf("%s",direction);
        
    if(strcmp(direction, "NORTH") == 0 || strcmp(direction, "SOUTH") == 0 || strcmp(direction, "EAST") == 0|| strcmp(direction, "WEST") == 0){
        //If-else ensures that a room exists in the direction entered
        if(getRoom(avatarRoom, direction) != NULL){
            avatarRoom = getRoom(avatarRoom, direction); //Function gets the room in the direction entered
            printf("Current Room: %s\n", getRoomName(avatarRoom));
        }
        else{
            printf("No room in %s direction\n", direction);
        }
    }
    else{
        printf("Invalid Direction\n");
        goCommand();
    }
    command();
}

//Called on getting "TAKE" input. Accepts item name and adds the item to the avatar's inventory
void takeCommand(){
    printf("Please enter Item Name\n");
    char* itemName[15];
    scanf("%s",itemName);
    int itemFound = 0; //Check variable to see that item entered by user is actually present in the room/is a valid item
    
    struct Item* itemsInRoom = getRoomItemList(avatarRoom); //Iterator variable to iterate through items in the avatar's room
    
    //Loop to iterate through the items. Checks for null as the nextItem after the last item would be NULL
    while(itemsInRoom != NULL){
        if(strcmp(getItemName(itemsInRoom), itemName) == 0){ //Compares user entered ITEM name and name of items present in the room
            if(avatarItemInventory == NULL){ //Checks if avatar's inventory is empty and makes the inventory as the new item
                avatarItemInventory = itemsInRoom;
                removeItemFromRoom(avatarRoom, itemsInRoom);
            }
            else{ //Else loops through the items in the inventory till the last item is reached and adds the new item after that
                struct Item* itemsWithCharacter = avatarItemInventory;
                while(getNextItem(itemsWithCharacter) != NULL){
                    itemsWithCharacter = getNextItem(itemsWithCharacter);
                }
                removeItemFromRoom(avatarRoom, itemsInRoom);
                setNextItem(itemsWithCharacter, itemsInRoom);
            }
            itemFound = 1;
        }
        itemsInRoom = getNextItem(itemsInRoom);
    }
    if(itemFound == 0){ //Prints appropriate message if item is not present
        printf("Item not found in room\n");
        takeCommand();
    }
    command();
}

//Called on getting "DROP" input. Drops the item inputted by user for the avatar's inventory
void dropCommand(){
    struct Item* itemInInvetory = avatarItemInventory; //Iterating variable for avatar's inventory
    printf("Please enter Item Name\n");
    char* itemName[15];
    scanf("%s",itemName);
    int itemFound = 0; ////Check variable to see that item entered by user is actually present in the inventory/is a valid item
    
    if(itemInInvetory == NULL){ //Check if avatar's inventory is empty
        printf("No item in inventory");
        command();
    }
    
    else if(strcmp(getItemName(itemInInvetory), itemName) == 0){ //Checks if first item in inventory is the item to be dropped
        avatarItemInventory = getNextItem(itemInInvetory);
        addItemToRoom(avatarRoom, itemInInvetory);
        itemFound = 1;
    }
    else{ //Iterates and checks if the item is present in the inventory and drops it if it is present
        while(itemInInvetory != NULL){
            if(strcmp(getItemName(itemInInvetory), itemName) == 0){
                setNextItem(getPrevItem(itemInInvetory), getNextItem(itemInInvetory));
                addItemToRoom(avatarRoom, itemInInvetory);
                itemFound = 1;
            }
            itemInInvetory = getNextItem(itemInInvetory);
        }
    }
        
    if(itemFound == 0){ //Check condition if item is not in inventory
        printf("Item not Found in Inventory\n");
        dropCommand();
    }
    printf("Item Dropped\n");
    command();
}

//Called on getting "INVENTORY" input. Prints the inventory of the avatar
void inventoryCommand(){
    struct Item* characterItemList = avatarItemInventory; //Iterating variable through the avatar's inventory
    if(characterItemList == NULL){ //Checks if the inventory is empty
        printf("Inventory is empty");
    }
    else{
        printf("Inventory: ");
        
        //Iterates through the inventory and prints every item
        while(characterItemList != NULL){ 
            printf(" %s", getItemName(characterItemList));
            characterItemList = getNextItem(characterItemList);
        }
    }
    printf("\n");
    command();
}

//Called on getting "LIST" input. Prints a List of all rooms, characters and items in the game
void listCommand(){
    printf("Rooms:\n");
    
    //Three Loops to loop through the boardLayout, characterList and itemList arrays to get the name of each room, character and item respectively
    for(int i = 0; i < 9; i++){
        printf("%i. %s\n", (i+1), getRoomName(boardLayout[i]));
    }
    printf("\nCharacters:\n");
    for(int i = 0; i < 6; i++){
        printf("%i. %s\n", (i+1), getCharacterName(characterList[i]));
    }
    printf("\nItems:\n");
    for(int i = 0; i < 6; i++){
        printf("%i. %s\n", (i+1), getItemName(itemList[i]));
    }
    command();
}

//Called on getting "LIST" input. Accepts the answer from the user and checks for the correctness as well as decides the winning and loosing state of the game
void clueCommand(){
    clueCount = clueCount + 1; //Keeps a count of number of calls to the function. After 10 calls player looses the game
        
    char* userRespondedChar = malloc(20 * sizeof(char)); //Malloc for user entered aswers of character and items
    char* userRespondedItem = malloc(20 * sizeof(char));
    char* temp = malloc(20 * sizeof(char));
    printf("Enter Character Name:");
    fgets(temp,20,stdin); //Used to resolve an error where system wasn't accepting response properly
    fgets(userRespondedChar, 20, stdin);
    printf("Enter Item Name:");
    fgets(userRespondedItem, 20, stdin);
    
    //Removes the new line character from each response
    userRespondedItem[strlen(userRespondedItem) - 1] = '\0';
    userRespondedChar[strlen(userRespondedChar) - 1] = '\0';
    
    //Check variables
    int characterFound = 0;
    int itemFound = 0;
    int clueCharacterMatch = 0;
    int clueRoomMatch = 0;
    int clueItemMatch = 0;
    
    //Loops through characterList to check if user has entered a valid character
    for(int i = 0; i < 6; i++){
        if(strcmp(userRespondedChar, getCharacterName(characterList[i])) == 0){ 
            removeCharacterFromRoom(getCharacterCurrentRoom(characterList[i]), characterList[i]); //Removes character from their previous room
            addCharacterToRoom(avatarRoom, characterList[i]); //Adds the character to avatar's current room
            characterFound = 1;
            
            clueCharacterMatch = strcmp(userRespondedChar, getCharacterName(clueCharacter)) == 0? 1 : 0; //Stores the check for if the user response matches to the clue(solution)
        }
        if(strcmp(userRespondedItem, getItemName(itemList[i])) == 0){
            clueItemMatch = strcmp(getItemName(clueItem), userRespondedItem) == 0? 1 : 0; //Stores the check for if the user response matches to the clue(solution)
            itemFound = 1;
        }
        clueRoomMatch = strcmp(getRoomName(avatarRoom), getRoomName(clueRoom)) == 0? 1 : 0;//Stores the check for if the user response matches to the clue(solution)
    }
    
    //If character or item input was incorrect the function is called again
    if(characterFound == 0 || itemFound == 0){
        clueCount = clueCount - 1;
        clueCommand();
    }
    
    //Checks if all three inputs are correct
    if(clueItemMatch == 1 && clueRoomMatch == 1 && clueCharacterMatch == 1){
        printf("GAME WON\n");
        exit(1);
    }
    //Else checks which of the three responses are correct
    else if(clueItemMatch == 1 || clueRoomMatch == 1 || clueCharacterMatch == 1){
        if(clueItemMatch == 1){
            printf("Item Guessed Correctly\n");
        }
        if(clueRoomMatch == 1){
            printf("Avatar is correct room\n");
        }
        if(clueCharacterMatch == 1){
            printf("Character Guessed Correctly\n");
        }
    }
    //Else when all responses are incorrect
    else{
        printf("All guesses are incorrect\n");
    }
    
    //Checks if maximum clue calls are reached. After 10 calls game terminates
    if(clueCount == 10){
        printf("Maximum Clue Attempts Reached\nGame Failed\n");
        exit(0);
    }
    command();
}


