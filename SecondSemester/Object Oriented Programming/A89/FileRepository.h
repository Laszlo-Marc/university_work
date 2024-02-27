#pragma once
#include "Repository.h"

class FileRepository : public Repository {
protected:
	string fileName;
public:
	FileRepository(string fileName, string userRepoFile) :Repository{ userRepoFile } { this->fileName = fileName; }
	virtual ~FileRepository() {};

	virtual void writeToFile() = 0;
	virtual void displayTutorials() = 0;
};