#include "Ui.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <tuple>
#include <atlstr.h>
#include <algorithm>
using namespace std;

constexpr auto CHOOSE_ADMIN = 1;
constexpr auto CHOOSE_USER = 2;
constexpr auto EXIT = 0;
constexpr auto DISPLAY_MENU = 9;
constexpr auto ADD_ADMIN = 1;
constexpr auto DISPLAY_ADMIN = 2;
constexpr auto DELETE_ADMIN = 3;
constexpr auto UPDATE_LIKES = 4;
constexpr auto UPDATE_DURATION = 5;
constexpr auto DISPLAY_USER_PRESENTER = 1;
constexpr auto ADD_USER = 2;
constexpr auto DELETE_USER = 3;
constexpr auto DISPLAY_USER = 4;

UI::UI()
{
}

UI::~UI()
{
}

UI::UI(const Service& copyService, const Validator& copyValidator) :service{ service }, validator{ validator }
{
}



void UI::Start()
{
	bool Done = false;
	this->service.initializeRepo();
	while (!Done)
	{
		int command;
		cout << "Type 1 for Administrator Mode, type 2 for User Mode or 0 to exit:  ";
		cin >> command;
		cout << '\n';
		if (command != CHOOSE_ADMIN && command != CHOOSE_USER && command != EXIT) {
				cout << "Invalid command!\n";
				cin.clear(); 
				
		}	
		else
			switch (command)
			{
			case CHOOSE_ADMIN:
				AdministratorMode();
				break;

			case CHOOSE_USER:
				UserMode();
				break;

			case EXIT:
				Done = true;
				break;
			}

	}
}

//Administrator Side
void UI::AdministratorMode()
{
	bool AdministratorMode = false;
	MenuAdminMode();
	while (AdministratorMode == false)
	{
		int command;
		cout << "\nCommand: ";
		cin >> command;
		if (command != ADD_ADMIN && command != DISPLAY_ADMIN && command != DELETE_ADMIN && command != UPDATE_LIKES && command != UPDATE_DURATION &&
			command != EXIT && command != DISPLAY_MENU) {
					cout << "Invalid command!\n";
					cin.clear();
		}
			
		else
			switch (command)
			{

			case ADD_ADMIN:
				AddTutorialAdminMode();
				break;

			case DISPLAY_ADMIN:
				DisplayTutorialsAdmin();
				break;

			case DELETE_ADMIN:
				DeleteTutorialAdminMode();
				break;

			case UPDATE_LIKES:
				UpdateTutorialLikesAdmin();
				break;

			case UPDATE_DURATION:
				UpdateTutorialDurationAdmin();
				break;

			case DISPLAY_MENU:
				MenuAdminMode();
				break;

			case EXIT:
				AdministratorMode = true;
				break;
			}

	}

}

void UI::MenuAdminMode()
{
	cout << "1.Add a tutorial\n";
	cout << "2.Display tutorials\n";
	cout << "3.Delete a tutorial\n";
	cout << "4.Update the likes of a tutorial\n";
	cout << "5.Update the duration of a tutorial\n";
	cout << "9.Display the menu\n";
	cout << "0.Exit the program\n";
}

void UI::UpdateTutorialLikesAdmin()
{
	string title;
	string presenter;
	string link;
	string likesInString;
	int likes;
	cin.ignore();
	cout << "Type in the title: ";
	getline(std::cin, title);
	cout << "\nType in the presenter: ";
	getline(std::cin, presenter);
	cout << "\nType in the link: ";
	getline(std::cin, link);
	cout << "\nType in the new likes: ";
	cin >> likesInString;
	likes = this->validator.validateLikes(likesInString);
	if (!this->validator.validateTitle(title) || !this->validator.validatePresenter(presenter) || !this->validator.validateLink(link))
		cout << "Invalid input!\n";
	else {
		if (this->service.UpdateLikesService(title, presenter, link, likes) == true)
			cout << "Likes updated succesfully\n";
		else
			cout << "The tutorial doesn't exist!\n";

	}
}

void UI::UpdateTutorialDurationAdmin()
{
	string title;
	string presenter;
	string link;
	string durationInString;
	int hours, minutes, seconds;
	cin.ignore();
	cout << "Type in the title: ";
	getline(std::cin, title);
	cout << "\nType in the presenter: ";
	getline(std::cin, presenter);
	cout << "\nType in the link: ";
	getline(std::cin, link);
	cout << "\nType in the new duration: ";
	cin >> durationInString;
	std::tie(hours, minutes, seconds) = this->validator.validateDuration(durationInString);
	if (!this->validator.validateTitle(title) || !this->validator.validatePresenter(presenter) || !this->validator.validateLink(link))
		cout << "Invalid input!\n";
	else {
		if (this->service.UpdateDurationService(title, presenter, link, hours, minutes, seconds) == true)
			cout << "Duration updated successfully\n";
		else
			cout << "The tutorial doesn't exist!\n";

	}

}

void UI::DeleteTutorialAdminMode()
{
	string title;
	string presenter;
	string link;
	cin.ignore();
	cout << "Type in the title: ";
	getline(std::cin, title);
	cout << "\nType in the presenter: ";
	getline(std::cin, presenter);
	cout << "\nType in the link: ";
	getline(std::cin, link);
	if (!this->validator.validateTitle(title) || !this->validator.validatePresenter(presenter) || !this->validator.validateLink(link))
		cout << "Invalid input!\n";
	else {
		if (this->service.DeleteService(title, presenter, link, 1) == true)
			cout << "The tutorial was deleted successfully!\n";
		else
			cout << "The tutorial doesn't exist!\n";

	}
}

void UI::DisplayTutorialsAdmin()
{
	int tutorialNumber = 1;
	for (const auto& tutorial : this->service.GetRepository()) {
		int minutes = 0;
		int seconds = 0;
		int hours = 0;
		std::tie(hours, minutes, seconds) = tutorial.getDuration();
		cout << tutorialNumber << ")  ""Title: " << tutorial.getTitle() << " Presenter: " <<
			tutorial.getPresenter() << " Duration:  " << hours << ":" << minutes << ":" << seconds
			<< " Likes: " << tutorial.getLikes() << "\nLink: "
			<< tutorial.getLink() << "\n" << "\n";
		tutorialNumber++;
	}
}

void UI::AddTutorialAdminMode()
{
	string title, presenter, link, durationInString, likesInString;
	int likes, hours, minutes, seconds;
	cin.ignore();
	cout << "Type in the title: ";
	getline(std::cin, title);
	cout << "\nType in the presenter: ";
	getline(std::cin, presenter);
	cout << "\nType in the link: ";
	getline(std::cin, link);
	cout << "\nType in the number of likes: ";
	cin >> likesInString;
	cin.ignore();
	cout << "\nEnter the duration of the video in minutes and seconds (hh:mm:ss): ";
	getline(std::cin, durationInString);
	tie(hours, minutes, seconds) = this->validator.validateDuration(durationInString);
	likes = this->validator.validateLikes(likesInString);
	if (!this->validator.validateTitle(title) || !this->validator.validatePresenter(presenter) || !this->validator.validateLink(link) || likes == -1 || hours == -1 || minutes == -1 || seconds == -1) {
		cout << "\nInvalid input!";
	}
	else {
		if (this->service.AddService(title, presenter, link, likes, hours, minutes, seconds, 1) == true) {
			cout << "\nThe tuorial has been successfully added!";
		}
		else {
			cout << "\nTutorial already exists!";
		}
	}
}

//User side

void UI::UserMode()
{
	bool UserMode = false;
	UserMenu();
	while (UserMode == false)
	{
		int command;
		cout << "\nCommand: ";
		cin >> command;
		
		if (command != DISPLAY_USER_PRESENTER && command != ADD_USER && command != DELETE_USER && command != DISPLAY_USER &&
			command != EXIT && command != DISPLAY_MENU){
			cout << "Invalid command!\n";
			cin.clear();
		}
		else
			switch (command)
			{

			case DISPLAY_USER_PRESENTER:
				DisplayTutorialsFromGivenPresenter();
				break;

			case ADD_USER:
				AddTutorialToWatchList();
				break;

			case DELETE_USER:
				DeleteTutorialFromWatchList();
				break;

			case DISPLAY_USER:
				DisplayTheWatchList();
				break;

			case DISPLAY_MENU:
				UserMenu();
				break;

			case EXIT:
				UserMode = true;
				break;
			}

	}
}

void UI::UserMenu()
{
	cout << "1.Display tutorials from a given presenter\n";
	cout << "2.Add a tutorial to your watchlist\n";
	cout << "3.Delete a tutorial from the watchlist\n";
	cout << "4.Display the watchlist\n";
	cout << "9.Display menu\n";
	cout << "0.Exit\n";
}

void UI::DisplayTutorialsFromGivenPresenter()
{
	string presenter;
	int presenterCount = 0;
	cin.ignore();
	cout << "From which presenter do you want to see tutorials: ";
	getline(std::cin, presenter);
	if (this->validator.validatePresenter(presenter)) {
		for (const auto& tutorial : this->service.GetRepository()) {
			if (tutorial.getPresenter() == presenter) {
				presenterCount++;
				int minutes = 0;
				int seconds = 0;
				int hours = 0;
				std::tie(hours, minutes, seconds) = tutorial.getDuration();
				cout << presenterCount << ")  ""Title: " << tutorial.getTitle() << " Presenter: " <<
					tutorial.getPresenter() << " Duration:  " << hours << ":" << minutes << ":" << seconds
					<< " Likes: " << tutorial.getLikes() << "\nLink: "
					<< tutorial.getLink() << "\n" << "\n";
				cout << "Press 'n' to go to the next tutorial, or 'w' to add it to your watchlist and then play it: ";
				char choice;
				cin >> choice;
				if (choice == 'w') {
					this->service.AddService(tutorial.getTitle(), presenter, tutorial.getLink(), tutorial.getLikes(), hours, minutes, seconds, 2);
					cout << "Tutorial added to watchlist!\n";
					CString cstr(tutorial.getLink().c_str());
					ShellExecute(nullptr, "open", cstr, nullptr, nullptr, SW_SHOWNORMAL);
				}
				else {
					CString cstr(tutorial.getLink().c_str());
					ShellExecute(nullptr, "open", cstr, nullptr, nullptr, SW_SHOWNORMAL);
				}

			}


		}
	}
	if (presenterCount == 0)
		DisplayTutorialsAdmin();
}

void UI::AddTutorialToWatchList()
{
	string title, presenter, link, durationInString, likesInString;
	int likes, hours, minutes, seconds;
	cin.ignore();
	cout << "Type in the title: ";
	getline(std::cin, title);
	cout << "\nType in the presenter: ";
	getline(std::cin, presenter);
	cout << "\nType in the link: ";
	getline(std::cin, link);
	cout << "\nType in the number of likes: ";
	cin >> likesInString;
	cin.ignore();
	cout << "\nEnter the duration of the video in minutes and seconds (hh:mm:ss): ";
	getline(std::cin, durationInString);
	tie(hours, minutes, seconds) = this->validator.validateDuration(durationInString);
	likes = this->validator.validateLikes(likesInString);
	if (!this->validator.validateTitle(title) || !this->validator.validatePresenter(presenter) || !this->validator.validateLink(link) || likes == -1 || hours == -1 || minutes == -1 || seconds == -1) {
		cout << "\nInvalid input!";
	}
	else {
		if (this->service.AddService(title, presenter, link, likes, hours, minutes, seconds, 2) == true) {
			cout << "\nThe tuorial has been successfully added!";
		}
		else {
			cout << "\nTutorial already exists!";
		}
	}
}

void UI::DeleteTutorialFromWatchList()
{
	string title;
	string presenter;
	string link;
	int likes = 0;
	cin.ignore();
	cout << "Type in the title: ";
	getline(std::cin, title);
	cout << "\nType in the presenter: ";
	getline(std::cin, presenter);
	cout << "\nType in the link: ";
	getline(std::cin, link);
	if (!this->validator.validateTitle(title) || !this->validator.validatePresenter(presenter) || !this->validator.validateLink(link))
		cout << "Invalid input!\n";
	else {
		string choice;
		cout << "Would you like to leave a like before deleting it?y/n\n";
		cin >> choice;
		if (choice == "y") {
			for (int i = 0; i < this->service.GetUserSize(); i++)
				if (title == this->service.GetUserRepository()[i].getTitle() && presenter == this->service.GetUserRepository()[i].getPresenter()) {
					likes = this->service.GetUserRepository()[i].getLikes();
				}
			this->service.UpdateLikesService(title, presenter, link, likes + 1);
			if (this->service.DeleteService(title, presenter, link, 2) == true)
				cout << "The tutorial was deleted successfully!\n";
			else
				cout << "The tutorial doesn't exist!\n";
		}
		else {
			if (this->service.DeleteService(title, presenter, link, 2) == true)
				cout << "The tutorial was deleted successfully!\n";
			else
				cout << "The tutorial doesn't exist!\n";
		}


	}
}

void UI::DisplayTheWatchList()
{
	int i = 0;
	for (const auto& tutorial : this->service.GetUserRepository()) {
		int minutes = 0;
		int seconds = 0;
		int hours = 0;
		std::tie(hours, minutes, seconds) = tutorial.getDuration();
		cout << ++i << ")  ""Title: " << tutorial.getTitle() << " Presenter: " <<
			tutorial.getPresenter() << " Duration:  " << hours << ":" << minutes << ":" << seconds
			<< " Likes: " << tutorial.getLikes() << "\nLink: "
			<< tutorial.getLink() << "\n" << "\n";
	}
}


