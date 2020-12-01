#pragma once
#include <unordered_map>
#include <unordered_set>

class CGraph
{
	struct Vertex
	{
		int EnteranceEdgeId;
		int OwnVertexId;
		std::unordered_set <int> ExitEdgeIds;
	};
	struct Edge
	{
		int StartVertexId;
		int OwnEdgeId;
		int EndVertexId;
	};
public:
	void Connect(int idVer1, int idVer2, int idEdge);
private:
	CGraph::Vertex AddVertex(int ownId, int exitId, int enteranceId);
	CGraph::Edge AddEdge(int startId, int ownId, int endId);
	void EraseVertex(int id);
	void EraseEdge(int id);
	void SwapVertex(int id1, int id2);
	std::unordered_map <int, Vertex> MapVertex;
	std::unordered_map <int, Edge> MapEdge;
};
