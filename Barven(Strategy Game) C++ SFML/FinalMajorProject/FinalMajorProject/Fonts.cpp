#include "Fonts.h"
Fonts::Fonts()
{
	loadFonts();
}

Fonts::~Fonts()
{
}

void Fonts::loadFonts()
{
	ASSERT(m_fontBasic.loadFromFile("Assets/Fonts/IMMORTAL.ttf"));
}