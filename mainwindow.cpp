#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QHeaderView>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QTableView>
#include <QDataWidgetMapper>
#include <memory>

#include "dialogmanager.h"
#include "enums.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_tableModel = DbManager::CreateMyCompaniesModel();
  m_tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

  SetupTableView();
  CreateMapper();
  CreateMenuBar();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::SetupTableView() {
  auto view = ui->companiesTableView;
  view->setModel(m_tableModel);
  view->hideColumn(0); // id
  view->setSelectionBehavior(QAbstractItemView::SelectRows);
  view->setSelectionMode(QAbstractItemView::SingleSelection);
  view->selectRow(0);
  view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  view->setFocusPolicy(Qt::StrongFocus);
}

void MainWindow::CreateMapper() {
  // form
  auto mapper = new QDataWidgetMapper();
  mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
  mapper->setModel(m_tableModel);
  mapper->addMapping(ui->shortNameLineEdit, MojaFirma::Skrot);
  mapper->addMapping(ui->nameLineEdit, MojaFirma::Nazwa);
  mapper->addMapping(ui->nipLineEdit, MojaFirma::NIP);
  mapper->addMapping(ui->emailLineEdit, MojaFirma::Email);
  mapper->toFirst();

  connect(ui->companiesTableView->selectionModel(),
          &QItemSelectionModel::currentRowChanged,
          [mapper](const QModelIndex &index) {
            mapper->setCurrentIndex(index.row());
          });
}

void MainWindow::CreateMenuBar()
{
    auto saleAction = new QAction(tr("Sprzedaż"), this);
    saleAction->setStatusTip(tr("Otwórz okno sprzedaży"));
    connect(saleAction, &QAction::triggered, this, [&](){
        auto row = ui->companiesTableView->currentIndex().row();
        auto companyId = m_tableModel->data(m_tableModel->index(row, MojaFirma::Id)).toInt();
        DialogManager::OpenSaleDialog(companyId, this);
    });

    auto purchaseAction = new QAction(tr("Zakupy"), this);
    purchaseAction->setStatusTip(tr("Otwórz okno zakupów"));
    connect(purchaseAction, &QAction::triggered, this, [&](){
        auto row = ui->companiesTableView->currentIndex().row();
        auto companyId = m_tableModel->data(m_tableModel->index(row, MojaFirma::Id)).toInt();
        DialogManager::OpenPurchaseDialog(companyId, this);
    });

    auto menu = menuBar()->addMenu(tr("Operacje"));
    menu->addAction(saleAction);
    menu->addAction(purchaseAction);

    auto addCompanyAction = new QAction(tr("Dodaj"), this);
    addCompanyAction->setStatusTip(tr("Dodaj nowa firmę"));
    connect(addCompanyAction, &QAction::triggered, this, [&](){
        DialogManager::OpenAddCompanyDialog(this);
        m_tableModel->select();
    });

    auto removeCompanyAction = new QAction(tr("Usuń"), this);
    removeCompanyAction->setStatusTip(tr("Usuń wybraną firmę"));
    connect(removeCompanyAction, &QAction::triggered, this, &MainWindow::OnRemoveClicked);

    auto companyMenu = menuBar()->addMenu(tr("Firma"));
    companyMenu->addAction(addCompanyAction);
    companyMenu->addAction(removeCompanyAction);

    auto jpkAction = new QAction(tr("Utwórz JPK"), this);
    jpkAction->setStatusTip(tr("Utwórz plik JPK dla firm"));
    connect(jpkAction, &QAction::triggered, this, &MainWindow::CreateJPKFiles);

    auto jpkyMenu = menuBar()->addMenu(tr("JPK"));
    jpkyMenu->addAction(jpkAction);
}

void MainWindow::OnRemoveClicked()
{
  auto selection = ui->companiesTableView->selectionModel()->selectedRows();

  int deletedRowIndex = -1;
  for (const auto &index : selection) {
    auto model = index.model();
    auto name =
        model->data(model->index(index.row(), MojaFirma::Nazwa)).toString();

    deletedRowIndex = index.row();
    auto removed = m_tableModel->removeRow(deletedRowIndex);
    if (removed) {
      QMessageBox box(QMessageBox::Question, tr("Info"),
                      "Na pewno chcesz usunąć " + name + "?", QMessageBox::Ok | QMessageBox::Cancel, this);
      if(box.exec() ==QMessageBox::Accepted)
      {
          m_tableModel->submitAll();
          m_tableModel->database().commit();
          m_tableModel->select();
          if (deletedRowIndex > 1) {
            m_tableModel->selectRow(deletedRowIndex - 1);
          } else if (m_tableModel->rowCount() > 0) {
            ui->companiesTableView->selectRow(deletedRowIndex - 1);
            ui->companiesTableView->scrollTo(
                m_tableModel->index(deletedRowIndex - 1, 0));
          }
          ui->companiesTableView->update();
      }
    }
  }
}

void MainWindow::CreateJPKFiles()
{

}
