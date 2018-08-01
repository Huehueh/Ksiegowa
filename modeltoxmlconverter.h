#ifndef MODELTOXMLCONVERTER_H
#define MODELTOXMLCONVERTER_H

#include <QXmlStreamWriter>
#include <QSqlTableModel>

class ModelToXmlConverter
{
public:
    ModelToXmlConverter(const QModelIndex& copmanyData, int year, int month);
    void AddSaleModel(QSqlTableModel* model);
    void AddPurchaseModel(QSqlTableModel* model);
    void CreateXmlFile();

private:
    QXmlStreamWriter* m_pWriter;
    QString output;
};

#endif // MODELTOXMLCONVERTER_H
