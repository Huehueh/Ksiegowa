#include "xmlcreator.h"

#include"jpk_names.h"

#include <QDate>
#include <QFile>
#include <QTextStream>
#include <QDebug>

XmlCreator::XmlCreator(const OneMonthCompanyData& data): m_pWriter(nullptr), mData (data)
{
    m_pWriter = new QXmlStreamWriter(&output);
    m_pWriter->setAutoFormatting(true);
}

void XmlCreator::CreateXml()
{
    m_pWriter->writeStartDocument();
    AddCompanyData();
    AddHeader();
    AddSales();
    AddPurchases();
    m_pWriter->writeEndDocument();
    qDebug() << output;

    QFile file("hue.xml");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
            qDebug() << "hue"; return;
    }
     QTextStream out(&file);
     out << output;
     file.close();
}

void XmlCreator::AddHeader()
{
    //Nagówek
    m_pWriter->writeStartElement("tns:Naglowek");
    m_pWriter->writeTextElement("tns:KodFormularza", "3");
    m_pWriter->writeTextElement("tns:WariantFormularza", "6");
    m_pWriter->writeTextElement("tns:CelZlozenia", "0");
    auto date = QDateTime::currentDateTime();
    m_pWriter->writeTextElement("tns:DataWyworzeniaJPK", date.toString(dateFormat)+"T"+date.toString(timeFormat));

    m_pWriter->writeEndElement();
}

void XmlCreator::AddCompanyData()
{
    // Podmiot1
    m_pWriter->writeStartElement(Company::Names.value(Fields::Subject));
}

void XmlCreator::AddSales(){}
void XmlCreator::AddPurchases(){}
