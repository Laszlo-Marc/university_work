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
	Tutorial(string title = "empty", string presenter = "empty", int hours = 0, int minutes = 0, int seconds = 0, string link = "empty", int likes = 0);
	string getTitle() const;
	string getPresenter() const;
	std::tuple<int, int, int>getDuration() const;
	string getLink() const;
	int getLikes() const;

	friend ostream& operator<<(ostream& is, const Tutorial& tutorial);
	friend istream& operator>>(istream& os, Tutorial& tutorial);

};