#include <stdio.h>
#include <string.h>
#include "models.h"

// This is where the memory is actually allocated for our global data structures
Candidate candidates[MAX_CANDIDATES];
int candidateCount = 0;
char votedUsers[MAX_VOTERS][20];
int votedCount = 0;

char KEY = 'X';

void encrypt_decrypt(char *data) {
    int len = strlen(data); 
    for (int i = 0; i < len; i++) {
        data[i] ^= KEY;
    }
}

void save_data() {
    FILE *fp = fopen("data/election_data.dat", "wb");
    if (fp == NULL) {
        printf("[!] Error: Could not save data. Ensure 'data' folder exists.\n");
        return;
    }

    // 1. Temporarily encrypt names for the file
    for(int i = 0; i < candidateCount; i++) encrypt_decrypt(candidates[i].name);

    // 2. Write everything
    fwrite(&candidateCount, sizeof(int), 1, fp);
    fwrite(candidates, sizeof(Candidate), candidateCount, fp);
    fwrite(&votedCount, sizeof(int), 1, fp);
    fwrite(votedUsers, sizeof(char) * 20, votedCount, fp);

    // 3. IMMEDIATELY decrypt back so the program can still use the names
    for(int i = 0; i < candidateCount; i++) encrypt_decrypt(candidates[i].name);

    fclose(fp);
}

void load_data() {
    FILE *fp = fopen("data/election_data.dat", "rb");
    if (fp == NULL) return; // No previous data found

    fread(&candidateCount, sizeof(int), 1, fp);
    fread(candidates, sizeof(Candidate), candidateCount, fp);
    fread(&votedCount, sizeof(int), 1, fp);
    fread(votedUsers, sizeof(char) * 20, votedCount, fp);

    // Decrypt names for UI use
    for(int i = 0; i < candidateCount; i++) encrypt_decrypt(candidates[i].name);

    fclose(fp);
}