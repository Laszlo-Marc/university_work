#pragma once
#include <cstdlib>
#include "Tutorial.h"
#include "Repository.h"
#include "FileRepository.h"
class Service
{
private:
    Repository Adminrepository;
    FileRepository* userRepo;
public:
    ~Service();
    Service(Repository& repository, FileRepository* userRepoFile) :Adminrepository{ repository }, userRepo{ userRepoFile } {};
    
    vector<Tutorial>& GetRepository();
    vector<Tutorial>& GetUserRepository();

    void AddService(string title, string presenter, string link, int likes, int hours, int minutes, int seconds, int criteria);
    void DeleteService(string title, string presenter, string link, int criteria);
    void UpdateDurationService(string title, string presenter, string link, int hours, int minutes, int seconds);
    void UpdateLikesService(string title, string presenter, string link, int likes);
    int GetSize();
    int GetUserSize();
    void openWatchList();
    Service& operator=(const Service& service);
};