#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "models.h"

// Prototypes for functions defined in other files
void voter_panel();
void admin_panel();
void load_data();
void save_data();

int main() {
    int choice;
    int c;
    load_data(); // Load existing votes/candidates on startup

    while (1) {
        printf("\n--- ELECTION RESULT PROCESSING SYSTEM ---");
        printf("\n1. Voter Panel\n2. Admin Panel\n3. Exit\nSelect: ");
        if (scanf("%d", &choice) != 1) break;
            // Clear leftover newline from previous input
    while ((c = getchar()) != '\n' && c != EOF) {
        ;
    }

        switch (choice) {
            case 1: voter_panel(); break;
            case 2: admin_panel(); break;
            case 3: 
                save_data(); 
                printf("Data saved. Exiting...\n");
                exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}