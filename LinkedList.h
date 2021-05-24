#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H
#include <string>

class Node;

class Tile;

class LinkedList
{
public:
   LinkedList();
   LinkedList(LinkedList &other);
   ~LinkedList();

   /**
    * Return the current size of the Linked List.
    */
   int size();

   /**
    * Get the value at the given index.
    */
   Tile *get(int index);

   /**
    * Add the value to the back of the Linked List
    */
   void addBack(Tile *tile);

   /**
    * Add the value to the front of the Linked List
    */
   void addFront(Tile *tile);

   /**
    * Remove the value at the back of the Linked List
    */
   void removeBack();

   /**
    * Remove the value at the front of the Linked List
    */
   void removeFront();

   /**
    * Removes all values from the Linked List
    */
   void clear();

   /**
    * Checks if a tile exists in a Linked List
    */
   int existsAt(char colour, int shape);

   /**
    * Checks if LinkedList is empty
    */
   bool isEmpty();

   std::string toString();

   void removeElement(Tile *tile);

private:
   Node *head;
};

#endif // ASSIGN2_LINKEDLIST_H