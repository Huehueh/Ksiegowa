#include "saledialog.h"

#include "enums.h"
#include "saledelegate.h"
#include "dbmanager.h"
#include "ui_tableDialog.h"

#include <QDataWidgetMapper>
#include <QSqlRecord>

#include "dialogmanager.h"

SaleDialog::SaleDialog(int companyId, QWidget *parent) :
    OperationDialog(companyId, parent)
{
    LoadModel();
    SetupUi();
}

void SaleDialog::LoadModel()
{
    m_pModel = DbManager::CreateSalesModel(mCompanyId);
}

void SaleDialog::SelectContractor(int id)
{
    m_pModel->setData(m_pModel->index(mSelectedIndex, Sprzedaz::KontrahentId), id);
    m_pModel->submit();
}

void SaleDialog::SetupUi()
{
  setWindowTitle(tr("Sprzedaż"));

    auto view = ui->operationsTableView;
  view->setModel(m_pModel);
  view->setEditTriggers(QAbstractItemView::NoEditTriggers);
  view->setSelectionBehavior(QAbstractItemView::SelectRows);
  view->setSelectionMode(QAbstractItemView::SingleSelection);
  view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  view->selectRow(mSelectedIndex);
  view->hideColumn(Sprzedaz::FirmaId);
  view->hideColumn(Sprzedaz::Id);
  view->setFocusPolicy(Qt::StrongFocus);
  view->selectRow(0);

  CreateMapper();

  connect(ui->addInvoiceButton, &QPushButton::clicked, this, [&]()
  {
      DialogManager::OpenAddSaleInvoiceDialog(mCompanyId, this);
  });
}

void SaleDialog::CreateMapper() {
  // form
  mMapper = new QDataWidgetMapper(this);
  mMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
  mMapper->setModel(m_pModel);
  mMapper->addMapping(ui->dateEdit1, Sprzedaz::DataSprzedazy);
  SetupDateEdit(ui->dateEdit1);
  mMapper->addMapping(ui->dateEdit2, Sprzedaz::DataWystawienia);
  SetupDateEdit(ui->dateEdit2);
  mMapper->addMapping(ui->invoiceEdit, Sprzedaz::DowodSprzedazy);
  mMapper->addMapping(ui->contractorLabel, Sprzedaz::KontrahentId);

  LoadKValues(m_pModel, 6, m_pModel->columnCount(), ui->kGridLayout, mMapper);

  mMapper->setItemDelegate(new SaleDelegate(mMapper));
  mMapper->toFirst();

  connect(ui->operationsTableView->selectionModel(),
          &QItemSelectionModel::currentRowChanged,
          [&](const QModelIndex &index) {
            mMapper->setCurrentIndex(index.row());
            mSelectedIndex = index.row();
          });
}


