#ifndef ONEMONTHCOMPANYDATA_H
#define ONEMONTHCOMPANYDATA_H

#include<QString>
#include <QDate>
#include "vector"

class OneMonthCompanyData
{
public:
    OneMonthCompanyData(QString companyName, QString companyNumber, int month, int year);

    struct Sale
    {

    };

    struct Purchase
    {

    };

    void AddSale(Sale sale);
    void AddPurchase(Purchase purchase);
    QDate From();
    QDate To();

private:
    int GetLastDayInMonth(int year, int month);

    QString mName;
    QString mNIP;
    int mMonth;
    int mYear;

    std::vector<Sale> m_SalesList;
    std::vector<Purchase> m_PurchaseList;
};

#endif // ONEMONTHCOMPANYDATA_H
