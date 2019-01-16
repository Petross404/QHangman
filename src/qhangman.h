#ifndef QHANGMAN_H
#define QHANGMAN_H

#include <QMainWindow>
#include <QScopedPointer>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsLineItem>
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QGraphicsEllipseItem>

namespace Ui
{
	class QHangman;
}

class QHangman : public QMainWindow
{
	Q_OBJECT

public:
	explicit QHangman ( QWidget *parent = nullptr );
	~QHangman() override;

	void paintHangMan();
	void setupConnections();
	void resetView();

private:
	QScopedPointer<Ui::QHangman>	m_ui;
	QScopedPointer<QGridLayout>	gridHangMan;
	QScopedPointer<QVBoxLayout>	vboxWidgets;
	QScopedPointer<QLabel>		pointsLabel;
	QScopedPointer<QLabel>		outputLabel;
	QScopedPointer<QTextEdit>	textEdit;
	QScopedPointer<QPushButton>	enterBtn;
	QScopedPointer<QPushButton>	resetBtn;
	QScopedPointer<QPushButton>	quitBtn;
	QScopedPointer<QGraphicsScene>	graphScene;
	QScopedPointer<QGraphicsView>	graphView;
	QScopedPointer<QBrush>		brush;
	QScopedPointer<QGraphicsLineItem>	lineHorizontal;
	QScopedPointer<QGraphicsLineItem>	lineVertical;
	QScopedPointer<QGraphicsLineItem>	lineHorizontalSmall;
	QScopedPointer<QGraphicsLineItem>	lineNeck;
	QScopedPointer<QGraphicsEllipseItem>	ellipseHead;
	QScopedPointer<QGraphicsRectItem>	rectBody;
	QScopedPointer<QGraphicsLineItem>	rightArm;
	QScopedPointer<QGraphicsLineItem>	leftArm;
	QScopedPointer<QGraphicsLineItem>	rightLeg;
	QScopedPointer<QGraphicsLineItem>	leftLeg;

protected:
	void paintEvent(QPaintEvent* e) override;
};

#endif // QHANGMAN_H
