#ifndef PURCHASEDELEGATE_H
#define PURCHASEDELEGATE_H

#include <QSqlRelationalDelegate>


class PurchaseDelegate : public QSqlRelationalDelegate
{
    Q_OBJECT
public:
    explicit PurchaseDelegate(QObject *parent = nullptr);
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

signals:

public slots:

private:
     const QString dateFormat = "yyyy-MM-dd";
};

#endif // PURCHASEDELEGATE_H
