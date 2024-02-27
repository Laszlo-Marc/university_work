#pragma once
#include <string>
#include <iostream>
using namespace std;

class Validator {
public:
	static bool validateTitle(string title);
	static bool validatePresenter(string presenter);
	static bool validateLink(string link);
	int validateLikes(string likes);
	std::tuple<int, int, int> Validator::validateDuration(string duration);
};