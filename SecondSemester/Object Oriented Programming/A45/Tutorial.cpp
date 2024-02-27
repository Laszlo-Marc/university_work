#include "Tutorial.h"
#include <tuple>

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

Tutorial::Tutorial(string title, string presenter,int hours,int minutes,int seconds, string link, int likes)
{
	this->title = title;
	this->presenter = presenter;
	this->hours = hours;
	this->minutes = minutes;
	this->seconds = seconds;
	this->link = link;
	this->likes = likes;
}

void Tutorial::setTitle(string title)
{
	this->title = title;
}

void Tutorial::setPresenter(string presenter)
{
	this->presenter = presenter;
}

void Tutorial::setDuration(int hours,int minutes,int seconds)
{
	this->hours = hours;
	this->minutes = minutes;
	this->seconds = seconds;
}

void Tutorial::setLink(string link)
{
	this->link = link;
}

void Tutorial::setLikes(int likes)
{
	this->likes = likes;
}

string Tutorial::getTitle()
{
	
	return this->title;
}

string Tutorial::getPresenter()
{
	return this->presenter;
}

std::tuple<int,int,int>Tutorial::getDuration()
{
	return std::make_tuple(this->hours,this->minutes,this->seconds); ;
}

string Tutorial::getLink()
{
	return this->link;
}

int Tutorial::getLikes()
{
	return this->likes;
}
