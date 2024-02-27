#pragma once
#include "Material.h"
#include "Repository.h"
#include "Service.h"
#include <stdio.h>

typedef struct
{
    Service service;
} UI;

UI* createUI(Service service);
void destroyUI(UI* ui);
void displayMaterialsUI(UI* ui);
void addMaterialUI(UI* ui);
void deleteMaterialUI(UI* ui);
void updateMaterialExpDateUI(UI* ui);
void updateMaterialQuantityUI(UI* ui);
void searchElementsByStringPastExpDate(UI* ui);
void displayMaterialsBySupplierUnderQuantity(UI* ui);
void undoUi(UI* ui);
void redoUi(UI* ui);
void menu(UI* ui);
void start(UI* ui);
