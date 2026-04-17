#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool validateKey(string key);
bool validateIfEachLetterAppearOnlyOnce(string key);
void encrypt(string key, string plainText);

int main(int agrc, string argv[])
{
    if (agrc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    string key = argv[1];
    if (!validateKey(key))
    {
        return 1;
    }

    string plainText = get_string("plaintext: ");
    encrypt(key, plainText);

    return 0;
}

bool validateKey(string key)
{
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.");
        return false;
    }
    int i = 0;

    char currentCharacter = key[i];

    while (currentCharacter != '\0')
    {
        if (isalpha(currentCharacter) == 0)
        {
            return false;
        }
        i++;
        currentCharacter = key[i];
    }
    if (!validateIfEachLetterAppearOnlyOnce(key))
    {
        return false;
    }

    return true;
}

bool validateIfEachLetterAppearOnlyOnce(string key)
{
    int counts[26] = {0};

    for (int i = 0; key[i] != '\0'; i++)
    {
        char c = tolower(key[i]);
        if (isalpha(c))
        {
            counts[c - 'a']++;
        }
    }

    bool allExactlyOnce = true;
    for (int i = 0; i < 26; i++)
    {
        if (counts[i] != 1)
        {
            allExactlyOnce = false;
            break;
        }
    }
    return allExactlyOnce;
}

void encrypt(string key, string plainText)
{
    int length = strlen(plainText);
    char encryptText[length + 1];

    for (int i = 0; i < length; i++)
    {
        if (isupper(plainText[i]))
        {
            encryptText[i] = toupper(key[plainText[i] - 'A']);
        }
        else if (islower(plainText[i]))
        {
            encryptText[i] = tolower(key[plainText[i] - 'a']);
        }
        else
        {
            encryptText[i] = plainText[i];
        }
    }
    encryptText[length] = '\0';
    printf("ciphertext: %s\n", encryptText);
}

