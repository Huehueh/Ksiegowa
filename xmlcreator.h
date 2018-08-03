#ifndef XMLCREATOR_H
#define XMLCREATOR_H

#include "onemonthcompanydata.h"

#include <QXmlStreamWriter>
#include <QString>

class XmlCreator
{
public:
    XmlCreator(const OneMonthCompanyData& data);
    void CreateXml();

private:
    void AddHeader();
    void AddCompanyData();
    void AddSales();
    void AddPurchases();

    QXmlStreamWriter* m_pWriter;
    QString output;
    const QString dateFormat = "yyyy-MM-dd";
    const QString timeFormat = "hh:mm:ss";
    OneMonthCompanyData mData;
};

#endif // XMLCREATOR_H
