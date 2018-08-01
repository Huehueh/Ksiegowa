#ifndef SALEDIALOG_H
#define SALEDIALOG_H

#include "operationdialog.h"

class SaleDialog : public OperationDialog
{
    Q_OBJECT

public:
    SaleDialog(int companyId, QWidget *parent = nullptr);

protected:
  void LoadModel() override;
  void SetupUi() override;
  void CreateMapper() override;
  void SelectContractor(int) override;
};

#endif // SALEDIALOG_H
