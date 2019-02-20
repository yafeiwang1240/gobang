#ifndef UTIL_H
#define UTIL_H
#include <QFrame>
#include <type.h>
#include <QComboBox>

namespace UTIL
{
    void paly(QFrame *frame, int x, int y, CHESS_PIECES type);

    void setComboBoxData(QComboBox *combobox, QStringList data);

    template<typename T>
    void m_Abs(T t1, T t2);
}

#endif // UTIL_H
