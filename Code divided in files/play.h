

#ifndef _RAVINA_PLAYH
#define _RAVINA_PLAYH

/*
 moveHeroAndPlay: This function moves the hero and picks up items.  It also does block checking to move the hero to only allowable blocks.
    It calls storeStatsAndDisplayMessage function to store the items picked up by hero and display the message in top message box.
 Pre: It takes a character input i.e. userInput to decide which direction to move, example: userInput='w' to move the hero to top;
      Struct Hero and array of structs Room and number of steps moved by hero i.e. stepsMoved.
 Post: If the next block is an allowable block, then hero moves or if the next block is an item block, hero picks up the item.
       After that storeStatsAndDisplayMessage function gets called to display the top message.
*/
void moveHeroAndPlay(char userInput, Hero* hero, Room** room, int stepsMoved);

/*
 storeStatsAndDisplayMessage: This function stores the picked up item in Hero struct and calls displayMessage function to display
      the message after a move. It generates a random number for every item picked up and stores it in item's array.
 Pre: It takes an enum element representing an item i.e. element = gold and so on; Hero struct and array of structs Room to
      store the item.
 Post: Picked up item gets added to Hero struct and top message gets displayed in message space.
*/
void storeStatsAndDisplayMessage(Elements element, Hero* hero, Room** room);

/*
 displayItemsCollected: This function displays the collected items and total items present in the board,
     at the bottom bar. It gets executed whenever hero moves to update the display of collected items list.
 Pre: It takes Hero struct and array of structs Room to calculate and display the total number of items
      and collected items at the bottom bar.
 Post: Updated collected items and total number of items list get displayed at the bottom item message space.
*/
void displayItemsCollected(Hero* hero, Room** room);

/*
 getPotion: This function stores the list of potion names in an array of strings, takes a number and stores the potion name
    corresponds to that number in passed address of string.
 Pre: It takes an integer number i.e. selectedPotion and stores the potion corresponds to that number from the list of
      names of potion, to the passed address of string i.e. potion
 Post: A potion name gets stored in address of string passed i.e. potion
*/
void getPotion(int selectedPotion, char** potion);

/*
 getWeapon: This function stores the list of weapon names in an array of strings, takes a number and stores the weapon name
    corresponds to that number in passed address of string.
 Pre: It takes an integer number i.e. selectedWeapon and stores the weapon corresponds to that number from the list of
      names of weapon, to the passed address of string i.e. weapon
 Post: A weapon name gets stored in address of string passed i.e. weapon
*/
void getWeapon(int selectedWeapon, char** weapon);

/*
 getMagic: This function stores the list of magic names in an array of strings, takes a number and stores the magic name
    corresponds to that number in passed address of string.
 Pre: It takes an integer number i.e. selectedMagic and stores the magic corresponds to that number from the list of
      names of magic, to the passed address of string i.e. magic
 Post: A magic name gets stored in address of string passed i.e. magic
*/
void getMagic(int selectedMagic, char** magic);

/*
 displayInventoryInformation: This function toggles the display (hide or show) of the right side inventory list. It
      displays the name and total quantity of item of specific type collected. To display the name of types of item,
      it calls getPotion, getMagic and getWeapon function to get the item type's name.
 Pre: It takes an integer hideOrShow to hide or show the inventory list i.e. if hideOrShow = 1 then show or else
      if its 0 then hide; Hero struct and array of structs Room to calculate total number of items and to display
      collected items. It calls getPotion, getWeapon, getMagic to get the name of items collected.
 Post: Hides or shows the right side updated inventory list, with specific name and quantity of items.
*/
void displayInventoryInformation(int hideOrShow, Hero* hero, Room** room);

#endif