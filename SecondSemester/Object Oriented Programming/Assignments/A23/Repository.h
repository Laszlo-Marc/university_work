#pragma once
#include "Material.h"
#include "DynamicArray.h"

typedef struct
{
    DynamicArray array;

} Repository;

Repository* createRepo(DynamicArray array);
int ExistenceOfMaterial(Repository* repo, char name[], char supplier[]);
int getCount(Repository* repo);
void addMaterialRepo(Repository* repo, char name[], char supplier[], int quantity, char date[]);
int deleteMaterialRepo(Repository* repo, char name[], char supplier[]);
int updateMaterialQuantityRepo(Repository* r, char name[], char supplier[], int quantity);
int updateProductExpDateRepo(Repository* repo, char name[], char supplier[], char date[]);
void destroyRepo(Repository* repo);
void searchElementsByGivenString(Repository* repo, char string[], Repository* repository, char currentDate[]);
int searchElementsBySupplierRepo(Repository* repo, char supplier[], Repository* repository);
void initializeRepo(Repository* repo);
Repository duplicateRepo(Repository* repo);
void copyRepo(Repository* repo, Repository newRepo);