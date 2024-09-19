#include "defs.h"

int main() {
	BuildingType building;
    initBuilding(&building);
	loadBuildingData(&building);
	int choice;
	
	while (C_TRUE) {
        printMenu(&choice);

        if (choice == 1) {
            printRooms(&building.rooms);
        } else if (choice == 2) {
            printGhostList(&building.ghosts);
        } else if (choice == 3) {
            printByLikelihood(&building.ghosts, C_FALSE);
        } else if (choice == 4) {
            printByLikelihood(&building.ghosts, C_TRUE);
        } else if (choice == 0) {
        	printf("Exiting...\n");
            break;
        } else {
            printf("Error: Invalid Selection. Please try again.\n");
        }
    }

    cleanupBuilding(&building);

    return 0;
}


void printMenu(int *choice)
{
  printf("\nMAIN MENU\n");
  printf("  (1) Print rooms\n");
  printf("  (2) Print ghosts\n");
  printf("  (3) Print ghosts by likelihood\n");
  printf("  (4) Print most/least likely ghosts\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  scanf("%2d", choice);
  while (getchar() != '\n');
}

