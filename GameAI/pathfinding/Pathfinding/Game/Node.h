#pragma once

#include <Trackable.h>

const int BAD_NODE_ID = -1;
#define NODE_ID int

class Node:public Trackable
{
public:
	Node( const NODE_ID& id );
	Node();
	~Node();

	const NODE_ID& getId() const {return mId;};

	inline NODE_ID getPrevNodeId() const { return mPrevNodeId; };
	inline void setPrevNodeId(NODE_ID prevId) { mPrevNodeId = prevId; };

private:
	const NODE_ID mId;
	NODE_ID mPrevNodeId;
};