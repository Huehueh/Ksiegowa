#include "dialogmanager.h"

#include "invoicecreatordialog.h"
#include "purchasedialog.h"
#include "saledialog.h"
#include "mainwindow.h"
#include "addcompanydialog.h"
#include "contractorsdialog.h"
#include "dictionarydialog.h"

#include <QDialog>

DialogManager *DialogManager::m_pInstance = nullptr;

DialogManager *DialogManager::CreateInstance() {
  if (m_pInstance == nullptr) {
    m_pInstance = new DialogManager();
  }
  return m_pInstance;
}

DialogManager *DialogManager::Instance() { return m_pInstance; }

DialogManager::DialogManager() {}

void DialogManager::OpenSaleDialog(int nip, QWidget* parent)
{
    auto dialog = new SaleDialog(nip, parent);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->exec();
}

void DialogManager::OpenPurchaseDialog(int companyId, QWidget* parent)
{
    auto dialog = new PurchaseDialog(companyId, parent);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->exec();
}

void DialogManager::OpenAddSaleInvoiceDialog(int companyId, QWidget* parent)
{
    auto dialog = new InvoiceCreatorDialog(companyId, InvoiceType::Sale, parent);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->exec();
}

void DialogManager::OpenAddPurchaseInvoiceDialog(int companyId, QWidget* parent)
{
    auto dialog = new InvoiceCreatorDialog(companyId, InvoiceType::Purchase, parent);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->exec();
}

void DialogManager::OpenAddCompanyDialog(QWidget* parent)
{
     auto dialog = new CompanyDialog(CompanyType::Main,  parent);
     dialog->setAttribute(Qt::WA_DeleteOnClose);
     dialog->exec();
}

int DialogManager::OpenSelectContractorDialog(QWidget* parent)
{
    auto dialog = new ContractorsDialog(parent);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    if(dialog->exec() ==QDialog::Accepted)
    {
        return dialog->GetContractorIndex() + 1;
    }
}

void DialogManager::OpenAddContractorDialog(QWidget* parent)
{
    auto dialog = new CompanyDialog(CompanyType::Contractor, parent);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->exec();
}

void DialogManager::OpenDictionaryDialog(QWidget* parent)
{
    auto dialog = new DictionaryDialog(parent);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->exec();
}
