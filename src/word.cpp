#include "word.h"

// QString word::hideWord(QString str)
// {
// 	size_t sz = str.size();
// 	std::vector<int> v( sz + 1 );
//
// 	for ( size_t i = 0; i <= 2; ++i )
// 	{
// 		v.at( i ) = rand() % static_cast<int>( sz ) + 1;
// 	}
//
// 	for ( size_t i = 0; i <= sz; ++i )
// 	{
// 		//At position i, replace the next 1 char with '-'
// 		str.replace( v.at( i ), 1, "_" );
// 	}
//
// 	return str;
// }
// kate: indent-mode cstyle; indent-width 8; replace-tabs off; tab-width 8; 
