/********************************************************************************
** Form generated from reading UI file 'qhangman.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QHANGMAN_H
#define UI_QHANGMAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QHangman
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QHangman)
    {
        if (QHangman->objectName().isEmpty())
            QHangman->setObjectName(QString::fromUtf8("QHangman"));
        QHangman->resize(328, 227);
        centralWidget = new QWidget(QHangman);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        QHangman->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QHangman);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 328, 21));
        QHangman->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QHangman);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QHangman->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QHangman);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QHangman->setStatusBar(statusBar);

        retranslateUi(QHangman);

        QMetaObject::connectSlotsByName(QHangman);
    } // setupUi

    void retranslateUi(QMainWindow *QHangman)
    {
        QHangman->setWindowTitle(QApplication::translate("QHangman", "QHangman", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QHangman: public Ui_QHangman {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QHANGMAN_H
