#include "defs.h"

/* 
  Function: 
  Purpose: 
  Params:   
		In:
		Out:
		In/Out:
	Return:
*/

/* 
  Function: initRoom
  Purpose: Initializes RoomType by memory allocation and setting elements to passed values
  Params:   
		In:
			id - room identification
			*name - room name
			**room - pointer to a pointer of a RoomType that will be set to allocated RoomType
*/
void initRoom(int id, char *name, RoomType **room) {
    *room = (RoomType *)malloc(sizeof(RoomType));

    if (*room == NULL) {
        printf("Memory allocation error\n");
        exit(0);
    }

    (*room)->id = id;
    strncpy((*room)->name, name, MAX_STR - 1);
    (*room)->name[MAX_STR - 1] = '\0'; //null termination

    initGhostList(&((*room)->ghosts));
}

/* 
  Function: initRoomArray
  Purpose: Initializes RoomArrayType by setting initial size to 0
  Params:   
		In:
			*arr - pointer to RoomArrayType to be initialized
*/
void initRoomArray(RoomArrayType *arr) {
	arr->size = 0;
}

/* 
  Function: addRoom
  Purpose: Adds RoomType pointer to RoomArrayType
  Params:   
		In:
			*arr - pointer to RoomArrayType where RoomType will be added
			*r - pointer to RoomType to be added
*/
void addRoom(RoomArrayType *arr, RoomType *r) {
    if (arr->size < MAX_ARR) {
        arr->elements[arr->size] = r;
        arr->size++;
    } else {
        printf("Error: Room limit reached.\n");
    }
}

/* 
  Function: cleanupRoomArray
  Purpose: Frees up memory of RoomArrayType
  Params:   
		In:
			*arr - pointer to a RoomArrayType to be cleaned
*/
void cleanupRoomArray(RoomArrayType *arr) {
    for (int i = 0; i < arr->size; i++) {
        RoomType *currentRoom = arr->elements[i];
        cleanupGhostList(&(currentRoom->ghosts));
        free(currentRoom);
        arr->elements[i] = NULL;
    }

    arr->size = 0;
}

/* 
  Function: printRooms
  Purpose: Prints the info about all the rooms' in a respective RoomArrayType
  Params:   
		In:
			*arr - pointer to a (constant) RoomArrayType
*/
void printRooms(const RoomArrayType *arr) {
    for (int i = 0; i < arr->size; i++) {
        RoomType *currentRoom = arr->elements[i];
        printRoom(currentRoom);
    }
}

/* 
  Function: printRoom
  Purpose: Prints all the information about a single room (id, name, ghost data)
  Params:   
		In:
			*room - pointer to (constant) RoomType in which the info will be printed
*/
void printRoom(const RoomType *room) { //my helper function
    printf("Room %d: %s\n", room->id, room->name);
    printf("--------------\n");

    if (room->ghosts.head == NULL) {
        printf("No ghosts in this room\n");
    } else {
        printGhostList(&(room->ghosts));
    }

    printf("--------------\n\n");
}

