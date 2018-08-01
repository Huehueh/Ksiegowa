#include "operationdialog.h"

#include <QAbstractSpinBox>
#include <QCalendarWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDateEdit>
#include <QEvent>

#include "dialogmanager.h"
#include "ui_tableDialog.h"


OperationDialog::OperationDialog(int companyId, QWidget *parent): QDialog(parent),
    ui(new Ui::OperationDialog()), mCompanyId(companyId), mSelectedIndex(0), mMapper(nullptr)
{
    ui->setupUi(this);
    connect(ui->dictButton, &QPushButton::clicked, this, [&](){
        DialogManager::OpenDictionaryDialog(this);
    });
    connect(ui->closeButton, &QPushButton::clicked, this, &OperationDialog::close);
}

bool OperationDialog::eventFilter(QObject *object, QEvent *event) {
  if (event->type() == QEvent::InputMethodQuery) {
    auto dateEdit = qobject_cast<QDateEdit *>(object);
    if (dateEdit && !dateEdit->calendarWidget()->isVisible()) {
      dateEdit->calendarWidget()->move(
          dateEdit->mapToGlobal(QPoint(0, dateEdit->height())));
      dateEdit->calendarWidget()->show();
      return true;
    }
  }
  return false;
}

void OperationDialog::SetupDateEdit(QDateEdit *dateEdit)
{
  dateEdit->setCalendarPopup(true);
  auto calendar = dateEdit->calendarWidget();
  calendar->setWindowFlags(Qt::Popup);

  dateEdit->installEventFilter(this);
  dateEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
  connect(calendar, &QCalendarWidget::clicked, this,
          [dateEdit, calendar](QDate date) {
            dateEdit->setDate(date);
            calendar->hide();
          });
}

void OperationDialog::LoadKValues(QSqlTableModel* model, int minCol, int maxCol, QGridLayout* layout, QDataWidgetMapper* mapper)
{
    const int maxRowCount = 5;
    int columnNumber = 0;
    int rowNumber = 0;
    for(int i = minCol; i<maxCol; i++)
    {
        rowNumber = i-minCol - maxRowCount * qRound(0.5f * columnNumber);
        if(rowNumber >= maxRowCount)
        {
            columnNumber+=2;
            rowNumber = i-minCol - maxRowCount * qRound(0.5f * columnNumber);
        }
        auto header = model->headerData(i, Qt::Horizontal).toString();
        layout->addWidget(new QLabel(header), rowNumber, columnNumber, Qt::AlignLeft);
        auto label = new QLineEdit();
        layout->addWidget(label, rowNumber, columnNumber+1, Qt::AlignLeft);
        mapper->addMapping(label, i);
    }
}

