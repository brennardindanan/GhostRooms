#include "defs.h"

/* 
  Function: initGhostList
  Purpose: Initializes a GhostListType by initializing head, tail, and count to NULL/zero
  Params:   
		In: GhostListType *list - Pointer to specified GhostListType to be initialized
*/
void initGhostList(GhostListType *list) {
    list->head = NULL;
    list->tail = NULL; 
    list->count = 0; 
}

/* 
  Function: initGhost
  Purpose: Initializes a GhostType through memory allocation and initializing properties
  Params:   
		In:
			id - identification number for ghost
			gt - ghost type
			*r - pointer to respective ghost's room
			like - likelihood of a ghost
		Out:
			**ghost - pointer to pointer that stores allocated GhostType
*/
void initGhost(int id, GhostEnumType gt, RoomType *r, float like, GhostType **ghost) {
    *ghost = (GhostType *)malloc(sizeof(GhostType));
    
    if (*ghost == NULL) {
		printf("Memory allocation error\n");
        exit(0);
    }

    (*ghost)->id = id;
    (*ghost)->ghostType = gt;
    (*ghost)->room = r;
    (*ghost)->likelihood = like;
}

/* 
  Function: addGhost
  Purpose: Creates new node, updates list pointers, adds GhostType to GhostListType
  Params:   
		In:
			*list - pointer to GhostListType where GhostType will be added
			*ghost - pointer to GhostType to be added
*/
void addGhost(GhostListType *list, GhostType *ghost) {
    NodeType *newNode = (NodeType *)malloc(sizeof(NodeType));
    if (newNode == NULL) {
        printf("Memory allocation error\n");
        exit(0);
    }

    newNode->ghost = ghost;
    newNode->next = NULL;

    if (list->head == NULL) { //if list empty
        list->head = newNode;
        list->tail = newNode;
    } else { //if list not empty
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->count++;
}

/* 
  Function: cleanupGhostData
  Purpose: Deallocates memory for ghosts' DATA only
  Params:   
		In:
			*list - pointer to GhostListType containing to be cleaned GhostData
*/
void cleanupGhostData(GhostListType *list) {
    NodeType *current = list->head;

    while (current != NULL) {
        NodeType *next = current->next;
        free(current->ghost);
        current->ghost = NULL;
        current = next;
    }
}

/* 
  Function: cleanupGhostList
  Purpose: Deallocates memory of GhostListType nodes ONLY
  Params:   
		In:
			*list - pointer to respective GhostListType where nodes are cleaned
*/
void cleanupGhostList(GhostListType *list) {
    NodeType *currentNode = list->head;

    while (currentNode != NULL) {
        NodeType *next = currentNode->next;
        free(currentNode);
        currentNode = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
}

/* 
  Function: printGhost
  Purpose: Prints all elements of GhostType (defined in defs.h) like id, type, room, likelihood.
  Params:   
		In:
			*ghost - pointer to respective GhostType's info
*/
void printGhost(const GhostType *ghost) {
    printf("ID:   %d | Type:    ", ghost->id);

    if (ghost->ghostType == POLTERGEIST) {
        printf("%12s", "Poltergeist ");
    } else if (ghost->ghostType == WRAITH) {
        printf("%12s", "Wraith ");
    } else if (ghost->ghostType == PHANTOM) {
        printf("%12s", "Phantom ");
    } else if (ghost->ghostType == BULLIES) {
        printf("%12s", "Bullies ");
    } else {
        printf("%12s", "Other ");
    }

    if (ghost->room != NULL) {
        printf("| Room: %-14s", ghost->room->name);
    } else {
        printf("| Room: %-14s", "Unknown");
    }

    printf("   | Likelihood: %.2f\n", ghost->likelihood);
}

/* 
  Function: printGhostList
  Purpose: Prints all ghosts in a GhostListType and their information
  Params:   
		In:
			*list - pointer to GhostListType where all ghosts will be printed
*/
void printGhostList(const GhostListType *list) {
    NodeType *current = list->head;

    while (current != NULL) {
        printGhost(current->ghost);
        current = current->next;
    }
}

/* 
  Function: addGhostByLikelihood
  Purpose: Adds ghosts to a GhostListType in descending order of likelihood
  Params:   
		In:
			*list - pointer to GhostListType where ghosts will be "re"added based on likelihood
			*ghost - pointer of ghost to be added
*/
void addGhostByLikelihood(GhostListType *list, GhostType *ghost) {
    NodeType *newNode = (NodeType *)malloc(sizeof(NodeType));
    if (newNode == NULL) {
        printf("Memory allocation error\n");
        exit(0);
    }

    newNode->ghost = ghost;
    newNode->next = NULL;
	
	if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        list->count++;
        return;
    }
	
    if (list->head == NULL || ghost->likelihood >= list->head->ghost->likelihood) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        NodeType *current = list->head;
        NodeType *previous = NULL;

        while (current != NULL && ghost->likelihood < current->ghost->likelihood) {
            previous = current;
            current = current->next;
        }

        newNode->next = current;
        previous->next = newNode;
    }

    if (list->tail == NULL || ghost->likelihood <= list->tail->ghost->likelihood) {
        list->tail = newNode;
    }

    list->count++;
}

/* 
  Function: printByLikelihood
  Purpose: Prints ghosts from GhostListType based on descending order of likelihood
  Params:   
		In:
			*origList - pointer to original GhostTypeList (not based on likelihood)
			endsOnly - Indicates whether to print all ghosts based on likelihood or just most likely and least likely ghosts
*/
void printByLikelihood(const GhostListType *origList, int endsOnly) {
    GhostListType tempList;
    initGhostList(&tempList);

    NodeType *current = origList->head;

    while (current != NULL) {
        addGhostByLikelihood(&tempList, current->ghost);
        current = current->next;
    }

    if (endsOnly == C_TRUE) {
        if (tempList.head != NULL) {
            printf("Most likely ghost:\n");
            printGhost(tempList.head->ghost);
        }

        if (tempList.tail != NULL && tempList.head != tempList.tail) {
            printf("Least likely ghost:\n");
            printGhost(tempList.tail->ghost);
        }
    } else {
        printGhostList(&tempList);
    }

    cleanupGhostList(&tempList);
}
