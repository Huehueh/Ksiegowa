#include "addcompanydialog.h"
#include "ui_addcompanydialog.h"

#include <QLineEdit>
#include <QModelIndex>
#include <QRegExpValidator>
#include <QSqlRecord>
#include <QSqlTableModel>

#include "dbmanager.h"
#include "enums.h"

CompanyDialog::CompanyDialog(CompanyType company, QWidget *parent)
    : QDialog(parent), ui(new Ui::AddCompanyDialog), m_pMapper(nullptr),
      m_CompanyType(company){

  ui->setupUi(this);

  switch (m_CompanyType) {
  case CompanyType::Main:
  default: {
    m_pModel = DbManager::CreateMyCompaniesModel();
    break;
  }
  case CompanyType::Contractor: {
    m_pModel = DbManager::CreateContractorsModel();
    break;
  }
  }

  m_pMapper = new QDataWidgetMapper();
  m_pMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
  m_pMapper->setModel(m_pModel);
  m_pModel->insertRow(m_pModel->rowCount());
  m_pMapper->toLast();

  CreateUi();

  connect(ui->okButton, &QPushButton::clicked, this,
          &CompanyDialog::OnAccept);
  connect(ui->cancelButton, &QPushButton::clicked, this,
          &CompanyDialog::OnCancel);
}

void CompanyDialog::CreateUi() {
  QRegExp rx("[0-9]\\d{0,9}");
  auto numberValidator = new QRegExpValidator(rx, this);

  switch (m_CompanyType) {
  case CompanyType::Main: {

    // shortcut
    m_pMapper->addMapping(ui->shortcutLineEdit, MojaFirma::Skrot);

    // name
    m_pMapper->addMapping(ui->nameLineEdit, MojaFirma::Nazwa);

    // nip
    m_pMapper->addMapping(ui->nipLineEdit, MojaFirma::NIP);
    ui->nipLineEdit->setValidator(numberValidator);

    // address
    m_pMapper->addMapping(ui->addressLineEdit, MojaFirma::Adres);

    // email
    m_pMapper->addMapping(ui->emailLineEdit, MojaFirma::Email);

    break;
  }
  case CompanyType::Contractor: {

    // shortcut
    ui->shortcutLineEdit->setVisible(false);
    ui->shortcutLabel->setVisible(false);

    // name
    m_pMapper->addMapping(ui->nameLineEdit, Kontrahent::NazwaKontrahenta);

    // nip
    m_pMapper->addMapping(ui->nipLineEdit, Kontrahent::NrKontrahenta);
    ui->nipLineEdit->setValidator(numberValidator);

    // address
    m_pMapper->addMapping(ui->addressLineEdit, Kontrahent::AdresKontrahenta);

    // email
    ui->emailLineEdit->setVisible(false);
    ui->emailLabel->setVisible(false);

    break;
  }
  }
}

void CompanyDialog::OnAccept() {
  m_pMapper->submit();
  m_pModel->submit();
  accept();
}

void CompanyDialog::OnCancel() {
  auto last = m_pModel->rowCount() - 1;
  m_pModel->removeRow(last, m_Index);
  reject();
}

CompanyDialog::~CompanyDialog() { delete ui; }
