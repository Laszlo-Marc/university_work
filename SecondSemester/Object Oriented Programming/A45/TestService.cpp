#include "TestService.h"
#include "DynamicArray.h"
#include "Repository.h"
#include "Service.h"
#include <assert.h>

void testService::testAddService()
{
	Service testService;
	assert(testService.AddService("C++ with Marc", "Marc Laszlo","https://www.youtube.com/watch?v=Rub-JsjMhWY" ,12, 30, 45,123000,1) == true);
	assert(testService.AddService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 12, 30, 45, 123000,1) == false);

}
/*
void testService::testGetRepo()
{
	DynamicArray<Tutorial> arrayForTest(10);
	Repository testRepo(arrayForTest);
	Service testService(testRepo);
	assert(testService.GetRepository() == arrayForTest);
	
}
*/


void testService::testDeleteService()
{
	Service testService;
	testService.AddService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 12, 30, 45, 123000,1);
	assert(testService.DeleteService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY",1) == true);
	assert(testService.DeleteService("C++ with John", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY",1) == false);
	
}

void testService::testGetSize()
{
	Service testService;
	testService.AddService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 12, 30, 45, 123000,1);
	assert(testService.GetSize() == 1);

}

void testService::testUpdateLikesService()
{
	Service testService;
	testService.AddService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 12, 30, 45, 123000,1);
	assert(testService.UpdateLikesService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 69000) == true);
	assert(testService.UpdateLikesService("C++ with Marc", "John69", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 69000) == false);

}

void testService::testUpdateDurationService()
{

	Service testService;
	testService.AddService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 12, 30, 45, 123000,1);
	assert(testService.UpdateDurationService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY",40,45,33) == true);
	assert(testService.UpdateDurationService("C++ with Marc", "John69", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 45,59,45) == false);
	
}

void testService::testAllService()
{
	testAddService();
	testDeleteService();
	//testGetRepo();
	testGetSize();
	testUpdateDurationService();
	testUpdateLikesService();
}
