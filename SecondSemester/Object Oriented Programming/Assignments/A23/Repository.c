#include "Repository.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


Repository* createRepo(DynamicArray array)
{
    Repository* repo = (Repository*)malloc(sizeof(Repository));
    if (repo == NULL)
        return NULL;

    repo->array = array;

    return repo;
}

void copyRepo(Repository* repo, Repository newRepo)
{
    for (int i = 0; i < repo->array.count; i++)
        assignValues(&newRepo.array.data[i], repo->array.data[i]);
}

Repository duplicateRepo(Repository* repo)
{
    Repository newRepo;
    newRepo.array.maxLength = repo->array.maxLength;
    newRepo.array.count = repo->array.count;

    newRepo.array.data = (Material*)malloc(newRepo.array.maxLength * sizeof(Material));

    copyRepo(repo, newRepo);
    return newRepo;

}

void initializeRepo(Repository* repo)
{
    addMaterialRepo(repo, "Flour", "King Flour", 100, "01.04.2024");
    addMaterialRepo(repo, "Sugar", "Domino Sugar", 50, "01.04.2024");
    addMaterialRepo(repo, "Butter", "Napolact", 10, "16.03.2023");
    addMaterialRepo(repo, "Yeast", "King Flour", 40, "16.03.2024");
    addMaterialRepo(repo, "Baking Powder", "King Flour", 70, "06.09.2024");
    addMaterialRepo(repo, "Eggs", "Eggland's Best", 124, "18.03.2023");
    addMaterialRepo(repo, "Vanila Extract", "Nielsen-Massey", 3, "16.06.2024");
    addMaterialRepo(repo, "Chocolate", "Callebaut", 5, "16.06.2024");
    addMaterialRepo(repo, "Cream", "Organic Valley", 150, "01.04.2023");
    addMaterialRepo(repo, "Fruit Fillings", "Solo Foods", 70, "18.03.2023");
}

void destroyRepo(Repository* repo)
{
    if (repo == NULL)
        return;

    free(repo);

}

void searchElementsByGivenString(Repository* repo, char givenString[], Repository* repository, char currentDate[])
{
    givenString[strlen(givenString) - 1] = '\0';
    if (strcmp(givenString, "") == 0)
    {
        for (int i = 0; i < repo->array.count; i++)
            if (strcmp(repo->array.data[i].date, currentDate) < 0)
                addMaterialRepo(repository, repo->array.data[i].name, repo->array.data[i].supplier, repo->array.data[i].quantity, repo->array.data[i].date);
    }
    else
    {
        for (int i = 0; i < repo->array.count; i++)
            if ((strstr(repo->array.data[i].name, givenString) != NULL || strstr(repo->array.data[i].supplier, givenString) != NULL) && strcmp(repo->array.data[i].date, currentDate) < 0)
                addMaterialRepo(repository, repo->array.data[i].name, repo->array.data[i].supplier, repo->array.data[i].quantity,
                    repo->array.data[i].date);
    }

}

int searchElementsBySupplierRepo(Repository* repo, char supplier[], Repository* repository)
{
    int count = 0;
    for (int i = 0; i < repo->array.count; i++)
        if (strcmp(repo->array.data[i].supplier, supplier) == 0)
        {
            count++;
            addMaterialRepo(repository, repo->array.data[i].name, repo->array.data[i].supplier, repo->array.data[i].quantity,
                repo->array.data[i].date);

        }

    if (count != 0)
        return 1;
    else
        return 0;
}

int ExistenceOfMaterial(Repository* repo, char name[], char supplier[])
{
    for (int i = 0; i < repo->array.count; i++)
        if ((strcmp(repo->array.data[i].name, name) == 0) && (strcmp(repo->array.data[i].supplier, supplier) == 0))
            return i;
    return -1;
}

int deleteMaterialRepo(Repository* repo, char name[], char supplier[])
{
    int position;
    position = ExistenceOfMaterial(repo, name, supplier);
    if (position == -1)
        return 0;
    else
    {
        deleteTElem(&repo->array, position);
        return 1;
    }
}

int updateMaterialQuantityRepo(Repository* repo, char name[], char supplier[], int quantity)
{
    int position;
    position = ExistenceOfMaterial(repo, name, supplier);
    if (position == -1)
        return 0;
    else
    {
        Material material = createMaterial(name, supplier, quantity, getDate(&repo->array.data[position]));
        updateTElem(&repo->array, material, position);
        return 1;
    }
}


void addMaterialRepo(Repository* repo, char name[], char supplier[], int quantity, char date[])
{
    int position;
    position = ExistenceOfMaterial(repo, name, supplier);
    if (position == -1)
    {
        Material material;
        material = createMaterial(name, supplier, quantity, date);
        addTElem(&repo->array, material);
    }
    else
    {
        repo->array.data[position].quantity = repo->array.data[position].quantity + quantity;
    }

}

int updateProductExpDateRepo(Repository* repo, char name[], char supplier[], char date[])
{
    int position;
    position = ExistenceOfMaterial(repo, name, supplier);
    if (position == -1)
        return 0;
    else
    {
        Material material = createMaterial(name, supplier, getQuantity(&repo->array.data[position]), date);
        updateTElem(&repo->array, material, position);
        return 1;
    }
}

int getCount(Repository* repo)
{
    return repo->array.count;
}