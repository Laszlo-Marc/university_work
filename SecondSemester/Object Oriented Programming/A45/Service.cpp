#include "Service.h"
#include <tuple>

int Service::GetSize()
{
	return this->GetRepository().getSize();
}

int Service::GetUserSize()
{
	return this->GetUserRepository().getSize();
}

Service::Service()
{
}

Service::Service(const Repository& repo,const Repository& userRepo):Adminrepository{repo},userRepo{userRepo}
{
	
}

Service::~Service() = default;

void Service::initializeRepo()
{
	this->Adminrepository.initializeRepo();
}

bool Service::AddService(string title, string presenter, string link, int likes,int hours,int minutes,int seconds,int criteria)
{
	if (criteria == 1) {
		if (this->Adminrepository.addRepo(title, presenter,hours,minutes,seconds, link, likes) == true)
			return true;
		else
			return false;
	}
	else 
		if (criteria == 2) {
			if (this->userRepo.addRepo(title, presenter, hours, minutes, seconds, link, likes) == true)
				return true;
			else
				return false;
		}
	
}

DynamicArray<Tutorial> Service::GetRepository()
{
	return this->Adminrepository.getArray();
}


bool Service::DeleteService(string title, string presenter, string link,int criteria)
{
	if (criteria == 1) {
		if (this->Adminrepository.deleteTutorialRepo(title, presenter, link) == true)
			return true;
		else
			return false;
	}
	else
		if (criteria == 2) {
			if (this->userRepo.deleteTutorialRepo(title, presenter, link) == true)
				return true;
			else
				return false;
		}
	
}

bool Service::UpdateLikesService(string title, string presenter, string link, int likes)
{
	if (this->Adminrepository.updateLikesRepo(title,presenter,link,likes) == true)
		return true;
	else
		return false;
}



bool Service::UpdateDurationService(string title, string presenter, string link, int hours, int minutes, int seconds)
{
	if (this->Adminrepository.updateDurationRepo(title, presenter, link, hours, minutes, seconds) == true)
		return true;
	else
		return false;
}

DynamicArray<Tutorial> Service::GetUserRepository()
{
	return this->userRepo.getArray();
}



Repository Service::searchByPresenter(string presenter)
{
	DynamicArray<Tutorial> temporaryArray(10);
	Repository temporaryRepo(temporaryArray);
	for (int i = 0; i < this->Adminrepository.getSize(); i++) {
		if (this->Adminrepository.getArray()[i].getPresenter() == presenter) {
			int minutes, seconds, hours;
			tie(hours, minutes, seconds) = this->Adminrepository.getArray()[i].getDuration();
			temporaryRepo.addRepo(this->Adminrepository.getArray()[i].getTitle(), this->Adminrepository.getArray()[i].getPresenter(), hours, minutes, seconds, this->Adminrepository.getArray()[i].getLink(), this->Adminrepository.getArray()[i].getLikes());

		}
	}
	return temporaryRepo;
}

