#ifndef INVOICECREATORDIALOG_H
#define INVOICECREATORDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class InvoiceCreatorDialog;
}

enum class InvoiceType
{
    Purchase,
    Sale
};

class InvoiceCreatorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InvoiceCreatorDialog(int companyId, InvoiceType type, QWidget *parent = 0);
    ~InvoiceCreatorDialog();

private slots:
    void OnAccept();

private:
    void CreateMapper();

    Ui::InvoiceCreatorDialog *ui;
    InvoiceType m_Type;
    QSqlTableModel* m_Model;
    QDataWidgetMapper* m_Mapper;

};

#endif // INVOICECREATORDIALOG_H
