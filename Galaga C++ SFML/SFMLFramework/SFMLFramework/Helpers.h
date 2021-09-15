//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#ifndef HELPERS_H
#define HELPERS_H

#include <cassert>

template <typename T> void safeDelete( T *&pointer )
{
	if( pointer )
	{
		delete pointer;
		pointer = nullptr;
	}
}

#ifdef _DEBUG
#define ASSERT assert
#else
#define ASSERT
#endif

#endif // !HELPERS_H
