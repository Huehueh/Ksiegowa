#ifndef DIALOGMANAGER_H
#define DIALOGMANAGER_H

#include <QWidget>

class DialogManager
{
public:
  static DialogManager *CreateInstance();
  static DialogManager *Instance();

  static void OpenSaleDialog(int companyId, QWidget* parent);
  static void OpenPurchaseDialog(int companyId, QWidget* parent);
  static void OpenAddSaleInvoiceDialog(int companyId, QWidget* parent);
  static void OpenAddPurchaseInvoiceDialog(int companyId, QWidget* parent);
  static void OpenAddCompanyDialog(QWidget* parent);
  static int OpenSelectContractorDialog(QWidget* parent);
  static void OpenAddContractorDialog(QWidget* parent);
  static void OpenDictionaryDialog(QWidget* parent);

private:
  DialogManager();
  static DialogManager *m_pInstance;

};

#endif // DIALOGMANAGER_H
