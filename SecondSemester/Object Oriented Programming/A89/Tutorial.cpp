#include "Tutorial.h"
#include <tuple>
#include <iostream>
#include <sstream>
#include <vector>
Tutorial::Tutorial(const Tutorial& copyTutorial)
{
	this->title = copyTutorial.title;
	this->presenter = copyTutorial.presenter;
	this->hours = copyTutorial.hours;
	this->minutes = copyTutorial.minutes;
	this->seconds = copyTutorial.seconds;
	this->link = copyTutorial.link;
	this->likes = copyTutorial.likes;
}

Tutorial& Tutorial::operator=(const Tutorial& copyTutorial)
{
	this->title = copyTutorial.title;
	this->presenter = copyTutorial.presenter;
	this->hours = copyTutorial.hours;
	this->minutes = copyTutorial.minutes;
	this->seconds = copyTutorial.seconds;
	this->link = copyTutorial.link;
	this->likes = copyTutorial.likes;
	return *this;
}

Tutorial::Tutorial(string title, string presenter, int hours, int minutes, int seconds, string link, int likes)
{
	this->title = title;
	this->presenter = presenter;
	this->hours = hours;
	this->minutes = minutes;
	this->seconds = seconds;
	this->link = link;
	this->likes = likes;
}


string Tutorial::getTitle() const
{

	return this->title;
}

string Tutorial::getPresenter() const
{
	return this->presenter;
}

std::tuple<int, int, int>Tutorial::getDuration() const
{
	return std::make_tuple(this->hours, this->minutes, this->seconds); ;
}

string Tutorial::getLink() const
{
	return this->link;
}

int Tutorial::getLikes() const
{
	return this->likes;
}

vector<string> tokenize(string str, char delimiter)
{
	vector <string> result;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

ostream& operator<<(ostream& os, const Tutorial& tutorial)
{
	os << tutorial.title << "|" << tutorial.presenter << "|" << tutorial.hours << "|" << tutorial.minutes << "|" << tutorial.seconds << "|" << tutorial.link << "|" << tutorial.likes << endl;
	return os;
}

istream& operator>>(istream& is, Tutorial& tutorial)
{

	string line;
	getline(is, line);

	vector<string> tokens = tokenize(line, '|');
	if (tokens.size() != 7)
		return is;
	tutorial.title = tokens[0];
	tutorial.presenter = tokens[1];
	tutorial.hours = stoi(tokens[2]);
	tutorial.minutes = stoi(tokens[3]);
	tutorial.seconds = stoi(tokens[4]);
	tutorial.link = tokens[5];
	tutorial.likes = stoi(tokens[6]);
	return is;
}
