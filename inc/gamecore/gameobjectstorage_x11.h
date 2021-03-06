/*
 * gameobjectstorage_x11.h
 *
 *  Created on: Mar 2, 2016
 *      Author: janne
 */

#ifndef INC_GAMECORE_GAMEOBJECTSTORAGE_X11_H_
#define INC_GAMECORE_GAMEOBJECTSTORAGE_X11_H_

#include <mutex>
#include <map>
#include "gameobject_x11.h"

typedef std::map<uint32_t, GameObject_X11*> GameObjectMap;
typedef std::pair<GameObjectMap::iterator, GameObjectMap::iterator> GameObjectPair;

class GameObjectStorage_X11
{
public:
	~GameObjectStorage_X11();

	static GameObjectStorage_X11* GetApi();

	void DropInstance();

	void AddObject(GameObject_X11*);

	void RemoveObject(GameObject_X11*);

	GameObjectPair GetAllObjects();

	void Update();

protected:

private:
	GameObjectStorage_X11();
	static GameObjectStorage_X11* instance;
	static std::mutex instanceCreationMutex;

	GameObjectMap gameObjectMap;
};



#endif /* INC_GAMECORE_GAMEOBJECTSTORAGE_X11_H_ */
