//
// Created by Gaurav Dawra on 25/12/21.
//

#ifndef BEAST_GRAPH_H
#define BEAST_GRAPH_H

#include <vector>
#include "Filesystem.h"

namespace Beast {
    class Graph {
    public:
        Graph(int n);
        Graph();
        void addEdge(int u, int v);
        void addEdgeIncremental(int u, int v);
        void tillIndex(int index);
        void topologicalSort();
        inline const std::vector<int>& getSorted() const {
            return m_TopologicalSort;
        }
        bool isCyclical() const;
    private:
        const int m_NumNodes; // value of n
        int m_NumEdges;
        bool m_IsCyclical;
        std::vector<std::vector<int> > m_AdjacencyList;
        std::vector<int> m_TopologicalSort;
        void depthFirstSearch(int cur, std::vector<int>& visited);
    };

    void buildGraph(const FileSystem& fileSystem, const BuildFile& buildFile, Graph& graph);
    void buildDependencyTogether(const BuildFile& buildFile, FileSystem& fileSystem, Graph& graph);
}

#endif //BEAST_GRAPH_H
