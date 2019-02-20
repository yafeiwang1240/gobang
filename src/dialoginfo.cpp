#include "dialoginfo.h"
#include "ui_dialoginfo.h"

DialogInfo::DialogInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInfo)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
}

DialogInfo::~DialogInfo()
{
    delete ui;
}

void DialogInfo::DialogShow(int UserPageId, QString title, QString info, bool ok, bool cancle) {

    m_FromID = UserPageId;

    ui->labTitle->setText(title);
    ui->labInfo->setText(info);
    ui->pshBtnCancle->setEnabled(cancle);
    ui->pshBtnCancle->setVisible(cancle);
    ui->pshBtnOk->setEnabled(ok);
    ui->pshBtnOk->setVisible(ok);
    this->show();
}

void DialogInfo::confim(bool ok){
    switch (m_FromID) {
    case DIALOG_INFO_MAINWINDOW:
        emit confirmMainWindows(ok);
        break;
    default:
        break;
    }
    this->close();
}

void DialogInfo::on_pshBtnOk_clicked()
{
    confim(true);
}

void DialogInfo::on_pshBtnCancle_clicked()
{
    confim(false);
}
