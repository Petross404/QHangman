#ifndef QHANGMAN_H
#define QHANGMAN_H

#include <QMainWindow>
#include <QtCore/QScopedPointer>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsLineItem>
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QGraphicsEllipseItem>

//#include "word.h"

namespace Ui
{
	class QHangman;
}

class QHangman : public QMainWindow
{
	Q_OBJECT

public:
	explicit QHangman ( QWidget* parent = nullptr );
	~QHangman() override;

	void setupConnections();

public slots:
	QString getStringOfLineEdit();
	void enterFnct();
	void printWord();
	void paintHangMan();
	void resetView();
	QString hideWord(QString str);

private:
	QScopedPointer<Ui::QHangman>	m_ui;
	QScopedPointer<QGridLayout>		gridHangMan;
	QScopedPointer<QVBoxLayout>		vboxWidgets;
	QScopedPointer<QLabel>		pointsLabel;
	QScopedPointer<QTextEdit>		outputTextEdit;
	QScopedPointer<QLineEdit>		lineEdit;
	QScopedPointer<QPushButton>		enterBtn;
	QScopedPointer<QPushButton>		resetBtn;
	QScopedPointer<QPushButton>		quitBtn;
	QScopedPointer<QGraphicsScene>	scene;
	QScopedPointer<QGraphicsView>	view;
	QScopedPointer<QBrush>		brush;
	QScopedPointer<QGraphicsLineItem>		lineHorizontal;
	QScopedPointer<QGraphicsLineItem>		lineVertical;
	QScopedPointer<QGraphicsLineItem>		lineHorizontalSmall;
	QScopedPointer<QGraphicsLineItem>		lineNeck;
	QScopedPointer<QGraphicsEllipseItem>	ellipseHead;
	QScopedPointer<QGraphicsRectItem>		rectBody;
	QScopedPointer<QGraphicsLineItem>		rightArm;
	QScopedPointer<QGraphicsLineItem>		leftArm;
	QScopedPointer<QGraphicsLineItem>		rightLeg;
	QScopedPointer<QGraphicsLineItem>		leftLeg;

	QString	mWord;
	char 	mChar;
	int		errorCnt;

protected:
	void paintEvent ( QPaintEvent* e ) override;
};

#endif // QHANGMAN_H
