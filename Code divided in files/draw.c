#include <curses.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "rogue.h"
#include "draw.h"
#include "play.h"


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