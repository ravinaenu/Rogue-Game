#include <curses.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* Game border 62 * 100 */
#define GAMESPACEY 62
#define GAMESPACEX 100

/* Info space to display Items Info */
#define GAMEINFOSPACEY 3
#define GAMEINFOSPACEX 98

/* Message space to display Messages */
#define MESSAGEINFOSPACEY 3
#define MESSAGEINFOSPACEX 98


/* Room's starting co ordinates */
#define BORDER 2
#define MAXROOMY 20
#define MAXROOMX 25
#define HALLWAYSTARTY 31
#define HALLWAYSTARTX 2
#define HALLWAYSIZE 97

#define Room1STARTY 8
#define Room1STARTX 4
#define Room2STARTY 8
#define Room2STARTX 36
#define Room3STARTY 8
#define Room3STARTX 68
#define Room4STARTY 33
#define Room4STARTX 4
#define Room5STARTY 33
#define Room5STARTX 36
#define Room6STARTY 33
#define Room6STARTX 68

typedef struct gameHero
{
    char charHero;
    int posY;
    int posX;
    int lastPosY;
    int lastPosX;
    char charAtLastPos;
    int color;
    int gold;
    int goldPoints;
    int weapon;
    int potion;
    int magic;
    int collectedPotion[99];
    int collectedWeapon[99];
    int collectedMagic[99];

} Hero;

typedef struct gameRoom
{
    int posY;
    int posX;
    int sizeY;
    int sizeX;
    int totalDoors;
    int totalGold;
    int totalWeapon;
    int totalPotion;
    int totalMagic;
    int totalMonsters;
    int stairsInThisRoom;
    int heroInThisRoom;
    int roomNumber;

} Room;

typedef enum {
    floorOrSteps = 0,
    gold = 1,
    potion = 2,
    weapon = 3,
    magic = 4
}  Elements;

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
 memoryAllocation: This function allocates memory for array of strings and returns it, to store the content of file in it.
 Pre: It takes integer totalRooms as input to allocate memory for that many strings.
 Post: It returns memory allocated array of strings, memory is allocated for passed totalRooms number of strings.
*/
char** memoryAllocation(int totalRooms);

/*
 memoryAllocationHero: This function allocates memory for Hero struct and returns it, to store parameters related to hero in it.
 Pre: It simply allocates memory for Hero struct
 Post: It returns memory allocated Hero struct
*/
Hero* memoryAllocationHero();

/*
 memoryAllocationRoom: This function allocates memory for array of structs Room and returns it, to store parameters related to each rooms in it.
 Pre: It takes integer totalRooms as input to allocate memory for that many structs.
 Post: It returns memory allocated array of structs Room, memory is allocated for passed totalRooms number of structs.
*/
Room** memoryAllocationRoom(int totalRooms);

/*
 memoryDeallocation: This function deallocates memory i.e. frees the memory
 Pre: It takes memory allocated, array of Room struct i.e. room, Hero struct hero,
      array of strings roomContents, integer totalRooms and string fileName.
 Post: It frees the memory.
*/
void memoryDeallocation(char** roomContents,int totalRooms,Hero* hero,Room** room,char* fileName);

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


int main(int argc, char *argv[])
{

    Hero* hero = NULL;
    Room** room = NULL;
    FILE *ptrFile;
    char** roomContents = NULL;
    int totalRooms = 6, count = 0, stepsMoved = 0, displayInventory = 0;
    char tempRoom[175];
    char userInput = ' ';
    char* fileName;

    /* start the ncurses mode */
    initscr();
    cbreak();
    noecho();


    start_color();
    srand(time(NULL));
    /* color pairs that are used to show colors */
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);



    /* function to initialize game, draw outer border, space to display
    game information and messages */
    initGame();


    /* Error if file name is not specified in command line argument*/
    if (argc != 2)
    {
        displayMessage(1,"File name is not specified in command line argument",0);
        getch();
        exit(1);

    }

    /* If file extension is not specified along with the file name, add it */
    fileName = malloc(sizeof(char)*(strlen(argv[1])+1));
    strcpy(fileName,argv[1]);
    fileName = strtok(fileName,".");
    strcat(fileName,".txt");

    if ((ptrFile=fopen(fileName,"r"))==NULL){
       displayMessage(1,"Error in reading file, please check the path specified",0);
       getch();
       exit(1);         /* Program exits if file pointer returns NULL. */
    }


    /* Allocate Memory */
    roomContents = memoryAllocation(totalRooms);
    hero = memoryAllocationHero();
    room = memoryAllocationRoom(totalRooms);

    while (fgets(tempRoom, sizeof tempRoom, ptrFile) != NULL) /* Read a line from the file, until the end */
    {
        if (count > 5)
        {
            break;
        }
        tempRoom[(strlen(tempRoom)-1)] = '\0'; /* Remove new line */
        roomContents[count] = malloc((strlen(tempRoom)+1) * sizeof(char)); /* Allocate space in roomContent, based on line size */
        strcpy(roomContents[count],tempRoom); /* Copy the content of each lines to roomContent i.e. Array of strings */
        count++;
    }
    totalRooms = count;
    fclose(ptrFile);

    /* Function to process the input received from the file and call other functions to
     draw the game room layout */
    processFileRoomsInput(roomContents,totalRooms,hero,room);
    /* Function to display the Items info list i.e. list present below the rooms  */
    displayItemsCollected(hero, room);

    move(hero->posY,hero->posX); /* move the cursor to hero's co-ordinates*/

    /* If user presses 'q' then quit */
    while (userInput != 'q')
    {
         userInput = getch();
         if (isalpha(userInput))
         {
            userInput = tolower(userInput);
         }

         if ((userInput == 'w') || (userInput == 's') || (userInput == 'a') || (userInput == 'd'))
         {

            moveHeroAndPlay(userInput, hero, room, stepsMoved); /* Function to move the hero */
            stepsMoved++;
            if (displayInventory == 1)
             {
                  /* Function to display inventory information */
                  displayInventoryInformation(displayInventory, hero, room);
             }

         }
         else if (userInput == 'i') /* On press of 'i', toggle the display of inventory information */
         {
             if (displayInventory == 0)
             {
                 displayInventory =1;
             }
             else
             {
                 displayInventory =0;
             }
             displayInventoryInformation(displayInventory, hero, room);
         }
         else /* if any non-supported key is pressed */
         {
            displayMessage(0,"Only 'w', 's', 'a', 'd', 'i' and 'q' keys are supported.",0);

         }
         move(hero->posY,hero->posX);

    }


    /* Free Memory */
    memoryDeallocation(roomContents,totalRooms,hero,room,fileName);


    endwin();
    return 0;

}

/* This function initializes the game, draws the game border, space to display message and information,
draws game logo.
It doesn't take any values and doesn't return anything.
*/
void initGame(void)
{
    attron(A_BOLD);

    attron(COLOR_PAIR(2));
    mvprintw(0,41," R ");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(7));
    mvprintw(0,44,"O ");
    attroff(COLOR_PAIR(7));

    attron(COLOR_PAIR(2));
    mvprintw(0,46,"G ");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(7));
    mvprintw(0,48,"U ");
    attroff(COLOR_PAIR(7));

    attron(COLOR_PAIR(2));
    mvprintw(0,50,"E ");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(5));
    mvprintw(0,52,"  3.6.3 ");
    attroff(COLOR_PAIR(5));

    attroff(A_BOLD);

    refresh();



    drawBlock(1,0,GAMESPACEY, GAMESPACEX,'|','-',7,1,0); /* draw game border box */
    drawLine(4,1,GAMEINFOSPACEX + 1,1,'_',5,0); /* draw horizontal message border */
    drawLine(57,1,MESSAGEINFOSPACEX + 1,1,'_',5,0); /* draw horizontal info border */
    refresh();
    drawLine(2,78,5,2,'|',6,0);
    drawLine(HALLWAYSTARTY,HALLWAYSTARTX,HALLWAYSIZE,1,'#',7,0); /*draw middle hallway line */
    attron(A_BOLD);

    attron(COLOR_PAIR(7));
    mvprintw(3,82,"Level ");
    mvprintw(3,91,"Hp ");
    attroff(COLOR_PAIR(7));


    attron(COLOR_PAIR(2));
    mvprintw(3,94,"25 ");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(3));
    mvprintw(3,88,"1 ");
    attroff(COLOR_PAIR(3));


    attron(COLOR_PAIR(4));
    mvprintw(59,10,"Gold: ");
    attroff(COLOR_PAIR(4));


    attron(COLOR_PAIR(3));
    mvprintw(59,32,"Weapon: ");
    attroff(COLOR_PAIR(3));


    attron(COLOR_PAIR(1));
    mvprintw(59,53,"Potion: ");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(6));
    mvprintw(59,74,"Magic: ");
    attroff(COLOR_PAIR(6));


    attroff(A_BOLD);

    refresh();
    move(3,1);

}

/* This function is used to draw various rooms and outer game border.
It takes starting X and Y position i.e. startPosY, startPosX; Total horizontal and vertical board/room
size i.e. totalSizeY, totalSizeX; Character border to draw the board i.e. '-', charBoarderY, charBorderX;
color of the border i.e. color; To make the border bold or not i.e. isBold, where isBold =1 means bold
border and 0 means normal border; and to display floor or not i.e. hasFloor, hasFloor =1 to display floor.
It doesn't return anything.
*/
void drawBlock(int startPosY, int startPosX,int totalSizeY, int totalSizeX, char charBoaderY, char charBoaderX, int color, int isBold, int hasFloor)
{
    /*
    Draw the board based on startPosY, startPosX to totalSizeY and totalSizeX
    */
   int i=startPosY,j=startPosX;

   for (i=startPosY;i<totalSizeY;i++)
   {
        if ((i==startPosY)||(i==totalSizeY-1))/* Draw only to starting and ending position */
        {
            for (j=startPosX;j<totalSizeX;j++)
            {
                if (isBold)
                {
                    attron(COLOR_PAIR(color));
                    attron(A_BOLD);
                    mvaddch(i, j, charBoaderX);
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(color));

                }
                else
                {
                    attron(COLOR_PAIR(color));
                    mvaddch(i, j, charBoaderX);
                    attroff(COLOR_PAIR(color));

                }

            }

        }
        else
        {
            for (j=startPosX;j<totalSizeX;j++)
            {
                /* Draw only to starting and ending position i.e. draw border */
                if ((j==startPosX)||(j==totalSizeX-1))
                {
                    if (isBold)
                    {
                        attron(COLOR_PAIR(color));
                        attron(A_BOLD);
                        mvaddch(i, j, charBoaderY);
                        attroff(A_BOLD);
                        attroff(COLOR_PAIR(color));

                    }
                    else
                    {
                        attron(COLOR_PAIR(color));
                        mvaddch(i, j, charBoaderY);
                        attroff(COLOR_PAIR(color));

                    }

                }
                else /* if not starting or ending position i.e. inner positions, then draw floor */
                {
                    if (hasFloor == 1)
                    {
                         mvaddch(i, j, '.');

                    }

                }

            }

        }

    }
}

/* This function is used to draw horizontal or vertical lines.
It takes what lines to draw i.e. horizontalOrVertical, if horizontalOrVertical = 1 the horizontal else if
horizontalOrVertical = 0, then vertical; starting co-ordinates of the line i.e. startPosY, startPosX;
Total size of the line i.e. totalSize; Character border to draw the line i.e. '-', charBoader;
color of the line i.e. color; And to make line bold or not i.e. isBold, if isBold = 1 then bold line.
It doesn't return anything.
*/
void drawLine(int startPosY, int startPosX, int totalSize, int horizontalOrVertical, char charBoader, int color, int isBold)
{
    /*
    Draw the board based on startPosY, startPosX to totalSize
    if horizontalOrVertical == 1 then horizontal else if 2, then vertical
    */
   int i=startPosY,j=startPosX;
   if (horizontalOrVertical == 1) /* Horizontal line */
   {
       for (j=startPosX;j<totalSize;j++) /* Draw line from left to right */
       {

           if (isBold)
           {
                attron(COLOR_PAIR(color));
                attron(A_BOLD);
                mvaddch(i, j, charBoader);
                attroff(A_BOLD);
                attroff(COLOR_PAIR(color));

            }
            else
            {
                attron(COLOR_PAIR(color));
                mvaddch(i, j, charBoader);
                attroff(COLOR_PAIR(color));

            }

       }

   }
   else if (horizontalOrVertical == 2) /* Vertical line */
   {

        for (i=startPosY;i<totalSize;i++) /* Draw line from top to bottom */
        {
           if (isBold)
           {
                attron(COLOR_PAIR(color));
                attron(A_BOLD);
                mvaddch(i, j, charBoader);
                attroff(A_BOLD);
                attroff(COLOR_PAIR(color));

            }
            else
            {
                attron(COLOR_PAIR(color));
                mvaddch(i, j, charBoader);
                attroff(COLOR_PAIR(color));

            }

       }

   }

}

/* This function displays the messages in the upper message space.
It displays error if isError = 1 or else normal message.
It takes messages to display i.e. message[] and integer elementCode to display additional message based on the elementCode i.e. 1-4
It doesn't return anything.
*/
void displayMessage(int isError, char message[], int elementCode)
{
    hideMessage(); /* Function to clear the message space i.e. to clear existence message*/
    if (isError == 1) /* To display error message */
    {
        attron(COLOR_PAIR(2));
        attron(A_BOLD);
        mvprintw(3,1,"%s",message);
        attroff(A_BOLD);
        attroff(COLOR_PAIR(2));

    }
    else /* Not an error message */
    {
        attron(A_BOLD);
        if (elementCode == 1) /* Gold */
        {
            attron(COLOR_PAIR(4));
            mvprintw(3,1,"%s","   *  ");
            attroff(COLOR_PAIR(4));

        }
        else if (elementCode == 2) /* Potion */
        {
            attron(COLOR_PAIR(1));
            mvprintw(3,1,"%s","   !  ");
            attroff(COLOR_PAIR(1));

        }
        else if (elementCode == 3) /* Weapon */
        {
            attron(COLOR_PAIR(3));
            mvprintw(3,1,"%s","   )  ");
            attroff(COLOR_PAIR(3));

        }
        else if (elementCode == 4) /* Magic */
        {
            attron(COLOR_PAIR(6));
            mvprintw(3,1,"%s","   $  ");
            attroff(COLOR_PAIR(6));

        }
        attron(COLOR_PAIR(7));
        mvprintw(3,8,"%s",message);
        attroff(COLOR_PAIR(7));

        attroff(A_BOLD);

    }

}

/* This function clears the messages from upper message window.
It doesn't take any values and doesn't return anything
*/
void hideMessage(void)
{
mvprintw(2,1,"                                                                             ");
mvprintw(3,1,"                                                                             ");

}


/* This function allocates the memory for array of strings rooms.
It takes totalRooms as input to allocate that many number of spaces and returns Array of strings
*/
char** memoryAllocation(int totalRooms)
{
    char** roomContents;

    roomContents = malloc(totalRooms * sizeof(char*));

    if (roomContents == NULL) /* If error while memory allocation, then display the message and end the program */
    {
        displayMessage(1,"Error while allocating memory",0);
        getch();
        exit(1);
    }

    return roomContents;

}

/* This function allocates the memory to Hero struct.
It doesn't take any input and returns the Hero struct.
*/
Hero* memoryAllocationHero()
{
    Hero* hero;
    hero = malloc(sizeof(Hero));
    if (hero == NULL)
    {
        displayMessage(1,"Error while allocating memory",0);
        getch();
        exit(1);
    }

    return hero;

}

/* This function allocates the memory to Room i.e. array of struct.
It takes totalRooms integer as input to allocate memory for that many struct and returns the array of struct i.e Room.
*/
Room** memoryAllocationRoom(int totalRooms)
{
    int i= 0;
    Room** room;
    room = malloc(sizeof(Room*)*totalRooms);
    if (room == NULL)
    {
        displayMessage(1,"Error while allocating memory",0);
        getch();
        exit(1);
    }

    for (i=0; i<totalRooms; i++)
    {
        room[i] = malloc(sizeof(Room));
        if (room[i] == NULL)
        {
            displayMessage(1,"Error while allocating memory",0);
            getch();
            exit(1);

        }

    }

    return room;

}


/* This function deallocates the memory.
It takes array of strings roomContents, integer totalRooms, struct hero, array of structs room and string fileName
to free the memory.
It doesn't return anything.

*/
void memoryDeallocation(char** roomContents,int totalRooms,Hero* hero,Room** room, char* fileName)
{
    int i = 0;
    for (i =0; i<totalRooms;i++) /* Free the memory for all totalRooms rooms */
    {
       free(roomContents[i]);
       free(room[i]);
       roomContents[i] = NULL;
       room[i] = NULL;
    }

    free(roomContents);
    free(room);
    free(hero);
    hero = NULL;
    free(fileName);
    fileName = NULL;

}

/* This function takes the strings of roomContents, processes it by breaking the string based on 'space' delimeter
   and stores all the generated substrings in an array of strings, then it calls  processAndDisplayElements function
   to display all the individual elements.
   It takes input from the file, stored in array of strings i.e. roomContents; Count of total rooms i.e. integer totalRooms;
   Struct hero and array of struct room.
   It doesn't return anything.
*/
void processFileRoomsInput(char** roomContents, int totalRooms, Hero* hero, Room** room)
{
    int i = 0, random = 0, j = 0, maxElements = 55, totalRoomContentLength = 0, k = 0;
    char** elementsInRoom; /* store maximum 55 words */
    int randomArray[6];
    char tempString2[174], tempString[174];
    char tempRoom[174];
    int counter = 0, elementCounter = 0, roomNumber = 0;

    /* Random number generation, for placement of the rooms
       Non-repeating random numbers between 1 to 6
    */
    while (i<totalRooms)
    {
        random = (rand()%totalRooms)+1;
        for (j = 0; j < i; j++)
        {
            if (randomArray[j] == random)
            {
                break;
            }
        }
        if (j==i){
            randomArray[i++]=random; /* store all non-repeating 1-6 random numbers in the array of int i.e. randomArray */
        }
    }

    elementsInRoom = malloc(maxElements * sizeof(char*));

    for (k=0; k<totalRooms; k++) /* For each rooms */
    {
        strcpy(tempString2,roomContents[k]); /* Temporarily copy the content of the room to a string i.e. tempString2, for processing */

        /* Compress the multiple occurrences of space */
        for (i=0, j=0; tempString2[i] != '\0'; i++, j++)
        {
            if (tempString2[i] == ' ' && tempString2[i+1] == ' ') /* If consecutive spaces are found */
            {
                j--;
                continue;
            }
            /* Add next character(other than a 'space') to tempString string,
               immediately after the single space (i.e. after compressing consecutive spaces) */
            tempString[j] = tempString2[i];
        }
        tempString[j] = '\0';

       totalRoomContentLength = strlen(tempString);

        /* Split the roomContent based on space to get the
           individual room elements */
        counter = 0;
        for (i=0; i<totalRoomContentLength; i++)
        {
            if (isspace(tempString[i])) /* Split the string to words based on 'space' delimiter */
            {
                if (i != 0) /* If it's not a first character */
                {
                    tempRoom[counter] = '\0'; /* When space encountered, end the string */
                    counter = 0;
                    if ((elementsInRoom[elementCounter] = malloc(sizeof(char) * (strlen(tempRoom)+1))) == NULL)
                    {
                        displayMessage(1,"Error while allocating memory",0);
                        getch();
                        exit(1);
                    }
                    strcpy(elementsInRoom[elementCounter], tempRoom); /* Add the string to array of strings i.e. elementsInRoom */
                    elementCounter++;
                    strcpy(tempRoom, "");
                }
            }
            else /* If it's not a space */
            {
                tempRoom[counter] = tempString[i]; /* Add character to a string tempRoom */
                counter++;
                if (i == totalRoomContentLength-1) /* When last character */
                {
                    tempRoom[counter] = '\0'; /* When last character, end the string */
                    if ((elementsInRoom[elementCounter] = malloc(sizeof(char) * (strlen(tempRoom)+1))) == NULL)
                    {
                        displayMessage(1,"Error while allocating memory",0);
                        getch();
                        exit(1);
                    }
                    strcpy(elementsInRoom[elementCounter], tempRoom);
                    elementCounter++;
                }

            }
        }

        roomNumber = randomArray[k]; /* Get Room number from randomArray i.e. from 1 to 6 */

        /* This function processes all the elements and displays on the board i.e. room and it's elements */
        processAndDisplayElements(elementsInRoom,elementCounter,k,totalRooms,hero,room,roomNumber);

        /* Nullify the variables and free the memory */
        strcpy(tempString2,"");
        strcpy(tempString,"");
        strcpy(tempRoom,"");
        totalRoomContentLength = 0;
        counter = 0;
        for (i = 0; i<elementCounter; i++)
        {
            free(elementsInRoom[i]);
            elementsInRoom[i] = NULL;
        }
        elementCounter = 0;

    }
        free(elementsInRoom);

}

/* This function draws the individual room elements. It take x and y position of the element i.e.
   posY and posX; Character to draw the element i.e. element, eg: element = '@'; The color of element i.e. integer color,
   it can be any integer from 1-7; To make element bold or not i.e. int isBold, if isBold = 1, make the element bold.
   It doesn't return anything.
*/
void drawRoomElements(int posY, int posX, char element, int color, int isBold)
{
    if (isBold)
    {
        attron(COLOR_PAIR(color));
        attron(A_BOLD);
        mvaddch(posY, posX, element);
        attroff(A_BOLD);
        attroff(COLOR_PAIR(color));

    }
    else
    {
        attron(COLOR_PAIR(color));
        mvaddch(posY, posX, element);
        attroff(COLOR_PAIR(color));

    }
    refresh();

}

/* This function processes the individual elements and then calls other functions to actually draw elements on the board.
   It takes the string of individual elements for example 'de4', breaks it, does the error checking and correction and calls the function
   to draw that element on the board.
   It takes array of string containing all the element string of the room i.e. elementsInRoom; Total number of elements present i.e.
   totalElements; original position of the room number in the file i.e. currentRoomNumber; Total number of rooms i.e.
   totalRooms; Struct Hero; Array of struct room; Display position of the room number on the board i.e. displayRoomNumber.
   It doesn't return anything.
*/
void  processAndDisplayElements(char** elementsInRoom, int totalElements, int currentRoomNumber, int totalRooms, Hero* hero, Room** room, int displayRoomNumber)
{
    int i = 0, roomStartPosY = 0, roomStartPosX = 0, totalSizeY = 0, totalSizeX = 0, doorPosition = 0;
    int tempTotalSizeY = 0, tempTotalSizeX = 0, totalRoomDoors = 0, elementPosY = 0, elementPosX = 0;
    int totalRoomGold = 0, totalRoomWeapon = 0, totalRoomPotion = 0, totalRoomMagic = 0, totalRoomMonster = 0;
    int stairsInRoom = 0, heroInRoom = 0;
    char* element;
    char* tokenElement;
    char elementInFile[2];
    element = malloc(sizeof(char)*11); /* element representing the individual element */
    if (element == NULL)
    {
        displayMessage(1,"Error while allocating memory",0);
        getch();
        exit(1);
    }

    switch (displayRoomNumber) /* Based on displayRoomNumber, assign the starting co-ordinates of Y and X, to draw rooms */
    {
    case 1:
        {
            roomStartPosY = Room1STARTY;
            roomStartPosX = Room1STARTX;
            break;
        }
    case 2:
        {
            roomStartPosY = Room2STARTY;
            roomStartPosX = Room2STARTX;
            break;
        }
    case 3:
        {
            roomStartPosY = Room3STARTY;
            roomStartPosX = Room3STARTX;
            break;
        }
    case 4:
        {
            roomStartPosY = Room4STARTY;
            roomStartPosX = Room4STARTX;
            break;
        }
    case 5:
        {
            roomStartPosY = Room5STARTY;
            roomStartPosX = Room5STARTX;
            break;
        }
    case 6:
        {
            roomStartPosY = Room6STARTY;
            roomStartPosX = Room6STARTX;
            break;
        }

    }


    for (i=0;i<totalElements;i++) /* For every elements */
    {
        strcpy(elementInFile,"");
        strcpy(element,elementsInRoom[i]); /* Copy individual element to element string */

        /* Extract the individual room dimensions from the first string */
        if (i == 0) /* First element will be the room dimensions */
        {
            tokenElement = strtok(element, "Xx*");
            totalSizeY = atoi(tokenElement);
            if (totalSizeY > MAXROOMY) /* If size of Y co-ordinate  is greater than maximum allowable size i.e. 20 */
            {
                totalSizeY = MAXROOMY; /* Set it to max size */
            }
            else if (totalSizeY <= 0)
            {
                totalSizeY = 1;
            }
            tokenElement = strtok(NULL, "Xx*");
            totalSizeX = atoi(tokenElement);
            if (totalSizeX > MAXROOMX) /* If size of X co-ordinate is greater than maximum allowable size i.e. 25 */
            {
                totalSizeX = MAXROOMX; /* Set it to max size */
            }
            else if (totalSizeX <= 0)
            {
                totalSizeX = 1;
            }
            /* Draw Room with border */
            tempTotalSizeY = roomStartPosY+BORDER+totalSizeY;
            tempTotalSizeX = roomStartPosX+BORDER+totalSizeX;

            /* Call this function to draw the box, it takes starting Y and X co-ordinates, total Y and X size,
               character of borders, color number, to make it bold or not and to add floor to box or not */
            drawBlock(roomStartPosY,roomStartPosX,tempTotalSizeY,tempTotalSizeX,'|','-',7,0,1);
        }


        if (element[0]=='d') /* To draw door */
        {
              totalRoomDoors++;

              if (element[1] == 'n') /* Door on north wall */
              {
                    tokenElement = strtok(element, "dn");
                    doorPosition = atoi(tokenElement);
                    if (doorPosition > totalSizeX) /* If door position is greater than total size of room */
                    {
                        doorPosition = totalSizeX; /* Then, door position will be at the last co-ordinate */
                    }
                    else if (doorPosition <= 0) /* If door position is zero or less */
                    {
                        doorPosition = 1; /* Then, door position will be at the first co-ordinate */
                    }
                    elementPosY = roomStartPosY;
                    elementPosX = roomStartPosX + doorPosition;

              }
              else if (element[1] == 'e') /* Door on east wall */
              {
                   tokenElement = strtok(element, "de");
                   doorPosition = atoi(tokenElement);
                   if (doorPosition > totalSizeY)
                   {
                       doorPosition = totalSizeY;
                   }
                   else if (doorPosition <= 0)
                   {
                       doorPosition = 1;
                   }
                   elementPosY = roomStartPosY +doorPosition;
                   elementPosX = roomStartPosX + totalSizeX + 1;

              }
              else if (element[1] == 's') /* Door on south wall */
              {
                  tokenElement = strtok(element, "ds");
                  doorPosition = atoi(tokenElement);
                  if (doorPosition > totalSizeX)
                  {
                      doorPosition = totalSizeX;
                  }
                  else if (doorPosition <= 0)
                  {
                      doorPosition = 1;
                  }
                  elementPosY = roomStartPosY + totalSizeY + 1;
                  elementPosX = roomStartPosX +doorPosition;

              }
              else if (element[1] == 'w') /* Door on west wall */
              {

                  tokenElement = strtok(element, "dw");
                  doorPosition = atoi(tokenElement);
                  if (doorPosition > totalSizeY)
                  {
                      doorPosition = totalSizeY;
                  }
                  else if (doorPosition <= 0)
                  {
                      doorPosition = 1;
                  }
                  elementPosY = roomStartPosY + doorPosition;
                  elementPosX = roomStartPosX;


              }
              /* Call this function to draw the room elements, it takes Y and X position of the element, character to draw,
                 color number, and to make it bold or not */
              drawRoomElements(elementPosY, elementPosX, '+', 7, 1);
              /* Call this function to draw to connect the door to the hallway, it takes which direction the door is i.e. 'n' or 's' and so on i.e. element[1],
                 Y and X position, starting Y and X position of the room, total horizontal and vertical size of the room */
              connectRoomsHallway(element[1], elementPosY, elementPosX, roomStartPosY, roomStartPosX, totalSizeY, totalSizeX);

        }

        if (element[0]=='s') /* Stairs */
        {
            stairsInRoom = 1;
            strcpy(elementInFile,"s");
            /* Call this function to extract the position of the element from the element string and draw the element on the board,
               it takes element string, elementInFile i.e. element to draw as mentioned in original file i.e. to draw gold "g" in string format,
               starting Y and X position of room, total horizontal and vertical size of room, color number, to make it bold or not and hero struct */
            calculatePositionAndDrawElement(element,elementInFile,'%',roomStartPosY,roomStartPosX,totalSizeY,totalSizeX,7,1,hero);

        }
        else if (element[0]=='g') /* Gold */
        {
            totalRoomGold++;
            strcpy(elementInFile,"g");
            calculatePositionAndDrawElement(element,elementInFile,'*',roomStartPosY,roomStartPosX,totalSizeY,totalSizeX,4,1,hero);

        }
        else if (element[0]=='m') /* Magic */
        {
            totalRoomMagic++;
            strcpy(elementInFile,"m");
            calculatePositionAndDrawElement(element,elementInFile,'$',roomStartPosY,roomStartPosX,totalSizeY,totalSizeX,6,1,hero);

        }

        else if (element[0]=='p') /* Potion */
        {
            totalRoomPotion++;
            strcpy(elementInFile,"p");
            calculatePositionAndDrawElement(element,elementInFile,'!',roomStartPosY,roomStartPosX,totalSizeY,totalSizeX,1,1,hero);

        }
        else if (element[0]=='w') /* Weapon */
        {
            totalRoomWeapon++;
            strcpy(elementInFile,"w");
            calculatePositionAndDrawElement(element,elementInFile,')',roomStartPosY,roomStartPosX,totalSizeY,totalSizeX,3,1,hero);

        }
        else if (element[0]=='M') /* Monsters */
        {
            totalRoomMonster++;
            strcpy(elementInFile,"M");
            calculatePositionAndDrawElement(element,elementInFile,'M',roomStartPosY,roomStartPosX,totalSizeY,totalSizeX,2,1,hero);


        }
        else if (element[0]=='h') /* Hero */
        {
            heroInRoom = 1;

            strcpy(elementInFile,"h");
            calculatePositionAndDrawElement(element,elementInFile,'@',roomStartPosY,roomStartPosX,totalSizeY,totalSizeX,5,1,hero);

            /* Initialize hero's members */
            hero->charHero = '@';
            hero->color = 5;
            hero->gold= 0;
            hero->goldPoints = 0;
            hero->magic = 0;
            hero->potion = 0;
            hero->weapon = 0;


        }

        strcpy(element,"");
        elementPosY = 0;
        elementPosX = 0;
    }

    /* Initialize all room's members */
    room[currentRoomNumber]->posY = roomStartPosY;
    room[currentRoomNumber]->posX = roomStartPosX;
    room[currentRoomNumber]->sizeY = totalSizeY;
    room[currentRoomNumber]->sizeX = totalSizeX;
    room[currentRoomNumber]->totalDoors = totalRoomDoors;
    room[currentRoomNumber]->totalGold = totalRoomGold;
    room[currentRoomNumber]->totalWeapon = totalRoomWeapon;
    room[currentRoomNumber]->totalPotion = totalRoomPotion;
    room[currentRoomNumber]->totalMagic = totalRoomMagic;
    room[currentRoomNumber]->totalMonsters = totalRoomMonster;
    room[currentRoomNumber]->stairsInThisRoom = stairsInRoom;
    room[currentRoomNumber]->heroInThisRoom = heroInRoom;
    room[currentRoomNumber]->roomNumber = currentRoomNumber;

    free(element);
    element = NULL;

}

/* This function extracts the position from the element string to draw the element on the board. It also does error checking
   and error correction. It takes element string i.e. element; Identity of the element mentioned in original file in string format
   i.e. elementInFile, example: elementInFile = "g" for gold; Character to draw the element i.e. elementToDraw,
   example: elementToDraw = '*'; Starting Y and X position of the room i.e. roomStartPosY and roomStartPosX;
   Total horizontal and vertical size of the room i.e. totalSizeY and totalSizeX; Color number of the element to draw i.e. color,
   example: color = 4; To make the element bold or not i.e. isBold,if isBold = 1 then make it bold and Hero struct.
   It doesn't return anything.
*/
void calculatePositionAndDrawElement(char* element, char elementInFile[2], char elementToDraw, int roomStartPosY, int roomStartPosX, int totalSizeY, int totalSizeX, int color, int isBold, Hero* hero)
{
    char* tokenElement;
    int elementPosY = 0, elementPosX = 0;

    tokenElement = strtok(element, elementInFile);
    tokenElement = strtok(tokenElement, ",");
    elementPosY = atoi(tokenElement); /* Get Y co-ordinate of the element */
    tokenElement = strtok(NULL, ",");
    elementPosX = atoi(tokenElement); /* Get X co-ordinate of the element  */


    elementPosY = elementPosY + 1;
    if (elementPosY <= 0) /* If it's less than zero, then make it 1 */
    {
        elementPosY = 1;

    }
    else if (elementPosY > totalSizeY) /*If it's greater than total size, then make it max size */
    {
        elementPosY = totalSizeY;
    }

    /* Calculate the exact Y co-ordinate on the screen i.e. element position given as input + actual starting
       co-ordinate of the room on the terminal */
    elementPosY = (elementPosY)  + roomStartPosY;

    elementPosX = elementPosX + 1;
    if (elementPosX <= 0)
    {
        elementPosX = 1;

    }
    else if (elementPosX > totalSizeX)
    {
        elementPosX = totalSizeX;
    }

    /* Calculate the exact X co-ordinate on the screen i.e. element position given as input + actual starting
       co-ordinate of the room on the terminal */
    elementPosX = (elementPosX)  + roomStartPosX;

    if (elementToDraw == '@') /* if Hero, then set hero's position */
    {
        hero->posY = elementPosY;
        hero->posX = elementPosX;
    }

    /* Call this function to draw the room elements, it takes Y and X position of the element, character to draw,
                 color number, and to make it bold or not */
    drawRoomElements(elementPosY, elementPosX, elementToDraw, color, isBold);


}

/* This function draws the hallway.
   It takes door's direction i.e. direction, example: direction='n'for door position at north of the room; Door's Y and X position
   i.e. doorPosY, doorPosX; Room's starting Y and X position (top-left) i.e. roomStartPosY, roomStartPosX;
   Total horizontal and vertical size of the room i.e. totalSizeY, totalSizeX;
   It doesn't return anything.

*/
void connectRoomsHallway(char direction, int doorPosY, int doorPosX, int roomStartPosY, int roomStartPosX, int totalSizeY, int totalSizeX)
{
    int startPosY = 0, startPosX = 0, lineSize = 0;

    if (direction == 'n') /* Door at north */
    {
        if (roomStartPosY < HALLWAYSTARTY) /* For the top 3 rooms */
        {
            startPosY = doorPosY-2;
            startPosX = doorPosX;
            lineSize = startPosY + 2;
            drawLine(startPosY,startPosX,lineSize,2,'#',7,0); /* Call this function to draw the line */
            if (doorPosX < (roomStartPosX + (totalSizeX / 2))) /* when the door is towards left */
            {
                startPosY = doorPosY-2;
                startPosX = roomStartPosX-2;
                lineSize = startPosX + 2+ (doorPosX-roomStartPosX);
                drawLine(startPosY,startPosX,lineSize,1,'#',7,0);
                lineSize = startPosY + (HALLWAYSTARTY-startPosY);
                drawLine(startPosY,startPosX,lineSize,2,'#',7,0);

            }
            else /* when the door is towards right */
            {
                startPosY = doorPosY-2;
                startPosX = doorPosX;
                lineSize = doorPosX + 4 + ((roomStartPosX+totalSizeX) - doorPosX);
                drawLine(startPosY,startPosX,lineSize,1,'#',7,0);
                startPosX = lineSize-1;
                lineSize = startPosY + (HALLWAYSTARTY-startPosY);
                drawLine(startPosY,startPosX,lineSize,2,'#',7,0);

            }

        }
        else  /* For the bottom 3 rooms */
        {
            startPosY = doorPosY - 1;
            startPosX = doorPosX;
            lineSize = HALLWAYSTARTY + (doorPosY-HALLWAYSTARTY);
            drawLine(HALLWAYSTARTY,startPosX,lineSize,2,'#',7,0);
        }

    }
    else if (direction == 'e') /* Door at east */
    {
        if (roomStartPosY < HALLWAYSTARTY) /* For the top 3 rooms */
        {
            startPosY = doorPosY;
            startPosX = doorPosX+1;
            lineSize = startPosX + 2;
            drawLine(startPosY,startPosX,lineSize,1,'#',7,0);
            startPosX = doorPosX+2;
            lineSize = startPosY + (HALLWAYSTARTY-doorPosY);
            drawLine(startPosY,startPosX,lineSize,2,'#',7,0);

        }
        else  /* For the bottom 3 rooms */
        {
            startPosY = doorPosY;
            startPosX = doorPosX + 1;
            lineSize = startPosX + 2;
            drawLine(startPosY,startPosX,lineSize,1,'#',7,0);
            startPosX = doorPosX+2;
            lineSize = HALLWAYSTARTY + (doorPosY-HALLWAYSTARTY);
            drawLine(HALLWAYSTARTY,startPosX,lineSize,2,'#',7,0);

        }

    }
    else if (direction == 's') /* Door at south */
    {
        if (roomStartPosY < HALLWAYSTARTY) /* For the top 3 rooms */
        {
            startPosY = doorPosY + 1;
            startPosX = doorPosX;
            lineSize = startPosY + (HALLWAYSTARTY-doorPosY);
            drawLine(startPosY,startPosX,lineSize,2,'#',7,0);
        }
        else  /* For the bottom 3 rooms */
        {
            startPosY = doorPosY+1;
            startPosX = doorPosX;
            lineSize = startPosY + 2;
            drawLine(startPosY,startPosX,lineSize,2,'#',7,0);

            if (doorPosX < (roomStartPosX + (totalSizeX / 2))) /* when the door is towards left */
            {
                startPosY = doorPosY+2;
                startPosX = roomStartPosX-2;
                lineSize = startPosX + 2+ (doorPosX-roomStartPosX);
                drawLine(startPosY,startPosX,lineSize,1,'#',7,0);
                lineSize = HALLWAYSTARTY + (startPosY-HALLWAYSTARTY);
                drawLine(HALLWAYSTARTY,startPosX,lineSize,2,'#',7,0);
            }
            else /* when the door is towards right */
            {
                startPosY = doorPosY+2;
                startPosX = doorPosX;
                lineSize = doorPosX + 4 + ((roomStartPosX+totalSizeX) - doorPosX);
                drawLine(startPosY,startPosX,lineSize,1,'#',7,0);
                startPosX = lineSize-1;
                lineSize = HALLWAYSTARTY + (startPosY-HALLWAYSTARTY);
                drawLine(HALLWAYSTARTY,startPosX,lineSize,2,'#',7,0);

            }
        }
    }
    else if (direction == 'w') /* Door at west */
    {
        if (roomStartPosY < HALLWAYSTARTY) /* For the top 3 rooms */
        {
            startPosY = doorPosY;
            startPosX = doorPosX - 2;
            lineSize = startPosX + 2;
            drawLine(startPosY,startPosX,lineSize,1,'#',7,0);
            lineSize = startPosY + (HALLWAYSTARTY-doorPosY);
            drawLine(startPosY,startPosX,lineSize,2,'#',7,0);

        }
        else  /* For the bottom 3 rooms */
        {
            startPosY = doorPosY;
            startPosX = doorPosX - 2;
            lineSize = startPosX + 2;
            drawLine(startPosY,startPosX,lineSize,1,'#',7,0);
            lineSize = HALLWAYSTARTY + (doorPosY-HALLWAYSTARTY);
            drawLine(HALLWAYSTARTY,startPosX,lineSize,2,'#',7,0);

        }

    }

}

/* This function moves the hero and grabs items like gold etc.
   It takes the input entered by user (direction to move) i.e. userInput; Struct hero; Array of structs for room;
   And number of steps moved so far.
   It doesn't return anything.

*/
void moveHeroAndPlay(char userInput, Hero* hero, Room** room, int stepsMoved)
{
    int x = 0, y = 0, heroColor = 0, heroMoved = 0, tempY = 0, tempX = 0;
    Elements element = floorOrSteps;
    /* charAtLastPos is character at particular position before hero moved to that position,
       charAtNextPos is character at the next position where hero is going to be moved
    */
    char charAtLastPos = '.', charAtNextPos = ' ';
    y = tempY = hero->posY;
    x = tempX = hero->posX;
    if (stepsMoved == 0) /* If the hero is moving first time, then default charAtLastPos will be '.' */
    {
        charAtLastPos = '.';
    }
    else
    {
        charAtLastPos = hero->charAtLastPos;

    }
    heroColor = hero->color;
    hero->lastPosY = tempY;
    hero->lastPosX = tempX;

    switch (userInput)
    {

        case 'w': /* Top Move */

            {
                charAtNextPos = mvinch(--y,x); /* Get the character at next position */
                move(++y,x);
                if ((charAtNextPos != '-') && (charAtNextPos != '|') && (charAtNextPos != ' ') && (charAtNextPos != 'M') && (charAtNextPos != '_')) /* Check if it's a valid position */
                {
                    /* move hero */
                     hero->charAtLastPos =  charAtNextPos;
                     move(--y,x);
                     ++heroMoved;
                }

            }
            break;

        case 'a': /* Left Move */

            {
                charAtNextPos = mvinch(y,--x);
                move(y,++x);
                if ((charAtNextPos != '-') && (charAtNextPos != '|') && (charAtNextPos != ' ') && (charAtNextPos != 'M') && (charAtNextPos != '_'))
                {
                    hero->charAtLastPos =  charAtNextPos;
                    move(y,--x);
                    ++heroMoved;
                }

            }
            break;

        case 's': /* Down Move */
            {
                charAtNextPos = mvinch(++y,x);
                move(--y,x);
                if ((charAtNextPos != '-') && (charAtNextPos != '|') && (charAtNextPos != ' ') && (charAtNextPos != 'M') && (charAtNextPos != '_'))
                {
                    hero->charAtLastPos =  charAtNextPos;
                    move(++y,x);
                    ++heroMoved;
                }

            }

            break;

        case 'd':   /* Right Move */
            {
                charAtNextPos = mvinch(y,++x);
                move(y,--x);
                if ((charAtNextPos != '-') && (charAtNextPos != '|') && (charAtNextPos != ' ') && (charAtNextPos != 'M') && (charAtNextPos != '_'))
                {
                    hero->charAtLastPos =  charAtNextPos;
                    move(y,++x);
                    ++heroMoved;
                }

            }

            break;

    }
    if (heroMoved > 0) /* If hero moved */
    {
        hideMessage(); /* Call this function to hide top message */

        if ((charAtLastPos == '+')||(charAtLastPos == '%')||(charAtLastPos == '#')) /* If hero moved to a door or staircase (hallway) or stairwall */
        {
            if ((charAtLastPos == '+')||(charAtLastPos == '%'))
            {
                attron(COLOR_PAIR(7));
                attron(A_BOLD);
                mvaddch(tempY, tempX, charAtLastPos);
                attroff(A_BOLD);
                attroff(COLOR_PAIR(7));

            }
            else
            {
                mvaddch(tempY, tempX, charAtLastPos);

            }

        }
        else /* If hero moved to a floor or items */
        {
            mvaddch(tempY, tempX, '.');

        }

        hero->posY = y;
        hero->posX = x;
        attron(COLOR_PAIR(heroColor));
        attron(A_BOLD);
        mvaddch(y, x, hero->charHero);
        attroff(A_BOLD);
        attroff(COLOR_PAIR(heroColor));

        if ((charAtNextPos == '*')||(charAtNextPos == '!')||(charAtNextPos == ')')||(charAtNextPos == '$')) /* If hero moved to any items */
        {
            if (charAtNextPos == '*') /* Hero moved to Gold */
            {
               element = gold;
            }
            else if (charAtNextPos == '!') /* Hero moved to Potion */
            {
                element = potion;
            }
            else if (charAtNextPos == ')') /* Hero moved to Weapon */
            {
                element = weapon;
            }
            else if (charAtNextPos == '$') /* Hero moved to Magic */
            {
                element = magic;
            }
            /* Call this function to store the item in hero's inventory i.e. hero moved to item so he picked up the item and display
            top message */
            storeStatsAndDisplayMessage(element, hero, room);

        }

    }

    refresh();
}

/* This function stores the picked up item in hero struct and calls displayMessage function to display
   the top message.
   It takes element enum to identify which item has been picked up; Hero struct to store the picked up item in it;
   Array of structs room.
   It doesn't return any values.

*/
void storeStatsAndDisplayMessage(Elements element, Hero* hero, Room** room)
{
    char* messageToDisplay;
    char* tempString;
    char* elementPotion;
    char* elementMagic;
    char* elementWeapon;
    int elementNumber = 0;
    int goldPieces = 0, selectedPotion = 0, selectedWeapon = 0, selectedMagic = 0;

    messageToDisplay = malloc(sizeof(char)*75);
    tempString = malloc(sizeof(char)*50);

    if (messageToDisplay == NULL)
    {
        displayMessage(1,"Error while allocating memory",0);
        getch();
        exit(1);
    }
    if (tempString == NULL)
    {
        displayMessage(1,"Error while allocating memory",0);
        getch();
        exit(1);
    }

    elementPotion = malloc(sizeof(char)*60);
    elementMagic = malloc(sizeof(char)*60);
    elementWeapon = malloc(sizeof(char)*60);
    if ((elementPotion == NULL)||(elementMagic == NULL)||( elementWeapon == NULL))
    {
        displayMessage(1,"Error while allocating memory",0);
        getch();
        exit(1);

    }

    /* Random number to get particular items */
    goldPieces = (rand()%100)+1;
    selectedPotion = (rand()%8);
    selectedWeapon = (rand()%8);
    selectedMagic = (rand()%8);

    strcpy(messageToDisplay, "");
    strcpy(tempString, "");


    switch (element)
    {
        case floorOrSteps:
        {
           break;
        }
        case gold:
        {
           strcat(messageToDisplay, "You found ");
           sprintf(tempString, "%d", goldPieces);
           strcat(messageToDisplay,tempString);
           strcat(messageToDisplay, " Gold Pieces. ");
           /* store in hero struct */
           hero->gold = hero->gold+1;
           hero->goldPoints = hero->goldPoints + goldPieces;
           elementNumber =1;

           break;
        }
        case potion:
        {

           strcat(messageToDisplay, "You got Potion of ");
           /* Call this function to get the potion name based on random number passed */
           getPotion(selectedPotion, &elementPotion);
           strcpy(tempString,elementPotion);
           strcat(messageToDisplay,tempString);
           strcat(messageToDisplay,".");

           hero->collectedPotion[hero->potion] = selectedPotion;
           hero->potion = hero->potion + 1;
           elementNumber= 2;
           break;
        }
        case weapon:
        {
           strcat(messageToDisplay, "Congratulation! new ");
            /* Call this function to get the weapon name based on random number passed */
           getWeapon(selectedWeapon, &elementWeapon);
           strcpy(tempString,elementWeapon);
           strcat(messageToDisplay,tempString);
           strcat(messageToDisplay," added to your arsenal.");

           hero->collectedWeapon[hero->weapon] = selectedWeapon;
           hero->weapon = hero->weapon + 1;
           elementNumber = 3;
           break;
        }
        case magic:
        {
           strcat(messageToDisplay, "You found Magic ");
            /* Call this function to get the magic name based on random number passed */
           getMagic(selectedMagic, &elementMagic);
           strcpy(tempString,elementMagic);
           strcat(messageToDisplay,tempString);
           strcat(messageToDisplay,".");

           hero->collectedMagic[hero->magic] = selectedMagic;
           hero->magic = hero->magic + 1;
           elementNumber = 4;
           break;
        }

    }
    /* Call this function to display the message in message space at the top */
    displayMessage(0, messageToDisplay, elementNumber);
    /* Update and display the side inventory list */
    displayItemsCollected(hero, room);

    free(messageToDisplay);
    messageToDisplay =NULL;
    free(tempString);
    tempString = NULL;
    free(elementPotion);
    elementPotion = NULL;
    free(elementWeapon);
    elementWeapon =  NULL;
    free(elementMagic);
    elementMagic = NULL;
}

/* This function displays the collected items and total items present in the board, at the bottom bar.
   It takes struct hero and array of structs room as inputs.
   It doesn't return anything.
*/
void displayItemsCollected(Hero* hero, Room** room)
{

    int totalGoldItems = 0, totalPotionItems = 0, totalWeaponItems = 0, totalMagicItems = 0, i = 0;

    /* Calculate the total items present in each room */
    for (i= 0; i<6; i++)
    {
        totalGoldItems += room[i]->totalGold;
        totalPotionItems += room[i]->totalPotion;
        totalWeaponItems += room[i]->totalWeapon;
        totalMagicItems += room[i]->totalMagic;

    }

    mvprintw(59,16,"            ");
    mvprintw(59,40,"        ");
    mvprintw(59,61,"        ");
    mvprintw(59,80,"        ");

    attron(A_BOLD);
    attron(COLOR_PAIR(7));
    /* Display Gold */
     mvprintw(59,16,"%03d",hero->goldPoints);
     mvprintw(59,20,"(");
     mvprintw(59,21,"%02d",hero->gold);
     mvprintw(59,23,"/");
     mvprintw(59,24,"%02d",totalGoldItems);
     mvprintw(59,26,")");

    /* Display Weapon */
     mvprintw(59,40,"(");
     mvprintw(59,41,"%02d",hero->weapon);
     mvprintw(59,43,"/");
     mvprintw(59,44,"%02d",totalWeaponItems);
     mvprintw(59,46,")");

    /* Display Potion */
     mvprintw(59,61,"(");
     mvprintw(59,62,"%02d",hero->potion);
     mvprintw(59,64,"/");
     mvprintw(59,65,"%02d",totalPotionItems);
     mvprintw(59,67,")");

    /* Display Magic */
     mvprintw(59,81,"(");
     mvprintw(59,82,"%02d",hero->magic);
     mvprintw(59,84,"/");
     mvprintw(59,85,"%02d",totalMagicItems);
     mvprintw(59,87,")");

    attroff(COLOR_PAIR(7));
    attroff(A_BOLD);
    refresh();

}

/* This function gets the potion name based on number passed.
   It takes a number i.e. selectedPotion and based on the number, it returns a potion name.
   Potion name gets stored in string potion (address of the string is passed).
   It doesn't return anything.

*/
void getPotion(int selectedPotion, char** potion)
{
    char** potions;
    int i = 0, totalItems = 10;

    potions = malloc(sizeof(char*)*totalItems);

    if ((potions == NULL))
    {
        displayMessage(1,"Error while allocating memory",0);
        getch();
        exit(1);

    }
    for (i=0;i<totalItems;i++)
    {
        potions[i] = malloc(sizeof(char)*60);

    }
    i = 0;
    /* Potions name */
    strcpy(potions[i++],"Strength");
    strcpy(potions[i++],"Poison");
    strcpy(potions[i++],"Magic Detection");
    strcpy(potions[i++],"Confusion");
    strcpy(potions[i++],"Haste");
    strcpy(potions[i++],"Healing");
    strcpy(potions[i++],"Extra Healing");
    strcpy(potions[i++],"See Invisible");
    strcpy(potions[i++],"Restore Strength");

    /* Copy the potion corresponds to selectedPotion in string potion */
    strcpy(*potion,potions[selectedPotion]);

    for (i=0;i<totalItems;i++)
    {
      free(potions[i]);
      potions[i] = NULL;

    }
    free(potions);

}

/* This function gets the weapon name based on number passed.
   It takes a number i.e. selectedWeapon and based on the number, it returns a weapon name.
   Weapon name gets stored in string weapon (address of the string is passed).
   It doesn't return anything.

*/
void getWeapon(int selectedWeapon, char** weapon)
{
    char** weapons;
    int i = 0, totalItems = 10;

    weapons = malloc(sizeof(char*)*totalItems);

    if ((weapons == NULL))
    {
        displayMessage(1,"Error while allocating memory",0);
        getch();
        exit(1);

    }
    for (i=0;i<totalItems;i++)
    {
        weapons[i] = malloc(sizeof(char)*60);

    }

    i = 0;
    /* Weapons name */
    strcpy(weapons[i++],"Mace");
    strcpy(weapons[i++],"Dagger");
    strcpy(weapons[i++],"Spear");
    strcpy(weapons[i++],"Longsword");
    strcpy(weapons[i++],"Two-handed Sword");
    strcpy(weapons[i++],"Crossbow");
    strcpy(weapons[i++],"Bow");
    strcpy(weapons[i++],"Dart");
    strcpy(weapons[i++],"Ammo");

    /* Copy the weapon corresponds to selectedWeapon in string weapon */
    strcpy(*weapon,weapons[selectedWeapon]);


    for (i=0;i<totalItems;i++)
    {
      free(weapons[i]);
      weapons[i] = NULL;

    }

    free(weapons);

}

/* This function gets the magic name based on number passed.
   It takes a number i.e. selectedMagic and based on the number, it returns a magic name.
   Magic name gets stored in string magic (address of the string is passed).
   It doesn't return anything.

*/
void getMagic(int selectedMagic, char** magic)
{

    char** magics;
    int i = 0, totalItems = 10;

    magics = malloc(sizeof(char*)*totalItems);


    if ((magics == NULL))
    {
        displayMessage(1,"Error while allocating memory",0);
        getch();
        exit(1);

    }
    for (i=0;i<totalItems;i++)
    {

        magics[i] = malloc(sizeof(char)*60);

    }

    i= 0;
    /* Magic name */
    strcpy(magics[i++],"Wand of Flame");
    strcpy(magics[i++],"Wand of Lightning");
    strcpy(magics[i++],"Wand of Light");
    strcpy(magics[i++],"Ring of Protection");
    strcpy(magics[i++],"Ring of Teleportation");
    strcpy(magics[i++],"Wand of Magic Missile");
    strcpy(magics[i++],"Scroll of Magic Mapping");
    strcpy(magics[i++],"Scroll of Bless Weapon");
    strcpy(magics[i++],"Scroll of Freeze Monster");

    /* Copy the magic corresponds to selectedMagic in string magic */
    strcpy(*magic,magics[selectedMagic]);

    for (i=0;i<totalItems;i++)
    {

      free(magics[i]);
      magics[i] = NULL;

    }

    free(magics);


}

/* This function displays the side inventory information. It displays gold collected, total gold, total value,
   magic collected, total magic, collected magic name and quantity, weapon collected, total weapon, collected
   weapon name and quantity, potion collected, total potion, collected potion name and quantity.
   It takes an integer hideOrShow to toggle the display of inventory i.e. 1 means show and 0 means hide,
   Struct hero and array of structs room.
   It doesn't return anything.

*/
void displayInventoryInformation(int hideOrShow, Hero* hero, Room** room)
{
    int totalGoldItems = 0, totalPotionItems = 0, totalWeaponItems = 0, totalMagicItems = 0, i = 0;
    int counter = 0, temp = 0,count = 0, position = 0, j = 0;
    int flagOfItems[99];
    char* element;

    element = malloc(sizeof(char)*60);
    if (element == NULL)
    {
        displayMessage(1,"Error while allocating memory",0);
        getch();
        exit(1);

    }

    /* Calculate total items */
    for (i= 0; i<6; i++)
    {
        totalGoldItems += room[i]->totalGold;
        totalPotionItems += room[i]->totalPotion;
        totalWeaponItems += room[i]->totalWeapon;
        totalMagicItems += room[i]->totalMagic;

    }

     /* Hide everything */
     drawLine(1,GAMESPACEX,GAMESPACEX+40,1,' ',7,1);
     drawLine(GAMESPACEY-1,GAMESPACEX,GAMESPACEX+40,1,' ',7,1);
     drawLine(1+1,GAMESPACEX+39,GAMESPACEY-1,2,' ',7,1);
     for (i= 0; i< GAMESPACEY-1;i++)
     {
        for (j = GAMESPACEX; j<GAMESPACEX+39; j++)
        {
            mvaddch(i,j,' ');

        }
     }


    if (hideOrShow == 1) /* Display the inventory list if hideOrShow is 1 */
    {
         drawLine(1,GAMESPACEX,GAMESPACEX+40,1,'-',7,1);
         drawLine(GAMESPACEY-1,GAMESPACEX,GAMESPACEX+40,1,'-',7,1);
         drawLine(1+1,GAMESPACEX+39,GAMESPACEY-1,2,'|',7,1);

         attron(A_BOLD);

         attron(COLOR_PAIR(4));
         mvprintw(5,GAMESPACEX+1,"*");
         /* Display information related to Gold */
         mvprintw(5,GAMESPACEX+9,"%03d",hero->goldPoints);
         mvprintw(7,GAMESPACEX+2,"%02d",hero->gold);
         mvprintw(7,GAMESPACEX+5,"/");
         mvprintw(7,GAMESPACEX+7,"%02d",totalGoldItems);

         attroff(COLOR_PAIR(4));
         attron(COLOR_PAIR(7));
         mvprintw(5,GAMESPACEX+3,"Gold: ");
         attroff(COLOR_PAIR(7));

         /* Display information related to Weapon */
         attron(COLOR_PAIR(3));
         mvprintw(11,GAMESPACEX+1,")");

         mvprintw(13,GAMESPACEX+2,"%02d",hero->weapon);
         mvprintw(13,GAMESPACEX+5,"/");
         mvprintw(13,GAMESPACEX+7,"%02d",totalWeaponItems);

         attroff(COLOR_PAIR(3));
         attron(COLOR_PAIR(7));
         mvprintw(11,GAMESPACEX+3,"Weapon: ");
         attroff(COLOR_PAIR(7));
         strcpy(element,"");


         for (i=0; i<hero->weapon; i++)
         {
             temp = hero->collectedWeapon[i]; /* For each collected weapon */
             flagOfItems[i] = 0;
             while (counter <= i)
             {
                 if (temp == hero->collectedWeapon[counter])
                 {
                     count++;
                     if (count < 2)
                     {
                         flagOfItems[i] = 1; /* Flag the non-repeating weapon as 1*/
                     }
                     else
                     {
                        flagOfItems[i] = 2;
                     }
                 }

                 counter++;
             }
             counter = 0;
             count = 0;
             while (counter < hero->weapon) /* Get the count of weapon of each type */
             {
                 if (temp == hero->collectedWeapon[counter])
                 {
                     count++;
                 }
                 counter++;
             }
             if (flagOfItems[i] <= 1) /* Display only non-repeating weapon and its count */
             {
                 attron(COLOR_PAIR(3));
                 mvprintw(15+position,GAMESPACEX+2,"%d",count);
                 attroff(COLOR_PAIR(3));

                 getWeapon(temp, &element);
                 mvprintw(15+position,GAMESPACEX+5,"%s",element);
                 position++;

             }
             strcpy(element,"");
             counter = 0;
             count = 0;

         }
         /* Display information related to Potion */
         attron(COLOR_PAIR(1));
         mvprintw(26,GAMESPACEX+1,"!");

         mvprintw(28,GAMESPACEX+2,"%02d",hero->potion);
         mvprintw(28,GAMESPACEX+5,"/");
         mvprintw(28,GAMESPACEX+7,"%02d",totalPotionItems);

         attroff(COLOR_PAIR(1));


         attron(COLOR_PAIR(7));
         mvprintw(26,GAMESPACEX+3,"Potion: ");
         attroff(COLOR_PAIR(7));
         strcpy(element,"");
         counter = 0;
         count = 0;
         position = 0;
         for (i=0; i<hero->potion; i++)
         {
             temp = hero->collectedPotion[i];
             flagOfItems[i] = 0;
             while (counter <= i)
             {
                 if (temp == hero->collectedPotion[counter])
                 {
                     count++;
                     if (count < 2)
                     {
                         flagOfItems[i] = 1;
                     }
                     else
                     {
                        flagOfItems[i] = 2;
                     }
                 }

                 counter++;
             }
             counter = 0;
             count = 0;
             while (counter < hero->potion)
             {
                 if (temp == hero->collectedPotion[counter])
                 {
                     count++;
                 }
                 counter++;
             }
             if (flagOfItems[i] <= 1)
             {
                 attron(COLOR_PAIR(1));
                 mvprintw(30+position,GAMESPACEX+2,"%d",count);
                 attroff(COLOR_PAIR(1));

                 getPotion(temp, &element);
                 mvprintw(30+position,GAMESPACEX+5,"%s",element);
                 position++;

             }
             strcpy(element,"");
             counter = 0;
             count = 0;

         }

         /* Display information related to Magic */
         attron(COLOR_PAIR(6));
         mvprintw(42,GAMESPACEX+1,"$");
         mvprintw(44,GAMESPACEX+2,"%02d",hero->magic);
         mvprintw(44,GAMESPACEX+5,"/");
         mvprintw(44,GAMESPACEX+7,"%02d",totalMagicItems);

         attroff(COLOR_PAIR(6));
         attron(COLOR_PAIR(7));
         mvprintw(42,GAMESPACEX+3,"Magic: ");
         attroff(COLOR_PAIR(7));
         strcpy(element,"");
         counter = 0;
         count = 0;
         position = 0;
         for (i=0; i<hero->magic; i++)
         {
             temp = hero->collectedMagic[i];
             flagOfItems[i] = 0;
             while (counter <= i)
             {
                 if (temp == hero->collectedMagic[counter])
                 {
                     count++;
                     if (count < 2)
                     {
                         flagOfItems[i] = 1;
                     }
                     else
                     {
                        flagOfItems[i] = 2;
                     }
                 }

                 counter++;
             }
             counter = 0;
             count = 0;
             while (counter < hero->magic)
             {
                 if (temp == hero->collectedMagic[counter])
                 {
                     count++;
                 }
                 counter++;
             }
             if (flagOfItems[i] <= 1)
             {
                 attron(COLOR_PAIR(6));
                 mvprintw(46+position,GAMESPACEX+2,"%d",count);
                 attroff(COLOR_PAIR(6));

                 getMagic(temp, &element);
                 mvprintw(46+position,GAMESPACEX+5,"%s",element);
                 position++;

             }
             strcpy(element,"");
             counter = 0;
             count = 0;

         }

         attroff(A_BOLD);


    }
    free(element);
    element = NULL;


}

