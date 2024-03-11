template< class T >

//The ONLY constructor for the linked node class - it takes in the
//newly created node's previous pointer, value, and next pointer,
//and assigns them.
LinkedNodeClass< T >::LinkedNodeClass(
     LinkedNodeClass *inPrev, //Address of node that comes before this one
     const T &inVal,          //Value to be contained in this node
     LinkedNodeClass *inNext  //Address of node that comes after this one
     )
{
  prevNode = inPrev;
  nodeVal = inVal;
  nextNode = inNext;
}

//Returns the value stored within this node.
template< class T >
T LinkedNodeClass< T >::getValue(
     ) const
{
  return nodeVal;
}

//Returns the address of the node that follows this node.
template< class T >
LinkedNodeClass< T >* LinkedNodeClass< T >::getNext(
     ) const
{
  return this->nextNode;
}

//Returns the address of the node that comes before this node.
template< class T >
LinkedNodeClass< T >* LinkedNodeClass< T >::getPrev(
     ) const
{
  return this->prevNode;
}

//Sets the object’s next node pointer to NULL.
template< class T >
void LinkedNodeClass< T >::setNextPointerToNull(
     )
{
  this->nextNode = 0;
}

//Sets the object's previous node pointer to NULL.
template< class T >
void LinkedNodeClass< T >::setPreviousPointerToNull(
     )
{
  this->prevNode = 0;
}

//This function DOES NOT modify "this" node. Instead, it uses
//the pointers contained within this node to change the previous
//and next nodes so that they point to this node appropriately.
template< class T >
void LinkedNodeClass< T >::setBeforeAndAfterPointers(
     )
{ 
  if(prevNode != 0)
  {
    prevNode->nextNode = this;
  }

  if(nextNode != 0)
  {
    nextNode->prevNode = this;
  }
}
