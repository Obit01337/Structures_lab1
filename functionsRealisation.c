#include <stdio.h>
#include <stdlib.h>

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

struct customer* addCustomer(struct customer *customers)
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
        return customers;
    amount += numCustomers;
    struct customer temp;
    //убрать функцию реаллок
    if (!(temp = checkRealloc(customers, amount)))
    {
        puts("Not enough memory, try again!");
    }
    for (i; i < amount; ++i)
    {

    }
    return customers;
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

struct customer* checkRealloc(struct customer *ptr, size_t size)
{
    struct customer *temp;
    temp = (struct customer*)realloc(ptr,size * sizeof(struct customer));
}




