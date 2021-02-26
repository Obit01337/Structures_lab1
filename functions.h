
char menu(void);
char getOption(void);

struct customersInfo addCustomers(struct customersInfo database);
int getUnsigned(void);
char* getStringLetters(void);
char* getStringDigits(size_t size);


void showCustomers(struct customersInfo database);
void printSpaces(size_t steps);


struct address
{
    char *street;
    unsigned homeNumber;// 3
    unsigned flatNumber;// 3
};
struct customer
{
    char *surname;
    char *name;
    char *patronymic;
    struct address address;
    char *phoneNumber;// 7
    char *cardNumber;// 16
};
struct customersInfo
{
    struct customer *customers;
    unsigned amount;
};