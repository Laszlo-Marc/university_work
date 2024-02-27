#include "HTMLFile.h"
#include <fstream>
#include <tuple>
#include <Windows.h>
void HTMLFile::writeToFile()
{
	ofstream outFile(this->fileName);
	if (outFile.is_open() == false)
	{
		throw runtime_error("File not open\n");
	}
	outFile << "<!DOCTYPE html>    <!-- write this exactly as it is here -->\n";
	outFile << "<html> <!-- write this exactly as it is here -->\n";
	outFile << "<head> <!--write this exactly as it is here-->\n";
	outFile << "\t<title>EventList</title>\n";
	outFile << "</head> <!--write this exactly as it is here(close head tag)-->\n";
	outFile << "<body> <!--write this exactly as it is here-->\n";
	outFile << "<table border = \"1\"> <!--write this exactly as it is here-->\n";
	outFile << "\t<tr>\n";
	outFile << "\t\t<td>Title</td>\n";
	outFile << "\t\t<td>Presenter</td>\n";
	outFile << "\t\t<td>Duration</td>\n";
	outFile << "\t\t<td>Link</td>\n";
	outFile << "\t\t<td>Likes</td>\n";
	outFile << "\t</tr>\n";
	for (Tutorial tutorial : this->getArray())
	{
		int hours, minutes, seconds;
		std::tie(hours, minutes, seconds) = tutorial.getDuration();
		outFile << "\t<tr>\n";
		outFile << "\t\t<td>" << tutorial.getTitle() << "</td>\n";
		outFile << "\t\t<td>" << tutorial.getPresenter() << "</td>\n";
		outFile << "\t\t<td>" << hours << ":" << minutes << ":" << seconds << "</td>\n";
		outFile << "\t\t<td>" << tutorial.getLink() << "</td>\n";
		outFile << "\t\t<td>" << tutorial.getLikes() << "</td>\n";
		outFile << "\t</tr>\n";
	}
	outFile << "</table>\n";
	outFile << "</body>\n";
	outFile << "</html>\n";
	outFile.close();
}

void HTMLFile::displayTutorials()
{

	ShellExecute(NULL, "open", "UserFile.html", NULL, NULL, SW_SHOWNORMAL);

}
