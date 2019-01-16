#ifndef QHANGMAN_H
#define QHANGMAN_H

#include <QMainWindow>
#include <QScopedPointer>

namespace Ui {
class QHangman;
}

class QHangman : public QMainWindow
{
    Q_OBJECT

public:
    explicit QHangman(QWidget *parent = nullptr);
    ~QHangman() override;

private:
    QScopedPointer<Ui::QHangman> m_ui;
};

#endif // QHANGMAN_H
