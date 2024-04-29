/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List()
    : head_(NULL), tail_(NULL), length_(0)
{
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const
{
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const
{
  if (tail_ == nullptr)
  {
    return nullptr;
  }

  return List<T>::ListIterator(tail_->next);
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy()
{

  ListNode *temp;
  ListNode *curr = head_;

  while (curr != nullptr)
  {
    temp = curr->next;
    delete curr;
    curr = temp;
  }

  head_ = nullptr;
  tail_ = nullptr;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const &ndata)
{
  /// @todo Graded in MP3.1
  ListNode *newNode = new ListNode(ndata);
  newNode->next = head_;
  newNode->prev = nullptr;

  if (head_ != nullptr)
  {
    head_->prev = newNode;
    head_ = newNode;
  }
  else
  {
    head_ = newNode;
  }

  if (tail_ == nullptr)
  {
    tail_ = newNode;
  }

  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T &ndata)
{
  ListNode *newNode = new ListNode(ndata);
  if (tail_ == nullptr)
  {
    if (head_ == nullptr)
    {
      head_ = newNode;
    }

    tail_ = newNode;
    length_++;
    return;
  }

  newNode->prev = tail_;
  tail_->next = newNode;
  tail_ = newNode;

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode *List<T>::split(ListNode *start, int splitPoint)
{

  if (start == nullptr)
  {
    return nullptr;
  }

  ListNode *curr = start;

  for (int i = 0; i < splitPoint && curr->next != nullptr; i++)
  {
    curr = curr->next;
  }

  if (curr->prev != nullptr)
  {
    curr->prev->next = nullptr;
  }
    curr->prev = nullptr;

  return curr;
}

/**
 * Modifies List using the rules for a TripleRotate.
 *
 * This function will to a wrapped rotation to the left on every three
 * elements in the list starting for the first three elements. If the
 * end of the list has a set of 1 or 2 elements, no rotation all be done
 * on the last 1 or 2 elements.
 *
 * You may NOT allocate ANY new ListNodes!
 */
template <typename T>
void List<T>::tripleRotate()
{
  if (head_ == nullptr || head_->next == nullptr || head_->next->next == nullptr)
    return; 

  ListNode *current = head_;

  while (current != nullptr && current->next != nullptr && current->next->next != nullptr)
  {
    ListNode *first = current;
    ListNode *second = first->next;
    ListNode *third = second->next;
    ListNode *next = third->next;

    // Rotating the nodes as per 1,2,3 -> 2,3,1
    if (first == head_) {
      head_ = second;  // Update the head to point to the new first node
    } else {
      second->prev = first->prev;  // Linking second node back to the list part before current triplet
      first->prev->next = second;
    }

    third->next = first;
    first->next = next;
    if (next != nullptr) {
      next->prev = first;
    }
    first->prev = third;

    current = next;
  }
}



/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse()
{
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *&startPoint, ListNode *&endPoint)
{
    if (startPoint == nullptr || endPoint == nullptr)
        return;

    ListNode *current = startPoint;
    ListNode *prev = nullptr, *next = nullptr;
    ListNode *endNext = endPoint->next; // To reconnect the end of the reversed segment back to the list

    // Reverse the segment from startPoint to endPoint
    while (current != endNext) {
        next = current->next; // Store next node

        // Reverse current node's pointers
        current->next = prev;
        current->prev = next;

        // Move prev and current one step forward
        prev = current;
        current = next;
    }

    // Reconnect the reversed segment with the rest of the list
    if (startPoint->prev) {
        startPoint->prev->next = endPoint;
    }
    if (endNext) {
        endNext->prev = startPoint;
    }

    // Update startPoint and endPoint to new locations
    ListNode *temp = startPoint;
    startPoint = endPoint;
    endPoint = temp;

    // Fix the prev and next pointers of the now reversed segment endpoints
    endPoint->next = startPoint->prev;  // Connecting endPoint to the list before startPoint
    startPoint->prev = endNext;  // Connecting startPoint to the list after endPoint

    // If the reversed segment includes the head of the list, update the head
    if (startPoint->prev == nullptr) {
        head_ = startPoint;
    }
}




/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n)
{
  /// @todo Graded in MP3.2
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> &otherList)
{
  // set up the current list
  head_ = merge(head_, otherList.head_);
  tail_ = head_;

  // make sure there is a node in the new list
  if (tail_ != NULL)
  {
    while (tail_->next != NULL)
      tail_ = tail_->next;
  }
  length_ = length_ + otherList.length_;

  // empty out the parameter list
  otherList.head_ = NULL;
  otherList.tail_ = NULL;
  otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode *List<T>::merge(ListNode *first, ListNode *second)
{
  /// @todo Graded in MP3.2
  return NULL;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode *List<T>::mergesort(ListNode *start, int chainLength)
{
  /// @todo Graded in MP3.2
  return NULL;
}
