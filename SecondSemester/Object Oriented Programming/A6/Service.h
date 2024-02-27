
#pragma once
#include <cstdlib>
#include "Tutorial.h"
#include "Repository.h"
class Service
{
private:
    Repository Adminrepository;
    Repository userRepo;
public:
    Service();
    Service(const Repository& repo, const Repository& userRepo);
    ~Service();
    void initializeRepo();
    bool AddService(string title, string presenter, string link, int likes, int hours, int minutes, int seconds, int criteria);
    vector<Tutorial> GetRepository();
    bool DeleteService(string title, string presenter, string link, int criteria);
    bool Service::UpdateDurationService(string title, string presenter, string link, int hours, int minutes, int seconds);
    bool UpdateLikesService(string title, string presenter, string link, int likes);
    int GetSize();
    int GetUserSize();
    vector<Tutorial> GetUserRepository();
    
};