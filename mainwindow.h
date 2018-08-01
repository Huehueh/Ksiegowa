#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <dbmanager.h>
#include <QAction>
#include <QActionGroup>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void OnRemoveClicked();
  void CreateJPKFiles();

private:

  void CreateMenuBar();
  void CreateMapper();
  void SetupTableView();

  Ui::MainWindow *ui;
  QSqlTableModel *m_tableModel;
};

#endif // MAINWINDOW_H
