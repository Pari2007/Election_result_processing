#include <stdio.h>
#include "models.h"

// Access global data from other files
extern Candidate candidates[];
extern int candidateCount;

/**
 * Renders a visual representation of the election results.
 * Includes a percentage-based bar chart and identifies the current leader.
 */
void display_visual_results() {
    if (candidateCount == 0) {
        printf("\n[!] No candidates registered. Please add candidates in the Admin Panel first.\n");
        return;
    }

    int totalVotes = 0;
    int leaderIndex = 0;
    int tieFound = 0;

    // Calculate total votes and find the current leader
    for (int i = 0; i < candidateCount; i++) {
        totalVotes += candidates[i].voteCount;
        if (i > 0 && candidates[i].voteCount > candidates[leaderIndex].voteCount) {
            leaderIndex = i;
            tieFound = 0;
        } else if (i > 0 && candidates[i].voteCount == candidates[leaderIndex].voteCount && candidates[i].voteCount > 0) {
            tieFound = 1;
        }
    }

    printf("\n==================================================");
    printf("\n           LIVE ELECTION DASHBOARD               ");
    printf("\n==================================================\n");
    printf("%-15s   %-20s   %s\n", "CANDIDATE", "VOTE SHARE", "STATS");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < candidateCount; i++) {
        float percent = (totalVotes == 0) ? 0 : ((float)candidates[i].voteCount / totalVotes) * 100;
        
        // Print Candidate Name
        printf("%-15s [", candidates[i].name);
        
        // 1. Logic for the Progress Bar (20 characters total)
        int barLength = (int)(percent / 5); // Each 5% corresponds to 1 character in the bar
        for (int j = 0; j < 20; j++) {
            if (j < barLength) {
                printf("#"); // Filled portion
            } else {
                printf("-"); // Empty portion
            }
        }
        
        // 2. Print Percent and raw Vote Count
        printf("] %.1f%% (%d)\n", percent, candidates[i].voteCount);
    }

    printf("--------------------------------------------------\n");
    printf("TOTAL VOTES CAST: %d\n", totalVotes);
    
// 3. Leader Announcement Logic
    if (totalVotes > 0) {
        if (tieFound) {
            printf("\n>>> STATUS: COMPETITIVE TIE FOR FIRST PLACE <<<\n");
        } else {
            printf("\n>>> CURRENT LEADER: %s <<<\n", candidates[leaderIndex].name);
        }
    } else {
        // If totalVotes is 0, we don't need to worry about the leaderIndex or tieFound
        printf("\n>>> STATUS: AWAITING FIRST BALLOT <<<\n");
    }
    printf("==================================================\n");
}