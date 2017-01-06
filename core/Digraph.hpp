// Digraph.hpp
//
// ICS 46 Spring 2016
// Project #4: Rock and Roll Stops the Traffic
//
// This header file declares a class template called Digraph, which is
// intended to implement a generic directed graph.  The implementation
// uses the adjacency lists technique, so each vertex stores a linked
// list of its outgoing edges.
//
// Along with the Digraph class template is a class DigraphException
// and a couple of utility structs that aren't generally useful outside
// of this header file.
//
// In general, directed graphs are all the same, except in the sense
// that they store different kinds of information about each vertex and
// about each edge; these two types are the type parameters to the
// Digraph class template.

#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <functional>
#include <list>
#include <map>
#include <utility>
#include <vector>
#include <iostream>
#include <set>
#include <queue>
#include "TripReader.hpp"
#include "RoadSegment.hpp"
// DigraphExceptions are thrown from some of the member functions in the
// Digraph class template, so that exception is declared here, so it
// will be available to any code that includes this header file.

class DigraphException
{
public:
    DigraphException(const std::string& reason): reason_{reason} { }

    std::string reason() const { return reason_; }

private:
    std::string reason_;
};



// A DigraphEdge lists a "from vertex" (the number of the vertex from which
// the edge points), a "to vertex" (the number of the vertex to which the
// edge points), and an EdgeInfo object.  Because different kinds of Digraphs
// store different kinds of edge information, DigraphEdge is a template
// struct.

template <typename EdgeInfo>
struct DigraphEdge
{
    int fromVertex;
    int toVertex;
    EdgeInfo einfo;
};



// A DigraphVertex includes two things: a VertexInfo object and a list of
// its outgoing edges.  Because different kinds of Digraphs store different
// kinds of vertex and edge information, DigraphVertex is a template struct.

template <typename VertexInfo, typename EdgeInfo>
struct DigraphVertex
{
    VertexInfo vinfo;
    std::list<DigraphEdge<EdgeInfo>> edges;
};



// Digraph is a class template that represents a directed graph implemented
// using adjacency lists.  It takes two type parameters:
//
// * VertexInfo, which specifies the kind of object stored for each vertex
// * EdgeInfo, which specifies the kind of object stored for each edge
//
// You'll need to implement the member functions declared here; each has a
// comment detailing how it is intended to work.
//
// Each vertex in a Digraph is identified uniquely by a "vertex number".
// Vertex numbers are not necessarily sequential and they are not necessarily
// zero- or one-based.

template <typename VertexInfo, typename EdgeInfo>
class Digraph
{
public:
    // The default constructor initializes a new, empty Digraph so that
    // contains no vertices and no edges.
    Digraph();

    // The copy constructor initializes a new Digraph to be a deep copy
    // of another one (i.e., any change to the copy will not affect the
    // original).
    Digraph(const Digraph& d);

    // The destructor deallocates any memory associated with the Digraph.
    ~Digraph();

    // The assignment operator assigns the contents of the given Digraph
    // into "this" Digraph, with "this" Digraph becoming a separate, deep
    // copy of the contents of the given one (i.e., any change made to
    // "this" Digraph afterward will not affect the other).
    Digraph& operator=(const Digraph& d);

    // vertices() returns a std::vector containing the vertex numbers of
    // every vertex in this Digraph.
    std::vector<int> vertices() const;

    // edges() returns a std::vector of std::pairs, in which each pair
    // contains the "from" and "to" vertex numbers of an edge in this
    // Digraph.  All edges are included in the std::vector.
    std::vector<std::pair<int, int>> edges() const;

    // This overload of edges() returns a std::vector of std::pairs, in
    // which each pair contains the "from" and "to" vertex numbers of an
    // edge in this Digraph.  Only edges outgoing from the given vertex
    // number are included in the std::vector.  If the given vertex does
    // not exist, a DigraphException is thrown instead.
    std::vector<std::pair<int, int>> edges(int vertex) const;

    // vertexInfo() returns the VertexInfo object belonging to the vertex
    // with the given vertex number.  If that vertex does not exist, a
    // DigraphException is thrown instead.
    //typename DigraphVertex<VertexInfo, EdgeInfo>::
    VertexInfo vertexInfo(int vertex) const;

    // edgeInfo() returns the EdgeInfo object belonging to the edge
    // with the given "from" and "to" vertex numbers.  If either of those
    // vertices does not exist *or* if the edge does not exist, a
    // DigraphException is thrown instead.
    //typename DigraphEdge<EdgeInfo>::
    EdgeInfo edgeInfo(int fromVertex, int toVertex) const;

    // addVertex() adds a vertex to the Digraph with the given vertex
    // number and VertexInfo object.  If there is already a vertex in
    // the graph with the given vertex number, a DigraphException is
    // thrown instead.
    void addVertex(int vertex, const VertexInfo& vinfo);

    // addEdge() adds an edge to the Digraph pointing from the given
    // "from" vertex number to the given "to" vertex number, and
    // associates with the given EdgeInfo object with it.  If one
    // of the vertices does not exist *or* if the same edge is already
    // present in the graph, a DigraphException is thrown instead.
    void addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo);

    // removeVertex() removes the vertex (and all of its incoming
    // and outgoing edges) with the given vertex number from the
    // Digraph.  If the vertex does not exist already, a DigraphException
    // is thrown instead.
    void removeVertex(int vertex);

    // removeEdge() removes the edge pointing from the given "from"
    // vertex number to the given "to" vertex number from the Digraph.
    // If either of these vertices does not exist *or* if the edge
    // is not already present in the graph, a DigraphException is
    // thrown instead.
    void removeEdge(int fromVertex, int toVertex);

    // vertexCount() returns the number of vertices in the graph.
    int vertexCount() const;

    // edgeCount() returns the total number of edges in the graph,
    // counting edges outgoing from all vertices.
    int edgeCount() const;

    // This overload of edgeCount() returns the number of edges in
    // the graph that are outgoing from the given vertex number.
    // If the given vertex does not exist, a DigraphException is
    // thrown instead.
    int edgeCount(int vertex) const;

    // isStronglyConnected() returns true if the Digraph is strongly
    // connected (i.e., every vertex is reachable from every other),
    // false otherwise.
    bool isStronglyConnected() const;

    // findShortestPaths() takes a start vertex number and a function
    // that takes an EdgeInfo object and determines an edge weight.
    // It uses Dijkstra's Shortest Path Algorithm to determine the
    // shortest paths from the start vertex to every other vertex
    // in the graph.  The result is returned as a std::map<int, int>
    // where the keys are vertex numbers and the value associated
    // with each key k is the precedessor of that vertex chosen by
    // the algorithm.  For any vertex without a predecessor (e.g.,
    // a vertex that was never reached, or the start vertex itself),
    // the value is simply a copy of the key.
    std::map<int, int> findShortestPaths(
        int startVertex,
        std::function<double(const EdgeInfo&)> edgeWeightFunc) const
    {
        std::map<int, bool> visited; //visited kv
    std::map<int, double> best; // dv best option so far
    std::map<int,int> pv; //predecessors 
    std::cout<<startVertex<<std::endl;
    //EdgeInfo ed;
    /*
    for(auto& e: di_map.at(startVertex).edges)
    {
        std::cout<<edgeWeightFunc(e.einfo)<<std::endl;

    }
    //EdgeInfo _ed=di_map.at(startVertex).edges;

    //vertxx=rmap.vertices();
    */
    std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, int>>, weight> pq;
    for(auto v: keys)
    {
        //std::cout<<v<<std::endl;
        visited.insert(std::make_pair(v, false));
        best.insert(std::make_pair(v, 99999));
        pv.insert(std::make_pair(v, NULL));

        //kdv.push_back(std::make_pair(v, std::make_pair(9999, false)));
        //pv.push_back(v, NULL);
    }
    pv[0]=0;
    best[0]=0;
    std::pair<int, double> option;
    option.first=startVertex;
    option.second=0;
    pq.push(option);
    std::vector<std::pair<int, int>> vertexEdges;
    while(!pq.empty())
    {
        int v = pq.top().first;
        pq.pop();
        if(visited.at(v)==false)
        {
            //std::cout<<v<<std::endl;
            visited.at(v)=true;
            //std::cout<<visited.at(v)<<std::endl;
            double weigh;
            for(auto edge:di_map.at(v).edges)
            {
                weigh= edgeWeightFunc(edge.einfo);
                //std::cout<<weigh<<std::endl;
                    for(auto vx:keys)
                    {
                        if(edge.toVertex==vx && visited.at(vx)==false)
                        {
                            //std::cout<<vx<<std::endl;
                            int new_loc=vx;
                            //std::cout<<new_loc<<std::endl;
                            if(best.at(new_loc)>weigh)
                            {
                                //std::cout<<new_loc<<std::endl;

                                //std::cout<<best.at(new_loc);

                                best.at(new_loc)=weigh;
                                //std::cout<<best.at(new_loc);
                                pv.at(new_loc)=v;
                                //std::cout<<best.at(new_loc);
                                //std::cout<<pv.at(new_loc);

                                option.first=new_loc;
                                //std::cout<<option.first<<std::endl;
                                option.second=best.at(new_loc);
                                pq.push(option);
                            }
                        }
                    }

            }
        }
    }
    
    return pv;

    }
    struct weight
    {
    public:
        bool operator()(std::pair<int, double> n1, std::pair<int, double> n2)
        {
            
            return n1.second<n2.second;
        }

    };
/* 
	struct EdgeInfo
	{
		EdgeInfo key;
	};
	struct VertexInfo
	{
		VertexInfo key;
	};
*/	
private:
    //DigraphVertex<VertexInfo,EdgeInfo> vertx;
    //DigraphEdge<VertexInfo> edge;
    //DigraphEdge

    //std::list<int> vertx;
    //std::Vector<Trip> trip;
    std::vector<int> keys;
    int num_vertex, num_edge;
    //std::map<DigraphVertex<VertexInfo, EdgeInfo>, int> Di_map;
    std::map<int, DigraphVertex<VertexInfo, EdgeInfo>> di_map;
    //std::map<int, std::set<std::string>> map2;
	//typename DigraphEdge<EdgeInfo>::EdgeInfo edge;
	//typename DigraphVertex<VertexInfo, EdgeInfo>::VertexInfo vertex;

    // Add whatever member variables you think you need here.  One
    // possibility is a std::map where the keys are vertex numbers
    // and the values are DigraphVertex<VertexInfo, EdgeInfo> objects.


    // You can also feel free to add any additional member functions
    // you'd like (public or private), so long as you don't remove or
    // change the signatures of the ones that already exist.
};



// You'll need to define the member functions of your Digraph class
// template here.
template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph()
{
    num_vertex=0;
    num_edge=0;

}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(const Digraph& d)
{
    di_map=d.di_map;
    /*
    Digraph D_map;

    for(auto& item: d)
    {
        VertexInfo v;
        EdgeInfo e;
        D_map.make_pair(item.first, )
    }
    */


}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::~Digraph()
{}

template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(const Digraph& d)
{
    return *this;

}


template <typename VertexInfo, typename EdgeInfo>
std::vector<int> Digraph<VertexInfo, EdgeInfo>::vertices() const
{
    return keys;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int,int>> Digraph<VertexInfo, EdgeInfo>::edges() const
{
	std::vector<std::pair<int, int>> vect;
	for (auto& vx : di_map)
	{
		for (auto& ex : vx.second.edges)
		{
			//std::cout<<"from: "<<ex.fromVertex<<" to vertex: "<<ex.toVertex<<std::endl;
        	//std::cout<<"m: "<<ex.einfo.miles<<"  mph: "<<ex.einfo.milesPerHour<<std::endl;
        	vect.push_back(std::make_pair(ex.fromVertex,ex.toVertex));

		}
	}
    return vect;
    //std::vector<std::pair<int, int>> all_edge;
    //for(auto& vertx:keys)
    //{
    /*
	for (int i=0; i<keys.size();i++)
	{


        std::cout<<"vertex: "<<di_map[i].vinfo<<std::endl;
        for (auto& edge : di_map[vertx].edges)
        {
            all_edge.push_back(std::make_pair(edge.fromVertex, edge.toVertex));
        }
    }
    return all_edge;
    */
    
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges(int vertex) const
{
	/*
	for (auto& edge : di_map[fromVertex].edges)
    {
        std::cout<<"from: "<<edge.fromVertex<<" to vertex: "<<edge.toVertex<<std::endl;
        std::cout<<"m: "<<edge.einfo.miles<<"  mph: "<<edge.einfo.milesPerHour<<std::endl;
    }
*/
    //std::cout<<"vertex: "<<vertex<<std::endl;
    std::vector<std::pair<int, int>> edge_items;
    try{
    //for(auto& k:keys)
    //{
        //if(k==vertex)
        //{
            
            for (auto& edge : di_map.at(vertex).edges)
            {
        //std::cout<<edge.toVertex<<std::endl;
        //std::cout<<"vertex: "<<edge.first<<std::endl;
        //if(edge.first==vertex)
        //{
        //  std::cout<<edge.second.edges.fromVertex<<std::endl;
            //edge_items.push_back(std::make_pair(edge.second.edges.fromVertex,
                //edge.second.edges.toVertex));
        //}
        //std::cout<<"from: "<<edge.fromVertex<<" to vertex: "<<edge.toVertex<<std::endl;
        //std::cout<<"m: "<<edge.einfo.miles<<"  mph: "<<edge.einfo.milesPerHour<<std::endl;
                edge_items.push_back(std::make_pair(edge.fromVertex,edge.toVertex));
            }
            return edge_items;

        }
    //}
//}
    
    //std::cout<<e.reason()<<std::endl;
    catch(...) 
    {
        //std::cout<<"out of range"<<std::endl;
        DigraphException e("index does not exist");
        std::cout<<e.reason()<<std::endl;

    }
    return edge_items;

}


template <typename VertexInfo, typename EdgeInfo>
//typename DigraphVertex<VertexInfo, EdgeInfo>::VertexInfo 
//typename DigraphVertex<VertexInfo, EdgeInfo>::
//typename Digraph<VertexInfo, EdgeInfo>::
VertexInfo Digraph<VertexInfo, EdgeInfo>::vertexInfo(int vertex) const
{
    VertexInfo vfo;
    try
    {
        vfo=di_map.at(vertex).vinfo;
        return vfo;
    }
    catch(...) 
    {
        //std::cout<<"out of range"<<std::endl;
        DigraphException e("index does not exist in vertexInfo");
        std::cout<<e.reason()<<std::endl;

    }
	return vfo;
    //std::cout<<di_map[vertex].vinfo<<std::endl;
    //return di_map[vertex];
}



template <typename VertexInfo, typename EdgeInfo>
//typename DigraphEdge<EdgeInfo>::EdgeInfo 
//typename DigraphEdge<EdgeInfo>::
//typename Digraph<VertexInfo, EdgeInfo>::
EdgeInfo Digraph<VertexInfo, EdgeInfo>::edgeInfo(int fromVertex, int toVertex) const
{
    //for (auto& edge : di_map[fromVertex].edges)
    EdgeInfo ed;
    DigraphException e("index does not exist in edgeInfo");
try{
    for (auto& edge : di_map.at(fromVertex).edges)
    {
        if(edge.toVertex==toVertex)
        {
            return edge.einfo;
        }
    }
    throw(e);
}
    catch(...) 
    {
        //std::cout<<"out of range"<<std::endl;
        //DigraphException e("index does not exist in edgeInfo");
        std::cout<<e.reason()<<std::endl;

    }
    return ed;
    
}



template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addVertex(int vertex, const VertexInfo&vinfo)
{
    //Digraph.map_loc.insert(std::pair<int, set<std::string>> (vertex, vinfo));
    //std::set<std::string> myset.insert(vinfo);
    //std::set<std::string> myset;
    //myset.insert(vinfo);
    //Di_map.insert(std::make_pair())
    //vertx{vinfo};
    //map_loc.insert(std::make_pair(vinfo, vertex));
    //di_map.insert(std::make_pair(vertex, std::make_pair(vinfo)))
    
    //Digraph.map_loc[vertex].insert(myset));
    //std::cout<<"vertex: "<<vertex<<std::endl;
    //std::cout<<"vertexinfo: "<<vinfo<<std::endl;
    //EdgeInfo ed(RoadSegment{4,2});
    //std::cout<<"vertex add: "<<vertex<<std::endl;
    DigraphException e("vertex already exists");
    //vertx.push_back(vertex);
    

    std::list<DigraphEdge<EdgeInfo>> ed;
    DigraphVertex<VertexInfo, EdgeInfo> vx{vinfo, ed};

    //std::cout<<ed.miles<<"    "<<ed.milesPerHour<<std::endl;
    //for(auto v: vertx)
    //for (int v: vertx)
try{
    for(auto v: keys)
    {
        //std::cout<<"v: "<<v<<std::endl;
        //std::cout<<"vinfo: "<<di_map[i].vinfo<<std::endl;
        //std::cout<<"vinfo0: "<<di_map[0].vinfo<<std::endl;

        //std::cout<<"vinfop: "<<vinfo<<std::endl;
        if(v==vertex)
        {
            //std::cout<<"---------there is a repeat of vertex!"<<std::endl;
            throw(e);
        }
    }
    //std::cout<<"executed"<<std::endl;

    keys.push_back(vertex);
    di_map.insert(std::make_pair(vertex, vx));
    num_vertex++;
    
}
    catch(...)
    {
        std::cout<<e.reason()<<std::endl;
        return;
    }
    //std::cout<<"------->"<<vertex<<std::endl;
    //std::cout<<"getting stored: "<<std::endl;

    
    //di_map.emplace(vertex, vinfo, ed);



    //std::cout<<"vertex: "<<vertex<<std::endl;
    /*   
    for(typename std::map<int, DigraphVertex<VertexInfo, EdgeInfo>>::iterator it=di_map.begin(); 
        it!=di_map.end(); ++it)
    {
        //int first=it->first;
        //std::set<std::string> second=it->second;
        std::cout<<it->first<<std::endl;

        //<<it->second<<std::endl;
        //std::cout<<it->second<<std:endl;
    }
    */
    //std::cout<<vertex<<"    "<<di_map[vertex].vinfo<<std::endl;
    
    
    //std::cout<<"addVertex"<<std::endl;
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo)
{
    DigraphEdge<EdgeInfo> ed{fromVertex, toVertex, einfo};
    DigraphException e("vertex does not exists");
    DigraphException v("vertex destination already exists");
    //di_map.edges.empalce(ed);
    /*
    for(int i=0; i<vertx.size();i++)
    {
        di_map[vertx[i]].edges.push_back(ed);
        //std::cout<<di_map[vertx[i]].edges.fromVertex<<std::endl;
    }
*/

    //std::cout<<di_map[fromVertex].edges.toVertex<<std::endl;
    //for (EdgeInfo& edge : di_map[fromVertex].edges)
    //std::cout<<"    -   -   -   -   -   "<<std::endl;
try{
    for (auto& edge : di_map[fromVertex].edges)
    {
        if(edge.toVertex==toVertex)
        {
            //std::cout<<"there is a repeat of edges!"<<std::endl;
            throw(v);
            //return;
        }
        //else
            //edge.push_back(ed);
            //di_map[fromVertex].edges.push_back(ed); 

        //std::cout<<edge.fromVertex<<" to vertex: "<<edge.toVertex<<std::endl;
        //std::cout<<"m: "<<edge.einfo.miles<<"  mph: "<<edge.einfo.milesPerHour<<std::endl;
    }
    //std::cout<<"-------->"<<fromVertex<<std::endl;
    di_map[fromVertex].edges.push_back(ed); 
    num_edge++;
}
    catch(std::out_of_range)
    {
        std::cout<<e.reason()<<std::endl;
        return;
    }
    catch(DigraphException& v)
    {
        std::cout<<v.reason()<<std::endl;
        return;
    }
    //std::cout<<"loc_before: "<<di_map[0].vinfo<<std::endl;
    //di_map.removeVertex(0);
    //std::cout<<"loc_0: "<<di_map[0].vinfo<<std::endl;
/*
    for (auto& edge : di_map[fromVertex].edges)
    {
        std::cout<<"from: "<<edge.fromVertex<<" to vertex: "<<edge.toVertex<<std::endl;
        std::cout<<"m: "<<edge.einfo.miles<<"  mph: "<<edge.einfo.milesPerHour<<std::endl;
    }

    for(typename std::map<int, DigraphVertex<VertexInfo, EdgeInfo>>::iterator it=di_map.begin(); 
        it!=di_map.end(); ++it)
    {
        
        //for(typename DigraphVertex<VertexInfo, EdgeInfo>::iterator it2=di_map.begin();
        //    it2!=di_map.end(); ++it2)
        //{
            //it->second=ed;
        
        
        //int first=it->first;
        //std::set<std::string> second=it->second;
        //std::cout<<it->first<<std::endl;
        it->second.edges.push_back(ed);
        //std::cout<<di_map.edges.fromVertex<<std::endl;
        //std::cout<<it->second.edges.fromVertex<<std::endl;

        // {ed};
        //<<it->second<<std::endl;
        //std::cout<<it->second<<std:endl;
       //}
    }
    std::cout<<di_map[0].edges.fromVertex<<std::endl;
    
    //edge{toVertex, fromVertex, einfo};
    //std::cout<<"to: "<<fromVertex<<" from: "<<toVertex<<std::endl;
    //std::cout<<"edgeinfo: "<<einfo.miles<<" "<<einfo.milesPerHour<<std::endl;

    //std::cout<<"addEdge"<<std::endl;
*/
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeVertex(int vertex)
{
    //std::cout<<"find: "<<di_map[vertex].vinfo<<std::endl;
    //if(di_map.find(vertex)<0)
    // if(di_map.find(vertex)==di_map.end())
    // {
    //     //std::cout<<"not exists!"<<std::endl;
    //     return;
    // }
    //int i=0;
//for(typename std::map<int, DigraphVertex<VertexInfo, EdgeInfo>>::iterator it=di_map.begin(); it!=di_map.end(); ++it)
    DigraphException e("vertex does not exist to be removed");
try{
    for(std::vector<int>::iterator it=keys.begin();it!=keys.end(); ++it)
    {
        //i++
        if(*it==vertex)
        {
            keys.erase(it);
            di_map.erase(vertex);
            return;
        }
    }
    throw(e);
}
catch(...)
{
    std::cout<<e.reason()<<std::endl;
    return;
}
    
    //keys.erase(keys.begin()+vertex);
    //std::cout<<"after find: "<<di_map[vertex].vinfo<<std::endl;

    //std::cout<<"after find: "<<di_map[50].vinfo<<std::endl;

    num_vertex--;
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeEdge(int fromVertex, int toVertex)
{
    /*
    std::cout<<"----->"<<fromVertex<<std::endl;
    //int i=0;
    for (auto& edge : di_map[fromVertex].edges)
    {
        std::cout<<"before from: "<<edge.fromVertex<<" to vertex: "<<edge.toVertex<<std::endl;
        std::cout<<"m: "<<edge.einfo.miles<<"  mph: "<<edge.einfo.milesPerHour<<std::endl;
    }
*/
    DigraphException e("edge does not exist");
    //DigraphException o("vertex does not exist");
try{
    for (auto& edge : di_map[fromVertex].edges)
    {
        if(edge.toVertex==toVertex)
        {
            //std::cout<<"found the vertex!"<<std::endl;
            edge.toVertex=di_map.erase(toVertex);
            num_edge--;
            return;
            //edge.remove(toVertex);
            //di_map.erase(edge);
            //di_map[fromVertex].erase(edge);
        }
        //std::cout<<"from: "<<edge.fromVertex<<" to vertex: "<<edge.toVertex<<std::endl;
        //std::cout<<"m: "<<edge.einfo.miles<<"  mph: "<<edge.einfo.milesPerHour<<std::endl;
    }
    throw(e);
}
    // catch(std::out_of_range)
    // {
    //     std::cout<<o.reason()<<std::endl;
    //     return;
    // }
    catch(DigraphException e)
    {
        std::cout<<e.reason()<<std::endl;
        return;
    }
    
    //di_map[fromVertex].edges.find(toVertex);
    //std::cout<<"map at ver/edge: "<<di_map[fromVertex].edges[toVertex]<<std::endl;
/*
    for (auto& edge : di_map[fromVertex].edges)
    {
        std::cout<<"after from: "<<edge.fromVertex<<" to vertex: "<<edge.toVertex<<std::endl;
        std::cout<<"m: "<<edge.einfo.miles<<"  mph: "<<edge.einfo.milesPerHour<<std::endl;
    }
    */
}

//void removeEdge(int fromVertex, int toVertex)
//{

//}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::vertexCount() const
{
    return num_vertex;
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount() const
{
    return num_edge;
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount(int vertex) const
{
    int edge_count=0;
    for (auto& edge : di_map.at(vertex).edges)
    {
        edge_count++;
    }
    return edge_count++;
}



template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::isStronglyConnected() const
{
    if(keys.size()<1)
        return false;
    std::map<int, bool> visited;
    std::vector<int> stack;
    for(auto v: keys)
    {
        visited.insert(std::make_pair(v, false));
        
    }
    stack.push_back(keys[0]);
    while(!stack.empty())
    {
        int loc=stack.back();
        stack.pop_back();
        if(visited.at(loc)==false)
        {
            visited.at(loc)=true;
            for(auto edge: di_map.at(loc).edges)
            {
                for(auto v: keys)
                {
                    if(edge.toVertex==v && visited.at(v)==false)
                    {
                        int new_v=v;
                        stack.push_back(new_v);
                    }
                }
            }
        }
    }
    //bool connected=false;
    int i=0;
    for(auto v: visited)
    {
        i++;
        if(v.second==false&&i==(visited.size()-1))
        {
            //std::cout<<"fasle"<<std::endl;
            return false;
        }
    }
    return true;



}
//template<typename VertexInfo, typename EdgeInfo>
//std::map<int, int> findShortestPaths(int startVertex,std::function<double(const EdgeInfo&)> edgeWeightFunc) //const
//{
    
//}



#endif // DIGRAPH_HPP

