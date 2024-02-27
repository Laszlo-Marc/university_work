#include "TestTutorial.h"
#include "Tutorial.h"
#include <assert.h>
#include <tuple>
using namespace std;

void testTutorial::testSetTitle()
{
	Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	testingTutorial.setTitle("C++ with John69");
	assert(testingTutorial.getTitle() == "C++ with John69");
}

void testTutorial::testSetPresenter()
{
	Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	testingTutorial.setPresenter("John69");
	assert(testingTutorial.getPresenter() == "John69");
}

void testTutorial::testSetLink()
{
	Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	testingTutorial.setLink("https://www.youtube.com/watch?v=Rub-JsjMhWX");
	assert(testingTutorial.getLink() == "https://www.youtube.com/watch?v=Rub-JsjMhWX");
}

void testTutorial::testSetLikes()
{
	Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	testingTutorial.setLikes(69000);
	assert(testingTutorial.getLikes() == 69000);
}

void testTutorial::testSetDuration()
{
	Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	testingTutorial.setDuration(69,36,17);
	int hours, minutes, seconds;
	std::tie(hours, minutes, seconds) = testingTutorial.getDuration();
	assert(hours == 69);
	assert(minutes == 36);
	assert(seconds == 17);
}

void testTutorial::testGetTitle()
{
	Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	assert(testingTutorial.getTitle() == "C++ with Marc");
}

void testTutorial::testGetPresenter()
{
	Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	assert(testingTutorial.getPresenter() == "Marc Laszlo");
}

void testTutorial::testGetLink()
{
	Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	assert(testingTutorial.getLink() == "https://www.youtube.com/watch?v=Rub-JsjMhWY");
}

void testTutorial::testGetLikes()
{
	Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	assert(testingTutorial.getLikes() == 123000);
}

void testTutorial::testGetDuration()
{
	Tutorial testingTutorial("C++ with Marc", "Marc Laszlo", 12, 30, 45, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 123000);
	int hours, minutes, seconds;
	std::tie(hours, minutes, seconds) = testingTutorial.getDuration();
	assert(hours == 12);
	assert(minutes == 30);
	assert(seconds == 45);
}

void testTutorial::testAllTutorial()
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
