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
	kPlayer = 0, kEnemy, kUndefined
};

inline EntityType get_entity_type(const std::string& type) {
	if (type == "Player") {
		return kPlayer;
	}
	if (type == "Enemy") {
		return kEnemy;
	}
	return kUndefined;
}


#endif  // SRC_ENTITY_TYPE_H_
