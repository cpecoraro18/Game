#pragma once

#ifndef SRC_ENTITY_TYPE_H_
#define SRC_ENTITY_TYPE_H_

/*******************************************************************************
* Includes
******************************************************************************/
#include <string>


/*******************************************************************************
* Namespaces
******************************************************************************/


enum EntityType {
	kPlayer = 0, kEnemy, kBlock, kCoin, kSpike, kKey, kBird, kKnight, kUndefined
};

inline EntityType get_entity_type(const std::string& type) {
	if (type == "Player") {
		return kPlayer;
	}
	if (type == "Enemy") {
		return kEnemy;
	}
	if (type == "Block") {
		return kBlock;
	}
	if (type == "Key") {
		return kKey;
	}
	return kUndefined;
}


#endif  // SRC_ENTITY_TYPE_H_
