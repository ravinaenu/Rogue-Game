This program takes the file name as command line argument input, parses through the file and draws the Rogue game board with rooms and items. It allows user to play the Rogue game, by moving hero with 'w'(move up), 's'(move down), 'a'(move left), 'd'(move right) keys. Hero can pick the items like potion, magic, weapon or gold by simply moving on it. 
Message box at the top of the board will display the message whenever hero picksup any item. Message will contain the name and type of the item picked for weapon,potion and magic. And for gold, it will display the quantity of gold collected. 
There is a bottom item list box, which will display the total number of items present in all the rooms and number of items collected so far.

Enhancements
1) User can press 'i' to display or hide the inventory list. Inventory list displays the name and quantity of the items picked up.
It will display the inventory list side to the game board, which will extend the original game size (101 * 62) to (141 * 62)
2) All doors of all the rooms are connected by a middle hallway. i.e. in total there are 6 rooms, 3 at the top and 3 at the bottom; And there is a middle hallway which seperates top and bottom rooms. And all the doors of all the rooms are connected to this middle hallway.

Other features:
1) The position of the rooms on the board is dependent on non-repeating random number from 1-6. i.e. There are 6 room positions predefined on the board, and each room from text file gets drawn in any of the predefined room-position.
For example: Room1 defined in text file may get drawn on extreme right-top or extreme left-bottom or bottom-middle.., on the board based on random number.
 
2) Hallway logic determines the 'left' or 'right' side, to connect North-doors of all 3 top rooms AND south-doors of all 3 bottom rooms to middle hallway, based on the door's shortest distance from left or right side of the room. 

3) Use of color to make UI attractive


User can quit the game by pressing 'q'.


Other functions of assignment 2 are used i.e. to create box (drawBlock function), string parsing logic to eliminate extra white spaces and other related to display (i.e. displayMessage)


Limitations:
1) User can pick maximum 99 items of each types i.e. gold, potion, magic and weapon.
2) A single room can contain maximum 55 elements/items.
