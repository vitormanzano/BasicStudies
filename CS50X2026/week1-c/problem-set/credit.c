#include <stdio.h>
#include <cs50.h>

int calculateChecksum(long cardNumber);
void printTheTypeOfTheCard(int firstTwoDigits, int length);
bool isVisa(int firstDigit, int length);
bool isAmericanExpress(int firstTwoDigits, int length);
bool isMasterCard(int firstTwoDigits, int length);
int calculateLength(long card);
int getFirstTwoDigits(long cardNumber);

int main(void)
{
    long card = get_long("Number: ");

    int sum = calculateChecksum(card);

    int firstTwoDigits = getFirstTwoDigits(card);

    if (sum % 10 == 0)
    {
        int length = calculateLength(card);

        printTheTypeOfTheCard(firstTwoDigits, length);
    }
    else
    {
        printf("INVALID\n");
    }
}

int calculateChecksum(long cardNumber)
{
    int round = 0;
    int othersDigits = 0;
    int digitsMultiplied = 0;
    while (cardNumber > 0)
    {
        int digit = cardNumber % 10;
        if (round == 0)
        {
            othersDigits += digit;
            round = 1;
        }
        else
        {
            int digitMultiplied = digit * 2;
            if (digitMultiplied > 9)
            {
                int firstDigit = digitMultiplied % 10;
                int secondDigit = digitMultiplied / 10;

                digitsMultiplied += firstDigit;
                digitsMultiplied += secondDigit;
            }
            else {
                digitsMultiplied += digitMultiplied;
            }
            round = 0;
        }
        cardNumber = cardNumber / 10;
    }

    return digitsMultiplied + othersDigits;
}

void printTheTypeOfTheCard(int firstTwoDigits, int length)
{
    int firstDigit = firstTwoDigits / 10;

    if (isVisa(firstDigit, length))
    {
        printf("VISA\n");
    }
    else if (isAmericanExpress(firstTwoDigits, length))
    {
        printf("AMEX\n");
    }
    else if (isMasterCard(firstTwoDigits, length))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

bool isVisa(int firstDigit, int length)
{
    if (length != 13 && length != 16)
    {
        return false;
    }
    if (firstDigit != 4)
    {
        return false;
    }
    return true;
}

bool isAmericanExpress(int firstTwoDigits, int length)
{
    if (length != 15)
    {
        return false;
    }

    if (firstTwoDigits != 34 && firstTwoDigits != 37)
    {
        return false;
    }
    return true;
}

bool isMasterCard(int firstTwoDigits, int length)
{
    if (length != 16)
    {
        return false;
    }

    if (firstTwoDigits < 51 || firstTwoDigits > 55)
    {
        return false;
    }
    return true;
}

int calculateLength(long card)
{
    int length = 0;
    do
    {
        length += 1;
        card = card / 10;
    }
    while (card > 0);

    return length;
}

int getFirstTwoDigits(long cardNumber)
{
    long firstTwoDigits = cardNumber;
    while (firstTwoDigits >= 100)
    {
        firstTwoDigits = firstTwoDigits / 10;
    }

    return firstTwoDigits;
}

