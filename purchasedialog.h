#ifndef PURCHASEDIALOG_H
#define PURCHASEDIALOG_H

#include "operationdialog.h"

class PurchaseDialog : public OperationDialog
{
    Q_OBJECT
public:
    explicit PurchaseDialog(int companyId, QWidget *parent = nullptr);

protected:
  void LoadModel() override;
  void SetupUi() override;
  void CreateMapper() override;
  void SelectContractor(int) override;
};

#endif // PURCHASEDIALOG_H
