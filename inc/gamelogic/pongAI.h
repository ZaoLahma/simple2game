/*
 * pongAI.h
 *
 *  Created on: May 6, 2016
 *      Author: janne
 */

#ifndef INC_GAMELOGIC_PONGAI_H_
#define INC_GAMELOGIC_PONGAI_H_

#include "gamelogic/pongballgameobject.h"
#include "gamelogic/pongpaddlegameobject.h"

class PongAI
{
public:
	PongAI(PongPaddleGameObject* paddlePtr, uint32_t _player);

	void TrackBall(PongBallGameObject* ballPtr);

protected:

private:
	PongAI();
	PongPaddleGameObject* paddle;
	double xDistance;
	uint32_t player;

	uint32_t KEY_UP;
	uint32_t KEY_DOWN;
};



#endif /* INC_GAMELOGIC_PONGAI_H_ */
