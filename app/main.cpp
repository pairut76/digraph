// main.cpp
//
// ICS 46 Spring 2016
// Project #4: Rock and Roll Stops the Traffic
//
// This is the program's main() function, which is the entry point for your
// console user interface.
#include <iostream>
#include <fstream>
#include "InputReader.hpp"
#include "RoadMapReader.hpp"
#include <string>
#include <vector>
#include <map>
#include <set>
#include "RoadSegment.hpp"
#include "Digraph.hpp"
/*
#include "RoadMapReader.cpp"
#include "RoadMapWriter.cpp"
#include "RoadSegment.hpp"
#include "Trip.hpp"
#include "TripMetric.hpp"
#include "TripReader.cpp"
*/
void open_f()
{
	
	//int lines=10;
	std::string str;
	int a;
	std::cin>>str;
	//std::string str;
	InputReader inpt(std::cin);
	//int x;
	//for(int i=0;i<20;++i)
	//while(!str.eof())
	//while(inpt.readLine())
	//while(std::cin.good())
	//

	inpt.readLine();
	for(int i=0; i<3;++i)
	{
		//inpt.readLine();
		a=inpt.readIntLine();
		//std::cout<<"a: "<<a<<std::endl;
		for(int j=0; j<a;++j)
		{
			std::cout<<inpt.readLine()<<std::endl;
		}
	}
	//while(true)//while
	
	return;

	//for (int i=0; i<20; ++i)
	//{
	//	std::getline(std::cin,str);
	//	std::cout<<i<<std::endl;
	//	std::cout<<str<<std::endl;
	//}
	/*
	std::ofstream myfile;
	try
	{
		myfile.open("sample.txt");
	}
	catch(...)
	{
		if(myfile.is_open())
			myfile.close();
	}
	//InputReader inpt{myfile};
	
	//char outpt[1000];
	//InputReader::readLine();
	//while(!myfile.eof())
	//{
	//	myfile>>outpt;
	//	std::cout<<outpt<<std::endl;
	//}
	
	//std::cout<<inpt.read<<std::endl;
*/
}
template <typename T>
T weight(T a,T b)
{
	return b+a;
}
//template<typename EdgeInfo>
double weight2(const RoadSegment& rs)
{	

	return rs.miles;//-rs.milesPerHour;
}
void test_weight()
{
	double x,y;
	x=3.4;
	y=5.3;
	int s,t;
	s=3;
	t=4;
	std::cout<<weight<int>(s,t)<<std::endl;
	std::cout<<weight<double>(x,y)<<std::endl;
}
void exception_test(RoadMap& rmap)
{
	std::vector<std::pair<int,int>> _edges; //from and to edges of a vertex

	_edges=rmap.edges(100);
	_edges=rmap.edges(3);
	rmap.vertexInfo(30);
	rmap.vertexInfo(7);
	rmap.edgeInfo(10,22);
	rmap.edgeInfo(22,22);
	rmap.edgeInfo(14,8);
	//rmap.removeVertex(0);
	rmap.addVertex(0, "whatever");
	std::cout<<rmap.vertexInfo(0)<<std::endl;
	rmap.addEdge(0, 1, RoadSegment{double (3.4), double (3.2)});
	rmap.removeVertex(100);
	rmap.removeVertex(0);
	rmap.vertexInfo(0);
	rmap.removeEdge(0, 1);
	rmap.removeEdge(1, 20);
	rmap.removeEdge(1,2);
	rmap.edgeInfo(1,2);//<<std::endl;
}
//template <typename VertexInfo, typename EdgeInfo>
int main()
{

	//std::cout<<"--------hello from main"<<std::endl;
	//open_f();
	//std::string str;
	//int a;
	//std::cin>>str;
	//std::string str;

	InputReader inpt(std::cin);
	//inpt.readLine();
	RoadMapReader map;
	RoadMap rmap=map.readRoadMap(inpt);
	
	std::vector<int> vertxx;
	//std::map<int, std::vector<int, int>> kdv; //vertices: best distance so far, visited or not
	std::map<int, bool> visited; //visited kv
	std::map<int, int> top; // dv
	std::map<int,int> pv; //predecessors 

	vertxx=rmap.vertices();


	for(auto& v: vertxx)
	{
		//std::cout<<v<<std::endl;
		visited.insert(std::make_pair(v, false));
		top.insert(std::make_pair(v, 99999));
		pv.insert(std::make_pair(v, 0));

		//kdv.push_back(std::make_pair(v, std::make_pair(9999, false)));
		//pv.push_back(v, NULL);
	}
	//std::vector<std::pair<int,int>> _edges; //from and to edges of a vertex

	// pv[vertxx[0]]=-1;
	// top[vertxx[0]]=0;
	//for(auto& v:vertxx)
	//{
		//_edges=rmap.edges(v);

		//for(auto& e: _edges)
		//{
	std::map<int, int> shortest;

	shortest=rmap.findShortestPaths(vertxx[0], (weight2));
	for(auto s: shortest)
	{
		std::cout<<"first: "<<s.first<<" second: "<<s.second<<std::endl;
		//}
	}
	std::cout<<rmap.isStronglyConnected()<<std::endl;
	//RoadMap new_map=rmap;
	//exception_test(new_map);
	//}


	//std::cout<<rmap.vertexInfo(30).vinfo<<std::endl;
	//std::cout<<rmap.vertexInfo(13).vinfo<<std::endl;

	//std::cout<<"after edge[0]: "<<rmap.edges(0)<<std::endl;
	//std::cout<<"after edge[1]: "<<rmap.edges(1)<<std::endl;

	//std::cout<<map.EdgeInfo<<std::endl;


	std::cout<<"done!"<<std::endl;
    return 0;
}
double func(const RoadSegment& rs){ return 3.4;}

void test_map(RoadMap rmap)
{
	/*
	std::cout<<"edgecount: "<<rmap.edgeCount()<<std::endl;
	std::cout<<"vertexcout: "<<rmap.vertexCount()<<std::endl;
	rmap.removeVertex(0);
	std::cout<<"aftervertexcout: "<<rmap.vertexCount()<<std::endl;
	rmap.removeVertex(0);
	//std::vector<std::pair<int, int>> vect;
	
	rmap.removeEdge(0,0);
	rmap.removeEdge(1,0);
	vect=rmap.edges(2);
	vect=rmap.edges();
	std::cout<<rmap.vertexInfo(2)<<std::endl;
	//EdgeInfo ei;
	//ei=rmap.edgeInfo(1,4);
	std::cout<<rmap.edgeInfo(1,4).miles<<"	"<<rmap.edgeInfo(1,4).milesPerHour<<std::endl;
	std::cout<<rmap.edgeInfo(0,0).miles<<"	"<<rmap.edgeInfo(0,0).milesPerHour<<std::endl;
	//std::vector<int> vect=rmap.edges(0);
	
	std::vector<int,int> vect=rmap.edges(0);


	for(int i=0; i<rmap.edges(0).size();++i)
	{
		std::cout<<"edge[0]: "<<vect[i]<<std::endl;
		//std::cout<<"edge[1]: "<<rmap.edges(1)<<std::endl;
	}
	*/
}

