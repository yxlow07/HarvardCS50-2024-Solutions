#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int scores[26] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};

int calculateScore(string playerInput) {
    int score = 0;

    // Loop through entire string to calculate score
    for (int i = 0; i < strlen(playerInput); i++) {
        if (isalpha(playerInput[i])) {
            int pos = tolower(playerInput[i]) - 'a';
            score += scores[pos];
        }
    }

    return score;
}

int main(void) {
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    int score1 = calculateScore(player1), score2 = calculateScore(player2);

    if (score1 == score2) {
        printf("Tie!\n");
        return 0;
    }

    if (score1 > score2) {
        printf("Player 1 wins!\n");
    } else {
        printf("Player 2 wins!\n");
    }
}
