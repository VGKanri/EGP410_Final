#include "Node.h"

Node::Node()
:mId(BAD_NODE_ID)
{
	mPrevNodeId = 0;
}

Node::Node( const NODE_ID& id )
:mId(id)
{
	mPrevNodeId = 0;
}

Node::~Node()
{
}
