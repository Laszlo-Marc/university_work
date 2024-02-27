#include "Service.h"
#include <tuple>
#include <algorithm>
int Service::GetSize()
{
	return this->Adminrepository.getSize();
}

int Service::GetUserSize()
{
	return this->userRepo->getSize();
}

void Service::openWatchList()
{
	this->userRepo->displayTutorials();
}

Service& Service::operator=(const Service& service)
{
	if (this == &service)
		return *this;
	this->Adminrepository = service.Adminrepository;
	this->userRepo = service.userRepo;
	return *this;
}


void Service::AddService(string title, string presenter, string link, int likes, int hours, int minutes, int seconds, int criteria)
{
	if (criteria == 1) {
		this->Adminrepository.addRepo(title, presenter, hours, minutes, seconds, link, likes);
			
	}
	else
		if (criteria == 2) {
			this->userRepo->addRepo(title, presenter, hours, minutes, seconds, link, likes);
			this->userRepo->writeToFile();
		}
}

Service::~Service()
{
}

vector<Tutorial>& Service::GetRepository()
{
	return this->Adminrepository.getArray();
}


void Service::DeleteService(string title, string presenter, string link, int criteria)
{

	if (criteria == 1) {
		this->Adminrepository.deleteTutorialRepo(title, presenter, link);
			
	}
	else
		if (criteria == 2) {
			this->userRepo->deleteTutorialRepo(title, presenter, link);
			this->userRepo->writeToFile();
		}
}

void Service::UpdateLikesService(string title, string presenter, string link, int likes)
{
	this->Adminrepository.updateLikesRepo(title, presenter, link, likes);
	this->userRepo->writeToFile();
}



void Service::UpdateDurationService(string title, string presenter, string link, int hours, int minutes, int seconds)
{
	this->Adminrepository.updateDurationRepo(title, presenter, link, hours, minutes, seconds);
	this->userRepo->writeToFile();
}

vector<Tutorial>& Service::GetUserRepository()
{
	return this->userRepo->getArray();
}

