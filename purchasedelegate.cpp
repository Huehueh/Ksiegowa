#include "purchasedelegate.h"

#include <QDateEdit>
#include <QLineEdit>
#include <QLabel>

#include "enums.h"

PurchaseDelegate::PurchaseDelegate(QObject *parent)
    : QSqlRelationalDelegate(parent) {}

QWidget *PurchaseDelegate::createEditor(QWidget *parent,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const {
  auto role = static_cast<Zakup::eData>(index.column());
  switch (role) {
  case Zakup::DataZakupu:
  case Zakup::DataWplywu: {
    return new QDateEdit(parent);
  }
  case Zakup::KontrahentId: {
    return new QLabel(parent);
  }
  default: {
    return QSqlRelationalDelegate::createEditor(parent, option, index);
  }
  }
}

void PurchaseDelegate::setEditorData(QWidget *editor,
                                         const QModelIndex &index) const {
  auto role = static_cast<Zakup::eData>(index.column());
  switch (role) {
  case Zakup::DataZakupu:
  case Zakup::DataWplywu:  {
    auto value = index.model()->data(index, Qt::EditRole).toString();
    auto dateEdit = static_cast<QDateEdit *>(editor);
    QDate date = QDate::fromString(value, dateFormat);
    dateEdit->setDate(date);
    break;
  }
  case Zakup::KontrahentId: {
    auto value = index.model()->data(index, Qt::EditRole).toString();
    auto label = static_cast<QLabel *>(editor);
    label->setText(value);
    break;
  }
  default: {
    QSqlRelationalDelegate::setEditorData(editor, index);
    break;
  }
  }
}

void PurchaseDelegate::setModelData(QWidget *editor,
                                        QAbstractItemModel *model,
                                        const QModelIndex &index) const {
  auto role = static_cast<Zakup::eData>(index.column());
  switch (role) {
  case Sprzedaz::DataSprzedazy:
  case Sprzedaz::DataWystawienia: {
    QDateEdit *dateEdit = static_cast<QDateEdit *>(editor);
    QDate date = dateEdit->date();
    auto value = date.toString(dateFormat);
    model->setData(index, value, Qt::EditRole);
    break;
  }
  default: { break; }
  }
}

