#pragma once

#ifndef SRC_COMPONENT_H_
#define SRC_COMPONENT_H_

class Component {
public:
	Component() {}

	virtual void Update() = 0;
};

#endif /* SRC_COMPONENT_H_ */