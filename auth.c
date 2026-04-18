#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

// Helper to read a single character without hitting Enter
int getch_mac() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int authenticate_admin() {
    char password[20] = {0}; // Initialize with zeros
    char correctPass[] = "admin2026";
    int i = 0;
    char ch;

    printf("Enter Admin Password: ");
    fflush(stdout);

    while (i < 19) {
        ch = getch_mac();
        if (ch == '\n' || ch == '\r') { // Enter key
            break;
        } else if (ch == 127) { // Backspace on Mac
            if (i > 0) {
                i--;
                printf("\b \b"); // Move back, print space, move back
                fflush(stdout);
            }
        } else {
            password[i++] = ch;
            printf("*");
            fflush(stdout);
        }
    }
    password[i] = '\0';
    printf("\n");

    if (strcmp(password, correctPass) == 0) return 1;
    
    printf("[!] Access Denied.\n");
    return 0;
}