#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "util.h"
#include "type.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    initDialog();
    initPalyType();
}

MainWindow::~MainWindow()
{
    clear();
    if(dialogInfo){
        dialogInfo->close();
        delete dialogInfo;
    }
    delete ui;
}

void MainWindow::initDialog() {
    dialogInfo = new DialogInfo();
    dialogTcp = new DialogTcp();
    connect(dialogInfo, SIGNAL(confirmMainWindows(bool)), this, SLOT(NotifyDialogConfirmMsg(bool)));
    connect(dialogTcp, SIGNAL(confirmMainWindows(bool,QString,int)), SLOT(NotifyDialogTcpMsg(bool,QString,int)));
}

void MainWindow::initPalyType() {
    QStringList data;
    data << "custom" << "man-machine" << "man-man";
    UTIL::setComboBoxData(ui->cbbPalyType, data);

}

void MainWindow::init() {

    for(int i = 0 ; i < CHESSBOARD_H_LINE; i++){
        m_Position_X[i] = CHESSBOARD_START_X +
                i * (CHESSBOARD_END_X - CHESSBOARD_START_X) / (CHESSBOARD_H_LINE - 1);
    }
    for(int i = 0 ; i < CHESSBOARD_V_LINE; i++){
        m_Position_Y[i] = CHESSBOARD_START_Y +
                i * (CHESSBOARD_END_Y - CHESSBOARD_START_Y) / (CHESSBOARD_V_LINE - 1);
    }
    for(int i = 0; i < CHESSBOARD_H_LINE; i++){
        for(int j = 0; j < CHESSBOARD_V_LINE; j++){
            m_PiecesStatus[i][j] = NUL;
        }
    }
}

void MainWindow::clear() {

    int temp = size;
    m_PlayStatus = NEW;
    for(int i = 0; i < temp; i++){
        retract();
    }
}

bool MainWindow::getPositon(int &x, int &y) {

    if(m_PlayStatus > PLAYING){
        return false;
    }

    // mouse out chessboard
    if(x < MOUSE_EVENT_MIN_X
            || x > MOUSE_EVENT_MAX_X
            || y < MOUSE_EVENT_MIN_Y
            || y > MOUSE_EVENT_MAX_Y)
    {
        return false;
    }

    // calculate x index
    int index_x = 0, index_y = 0;
    if(x < m_Position_X[0]){
        index_x = 0;
    }else if(x > m_Position_X[CHESSBOARD_H_LINE - 1]){
        index_x = CHESSBOARD_H_LINE - 1;
    }else {
        index_x = (x - CHESSBOARD_START_X)
                / ((CHESSBOARD_END_X - CHESSBOARD_START_X) / (CHESSBOARD_H_LINE - 1));
        if((x - CHESSBOARD_START_X) % ((CHESSBOARD_END_X - CHESSBOARD_START_X) / (CHESSBOARD_H_LINE - 1))
                > ((CHESSBOARD_END_X - CHESSBOARD_START_X) / (CHESSBOARD_H_LINE - 1)) / 2) {
            index_x++;
        }
    }

    // calculate y index
    if(y < m_Position_Y[0]){
        index_y = 0;
    }else if(x > m_Position_Y[CHESSBOARD_V_LINE - 1]){
        index_y = CHESSBOARD_V_LINE - 1;
    }else {
        index_y = (y - CHESSBOARD_START_Y)
                / ((CHESSBOARD_END_Y - CHESSBOARD_START_Y) / (CHESSBOARD_V_LINE - 1));
        if((y - CHESSBOARD_START_Y) % ((CHESSBOARD_END_Y - CHESSBOARD_START_Y) / (CHESSBOARD_V_LINE - 1))
                > ((CHESSBOARD_END_Y - CHESSBOARD_START_Y) / (CHESSBOARD_V_LINE - 1)) / 2) {
            index_y++;
        }
    }

    // already exist pieces
    if(m_PiecesStatus[index_x][index_y] != NUL){
        return false;
    }

    // calculate x, y
    x = CHESSBOARD_START_X +
            index_x * (CHESSBOARD_END_X - CHESSBOARD_START_X) / (CHESSBOARD_H_LINE - 1);
    y = CHESSBOARD_START_Y +
            index_y * (CHESSBOARD_END_Y - CHESSBOARD_START_Y) / (CHESSBOARD_V_LINE - 1);

    // be placed in the middle
    x -= CHESS_PIECES_SIZE / 2;
    y -= CHESS_PIECES_SIZE / 2;

     // set pieces exist
    m_PiecesStatus[index_x][index_y] = m_Sequence ? BLACK : WHITE;
    CHESS_PIECES_POSITION point;
    point.INDEX_X = index_x;
    point.INDEX_Y = index_y;
    m_PointStack.push(point);
    return true;
}

void MainWindow::retract() {
    if(size <= 0){
        return;
    }
    ui->rdoBtnWhite->setChecked(m_Sequence);
    m_Sequence = m_Sequence ? false : true;
    ui->rdoBtnBlack->setChecked(m_Sequence);
    size--;
    QFrame *frame = m_FrameStack.pop();
    CHESS_PIECES_POSITION point = m_PointStack.pop();
    m_PiecesStatus[point.INDEX_X][point.INDEX_Y] = NUL;
    delete frame;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    int x = event->x();
    int y = event->y();
    if(!getPositon(x, y)){
        return;
    }
    m_PlayStatus = PLAYING;

    QFrame *frame = new QFrame(MainWindow::centralWidget());
    UTIL::paly(frame, x, y, m_Sequence ? BLACK : WHITE);
    ui->rdoBtnWhite->setChecked(m_Sequence);
    m_Sequence = m_Sequence ? false : true;
    ui->rdoBtnBlack->setChecked(m_Sequence);
    size++;
    m_FrameStack.push(frame);
    bunko();
}

void MainWindow::bunko() {
    int result = getBunko();
    QString title = "提示";
    QString info;
    switch (result) {
    case WHITE:
        info = "白棋获胜";
        break;
    case BLACK:
        info = "黑棋获胜";
        break;
    default:
        break;
    }
    if(result > NUL){
       dialogInfo->DialogShow(DIALOG_INFO_MAINWINDOW, title, info, false, true);
    }
}

int MainWindow::getBunko() {
    for(int i = 0; i < CHESSBOARD_H_LINE; i++){
        for(int j = 0; j < CHESSBOARD_V_LINE; j++){
            if(m_PiecesStatus[i][j] > NUL && searchBunko(i, j, 0, m_PiecesStatus[i][j])){
                return m_PiecesStatus[i][j];
            }
        }
    }
    return NUL;
}

bool MainWindow::searchBunko(int x, int y, int num, int type) {


    if(searchUpBunko(x, y, num, type)
            || searchUpRightBunko(x, y, num, type)
            || searchRightBunko(x, y, num, type)
            || searchDownRightBunko(x, y, num, type)){
        return true;
    }
    return false;
}

bool MainWindow::searchUpBunko(int x, int y, int num, int type) {

    num++;

    if(num >= 5){
        return true;
    }

    if(y - 1 < 0){
        return false;
    }

    if(type == m_PiecesStatus[x][y - 1]){
        return searchUpBunko(x, y - 1, num, type);
    }
    return false;
}

bool MainWindow::searchUpRightBunko(int x, int y, int num, int type) {

    num++;

    if(num >= 5){
        return true;
    }

    if(y - 1 < 0 || x + 1 >= CHESSBOARD_H_LINE){
        return false;
    }

    if(type == m_PiecesStatus[x + 1][y - 1]){
        return searchUpRightBunko(x + 1, y - 1, num, type);
    }
    return false;
}

bool MainWindow::searchRightBunko(int x, int y, int num, int type) {

    num++;

    if(num >= 5){
        return true;
    }

    if(x + 1 >= CHESSBOARD_H_LINE){
        return false;
    }

    if(type == m_PiecesStatus[x + 1][y]){
        return searchRightBunko(x + 1, y, num, type);
    }
    return false;
}

bool MainWindow::searchDownRightBunko(int x, int y, int num, int type) {

    num++;

    if(num >= 5){
        return true;
    }

    if(y + 1 >= CHESSBOARD_V_LINE || x + 1 >= CHESSBOARD_H_LINE){
        return false;
    }

    if(type == m_PiecesStatus[x + 1][y + 1]){
        return searchDownRightBunko(x + 1, y + 1, num, type);
    }
    return false;
}

void MainWindow::NotifyDialogConfirmMsg(bool ok) {
    m_PlayStatus = END;
}

void MainWindow::NotifyDialogTcpMsg(bool ok, QString ip, int port) {

}

void MainWindow::on_pshBtnRetract_clicked()
{
    retract();
}

void MainWindow::on_rdoBtnWhite_clicked()
{
    m_Sequence = false;
}

void MainWindow::on_rdoBtnBlack_clicked()
{
    m_Sequence = true;
}

void MainWindow::on_pshBtnStart_clicked()
{
    clear();
}
