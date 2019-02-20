#include "util.h"
#include "qrect.h"
#include "define.h"

namespace UTIL
{

void paly(QFrame *frame, int x, int y, CHESS_PIECES type) {
    frame->setGeometry(QRect(x, y, CHESS_PIECES_SIZE, CHESS_PIECES_SIZE));
    switch (type) {
    case WHITE:
        frame->setStyleSheet(QStringLiteral("image: url(:/images/white.png);"));
        break;
    case BLACK:
        frame->setStyleSheet(QStringLiteral("image: url(:/images/black.png);"));
        break;
    default:
        break;
    }
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    frame->show();
}

void setComboBoxData(QComboBox *combobox, QStringList data){
    combobox->clear();
    combobox->addItems(data);
}

template<typename T>
void m_Abs(T t1, T t2){
    if(t1 > t2){
        return t1 - t2;
    }
    return t2 - t1;
}

}
