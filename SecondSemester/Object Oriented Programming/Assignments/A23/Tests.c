#include <stdlib.h>
#include "tests.h"
#include "Material.h"
#include "Repository.h"
#include "UndoRedo.h"
#include "Validation.h"
#include "Service.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

void testCreateDynamicArray()
{
    DynamicArray* array = createDynamicArray(100);
    assert(array->count == 0);
    assert(array->maxLength == 100);
    destroyArray(array);
}

void testAddTElem()
{
    Material material = createMaterial("Flour", "King Flour", 100, "11.12.2023");
    DynamicArray* array = createDynamicArray(100);
    addTElem(array, material);
    assert(strcmp(array->data[0].name, "Flour") == 0);
    assert(strcmp(array->data[0].supplier, "King Flour") == 0);
    assert(array->data[0].quantity == 100);
    assert(strcmp(array->data[0].date, "11.12.2023") == 0);
    destroyArray(array);

}

void testDeleteTElem()
{
    Material mat1 = createMaterial("Flour", "King Flour", 100, "11.12.2023");
    Material mat2 = createMaterial("Eggs", "State Farm", 100, "11.09.2023");
    DynamicArray* array = createDynamicArray(100);
    addTElem(array, mat1);
    addTElem(array, mat2);
    assert(strcmp(array->data[0].name, "Flour") == 0);
    assert(strcmp(array->data[0].supplier, "King Flour") == 0);
    assert(array->data[0].quantity == 100);
    assert(strcmp(array->data[0].date, "11.12.2023") == 0);
    deleteTElem(array, 0);
    assert(strcmp(array->data[0].name, "Eggs") == 0);
    assert(strcmp(array->data[0].supplier, "State Farm") == 0);
    assert(array->data[0].quantity == 100);
    assert(strcmp(array->data[0].date, "11.09.2023") == 0);
    destroyArray(array);

}

void testUpdateTElem()
{
    Material mat1 = createMaterial("Flour", "King Flour", 100, "11.12.2023");
    Material mat2 = createMaterial("Eggs", "State Farm", 100, "09.09.2040");
    DynamicArray* array = createDynamicArray(100);
    addTElem(array, mat1);
    assert(strcmp(array->data[0].name, "Flour") == 0);
    assert(strcmp(array->data[0].supplier, "King Flour") == 0);
    assert(array->data[0].quantity == 100);
    assert(strcmp(array->data[0].date, "11.12.2023") == 0);
    updateTElem(array, mat2, 0);
    assert(strcmp(array->data[0].date, "09.09.2040") == 0);
    destroyArray(array);
}

void testGetters()
{
    Material material = createMaterial("Flour", "King Flour", 100, "11.12.2023");
    assert(strcmp(getName(&material), "Flour") == 0);
    assert(strcmp(getSupplier(&material), "King Flour") == 0);
    assert(getQuantity(&material) == 100);
    assert(strcmp(getDate(&material), "11.12.2023") == 0);

}

void testCreateMaterial()
{
    Material material = createMaterial("Flour", "King Flour", 100, "11.12.2023");
    assert(strcmp(material.name, "Flour") == 0);
    assert(strcmp(material.supplier, "King Flour") == 0);
    assert(material.quantity == 100);
    assert(strcmp(material.date, "11.12.2023") == 0);
}

void testCreateRepo()
{
    DynamicArray* array = createDynamicArray(100);
    Repository* repo = createRepo(*array);
    initializeRepo(repo);
    assert(repo->array.maxLength == 100);
    assert(repo->array.count == 10);
    assert(strcmp(repo->array.data[0].name, "Flour") == 0);
    assert(strcmp(repo->array.data[0].supplier, "King Flour") == 0);
    assert(repo->array.data[0].quantity == 100);
    assert(strcmp(repo->array.data[0].date, "01.04.2024") == 0);
    destroyRepo(repo);
    destroyArray(array);
}

void testAssignValues()
{
    Material material = createMaterial("Flour", "King Flour", 100, "11.12.2023");
    Material newMaterial;
    assignValues(&newMaterial, material);
    assert(strcmp(material.name, newMaterial.name) == 0);
    assert(strcmp(material.supplier, newMaterial.supplier) == 0);
    assert(material.quantity == newMaterial.quantity);
    assert(strcmp(material.date, newMaterial.date) == 0);

}

void testGetCount()
{
    DynamicArray* array = createDynamicArray(100);
    Repository* repo = createRepo(*array);
    initializeRepo(repo);
    assert(getCount(repo) == 10);
    destroyRepo(repo);
    destroyArray(array);
}

void testAddMaterialRepo()
{
    DynamicArray* array = createDynamicArray(100);
    Repository* repo = createRepo(*array);
    initializeRepo(repo);
    addMaterialRepo(repo, "Oranges", "State Farm", 100, "11.12.2034");
    assert(strcmp(repo->array.data[10].name, "Oranges") == 0);
    assert(strcmp(repo->array.data[10].supplier, "State Farm") == 0);
    assert(repo->array.data[10].quantity == 100);
    assert(strcmp(repo->array.data[10].date, "11.12.2034") == 0);
    destroyRepo(repo);
    destroyArray(array);
}

void testDeleteMaterialRepo()
{
    DynamicArray* array = createDynamicArray(100);
    Repository* repo = createRepo(*array);
    initializeRepo(repo);
    assert(strcmp(repo->array.data[0].name, "Flour") == 0);
    assert(strcmp(repo->array.data[0].supplier, "King Flour") == 0);
    assert(repo->array.data[0].quantity == 100);
    assert(strcmp(repo->array.data[0].date, "01.04.2024") == 0);
    assert(repo->array.count == 10);
    assert(deleteMaterialRepo(repo, "Flour", "King Flour") == 1);
    assert(repo->array.count == 9);
    assert(strcmp(repo->array.data[0].name, "Sugar") == 0);
    assert(strcmp(repo->array.data[0].supplier, "Domino Sugar") == 0);
    assert(repo->array.data[0].quantity == 50);
    assert(strcmp(repo->array.data[0].date, "01.04.2024") == 0);
    assert(deleteMaterialRepo(repo, "Sugar", "Domino Sugar") == 1);
    destroyRepo(repo);
    destroyArray(array);

}

void testCheckExistenceMaterial()
{
    DynamicArray* array = createDynamicArray(100);
    Repository* repo = createRepo(*array);
    initializeRepo(repo);
    assert(ExistenceOfMaterial(repo, "Flour", "King Flour") == 0);
    assert(ExistenceOfMaterial(repo, "Oil", "fruit") == -1);
    destroyRepo(repo);
    destroyArray(array);

}

void testDuplicateRepo()
{
    DynamicArray* array = createDynamicArray(100);
    Repository* repo = createRepo(*array);
    initializeRepo(repo);
    Repository new_repo = duplicateRepo(repo);
    assert(strcmp(new_repo.array.data[0].name, repo->array.data[0].name) == 0);
    assert(strcmp(new_repo.array.data[0].supplier, repo->array.data[0].supplier) == 0);
    assert(new_repo.array.data[0].quantity == repo->array.data[0].quantity);
    assert(strcmp(new_repo.array.data[0].date, repo->array.data[0].date) == 0);
    assert(new_repo.array.count == repo->array.count);
    assert(new_repo.array.maxLength == repo->array.maxLength);
    free(new_repo.array.data);
    destroyRepo(repo);
    destroyArray(array);
}

void testCopyRepo()
{
    DynamicArray* array = createDynamicArray(100);
    Repository* repo = createRepo(*array);
    initializeRepo(repo);
    Repository new_repo;
    new_repo.array.maxLength = repo->array.maxLength;
    new_repo.array.count = repo->array.count;
    new_repo.array.data = (Material*)malloc(new_repo.array.maxLength * sizeof(Material));
    copyRepo(repo, new_repo);
    assert(strcmp(new_repo.array.data[0].name, repo->array.data[0].name) == 0);
    assert(strcmp(new_repo.array.data[0].supplier, repo->array.data[0].supplier) == 0);
    assert(new_repo.array.data[0].quantity == repo->array.data[0].quantity);
    assert(strcmp(new_repo.array.data[0].date, repo->array.data[0].date) == 0);

    assert(strcmp(new_repo.array.data[1].name, repo->array.data[1].name) == 0);
    assert(strcmp(new_repo.array.data[1].supplier, repo->array.data[1].supplier) == 0);
    assert(new_repo.array.data[1].quantity == repo->array.data[1].quantity);
    assert(strcmp(new_repo.array.data[1].date, repo->array.data[1].date) == 0);
    destroyRepo(repo);
    destroyArray(array);
    free(new_repo.array.data);

}

void testAddMaterialService()
{
    DynamicArray* array = createDynamicArray(100);
    Repository* repo = createRepo(*array);
    initializeRepo(repo);
    UndoRepo* UndoRedo = createUndoRepo(100, repo);
    Service* service = createService(*repo, *UndoRedo);

    addMaterialService(service, "Strawberry", "Marc", 100, "11.12.2034");
    assert(strcmp(service->repo.array.data[10].name, "Strawberry") == 0);
    assert(strcmp(service->repo.array.data[10].supplier, "Marc") == 0);
    assert(service->repo.array.data[10].quantity == 100);
    assert(strcmp(service->repo.array.data[10].date, "11.12.2034") == 0);
    destroyService(service);
    destroyUndoRedo(UndoRedo);
    destroyRepo(repo);
    destroyArray(array);
}

void testDeleteMaterialService()
{
    DynamicArray* DA = createDynamicArray(100);
    Repository* repo = createRepo(*DA);
    initializeRepo(repo);
    UndoRepo* UndoRedo = createUndoRepo(100, repo);
    Service* service = createService(*repo, *UndoRedo);
    assert(strcmp(repo->array.data[0].name, "Flour") == 0);
    assert(strcmp(repo->array.data[0].supplier, "King Flour") == 0);
    assert(repo->array.data[0].quantity == 100);
    assert(strcmp(repo->array.data[0].date, "01.04.2024") == 0);
    assert(deleteMaterialService(service, "Flour", "King Flour") == 1);
    assert(strcmp(repo->array.data[0].name, "Sugar") == 0);
    assert(strcmp(repo->array.data[0].supplier, "Domino Sugar") == 0);
    assert(repo->array.data[0].quantity == 50);
    assert(strcmp(repo->array.data[0].date, "01.04.2024") == 0);
    destroyService(service);
    destroyRepo(repo);
    destroyUndoRedo(UndoRedo);
    destroyArray(DA);

}


void testCopyRepoService()
{
    DynamicArray* array = createDynamicArray(100);
    Repository* repo = createRepo(*array);
    initializeRepo(repo);
    UndoRepo* UndoRedo = createUndoRepo(100, repo);
    Service* service = createService(*repo, *UndoRedo);
    addMaterialService(service, "Oranges", "Farm", 100, "11.12.2022");
    UndoOperation(UndoRedo);
    copyRepoService(service, UndoRedo);

    assert(strcmp(repo->array.data[0].name, "Flour") == 0);
    assert(strcmp(repo->array.data[0].supplier, "King Flour") == 0);
    assert(repo->array.data[0].quantity == 100);
    assert(strcmp(repo->array.data[0].date, "01.04.2024") == 0);

    destroyRepo(repo);
    destroyService(service);
    destroyUndoRedo(UndoRedo);
    destroyArray(array);
}

void testCreateUndoRepo()
{
    DynamicArray* array = createDynamicArray(100);
    Repository* repo = createRepo(*array);
    initializeRepo(repo);
    UndoRepo* UndoRedo = createUndoRepo(100, repo);
    assert(UndoRedo->maxLength == 100);
    assert(UndoRedo->count == 0);
    assert(UndoRedo->currentPosition == 0);
    assert(UndoRedo->totalOperations == 0);
    destroyRepo(repo);
    destroyUndoRedo(UndoRedo);
    destroyArray(array);

}

void testAddRepoUndoRedo()
{
    DynamicArray* array = createDynamicArray(100);
    Repository* repo = createRepo(*array);
    Repository new_repo;
    initializeRepo(repo);
    new_repo = duplicateRepo(repo);
    UndoRepo* UndoRedo = createUndoRepo(100, &new_repo);
    Service* service = createService(*repo, *UndoRedo);
    addMaterialService(service, "Oranges", "Farm", 100, "11.12.2023");
    destroyService(service);
    destroyUndoRedo(UndoRedo);
    destroyRepo(repo);
    destroyArray(array);
    free(new_repo.array.data);
}

void testUndoOperation()
{
    DynamicArray* array = createDynamicArray(100);
    Repository* repo = createRepo(*array);
    initializeRepo(repo);
    UndoRepo* UndoRedo = createUndoRepo(100, repo);
    UndoRedo->currentPosition++;
    assert(UndoOperation(UndoRedo) == 1);
    assert(UndoOperation(UndoRedo) == 0);
    destroyRepo(repo);
    destroyArray(array);
    destroyUndoRedo(UndoRedo);
}

void testRedoOperation()
{
    DynamicArray* array = createDynamicArray(100);
    Repository* repo = createRepo(*array);
    initializeRepo(repo);
    UndoRepo* UndoRedo = createUndoRepo(100, repo);
    UndoRedo->totalOperations++;
    assert(RedoOperation(UndoRedo) == 1);
    assert(RedoOperation(UndoRedo) == 0);
    destroyRepo(repo);
    destroyUndoRedo(UndoRedo);
    destroyArray(array);
}

void testValidateMaterialName()
{
    char name[100] = "";
    assert(validateMaterialName(name) == 0);
    char name2[100] = "1Marfi35";
    assert(validateMaterialName(name2) == 0);
    char name3[100] = "Marc";
    assert(validateMaterialName(name3) == 1);
}

void testValidateMaterialQuantity()
{
    char quantity[100] = "";
    assert(validateMaterialQuantity(quantity) == 0);
    char quantity1[100] = "012";
    assert(validateMaterialQuantity(quantity1) == 0);
    char quantity2[100] = "10Ma";
    assert(validateMaterialQuantity(quantity2) == 0);
    char quantity3[100] = "0";
    assert(validateMaterialQuantity(quantity3) == 0);
    char quantity4[100] = "123";
    assert(validateMaterialQuantity(quantity4) == 123);
}

void testValidateSupplier()
{
    char type[100] = "Farm";
    assert(validateMaterialSupplier(type) == 1);
    char type1[100] = "";
    assert(validateMaterialSupplier(type1) == 0);
}

void testValidateExpDate()
{
    char date1[100] = "10.10.11111";
    assert(validateMaterialExpDate(date1) == 0);
    char date2[100] = "10/10.1111";
    assert(validateMaterialExpDate(date2) == 0);
    char date3[100] = "10.10/1111";
    assert(validateMaterialExpDate(date3) == 0);
    char date4[100] = "00.10.2022";
    assert(validateMaterialExpDate(date4) == 0);
    char date5[100] = "11.00.2022";
    assert(validateMaterialExpDate(date5) == 0);
    char date6[100] = "11.11.0000";
    assert(validateMaterialExpDate(date6) == 0);
    char date7[100] = "32.11.2022";
    assert(validateMaterialExpDate(date7) == 0);
    char date8[100] = "12.13.2022";
    assert(validateMaterialExpDate(date8) == 0);
    char date9[100] = "12.13.2020";
    assert(validateMaterialExpDate(date9) == 0);
    char date10[100] = "15.03.2024";
    assert(validateMaterialExpDate(date10) == 1);
    char date11[100] = "11.A3.20AB";
    assert(validateMaterialExpDate(date11) == 0);
    char date12[100] = "11.12.2025";
    assert(validateMaterialExpDate(date12) == 1);
}



void testALL()
{
    
    testAddRepoUndoRedo();
    
    testCopyRepo();
    testCopyRepoService();
    testAddMaterialService();
    testDeleteMaterialService();
    
    
    
    testAddMaterialRepo();
    testAddTElem();
    testAssignValues();
    testCheckExistenceMaterial();
    testCreateDynamicArray();
    testCreateMaterial();
    testCreateRepo();
    testCreateUndoRepo();
    testDeleteMaterialRepo();
    testDeleteTElem();
    testDuplicateRepo();
    testGetCount();
    testGetters();
    testRedoOperation();
    testUndoOperation();
    testUpdateTElem();
    testValidateMaterialName();
    testValidateMaterialQuantity();
    testValidateExpDate();
    testValidateSupplier();
    
    

    _CrtDumpMemoryLeaks();
   
   
}