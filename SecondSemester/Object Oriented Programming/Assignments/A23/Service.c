#include "Service.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

Service* createService(Repository repo, UndoRepo UndoRedo)
{
    Service* service = (Service*)malloc(sizeof(Service));

    if (service == NULL)
        return NULL;
    service->repo = repo;
    service->undoRedo = UndoRedo;

    return service;
}

void copyRepoService(Service* service, UndoRepo* UndoRedo)
{
    service->repo.array.count = UndoRedo->data[UndoRedo->currentPosition].array.count;
    service->repo.array.maxLength = UndoRedo->data[UndoRedo->currentPosition].array.maxLength;
    for (int i = 0; i < UndoRedo->data[UndoRedo->currentPosition].array.count; i++)
        service->repo.array.data[i] = UndoRedo->data[UndoRedo->currentPosition].array.data[i];
}

void destroyService(Service* service)
{
    if (service == NULL)
        return;

    free(service);
}

void addMaterialService(Service* service, char name[], char supplier[], int quantity, char date[])
{
    addMaterialRepo(&service->repo, name, supplier, quantity, date);
    addRepoUndoRedo(&service->undoRedo, &service->repo);

}

int deleteMaterialService(Service* service, char name[], char supplier[])
{
    if (deleteMaterialRepo(&service->repo, name, supplier) == 0)
        return 0;
    else
    {
        addRepoUndoRedo(&service->undoRedo, &service->repo);
        return 1;
    }
}

int updateMaterialExpDate(Service* service, char name[], char supplier[], char newDate[])
{
    if (updateProductExpDateRepo(&service->repo, name, supplier, newDate) == 0)
        return 0;
    else
    {
        addRepoUndoRedo(&service->undoRedo, &service->repo);
        return 1;
    }
}

void sortingByQuantity(Service* service, Repository* repo)
{
    for (int i = 0; i < repo->array.count - 1; i++)
        for (int j = i + 1; j < repo->array.count; j++)
            if (repo->array.data[i].quantity > repo->array.data[j].quantity)
            {
                Material aux = repo->array.data[i];
                repo->array.data[i] = repo->array.data[j];
                repo->array.data[j] = aux;
            }
}


void searchMaterialByGivenString(Service* service, char givenString[], Repository* repository, char currentDate[])
{
    searchElementsByGivenString(&service->repo, givenString, repository, currentDate);
    sortingByQuantity(service, repository);

}

int searchMaterialsBySupplier(Service* service, char supplier[], Repository* repository, int quantity)
{
    int ok = searchElementsBySupplierRepo(&service->repo, supplier, repository);
    int i = 0;
    while (i < repository->array.count)
    {
        if (repository->array.data[i].quantity > quantity)
            deleteMaterialRepo(repository, repository->array.data[i].name, repository->array.data[i].supplier);
        else
            i++;

    }

    if (repository->array.count == 0)
        return 0;
    else if (ok == 0)
        return 1;
    else
        return 2;
}

int updateMaterialQuantity(Service* service, char name[], char supplier[], int newQuantity)
{

    if (updateMaterialQuantityRepo(&service->repo, name, supplier, newQuantity) == 0)
        return 0;
    else
    {
        addRepoUndoRedo(&service->undoRedo, &service->repo);
        return 1;
    }
}