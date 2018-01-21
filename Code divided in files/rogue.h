
#ifndef _RAVINA_ROGUEH
#define _RAVINA_ROGUEH


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


#endif
