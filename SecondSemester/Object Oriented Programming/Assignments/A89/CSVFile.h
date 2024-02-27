#pragma once
#include "FileRepository.h"

class CSVFile : public FileRepository {
public:
	CSVFile(string fileName, string userRepoFile) :FileRepository(fileName, userRepoFile) { this->writeToFile(); }
	~CSVFile() {}
	void writeToFile() override;
	void displayTutorials() override;
};