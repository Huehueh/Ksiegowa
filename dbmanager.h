#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QString>
#include <QSqlQueryModel>

class DbManager {
public:
  static DbManager *CreateInstance(const QString &path);
  static DbManager *Instance();
  static QSqlTableModel *CreateMyCompaniesModel();
  static QSqlTableModel *CreateContractorsModel();
  static QSqlRelationalTableModel *CreateSalesModel(int companyId);
  static QSqlRelationalTableModel *CreatePurchaseModel(int companyId);
  static QSqlTableModel* Select(QString tableName);

private:
  DbManager(const QString &path);
  virtual ~DbManager();
  static DbManager *m_pInstance;
};

#endif // DBMANAGER_H
