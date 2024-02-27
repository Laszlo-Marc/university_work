#pragma once
#include "Material.h"

typedef Material TElem;

typedef struct
{
    TElem* data;
    int count;
    int maxLength;

} DynamicArray;

DynamicArray* createDynamicArray(int capacity);
void destroyArray(DynamicArray* array);
void addTElem(DynamicArray* array, TElem TElem);
void deleteTElem(DynamicArray* array, int position);
void updateTElem(DynamicArray* array, TElem TElem, int position);