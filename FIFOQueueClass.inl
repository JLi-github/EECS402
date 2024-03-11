
//Default Constructor.  Will properly initialize a queue to
//be an empty queue, to which values can be added.
template< class T >
FIFOQueueClass< T >::FIFOQueueClass(
     )
{
  head = 0;
  tail = 0;
}

//Inserts the value provided (newItem) into the queue.
template< class T >
void FIFOQueueClass< T >::enqueue(
     const T &newItem
     )
{
  LinkedNodeClass< T > *temp;

  if(head == 0)
  {
    temp = new LinkedNodeClass< T >(0, newItem, 0);
    head = temp;
    tail = temp;
  }
  
  else 
  {
    temp = new LinkedNodeClass< T >(tail, newItem, 0);
    temp->setBeforeAndAfterPointers();
    tail = temp;
  } 
}

//Attempts to take the next item out of the queue.  If the
//queue is empty, the function returns false and the state
//of the reference parameter (outItem) is undefined.  If the
//queue is not empty, the function returns true and outItem
//becomes a copy of the next item in the queue, which is
//removed from the data structure.
template< class T >
bool FIFOQueueClass< T >::dequeue(
     T &outItem
     )
{
  bool status = true;
  LinkedNodeClass< T > *temp;
 
  if(head == 0)
  {
    cout << "List is empty, can't dequeue from list" << endl;
    status = false;
  }

  else
  {
    temp = head;
    head = head->getNext();
    outItem = temp->getValue();
    delete temp;
    status = true;
  }

  return status;
}

//Prints out the contents of the queue.  All printing is done
//on one line, using a single space to separate values, and a
//single newline character is printed at the end.
template< class T >
void FIFOQueueClass< T >::print(
     ) const
{
  LinkedNodeClass< T > *temp;
  temp = head;

  if(temp == 0)
  {
    cout << "List is empty to print!" << endl;
  }

  while(temp != 0)
  {
    cout << temp->getValue() << " ";
    temp = temp->getNext();
  }

  cout << endl;
  cout << "\n";
}

template< class T >
int FIFOQueueClass< T >::getNumElems(
     ) const
{
  int counter = 0;
  LinkedNodeClass< T > *temp = head;

  if(temp == 0)
  {
    //cout << "List is empty" << endl;
  }

  else
  {
    while(temp != 0)
    {
      counter = counter + 1;
      temp = temp->getNext();
    }
  }
  
  return counter;
}

//Clears the queue to an empty state without resulting in any
//memory leaks.
template< class T >
FIFOQueueClass< T >::~FIFOQueueClass(
     )
{
  LinkedNodeClass< T > *temp = head;

  while(temp != 0)
  {
    LinkedNodeClass< T > *del = temp;
    temp = temp->getNext();
    delete del;
  }

  head = 0;
  tail = 0; 
}

