#ifndef MODELS_H
#define MODELS_H

#define MAX_CANDIDATES 10
#define MAX_VOTERS 100

typedef struct {
    int id;
    char name[50];
    int voteCount;
} Candidate;

typedef struct {
    char voterID[20];
    int hasVoted;
} Voter;

#endif