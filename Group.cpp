#include "Group.h"

Group::Group() 
{
	children = std::list<Node*>();
}

Group::~Group() 
{
	for (std::list<Node*>::iterator it = children.begin(); it != children.end(); it++) {
		delete *it;
	}

}
void Group::addChild(Node* toAdd) 
{
	children.push_back(toAdd);
}

void Group::removeChild(Node* toRemove) 
{
	children.remove(toRemove);
}


void Group::draw(Matrix4 C)
{
	//Loop through all Node* in children and call draw(C) passing in Matrix4 C as an argument
	for (std::list<Node*>::iterator it = children.begin(); it != children.end(); it++)
	{
		(*it)->draw(C);
	}
}

void Group::update(Matrix4 C) //?
{
	for (std::list<Node*>::iterator it = children.begin(); it != children.end(); it++)
	{
		(*it)->update(C);
	}
}