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
	, graphScene( new QGraphicsScene )
	, graphView( new QGraphicsView( graphScene.data() ) )
	, brush( new QBrush( Qt::black ) )
	, lineHorizontal( new QGraphicsLineItem( QLineF(
	                          QPointF( 1, 0 ), QPointF( 1, 120 ) ) ) )
	, lineVertical( new QGraphicsLineItem( QLineF(
	                QPointF( 1, 120 ), QPointF( 40, 120 ) ) ) )
	, lineHorizontalSmall( new QGraphicsLineItem( QLineF(
	                               QPointF( 40, 90 ), QPointF( 40, 30 ) ) ) )
	, ellipseHead( new QGraphicsEllipseItem( QRectF(
	                        QPointF( 20, 50 ), QSizeF( 11, 16 ) ) ) )
	, rectBody( new QGraphicsRectItem( 100, 200, 20 , 40, Q_NULLPTR) )
{
	m_ui->setupUi( this );

	m_ui->gridLayout->addLayout( gridHangMan.data(), 0, 0 );
	m_ui->gridLayout->addLayout( vboxWidgets.data(), 0, 1 );

	gridHangMan->addWidget( graphView.data(), 0, 0 );
	vboxWidgets->addWidget( pointsLabel.data() );
	vboxWidgets->addWidget( enterBtn.data() );
	vboxWidgets->addWidget( resetBtn.data() );
	vboxWidgets->addWidget( quitBtn.data() );

	graphView->setAlignment( Qt::AlignCenter | Qt::AlignBottom );
	paintHangMan();
}

void QHangman::paintHangMan()
{
	QPen pen;
	pen.setWidth( 2 );
	graphScene->addLine( lineHorizontal.data()->line(), pen );
	graphScene->addLine( lineVertical.data()->line(), pen );
	graphScene->addLine( lineHorizontalSmall.data()->line(), pen );
	graphScene->addEllipse( ellipseHead.data()->rect(), pen);
	graphScene->addRect( rectBody.data()->rect(), pen );
}

void QHangman::paintEvent( QPaintEvent* e )
{
	QPainter painter;
	QPolygon poly;
}

QHangman::~QHangman() = default;
// kate: indent-mode cstyle; indent-width 8; replace-tabs off; tab-width 8; 
