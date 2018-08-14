#ifndef WGRAPH_H
#define WGRAPH_H

#include "graph.h"
#include "ds.h"
#include <set>

// specialize hash to provide a hash function for Edge (pair of strings)

namespace std
{
    template <>
    class hash<graph::Edge>
    {
    public:

        std::size_t operator() (const graph::Edge & p) const
        {
            return std::hash<std::string> () (p.first) ^
                    std::hash<std::string> () (p.second);
        }
    };
}



struct WEdge
{
    std::string s, d;
    double w;

    WEdge(const std::string & s, const std::string & d, double w) : s(s), d(d), w(w)
    {}

};

bool operator < (const WEdge & e1, const WEdge & e2)
{
    return (e1.w < e2.w);
}


class wgraph : public graph
{
public:
    wgraph()
    {

    }

    void add_edge(const T &s, const T &d, double w)
    {
        graph::add_edge(s, d);
        _w[{s,d}] = _w[{d,s}] = w;
    }

    void remove_edge(const T &s, const T &d)
    {
        graph::remove_edge(s, d);
        _w.erase({s,d});
        _w.erase({d,s});
    }

    void remove_vertex(const T & v)
    {
        for (auto w: Adj(v))
        {
            _w.erase({v,w});
            _w.erase({w, v});
        }
        graph::remove_vertex(v);
    }

    inline double cost(const T & s, const T & d) const
    {
        return _w.at({s,d});
    }

    inline double cost(const Edge & e) const
    {
        return cost(e.first, e.second);
    }

    std::set<WEdge> E() const
    {
        std::set<WEdge> ans;

        for (auto v: V())
        {
            for (auto w: Adj(v))
                if (v < w)
                ans.insert(WEdge(v, w, cost(v, w)));
        }

        return ans;
    }


    wgraph Kruskal() const
    {

        ds<T> S;
        wgraph ans;

        if (!is_connected())
            return ans;

        for (auto v: V())
        {
            ans.add_vertex(v);
            S.make_set(v);
        }

        std::set<WEdge> Edges = E();

        for (auto e: Edges)
        {
            if (S.find(e.s) != S.find(e.d))
            {
                ans.add_edge(e.s, e.d, e.w);
                S.join(e.s, e.d);
            }

        }

        return ans;
    }

    wgraph Boruvka() const
    {
        ds<T> S;
        wgraph ans;

        if (!is_connected())
            return ans;

        for (auto v: V())
        {
            ans.add_vertex(v);
            S.make_set(v);
        }

        std::unordered_set<Edge> E;

        for (auto v: V())
            for (auto w: Adj(v))
                if (v < w)
                    E.insert({v,w});

        while (!E.empty())
        {
            std::unordered_map<T, Edge> b;

            // find lightest edge out of each component (represented by a root)
            for (auto p = E.begin(); p != E.end();)
            {
                // endpoints of edge are in the same tree
                T i(S.find(p->first)->value), j(S.find(p->second)->value);

                if (i == j)
                {
                    p = E.erase(p);
                    continue;
                }

                if (b.count(i) == 0 || cost(b.at(i)) > cost(*p))
                    b[i] = *p;

                if (b.count(j) == 0 || cost(b.at(j)) > cost(*p))
                    b[j] = *p;

                ++p;
            }

            // add best edge adjacent to each component to MST


            for (auto e: b)
            {
                T i(e.second.first), j(e.second.second);
                if (S.find(i) != S.find(j))
                {
                    S.join(i, j);
                    ans.add_edge(i, j, cost(i,j));
                    E.erase({i,j});
                }
            }
       }


       return ans;
    }


    void print_connections() const
    {
        std::size_t total_cost(0);
        for (auto v: V())
        {
            for (auto e: Adj(v))
            {
                total_cost += cost (v, e);
            }
        }

        total_cost = total_cost/2;
        std::cout << total_cost << std::endl;

        bool direct_connect = false;
        for (auto v: V())
        {
            if (v != "DI")
            {
                direct_connect = false;

                for (auto e: Adj(v))
                {
                    if (e == "DI")
                        direct_connect = true;
                }
                if (direct_connect)
                    std::cout << v << " true ";
                else
                    std::cout << v << " false ";

                    for (auto e: Adj(v))
                    {
                        if(e!="DI")
                            std::cout << e << " ";
                    }
                std::cout << std::endl;
            }
        }
    }




private:

    // weight information
    std::unordered_map<Edge, double> _w;

};

std::ostream & operator << (std::ostream & os, const wgraph & G)
{
    os << G.n() << " " << G.m() << std::endl;
    for (auto v: G.V())
        os << v << " ";
    os << std::endl;

    for (auto v: G.V())
    {
        for (auto w: G.Adj(v))
            if (v < w)
                os << v << " " << w << " " << G.cost(v, w) << std::endl;
    }

    return os;



}


//updated to input the wgraph HW6 problems
std::istream & operator >> (std::istream & is, wgraph & G)
{
    std::size_t n, m;
    std::string s, d, e, di("DI");
    double w;

    is >> n;

    G.add_vertex(di);

    for (std::size_t i = 0; i < n; i++)
    {
        is >> s >> e;
        G.add_vertex(s);
        if(stoi(e) != -1)
            G.add_edge(di, s, stoi(e));
    }

    is >> m;

    for (std::size_t i = 0; i < m; ++i)
    {
        is >> s >> d >> w;
        G.add_edge(s, d, w);

    }
    return is;

}


#endif // WGRAPH_H
