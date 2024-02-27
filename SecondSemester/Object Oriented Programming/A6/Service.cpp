#include "Service.h"
#include <tuple>
#include <algorithm>
int Service::GetSize()
{
	return this->Adminrepository.getSize();
}

int Service::GetUserSize()
{
	return this->userRepo.getSize();
}

Service::Service()
{
}

Service::Service(const Repository& repo, const Repository& userRepo) :Adminrepository{ repo }, userRepo{ userRepo }
{

}

Service::~Service() = default;

void Service::initializeRepo()
{
	this->Adminrepository.initializeRepo();
}

bool Service::AddService(string title, string presenter, string link, int likes, int hours, int minutes, int seconds, int criteria)
{
	if (criteria == 1) {
		if (this->Adminrepository.addRepo(title, presenter, hours, minutes, seconds, link, likes) == true)
			return true;
		else
			return false;}
	else
		if (criteria == 2) {
			if (this->userRepo.addRepo(title, presenter, hours, minutes, seconds, link, likes) == true)
				return true;
			else
				return false;}}

vector<Tutorial> Service::GetRepository()
{
	return this->Adminrepository.getArray();
}


bool Service::DeleteService(string title, string presenter, string link, int criteria)
{
	
	if (criteria == 1) {
		if (this->Adminrepository.deleteTutorialRepo(title, presenter, link) == true)
			return true;
		else
			return false;}
	else
		if (criteria == 2) {
			if (this->userRepo.deleteTutorialRepo(title, presenter, link) == true)
				return true;
			else
				return false;}}

bool Service::UpdateLikesService(string title, string presenter, string link, int likes)
{
	if (this->Adminrepository.updateLikesRepo(title, presenter, link, likes) == true)
		return true;
	else
		return false;}



bool Service::UpdateDurationService(string title, string presenter, string link, int hours, int minutes, int seconds)
{
	if (this->Adminrepository.updateDurationRepo(title, presenter, link, hours, minutes, seconds) == true)
		return true;
	else
		return false;}

vector<Tutorial> Service::GetUserRepository()
{
	return this->userRepo.getArray();
}

