#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
// https://manual.cs50.io/3/ispunct

int getValueOfTheCharacter(char charactere, const int valueOfCharacters[]);
void printFinalScore(int scorePlayer1, int scorePlayer2);

int main(void)
{
    const int valueOfCharacters[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                                     1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    string player1Word = get_string("Player 1: ");
    string player2Word = get_string("Player 2: ");

    int scorePlayer1 = 0;
    int scorePlayer2 = 0;

    int i = 0;

    while (player1Word[i] != '\0')
    {
        scorePlayer1 += getValueOfTheCharacter(player1Word[i], valueOfCharacters);
        i++;
    }
    i = 0;

    while (player2Word[i] != '\0')
    {
        scorePlayer2 += getValueOfTheCharacter(player2Word[i], valueOfCharacters);
        i++;
    }

    printFinalScore(scorePlayer1, scorePlayer2);
}

int getValueOfTheCharacter(char character, const int valueOfCharacters[])
{
    if (ispunct(character) != 0)
    {
        return 0;
    }
    char characterLower = tolower(character);
    int characterPosition = characterLower - 97;

    return valueOfCharacters[characterPosition];
}

void printFinalScore(int scorePlayer1, int scorePlayer2)
{
    if (scorePlayer1 > scorePlayer2)
    {
        printf("Player 1 wins!\n");
    }
    else if (scorePlayer1 < scorePlayer2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie\n");
    }
}

