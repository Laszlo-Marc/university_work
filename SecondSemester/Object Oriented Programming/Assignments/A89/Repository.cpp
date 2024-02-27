#include "Repository.h"
#include <cstring>
#include <iostream>
#include <tuple>
#include <fstream>
#include "Exceptions.h"
void Repository::loadData()
{
	ifstream inFile(this->FileName);
	if (!inFile.is_open())
		throw runtime_error("File not open");
	Tutorial currentElement;
	while (inFile >> currentElement) {
		this->tutorials.push_back(currentElement);
	}
	inFile.close();
}
void Repository::writeToFile()
{
	ofstream outFile(this->FileName);
	if (!outFile.is_open()) {
		throw runtime_error("File not open");
	}
	for (Tutorial tutorial : this->tutorials) {
		outFile << tutorial;
	}
	outFile.close();
}


Repository::Repository(const string& FileName)
{
	this->FileName = FileName;
	this->loadData();
}

int Repository::getSize()
{
	return this->tutorials.size();
}

vector<Tutorial>& Repository::getArray()
{
	return this->tutorials;
}



void Repository::addRepo(string title, string presenter, int hours, int minutes, int seconds, string link, int likes)
{
	int position;
	position = checkTutorialExistence(title, presenter, link);
	if (position == -1) {
		Tutorial tutorial(title, presenter, hours, minutes, seconds, link, likes);
		tutorials.push_back(tutorial);

	}
	else
		throw ExceptionsRepository("The tutorial already exists!");
	this->writeToFile();
}

int Repository::checkTutorialExistence(string title, string presenter, string link)
{
	auto position = find_if(tutorials.begin(), tutorials.end(), [&](const Tutorial& tutorial) {
		return tutorial.getTitle() == title && tutorial.getPresenter() == presenter && tutorial.getLink() == link;
		});

	if (position != tutorials.end()) {
		return distance(tutorials.begin(), position);
	}

	return -1;
}

void Repository::deleteTutorialRepo(string title, string presenter, string link)
{
	int position;
	position = checkTutorialExistence(title, presenter, link);
	if (position != -1)
	{
		this->tutorials.erase(this->tutorials.begin() + position);

	}
	else
		throw ExceptionsRepository("The tutorial doesn't exist!");
	this->writeToFile();
}

void Repository::updateDurationRepo(string title, string presenter, string link, int hours, int minutes, int seconds)
{
	int position;
	position = checkTutorialExistence(title, presenter, link);
	if (position != -1) {
		int likes = this->tutorials[position].getLikes();
		Tutorial tutorial(title, presenter, hours, minutes, seconds, link, likes);
		this->tutorials[position] = tutorial;

	}
	throw ExceptionsRepository("The tutorial doesn't exist!");
	this->writeToFile();
}

void Repository::updateLikesRepo(string title, string presenter, string link, int likes)
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

	}
	else
		throw ExceptionsRepository("The tutorial doesn't exist!");
	this->writeToFile();
}

Repository& Repository::operator=(const Repository& repository)
{
	if (&repository == this) {
		return *this;
	}
	this->tutorials = repository.tutorials;
	this->writeToFile();
	return *this;
}
