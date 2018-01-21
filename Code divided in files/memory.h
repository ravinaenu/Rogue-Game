
#ifndef _RAVINA_MEMORYH
#define _RAVINA_MEMORYH


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

#endif