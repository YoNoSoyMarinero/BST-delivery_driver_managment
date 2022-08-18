#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct Driver
{
    char *name;
    char *surname;
    char *vehicle;
    char sex;
    int id;
    int age;
};

struct DriverBTSNode
{
    struct Driver *driver;
    struct DriverBTSNode *left;
    struct DriverBTSNode *right;
};

void printDriver(struct Driver *driver)
{
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
    printf("Name: %s\n", driver->name);
    printf("Surname: %s\n", driver->surname);
    printf("Vehicle: %s\n", driver->vehicle);
    printf("Age: %d\n", driver->age);
    printf("Id: %d\n", driver->id);
    printf("Sex: %c\n", driver->sex);
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
}

struct Driver *createDriver(char *name, char *surname, char *vehicle, char sex, int id, int age)
{
    struct Driver *newDriver = (struct Driver *)malloc(sizeof(struct Driver));
    newDriver->name = name;
    newDriver->surname = surname;
    newDriver->age = age;
    newDriver->sex = sex;
    newDriver->vehicle = vehicle;
    newDriver->id = id;
    return newDriver;
}

struct DriverBTSNode *CreateNewNode(struct Driver *newDriver)
{
    struct DriverBTSNode *newNode = (struct DriverBTSNode *)malloc(sizeof(struct DriverBTSNode));
    newNode->driver = newDriver;
    newNode->left = NULL;
    newNode->right = NULL;
}

void Insert(struct DriverBTSNode **root, char *name, char *surname, char *vehicle, char sex, int id, int age)
{
    struct Driver *newDriver = createDriver(name, surname, vehicle, sex, id, age);
    if (*root == NULL)
        *root = CreateNewNode(newDriver);
    else if (id <= (*root)->driver->id)
        Insert(&((*root)->left), name, surname, vehicle, sex, id, age);
    else
        Insert(&((*root)->right), name, surname, vehicle, sex, id, age);
}

void Search(struct DriverBTSNode **root, int id)
{
    if (*root == NULL)
    {
        printf("There is no driver with that ID\n");
        return;
    }
    if ((*root)->driver->id == id)
    {
        printDriver((*root)->driver);
        return;
    }
    else if ((*root)->driver->id >= id)
        Search(&((*root)->left), id);
    else
        Search(&((*root)->right), id);
}

void testData(struct DriverBTSNode **root)
{
    Insert(root, "Peter", "Jackson", "Car", 'M', 7859, 40);
    Insert(root, "Mary", "Fox", "Bike", 'F', 1254, 26);
    Insert(root, "Mike", "Johnson", "Motorcycle", 'M', 9899, 30);
    Insert(root, "Clara", "Peters", "Car", 'F', 3246, 41);
    Insert(root, "Noah", "Mayer", "Bike", 'M', 1003, 19);
}

void displayAllDrivers(struct DriverBTSNode **root)
{
    if (*root == NULL)
        return;

    displayAllDrivers(&((*root)->left));
    printDriver((*root)->driver);
    displayAllDrivers(&((*root)->right));
}

struct DriverBTSNode *FindMin(struct DriverBTSNode *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

struct DriverBTSNode *deleteById(struct DriverBTSNode *root, int id)
{
    if (root == NULL)
        return root;
    else if (id < root->driver->id)
        root->left = deleteById(root->left, id);
    else if (id > root->driver->id)
        root->right = deleteById(root->right, id);
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            root = NULL;
        }
        else if (root->left == NULL)
        {
            struct DriverBTSNode *temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL)
        {
            struct DriverBTSNode *temp = root;
            root = root->left;
            free(temp);
        }
        else
        {
            struct DriverBTSNode *temp = FindMin(root->right);
            root->driver = temp->driver;
            root->right = deleteById(root->right, temp->driver->id);
        }
    }
    return root;
};

void appMenu()
{
    printf("WELCOME TO SIMPLE DELIVERY DRIVER MANAGMENT SYSTEM!\n");
    printf("To display all drivers please enter: (1)\n");
    printf("To search driver by her/his id please enter: (2)\n");
    printf("To delete driver by her/his id please enter (3): \n");
    printf("To add driver please press: (4)\n");
    printf("To exit please press: (5)\n");
    printf("Your answer: ");
}

char *dataInput(char *input, char *info)
{
    printf("Input driver's %s: ", info);
    scanf("%s", input);
}

char dataInputSex()
{
    printf("Input driver's sex: ");
    char sex;
    scanf(" %c", &sex);
    return sex;
}

int dataInputAge()
{
    printf("Input driver's age: ");
    int age;
    scanf(" %d", &age);
    return age;
}

int dataInputID()
{
    printf("Input driver's id: ");
    int id;
    scanf(" %d", &id);
    return id;
}

void main()
{
    bool running = true;
    int answer; // will be an user response
    int search; // will take an id for search

    struct DriverBTSNode *root = NULL;
    testData(&root);

    while (running)
    {
        appMenu();
        scanf("%d", &answer);
        switch (answer)
        {
        case 1:
            displayAllDrivers(&root);
            break;
        case 2:
            printf("Input ID here: ");
            scanf("%d", &search);
            Search(&root, search);
            break;
        case 3:
            printf("Input ID here: ");
            scanf("%d", &search);
            root = deleteById(root, search);
            break;
        case 4:
            char name[100];
            dataInput(name, "name");
            char surname[100];
            dataInput(surname, "surname");
            char vehicle[100];
            dataInput(vehicle, "vehicle");
            char sex = dataInputSex();
            int id = dataInputID();
            int age = dataInputAge();
            Insert(&root, name, surname, vehicle, sex, id, age);
            break;
        case 5:
            running = false;
            break;
        }
    }
}