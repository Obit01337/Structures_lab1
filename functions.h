char menu(void);
char checkOption(void);
struct customersInfo addCustomer(struct customersInfo info);
int checkUnsigned(void);


struct customer
{
    char *lastName;
    char *firstName;
    char *middleName;
    char *address;
    char *phoneNumber;
    char *cardNumber;
};

struct customersInfo
{
    struct customer *customers;
    unsigned amount;
};