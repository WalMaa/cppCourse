
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
private:
    ListNode *position_;

public:
    ListIterator() : position_(NULL) {}
    ListIterator(ListNode *x) : position_(x) {}

    // Pre-Increment, ++iter
    ListIterator &operator++()
    { // Pre-increment
        if (position_ != nullptr)
        {
            position_ = position_->next;
        }

        return *this;
    }

    // Post-Increment, iter++
    ListIterator operator++(int)
    {
        ListIterator tmp(*this); // Using copy constructor to create a temporary iterator

        if (position_ != nullptr)
        {
            position_ = position_->next;
        }

        return tmp;
    }

    // Pre-Decrement, --iter
    ListIterator &operator--()
    {
        if (position_ != nullptr)
        {
            position_ = position_->prev;
        }

        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int)
    {
        ListIterator tmp(*this); // Using copy constructor to create a temporary iterator

        if (position_ != nullptr)
        {
            position_ = position_->prev;
        }

        return tmp;
    }

    bool operator!=(const ListIterator &rhs)
    {
        return this->position_ != rhs.position_;
    }

    bool operator==(const ListIterator &rhs)
    {
        return this->position_ == rhs.position_;
    }

    const T &operator*()
    {
        return position_->data;
    }

    const T *operator->()
    {
        return &(position_->data);
    }
};
