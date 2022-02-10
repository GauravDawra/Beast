//
// Created by Gaurav Dawra on 25/12/21.
//

#include "Graph.h"
namespace Beast {
    Graph::Graph(int n) : m_NumNodes(n), m_NumEdges(0), m_IsCyclical(false) {
        m_AdjacencyList.assign(n, std::vector<int>());
    }
    Graph::Graph() : m_NumNodes(0), m_NumEdges(0), m_IsCyclical(false) {
        // blank for now
    }
    void Graph::addEdge(int u, int v) {
        if(u > m_NumNodes or v > m_NumNodes) {
            return; // failure
        }
        m_AdjacencyList[u].push_back(v);
        m_NumEdges++;
    }

    void Graph::addEdgeIncremental(int u, int v) {
        if (u == m_NumNodes + 1 || v == m_NumNodes + 1) {
            m_AdjacencyList.push_back(std::vector<int>());
        }
        else if (u > m_NumNodes + 1 || v > m_NumNodes + 1) {
            return;
        }
        m_AdjacencyList[u].push_back(v);
        m_NumEdges++;
    }

    void Graph::depthFirstSearch(int cur, std::vector<int>& visited) {
        visited[cur] = 1;
        for (int v : m_AdjacencyList[cur]) {
            if (!visited[v]) {
                depthFirstSearch(v, visited);
                if (m_IsCyclical) return;
            }
            else if (visited[v] == 1) { // cyclical dependancy
                m_IsCyclical = true;
                return;
            }
        }
        m_TopologicalSort.push_back(cur);
        visited[cur] = 2;
    }

    void Graph::topologicalSort() {
        m_TopologicalSort.clear();
        m_TopologicalSort.reserve(m_NumNodes);
        std::vector<int> visited(m_NumNodes, 0);
        for (int i = 0; i < m_NumNodes; i++) {
            if (!visited[i]) {
                depthFirstSearch(i, visited);
            }
        }
        if (!m_IsCyclical) {
            std::reverse(m_TopologicalSort.begin(), m_TopologicalSort.end());
        }
        else {
            m_TopologicalSort.clear();
        }
    }

    bool Graph::isCyclical() const {
        return m_IsCyclical;
    }

    void Graph::tillIndex(int index) {
        while (m_AdjacencyList.size() < index) {
            m_AdjacencyList.push_back(std::vector<int>());
        }
    }

    void buildGraph(const FileSystem& fileSystem, const BuildFile& buildFile, Graph& graph) {
        for (const BuildRule& rule : buildFile.getRules()) {
            int outputIndex = fileSystem.index(rule.getOutputTarget());
            for (const std::string& inputTarget : rule.getInputTargets()) {
                graph.addEdge(fileSystem.index(inputTarget), outputIndex);
            }
        }
    }

    void buildDependencyTogether(const BuildFile &buildFile, FileSystem &fileSystem, Graph &graph) {
        for (const BuildRule& rule : buildFile.getRules()) {
            const std::string& output = rule.getOutputTarget();
            fileSystem.addFile(output);
            graph.tillIndex(fileSystem.index(output));
            for (const std::string& input : rule.getInputTargets()) {
                fileSystem.addFile(input);
                graph.tillIndex(fileSystem.index(input));
                graph.addEdgeIncremental(fileSystem.index(input), fileSystem.index(output));
            }
        }
    }
}
