#include <crtdbg.h>
#include "UI.h"
#include "CSVFile.h"
#include "HTMLFile.h"
#include "Repository.h"
int run() {
	try
	{
		Repository repository("tutorials.txt");
		FileRepository* tutorialsFile = nullptr;
		cout << "Choose file type(HTML/CSV):\n";
		string fileType;
		cin >> fileType;
		while (fileType != "HTML" && fileType != "CSV")
		{
			cout << "Invalid type,try again: \n";
			cin >> fileType;
		}
		if (fileType == "HTML")
			tutorialsFile = new HTMLFile{ "UserFile.html", "UserFile.txt" };
		else
			tutorialsFile = new CSVFile{ "UserFile.csv", "UserFile.txt" };
		Service service(repository, tutorialsFile);
		Validator validator;
		UI ui(service,validator);
		ui.Start();
		delete tutorialsFile;
		return 0;
	}
	catch (exception exception)
	{
		cout << exception.what();
		return 1;
	}
	
}

int main() {
	run();
	_CrtDumpMemoryLeaks();

	return 0;

}