//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#ifndef ENEMYSTATEENUM_H
#define ENEMYSTATEENUM_H

enum class EnemyState
{
	inactive,
	idle,
	resetingPosition,
	dive,
	initialManeuver,
	movingRight,
	kamikaze
};

#endif // !ENEMYSTATEENUM_H
