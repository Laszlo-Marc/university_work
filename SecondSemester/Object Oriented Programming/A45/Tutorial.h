#pragma once
#include <string>
#include <iostream>
using namespace std;
class Tutorial {
private:
	string title;
	string presenter;
	int likes;
	string link;
	int hours;
	int minutes;
	int seconds;
public:

	Tutorial(const Tutorial& copyTutorial);
	Tutorial& operator=(const Tutorial& copyTutorial);
	Tutorial(string title="empty", string presenter = "empty", int hours=0, int minutes=0, int seconds=0, string link="empty", int likes=0);
	void setTitle(string title);
	void setPresenter(string presenter);
	void setDuration(int hours,int minutes,int seconds);
	void setLink(string link);
	void setLikes(int likes);
	string getTitle();
	string getPresenter();
	std::tuple<int,int, int>Tutorial::getDuration();
	string getLink();
	int getLikes();
};