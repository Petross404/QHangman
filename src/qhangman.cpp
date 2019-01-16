#include "qhangman.h"
#include "ui_qhangman.h"

QHangman::QHangman(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::QHangman)
{
    m_ui->setupUi(this);
}

QHangman::~QHangman() = default;
