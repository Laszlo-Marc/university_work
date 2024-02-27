#include "Repository.h"
#include <cstring>
#include <iostream>
#include <tuple>

Repository::Repository()
{}

Repository::Repository(const vector<Tutorial>& vector) :tutorials{ vector }
{

}

Repository::~Repository() = default;



void Repository::initializeRepo()
{
	addRepo("Java Tutorial for Beginners: Object-Oriented Programming", "Derek Banas", 1, 35, 45, "https://www.youtube.com/watch?v=kJzB8DvH5Oc", 1200000);
	addRepo("Python Tutorial: Object-Oriented Programming", "Derek Banas", 1, 10, 14, "https://www.youtube.com/watch?v=5-daZoKgUcA", 610000);
	addRepo("C++ Tutorial: Object-Oriented Programming", "Derek Banas", 1, 49, 56, "https://www.youtube.com/watch?v=Rub-JsjMhWY", 1400000);
	addRepo("JavaScript Tutorial: Object-Oriented Programming", "Derek Banas", 1, 17, 13, "https://www.youtube.com/watch?v=PFmuCDHHpwk", 1000000);
	addRepo("Python OOP Tutorial: Classes and Objects", "Corey Schafer", 1, 12, 8, "https://www.youtube.com/watch?v=ZDa-Z5JzLYM", 1500000);
	addRepo("Python OOP Tutorial: Inheritance", "Corey Schafer", 1, 2, 9, "https://www.youtube.com/watch?v=RSl87lqOXDE", 7200000);
	addRepo("Python OOP Tutorial: Special (Magic/Dunder) Methods", "Corey Schafer", 0, 55, 5, "https://www.youtube.com/watch?v=3ohzBxoFHAY", 8300000);
	addRepo("Python OOP Tutorial: Property Decorators - Getters, Setters, and Deleters", "Corey Schafer", 0, 26, 7, "https://www.youtube.com/watch?v=jCzT9XFZ5bw", 550000);
	addRepo("C# OOP Tutorial - Object Oriented Programming", "Mosh Hamedani", 2, 6, 10, "https://www.youtube.com/watch?v=HF1luRD4Qmk", 1600000);
	addRepo("C# Tutorial for Beginners: Learn C# from Scratch", "Mosh Hamedani", 6, 2, 12, "https://www.youtube.com/watch?v=gfkTfcpWqAY", 2500000);
	addRepo("Python OOP Tutorial: Object Oriented Programming for Beginners", "Mosh Hamedani", 1, 33, 0, "https://www.youtube.com/watch?v=JeznW_7DlB0", 2600000);
	addRepo("Java Tutorial for Beginners: Learn Java Programming", "Mosh Hamedani", 4, 57, 0, "https://www.youtube.com/watch?v=eIrMbAQSU34", 3000000);
	addRepo("Java OOP Tutorial - Part 1 | Object Oriented Programming Tutorial for Beginners | Java Training", "Telusko", 1, 41, 0, "https://www.youtube.com/watch?v=kgJskQgFSck", 1100000);
	addRepo("Java OOP Tutorial - Part 2 | Abstraction and Encapsulation in Java | Java Tutorial for Beginners", "Telusko", 0, 43, 0, "https://www.youtube.com/watch?v=zH9gK7VJuLw", 420000);
}

int Repository::getSize()
{
	return this->tutorials.size();
}

vector<Tutorial>& Repository::getArray()
{
	return this->tutorials;
}



bool Repository::addRepo(string title, string presenter, int hours, int minutes, int seconds, string link, int likes)
{
	int position;
	position = checkTutorialExistence(title, presenter, link);
	if (position == -1) {
		Tutorial tutorial(title, presenter, hours, minutes, seconds, link, likes);
		tutorials.push_back(tutorial);
		return true;
	}
	return false;}

int Repository::checkTutorialExistence(string title, string presenter, string link)
{
	auto position = find_if(tutorials.begin(), tutorials.end(), [&](const Tutorial& tutorial) {
		return tutorial.getTitle() == title && tutorial.getPresenter() == presenter && tutorial.getLink() == link;
		});

	if (position != tutorials.end()) {
		return distance(tutorials.begin(), position);
	}

	return -1;}

bool Repository::deleteTutorialRepo(string title, string presenter, string link)
{
	int position;
	position = checkTutorialExistence(title, presenter, link);
	if (position != -1)
	{
		this->tutorials.erase(this->tutorials.begin() + position);
		return true;}
	else
		return false;}

bool Repository::updateDurationRepo(string title, string presenter, string link, int hours, int minutes, int seconds)
{
	int position;
	position = checkTutorialExistence(title, presenter, link);
	if (position != -1) {
		int likes = this->tutorials[position].getLikes();
		Tutorial tutorial(title, presenter, hours, minutes, seconds, link, likes);
		this->tutorials[position] = tutorial;
		return true;}
	return false;}

bool Repository::updateLikesRepo(string title, string presenter, string link, int likes)
{
	int position;
	position = checkTutorialExistence(title, presenter, link);
	if (position != -1) {
		int minutes = 0;
		int seconds = 0;
		int hours = 0;
		std::tie(hours, minutes, seconds) = this->tutorials[position].getDuration();
		Tutorial tutorial(title, presenter, hours, minutes, seconds, link, likes);
		this->tutorials[position] = tutorial;
		return true;}
	else
		return false;}
