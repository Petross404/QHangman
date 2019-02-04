#include "qhangman.h"
#include "ui_qhangman.h"
//#include "word.h"
#include <QMessageBox>
#include <QTimer>
#include <QtCore/QRegularExpression>
#include <map>
#include <tuple>
#include <functional>
#include <random>
#include <memory>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

#define qOverload_l	qOverload<QLayout*, int, int, Qt::Alignment>
#define qOverload_lw	qOverload<QWidget*, int, int, Qt::Alignment>

#define QRegCondition (lineEdit->text().contains( QRegularExpression( "[0-9]" ) ) || lineEdit->text().contains( QRegularExpression( "[[:punct:]]" ) ) || lineEdit->text().contains( QRegularExpression( "[[:space:]]" ) ) )

//namespace wd = word;

QHangman::QHangman( QWidget* parent ) :
	QMainWindow( parent )
	, m_ui( new Ui::QHangman )
	, gridHangMan( new QGridLayout )
	, gridWidgets( new QGridLayout )
	, warningLabel( new QLabel )
	, pointsLabel( new QLabel( tr( "Points" ) ) )
	, outputTextEdit( new QTextEdit )
	, lineEdit( new QLineEdit )
	, lineWordEdit( new QLineEdit )
	, enterBtn( new QPushButton( tr( "Enter single character" ) ) )
	, wordBtn( new QPushButton( tr( "Enter word" ) ) )
	, resetBtn( new QPushButton( tr( "Reset word" ) ) )
	, quitBtn( new QPushButton( tr( "Quit" ) ) )
	, scene( new QGraphicsScene )
	, view( new QGraphicsView( scene.data() ) )
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
	, mWord( "" )
	, temporaryStr( "" )
	, errorCnt( 1 )
{
	std::invoke( &Ui::QHangman::setupUi, m_ui, this );
	std::invoke( qOverload<int, int>( &QHangman::setMinimumSize ), this, 650, 500 );
	std::invoke( &QGridLayout::setSizeConstraint, gridWidgets.data(), QLayout::SetMaximumSize );
	std::invoke( &QTextEdit::setTextInteractionFlags, outputTextEdit.data(),
	             ( Qt::TextSelectableByKeyboard |
	               Qt::TextSelectableByKeyboard ) );

	std::invoke( &QTextEdit::setAlignment,
	             outputTextEdit.data(),
	             ( Qt::AlignCenter | Qt::AlignVCenter ) );

	std::invoke( &QTextEdit::setFont, outputTextEdit.data(), ( QFont( "Times", 11, QFont::DemiBold ) ) );
	std::invoke( &QTextEdit::setMaximumHeight, outputTextEdit.data(), 35 );
	std::invoke( &QLabel::setMaximumHeight, warningLabel.data(), 30 );
	std::invoke( &QLabel::hide, warningLabel.data() );

	std::invoke( &QLineEdit::setMaximumHeight, lineEdit.data(), 30 );
	std::invoke( &QLineEdit::setFont, lineEdit.data(), ( QFont( "Oxygen Mono", 9, QFont::Bold ) ) );
	std::invoke( &QLineEdit::setMaxLength, lineEdit.data(), 1 );
	std::invoke( qOverload<>( &QLineEdit::setFocus ), lineEdit.data() );
	std::invoke( &QPushButton::setEnabled, enterBtn.data(), false );
	std::invoke( &QPushButton::setEnabled, wordBtn.data(), false );

	m_ui->gridLayout->addLayout( gridHangMan.data(), 0, 0 );
	m_ui->gridLayout->addLayout( gridWidgets.data(), 0, 1 );

	std::invoke( qOverload_lw( &QGridLayout::addWidget ), gridHangMan.data(),
	             view.data(), 0, 0, Qt::AlignCenter );
	std::invoke( qOverload_lw( &QGridLayout::addWidget ), gridHangMan.data(),
	             outputTextEdit.data(), 1, 0, Qt::AlignCenter );

	std::invoke( qOverload_lw( &QGridLayout::addWidget ), gridWidgets.data(),
	             warningLabel.data(), 0, 0, Qt::AlignCenter );
	std::invoke( qOverload_lw( &QGridLayout::addWidget ), gridWidgets.data(),
	             pointsLabel.data(), 1, 0, Qt::AlignCenter );
	gridWidgets->addWidget( lineEdit.data(), 2, 0 );
	gridWidgets->addWidget( lineWordEdit.data(), 2, 1 );
	gridWidgets->addWidget( enterBtn.data(), 3, 0 );
	gridWidgets->addWidget( wordBtn.data(), 3, 1 );
	gridWidgets->addWidget( resetBtn.data(), 4, 0 );
	gridWidgets->addWidget( quitBtn.data(), 5, 0 );

	std::invoke( &QLabel::setMinimumWidth, pointsLabel.data(), 250 );
	std::invoke( &QGraphicsView::setAlignment, view.data(), ( Qt::AlignCenter | Qt::AlignBottom ) );
	std::invoke( qOverload<const QRectF&, Qt::AspectRatioMode>( &QGraphicsView::fitInView ), view.data(),
	             scene.data()->sceneRect(), Qt::KeepAspectRatio );

	srand( static_cast<int>( time( 0 ) ) );		///It's best to call srand only once
	mWord = std::invoke( &QHangman::resetWord, this );
	temporaryStr = std::invoke( &QHangman::hideWord, this, mWord );
	std::invoke( &QHangman::printWord, this );

	connect( quitBtn.data(), &QPushButton::clicked, this, &QApplication::quit );
	connect( resetBtn.data(), &QPushButton::clicked, this, &QHangman::resetView );
	connect( enterBtn.data(), &QPushButton::clicked, this, &QHangman::printWord );

	connect( lineEdit.data(), &QLineEdit::returnPressed, enterBtn.data(), &QPushButton::click );

	//If the entered word is wrong, hang the user immediately!
	connect( wordBtn.data(), &QPushButton::clicked, this,
	         [this]()
	{
		if ( std::invoke( &QLineEdit::text, lineWordEdit.data() ) == mWord ) emit wordIsFound();
		else	//Call paintHangMan until all parts are painted
		{
			do
			{
				std::invoke( &QHangman::paintHangMan, this );
			}
			while ( errorCnt <= 11 );
		}
	} );

	connect( lineEdit.data(), &QLineEdit::textChanged, this,
	         [this]()
	{
		//Digits and other special characters aren't allowed.
		/*if ( lineEdit->text().contains( QRegularExpression( "[0-9]" ) )
			|| lineEdit->text().contains( QRegularExpression( "[[:punct:]]" ) )
			|| lineEdit->text().contains( QRegularExpression( "[[:space:]]" ) ) )*/
		std::function<void()> clear = [this]()
		{
			std::invoke( &QLabel::clear, warningLabel.data() );
			std::invoke( &QLabel::hide, warningLabel.data() );
		};
		auto str = std::invoke( &QLineEdit::text, lineEdit.data() );

		if ( QRegCondition )
		{
			std::function<void()> f = [this]()
			{
				if ( QRegCondition )
				{
					QString newline {warningLabel->text().isEmpty() ? QChar( '\0' )
					                 : QChar( '\n' )};
					std::invoke( &QLabel::setText, warningLabel.data(),
					             warningLabel->text() + newline + "the char "
					             + lineEdit->text() + " can't be contained in a word" );

					std::invoke( &QLabel::show, warningLabel.data() );
					std::invoke( &QPushButton::setEnabled, enterBtn.data(), false );
				}
			};
			QTimer::singleShot( 400, this, f ); //Don't fire up immediately, it's rude.
		}
		else if ( std::invoke( &decltype( str )::size, str ) > 0 )
		{
			std::invoke( clear );
			std::invoke( &QPushButton::setEnabled, enterBtn.data(), true );
		}
		else
		{
			std::invoke( clear );
		}
	} );

	connect( lineWordEdit.data(), &QLineEdit::textChanged, this,
	         [this]()
	{
		auto str_ = std::invoke( &QLineEdit::text, lineEdit.data() );
		if ( !std::invoke( &decltype( str_ )::isEmpty, str_ ) )
			std::invoke( &QPushButton::setEnabled, wordBtn.data(), true );
		else
			std::invoke( &QPushButton::setEnabled, wordBtn.data(), false );

		auto str = std::invoke( &QLineEdit::text, lineWordEdit.data() );
		if ( std::invoke( &decltype( str )::size, str ) == 1 )
		{
			std::function<void()> lambda = [this]()
			{
				//It's a stupid hack to re-check the same condition, but with fast enough deletion of the word
				//the warningLabel can stay shown with the text displayed even if the lineWordEdit size is 0.
				if ( lineWordEdit->text().size() == 1 )
				{
					std::invoke( &QLabel::setText, warningLabel.data(),
					             QStringLiteral( "Words aren't one character long ya' know!" ) );
					std::invoke( &QLabel::show, warningLabel.data() );
				}
			};
			QTimer::singleShot( 400, this, lambda );	//It's rude to fire up a warning immediately
		}
		else
		{
			std::invoke( &QLabel::clear, warningLabel.data() );
			std::invoke( &QLabel::hide, warningLabel.data() );
		}
	} );

	//Each time the user wants to write a character, the previous must be erased
	connect( enterBtn.data(), &QPushButton::clicked, lineEdit.data(), &QLineEdit::clear );
	//Finally, the user found the word
	connect( this, &QHangman::wordIsFound, this,
	         [this]()
	{
		std::invoke( &QHangman::celebrate, this );
		mWord = std::invoke( &QHangman::resetWord, this );
		temporaryStr = std::invoke( &QHangman::hideWord, this, mWord );
		std::invoke( &QHangman::printWord, this );
	} );
}

void QHangman::celebrate()
{
	QMessageBox::about( this,
	                    QStringLiteral( "Hooray!" ),
	                    QStringLiteral( "You have found the word!" ) );
	std::invoke( &QTextEdit::setText, outputTextEdit.data(), resetWord() );
}

QString QHangman::hideWord( QString str )
{
	size_t szStr = std::invoke( &QString::size, str );
	size_t nCharsToHide = szStr / 2;
	std::vector<int> v( szStr + 1 );

	for ( size_t i = 0; i <= nCharsToHide; ++i )
	{
		v.at( i ) = rand() % static_cast<int>( szStr );
	}

	for ( size_t i = 0; i <= szStr; ++i )
	{
		//At position i, replace the next 1 char with '-'
		std::invoke( qOverload<int, int, const QString&>( &QString::replace ), str,
		             v.at( i ), 1, "_" );
	}

	return str;
}

void QHangman::paintHangMan()
{
#ifdef ENABLE_OFFENSIVE
	QString msg {"Die little bitch!"};
#else
	QString msg {"Oops!"};
#endif
	QPen pen;
	QPen boldPen;
	pen.setWidth( 2 );
	boldPen.setWidth( 6 );
	using fncObj = std::function<void()>;
	fncObj draw1 = [this, pen]() {scene->addLine( lineHorizontal.data()->line(), pen );};
	fncObj draw2 = [this, pen]() {scene->addLine( lineVertical.data()->line(), pen );};
	fncObj draw3 = [this, pen]() {scene->addLine( lineHorizontalSmall.data()->line(), pen );};
	fncObj draw4 = [this, pen]() {scene->addEllipse( ellipseHead.data()->rect(), pen );};
	fncObj draw5 = [this, pen]() {scene->addLine( lineNeck.data()->line(), pen );};
	fncObj draw6 = [this, pen]() {scene->addRect( rectBody.data()->rect(), pen );};
	fncObj draw7 = [this, pen]() {scene->addLine( rightArm.data()->line(), pen );};
	fncObj draw8 = [this, pen]() {scene->addLine( leftArm.data()->line(), pen );};
	fncObj draw9 = [this, pen]() {scene->addLine( rightLeg.data()->line(), pen );};
	fncObj draw10 = [this, pen]() {scene->addLine( leftLeg.data()->line(), pen );};
	auto  drawFinal = [this, &msg]()
	{
		std::invoke( qOverload<const QString&, const QFont&>( &QGraphicsScene::addText ),
		             scene.data(), ( msg, QFont( "Arial", 20 ) ) );
		std::invoke( &QGraphicsScene::setBackgroundBrush, scene.data(), QBrush( Qt::red ) );
		std::invoke( qOverload<bool>(&QPushButton::setEnabled), enterBtn.data(), false );
		std::invoke( &QLineEdit::setEnabled, lineEdit.data(), false );
	};
	fncObj reset = [this]() {resetView();};

	std::map<int, std::function<void()>> mp
	{
		{1,	draw1},
		{2,	draw2},
		{3,	draw3},
		{4,	draw4},
		{5,	draw5},
		{6,	draw6},
		{7,	draw7},
		{8,	draw8},
		{9,	draw9},
		{10,	draw10},
		{11,	drawFinal},
		{12,	reset}
	};

	++errorCnt;		//Increment every time this fnc is called.
	mp.at( errorCnt )();	//Execute!
}

void QHangman::resetView()
{
	std::invoke( &QGraphicsScene::clear, scene );
	std::invoke( &QGraphicsScene::setBackgroundBrush, scene, ( QtBrush( Qt::White ) ) );
	errorCnt = 0;
}

QString QHangman::resetWord()
{
	std::vector<QString> v
	{
		"abcdef",
		"computer",
		"house",
		"kitchen",
		"desktop",
		"children"
	};
	auto i = ( rand() % v.size() );
	return v.at( i );
}

void QHangman::printWord()
{
	QString strChar = std::invoke( &QLineEdit::text, lineEdit.data() );

	std::invoke( &QTextEdit::setText, outputTextEdit.data(), temporaryStr );
	if ( ( !std::invoke( qOverload<const QString&, Qt::CaseSensitivity>( &QString::contains ), mWord,
	                     strChar, Qt::CaseInsensitive ) )
	                && ( !std::invoke( qOverload<const QString&, Qt::CaseSensitivity>( &QString::contains ),
	                                   temporaryStr, strChar, Qt::CaseInsensitive ) ) )
	{
		std::invoke( &QHangman::paintHangMan, this );
	}
	else if ( ( std::invoke( qOverload<const QString&, Qt::CaseSensitivity>( &QString::contains ), mWord,
	                         strChar, Qt::CaseInsensitive ) )
	                && ( !std::invoke( qOverload<const QString&, Qt::CaseSensitivity>( &QString::contains ), temporaryStr,
	                                   strChar, Qt::CaseInsensitive ) ) )
	{
		std::vector<int> v( std::invoke( &QString::size, mWord ) );
		int j{0};

		while ( ( j = std::invoke( qOverload<const QString&, int, Qt::CaseSensitivity>( &QString::indexOf ),
		                           strChar, j, Qt::CaseInsensitive ) ) != -1 )
		{
// 			std::invoke( qOverload<int, int, const QString&>( &QString::replace ), temporaryStr,
// 			             j, 1, strChar );
// 			std::invoke( qOverload<const QString&>( &QTextEdit::setText ), temporaryStr );
			++j;
		}
		if ( temporaryStr == mWord )
		{
			emit wordIsFound();
		}
	}
}

QHangman::~QHangman() = default;
// kate: indent-mode cstyle; indent-width 8; replace-tabs off; tab-width 8; 

