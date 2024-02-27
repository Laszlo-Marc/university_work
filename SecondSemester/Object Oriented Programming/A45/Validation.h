#pragma once
#include <string>
#include <iostream>
using namespace std;

class Validator {
public:
	bool validateTitle(string title);
	bool validatePresenter(string presenter);
	bool validateLink(string link);
	int validateLikes(string likes);
	std::tuple<int,int, int> Validator::validateDuration(string duration);
};