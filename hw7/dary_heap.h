#ifndef DARYHEAP_H
#define DARYHEAP_H

#include <vector>
#include <unordered_map>
#include <cassert>

template <class T>
class dary_heap
{
  public:

    dary_heap(std::size_t d = 2, bool minimum = true)
    {
        _d = d;
        _min = minimum;
        _n = 0;
    }

    std::size_t n()
    {
        return _n;
    }

    inline bool empty() const
    {
        return (_n == 0);
    }

    T front() const
    {
        assert(!empty());
        return _data[0];
    }

    void push(const T & x)
    {
        if (_n == _data.size())
            _data.push_back(x);
        else
            _data[_n] = x;

        _location[x] = _n;

        ++_n;

        std::size_t i(_location[x]);


        while (i > 0)
        {
            std::size_t parent = (i-1)/_d;
            if(_min==true)
            {
                if (_data[i] < _data[parent])
                {
                    std::swap(_data[i], _data[parent]);
                    _location[_data[i]] = i;
                    _location[_data[parent]] = parent;
                    i = parent;
                }
                else
                    break;
            }
            if(_min == false)
            {
                if (_data[i] > _data[parent])
                {
                    std::swap(_data[i], _data[parent]);
                    _location[_data[i]] = i;
                    _location[_data[parent]] = parent;
                    i = parent;
                }
                else
                    break;
            }

        }
    }


    void pop_front()
    {
        assert(!empty());
        _location.erase(_data[0]);
        if (--_n == 0)
            return;

        _data[0] = _data[_n];
        _location[_data[0]] = 0;
        std::size_t i(0);

        if (_min == true)                 //min heap
        {
            while (i*_d +1 < _n)  // has at least one child
            {
                std::size_t left(i*_d + 1), right((i+1)*_d), m(left);
                for (std::size_t c = left+1; c <= right && c < _n; ++c)
                    if (_data[c] < _data[m])
                        m = c;

                if (!(_data[m] < _data[i]))
                    break;

                std::swap(_data[i], _data[m]);
                _location[_data[i]] = i;
                _location[_data[m]] = m;
                i = m;
            }
        }
        if(_min == false)                      //max heap
        {
            while (i*_d +1 < _n)  // has at least one child
            {
                std::size_t left(i*_d + 1), right((i+1)*_d), m(left);
                for (std::size_t c = left+1; c <= right && c < _n; ++c)
                    if (_data[c] > _data[m])
                        m = c;

                if (!(_data[m] > _data[i]))
                    break;

                std::swap(_data[i], _data[m]);
                _location[_data[i]] = i;
                _location[_data[m]] = m;
                i = m;
            }
        }
    }

    void adjust_key(const T & x, const T & newx)
    {
        if (_min==true)
            assert(newx < x);
        if (_min==false)
            assert(x < newx);

        std::size_t i(_location.at(x));
        _data[i] = newx;
        _location.erase(x);
        _location[newx] = i;

        if (_min == true)
        {
            while (i > 0 && _data[i] < _data[(i-1)/_d])
            {
                std::size_t parent((i-1)/_d);
                std::swap(_data[i], _data[parent]);
                _location[_data[i]] = i;
                _location[_data[parent]] = parent;
                i = parent;
            }
        }
        if (_min == false)
        {
            while (i > 0 && _data[i] > _data[(i-1)/_d])
            {
                std::size_t parent((i-1)/_d);
                std::swap(_data[i], _data[parent]);
                _location[_data[i]] = i;
                _location[_data[parent]] = parent;
                i = parent;
            }
        }

    }

    void print_status() const
    {
        std::cout << "_d = " << _d << "; _n = "  << _n << std::endl;
        for (std::size_t i = 0; i < _n; ++i)
            std::cout << "(" << i << ", " << _data.at(i) << ") ";
        std::cout << std::endl;

        for (auto v: _location)
            std::cout << "(" << v.first << ", " << v.second << ") ";
        std::cout << std::endl;
    }

    bool find_member(const T x)
    {
        if (std::find(_data.begin(), _data.end(), x)  != _data.end())
            return true;
        return false;
    }

    void erase1(const T x)
    {
        if(!find_member(x))
            return;

        T temp = front();
        pop_front();
        if (x != front())
        {
            adjust_key(x, temp);
        }
    }

private:
    bool _min;              //1 if min heap, 0 if max heap
    std::vector<T> _data;   // keys
    std::size_t    _d;      // number of children
    std::size_t    _n;      // number of keys currently in heap
    std::unordered_map<T, std::size_t>  _location;   // location of key in _data
};

#endif // DARYHEAP_H
