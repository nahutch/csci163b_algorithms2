#ifndef MLIST_H
#define MLIST_H

#include <vector>
#include <unordered_map>
#include <cassert>
#include "dary_heap.h"

template <class T>
class mlist
{
public:
    mlist()
    {
        minimum = (2, true);
        maximum = (2, true);
    }


    bool empty()
    {
        return ((minimum.empty() && maximum.empty()));
    }

    bool member(const T & x)
    {
        return(minimum.find_member(x) || maximum.find_member(x));
    }

    bool insert(const T & x)  //if empty, just push to max. but 3 cases: if equal size, add to top, push down min to the bottom.
    {
        if(member(x))
        {
            if(minimum.n() == maximum.n())     // if heaps are the same size, add to min heap, then push the front down to the max heap
            {
                minimum.push(x);
                maximum.push(minimum.front());
                minimum.pop_front();
            }
            else if (x > maximum.front())      //if x is bigger than the median and heaps are different sizes, push to min heap
            {
                minimum.push(x);
            }
            else                              //if x is smaller than the median & heaps are different sizes, push to min heap, swap fronts
            {
                minimum.push(x);
                T temp = minimum.front();
                minimum.pop_front();
                minimum.push(maximum.front());
                maximum.pop_front();
                maximum.push(temp);
            }

            return true;
        }

        else
            return false;
    }

    std::size_t size()
    {
        return (minimum.n() + maximum.n());
    }

    bool erase(const T & x)
    {
        if(minimum.find_member(x))                  //if x in min heap
        {
            minimum.erase1(x);
            if (minimum.n() - 2 == maximum.n())     //if minimum was smaller than max before deleting, push front of max.
            {
                minimum.push(maximum.front());
                maximum.pop_front();
            }
                                                    //if they were the same size, all you need to do is delete from min heap
        }
        else if(maximum.find_member(x))
        {
            maximum.erase1(x);
            if (minimum.n() > maximum.n())          //if they were the same size before deleting, move front of min down
            {
                maximum.push(minimum.front());
                minimum.pop_front();
            }
                                                    //if max is the same size after, all you need to do is erase x
        }
        else
            return false;
    }


    T median()
    {
        T is_empty;
        if(empty())
            return is_empty;
        return maximum.front();
    }


private:
    dary_heap<T> minimum;
    dary_heap<T> maximum;

};

#endif // MLIST_H
