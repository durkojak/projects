#include "CDate.h"

CDate::CDate(int year, int month, int day, int hour, int minute,int second) {
    this->mYear = year;
    this->mMonth = month;
    this->mDay = day;
    this->mHour = hour;
    this->mMinute = minute;
    this->mSecond = second;
}

int CDate::getYear() const { return this->mYear; }

int CDate::getMonth() const { return this->mMonth; }

int CDate::getDay() const { return this->mDay; }

int CDate::getHour() const { return this->mHour; }

int CDate::getMinute() const { return this->mMinute; }

void CDate::setYear(int year) { this->mYear = year; }

void CDate::setMonth(int month) { this->mMonth = month; }

void CDate::setDay(int day) { this->mDay = day; }

void CDate::setHour(int hour) { this->mHour = hour; }

void CDate::setMinute(int minute) { this->mMinute = minute; }

std::ostream &operator<<(std::ostream &os, const CDate &date) {
    os << date.mYear << "-" << date.mMonth << "-" << date.mDay << "-" << date.mHour
       << "-" << date.mMinute << "-" << date.mSecond << std::endl;
    return os;
}

bool CDate::operator==(const CDate &rhs) const {
    return mYear == rhs.mYear &&
           mMonth == rhs.mMonth &&
           mDay == rhs.mDay;
}

bool CDate::operator!=(const CDate &rhs) const {
    return !(rhs == *this);
}

bool CDate::operator<(const CDate &rhs) const {
    return this->mYear < rhs.mYear ||
            (this->mYear == rhs.mYear && this->mMonth <  rhs.mMonth) ||
            (this->mYear == rhs.mYear && this->mMonth ==  rhs.mMonth && this->mDay < rhs.mDay) ||
            (this->mYear == rhs.mYear && this->mMonth ==  rhs.mMonth && this->mDay == rhs.mDay && this->mHour < rhs.mHour) ||
            (this->mYear == rhs.mYear && this->mMonth ==  rhs.mMonth && this->mDay == rhs.mDay && this->mHour == rhs.mHour && this->mMinute < rhs.mMinute) ||
            (this->mYear == rhs.mYear && this->mMonth ==  rhs.mMonth && this->mDay == rhs.mDay && this->mHour == rhs.mHour && this->mMinute == rhs.mMinute && this->mSecond <
                                                                                                                                                                       rhs.mSecond);
}
