#pragma once
#include "Repository.h"
#include "UndoRedo.h"

typedef struct
{
    Repository repo;
    UndoRepo undoRedo;

} Service;

Service* createService(Repository repository, UndoRepo UndoRedo);
void addMaterialService(Service* service, char name[], char supplier[], int quantity, char date[]);
int deleteMaterialService(Service* service, char name[], char supplier[]);
int updateMaterialQuantity(Service* service, char name[], char supplier[], int quantity);
int updateMaterialExpDate(Service* service, char name[], char supplier[], char date[]);
void destroyService(Service* service);
void sortingByQuantity(Service* service, Repository* repo);
void searchMaterialByGivenString(Service* service, char givenString[], Repository* repository, char currenDate[]);
void copyRepoService(Service* service, UndoRepo* UndoRedo);
int searchMaterialsBySupplier(Service* service, char supplier[], Repository* repository, int quantity);

