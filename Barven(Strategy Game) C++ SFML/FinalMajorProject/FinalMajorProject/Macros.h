//Author: Maciej Dowbor
//Last Accessed: 17/03/2021

#ifndef MACROS_H
#define MACROS_H

#include <cassert>

template <typename T> void safeDelete(T*& pointer)
{
	if (pointer)
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

#endif // !MACROS_H

