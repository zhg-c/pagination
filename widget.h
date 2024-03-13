#ifndef WIDGET_H
#define WIDGET_H

#include "datamodel.h"

#include <QWidget>
#include <QShowEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_Sel_clicked();

    void on_pushButton_Previous_clicked();

    void on_pushButton_Next_clicked();

    void on_pushButton_JumpPage_clicked();

private:
    void InitDlg();
    void UpdateData();

private:
    Ui::Widget *ui;
    DataModel *m_DataMode;
    int m_CurrPage;
    int m_RowCount;
    int m_TotalPage;
};

#endif // WIDGET_H
