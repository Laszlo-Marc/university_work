#include <iostream>
#include "Repository.h"
#include "DynamicArray.h"
#include "Tutorial.h"
#include "Validation.h"
#include "Service.h"
#include "Ui.h"
#include "TestTutorial.h"
#include "TestDynamicArray.h"
#include "TestRepo.h"
#include "TestService.h"
#include "TestValidation.h"
#include <crtdbg.h>
#include <windows.h>
using namespace std;

void run() {
    testTutorial::testAllTutorial();
    testDynamicArray::testAllDynamicArray();
    testRepo::testAllRepo();
    testService::testAllService();
    testValidation::testAllValidate();
    UI ui{};
    
    ui.Start();
}
int main(int argc, char* argv[])
{
    run();
    _CrtDumpMemoryLeaks();
    

    return 0;

}