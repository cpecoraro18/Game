#pragma once
#ifndef SRC_AABBTREE_H_
#define SRC_AABBTREE_H_

#include "AABB.h"

#include <stack>
#include <vector>
#include <memory>
#include <map>
#include <forward_list>



struct AABBNode {
	AABB aabb;

	AABB* leftChild;
	AABB* rightChild;
	bool isLeaf;


};

struct Tree {
	AABBNode* nodes;
};

class AABBTree {

	void InsertLeaf(Tree tree, int objectIndex, AABB box);


};

#endif /* SRC_AABBTREE_H_ */