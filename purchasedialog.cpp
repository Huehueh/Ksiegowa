#include "purchasedialog.h"

#include "enums.h"
#include "purchasedelegate.h"
#include "dbmanager.h"
#include "ui_tableDialog.h"

#include <QDataWidgetMapper>

#include "dialogmanager.h"

PurchaseDialog::PurchaseDialog(int companyId, QWidget *parent) : OperationDialog(companyId, parent)
{
    LoadModel();
    SetupUi();
}

void PurchaseDialog::LoadModel()
{
    m_pModel = DbManager::CreatePurchaseModel(mCompanyId);
}

void PurchaseDialog::SetupUi()
{
  setWindowTitle(tr("Zakup"));

  auto view = ui->operationsTableView;
  view->setModel(m_pModel);
  view->setSelectionBehavior(QAbstractItemView::SelectRows);
  view->setSelectionMode(QAbstractItemView::SingleSelection);
  view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  view->hideColumn(Zakup::FirmaId);
  view->hideColumn(Zakup::Id);
  view->setFocusPolicy(Qt::StrongFocus);
  view->selectRow(0);

  CreateMapper();

  connect(ui->addInvoiceButton, &QPushButton::clicked, this, [&](){
      DialogManager::OpenAddPurchaseInvoiceDialog(mCompanyId, this);
  });
}

void PurchaseDialog::SelectContractor(int id)
{
    m_pModel->setData(m_pModel->index(mSelectedIndex, Zakup::KontrahentId), id);
    m_pModel->submit();
}

void PurchaseDialog::CreateMapper() {
  // form
  mMapper = new QDataWidgetMapper(this);
  mMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
  mMapper->setModel(m_pModel);
  mMapper->addMapping(ui->dateEdit1, Zakup::DataZakupu);
  SetupDateEdit(ui->dateEdit1);
  mMapper->addMapping(ui->dateEdit2, Zakup::DataWplywu);
  SetupDateEdit(ui->dateEdit2);
  mMapper->addMapping(ui->invoiceEdit, Zakup::DowodZakupu);
  mMapper->addMapping(ui->contractorLabel, Zakup::KontrahentId);

  LoadKValues(m_pModel, 6, m_pModel->columnCount(), ui->kGridLayout, mMapper);

  mMapper->setItemDelegate(new PurchaseDelegate(mMapper));
  mMapper->toFirst();

  connect(ui->operationsTableView->selectionModel(),
          &QItemSelectionModel::currentRowChanged,
          [&](const QModelIndex &index) {
            mMapper->setCurrentIndex(index.row());
            mSelectedIndex = index.row();
          });
}

