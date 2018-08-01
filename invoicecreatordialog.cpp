#include "invoicecreatordialog.h"
#include "ui_invoicecreatordialog.h"

#include "dbmanager.h"
#include "enums.h"

#include <QSqlRecord>
#include <QSqlField>

InvoiceCreatorDialog::InvoiceCreatorDialog(int companyId, InvoiceType type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InvoiceCreatorDialog), m_Type(type)
{
    ui->setupUi(this);

    switch(m_Type)
    {
    case InvoiceType::Purchase:
    {
        setWindowTitle(tr("Dowód zakupu"));
        m_Model = DbManager::CreatePurchaseModel(companyId);
//        auto record = m_Model->record();
//        record.setValue(Zakup::FirmaId, companyId);
//        record.setValue(Zakup::DowodZakupu, "kinolowy");
//        m_Model->insertRecord(m_Model->rowCount(), record);
//        m_Model->select();
        break;
    }
    case InvoiceType::Sale:
    {
        setWindowTitle(tr("Dowód sprzedaży"));
        m_Model = DbManager::CreateSalesModel(companyId);
        break;
    }
    }

    m_Model->insertRow(m_Model->rowCount());

    connect(ui->saveButton, &QPushButton::clicked, this, &InvoiceCreatorDialog::OnAccept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &InvoiceCreatorDialog::reject);

    CreateMapper();
}

void InvoiceCreatorDialog::CreateMapper()
{
  // form
  m_Mapper = new QDataWidgetMapper(this);
  m_Mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
  m_Mapper->setModel(m_Model);

  switch(m_Type)
  {
  case InvoiceType::Purchase:
  {
      m_Mapper->addMapping(ui->nameLineEdit, Sprzedaz::DowodSprzedazy);
      m_Mapper->addMapping(ui->dateEdit_1, Sprzedaz::DataSprzedazy);
      ui->date1->setText(tr("Data sprzedaży"));
      m_Mapper->addMapping(ui->dateEdit_2, Sprzedaz::DataWystawienia);
      ui->date2->setText(tr("Data wystawienia"));
      m_Mapper->addMapping(ui->amountLineEdit, Sprzedaz::K_19);
      m_Mapper->addMapping(ui->taxLineEdit, Sprzedaz::K_20);
      break;
  }
  case InvoiceType::Sale:
  {
      m_Mapper->addMapping(ui->nameLineEdit, Zakup::DowodZakupu);
      m_Mapper->addMapping(ui->dateEdit_1, Zakup::DataZakupu);
      ui->date1->setText(tr("Data zakupu"));
      ui->dateEdit_1->setDate(QDate());
      m_Mapper->addMapping(ui->dateEdit_2, Zakup::DataWplywu);
      ui->date2->setText(tr("Data wpływu"));
      ui->dateEdit_2->setDate(QDate());
      m_Mapper->addMapping(ui->amountLineEdit, Zakup::K_45);
      m_Mapper->addMapping(ui->taxLineEdit, Zakup::K_46);
      break;
  }
  }
  m_Mapper->toFirst();
}

void InvoiceCreatorDialog::OnAccept()
{
    m_Mapper->submit();
    accept();
}

InvoiceCreatorDialog::~InvoiceCreatorDialog()
{
    delete ui;
}
