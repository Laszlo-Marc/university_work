#pragma once


#include "Service.h"
#include "Validator.h"

class UI
{
private:
    Service service;
    Validator validator;

public:
    ~UI();
    UI(Service service, Validator validator) : service{ service }, validator{ validator } {};

    void Start();

    //Admin side
    
    //function that runs the administrator part of the program
    void AdministratorMode();
    
    //menu with the commands for the administrator
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
