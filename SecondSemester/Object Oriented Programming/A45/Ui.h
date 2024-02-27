#pragma once
#include "Service.h"
#include "Validation.h"

class UI
{
private:
    Service service;
    Validator validator;

public:
    UI();
   
    ~UI();

    UI(const Service& copyService, const Validator& copyValidator);

    void Start();

    //Admin side
    void AdministratorMode();

    void MenuAdminMode();

    void UpdateTutorialLikesAdmin();

    void UpdateTutorialDurationAdmin();

    void DeleteTutorialAdminMode();

    void DisplayTutorialsAdmin();

    void AddTutorialAdminMode();

    //User side

    void UserMode();

    void UserMenu();

    void DisplayTutorialsFromGivenPresenter();

    void AddTutorialToWatchList();

    void DeleteTutorialFromWatchList();
    
    void DisplayTheWatchList();
};
