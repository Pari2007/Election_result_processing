#include <stdio.h>
#include <string.h>
#include "models.h"

// Accessing global data defined in file_io.c
extern Candidate candidates[];
extern int candidateCount;
extern char votedUsers[MAX_VOTERS][20];
extern int votedCount;

/**
 * Checks if a Voter ID has already been used in this election.
 */
int has_already_voted(char *id) {
    for (int i = 0; i < votedCount; i++) {
        if (strcmp(votedUsers[i], id) == 0) return 1;
    }
    return 0;
}

/**
 * The user-facing voting interface.
 */
void voter_panel() {
    char id[20];
    int choice;

    printf("\n--- VOTING BOOTH ---");
    printf("\nEnter your Voter ID: ");
    scanf("%19s", id);

    // 1. Eligibility Check
    if (has_already_voted(id)) {
        printf("[!] Error: This ID has already cast a vote!\n");
        return;
    }

    // 2. Election State Check
    if (candidateCount == 0) {
        printf("[!] Error: No candidates are currently registered.\n");
        return;
    }

    // 3. Display Candidates
    printf("\nAvailable Candidates:\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("%d. %s\n", candidates[i].id, candidates[i].name);
    }

    printf("Enter Candidate ID to vote: ");
    if (scanf("%d", &choice) != 1) {
        printf("[!] Invalid numeric input.\n");
        // Clear buffer
        while (getchar() != '\n'); 
        return;
    }

    // 4. Vote Processing
    int found = 0;
    for (int i = 0; i < candidateCount; i++) {
        if (candidates[i].id == choice) {
            candidates[i].voteCount++;
            
            // Record the voter to prevent double-voting
            strncpy(votedUsers[votedCount++], id, 19); 
            
            printf("\n[SUCCESS] Vote cast for %s!\n", candidates[i].name);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("[!] Invalid Candidate ID! Please try again.\n");
    }
}