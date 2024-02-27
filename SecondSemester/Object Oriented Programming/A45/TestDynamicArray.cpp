#include "TestDynamicArray.h"
#include "DynamicArray.h"
#include <assert.h>

void testDynamicArray::testClear()
{
    DynamicArray<Tutorial> arrayForClearTest;
    Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
    arrayForClearTest.addToArray(testingTutorial);
    arrayForClearTest.addToArray(testingTutorial);
    arrayForClearTest.addToArray(testingTutorial);
    assert(arrayForClearTest.getSize() == 3);
    arrayForClearTest.deleteElem(0);
    arrayForClearTest.deleteElem(0);
    arrayForClearTest.deleteElem(0);
    assert(arrayForClearTest.getSize() == 0);
    
}



void testDynamicArray::testAdd()
{
    DynamicArray<Tutorial> arrayForAddTest;
    Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
    arrayForAddTest.addToArray(testingTutorial);
    arrayForAddTest.addToArray(testingTutorial);
    assert(arrayForAddTest[0].getTitle() == "C++ with Marc");
    arrayForAddTest.addToArray(testingTutorial);
    assert(arrayForAddTest[1].getPresenter() == "Marc Laszlo");
    
}

void testDynamicArray::testDelete()
{
    DynamicArray<Tutorial>  arrayForDeleteTest;
    Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
    arrayForDeleteTest.addToArray(testingTutorial);
    arrayForDeleteTest.addToArray(testingTutorial);
    assert(arrayForDeleteTest[0].getTitle() == "C++ with Marc");
    assert(arrayForDeleteTest[1].getTitle() == "C++ with Marc");
    assert(arrayForDeleteTest.getSize() == 2);
    arrayForDeleteTest.deleteElem(0);
    assert(arrayForDeleteTest[0].getTitle() == "C++ with Marc");
    assert(arrayForDeleteTest.getSize() == 1);
    
}

void testDynamicArray::testUpdate()
{
    DynamicArray<Tutorial>  arrayForUpdateTest;
    Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
    Tutorial testingTutorial2("C++ with John", "John", 34, 12, 34, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 6789);
    arrayForUpdateTest.addToArray(testingTutorial);
    arrayForUpdateTest.addToArray(testingTutorial);
    arrayForUpdateTest.addToArray(testingTutorial);
    arrayForUpdateTest.update(testingTutorial2, 1);
    assert(arrayForUpdateTest[1].getTitle() == "C++ with John");
    
}

void testDynamicArray::testGetSize()
{
    DynamicArray<Tutorial>  arrayForTestSize;
    Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
    arrayForTestSize.addToArray(testingTutorial);
    arrayForTestSize.addToArray(testingTutorial);
    assert(arrayForTestSize.getSize() == 2);
    arrayForTestSize.deleteElem(1);
    assert(arrayForTestSize.getSize() == 1);
    arrayForTestSize.deleteElem(0);
    assert(arrayForTestSize.getSize() == 0);
    
}

void testDynamicArray::testAllDynamicArray()
{
    testUpdate();
    testAdd();
    testClear();
    testDelete();
    testGetSize();
    
}
