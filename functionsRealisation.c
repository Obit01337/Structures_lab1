#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "functions.h"


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
    } while (!(option = checkOption()));
    return option;
}

char checkOption(void)
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

//Add customer information

struct customersInfo addCustomer(struct customersInfo info)
{
    static unsigned amount;
    static int i;
    int numCustomers;
    do
    {
        system("cls");
        puts("How many customers do you want to add? Enter the number");
        puts("<0)\tBack to menu>");
    } while ((numCustomers = checkUnsigned()) < 0);
    if (numCustomers == 0)
    {
        return info;
    }
    amount += numCustomers;
    struct customer *temp;
    if (!(temp = (struct customer*)realloc(info.customers, amount * sizeof(struct customer))))
    {
        puts("Not enough memory to add new customers!");
        system("pause>0");
        return info;
    }
    else
    {
        info.customers = temp;
        info.amount = amount;
    }
    for (i; i < amount; ++i)
    {

    }
    return info;
}

int checkUnsigned()
{
    int num;
    char newLine;
    rewind(stdin);
    if (scanf("%i%c", &num, &newLine) != 2 || newLine != '\n' || num < 0)
    {
        puts("Invalid input, try again!");
        system("pause>0");
        system("cls");
        return -1;
    }
    return num;
}





