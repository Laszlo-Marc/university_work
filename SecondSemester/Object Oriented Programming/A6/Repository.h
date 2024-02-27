#pragma once
#include "Tutorial.h"
#include <string>
#include <vector>
class Repository {
protected:
	vector<Tutorial> tutorials;
public:
	Repository();
	Repository(const vector<Tutorial>& array);
	~Repository();
	void initializeRepo();
	int getSize();
	vector<Tutorial>& getArray();
	bool addRepo(string title, string presenter, int hours, int minutes, int seconds, string link, int likes);
	int checkTutorialExistence(string title, string presenter, string link);
	bool deleteTutorialRepo(string presenter, string title, string link);
	bool updateDurationRepo(string title, string presenter, string link, int hours, int minutes, int seconds);
	bool updateLikesRepo(string title, string presenter, string link, int likes);

	Tutorial& operator[](int position) {
		return this->tutorials[position];
	}


};