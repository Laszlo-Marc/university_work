#pragma once
#include "Tutorial.h"
#include <string>
#include <vector>
class Repository {
private:
	vector<Tutorial> tutorials;
	string FileName;
	void loadData();
	void writeToFile();
public:
	virtual ~Repository();
	Repository(const string& FileName);
	int getSize();
	vector<Tutorial>& getArray();
	void addRepo(string title, string presenter, int hours, int minutes, int seconds, string link, int likes);
	int checkTutorialExistence(string title, string presenter, string link);
	void deleteTutorialRepo(string pr2esenter, string title, string link);
	void updateDurationRepo(string title, string presenter, string link, int hours, int minutes, int seconds);
	void updateLikesRepo(string title, string presenter, string link, int likes);
	Repository& operator=(const Repository& repository);

};