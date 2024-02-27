#pragma once
#include "FileRepository.h"

class HTMLFile : public FileRepository
{
public:
	HTMLFile(std::string fileName, std::string userRepositoryFile) : FileRepository(fileName, userRepositoryFile) { this->writeToFile(); }
	~HTMLFile() {};

	void writeToFile() override;
	void displayTutorials() override;
};