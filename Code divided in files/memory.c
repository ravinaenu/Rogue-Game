#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

#include "rogue.h"
#include "memory.h"
#include "draw.h"

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




