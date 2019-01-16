#ifndef QHANGMAN_H
#define QHANGMAN_H

#include <QMainWindow>
#include <QScopedPointer>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>

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

private:
	QScopedPointer<Ui::QHangman>	m_ui;
	QScopedPointer<QGridLayout>	gridHangMan;
	QScopedPointer<QVBoxLayout>	vboxWidgets;
	QScopedPointer<QLabel>		pointsLabel;
	QScopedPointer<QPushButton>	enterBtn;
	QScopedPointer<QPushButton>	resetBtn;
	QScopedPointer<QPushButton>	quitBtn;
	QScopedPointer<QGraphicsScene>	graphScene;
	QScopedPointer<QGraphicsView>	graphView;
	QScopedPointer<QBrush>		brush;
	QScopedPointer<QGraphicsLineItem>	lineHorizontal;
	QScopedPointer<QGraphicsLineItem>	lineVertical;
	QScopedPointer<QGraphicsLineItem>	lineHorizontalSmall;

protected:
	void paintEvent(QPaintEvent* e) override;
};

#endif // QHANGMAN_H
