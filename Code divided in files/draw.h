
#ifndef _RAVINA_DRAWH
#define _RAVINA_DRAWH

/*
 initGame: This function prints Rogue heading and calls drawBlock function to draw game border
 Pre: Empty screen
 Post: Upper 'Rogue' heading gets printed, Game board gets drawn, upper border partition to display messages
       and below border partition to display information related to items gets drawn
*/
void initGame(void);

/*
 drawBlock: This function prints game border and rooms
 Pre: It takes starting position of Y and X indexes i.e. startPosY, startPosX; Total vertical and horizontal size of
      the box to be drawn i.e. totalSizeY, totalSizeX; Character to use to draw Y and X axis i.e. charBoaderY, charBoaderX,
      example: charBoaderY = '|'; Color number to draw the borders i.e. color, it supports number from 1-7 each represents a color;
      To make the borders bold or not i.e. isBold, if isBold = 1 then bold borders or else normal border; To use the floor or not i.e. hasFloor,
      if hasFloor = 1 then room will have floor or else there will be an empty box.
 Post: By using the passed arguments, it draws game border and rooms with the floor
*/
void drawBlock(int startPosY, int startPosX,int totalSizeY, int totalSizeX, char charBoaderY, char charBoaderX, int color, int isBold, int hasFloor);

/*
 drawLine: This function draws horizontal line from left to right or vertical line from top to bottom
 Pre: It takes starting position of Y and X indexes i.e. startPosY, startPosX; Total vertical or horizontal size of
      the line to be drawn i.e. totalSize; Horizontal or vertical line to draw i.e. horizontalOrVertical, if horizontalOrVertical = 1
      then horizontal line or if 0 then vertical; Character to use to draw the line i.e. charBoader,
      example: charBoader = '|'; Color number to draw the line i.e. color, it supports number from 1-7 each represents a color;
      To make the borders bold or not i.e. isBold, if isBold = 1 then bold borders or else normal border;
 Post: By using the passed arguments, it draws either horizontal or vertical line
       It is used to draw the line creating the message space and info space where game messages and information
       related to items get displayed. It is also used to draw the each and individual hallway lines.
*/
void drawLine(int startPosY, int startPosX, int totalSize, int horizontalOrVertical, char charBoader, int color, int isBold);

/*
displayMessage: This function displays game messages or error message in upper message space
 Pre: It takes integer isError to display success or error message i.e. if isError = 1 then display error message or if its 0, then
      display success message; String message to additionally display the passed message; Display additional message corresponds
      to elementCode, elementCode can be an integer between 1-4.
 Post: If isError is 1, error message passed in message string will get displayed in message space. If isError is 0, then
       success message passed in message string along with the additional message corresponds to passed elementCode will get
       displayed in message space.
*/
void displayMessage(int isError, char message[], int elementCode);

/*
 hideMessage: This function clears the upper message space
 Pre: Non-empty message space
 Post: Empty message space, to display the next message
*/
void hideMessage(void);



/*
 processFileRoomsInput: This function takes array of strings roomContents, removes extra 'space' from each strings and then
        breaks each strings with 'space' delimeter and stores it in a new array of strings (i.e. now containing individual
        item strings), then it calls processAndDisplayElements function for further processing and display of items.
 Pre: It takes array of strings roomContents where there may be more than one space between each items in strings,
      The individual items in each strings need to be separated out and stored in an array of strings.
      It also takes a count of totalRooms, Hero struct and array of structs of Room to pass to processAndDisplayElements function.
 Post: Extra white spaces from each strings of roomContents get removed, a new array of strings gets created
       for each strings containing items (which were separated by a 'space'), The newly formed array of strings of items along
       with Hero struct and array of structs Room get passed to processAndDisplayElements function, totalRooms number
       of times i.e. for each strings of roomContents, for further processing and display of items.
*/
void processFileRoomsInput(char** roomContents,int totalRooms,Hero* hero,Room** room);

/*
 drawRoomElements: This function draws individual room items on the board.
 Pre: It takes Y and X position of the item to be drawn i.e. posY and posX; Character to draw on the board i.e.
      character element; Color number to draw the item i.e. color, it supports number from 1-7 each represents a color;
      To make the item bold or not i.e. isBold, if isBold = 1 then bold.
 Post: Based on the passed parameters, item gets drawn on the board i.e. (inside the room)
*/
void drawRoomElements(int posY, int posX, char element, int color, int isBold);

/*
 processAndDisplayElements: This function processes the individual element strings by determining which element the element
        string represents, separating out element's Y and X indexes, calculating the exact position on the board (with the help of calculatePositionAndDrawElement function),
        It also does error checking and correction for item's positioning on the board (i.e. inside the room).
        This function gets called totalRooms number of times from processFileRoomsInput function
 Pre: It takes array of string containing each item string i.e. elementsInRoom; Count of number of items string present in
      elementsInRoom i.e. totalElements; Number representing room's number in original text file i.e. currentRoomNumber;
      Number representing total number of rooms i.e. totalRooms; Hero struct; Array of structs Room; Number representing the room display position
      on the board (i.e. terminal). Uptill now no rooms or items get drawn on the board, this function will do the processing to display rooms, items
      and hallway on the board
 Post: It will process each items and passes them to calculatePositionAndDrawElement, connectRoomsHallway, drawBlock functions for either further processing
       or to actually draw on the board. It also initializes Hero and Room structs.
*/
void  processAndDisplayElements(char** elementsInRoom, int totalElements, int currentRoomNumber, int totalRooms, Hero* hero, Room** room, int displayRoomNumber);

/*
 calculatePositionAndDrawElement: This function extracts item's (i.e. hero, gold, potion, weapon, stairwall and magic) Y and X position,
        does the error checking and correction and calls drawRoomElements function to draw the items on the board
 Pre: It takes item string i.e. element; The string which is used to represent the item in original file i.e. elementInFile,
      example: for gold, elementInFile = "g"; Character to draw on the board i.e. elementToDraw, example: for gold, elementToDraw = '*';
      Starting Y and X position of the room i.e. roomStartPosY and roomStartPosX; Total horizontal or vertical size of the room i.e.
      totalSizeY and totalSizeX; Color number to draw the item with color i.e. color; To make the item bold or not i.e. isBold and Hero struct.
      Up till now item's exact position is not yet determined and not drawn on the board.
 Post: Exact location of an item with error checking and correction (if any) is determined. And drawRoomElements function gets called
       to draw the item on the board.
*/
void calculatePositionAndDrawElement(char* element, char elementInFile[2], char elementToDraw, int roomStartPosY, int roomStartPosX, int totalSizeY, int totalSizeX, int color, int isBold, Hero* hero);

/*
 connectRoomsHallway: This function calculates the location of hallway path and it calls drawLine function to draw
      the hallway.
 Pre: It takes character direction to determine the door's direction in the room, example: direction = 'n';
      Door's Y and X position i.e. doorPosY and doorPosX; Starting Y and X position of the room i.e. roomStartPosY and roomStartPosX;
      Total horizontal or vertical size of the room i.e. totalSizeY and totalSizeX;
      Up till now hallway path is not calculated or drawn yet.
 Post: Calculates the exact path of hallway and calls drawLine function to draw the hallway line by line.
*/
void connectRoomsHallway(char direction, int doorPosY, int doorPosX,int roomStartPosY, int roomStartPosX, int totalSizeY, int totalSizeX);



#endif