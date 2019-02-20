#ifndef DIALOGINFO_H
#define DIALOGINFO_H

#include <QDialog>
#include "define.h"

namespace Ui {
class DialogInfo;
}

class DialogInfo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInfo(QWidget *parent = 0);
    ~DialogInfo();

    void DialogShow(int UserPageId, QString title, QString info, bool ok = true, bool cancle = true);

private:
    void confim(bool);


    Ui::DialogInfo *ui;

    int m_FromID = DIALOG_INFO_NUL;

signals:
    void confirmMainWindows(bool ok);

private slots:

    void on_pshBtnOk_clicked();

    void on_pshBtnCancle_clicked();
};

#endif // DIALOGINFO_H
