#ifndef DIALOGTCP_H
#define DIALOGTCP_H

#include <QDialog>
#include <define.h>

namespace Ui {
class DialogTcp;
}

class DialogTcp : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTcp(QWidget *parent = 0);
    ~DialogTcp();

    void DialogShow(int UserID);

signals:
    void confirmMainWindows(bool ok, QString ip, int port);

private slots:
    void on_pshBtnOK_clicked();

    void on_pshBtnCancle_clicked();

private:

    void confim(bool);

    Ui::DialogTcp *ui;

    int m_FromID = DIALOG_INFO_NUL;
};

#endif // DIALOGTCP_H
