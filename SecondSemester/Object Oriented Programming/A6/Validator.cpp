#include "Validation.h"
#include <ctype.h>
#include <string>
#include <tuple>
using namespace std;


bool Validator::validateTitle(string title)
{
    for (char i : title)
        if (isdigit(i))
            return false;
    return true;
}

bool Validator::validatePresenter(string presenter)
{
    for (char i : presenter)
        if (isdigit(i))
            return false;
    return true;
}

bool Validator::validateLink(string link)
{
    std::string prefix = "https://www.youtube.com/";
    if (link.find(prefix) != 0) {
        return false;
    }

    return true;
}

int Validator::validateLikes(string likes)
{
    for (char i : likes)
        if (isalpha(i))
            return -1;
    int newLikes;
    newLikes = stoi(likes);
    return newLikes;

}

std::tuple<int, int, int> Validator::validateDuration(string duration)
{
    int firstDelimiterIndex = duration.find(":");
    int lastDelimiterIndex = duration.rfind(":");
    if (firstDelimiterIndex == string::npos || lastDelimiterIndex == string::npos || firstDelimiterIndex == lastDelimiterIndex) {
        return std::make_tuple(-1, -1, -1);}

    string hours = duration.substr(0, firstDelimiterIndex);
    string minutes = duration.substr(firstDelimiterIndex + 1, lastDelimiterIndex - firstDelimiterIndex - 1);
    string seconds = duration.substr(lastDelimiterIndex + 1);

    for (char i : hours) {
        if (isalpha(i)) {
            return std::make_tuple(-1, -1, -1); }}
    int newHours = stoi(hours);

    for (char i : minutes) {
        if (isalpha(i)) {
            return std::make_tuple(-1, -1, -1); }}
    int newMinutes = stoi(minutes);

    for (char i : seconds) {
        if (isalpha(i)) {
            return std::make_tuple(-1, -1, -1);}}
    int newSeconds = stoi(seconds);

    if (newMinutes < 0 || newMinutes > 59 || newSeconds < 0 || newSeconds > 59) {
        return std::make_tuple(-1, -1, -1);}

    return std::make_tuple(newHours, newMinutes, newSeconds); }
