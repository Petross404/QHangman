#include "qhangman.h"
#include "ui_qhangman.h"
//#include "word.h"
#include <QMessageBox>
#include <QTimer>
#include <QtCore/QRegularExpression>
#include <map>
#include <functional>
#include <random>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

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
	m_ui->setupUi( this );
	setMinimumSize( 650, 500 );
	gridWidgets->setSizeConstraint( QLayout::SetMaximumSize );
	outputTextEdit->setTextInteractionFlags( Qt::TextSelectableByMouse
	                | Qt::TextSelectableByKeyboard );
	outputTextEdit->setAlignment( Qt::AlignCenter | Qt::AlignVCenter );
	outputTextEdit->setFont( QFont( "Times", 11, QFont::DemiBold ) );
	outputTextEdit->setMaximumHeight( 35 );
	warningLabel->setMaximumHeight( 30 );
	warningLabel->hide();
	lineEdit->setMaximumHeight( 30 );
	lineEdit->setFont( QFont( "Oxygen Mono", 9, QFont::Bold ) );
	lineEdit->setMaxLength( 1 );
	lineEdit->setFocus();
	enterBtn->setEnabled( false );
	wordBtn->setEnabled( false );

	m_ui->gridLayout->addLayout( gridHangMan.data(), 0, 0 );
	m_ui->gridLayout->addLayout( gridWidgets.data(), 0, 1 );

	gridHangMan->addWidget( view.data(), 0, 0 );
	gridHangMan->addWidget( outputTextEdit.data(), 1, 0 );
	gridWidgets->addWidget( warningLabel.data(), 0, 0 );
	gridWidgets->addWidget( pointsLabel.data(), 1, 0 );
	gridWidgets->addWidget( lineEdit.data(), 2, 0 );
	gridWidgets->addWidget( lineWordEdit.data(), 2, 1 );
	gridWidgets->addWidget( enterBtn.data(), 3, 0 );
	gridWidgets->addWidget( wordBtn.data(), 3, 1 );
	gridWidgets->addWidget( resetBtn.data(), 4, 0 );
	gridWidgets->addWidget( quitBtn.data(), 5, 0 );

	pointsLabel->setMinimumWidth( 250 );
	//scene->addPixmap(QPixmap(":/resources/maxresdefault.jpg"));
	view->setAlignment( Qt::AlignCenter | Qt::AlignBottom );
	view->fitInView( scene.data()->sceneRect(), Qt::KeepAspectRatio );

	srand( static_cast<int>( time( 0 ) ) );		///It's best to call srand only once
	mWord = resetWord();
	temporaryStr = hideWord( mWord );
	printWord();

	connect( quitBtn.data(), &QPushButton::clicked, this, &QApplication::quit );
	connect( resetBtn.data(), &QPushButton::clicked, this, &QHangman::resetView );
	connect( enterBtn.data(), &QPushButton::clicked, this, &QHangman::printWord );

	connect( lineEdit.data(), &QLineEdit::returnPressed, enterBtn.data(), &QPushButton::click );

	//If the entered word is wrong, hang the user immediately!
	connect( wordBtn.data(), &QPushButton::clicked, this,
	         [this]()
	{
		if ( lineWordEdit.data()->text() == mWord ) emit wordIsFound();
		else	//Call paintHangMan until all parts are painted
		{
			do
			{
				paintHangMan();
			}
			while ( errorCnt <= 11 );
		}
	} );

	connect( lineEdit.data(), &QLineEdit::textChanged, this,
	         [this]()
	{
		if ( !lineEdit->text().isEmpty() ) { enterBtn->setEnabled( true ); }
		else { enterBtn->setEnabled( false ); }

		//Digits and other special characters aren't allowed.
		if ( lineEdit->text().contains( QRegularExpression( "[0-9]" ) )
		                || lineEdit->text().contains( QRegularExpression( "[[:punct:]]" ) ) )
		{
			auto lambda = [this]()
			{
				QString msg {QStringLiteral( "d can't be contained" )};
				QString newline {warningLabel->text().isEmpty() ? QChar( '\0' )
				                 : QChar( '\n' )};
				warningLabel->setText( warningLabel->text() + newline + msg );
				warningLabel->show();
			};
			QTimer::singleShot( 400, this, lambda ); //Don't fire up immediately, it's rude.
		}
		else
		{
			warningLabel->clear();
			warningLabel->hide();
		}

	} );

	connect( lineWordEdit.data(), &QLineEdit::textChanged, this,
	         [this]()
	{
		if ( !lineWordEdit->text().isEmpty() ) { wordBtn->setEnabled( true ); }
		else { wordBtn->setEnabled( false ); }

		if ( lineWordEdit->text().size() == 1 )
		{
			auto lambda = [this]()
			{
				//It's a stupid hack to re-check the same condition, but with fast enough deletion of the word
				//the warningLabel can stay shown with the text displayed even if the lineWordEdit size is 0.
				if ( lineWordEdit->text().size() == 1 )
				{
					warningLabel->setText( "Words aren't one character long ya' know!" );
					warningLabel->show();
				}
			};
			QTimer::singleShot( 400, this, lambda );
		}
		else
		{
			warningLabel->clear();
			warningLabel->hide();
		}
	} );

	//Each time the user wants to write a character, the previous must be erased
	connect( enterBtn.data(), &QPushButton::clicked, lineEdit.data(), &QLineEdit::clear );
	//Finally, the user found the word
	connect( this, &QHangman::wordIsFound, this,
	         [this]()
	{
		celebrate();
		mWord = resetWord();
		temporaryStr = hideWord( mWord );
		printWord();
	} );
}

void QHangman::celebrate()
{
	QMessageBox::about( this,
	                    QStringLiteral( "Hooray!" ),
	                    QStringLiteral( "You have found the word!" ) );
	outputTextEdit->setText( resetWord() );
}

QString QHangman::hideWord( QString str )
{
	size_t szStr = str.size();
	size_t nCharsToHide = szStr / 2;
	std::vector<int> v( szStr + 1 );

	for ( size_t i = 0; i <= nCharsToHide; ++i )
	{
		v.at( i ) = rand() % static_cast<int>( szStr );
	}

	for ( size_t i = 0; i <= szStr; ++i )
	{
		//At position i, replace the next 1 char with '-'
		str.replace( v.at( i ), 1, "_" );
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
	auto draw1 = [this, pen]() {scene->addLine( lineHorizontal.data()->line(), pen );};
	auto draw2 = [this, pen]() {scene->addLine( lineVertical.data()->line(), pen );};
	auto draw3 = [this, pen]() {scene->addLine( lineHorizontalSmall.data()->line(), pen );};
	auto draw4 = [this, pen]() {scene->addEllipse( ellipseHead.data()->rect(), pen );};
	auto draw5 = [this, pen]() {scene->addLine( lineNeck.data()->line(), pen );};
	auto draw6 = [this, pen]() {scene->addRect( rectBody.data()->rect(), pen );};
	auto draw7 = [this, pen]() {scene->addLine( rightArm.data()->line(), pen );};
	auto draw8 = [this, pen]() {scene->addLine( leftArm.data()->line(), pen );};
	auto draw9 = [this, pen]() {scene->addLine( rightLeg.data()->line(), pen );};
	auto draw10 = [this, pen]() {scene->addLine( leftLeg.data()->line(), pen );};
	auto drawFinal = [this, msg]()
	{
		scene->addText( msg, QFont( "Arial", 20 ) );
		scene->setBackgroundBrush( QBrush( Qt::red ) );
		enterBtn->setEnabled( false );
		lineEdit->setEnabled( false );
	};
	auto reset = [this]() {resetView();};

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

	//++errorCnt;		//Increment every time this fnc is called.
	mp.at( errorCnt )();	//Execute!
}

void QHangman::resetView()
{
	scene->clear();
	scene->setBackgroundBrush( QBrush( Qt::white ) );
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
	QString strChar = lineEdit->text();

	outputTextEdit->setText( temporaryStr );
	if ( ( !mWord.contains( strChar, Qt::CaseInsensitive ) ) &&
	                ( !temporaryStr.contains( strChar, Qt::CaseInsensitive ) ) )
	{
		paintHangMan();
	}
	else if ( ( mWord.contains( strChar, Qt::CaseInsensitive ) ) &&
	                ( !temporaryStr.contains( strChar, Qt::CaseInsensitive ) ) )
	{
		std::vector<int> v( mWord.size() );
		int j{0};

		while ( ( j = mWord.indexOf( strChar, j ) ) != -1 )
		{
			temporaryStr.replace( j, 1, strChar );
			outputTextEdit->setText( temporaryStr );
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

