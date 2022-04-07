
/*
***************************
                        Assignment 1 - Milestone 2
Full Name  :Kranti KC
Student ID#:146277215
Email      :Kk-c3
Section    :NDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
***************************
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "core.h"

void clearInputBuffer(void)
{
    while (getchar() != '\n')
    {
        ;
    }
}


void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}
int inputInt()
{

    int A = -1;
    char bc = '\0';
    int KG = 1;
    do
    {
        scanf("%d%c", &A, &bc);
        if (bc != '\n')
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }
        else
        {
            KG = 0;
        }

    } while (KG);
    return A;
}

int inputIntPositive()
{
    int A = -1;
    do
    {
        A = inputInt();
    } while (A < 0 && printf("ERROR! Value must be > 0: "));
    return A;
}

int inputIntRange(int min, int max)
{
    int A = min - 1;
    do
    {
        A = inputInt();

    } while ((A < min || A > max) && printf("ERROR! Value must be between %d and %d inclusive: ", min, max));
    return A;
}

char inputCharOption(const char* cString)
{
    char A = '\0';
    char bc = '\0';
    int i = 0;
    int l = 0;
    for (l = 1; cString[l]; l++)
        ;
    int KG = 1;
    do
    {
        scanf("%c%c", &A, &bc);

        if (bc == '\n')
        {
            for (i = 0; i < l && KG; i++)
                if (cString[i] == A)
                    KG = 0;
        }

    } while (KG && printf("ERROR: Character must be one of [%s]: ", cString));

    return A;
}

void inputCString(char* cString, int min, int max)
{
    char ai[100] = { '\0' };
    int A = 0;
    int i = 0;
    int j = 0;
    do
    {
        scanf("%99[^\n]%*c", ai);
        for (i = 1; ai[i]; i++)
            ;
        if (min == max)
        {
            if (i == min)
            {
                for (j = 0; ai[j]; cString[j] = ai[j], j++)
                    ;
                cString[j] = '\0';
                A = 1;
            }
        }
        else
        {
            if (i >= min && i <= max)
            {
                for (j = 0; ai[j]; cString[j] = ai[j], j++)
                    ;
                cString[j] = '\0';
                A = 1;
            }
        }
        if (!A)
        {
            if (min == max)
            {
                printf("ERROR: String length must be exactly %d chars: ", min);
            }
            else if (min == 0 || i > max)
            {
                printf("ERROR: String length must be no more than %d chars: ", max);
            }
            else
            {
                printf("ERROR: String length must be between %d and %d chars: ", min, max);
            }
        }

    } while (!A);
}
void displayFormattedPhone(const char* cString)
{
    int checkifValid = 1;
    int i = 0;
    if (cString != NULL)
    {
        for (i = 0; cString[i] && checkifValid; i++)
        {

            if (cString[i] < 48 || cString[i] > 57)
            {
                checkifValid = 0;
            }
        }
    }
    if (checkifValid && i == 10)
    {
        printf("(");
        for (i = 0; i < 3; i++)
            printf("%c", cString[i]);
        printf(")");
        for (i = 3; i < 6; i++)
            printf("%c", cString[i]);
        printf("-");
        for (i = 6; i < 10; i++)
            printf("%c", cString[i]);
    }
    else
    {
        printf("(___)___-____");
    }
}
