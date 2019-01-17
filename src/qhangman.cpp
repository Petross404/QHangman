#include "qhangman.h"
#include "ui_qhangman.h"

QHangman::QHangman( QWidget* parent ) :
	QMainWindow( parent )
	, m_ui( new Ui::QHangman )
	, gridHangMan( new QGridLayout )
	, vboxWidgets( new QVBoxLayout )
	, pointsLabel( new QLabel( tr( "Points" ) ) )
	, outputTextEdit( new QTextEdit )
	, lineEdit( new QLineEdit )
	, enterBtn( new QPushButton( tr( "Enter" ) ) )
	, resetBtn( new QPushButton( tr( "Reset Word" ) ) )
	, quitBtn( new QPushButton( tr( "Quit" ) ) )
	, graphScene( new QGraphicsScene )
	, graphView( new QGraphicsView( graphScene.data() ) )
	, brush( new QBrush( Qt::black ) )
	, lineHorizontal( new QGraphicsLineItem( QLineF(
	                          QPointF( 1, 0 ), QPointF( 1, 180 ) ) ) )
	, lineVertical( new QGraphicsLineItem( QLineF(
	                QPointF( 99, 0 ), QPointF( 0, 0 ) ) ) )
	, lineHorizontalSmall( new QGraphicsLineItem( QLineF(
	                               QPointF( 99, 0 ), QPointF( 99, 40 ) ) ) )
	, lineNeck( new QGraphicsLineItem( QLineF( QPointF( 99, 85 ), QPointF( 99, 70 ) ) ) )
	, ellipseHead( new QGraphicsEllipseItem( QRectF(
	                        QPointF( 88, 40 ), QSizeF( 21, 30 ) ) ) )
	, rectBody( new QGraphicsRectItem( 89, 87, 20, 40, Q_NULLPTR ) )
	, rightArm( new QGraphicsLineItem( 57, 96, 87, 89, Q_NULLPTR ) )
	, leftArm( new QGraphicsLineItem( 108, 89, 137, 96, Q_NULLPTR ) )
	, rightLeg( new QGraphicsLineItem( QLineF( QPointF( 89, 129 ), QPointF( 79, 158 ) ) ) )
	, leftLeg( new QGraphicsLineItem( QLineF( QPointF( 110, 129 ), QPointF( 120, 158 ) ) ) )
	, mWord( "computer" )
{
	m_ui->setupUi( this );
	setMinimumSize( 650, 500 );
	vboxWidgets->setSizeConstraint( QLayout::SetMaximumSize );
	outputTextEdit->setTextInteractionFlags( Qt::TextSelectableByMouse 
						| Qt::TextSelectableByKeyboard );
	outputTextEdit->setAlignment(Qt::AlignJustify | Qt::AlignVCenter);
	outputTextEdit->setFont(QFont("Times", 10, QFont::Bold));
	outputTextEdit->setMaximumHeight( 35 );
	lineEdit->setMaximumHeight( 30 );
	lineEdit->setFont(QFont("Oxygen Mono", 9, QFont::Bold));

	m_ui->gridLayout->addLayout( gridHangMan.data(), 0, 0 );
	m_ui->gridLayout->addLayout( vboxWidgets.data(), 0, 1 );

	gridHangMan->addWidget( graphView.data(), 0, 0 );
	vboxWidgets->addWidget( pointsLabel.data() );
	vboxWidgets->addWidget( outputTextEdit.data() );
	vboxWidgets->addWidget( lineEdit.data() );
	vboxWidgets->addWidget( enterBtn.data() );
	vboxWidgets->addWidget( resetBtn.data() );
	vboxWidgets->addWidget( quitBtn.data() );

	pointsLabel->setMinimumWidth( 250 );
	graphView->setAlignment( Qt::AlignCenter | Qt::AlignBottom );
// 	graphView->ensureVisible(graphScene.data()->sceneRect());
	graphView->fitInView( graphScene.data()->sceneRect(), Qt::KeepAspectRatio );

	setupConnections();
	printWord();
	//paintHangMan();
}

QString QHangman::getStringOfLineEdit()
{
	return lineEdit->text();
}

void QHangman::paintHangMan()
{
	QPen pen;
	QPen boldPen;
	pen.setWidth( 2 );
	boldPen.setWidth( 6 );
	graphScene->addLine( lineHorizontal.data()->line(), pen );
	graphScene->addLine( lineVertical.data()->line(), pen );
	graphScene->addLine( lineHorizontalSmall.data()->line(), pen );
	graphScene->addEllipse( ellipseHead.data()->rect(), pen );
	graphScene->addLine( lineNeck.data()->line(), pen );
	graphScene->addRect( rectBody.data()->rect(), pen );
	graphScene->addLine( rightArm.data()->line(), pen );
	graphScene->addLine( leftArm.data()->line(), pen );
	graphScene->addLine( rightLeg.data()->line(), pen );
	graphScene->addLine( leftLeg.data()->line(), pen );
}

void QHangman::resetView()
{
	graphScene->clear();
}

void QHangman::setupConnections()
{
	connect( quitBtn.data(), &QPushButton::clicked, this, &QApplication::quit );
	connect( resetBtn.data(), &QPushButton::clicked, this, &QHangman::resetView );
	connect( enterBtn.data(), &QPushButton::clicked, this, &QHangman::printWord );
	connect( lineEdit.data(), &QLineEdit::returnPressed, enterBtn.data(), &QPushButton::clicked );

	//Each time the user wants to write a character, the previous must be erased
	connect( enterBtn.data(), &QPushButton::clicked, lineEdit.data(), &QLineEdit::clear );
}

void QHangman::paintEvent( QPaintEvent* e )
{
	QPainter painter;
	QPolygon poly;
}

void QHangman::printWord()
{
	
	QString a = getStringOfLineEdit();
	if (!mWord.contains(a, Qt::CaseInsensitive))
	{
		paintHangMan();
	}
	else outputTextEdit->setText( mWord );
}

QHangman::~QHangman() = default;
// kate: indent-mode cstyle; indent-width 8; replace-tabs off; tab-width 8; 
