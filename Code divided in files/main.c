#include <curses.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "rogue.h"
#include "memory.h"
#include "draw.h"
#include "play.h"


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