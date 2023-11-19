#include <iostream>
using namespace std;

class Date {

    private:
        int year, month, day, hour, minute, second;
        bool isOurEra;

        static int daysInMonth[13];

    public:
        //инициализация по умолчанию
        Date()
        {
            this->isOurEra = true;
            this->year = 1960;
            this->month = 1;
            this->day = 1;
            this->hour = 0;
            this->minute = 0;
            this->second = 0;
        }

        Date (const Date& date)
        {
            this->isOurEra = date.isOurEra;
            this->year = date.year;
            this->month = date.month;
            this->day = date.day;
            this->hour = date.hour;
            this->minute = date.minute;
            this->second = date.second;
        }

        //деструктор
        ~Date()
        {
            cout << "~Date()" << endl;
        }

        //проверка на високосный год
        bool isLeapYear(int year)
        {
            if (year % 4!= 0) {
                return false;
            } else if (year % 100!= 0) {
                return true;
            } else if (year % 400!= 0) {
                return false;
            } else
                return true;
        }

        //преобразование даты в правильный формат
        void transforms()
        {
            if (second >= 60)
            {
                minute += second / 60;
                second %= 60;
            }
            else if (second < 0)
            {
                int m = (-second - 1) / 60 + 1;
                minute -= m;
                second += m * 60;
            }

            if (minute >= 60) {
                hour += minute / 60;
                minute %= 60;
            }
            else if (minute < 0) {
                int h = (-minute - 1) / 60 + 1;
                hour -= h;
                minute += h * 60;
            }

            if (hour >= 24) {
                day += hour / 24;
                hour %= 24;
            }
            else if (hour < 0) {
                int d = (-hour - 1) / 24 + 1;
                day -= d;
                hour += day * 24;
            }

            while (month > 12) {
                year++;
                month -= 12;
            }
            while (month < 1) {
                year--;
                month += 12;
            }

            if (year < 0) {
                isOurEra = false;
                year = -year;
            }

            if (isLeapYear(year)) {
                daysInMonth[2] = 29;
            }
            else {
                daysInMonth[2] = 28;
            }

            while (day > daysInMonth[month]) {
                day -= daysInMonth[month];
                month++;
                if (month > 12) {
                    year++;
                    month = 1;
                }
            }
            while (day < 1) {
                month--;
                if (month < 1) {
                    year--;
                    month = 12;
                }
                day += daysInMonth[month];
            }
        }

        //сложение дат
         Date add(int year, int month, int day, int hour, int minutes, int seconds) const
         {
            Date newDate = *this;

            newDate.year += year;
            newDate.month += month;
            newDate.day += day;
            newDate.hour += hour;
            newDate.minute += minutes;
            newDate.second += seconds;
            newDate.transforms();

            return newDate;
        }

        //вычитание дат
        Date subtract(int year, int month, int day, int hour, int minutes, int seconds) const
        {
            return add(-year, -month, -day, -hour, -minutes, -seconds);
        }

        //перегрузки
        friend ostream& operator<<(ostream& os, const Date& date)
        {
            os << "The date is :" << endl;
            cout<< "day --- " << date.day << endl;
            cout<< "month --- " << date.month << endl;
            cout<< "year --- " << date.year << endl;
            cout<< "hour --- " << date.hour << endl;
            cout<< "minute --- " << date.minute << endl;
            cout<< "second --- " << date.second << endl;
            cout<< "era --- " << date.isOurEra << endl;
            os << endl;
            return os;
        }

        Date& operator=(const Date& date)
        {
            this->isOurEra = date.isOurEra;
            this->year = date.year;
            this->month = date.month;
            this->day = date.day;
            this->hour = date.hour;
            this->minute = date.minute;
            this->second = date.second;

            return *this;
        }

        Date& operator+=(const Date& date)
        {
            this->isOurEra = date.isOurEra;
            this->year += date.year;
            this->month += date.month;
            this->day += date.day;
            this->hour += date.hour;
            this->minute += date.minute;
            this->second += date.second;
            transforms();
            return *this;
        }

        Date& operator-(const Date& date)
        {
            Date val = *this;
            val.transforms();
            return val -= date;
        }

        Date& operator-=(const Date& date)
        {
            this->isOurEra = date.isOurEra;
            this->year -= date.year;
            this->month -= date.month;
            this->day -= date.day;
            this->hour -= date.hour;
            this->minute -= date.minute;
            this->second -= date.second;
            transforms();
            return *this;
        }

        bool operator>(const Date& date)
        {
            if ((this->isOurEra > date.isOurEra) || (this->year > date.year) || (this->month > date.month) || (this->day > date.day) || (this->hour > date.hour) || (this->minute > date.minute) || (this->second > date.second))
                return true;

            else return false;
        }

        bool operator<(const Date& date)
        {
            if ((this->isOurEra < date.isOurEra) || (this->year < date.year) || (this->month < date.month) || (this->day < date.day) || (this->hour < date.hour) || (this->minute < date.minute) || (this->second < date.second))
                return true;

            else return false;
        }

        bool operator==(const Date& date) const
        {
            if ((this->isOurEra == date.isOurEra) && (this->year == date.year) && (this->month == date.month) && (this->day == date.day) && (this->hour == date.hour) && (this->minute == date.minute) && (this->second == date.second))
                return true;

            else return false;
        }
};

int Date::daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


int main()
{
    Date date1;
    cout << date1;
    return 0;
}
