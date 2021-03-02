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
                break;
            case '3':
                changeCustomerInformation(database);
                break;
            case '4':
                break;
            case '5':
                sortCustomers(database);
                break;
            case '6':
                database = deleteCustomers(database);
                break;
            case '7':
                break;
            case '0':
                for (unsigned i = database.amount; i >= 0; ++i)
                        freeStruct(database.customers, i);
                free(database.customers);
                return 0;
        }
    } while (1);
}


