#include <stdio.h>
#include <string.h>
#include "models.h"

// Accessing global data defined in file_io.c
extern Candidate candidates[];
extern int candidateCount;
extern char votedUsers[MAX_VOTERS][20];
extern int votedCount;

// Function prototypes to link with auth.c and ui.c
int authenticate_admin();
void display_visual_results();


void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void add_candidate() {
    if (candidateCount >= MAX_CANDIDATES) {
        printf("\n[!] Error: Maximum candidate limit (%d) reached.\n", MAX_CANDIDATES);
        return;
    }

    printf("\nEnter Candidate Name: ");
    // %49[^\n] reads up to 49 chars including spaces
    if (scanf(" %49[^\n]", candidates[candidateCount].name) == 1) {
        candidates[candidateCount].id = candidateCount + 1;
        candidates[candidateCount].voteCount = 0;
        
        candidateCount++;
        printf("[+] Candidate '%s' added successfully with ID: %d\n", 
               candidates[candidateCount-1].name, candidates[candidateCount-1].id);
        
        clear_input_buffer(); // Clean up after the name input
    } else {
        printf("[!] Error: Invalid name input.\n");
        clear_input_buffer();
    }
}

void view_voter_logs() {
    printf("\n--- AUDIT LOG (Total Participation: %d) ---\n", votedCount);
    if (votedCount == 0) {
        printf("No votes have been recorded in the system yet.\n");
    } else {
        for (int i = 0; i < votedCount; i++) {
            printf("[%d] Voter ID Reference: %s\n", i + 1, votedUsers[i]);
        }
    }
    printf("------------------------------------------\n");
}

void admin_panel() {
    // Requires password defined in auth.c
    if (!authenticate_admin()) return;

    int choice;
    while (1) {
        printf("\n--- ADMIN CONTROL PANEL ---");
        printf("\n1. Add New Candidate");
        printf("\n2. View Live Results Dashboard");
        printf("\n3. View Voter Audit Logs");
        printf("\n4. Return to Main Menu");
        printf("\nSelect Option: ");

        if (scanf("%d", &choice) != 1) {
            printf("[!] Invalid input. Please enter a number.\n");
            clear_input_buffer(); // Prevent infinite loops on bad input
            continue;
        }

        switch (choice) {
            case 1: 
                add_candidate(); 
                break;
            case 2: 
                display_visual_results(); 
                break;
            case 3: 
                view_voter_logs(); 
                break;
            case 4: 
                return; 
            default: 
                printf("[!] Invalid option.\n");
        }
    }
}