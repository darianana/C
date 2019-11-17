#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>
#include <functional>
#include <set>
#include <queue>
#include <string>
#include <map>
#include <iomanip>
#include <sstream>
#include <cassert>

class Date {
public:
    explicit Date(int year, int month, int day);
    bool IsLeap() const;
    std::string ToString() const;
    Date DaysLater(int day) const;
    int DaysLeft(const Date& date) const;
    int years;
    int months;
    int days;
};

Date::Date(int year, int month, int day) {
    years = year;
    months = month;
    days = day;
}

bool Date::IsLeap() const {
    if ((years % 4 != 0) || (years % 100 == 0 && years % 400 != 0))
        return false;
    else if (years % 400 == 0)
        return true;
    else
        return true;
}

std::string Date::ToString() const {
    std::string days_string = std::to_string(days);
    std::string month_string = std::to_string(months);
    std::string years_string = std::to_string(years);
    if (days_string.length() != 2) days_string = "0" + days_string;
    if (month_string.length() != 2) month_string = "0" + month_string;
    while (years_string.length() != 4) {
        years_string = "0" + years_string;
    }
    std :: string date_str = days_string + "." + month_string + "." + years_string;
    return date_str;
}

Date Date::DaysLater(int day) const {
    int quan_days = 0;
    int local_year = years;
    int local_month = months;
    int local_day = days;
    int left_days;
    while (day > 0) {
        switch (local_month) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                quan_days = 31;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                quan_days = 30;
                break;
            case 2:
                if (IsLeap())
                    quan_days = 29;
                else
                    quan_days = 28;
                break;
        }
        if (local_month == 12) {
            left_days = quan_days - local_day + 1;
            if (left_days <= day) {
                local_year++;
                local_month = 1;
                local_day = 1;
                day -= left_days;
            } else {
                local_day += day;
                day -= left_days;
            }
        }
        if (local_month < 12) {
            left_days = quan_days - local_day + 1;
            if (day >= left_days) {
                local_month++;
                local_day = 1;
                day -= left_days;
            } else {
                local_day += day;
                day -= left_days;
            }
        }
    }
    Date res(local_year, local_month, local_day);
    return res;
}

int Date::DaysLeft(const Date& date) const {
    int local_year = date.years;
    int local_month = date.months;
    int local_day = date.days;
    int a = (14 - local_month) / 12;
    int y = local_year + 4800 - a;
    int m = local_month + 12 * a - 3;
    int jdn1 = local_day + ((153 * m + 2) / 5) + 365 * y + (y / 4) - (y / 100) +
               (y / 400) - 32045;

    int a1 = (14 - months) / 12;
    int y1 = years + 4800 - a1;
    int m1 = months + 12 * a1 - 3;
    int jdn2 = days + ((153 * m1 + 2) / 5) + 365 * y1 + (y1 / 4) - (y1 / 100) +
               (y1 / 400) - 32045;
    return (jdn1 - jdn2);
}


int main() {
//    Date dt(2000, 1, 1);
//    cout << dt.DaysLater(366).ToString();
    {
        Date dt(1997, 1, 19);
        assert(!dt.IsLeap());
        assert(dt.ToString() == "19.01.1997");
    }
    {
        Date dt(100, 10, 1);
        assert(!dt.IsLeap());
        assert(dt.ToString() == "01.10.0100");
    }
    {
        Date dt(1, 1, 1);
        assert(!dt.IsLeap());
        assert(dt.ToString() == "01.01.0001");
    }
    {
        Date dt(2000, 10, 22);
        assert(dt.IsLeap());
        assert(dt.ToString() == "22.10.2000");
    }
    {
        Date dt(400, 1, 9);
        assert(dt.IsLeap());
        assert(dt.ToString() == "09.01.0400");
    }
    {
        Date dt(1996, 7, 8);
        assert(dt.IsLeap());
        assert(dt.ToString() == "08.07.1996");
    }
    {
        Date dt(2000, 1, 1);
        assert(dt.DaysLater(0).ToString() == "01.01.2000");
        assert(dt.DaysLater(10).ToString() == "11.01.2000");
        assert(dt.DaysLater(30).ToString() == "31.01.2000");
        assert(dt.DaysLater(31).ToString() == "01.02.2000");
        assert(dt.DaysLater(60).ToString() == "01.03.2000");
        assert(dt.DaysLater(366).ToString() == "01.01.2001");
    }
    {
        Date dt(2001, 1, 1);
        assert(dt.DaysLater(0).ToString() == "01.01.2001");
        assert(dt.DaysLater(10).ToString() == "11.01.2001");
        assert(dt.DaysLater(30).ToString() == "31.01.2001");
        assert(dt.DaysLater(31).ToString() == "01.02.2001");
        assert(dt.DaysLater(59).ToString() == "01.03.2001");
        assert(dt.DaysLater(365).ToString() == "01.01.2002");
    }
    {
        Date dt(2000, 1, 1);
        assert(dt.DaysLeft(Date{2000, 1, 1}) == 0);
        assert(dt.DaysLeft(Date{2000, 1, 11}) == 10);
        assert(dt.DaysLeft(Date{2000, 1, 31}) == 30);
        assert(dt.DaysLeft(Date{2000, 2, 1}) == 31);
        assert(dt.DaysLeft(Date{2000, 3, 1}) == 60);
        assert(dt.DaysLeft(Date{2001, 1, 1}) == 366);
    }
    {
        Date dt(2001, 1, 1);
        assert(dt.DaysLeft(Date{2001, 1, 1}) == 0);
        assert(dt.DaysLeft(Date{2001, 1, 11}) == 10);
        assert(dt.DaysLeft(Date{2001, 1, 31}) == 30);
        assert(dt.DaysLeft(Date{2001, 2, 1}) == 31);
        assert(dt.DaysLeft(Date{2001, 3, 1}) == 59);
        assert(dt.DaysLeft(Date{2002, 1, 1}) == 365);
    }
    std::cout << 1;
}