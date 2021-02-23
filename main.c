#include <stdio.h>
#include <stdlib.h>

#include "functions.h"


int main(void)
{
    struct customer *customers = NULL;
    do
    {
        system("cls");
        switch (menu())
        {
            case '1':
                addCustomer(customers);
                break;
            case '2':
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
                return 0;
            default:
                puts("Invalid input, try again!");
                system("pause>0");
                break;
        }
    } while (1);
}


