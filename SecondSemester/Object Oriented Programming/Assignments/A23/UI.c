#include "UI.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "Validation.h"
#include <stdlib.h>
#pragma warning(disable : 4996)
UI* createUI(Service service)
{
    UI* ui = (UI*)malloc(sizeof(UI));

    if (ui == NULL)
        return NULL;

    ui->service = service;

    return ui;
}

void destroyUI(UI* ui)
{
    if (ui == NULL)
        return;

    free(ui);
}

void displayMaterialsUI(UI* ui)
{
    for (int i = 0; i < ui->service.repo.array.count; i++)
        printf("Name: %s  Supplier: %s  Quantity: %d  Expiration date: %s\n", ui->service.repo.array.data[i].name,
            ui->service.repo.array.data[i].supplier, ui->service.repo.array.data[i].quantity,
            ui->service.repo.array.data[i].date);

}

void addMaterialUI(UI* ui)
{
    char name[100] = "";
    char supplier[100] = "";
    char quantity[100] = "";
    int new_quantity;
    char date[100] = "";
    char empty[100] = "";
    printf("Type in the name of the material: ");
    gets_s(empty, sizeof(empty));
    gets_s(name, sizeof(name));
    printf("Type in the supplier of the material: ");
    gets_s(supplier, sizeof(supplier));
    printf("Type in the quantity of the material: ");
    gets_s(quantity, sizeof(quantity));
    printf("Type in the expiration date of the material: ");
    gets_s(date, sizeof(date));
    if (validateMaterialName(name) != 0 && validateMaterialExpDate(date) != 0 && validateMaterialQuantity(quantity)
        && validateMaterialSupplier(supplier))
    {
        new_quantity = validateMaterialQuantity(quantity);
        addMaterialService(&ui->service, name, supplier, new_quantity, date);
        printf("Material added succesfully!");
    }
    else
        printf("Invalid parameters!");
}

void deleteMaterialUI(UI* ui)
{
    char name[100] = "";
    char type[100] = "";
    char empty[100] = "";
    printf("Type in the name of the material: ");
    gets_s(empty, sizeof(empty));
    gets_s(name, sizeof(name));
    printf("Type in the supplier of the material: ");
    gets_s(type, sizeof(type));
    if (validateMaterialName(name) != 0 && validateMaterialSupplier(type) != 0)
    {
        if (deleteMaterialService(&ui->service, name, type) == 0)
            printf("There is no material with the given name and supplier!");
        else
            printf("Material deleted successfully!");
    }
    else
        printf("Invalid parameters!");
}

void updateMaterialExpDateUI(UI* ui)
{
    char name[100] = "";
    char type[100] = "";
    char date[100] = "";
    char empty[100] = "";
    printf("Type in the name of the material: ");
    gets_s(empty, sizeof(empty));
    gets_s(name, sizeof(name));
    printf("Type in the supplier of the material: ");
    gets_s(type, sizeof(type));
    printf("Type in the expiration date of the material: ");
    gets_s(date, sizeof(date));
    if (validateMaterialName(name) != 0 && validateMaterialSupplier(type) != 0 && validateMaterialExpDate(date) != 0)
    {
        if (updateMaterialExpDate(&ui->service, name, type, date) == 1)
            printf("Expiration date updated successfully!");
        else
            printf("The given material doesn't exist!");
    }
    else
        printf("Invalid parameters!");

}

void updateMaterialQuantityUI(UI* ui)
{
    int new_quantity;
    char name[100] = "";
    char type[100] = "";
    char quantity[100] = "";
    char empty[100] = "";
    printf("Type in the name of the material: ");
    gets_s(empty, sizeof(empty));
    gets_s(name, sizeof(name));
    printf("Type in the supplier of the material: ");
    gets_s(type, sizeof(type));
    printf("Type in the quantity of the material: ");
    gets_s(quantity, 100);
    if (validateMaterialName(name) != 0 && validateMaterialSupplier(type) != 0 && validateMaterialQuantity(quantity) != 0)
    {
        new_quantity = validateMaterialQuantity(quantity);
        if (updateMaterialQuantity(&ui->service, name, type, new_quantity) == 1)
            printf("Material quantity updated successfully!");
        else
            printf("The given material doesn't exist!");
    }
    else
        printf("Invalid parameters!");
}

void searchElementsByStringPastExpDate(UI* ui)
{
    DynamicArray* array = createDynamicArray(100);
    Repository* repo = createRepo(*array);
    char empty[100] = "";
    char string[100] = "";
    char currentDate[100] = "";

    printf("Type in the string after which you want to search the materials: ");
    gets_s(empty, sizeof(empty));
    fgets(string, sizeof(string), stdin);
    printf("Type in the current date: ");
    scanf("%s", currentDate);
    searchMaterialByGivenString(&ui->service, string, repo, currentDate);
    for (int i = 0; i < repo->array.count; i++)
        printf("Name: %s  Supplier: %s  Quantity: %d  Expiration date: %s\n", repo->array.data[i].name,
            repo->array.data[i].supplier, repo->array.data[i].quantity, repo->array.data[i].date);

    destroyRepo(repo);
    destroyArray(array);
}

void displayMaterialsBySupplierUnderQuantity(UI* console)
{
    DynamicArray* array = createDynamicArray(100);
    Repository* repo = createRepo(*array);
    char empty[100] = "";
    char supplier[100] = "";
    int quantity;
    printf("Type in the supplier by which you want to display the materials: ");
    gets_s(empty, sizeof(empty));
    gets_s(supplier, sizeof(supplier));
    if (validateMaterialSupplier(supplier) != 0)
    {
        printf("Type in the required quantity: ");
        scanf("%d", &quantity);
        if (searchMaterialsBySupplier(&console->service, supplier, repo, quantity) == 0)
            printf("There are no materials which check the conditions for display!");
        else if (searchMaterialsBySupplier(&console->service, supplier, repo, quantity) == 1)
        {
            printf("There are no materials from that supplier!");

        }
        else if (searchMaterialsBySupplier(&console->service, supplier, repo, quantity) == 2)
            for (int i = 0; i < repo->array.count; i++)
                printf("Name: %s  Supplier: %s  Quantity: %d  Expiration date: %s\n", repo->array.data[i].name,
                    repo->array.data[i].supplier, repo->array.data[i].quantity, repo->array.data[i].date);
    }
    else
        printf("The given supplier doesn't exist! Try again!");
    destroyRepo(repo);
    destroyArray(array);
}

void undoUi(UI* ui)
{
    if (UndoOperation(&ui->service.undoRedo) == 0)
        printf("There is no undo operation available!");
    else
        copyRepoService(&ui->service, &ui->service.undoRedo);
}

void redoUi(UI* ui)
{
    if (RedoOperation(&ui->service.undoRedo) == 0)
        printf("There is no redo operation available!");
    else
        copyRepoService(&ui->service, &ui->service.undoRedo);
}

void menu(UI* ui)
{
    printf("1. Display all the materials\n");
    printf("2. Add a new material\n");
    printf("3. Delete a material\n");
    printf("4. Update material's quantity\n");
    printf("5. Update material's expiration date\n");
    printf("6. Display all materials past expiration date containing a given string\n");
    printf("7. Undo an operation\n");
    printf("8. Redo an operation\n");
    printf("9. Display all materials from a given supplier, which are in short supply\n");
    printf("E. Exit the program!");


}

void start(UI* ui)
{

    bool done = false;

    while (done == false)
    {
        char command[100];

        printf("\n");
        printf("Command: ");
        scanf("%s", command);
        printf("\n");

        if (strlen(command) != 1)
            printf("Invalid command!\n");
        else
            switch (command[0])
            {
            case '0':
                menu(ui);
                break;

            case '1':
                displayMaterialsUI(ui);
                break;
            case '2':
                addMaterialUI(ui);
                break;

            case '3':
                deleteMaterialUI(ui);
                break;

            case '4':
                updateMaterialQuantityUI(ui);
                break;

            case '5':
                updateMaterialExpDateUI(ui);
                break;

            case '6':

                searchElementsByStringPastExpDate(ui);
                break;

            case '7':
                undoUi(ui);
                break;

            case '8':
                redoUi(ui);
                break;

            case '9':
                displayMaterialsBySupplierUnderQuantity(ui);
                break;

            case 'E':

                done = true;
                break;

            default:
                printf("Invalid command!\n");
            }
    }
}

