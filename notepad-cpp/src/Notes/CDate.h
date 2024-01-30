#ifndef DURKOJAK_CDATE_H
#define DURKOJAK_CDATE_H


#include <ostream>

class CDate {
public:
    CDate(int year, int month, int day, int hour, int minute,int second);

    bool operator==(const CDate &rhs) const;

    bool operator!=(const CDate &rhs) const;

    bool operator<(const CDate &rhs) const;

    int getYear() const;
    int getMonth() const;
    int getDay() const;
    int getHour() const;
    int getMinute() const;

    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);
    void setHour(int hour);
    void setMinute(int minute);

    friend std::ostream &operator<<(std::ostream &os, const CDate &date);

private:
    int mYear;
    int mMonth;
    int mDay;
    int mHour;
    int mMinute;
    int mSecond;
};


#endif //DURKOJAK_CDATE_H
