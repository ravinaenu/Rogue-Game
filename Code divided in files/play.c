#include <curses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "rogue.h"
#include "play.h"
#include "draw.h"



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

