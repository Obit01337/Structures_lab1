#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "functions.h"


int main(void)
{
    struct customersInfo database;
    database.customers = NULL;
    database.amount = 0;
    do
    {
        system("cls");
        switch (menu())
        {
            case '1':
                database = addCustomers(database);
                break;
            case '2':
                showCustomers(database);
                system("pause>0");
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                break;
            case '7':
                break;
            case '0':
                for (unsigned i = database.amount; i >= 0; ++i)
                {
                        free(database.customers[i].surname);
                        free(database.customers[i].name);
                        free(database.customers[i].patronymic);
                        free(database.customers[i].address.street);
                        free(database.customers[i].phoneNumber);
                        free(database.customers[i].cardNumber);
                }
                free(database.customers);
                return 0;
            default:
                puts("Invalid input, try again!");
                system("pause>0");
                break;
        }
    } while (1);
}


