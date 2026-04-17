#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

int countLetters(string text);
int countWords(string text);
int countSentences(string text);
int calculateIndex(int numberOfLetters, int numberOfWords, int numberOfSentences);
void printGrade(int index);

int main(void)
{
    string text = get_string("Text: ");

    int numberOfLetters = countLetters(text);
    int numberOfWords = countWords(text);
    int numberOfSentences = countSentences(text);

    int index = calculateIndex(numberOfLetters, numberOfWords, numberOfSentences);

    printGrade(index);
}

int countLetters(string text)
{
    int numberOfLetters = 0, i = 0;

    char currentCharacter = text[i];

    while (currentCharacter != '\0')
    {
        if (isalpha(currentCharacter) != 0)
        {
            numberOfLetters++;
        }
        i++;
        currentCharacter = text[i];
    }

    return numberOfLetters;
}
int countWords(string text)
{
    int numberOfWords = 0, i = 0;

    char currentCharacter = text[i];

    while (currentCharacter != '\0')
    {
        if (isspace(currentCharacter) != 0)
        {
            numberOfWords++;
        }
        i++;
        currentCharacter = text[i];
    }
    numberOfWords++;

    return numberOfWords;
}
int countSentences(string text)
{
    int numberOfSentences = 0, i = 0;

    char currentCharacter = text[i];

    while (currentCharacter != '\0')
    {
        if (currentCharacter == '.' || currentCharacter == '!' || currentCharacter == '?')
        {
            numberOfSentences++;
        }
        i++;
        currentCharacter = text[i];
    }

    return numberOfSentences;
}

int calculateIndex(int numberOfLetters, int numberOfWords, int numberOfSentences)
{
    float L = ((float) numberOfLetters / numberOfWords) * 100.;
    float S = ((float) numberOfSentences / numberOfWords) * 100;

    float colemanLiauIndex = 0.0588 * L - 0.296 * S - 15.8;

    return (int) round(colemanLiauIndex);
}

void printGrade(int index)
{
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

