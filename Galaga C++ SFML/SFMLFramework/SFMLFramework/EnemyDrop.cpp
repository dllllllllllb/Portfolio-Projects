//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "EnemyDrop.h"

EnemyDrop::EnemyDrop( ) :
	m_dropType( EnemyDropType::credit )
{
	m_isActive = false;
}

EnemyDrop::~EnemyDrop( )
{
}

void EnemyDrop::setDropType( const EnemyDropType &dropTypeIndex )
{
	m_dropType = dropTypeIndex;
}

const EnemyDropType &EnemyDrop::getDropType( ) const
{
	return m_dropType;
}