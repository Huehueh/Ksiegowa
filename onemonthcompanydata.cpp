#include "onemonthcompanydata.h"

OneMonthCompanyData::OneMonthCompanyData(QString companyName, QString companyNumber, int month, int year)
    : mName(companyName)
    , mNIP(companyNumber)
    , mMonth(month)
    , mYear(year)
{

}

QDate OneMonthCompanyData::From()
{
    QDate date;
    date.setDate(mYear, mMonth, 1);
    return date;
}

QDate OneMonthCompanyData::To()
{
    QDate date;
    date.setDate(mYear, mMonth, GetLastDayInMonth(mYear, mMonth));
    return date;
}

int OneMonthCompanyData::GetLastDayInMonth(int year, int month) {
    if(month == 0 || month == 2 || month == 4 || month == 6 || month == 7 || month == 9 || month == 11)
        return 31;
    else if(month == 3 || month == 5 || month == 8 || month == 10)
        return 30;
    else {
        if(year % 4 == 0) {
            if(year % 100 == 0) {
                if(year % 400 == 0)
                    return 29;
                return 28;
            }
            return 29;
        }
        return 28;
    }
}
