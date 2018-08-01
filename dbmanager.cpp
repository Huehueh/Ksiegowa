#include "dbmanager.h"

#include <QDebug>
#include <QSqlQuery>
#include <QTableView>
#include <QDate>
#include <QString>

#include "columnnames.h"
#include "enums.h"
#include "names.h"

DbManager *DbManager::m_pInstance = nullptr;

DbManager *DbManager::CreateInstance(const QString &path) {
  if (m_pInstance == nullptr) {
    m_pInstance = new DbManager(path);
  }
  return m_pInstance;
}

DbManager *DbManager::Instance() { return m_pInstance; }

DbManager::DbManager(const QString &path) {
  auto db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(path);

  if (!db.open()) {
    qDebug() << "Error: connection with database fail";
  } else {
    qDebug() << "Database: connection ok " << db.isValid();
  }
  if (db.isOpen()) {
    auto list = db.tables();
    for (auto l : list) {
      qDebug() << l;
    }
  }
}

DbManager::~DbManager()
{
    QSqlDatabase::database().close();
}

QSqlTableModel *DbManager::CreateMyCompaniesModel() {
  QSqlTableModel *model = new QSqlTableModel(nullptr, QSqlDatabase::database());
  model->setTable(TableNames::mojeFirmy);
  model->select();

  for (const auto &it : ColumnNames::my_companies) {
    model->setHeaderData(it.first, Qt::Horizontal, it.second);
  }
  return model;
}

QSqlTableModel *DbManager::CreateContractorsModel() {

  QSqlTableModel *model = new QSqlTableModel(nullptr, QSqlDatabase::database());
  model->setTable(TableNames::konrahenci);
  model->select();

  for (const auto &it : ColumnNames::contractors) {
    model->setHeaderData(it.first, Qt::Horizontal, it.second);
  }
  return model;
}

QSqlRelationalTableModel *DbManager::CreateSalesModel(int companyId) {

  auto *model = new QSqlRelationalTableModel(nullptr, QSqlDatabase::database());
  model->setTable(TableNames::sprzedaz);
  model->setFilter("FirmaId='" + QString::number(companyId) + "'");

  model->setRelation(Sprzedaz::KontrahentId,
                     QSqlRelation(TableNames::konrahenci, "Id", "NazwaKontrahenta"));
  model->select();

  for (const auto &it : ColumnNames::sale) {
    model->setHeaderData(it.first, Qt::Horizontal, it.second);
  }

  return model;
}

QSqlRelationalTableModel *DbManager::CreatePurchaseModel(int companyId) {

  auto *model = new QSqlRelationalTableModel(nullptr, QSqlDatabase::database());
  model->setTable(TableNames::zakup);
  model->setFilter("FirmaId='" + QString::number(companyId) + "'");

  model->setRelation(Sprzedaz::KontrahentId,
                     QSqlRelation(TableNames::konrahenci, "Id", "NazwaKontrahenta"));
  model->select();

  for (const auto &it : ColumnNames::purchase) {
    model->setHeaderData(it.first, Qt::Horizontal, it.second);
  }

  return model;
}

QSqlTableModel* DbManager::Select(QString tableName)
{
    if (!QSqlDatabase::database().tables().contains(tableName))
    {
        QString queryText("CREATE TABLE IF NOT EXISTS :tableName () Id int primary key, JpkNumber varchar(255), Status int, UPO varchar(255))");
        QSqlQuery query(QSqlDatabase::database());
        query.prepare(queryText);
        query.bindValue(":tableName", tableName);
        query.exec();

        //dodanie do jpktables że taka została stworzona
    }

    auto *model = new QSqlTableModel(nullptr, QSqlDatabase::database());
    model->setTable(tableName);
    return model;
}



