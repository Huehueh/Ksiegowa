#ifndef SALEPURCHASEDELEGATE_H
#define SALEPURCHASEDELEGATE_H

#include <QSqlRelationalDelegate>

class SaleDelegate : public QSqlRelationalDelegate {
  Q_OBJECT
public:
  SaleDelegate(QObject *parent = nullptr);
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const override;
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override;

private:
  const QString dateFormat = "yyyy-MM-dd";
};

#endif // SALEPURCHASEDELEGATE_H
