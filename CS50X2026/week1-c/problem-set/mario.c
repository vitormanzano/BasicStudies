#include <stdio.h>
#include <cs50.h>

void drawTree(int height);

int main(void)
{
    int height;
    do
    {
        height = get_int("What's height? ");
    }
    while (height < 1 || height > 8);
    drawTree(height);
}

void drawTree(int height)
{
    const char sign = '#';

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height - i; j++)
        {
            printf(" ");
        }
        printf("%.*s", i + 1, "########");
        printf(" ");
        printf("%.*s\n", i + 1, "########");
    }
}

