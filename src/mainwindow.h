#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QFrame>
#include "qstack.h"
#include "define.h"
#include "type.h"
#include "dialoginfo.h"
#include "dialogtcp.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void mousePressEvent(QMouseEvent *event);

    void NotifyDialogConfirmMsg(bool ok);

    void NotifyDialogTcpMsg(bool ok, QString ip, int port);

    void on_pshBtnRetract_clicked();

    void on_rdoBtnWhite_clicked();

    void on_rdoBtnBlack_clicked();

    void on_pshBtnStart_clicked();

private:
    void init();
    void clear();
    void retract();
    bool getPositon(int &x, int &y);
    void initDialog();
    void initPalyType();
    void bunko();
    int getBunko();
    bool searchBunko(int x, int y, int num, int type);
    bool searchUpBunko(int x, int y, int num, int type);
    bool searchUpRightBunko(int x, int y, int num, int type);
    bool searchRightBunko(int x, int y, int num, int type);
    bool searchDownRightBunko(int x, int y, int num, int type);

private:
    Ui::MainWindow *ui;
    DialogInfo *dialogInfo = NULL;
    DialogTcp *dialogTcp = NULL;

    bool m_Sequence = true;
    int size = 0;

    QStack<QFrame *>  m_FrameStack;
    QStack<CHESS_PIECES_POSITION> m_PointStack;
    int m_Position_X[CHESSBOARD_H_LINE];
    int m_Position_Y[CHESSBOARD_V_LINE];

    int m_PiecesStatus[CHESSBOARD_H_LINE][CHESSBOARD_V_LINE];
    int m_Rank[CHESSBOARD_H_LINE][CHESSBOARD_V_LINE];
    int m_RankWhite[CHESSBOARD_H_LINE][CHESSBOARD_V_LINE];
    int m_RankBlack[CHESSBOARD_H_LINE][CHESSBOARD_V_LINE];

    PLAY_STATUS m_PlayStatus    = NEW;
    PALY_TYPE m_PalyType        = CUSTOM;

};

#endif // MAINWINDOW_H
