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
	    using index_t = FileSystem::index_t;
	    Graph(int n);
        Graph();
        void addEdge(index_t u, index_t v);
        void addEdgeIncremental(index_t u, index_t v);
        void tillIndex(index_t index);
        void topologicalSort();
        inline const std::vector<int>& getSorted() const {
            return m_TopologicalSort;
        }
        bool isCyclical() const;
    private:
        const int m_NumNodes; // value of n
        int m_NumEdges;
        bool m_IsCyclical;
        std::vector<std::vector<index_t> > m_AdjacencyList;
        std::vector<index_t> m_TopologicalSort;
        void depthFirstSearch(index_t cur, std::vector<int>& visited);
    };

    void buildGraph(const FileSystem& fileSystem, const BuildFile& buildFile, Graph& graph);
    void buildDependencyTogether(const BuildFile& buildFile, FileSystem& fileSystem, Graph& graph);
}

#endif //BEAST_GRAPH_H
