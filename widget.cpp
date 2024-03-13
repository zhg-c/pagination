#include "widget.h"
#include "ui_widget.h"
#include "database.h"

#include <QDebug>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QMutex>
#include <QThread>
#include <QtConcurrent>
#include <thread>
#include <QTimer>
#include <QUrlQuery>
#include <QPair>

Widget::Widget(QWidget *parent) : QWidget(parent),
    ui(new Ui::Widget),
    m_DataMode(new DataModel(this)),
    m_CurrPage(0),
    m_RowCount(0),
    m_TotalPage(0)
{
  ui->setupUi(this);
  InitDlg();
}

Widget::~Widget() { delete ui; }

void Widget::on_pushButton_clicked() {}

void Widget::InitDlg() {
    ui->tableView->setModel(m_DataMode);
    ui->label_RowCount->setText(QString("总数：0"));
    ui->lineEdit_Page->setValidator(new QIntValidator(this));
}

void Widget::UpdateData()
{
    ui->label_CurrPage->setText(QString::number(m_CurrPage) + "/" + QString::number(m_TotalPage));
    ui->pushButton_Previous->setEnabled(m_CurrPage > 1);
    ui->pushButton_Next->setEnabled(m_CurrPage < m_TotalPage);
    m_DataMode->ShowDatas(m_CurrPage - 1);
}

void Widget::on_pushButton_Sel_clicked()
{
    m_CurrPage = 1;
    Database::GetInstance().GetCount(m_RowCount);
    if(m_RowCount > ROWS_PER_PAGE)
    {
        m_TotalPage = m_RowCount / ROWS_PER_PAGE;
        if(m_RowCount % ROWS_PER_PAGE)
        {
            m_TotalPage++;
        }
    }
    else if(m_RowCount > 0)
    {
        m_TotalPage = 1;
    }
    else
    {
        m_RowCount = 0;
        m_CurrPage = 0;
    }
    ui->pushButton_Next->setEnabled(m_TotalPage > 1);
    ui->pushButton_Previous->setEnabled(false);
    ui->label_RowCount->setText(QString("总数：") + QString::number(m_RowCount));
    ui->label_CurrPage->setText(QString::number(m_CurrPage) + "/" + QString::number(m_TotalPage));
    if(!m_RowCount)
    {
        return;
    }
    m_DataMode->ShowDatas(m_CurrPage - 1);

}

void Widget::on_pushButton_Previous_clicked()
{
    if(m_CurrPage < 2)
    {
        return;
    }
    m_CurrPage--;
    UpdateData();
}

void Widget::on_pushButton_Next_clicked()
{
    if(m_CurrPage >= m_TotalPage)
    {
        return;
    }
    m_CurrPage++;
    UpdateData();
}

void Widget::on_pushButton_JumpPage_clicked()
{
    QString qstrTmp = ui->lineEdit_Page->text();
    if(qstrTmp.isEmpty())
    {
        return;
    }
    int Num = qstrTmp.toInt();
    if(Num < 1 || Num > m_TotalPage)
    {
        return;
    }
    m_CurrPage = Num;
    UpdateData();
}
