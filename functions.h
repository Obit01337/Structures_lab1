
char menu(void);
char getOption(void);

struct customersInfo addCustomer(struct customersInfo database);
int getUnsigned(void);
char* getStringLetters(void);
char* getStringDigits(size_t size);

struct address
{
    char *street;
    unsigned homeNumber;
    unsigned flatNumber;
};
struct customer
{
    char *surname;
    char *name;
    char *patronymic;
    struct address address;
    char *phoneNumber;
    char *cardNumber;
};
struct customersInfo
{
    struct customer *customers;
    unsigned amount;
};