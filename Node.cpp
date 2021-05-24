
#include "Node.h"
#include "Tile.h"
#include <iostream>

Node::Node(Tile *tile, Node *next)
{
   this->tile = tile;
   this->next = next;
}

Node::Node(Tile *tile)
{
   this->tile = tile;
   this->next = nullptr;
}

Node::Node(Node &other)
{
   this->tile = other.tile;
   this->next = other.next;
}

Node::~Node()
{
   if (tile != nullptr)
   {
      delete tile;
   }
}

void Node::clearNodeList()
{
   if (next != nullptr)
   {
      next->~Node();
   }
}

Tile *Node::getTile()
{
   return tile;
}
Node *Node::getNext()
{
   return next;
}

void Node::setNext(Node *next)
{
   this->next = next;
}

void Node::setNextNullptr()
{
   this->next = nullptr;
}
