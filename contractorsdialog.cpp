#include "contractorsdialog.h"
#include "ui_contractorsdialog.h"

#include "dbmanager.h"
#include "enums.h"
#include "dialogmanager.h"

#include <QDialogButtonBox>
#include <QPushButton>

ContractorsDialog::ContractorsDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::ContractorsDialog), m_SelectedIndex{0} {
  ui->setupUi(this);

  auto tableModel = DbManager::CreateContractorsModel();
  ui->contractorsView->setModel(tableModel);

  SetupUi();

  connect(
      ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this,
      [&]() {
        m_SelectedIndex = ui->contractorsView->selectionModel()->selectedRows().at(0).row();
      });

  connect(ui->addContractorButton, &QPushButton::clicked, this, [&](){
      DialogManager::OpenAddContractorDialog(this);
  });
}

ContractorsDialog::~ContractorsDialog() { delete ui; }


void ContractorsDialog::SetupUi() {
  auto view = ui->contractorsView;
  view->setEditTriggers(QAbstractItemView::NoEditTriggers);
  view->setSelectionBehavior(QAbstractItemView::SelectRows);
  view->setSelectionMode(QAbstractItemView::SingleSelection);
  view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  view->hideColumn(Kontrahent::Id);
  view->selectRow(m_SelectedIndex);
}
