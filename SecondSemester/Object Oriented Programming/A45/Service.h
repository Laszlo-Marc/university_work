#pragma once
#include <cstdlib>
#include "DynamicArray.h"
#include "Repository.h"
#include "Tutorial.h"

class Service
{
private:
    Repository Adminrepository;
    Repository userRepo;
public:
    Service();
    Service(const Repository& repo,const Repository& userRepo);
    ~Service();
    void initializeRepo();
    bool AddService(string title, string presenter, string link, int likes,int hours,int minutes,int seconds,int criteria);
    DynamicArray<Tutorial> GetRepository();
    bool DeleteService(string title, string presenter, string link,int criteria);
    bool Service::UpdateDurationService(string title, string presenter, string link,int hours, int minutes,int seconds);
    bool UpdateLikesService(string title, string presenter, string link, int likes);
    int GetSize();
    int GetUserSize();
    DynamicArray<Tutorial> GetUserRepository();
    Repository searchByPresenter(string presenter);
};