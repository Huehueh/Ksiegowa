#ifndef CONTRACTORSDIALOG_H
#define CONTRACTORSDIALOG_H

#include <QDialog>
#include <functional>

namespace Ui {
class ContractorsDialog;
}

class ContractorsDialog : public QDialog {
  Q_OBJECT

public:
  ContractorsDialog(QWidget *parent = nullptr);
  ~ContractorsDialog();

  inline int GetContractorIndex() {return m_SelectedIndex;};

private:
  Ui::ContractorsDialog *ui;
  int m_SelectedIndex;

  void SetupUi();
};

#endif // CONTRACTORSDIALOG_H
