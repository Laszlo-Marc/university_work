#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int validateMaterialName(char name[])
{
    if (strlen(name) < 1)
        return 0;
    for (int i = 0; i < strlen(name); i++)
        if (isdigit(name[i]))
            return 0;
    return 1;
}

int validateMaterialQuantity(char quantity[])
{
    int new_quantity = 0;
    if (strlen(quantity) < 1)
        return 0;
    if (strlen(quantity) >= 1)
        if (quantity[0] == '0')
            return 0;
    for (int i = 0; i < strlen(quantity); i++)
        if (isalpha(quantity[i]))
            return 0;
    new_quantity = strtol(quantity, NULL, 10);
    if (new_quantity == 0)
        return 0;
    return new_quantity;

}

int validateMaterialSupplier(char supplier[])
{

    if (strlen(supplier) < 1)
        return 0;
    for (int i = 0; i < strlen(supplier); i++)
        if (isdigit(supplier[i]))
            return 0;
    return 1;
}

int validateMaterialExpDate(char date[])
{
    char str1[100], str2[100], str3[100];
    int day, month, year;
    if (strlen(date) != 10)
        return 0;

    if (date[2] != '.')
        return 0;
    if (date[5] != '.')
        return 0;

    if (date[0] == '0' && date[1] == '0')
        return 0;

    if (date[3] == '0' && date[4] == '0')
        return 0;

    if (date[6] == 0 && date[7] == 0 && date[8] == 0 && date[9] == 0)
        return 0;

    str1[0] = date[0];
    str1[1] = date[1];
    str1[2] = 0;
    day = strtol(str1, NULL, 10);
    if (day <= 0)
        return 0;
    if (day > 31)
        return 0;

    str2[0] = date[3];
    str2[1] = date[4];
    str2[2] = 0;
    month = strtol(str2, NULL, 10);

    if (month <= 0)
        return 0;
    if (month > 12)
        return 0;

    str3[0] = date[6];
    str3[1] = date[7];
    str3[2] = date[8];
    str3[3] = date[9];
    year = strtol(str3, NULL, 10);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if (year < tm.tm_year + 1900)
        return 0;

    if (year == tm.tm_year + 1900 && day == tm.tm_mday && month == tm.tm_mon + 1)
        return 0;

    if (isalpha(date[0]) || isalpha(date[1]) || isalpha(date[3]) || isalpha(date[4]) || isalpha(date[6]) ||
        isalpha(date[7]) || isalpha(date[8]) || isalpha(date[9]))
        return 0;

    return 1;

}
