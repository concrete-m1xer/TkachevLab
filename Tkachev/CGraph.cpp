#include "CGraph.h"
#include "assistance.h"

void CGraph::Connect(int idVer1, int idVer2, int idEdge)
{
    bool Ver1Connection = (MapVertex.find(idVer1) != MapVertex.end());
    bool Ver2Connection = (MapVertex.find(idVer2) != MapVertex.end());
    bool EdgeConnection = (MapEdge.find(idEdge) != MapEdge.end());
    if (Ver1Connection && Ver2Connection && EdgeConnection)
    {
        stringAlert("All this elements are already connected to the net, please, chose another ");
    }
    if (!Ver1Connection && !Ver1Connection && !EdgeConnection)
    {
        AddVertex(idVer1, idEdge);
        AddVertex(idVer2, -1, idEdge);
        AddEdge(idVer1, idEdge, idVer2);
    }
    if (Ver1Connection && !Ver2Connection && !EdgeConnection)
    {
        MapVertex[idVer1]
    }
}

CGraph::Vertex CGraph::AddVertex(int ownId, int exitId = -1, int enteranceId = -1)
{
    Vertex V;
    V.EnteranceEdgeId = enteranceId;
    V.OwnVertexId = ownId;
    if (exitId != -1)
    {
        V.ExitEdgeIds.insert(exitId);
    }
    MapVertex.insert(std::pair <int, Vertex>(ownId, V));
    return CGraph::Vertex();
}

CGraph::Edge CGraph::AddEdge(int startId, int ownId, int endId)
{
    Edge E;
    E.StartVertexId = startId;
    E.OwnEdgeId = ownId;
    E.EndVertexId = endId;
    MapEdge.insert(std::pair<int, Edge>(ownId, E));
    return CGraph::Edge();
}

void CGraph::EraseVertex(int id)
{
    std::unordered_map<int, Vertex>::iterator it = MapVertex.find(id);
    EraseEdge(it->second.EnteranceEdgeId);
    for (int id : it->second.ExitEdgeIds)
    {
        EraseEdge(id);
    }
    MapVertex.erase(it);
}

void CGraph::EraseEdge(int id)
{
    std::unordered_map<int, Edge>::iterator it = MapEdge.find(id);
    MapVertex[it->second.StartVertexId].ExitEdgeIds.erase(id);
    MapVertex[it->second.EndVertexId].EnteranceEdgeId = -1; //если вершина имеет "входящее id" -1, то значит в неё не заходят ребра
    MapEdge.erase(id);
}

void CGraph::SwapVertex(int inid, int ejid)
{
    swapValues(MapVertex[inid].OwnVertexId, MapVertex[ejid].OwnVertexId);
}
