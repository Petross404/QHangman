#include "qhangman.h"
#include "ui_qhangman.h"

QHangman::QHangman( QWidget* parent ) :
	QMainWindow( parent )
	, m_ui( new Ui::QHangman )
	, gridHangMan( new QGridLayout )
	, vboxWidgets( new QVBoxLayout )
	, pointsLabel( new QLabel( tr( "Points" ) ) )
	, enterBtn( new QPushButton( tr( "Enter" ) ) )
	, resetBtn( new QPushButton( tr( "Reset Word" ) ) )
	, quitBtn( new QPushButton( tr( "Quit" ) ) )
	, graphScene( new QGraphicsScene)
	, graphView (new QGraphicsView(graphScene.data()))
	, brush(new QBrush(Qt::black))
	, lineHorizontal(new QGraphicsLineItem(QPointF(1, 1), QPointF(1, 10)))
{
	m_ui->setupUi( this );

	m_ui->gridLayout->addLayout( gridHangMan.data(), 0, 0 );
	m_ui->gridLayout->addLayout( vboxWidgets.data(), 0, 1 );
	vboxWidgets->addWidget( pointsLabel.data() );
	vboxWidgets->addWidget( enterBtn.data() );
	vboxWidgets->addWidget( resetBtn.data() );
	vboxWidgets->addWidget( quitBtn.data() );

}

void QHangman::paintHangMan()
{
	
}

void QHangman::paintEvent(QPaintEvent* e)
{
	QPainter painter;
	QPolygon poly;

	
}

QHangman::~QHangman() = default;
// kate: indent-mode cstyle; indent-width 8; replace-tabs off; tab-width 8; 
