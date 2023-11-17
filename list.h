#ifndef __LIST_H__
#define __LIST_H__

template <
    typename T,
    bool ORDERED = false,
    typename TO = unsigned int,
    bool RELATIVE = false> // Relative lists only works with unsigned integer ranks
class List
{
private:
    struct Element
    {
        T data;
        Element *prev, *next;
        TO rank;
    };

    Element *head, *tail;
    int _size;

    void insert_first(T data, TO rank = 0)
    {
        Element *e = new Element();
        e->data = data;
        if (ORDERED)
            e->rank = rank;
        e->next = 0;
        e->prev = 0;
        head = e;
        tail = e;
        _size++;
    }

public:
    List() : head(0), tail(0), _size(0)
    {
    }

    ~List() {}

    T get(int pos)
    {
        Element *e = head;
        while (pos--)
            e = e->next;
        return e->data;
    }

    TO get_rank(int pos)
    {
        Element *e = head;
        while (pos--)
            e = e->next;
        return e->rank;
    }

    int size() { return _size; }

    void insert(T data, TO rank = 0)
    {
        if (ORDERED)
            insert_ordered(data, rank);
        else
            insert_tail(data);
    }

    void insert_ordered(T data, TO rank)
    {
        Element *e = head;
        while ((e != 0) && (e->rank < rank))
        {
            if (RELATIVE)
                rank = rank - e->rank;
            e = e->next;
        }

        if (e == 0)
        {
            insert_tail(data, rank);
        }
        else
        {
            Element *new_e = new Element();
            new_e->data = data;
            new_e->rank = rank;
            new_e->prev = e->prev;
            new_e->next = e;
            if (new_e->prev != 0)
                new_e->prev->next = new_e;
            new_e->next->prev = new_e;
            _size++;

            if (e == head)
                head = new_e;

            if (RELATIVE)
                e->rank -= rank;
        }
    }

    void insert_tail(T data, TO rank = 0)
    {
        if (_size == 0)
            insert_first(data, rank);
        else
        {
            Element *e = new Element();
            e->data = data;
            if (ORDERED)
                e->rank = rank;
            e->prev = tail;
            e->next = 0;
            tail->next = e;
            tail = e;
            _size++;
        }
    }

    void insert_head(T data, TO rank = 0)
    {
        if (_size == 0)
            insert_first(data, rank);
        else
        {
            Element *e = new Element();
            e->data = data;
            if (ORDERED)
                e->rank = rank;
            e->prev = 0;
            e->next = head;
            head->prev = e;
            head = e;
            _size++;
        }
    }

    T remove_tail()
    {
        T ret_val = tail->data;

        tail->prev->next = 0;
        Element *to_delete = tail;

        tail = tail->prev;
        _size--;

        delete to_delete;
        return ret_val;
    }

    T remove_head()
    {
        T ret_val = head->data;

        head->next->prev = 0;
        Element *to_delete = head;

        head = head->next;
        _size--;

        delete to_delete;
        return ret_val;
    }

    TO update_head_rank(TO value)
    {
        if (_size == 0)
            return -1;
        if (head->rank < value)
            head->rank = 0;
        else
            head->rank -= value;
        return head->rank;
    }
};

#endif