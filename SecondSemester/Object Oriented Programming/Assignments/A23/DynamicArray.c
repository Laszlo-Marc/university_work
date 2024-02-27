#include "DynamicArray.h"
#include <stdlib.h>

DynamicArray* createDynamicArray(int capacity)
{
    DynamicArray* array = (DynamicArray*)malloc(sizeof(DynamicArray));

    if (array == NULL)
        return NULL;

    array->maxLength = capacity;
    array->count = 0;


    array->data = (TElem*)malloc(capacity * sizeof(TElem));
    if (array->data == NULL)
        return NULL;

    return array;
}

void destroyArray(DynamicArray* array)
{
    if (array == NULL)
        return;

    
    free(array->data);
    array->data = NULL;

    
    free(array);
}

void resize(DynamicArray* array)
{
    array->data = (TElem*)(realloc(array, sizeof(TElem) * array->maxLength * 2));
    array->maxLength = array->maxLength * 2;
}

void deleteTElem(DynamicArray* array, int position)
{
    for (int i = position; i <= array->count - 1; i++)
        array->data[i] = array->data[i + 1];

    array->count--;
}

void addTElem(DynamicArray* array, TElem TElem)
{
    if (array == NULL)
        return;
    if (array->data == NULL)
        return;

    if (array->maxLength == array->count)
        resize(array);
    array->data[array->count] = TElem;
    array->count++;

}

void updateTElem(DynamicArray* array, TElem TElem, int position)
{
    array->data[position] = TElem;
}