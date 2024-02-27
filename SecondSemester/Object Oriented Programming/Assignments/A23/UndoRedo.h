#pragma once
#include "Repository.h"


typedef struct
{
    Repository* data;
    int count;
    int maxLength;
    int currentPosition;
    int totalOperations;

}UndoRepo;


UndoRepo* createUndoRepo(int capacity, Repository* repo);
void destroyUndoRedo(UndoRepo* UndoRedo);
void resizeUndoRedo(UndoRepo* UndoRedo);
void addRepoUndoRedo(UndoRepo* UndoRedo, Repository* repo);
int RedoOperation(UndoRepo* UndoRedo);
int UndoOperation(UndoRepo* UndoRedo);