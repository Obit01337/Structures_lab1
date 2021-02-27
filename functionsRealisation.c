#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "functions.h"

//Menu settings
//######################################################################################################################
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
    } while (!(option = getOption('0', '7')));
    return option;
}

char getOption(char leftBorder, char rightBorder)
{
    char option, newLine;
    rewind(stdin);
    if (scanf("%c%c", &option, &newLine) != 2 || newLine != '\n' || option < leftBorder || option > rightBorder)
    {
        puts("Invalid input, try again!");
        system("pause>0");
        system("cls");
        return '\0';
    }
    return option;
}
//######################################################################################################################

//Add customer information
//######################################################################################################################
struct customersInfo addCustomers(struct customersInfo database)
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
        } while (!(database.customers[i].surname = getStringLetters()));
        do
        {
            system("cls");
            printf("Enter name for customer %i:\n>", i + 1);
        } while (!(database.customers[i].name = getStringLetters()));
        do
        {
            system("cls");
            printf("Enter patronymic for customer %i:\n>", i + 1);
        } while (!(database.customers[i].patronymic = getStringLetters()));
        do
        {
            system("cls");
            printf("Enter street for customer %i:\n>", i + 1);
        } while (!(database.customers[i].address.street = getStringLetters()));
        do
        {
            system("cls");
            printf("Enter house number for customer %i:\n>", i + 1);
        } while (!(database.customers[i].address.homeNumber = getUnsigned()) || database.customers[i].address.homeNumber > 999);
        do
        {
            system("cls");
            printf("Enter flat number for customer %i:\n>", i + 1);
        } while (!(database.customers[i].address.flatNumber = getUnsigned()) || database.customers[i].address.flatNumber > 999);
        do
        {
            system("cls");
            printf("Enter phone number for customer %i:\n", i + 1);
            printf("<Phone number must have 7 digits>\n>");
        } while (!(database.customers[i].phoneNumber = getStringDigits(7)));
        do
        {
            system("cls");
            printf("Enter card number for customer %i:\n", i + 1);
            printf("<Card number must have 16 digits>\n>");
        } while (!(database.customers[i].cardNumber = getStringDigits(16)));
    }
    return database;
}

unsigned getUnsigned(void)
{
    unsigned num;
    char newLine;
    rewind(stdin);
    if (scanf("%u%c", &num, &newLine) != 2 || newLine != '\n')
    {
        puts("Invalid input, try again!");
        system("pause>0");
        return 0;
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
        if ((!i && (c >= 'A' && c <= 'Z')) || (i && (c >= 'a' && c<= 'z')))
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
    if (!(str = (char*)malloc(size + 1)))
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
    if (getchar() != '\n')
    {
        puts("Too many digits!");
        system("pause>0");
        rewind(stdin);
        return NULL;
    }
    str[size] = '\0';
    return str;
}
//######################################################################################################################

//Show customer information
//######################################################################################################################
void showCustomers(struct customersInfo database)
{
    if (database.amount == 0)
    {
        puts("There is no customer information in the database!");
        system("pause>0");
        return;
    }
    // Determine the length of the columns
    size_t surnameColumnLen = strlen("Surname");
    size_t nameColumnLen = strlen("Name");
    size_t patronymicColumnLen = strlen("Patronymic");
    size_t addressColumnLen = 1;
    size_t phoneNumberLen = strlen("Phone Number");
    size_t cardNumberLen = 19;
    for (int i = 0; i < database.amount; ++i)
    {
        if (strlen(database.customers[i].surname) > surnameColumnLen)
            surnameColumnLen = strlen(database.customers[i].surname);
        if (strlen(database.customers[i].name) > nameColumnLen)
            nameColumnLen = strlen(database.customers[i].name);
        if (strlen(database.customers[i].patronymic) > patronymicColumnLen)
            patronymicColumnLen = strlen(database.customers[i].patronymic);
        if (strlen(database.customers[i].address.street) > addressColumnLen)
            addressColumnLen = strlen(database.customers[i].address.street);
    }
    addressColumnLen += 13;


    size_t steps;
    // Show columns
    system("cls");
    printf("     | ");
    printSpaces(steps = (surnameColumnLen - strlen("Surname")) / 2);
    printf("Surname");
    printSpaces(surnameColumnLen - steps - strlen("Surname") + 1);

    printf("| ");
    printSpaces(steps = (nameColumnLen - strlen("Name")) / 2);
    printf("Name");
    printSpaces(nameColumnLen - steps - strlen("Name") + 1);

    printf("| ");
    printSpaces(steps = (patronymicColumnLen - strlen("Patronymic")) / 2);
    printf("Patronymic");
    printSpaces(patronymicColumnLen - steps - strlen("Patronymic") + 1);

    printf("| ");
    printSpaces(steps = (addressColumnLen - strlen("Address")) / 2);
    printf("Address");
    printSpaces(addressColumnLen - steps - strlen("Address") + 1);

    printf("| ");
    printSpaces(steps = (phoneNumberLen - strlen("Phone Number")) / 2);
    printf("Phone Number");
    printSpaces(phoneNumberLen - steps - strlen("Phone Number") + 1);

    printf("| ");
    printSpaces(steps = (cardNumberLen - strlen("Card Number")) / 2);
    printf("Card Number");
    printSpaces(cardNumberLen - steps - strlen("Card Number") + 1);

    printf("|\n\n");
    for (int i = 0; i < database.amount; ++i)
    {
        size_t max = surnameColumnLen + nameColumnLen + patronymicColumnLen + addressColumnLen + phoneNumberLen + cardNumberLen + 24;
        for (int j = 0; j < max; ++j)
            putchar('-');
        puts("");

        printf("%5i", i + 1);

        printf("| ");
        printSpaces(steps = (surnameColumnLen - strlen(database.customers[i].surname)) / 2);
        printf("%s", database.customers[i].surname);
        printSpaces(surnameColumnLen - steps - strlen(database.customers[i].surname) + 1);

        printf("| ");
        printSpaces(steps = (nameColumnLen - strlen(database.customers[i].name)) / 2);
        printf("%s", database.customers[i].name);
        printSpaces(nameColumnLen - steps - strlen(database.customers[i].name) + 1);

        printf("| ");
        printSpaces(steps = (patronymicColumnLen - strlen(database.customers[i].patronymic)) / 2);
        printf("%s", database.customers[i].patronymic);
        printSpaces(patronymicColumnLen - steps - strlen(database.customers[i].patronymic) + 1);

        printf("| ");
        printSpaces(steps = (addressColumnLen - (strlen(database.customers[i].address.street) + 13)) / 2);
        printf("%s ", database.customers[i].address.street);
        printf("h.%3u ", database.customers[i].address.homeNumber);
        printf("fl.%3u", database.customers[i].address.flatNumber);
        printSpaces(addressColumnLen - steps - (strlen(database.customers[i].address.street) + 13) + 1);

        printf("| ");
        printSpaces(steps = (phoneNumberLen - (strlen(database.customers[i].phoneNumber) + 2)) / 2);
        for (int j = 0; database.customers[i].phoneNumber[j] != '\0'; ++j)
        {
            if (j == 3 || j == 5)
                putchar('-');
            putchar(database.customers[i].phoneNumber[j]);
        }
        printSpaces(phoneNumberLen - steps - (strlen(database.customers[i].phoneNumber) + 2) + 1);

        printf("| ");
        printSpaces(steps = (cardNumberLen - (strlen(database.customers[i].cardNumber) + 3)) / 2);
        for (int j = 0; database.customers[i].cardNumber[j] != '\0'; ++j)
        {
            if (j == 4 || j == 8 || j == 12)
                putchar(' ');
            putchar(database.customers[i].cardNumber[j]);
        }
        printSpaces(cardNumberLen - steps - (strlen(database.customers[i].cardNumber) + 3) + 1);

        puts("|");
    }
    system("pause>0");
}

void printSpaces(size_t steps)
{
    for (int i = 0; i < steps; ++i)
        printf(" ");
}
//######################################################################################################################

// Change customer information
//######################################################################################################################
void changeCustomerInformation(struct customersInfo database)
{
    system("cls");
    if (database.amount == 0)
    {
        puts("There is no customer information in the database!");
        system("pause>0");
        return;
    }
    unsigned num;
    char option;
    do
    {
        do
        {
            puts("Enter the number of the user you want to change:");
            putchar('>');
            if (database.amount < (num = getUnsigned()) || num == 0)
            {
                puts("There is no user with this number yet! Try again.");
                system("pause>0");
                system("cls");
            }
            else break;
        } while (true);

        do
        {
            if(!changeField(database, num - 1)) break;
            system("cls");
            do puts("continue to modify this user's information?\n<1) - yes, 0) - no>");
            while (!(option = getOption('0', '1')));
        } while (option == '1');
        system("cls");
        do puts("continue to make changes to the database?\n<1) - yes, 0) - no>");
        while (!(option = getOption('0', '1')));
    } while (option == '1');
}


char customerMenu(void)
{
    char option;
    do
    {
        puts("select the field to change from the list below:");
        puts("1)\t<Surname>");
        puts("2)\t<Name>");
        puts("3)\t<Patronymic>");
        puts("4)\t<Address>");
        puts("5)\t<Phone number>");
        puts("6)\t<Card number>");
        puts("0)\t<Back>");
        printf(">");
    } while (!(option = getOption('0', '6')));
    return option;
}

bool changeField(struct customersInfo database, unsigned num)
{
    system("cls");
    char *string;
    unsigned house, flat;
    switch (customerMenu())
    {
        case '1':
            system("cls");
            printf("Enter new surname for customer %i:\n>", num + 1);
            while (!(string = getStringLetters()));
            if (areYouSure())
                database.customers[num].surname = string;
            else return 1;
            break;
        case '2':
            system("cls");
            printf("Enter new name for customer %i:\n>", num + 1);
            while (!(string = getStringLetters()));
            if (areYouSure())
                database.customers[num].name = string;
            else return 1;
            break;
        case '3':
            system("cls");
            printf("Enter new patronymic for customer %i:\n>", num + 1);
            while (!(string = getStringLetters()));
            if (areYouSure())
                database.customers[num].patronymic = string;
            else return 1;
            break;
        case '4':
            system("cls");
            printf("Enter new street for customer %i:\n>", num + 1);
            while (!(string = getStringLetters()));

            printf("Enter new house number for customer %i:\n>", num + 1);
            while (!(house = getUnsigned()) || house > 999);

            printf("Enter new flat number for customer %i:\n", num + 1);
            while (!(flat = getUnsigned()) || flat > 999);

            if (areYouSure())
            {
                database.customers[num].address.street = string;
                database.customers[num].address.homeNumber = house;
                database.customers[num].address.flatNumber = flat;
            }
            else return 1;

            break;
        case '5':
            system("cls");
            printf("Enter new phone number for customer %i:\n>", num + 1);
            while (!(string = getStringDigits(7)));
            if (areYouSure())
                database.customers[num].phoneNumber = string;
            else return 1;
            break;
        case '6':
            system("cls");
            printf("Enter new card number for customer %i:\n>", num + 1);
            while (!(string = getStringDigits(16)));
            if (areYouSure())
                database.customers[num].cardNumber = string;
            else return 1;
            break;
        case '0':
            return 0;
    }
    return 1;
}

char areYouSure(void)
{
    char option;
    do puts("Are you sure?\n<1) - yes, 0) - no>");
    while (!(option = getOption('0', '1')));
    return option;
}
//######################################################################################################################