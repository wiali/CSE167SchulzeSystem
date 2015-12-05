#pragma once
#include "Node.h"
#include <list>

class Group : public Node {
public:
	std::list<Node*> children;

	Group();
	~Group();
	void addChild(Node*);
	void removeChild(Node*);

	virtual void draw(Matrix4);
	void update(Matrix4);

};