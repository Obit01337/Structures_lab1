
char menu(void);
char getOption(char leftBorder, char rightBorder);

struct customersInfo addCustomers(struct customersInfo database);
unsigned getUnsigned(void);
char* getStringLetters(void);
char* getStringDigits(size_t size);


void showCustomers(struct customersInfo database);
void printSpaces(size_t steps);

void changeCustomerInformation(struct customersInfo database);
bool changeField(struct customersInfo database, unsigned num);
char areYouSure(void);

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