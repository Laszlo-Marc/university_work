#include "CSVFile.h"
#include <fstream>
#include <Windows.h>
void CSVFile::writeToFile()
{
	ofstream CSVOutFile(this->fileName);

	if (!CSVOutFile.is_open())
		throw runtime_error("File not open\n");

	for (Tutorial tutorial : this->getArray()) {
		CSVOutFile << tutorial;
	}

	CSVOutFile.close();
}

void CSVFile::displayTutorials()
{
	ShellExecuteA(NULL, NULL, "C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE", this->fileName.c_str(), NULL, SW_SHOWMAXIMIZED);

}
