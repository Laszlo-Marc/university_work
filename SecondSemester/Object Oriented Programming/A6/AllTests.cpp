#include "AllTests.h"
#include <assert.h>
#include <tuple>
#include "Repository.h"
#include "Service.h"
#include "Tutorial.h"
#include "Validation.h"


void testAll::testGetArray()
{
	Repository repo;
	
	repo.addRepo("C++ with Marc", "Marc", 1, 24, 3, "https://www.youtube.com/watch?v=kJzB8DvH5Oc", 12345);
	repo.addRepo("C++ with John", "John", 4, 56, 6, "https://www.youtube.com/watch?v=5-daZoKgUcA", 45678);

    vector<Tutorial>& tutorials = repo.getArray();

	assert(tutorials.size() == 2);
	assert(tutorials[0].getTitle() == "C++ with Marc");
	assert(tutorials[0].getPresenter() == "Marc");
	assert(tutorials[0].getLink() == "https://www.youtube.com/watch?v=kJzB8DvH5Oc");
	assert(tutorials[1].getTitle() == "C++ with John");
	assert(tutorials[1].getPresenter() == "John");
	assert(tutorials[1].getLink() == "https://www.youtube.com/watch?v=5-daZoKgUcA");
	
}

void testAll::testInitializeRepo()
{
	Repository testRepo;
	testRepo.initializeRepo();
	assert(testRepo[0].getTitle() == "Java Tutorial for Beginners: Object-Oriented Programming");
	assert(testRepo[0].getPresenter() == "Derek Banas");
	assert(testRepo[0].getLink() == "https://www.youtube.com/watch?v=kJzB8DvH5Oc");
	assert(testRepo[0].getLikes() == 1200000);
	int hours, minutes, seconds;
	std::tie(hours, minutes, seconds) = testRepo[0].getDuration();
	assert(hours == 1);
	assert(minutes == 35);
	assert(seconds == 45);
	Repository copyConstructorRepo{ testRepo.getArray()};
	assert(copyConstructorRepo[0].getTitle() == "Java Tutorial for Beginners: Object-Oriented Programming", "Derek Banas");
	assert(copyConstructorRepo[0].getPresenter() == "Derek Banas");
	assert(copyConstructorRepo[0].getLink() == "https://www.youtube.com/watch?v=kJzB8DvH5Oc");
	assert(copyConstructorRepo[0].getLikes() == 1200000);
	int hours1, minutes1, seconds1;
	std::tie(hours1, minutes1, seconds1) = testRepo[0].getDuration();
	assert(hours1 == 1);
	assert(minutes1 == 35);
	assert(seconds1 == 45);

}

void testAll::testGetRepository()
{
	Service service;

	service.AddService("C++ with Marc", "Marc","https://www.youtube.com/watch?v=kJzB8DvH5Oc",12345, 1, 24, 3,1);
	service.AddService("C++ with John", "John", "https://www.youtube.com/watch?v=5-daZoKgUcA" , 45678,4, 56, 6,1);

	vector<Tutorial>& tutorials = service.GetRepository();

	assert(tutorials.size() == 2);
	assert(tutorials[0].getTitle() == "C++ with Marc");
	assert(tutorials[0].getPresenter() == "Marc");
	assert(tutorials[0].getLink() == "https://www.youtube.com/watch?v=kJzB8DvH5Oc");
	assert(tutorials[1].getTitle() == "C++ with John");
	assert(tutorials[1].getPresenter() == "John");
	assert(tutorials[1].getLink() == "https://www.youtube.com/watch?v=5-daZoKgUcA");


}

void testAll::testGetUserRepository()
{
	Service service;

	service.AddService("C++ with Marc", "Marc", "https://www.youtube.com/watch?v=kJzB8DvH5Oc", 12345, 1, 24, 3, 2);
	service.AddService("C++ with John", "John", "https://www.youtube.com/watch?v=5-daZoKgUcA", 45678, 4, 56, 6, 2);

	vector<Tutorial>& tutorials = service.GetUserRepository();

	assert(tutorials.size() == 2);
	assert(tutorials[0].getTitle() == "C++ with Marc");
	assert(tutorials[0].getPresenter() == "Marc");
	assert(tutorials[0].getLink() == "https://www.youtube.com/watch?v=kJzB8DvH5Oc");
	assert(tutorials[1].getTitle() == "C++ with John");
	assert(tutorials[1].getPresenter() == "John");
	assert(tutorials[1].getLink() == "https://www.youtube.com/watch?v=5-daZoKgUcA");


}

void testAll::testInitializeService()
{
	Service testService;
	testService.initializeRepo();
	assert(testService.GetSize() == 14);
	Service copyConstructorService{ testService.GetRepository(), testService.GetUserRepository() };
	assert(copyConstructorService.GetSize() == 14);
}

void testAll::testAddService()
{
	Service testService;
	assert(testService.AddService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 12, 30, 45, 123000, 1) == true);
	assert(testService.AddService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 12, 30, 45, 123000, 1) == false);
	assert(testService.AddService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 12, 30, 45, 123000, 2) == true);
	assert(testService.AddService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 12, 30, 45, 123000, 2) == false);

}

void testAll::testDeleteService()
{
	Service testService;
	testService.AddService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 12, 30, 45, 123000, 1);
	assert(testService.DeleteService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 1) == true);
	assert(testService.DeleteService("C++ with John", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 1) == false);
	testService.AddService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 12, 30, 45, 123000, 2);
	assert(testService.DeleteService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 2) == true);
	assert(testService.DeleteService("C++ with John", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 2) == false);

}

void testAll::testGetSizeService()
{
	Service testService;
	testService.AddService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 12, 30, 45, 123000, 1);
	assert(testService.GetSize() == 1);
	testService.AddService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 12, 30, 45, 123000, 2);
	assert(testService.GetUserSize() == 1);

}

void testAll::testGetSize()
{
	Repository testRepo;
	testRepo.initializeRepo();
	assert(testRepo.getSize() == 14);
}

void testAll::testUpdateLikesService()
{
	Service testService;
	testService.AddService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 12, 30, 45, 123000, 1);
	assert(testService.UpdateLikesService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 69000) == true);
	assert(testService.UpdateLikesService("C++ with Marc", "John69", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 69000) == false);
	testService.AddService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 12, 30, 45, 123000, 2);
	assert(testService.UpdateLikesService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 69000) == true);
	assert(testService.UpdateLikesService("C++ with Marc", "John69", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 69000) == false);

}

void testAll::testUpdateDurationService()
{
	Service testService;
	testService.AddService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 12, 30, 45, 123000, 1);
	assert(testService.UpdateDurationService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 40, 45, 33) == true);
	assert(testService.UpdateDurationService("C++ with Marc", "John69", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 45, 59, 45) == false);
	testService.AddService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 12, 30, 45, 123000, 2);
	assert(testService.UpdateDurationService("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 40, 45, 33) == true);
	assert(testService.UpdateDurationService("C++ with Marc", "John69", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 45, 59, 45) == false);

}

void testAll::testAllService()
{
	testGetUserRepository();
	testGetRepository();
	testInitializeService();
	testAddService();
	testDeleteService();
	testGetSizeService();
	testUpdateDurationService();
	testUpdateLikesService();
	
}


void testAll::testSetTitle()
{
	Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	testingTutorial.setTitle("C++ with John69");
	assert(testingTutorial.getTitle() == "C++ with John69");
}

void testAll::testSetPresenter()
{
	Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	testingTutorial.setPresenter("John69");
	assert(testingTutorial.getPresenter() == "John69");
}

void testAll::testSetLink()
{
	Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	testingTutorial.setLink("https://www.youtube.com/watch?v=Rub-JsjMhWX");
	assert(testingTutorial.getLink() == "https://www.youtube.com/watch?v=Rub-JsjMhWX");

}

void testAll::testSetLikes()
{
	Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	testingTutorial.setLikes(69000);
	assert(testingTutorial.getLikes() == 69000);

}

void testAll::testSetDuration()
{
	Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	testingTutorial.setDuration(69, 36, 17);
	int hours, minutes, seconds;
	std::tie(hours, minutes, seconds) = testingTutorial.getDuration();
	assert(hours == 69);
	assert(minutes == 36);
	assert(seconds == 17);
}

void testAll::testGetTitle()
{
	Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	assert(testingTutorial.getTitle() == "C++ with Marc");

}

void testAll::testGetPresenter()
{
	Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	assert(testingTutorial.getPresenter() == "Marc Laszlo");

}

void testAll::testGetLink()
{
	Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	assert(testingTutorial.getLink() == "https://www.youtube.com/watch?v=Rub-JsjMhWY");

}

void testAll::testGetLikes()
{

	Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	assert(testingTutorial.getLikes() == 123000);

}

void testAll::testGetDuration()
{
	Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	int hours, minutes, seconds;
	std::tie(hours, minutes, seconds) = testingTutorial.getDuration();
	assert(hours == 12);
	assert(minutes == 30);
	assert(seconds == 45);
}

void testAll::testAllTutorial()
{
	testSetTitle();
	testSetPresenter();
	testSetLink();
	testSetLikes();
	testSetDuration();
	testGetDuration();
	testGetLikes();
	testGetLink();
	testGetPresenter();
	testGetTitle();
}

void testAll::testValidateTitle()
{
	assert(Validator::validateTitle("Valid Title") == true);
	assert(Validator::validateTitle("Invalid123 Title") == false);
	assert(Validator::validateTitle("") == true);
}

void testAll::testValidatePresenter()
{
	assert(Validator::validatePresenter("Valid Presenter") == true);
	assert(Validator::validatePresenter("Invalid123 Presenter") == false);
	assert(Validator::validatePresenter("") == true);
}

void testAll::testValidateDuration()
{
	Validator* testValidator = new Validator();
	string validDuration = "12:45:46";
	int hours = 0, minutes = 0, seconds = 0;
	tie(hours, minutes, seconds) = testValidator->validateDuration(validDuration);
	assert(hours == 12);
	assert(minutes == 45);
	assert(seconds == 46);
	string invalidDuration = "12:35:100";
	int hours2, minutes2, seconds2;
	tie(hours2, minutes2, seconds2) = testValidator->validateDuration(invalidDuration);
	assert(hours2 == -1);
	assert(minutes2 == -1);
	assert(seconds2 == -1);
	string invalidDuration2 = "12:-1:-2";
	int hours3, minutes3, seconds3;
	tie(hours3, minutes3, seconds3) = testValidator->validateDuration(invalidDuration2);
	assert(hours3 == -1);
	assert(minutes3 == -1);
	assert(seconds3 == -1);
	string invalidDuration3 = "10:bb:12";
	int hours4, minutes4, seconds4;
	tie(hours4, minutes4, seconds4) = testValidator->validateDuration(invalidDuration3);
	assert(hours4 == -1);
	assert(minutes4 == -1);
	assert(seconds4 == -1);
	string invalidDuration4 = "12-67-10";
	int hours5, minutes5, seconds5;
	tie(hours5, minutes5, seconds5) = testValidator->validateDuration(invalidDuration);
	assert(hours5 == -1);
	assert(minutes5 == -1);
	assert(seconds5 == -1);
	string invalidDuration5 = "10::";
	int hours6, minutes6, seconds6;
	tie(hours6, minutes6, seconds6) = testValidator->validateDuration(invalidDuration);
	assert(hours6 == -1);
	assert(minutes6 == -1);
	assert(seconds6 == -1);
	string invalidDuration6 = "11:10:bb";
	int hours7, minutes7, seconds7;
	tie(hours7, minutes7, seconds7) = testValidator->validateDuration(invalidDuration);
	assert(hours7 == -1);
	assert(minutes7 == -1);
	assert(seconds7 == -1);
	string invalidDuration7 = "bb:10:12";
	int hours8, minutes8, seconds8;
	tie(hours8, minutes8, seconds8) = testValidator->validateDuration(invalidDuration);
	assert(hours8 == -1);
	assert(minutes8 == -1);
	assert(seconds8 == -1);
	string invalidDuration8 = "10:100:10";
	int hours9, minutes9, seconds9;
	tie(hours9, minutes9, seconds9) = testValidator->validateDuration(invalidDuration);
	assert(hours9 == -1);
	assert(minutes9 == -1);
	assert(seconds9 == -1);
	delete testValidator;
}

void testAll::testValidateLikes()
{
	Validator* testValidator = new Validator();
	string validLikes = "123000";
	assert(testValidator->validateLikes(validLikes) == 123000);
	string invalidLikes = "abvajfa";
	assert(testValidator->validateLikes(invalidLikes) == -1);
	delete testValidator;

}

void testAll::testValidateLink()
{
	Validator* testValidator = new Validator();
	string validLink = "https://www.youtube.com/watch?v=vLnPwxZdW4Y";
	assert(testValidator->validateLink(validLink));
	string invalidLink = "hwatch?v=vLnPwxZdW4Y";
	assert(!testValidator->validateLink(invalidLink));
	delete testValidator;
}

void testAll::testAllValidate()
{
	testValidateTitle();
	testValidatePresenter();
	testValidateDuration();
	testValidateLikes();
	testValidateLink();
}

void testAll::testAbsolutelyEverything()
{
	testAllRepo();
	testAllService();
	testAllTutorial();
	testAllValidate();
}

void testAll::testAddRepo()
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

void testAll::testCheckTutorialExistence()
{
	Repository testRepo;
	testRepo.addRepo("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	assert(testRepo.checkTutorialExistence("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY") == 0);
	assert(testRepo.checkTutorialExistence("C++ with John", "Marc", "https://www.youtube.com/watch?v=Rub-JsjMhWX") == -1);

}

void testAll::testDeleteTutorial()
{
	Repository testRepo;
	testRepo.addRepo("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	assert(testRepo.deleteTutorialRepo("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY") == true);
	assert(testRepo.deleteTutorialRepo("C++ with John", "Marc", "https://www.youtube.com/watch?v=Rub-JsjMhWX") == false);

}

void testAll::testUpdateLikes()
{
	Repository testRepo;
	testRepo.addRepo("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	assert(testRepo.updateLikesRepo("C++ with Marc", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 146000) == true);
	assert(testRepo[0].getLikes() == 146000);
	assert(testRepo.updateLikesRepo("C++ with John", "Marc Laszlo", "https://www.youtube.com/watch?v=Rub-JsjMhWY", 146000) == false);

}

void testAll::testUpdateDuration()
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

void testAll::testAllRepo()
{
	testGetArray();
	testAddRepo();
	testCheckTutorialExistence();
	testDeleteTutorial();
	testGetSize();
	testInitializeRepo();
	testUpdateDuration();
	testUpdateLikes();

}
