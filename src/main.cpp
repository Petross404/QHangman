#include "qhangman.h"
#include <QApplication>

int main( int argc, char* argv[] )
{
	QApplication app( argc, argv );
	QHangman w;
	std::invoke( &QHangman::show, w );

	return app.exec();
}

// kate: indent-mode cstyle; indent-width 8; replace-tabs off; tab-width 8; 
