#include "Service.h"
#include "UndoRedo.h"
#include "Repository.h"
#include "UI.h"
#include <stdio.h>
#include <time.h>
#include <crtdbg.h>
#include <string.h>
#include "Tests.h"
#include <stdlib.h>

int main()
{
    DynamicArray* array = createDynamicArray(100);
    Repository* repo = createRepo(*array);
    Repository newRepo;
    initializeRepo(repo);
    newRepo = duplicateRepo(repo);
    UndoRepo* UndoRedo = createUndoRepo(100, &newRepo);
    Service* service = createService(*repo, *UndoRedo);
    UI* console = createUI(*service);
    start(console);
    destroyUI(console);
    destroyService(service);
    destroyUndoRedo(UndoRedo);
    destroyRepo(repo);
    destroyArray(array);
    free(newRepo.array.data);


    testALL(); 
    _CrtDumpMemoryLeaks();
   
    return 0;
}
