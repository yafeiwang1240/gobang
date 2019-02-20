#include "dialogtcp.h"
#include "ui_dialogtcp.h"

DialogTcp::DialogTcp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTcp)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
}

DialogTcp::~DialogTcp()
{
    delete ui;
}

void DialogTcp::DialogShow(int UserID) {
    m_FromID = UserID;
    this->show();
}

void DialogTcp::confim(bool ok){
    switch (m_FromID) {
    case DIALOG_INFO_MAINWINDOW:
        confirmMainWindows(ok, ui->tedIP->toPlainText(), ui->tedPort->toPlainText().toInt());
        break;
    default:
        break;
    }
    this->close();
}

void DialogTcp::on_pshBtnOK_clicked()
{
    confim(true);
}

void DialogTcp::on_pshBtnCancle_clicked()
{
    confim(false);
}
