

//Default Constructor.  Will properly initialize a list to
//be an empty list, to which values can be added.
template< class T >
SortedListClass< T >::SortedListClass(
     )
{
  head = 0;
  tail = 0;
}

//Copy constructor. Will make a complete (deep) copy of the list, such
//that one can be changed without affecting the other.
template< class T >
SortedListClass< T >::SortedListClass(
     const SortedListClass< T > &rhs
     )
{ 
  LinkedNodeClass< T > *temp;
  LinkedNodeClass< T > *tempOther;
  
  if(rhs.head == 0)
  {
    cout << "List is empty for copy" << endl;
  }

  if(rhs.head != 0)
  { 
    temp = new LinkedNodeClass< T >(0, 
                               rhs.head->getValue(), 
                               rhs.head->getNext()); 
    temp->setBeforeAndAfterPointers(); 

    head = temp;
    tempOther = rhs.head->getNext();

    while(tempOther != 0)
    {
      temp = new LinkedNodeClass< T >(tempOther->getPrev(), 
                                    tempOther->getValue(),
                                    tempOther->getNext()); 
      temp->setBeforeAndAfterPointers(); 
      tempOther = tempOther->getNext(); 
    }

    temp->setNextPointerToNull();
    tail = temp;
  } 
}

//Clears the list to an empty state without resulting in any
//memory leaks.
template< class T >
void SortedListClass< T >::clear(
     )
{
  LinkedNodeClass< T > *temp = head;

  while(temp != 0)
  {
    LinkedNodeClass< T > *del = temp;
    temp = temp->getNext();
    delete del;
  }

  head = tail = 0; 
}

//Allows the user to insert a value into the list.  Since this
//is a sorted list, there is no need to specify where in the list
//to insert the element.  It will insert it in the appropriate
//location based on the value being inserted.  If the node value
//being inserted is found to be "equal to" one or more node values
//already in the list, the newly inserted node will be placed AFTER
//the previously inserted nodes.
template< class T >
void SortedListClass< T >::insertValue(
     const T &valToInsert  //The value to insert into the list
     )
{
  LinkedNodeClass< T > *temp; 

  if(head == 0 && tail == 0)
  {
    temp = new LinkedNodeClass< T >(0, valToInsert, 0);
    head = temp;
    tail = temp;
  }

  else if(head->getValue() > valToInsert)
  {
    temp = new LinkedNodeClass< T >(0, valToInsert, head);
    temp->setBeforeAndAfterPointers();
    head = temp;
    head->setPreviousPointerToNull();
  }

  else if(head->getNext() == 0 && head->getValue() == valToInsert)
  {
    temp = new LinkedNodeClass< T >(head, valToInsert, 0); 
    temp->setBeforeAndAfterPointers();
    tail = temp;
    tail->setNextPointerToNull();
  }
 
  else if(head->getNext() == 0 && head->getValue() < valToInsert)
  {
    temp = new LinkedNodeClass< T >(head, valToInsert, 0);  
    temp->setBeforeAndAfterPointers();
    tail = temp;
    tail->setNextPointerToNull();
  }
  
  else if(head->getNext() != 0)
  {
    temp = head->getNext();

    while(temp->getValue() < valToInsert && temp->getNext() != 0)
    {
      temp = temp->getNext();
    }

    if(temp->getValue() > valToInsert && temp->getNext() != 0)
    { 
      temp = new LinkedNodeClass< T >(temp->getPrev(), valToInsert, 
                                 temp->getNext()->getPrev());
      temp->setBeforeAndAfterPointers();
      temp = temp->getPrev();
    }

    if(temp->getValue() == valToInsert && temp->getNext() != 0)
    { 
      temp = new LinkedNodeClass< T >(temp->getPrev(), valToInsert, 
                                 temp->getNext()->getPrev());
      temp->setBeforeAndAfterPointers();
      temp = temp->getNext(); 
    }

    if(temp->getNext() == 0)
    {
      if(tail->getValue() > valToInsert)
      {
        temp = new LinkedNodeClass< T >(tail->getPrev(), valToInsert, tail);
        temp->setBeforeAndAfterPointers();
        tail->setNextPointerToNull();
      }
        
      if(tail->getValue() == valToInsert || tail->getValue() < valToInsert)
      {
        temp = new LinkedNodeClass< T >(tail->getPrev()->getNext(), 
                                                   valToInsert, 0);
        temp->setBeforeAndAfterPointers();
        tail = temp;
        tail->setNextPointerToNull();
      }
    }
  }
}

//Prints the contents of the list from head to tail to the screen.
//Begins with a line reading "Forward List Contents Follow:", then
//prints one list element per line, indented two spaces, then prints
//the line "End Of List Contents" to indicate the end of the list.
template< class T >
void SortedListClass< T >::printForward(
     ) const
{
  LinkedNodeClass< T > *temp = head;

  if(temp == 0)
  {
    cout << "List is Empty for print!" << endl;
  }

  else 
  {
    cout << "Forward List Contents Follow:" << endl;
  
    while(temp != 0)
    {
      cout << "  " << temp->getValue() << endl;
      temp = temp->getNext();
    }

    cout << "End Of List Contents" << endl;
  }
}

//Prints the contents of the list from tail to head to the screen.
//Begins with a line reading "Backward List Contents Follow:", then
//prints one list element per line, indented two spaces, then prints
//the line "End Of List Contents" to indicate the end of the list.
template< class T >
void SortedListClass< T >::printBackward(
     ) const
{
  LinkedNodeClass< T > *temp = tail;

  if(temp == 0)
  {
    cout << "List is Empty for print!" << endl;
  }

  else 
  {
    cout << "Backward List Contents Follow:" << endl;
    
    while(temp != 0)
    {
      cout << "  " << temp->getValue() << endl;
      temp = temp->getPrev();
    }
  
    cout << "End Of List Contents" << endl;
  }
}

//Removes the front item from the list and returns the value that
//was contained in it via the reference parameter.  If the list
//was empty, the function returns false to indicate failure, and
//the contents of the reference parameter upon return is undefined.
//If the list was not empty and the first item was successfully
//removed, true is returned, and the reference parameter will
//be set to the item that was removed.
template< class T >
bool SortedListClass< T >::removeFront(
     T &theVal
     )
{
  bool status = true;
  LinkedNodeClass< T > *remove;

  if(head == 0)
  {
    status = false;
  }

  else
  {
    //remove = head;
    head = head->getNext();
    remove = head->getPrev();
    theVal = remove->getValue();
    delete remove;
    head->setPreviousPointerToNull();
    status = true;
  }

  return status;
}

//Removes the last item from the list and returns the value that
//was contained in it via the reference parameter.  If the list
//was empty, the function returns false to indicate failure, and
//the contents of the reference parameter upon return is undefined.
//If the list was not empty and the last item was successfully
//removed, true is returned, and the reference parameter will
//be set to the item that was removed.
template< class T >
bool SortedListClass< T >::removeLast(
     T &theVal
     )
{
  bool status = true;
  LinkedNodeClass< T > *remove;

  if(tail == 0)
  {
    status = false;
  }

  else
  {
    theVal = tail->getValue();
    tail = tail->getPrev();
    remove = tail->getNext();
    delete remove;
    tail->setNextPointerToNull();
    status = true;
  }

  return status;
}

//Returns the number of nodes contained in the list.
template< class T >
int SortedListClass< T >::getNumElems(
     ) const
{
  int counter = 0;
  LinkedNodeClass< T > *temp = head;

  if(temp == 0)
  {
    ;
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

//Provides the value stored in the node at index provided in the
//0-based "index" parameter.  If the index is out of range, then outVal
//remains unchanged and false is returned.  Otherwise, the function
//returns true, and the reference parameter outVal will contain
//a copy of the value at that location.
template< class T >
bool SortedListClass< T >::getElemAtIndex(
     const int index,
     T &outVal) const
{
  LinkedNodeClass< T > *temp = head;
  bool status;

  if(temp == 0)
  {
    cout << "List is Empty to get Index!" << endl;
    status = false;
    outVal = 0;
  }

  if(temp != 0)
  {
    if(index > this->getNumElems() || index == this->getNumElems() || index < 0)
    {
      cout << "Index is out of range" << endl;
      status = false;
      outVal = 0;
    }

    if(index < this->getNumElems())
    {
      if(index == 0)
      {
        outVal = head->getValue();
        status = true;
      }

      if(index != 0)
      {
        for(int i = 1; i < (index + 1); i++)
        {
          temp = temp->getNext();
          
          if(index == i)
          {
            outVal = temp->getValue();
            status = true;
          }
        }
      }
    }
  }

  return status;
}

template< class T >
SortedListClass< T >::~SortedListClass(
     )
{
  LinkedNodeClass< T > *temp = head;

  while(temp != 0)
  {
    LinkedNodeClass< T > *del = temp;
    temp = temp->getNext();
    delete del;
  }

  head = tail = 0; 
}
