#include "TestRepo.h"
#include "DynamicArray.h"
#include "Repository.h"
#include <assert.h>
#include <tuple>
void testRepo::testInitializeRepo()
{
	Repository testRepo;
	testRepo.initializeRepo();
	assert(testRepo[0].getTitle() == "Java Tutorial for Beginners: Object-Oriented Programming", "Derek Banas");//"Java Tutorial for Beginners: Object-Oriented Programming","Derek Banas",1,35,45,"https://www.youtube.com/watch?v=kJzB8DvH5Oc",1200000
	assert(testRepo[0].getPresenter() == "Derek Banas");
	assert(testRepo[0].getLink() == "https://www.youtube.com/watch?v=kJzB8DvH5Oc");
	assert(testRepo[0].getLikes() == 1200000);
	int hours, minutes, seconds;
	std::tie(hours, minutes, seconds) = testRepo[0].getDuration();
	assert(hours == 1);
	assert(minutes == 35);
	assert(seconds == 45);
	

}

void testRepo::testGetSize()
{
	
	Repository testRepo;
	testRepo.initializeRepo();
	assert(testRepo.getSize() == 14);


}


void testRepo::testAddRepo()
{
	
	Repository testRepo;
	assert(testRepo.addRepo("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000) == true);
	assert(testRepo[0].getTitle() == "C++ with Marc");
	assert(testRepo[0].getPresenter() == "Marc Laszlo");
	assert(testRepo[0].getLink() == "https://www.youtube.com/watch?v=Rub-JsjMhWY");
	assert(testRepo[0].getLikes() == 123000);
	int hours, minutes, seconds;
	std::tie(hours, minutes, seconds) = testRepo[0].getDuration();
	assert(hours == 12);
	assert(minutes == 30);
	assert(seconds == 45);
	assert(testRepo.addRepo("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000) == false);

	
}

void testRepo::testCheckTutorialExistence()
{
	
	Repository testRepo;
	testRepo.addRepo("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	assert(testRepo.checkTutorialExistence("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY") == 0);
	assert(testRepo.checkTutorialExistence("C++ with John", "Marc", "https://www.youtube.com/watch?v=Rub-JsjMhWX") == -1);
	
}

void testRepo::testDeleteTutorial()
{
	
	Repository testRepo;
	testRepo.addRepo("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	assert(testRepo.deleteTutorialRepo("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY") == true);
	assert(testRepo.deleteTutorialRepo("C++ with John", "Marc", "https://www.youtube.com/watch?v=Rub-JsjMhWX") == false);

}

void testRepo::testUpdateLikes()
{
	
	Repository testRepo;
	testRepo.addRepo("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	assert(testRepo.updateLikesRepo("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 146000) == true);
	assert(testRepo[0].getLikes() == 146000);
	assert(testRepo.updateLikesRepo("C++ with John", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 146000) == false);
	
}

void testRepo::testUpdateDuration()
{
	
	Repository testRepo;
	testRepo.addRepo("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	assert(testRepo.updateDurationRepo("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 69, 42, 10) == true);
	int hours, minutes, seconds;
	std::tie(hours, minutes, seconds) = testRepo[0].getDuration();
	assert(hours == 69);
	assert(minutes == 42);
	assert(seconds == 10);
	assert(testRepo.updateDurationRepo("C++ with John", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 69, 42, 10) == false);
}

void testRepo::testAllRepo()
{
	testAddRepo();
	testCheckTutorialExistence();
	testDeleteTutorial();
	//testgetArray();
	testGetSize();
	testInitializeRepo();
	testUpdateDuration();
	testUpdateLikes();
	
}
