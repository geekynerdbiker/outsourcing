#include "Manager.h"
#include "Queue.h"
#include <cstring>

Manager::~Manager()
{
    if (fout.is_open())
        fout.close();
    
    if (ferr.is_open())
        ferr.close();
}

void Manager::Run(const char* filepath)
{
    fout.open(RESULT_LOG_PATH);
    ferr.open(ERROR_LOG_PATH);
    
    cout << Load(filepath);
}
void Manager::PrintError(Result result)
{
    ferr << "Error code: " << result << std::endl;
}

/// <summary>
/// make a graph
/// </summary>
///
/// <param name="filepath">
/// the filepath to read to make the graph
/// </param>
///
/// <returns>
/// Result::Success if load is successful.
/// Result::LoadFileNotExist if file is not exist.
/// </returns>
Result Manager::Load(const char* filepath)
{
    FILE* file = fopen(filepath, "r");
    
    if (file == NULL) {
        printf("File does not exist.\n");
        return LoadFileNotExist;
    }
    
    return Success;
    
}
/// <summary>
/// print out the graph as matrix form
/// </summary>
///
/// <returns>
/// Result::Success if the printing is successful
/// Result::GraphNotExist if there is no graph
/// </returns>
Result Manager::Print()
{
    return Success;
    // TODO: implement
}
/// <summary>
/// find the path from startVertexKey to endVertexKey with BFS
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindPathBfs(int startVertexKey, int endVertexKey)
{
    bool *m_visit = new bool [m_graph.Size()];
    
    Queue<int> q;
    q.Push(startVertexKey);
    m_visit[startVertexKey] = true;
    
    while (!q.Empty())
    {
        int pPoint = q.front;
        q.Pop();
        
        if (pPoint == endVertexKey)
        {
            return Success; //Arrive the distinition
        }
        
        for (int i = 0; i < m_graph.Size(); i++) {
            //The current point is not visited and can pass
            if (!m_visit[m_graph.FindVertex(pPoint)->GetKey()])
            {
                m_visit[m_graph.FindVertex(pPoint)->GetKey()] = true;
                q.Push(m_graph.FindVertex(pPoint)->GetKey());
            }
        }
        
    }
    return Success;
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
    // TODO: implement
    return Success;
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Bellman-Ford
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::NegativeCycleDetected if exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
    return Success;
    // TODO: implement
}

Result Manager::RabinKarpCompare(const char* CompareString,const char* ComparedString)
{
    return Success;
    // TODO: implement
}
