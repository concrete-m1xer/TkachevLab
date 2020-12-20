#include "CGraph.h"

void CGraph::ConnectDirected(int idVer1, int idVer2, int idEdge, double Weight, double Capacity, bool IsStraight)
{
    bool Ver1Connection = HasVertex(idVer1);
    bool Ver2Connection = HasVertex(idVer2);
    bool EdgeConnection = HasEdge(idEdge);
    if (!EdgeConnection && idVer1 != 0 && idVer2 != 0 && idEdge != 0)
    {
        if (Ver1Connection && Ver2Connection)
        {   
            AddEdge(idVer1, idEdge, idVer2, Weight, Capacity, true, IsStraight);
        }
        else if (!Ver1Connection && !Ver2Connection)
        {
            AddVertex(idVer1);
            AddVertex(idVer2);
            AddEdge(idVer1, idEdge, idVer2, Weight, Capacity, true, IsStraight);
        }
        else if (Ver1Connection && !Ver2Connection)
        {
            AddVertex(idVer2);
            AddEdge(idVer1, idEdge, idVer2, Weight, Capacity, true, IsStraight);
        }
        else if (!Ver1Connection && Ver2Connection)
        {
            AddVertex(idVer1);
            AddEdge(idVer1, idEdge, idVer2, Weight, Capacity, true, IsStraight);
        }
    }
    else
    {
        StringAlert("This is already connected, chose another one");
    }
} 

std::vector<std::vector<int>> CGraph::FindAllPaths(int IdStart, int IdEnd) const
{
    auto WorkMap = MapVertex;
    std::vector<std::vector<int>> PathsVertex = { };
    std::vector<int> CurrentPath = { };
    std::stack<int> StackVert;
    StackVert.push(IdStart);
    while (!StackVert.empty())
    {
        std::map<int, Vertex>::iterator it = WorkMap.find(StackVert.top());
        if (!it->second.IsMarked)
        {
            if (it->first != IdEnd)
            {
                CurrentPath.push_back(it->first);
                it->second.IsMarked = true;
                for (int id : GetAdjacent(it->second.OwnVertexId))
                {
                    auto iter = WorkMap.find(id);
                    if(!iter->second.IsMarked)
                    {
                        StackVert.push(iter->first);
                    }
                }
            }
            else
            {
                CurrentPath.push_back(IdEnd);
                PathsVertex.push_back(CurrentPath);
                StackVert.pop();
                CurrentPath.pop_back();
            }
        }
        else if (it->second.IsMarked)
        {
            CurrentPath.pop_back();
            StackVert.pop();
            it->second.IsMarked = false;
        }
    }
    std::vector<std::vector<int>> Paths = { };
    for (unsigned int i = 0; i < PathsVertex.size(); i++)
    {
        Paths.push_back({ });
        for (unsigned int j = 0; j < PathsVertex[i].size()-1; j++)
        {
            for (const Edge& E : GetEjectors(PathsVertex[i][j]))
            {
                if (E.EndVertexId == PathsVertex[i][j + 1])
                {
                    Paths[i].push_back(E.OwnEdgeId);
                }
            }
        }
    }
    return Paths;
}

bool CGraph::IsCycled() const
{
    std::map<int, Vertex> WorkMap = MapVertex;

    std::stack <int> StackVert;
    for (const std::pair<const int, Vertex>& iter : MapVertex)
    {
        WorkMap = MapVertex;
        StackVert.push(iter.first);
        while (!StackVert.empty())
        {
            std::map<int, Vertex>::iterator it = WorkMap.find(StackVert.top());
            if (!it->second.IsMarked && !it->second.IsPassed)
            {
                it->second.IsMarked = true;
                for (int U : GetAdjacent(it->second.OwnVertexId))
                {
                    std::map<int, Vertex>::iterator itC = WorkMap.find(U);
                    if (!itC->second.IsMarked && !itC->second.IsPassed)
                    {
                        StackVert.push(itC->second.OwnVertexId);
                    }
                    else if (itC->second.IsMarked && !itC->second.IsPassed)
                    {
                        return true;
                    }
                }
            }
            else if (it->second.IsMarked && !it->second.IsPassed)
            {
                it->second.IsPassed = true;
                StackVert.pop();
            }
            else if (it->second.IsPassed)
            {
                StackVert.pop();
            }
        }
    }
    return false;
}


std::vector<int> CGraph::TopologicalSorting() const
{
    std::vector<int> Sorted; 
    if (!IsCycled())
    {
        std::map<int, Vertex> WorkMap;
        std::stack <int> StackVert;
        for (const std::pair<const int, Vertex>& iter : MapVertex)
        {
            Sorted.clear();
                WorkMap = MapVertex;
                StackVert.push(iter.first);
                while (!StackVert.empty())
                {
                    std::map<int, Vertex>::iterator it = WorkMap.find(StackVert.top());
                    if (!it->second.IsMarked && !it->second.IsPassed)
                    {
                        it->second.IsMarked = true;
                        for (int U : GetAdjacent(it->second.OwnVertexId))
                        {
                            std::map<int, Vertex>::iterator itC = WorkMap.find(U);
                            if (!itC->second.IsMarked && !itC->second.IsPassed)
                            {
                                StackVert.push(itC->second.OwnVertexId);
                            }
                        }
                    }
                    else if (it->second.IsMarked && !it->second.IsPassed)
                    {
                        it->second.IsPassed = true;
                        Sorted.insert(Sorted.begin(), it->first);
                        StackVert.pop();
                    }
                    else if (it->second.IsPassed)
                    {
                        StackVert.pop();
                    }
                }
                if (Sorted.size() == MapVertex.size())
                {
                    return Sorted;
                }
        }
        return { };
    }
    else
    {
        return { };
    }

}

void CGraph::DeleteVertex(int id)
{
    if (HasVertex(id))
    {
        auto it = MapVertex.find(id);
        std::vector<int> IdsForDelete;
        IdsForDelete.reserve(it->second.EdgeIds.size());
        for (int id : it->second.EdgeIds)
        {
            IdsForDelete.push_back(id);
        }
        for (int id : IdsForDelete)
        {
            DeleteEdge(id);
        }
        MapVertex.erase(it);
    }
    else
    {
        StringAlert("Vertex is not even added ");
    }
}

void CGraph::DeleteEdge(int id)
{
    if (HasEdge(id))
    {
        auto it = MapEdge.find(id);
        MapVertex[it->second.StartVertexId].EdgeIds.erase(id);
        MapVertex[it->second.EndVertexId].EdgeIds.erase(id);
        MapEdge.erase(id);
    }
    else
    {
        StringAlert("Edge not added yet ");
    }
}

void CGraph::ReplaceEdge(int IdOld, int IdNew, double Weight, bool IsStraight)
{
    int StartVertexId;
    int EndVertexId;
    if (HasEdge(IdOld))
    {
        StartVertexId = MapEdge[IdOld].StartVertexId;
        EndVertexId = MapEdge[IdOld].EndVertexId;
        DeleteEdge(IdOld);
        ConnectDirected(StartVertexId, EndVertexId, IdNew, Weight, IsStraight);
    }
    else
    {
        StringAlert("This edge not added to graph ");
    }
}

void CGraph::SwapVertex(int inid, int ejid)
{
    if (HasVertex(inid) && HasVertex(ejid))
    {
        swapValues(MapVertex[inid].EdgeIds, MapVertex[ejid].EdgeIds);
        for (auto& p : MapEdge)
        {
            if (p.second.EndVertexId == ejid)
            {
                p.second.EndVertexId = inid;
            }
            else if (p.second.EndVertexId == inid)
            {
                p.second.EndVertexId = ejid;
            }
            if (p.second.StartVertexId == inid)
            {
                p.second.StartVertexId = ejid;
            }
            else if (p.second.StartVertexId == ejid)
            {
                p.second.StartVertexId = inid;
            }
        }
        swapValues(MapVertex[inid].IsMarked, MapVertex[ejid].IsMarked);
        swapValues(MapVertex[inid].IsPassed, MapVertex[ejid].IsPassed);
    }
}



double CGraph::MaxFlow(int SourceId, int TargetId) const
{
    if (!IsCycled() && HasVertex(SourceId) && HasVertex(TargetId))
    {
        auto WorkMap = MapEdge;
        double maxFlow = 0.0;
        for (const std::vector<int>& vec : FindAllPaths(SourceId, TargetId)) // для каждого возможного пути
        {
            double CurrentFlow = 0.0;
            double MinCapacity = WorkMap[vec[0]].Capacity;
            for (int id : vec) // ищем минимальную проводимость
            {
                auto it = WorkMap.find(id);
                if (it->second.Capacity < MinCapacity)
                {
                    MinCapacity = it->second.Capacity;
                }
            }
            CurrentFlow = MinCapacity;
            for (int id : vec) // пускаем поток величиной, равной минимальной пропускной способности это пути, уменьшаем пропускные способности всех
            {
                auto it = WorkMap.find(id);
                it->second.Capacity -= CurrentFlow;
            }
            maxFlow += CurrentFlow;
        }
        return maxFlow;
    }
    else
    {
        StringAlert("Cannot find maximum flow (has cycle or one of entered ids is not suitable) ");
        return 0.0;
    }
}

double CGraph::MinPath(int StartId, int EndId) const
{
    if (!IsCycled() && HasVertex(StartId) && HasVertex(EndId))
    {
        double minimalPath = 0.0;
        std::vector<std::vector<int>> Paths = FindAllPaths(StartId, EndId);
        std::vector<int> IdPaths;
        if (!Paths.empty())
        {
            for (int id : Paths[0])
            {
                auto it = MapEdge.find(id);
                minimalPath += it->second.Weight;
            }
            for (const auto& vec : Paths)
            {
                double CurrentPath = 0.0;
                for (int id : vec)
                {
                    auto it = MapEdge.find(id);
                    CurrentPath += it->second.Weight;
                }
                if (CurrentPath < minimalPath)
                {
                    minimalPath = CurrentPath;
                    IdPaths = vec;
                }
            }
        }
        if (minimalPath >= INT_MAX)
        {
            StringAlert("InFiNyTy");
            IdPaths.clear();
            return 0.0;
        }
        else
        {
            for (int Id : IdPaths)
            {
                std::cout << Id << "  ";
            }
            std::cout << std::endl;
            return minimalPath;
        }
    }
    else 
    {
        StringAlert("Cannot find minimum path (has cycle or one of entered ids is not suitable) ");
        return 0.0;
    }
}

void CGraph::StringAlert(std::string s) const
{
    std::cout << std::endl << s << std::endl;
}

// рекурсивно - легко и понятно (не использую, просто так написал)
//void CGraph::DepthFirstSearch(int IdV)
//{
//    auto SearchMap = MapVertex;
//    auto iter = SearchMap.find(IdV);
//    iter->second.IsMarked = true;
//    std::vector <int> Adjacent = GetAdjacent(IdV);
//    for (int i = 0; i < Adjacent.size(); i++)
//    {
//        auto it = SearchMap.find(Adjacent[i]);
//        if (!it->second.IsMarked && !it->second.IsPassed)
//        {
//            DepthFirstSearch(it->second.OwnVertexId);
//        }
//    }
//    iter->second.IsPassed = true;
//}

CGraph::Vertex CGraph::AddVertex(int ownId)
{
    Vertex V;
    V.OwnVertexId = ownId;
    V.IsMarked = false;
    V.IsPassed = false;
    MapVertex.insert(std::pair <int, Vertex>(ownId, V));
    return V;
}

CGraph::Edge CGraph::AddEdge(int startId, int ownId, int endId, double Weight, double Cap, bool IsDirected, bool StartToEnd)
{
    Edge E;
    E.StartVertexId = startId;
    E.OwnEdgeId = ownId;
    E.EndVertexId = endId;
    E.Weight = Weight;
    E.Capacity = Cap;
    IsDirected ? E.IsDirected = true : E.IsDirected = false;
    if (!StartToEnd)
    {
        E.StartVertexId = endId;
        E.EndVertexId = startId;
    }
    MapEdge.insert(std::pair<int, Edge>(ownId, E));
    MapVertex[startId].EdgeIds.insert(ownId);
    MapVertex[endId].EdgeIds.insert(ownId);
    return E;
}


bool CGraph::HasVertex(int Id) const
{
    if (MapVertex.find(Id) != MapVertex.end())
        return true;
    else
        return false;
}

bool CGraph::HasEdge(int Id) const
{
    if (MapEdge.find(Id) != MapEdge.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CGraph::ResetEdge(int Id, bool IsBroken, double Capacity, double Weight)
{
    if (HasEdge(Id))
    {

        auto it = MapEdge.find(Id);
        if (IsBroken)
        {
            it->second.Capacity = 0;
            it->second.Weight = INT_MAX;
        }
        else
        {
            it->second.Capacity = Capacity;
            it->second.Weight = Weight;
        }
    }
}

// получаем все рёбра, выходящие из вершины (либо неориентированные)
std::vector<CGraph::Edge> CGraph::GetEjectors(int IdV) const
{
    std::vector <Edge> Ejectors;
    auto it = MapVertex.find(IdV);
    for (int id : it->second.EdgeIds)
    {
        auto itE = MapEdge.find(id);
        Edge E = itE->second;
        if ((E.IsDirected && E.StartVertexId == IdV) || !E.IsDirected)
        {
            if (E.EndVertexId == IdV)
            {
                swapValues(E.StartVertexId, E.EndVertexId);
            }
            Ejectors.push_back(E);
        }
    }
    return Ejectors;
}

std::vector<int> CGraph::GetAdjacent(int IdV) const
{
    std::vector <int> Adjacent;
    std::vector <Edge> Ejectors = GetEjectors(IdV);
    for (const Edge& E : Ejectors)
    {
        Adjacent.push_back(MapVertex.find(E.EndVertexId)->second.OwnVertexId);
    }
    return Adjacent;
}

std::ostream& operator <<(std::ostream& out, const CGraph& G)
{
    std::vector<std::vector <int>> matrix;
    matrix.resize(G.MapVertex.size() + 1);
    for (std::vector <int>& v : matrix)
    {
        v.resize(G.MapVertex.size() + 1);
    }
    matrix[0][0] = 0;
    auto it = G.MapVertex.begin();
    for (unsigned int i = 0; i < G.MapVertex.size(); i++)
    {
        matrix[0][i + 1] = it->first;
        matrix[i + 1][0] = it->first;
        it++;
    }
    for (unsigned int i = 1; i < matrix.size(); i++)
    {
        auto adj = G.GetAdjacent(matrix[i][0]);
        auto eject = G.GetEjectors(matrix[i][0]);
        for (unsigned int j = 1; j < matrix[i].size(); j++)
        {
            for (unsigned int k = 0; k < adj.size(); k++)
            {
                if (adj[k] == matrix[0][j])
                {
                    matrix[i][j] = eject[k].OwnEdgeId;
                }
            }
        }
    }
    for (unsigned int i = 0; i < matrix.size(); i++)
    {
        for (unsigned int j = 0; j < matrix[i].size(); j++)
        {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    return out;
}

std::istream& operator>>(std::istream& in, CGraph& G)
{
    G.MapEdge.clear();
    G.MapVertex.clear();
    std::cout << "Please, enter number of vertexes: ";
    int n = 0;
    std::cin >> n;
    std::vector <int> VecVertex;
    VecVertex.reserve(n);
    for (int i = 0; i < n; i++)
    {
        VecVertex.push_back(tryInput("Please, enter vertex id: ", 0));
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << "Please, enter an id of directed edge between vertexes " 
                << VecVertex[i] << " and " << VecVertex[j] << " (zero, if there is no edge): ";
            int id = tryInput("", 0);
            if (id != 0)
            {
                double w = tryInput<double>("Please, enter a weight of this edge: ", 0.0);
                double c = tryInput<double>("Please, enter a capacity of this edge: ", 0.0);
                bool IsStraight = tryInput<bool>("Whether this edge is from first to second vertex? ([1] - yes, [0] - revers): ", 0, 1);
                G.ConnectDirected(VecVertex[i], VecVertex[j], id, w, c);
            }
        }
    }
    return in;
}

std::ifstream& operator>>(std::ifstream& fin, CGraph& G)
{
    G.MapEdge.clear();
    G.MapVertex.clear();
    int size = 0;
    fin >> size;
    while (size--)
    {
        int OwnEdgeId = 0, StartVertexId = 0, EndVertexId = 0;
        bool IsDirected = true;
        double Weight = 0.0, Capacity = 0.0;
        fin >> OwnEdgeId;
        fin >> StartVertexId;
        fin >> EndVertexId;
        fin >> IsDirected;
        fin >> Weight;
        fin >> Capacity;
        if (IsDirected)
        {
            G.ConnectDirected(StartVertexId, EndVertexId, OwnEdgeId, Weight, Capacity);
        }
    }
    return fin;
}

std::ofstream& operator<<(std::ofstream& fout, const CGraph& G)
{
    fout << G.MapEdge.size() << std::endl;
    for (auto& p : G.MapEdge)
    {
        fout << p.second.OwnEdgeId << std::endl;
        fout << p.second.StartVertexId << std::endl;
        fout << p.second.EndVertexId << std::endl;
        fout << p.second.IsDirected << std::endl;
        fout << p.second.Weight << std::endl;
        fout << p.second.Capacity << std::endl;
    }
    return fout;
}
