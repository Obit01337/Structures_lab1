char menu(void);
char checkOption(void);
struct customer* addCustomer(struct customer *customers);
int checkUnsigned(void);
struct customer* checkRealloc(struct customer *ptr, size_t size);


struct customer
{
    char *lastName;
    char *firstName;
    char *middleName;
    char *address;
    char *phoneNumber;
    char *cardNumber;
};