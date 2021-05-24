
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

class Tile;

class Node
{
public:
   Node(Tile *tile, Node *next);
   Node(Tile *tile);
   Node(Node &other);
   ~Node();

   void clearNodeList();

   Tile *getTile();
   Node *getNext();
   void setNext(Node *next);
   void setNextNullptr();

private:
   Tile *tile;
   Node *next;
}

;

#endif // ASSIGN2_NODE_H
