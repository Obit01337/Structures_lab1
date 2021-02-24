#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "functions.h"

//Menu settings
//###################################################################
char menu(void)
{
    char option;
    do
    {
        puts("select an option from the list below:");
        puts("1)\t<Add customer information>");
        puts("2)\t<Show customer information>");
        puts("3)\t<Change customer information>");
        puts("4)\t<Find customer according to the specified data (full match)>");
        puts("5)\t<Sort customer information>");
        puts("6)\t<Remove customer from database>");
        puts("7)\t<Find customer according to the specified data (partial match using *)>");
        puts("0)\t<Exit the program>");
        printf(">");
    } while (!(option = getOption()));
    return option;
}
char getOption(void)
{
    char option, newLine;
    rewind(stdin);
    if (scanf("%c%c", &option, &newLine) != 2 || newLine != '\n')
    {
        puts("Invalid input, try again!");
        system("pause>0");
        system("cls");
        return '\0';
    }
    return option;
}
//###################################################################

//Add customer information
//###################################################################
struct customersInfo addCustomer(struct customersInfo database)
{
    // Get number of new customers
    int number;
    do
    {
        system("cls");
        puts("How many customers do you want to add? Enter the number:");
        puts("0)\t<Back to menu>");
        printf(">");
    } while ((number = getUnsigned()) < 0);
    if (number == 0)
        return database;

    // Reallocation check
    struct customer *temp;
    database.amount += number;
    if (!(temp = (struct customer*)realloc(database.customers, database.amount * sizeof(struct customer))))
    {
        database.amount -= number;
        puts("Not enough memory to add new customers!");
        system("pause>0");
        return database;
    }
    database.customers = temp;

    for (unsigned i = database.amount - number; i < database.amount; ++i)
    {
        do
        {
            system("cls");
            printf("Enter surname for customer %i:\n>", i + 1);
        } while (!(database.customers->surname = getStringLetters()));
        do
        {
            system("cls");
            printf("Enter name for customer %i:\n>", i + 1);
        } while (!(database.customers->name = getStringLetters()));
        do
        {
            system("cls");
            printf("Enter patronymic for customer %i:\n>", i + 1);
        } while (!(database.customers->patronymic = getStringLetters()));
        do
        {
            system("cls");
            printf("Enter street for customer %i:\n>", i + 1);
        } while (!(database.customers->address.street = getStringLetters()));
        do
        {
            system("cls");
            printf("Enter house number for customer %i:\n>", i + 1);
        } while ((database.customers->address.homeNumber = getUnsigned()) < 0);
        do
        {
            system("cls");
            printf("Enter flat number for customer %i:\n>", i + 1);
        } while ((database.customers->address.flatNumber = getUnsigned()) < 0);
        do
        {
            system("cls");
            printf("Enter phone number for customer %i:\n", i + 1);
            printf("<Phone number must have 7 digits>\n>");
        } while (!(database.customers->phoneNumber = getStringDigits(7)));
        do
        {
            system("cls");
            printf("Enter card number for customer %i:\n", i + 1);
            printf("<Card number must have 16 digits>\n>");
        } while (!(database.customers->cardNumber = getStringDigits(16)));
    }
    return database;
}

int getUnsigned(void)
{
    int num;
    char newLine;
    rewind(stdin);
    if (scanf("%i%c", &num, &newLine) != 2 || newLine != '\n' || num < 0)
    {
        puts("Invalid input, try again!");
        system("pause>0");
        return -1;
    }
    return num;
}
char* getStringLetters(void)
{
    char* str = NULL;
    char c;
    int i;
    rewind(stdin);
    for (i = 0; (c = (char)getchar()) != '\n'; ++i)
    {
        //Letter check
        if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
        {
            puts("You can't enter not letters!");
            system("pause>0");
            rewind(stdin);
            return NULL;
        }
        //Reallocation check
        if (!(str = (char*)realloc(str, i + 2)))
        {
            puts("Not enough memory!");
            system("pause>0");
            return NULL;
        }
        //Converts letters to the correct case
        if ((!i && (c >= 'A' && c <= 'Z')) || (c >= 'a' && c<= 'z'))
            str[i] = c;
        else if (!i)
            str[i] =(char)(c - ('a' - 'A'));
        else
            str[i] = (char)(c + ('a' - 'A'));
    }
    str[i] = '\0';
    return str;
}
char* getStringDigits(size_t size)
{
    char *str = NULL;
    if (!(str = (char*)malloc(size)))
    {
        puts("Not enough memory!");
        system("pause>0");
        return NULL;
    }
    rewind(stdin);
    for (int i = 0; i < size; ++i)
    {
        str[i] = (char)getchar();
        if (str[i] < '0' || str[i] > '9')
        {
            puts("You can't enter not digits!");
            system("pause>0");
            rewind(stdin);
            return NULL;
        }
    }
    return str;
}
//###################################################################

//Show customer information
//###################################################################
//###################################################################