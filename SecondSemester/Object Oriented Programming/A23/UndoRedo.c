#include "UndoRedo.h"
#include <stdio.h>
#include <stdlib.h>

UndoRepo* createUndoRepo(int capacity, Repository* repo)
{
    UndoRepo* undoRedoEntity = (UndoRepo*)malloc(sizeof(UndoRepo));
    if (undoRedoEntity == NULL)
        return NULL;
    undoRedoEntity->count = 0;
    undoRedoEntity->maxLength = capacity;
    undoRedoEntity->currentPosition = 0;
    undoRedoEntity->totalOperations = 0;


    undoRedoEntity->data = (Repository*)malloc(capacity * sizeof(Repository));
    if (undoRedoEntity->data == NULL)
        return NULL;

    undoRedoEntity->data[undoRedoEntity->currentPosition] = duplicateRepo(repo);
    return undoRedoEntity;
}

void destroyUndoRedo(UndoRepo* UndoRedo)
{

    if (UndoRedo == NULL)
        return;

    for (int i = 0; i <= UndoRedo->count; i++)
        free(UndoRedo->data[i].array.data);

    free(UndoRedo->data);
    UndoRedo->data = NULL;


    free(UndoRedo);
}

void resizeUndoRedo(UndoRepo* UndoRedo)
{
    UndoRedo->data = (Repository*)(realloc(UndoRedo, sizeof(Repository) * UndoRedo->maxLength * 2));
    UndoRedo->maxLength = UndoRedo->maxLength * 2;
}

void addRepoUndoRedo(UndoRepo* UndoRedo, Repository* repo)
{
    if (UndoRedo == NULL)
        return;
    if (UndoRedo->data == NULL)
        return;


    if (UndoRedo->maxLength == UndoRedo->currentPosition)
        resizeUndoRedo(UndoRedo);

    UndoRedo->currentPosition++;
    UndoRedo->count++;
    UndoRedo->totalOperations = UndoRedo->currentPosition;
    UndoRedo->data[UndoRedo->currentPosition] = duplicateRepo(repo);


}

int RedoOperation(UndoRepo* UndoRedo)
{
    if (UndoRedo->currentPosition == UndoRedo->totalOperations)
        return 0;

    UndoRedo->currentPosition++;
    return 1;

}

int UndoOperation(UndoRepo* UndoRedo)
{
    if (UndoRedo->currentPosition == 0)
        return 0;

    UndoRedo->currentPosition--;
    return 1;
}