//
// Created by Gaurav Dawra on 25/12/21.
//

#include "Graph.h"
#include "Error.h"
#include <unordered_set>
namespace Beast {
    Graph::Graph(int n) : m_NumNodes(n), m_NumEdges(0), m_IsCyclical(false) {
        m_AdjacencyList.assign(n, std::vector<int>());
    }
    Graph::Graph() : m_NumNodes(0), m_NumEdges(0), m_IsCyclical(false) {
        // blank for now
    }
    void Graph::addEdge(index_t u, index_t v) {
        if(u > m_NumNodes or v > m_NumNodes) {
            return; // failure
        }
        m_AdjacencyList[u].push_back(v);
        m_NumEdges++;
    }

    void Graph::addEdgeIncremental(index_t u, index_t v) {
        if (u == m_NumNodes + 1 || v == m_NumNodes + 1) {
            m_AdjacencyList.push_back(std::vector<int>());
        }
        else if (u > m_NumNodes + 1 || v > m_NumNodes + 1) {
            return;
        }
        m_AdjacencyList[u].push_back(v);
        m_NumEdges++;
    }

    void Graph::depthFirstSearch(index_t cur, std::vector<int>& visited) {
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
        for (index_t i = m_NumNodes - 1; i >= 0; i--) { // this has been done in reverse so that if sub->C and B->A is defined in this order, then sub->C is executed first
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

    void Graph::tillIndex(index_t index) {
        while (m_AdjacencyList.size() < index) {
            m_AdjacencyList.emplace_back();
        }
    }

    void buildGraph(const FileSystem& fileSystem, const BuildFile& buildFile, Graph& graph) {
    	std::vector<int8_t> state(fileSystem.size(), 0);
    	int numRequiredButNotPresent = 0;
    	std::unordered_set<Graph::index_t> requiredButNotPresent;
        for (const BuildRule& rule : buildFile.getRules()) {
            Graph::index_t outputIndex = fileSystem.index(rule.getOutputTarget());
	        if (state[outputIndex] == 1) {
            	numRequiredButNotPresent--;
            	requiredButNotPresent.erase(outputIndex);
            }
            state[outputIndex] = 2; // it is present
            for (const std::string& inputTarget : rule.getInputTargets()) {
            	Graph::index_t inputIndex = fileSystem.index(inputTarget);
            	if (state[inputIndex] == 0 && !fileSystem.getReference(inputIndex)->exists()) {
            		state[inputIndex] = 1;
            		numRequiredButNotPresent++;
            		requiredButNotPresent.insert(inputIndex);
            	}
                graph.addEdge(inputIndex, outputIndex);
            }
        }
        if (requiredButNotPresent.size()) {
        	RAISE_ERROR_AND_EXIT("Dependency " + fileSystem.name(*requiredButNotPresent.begin()) + " does not exist and has no build rule", -1);
        }
    }

//    void buildDependencyTogether(const BuildFile &buildFile, FileSystem &fileSystem, Graph &graph) {
//        for (const BuildRule& rule : buildFile.getRules()) {
//            const std::string& output = rule.getOutputTarget();
//            fileSystem.addFile(output);
//            graph.tillIndex(fileSystem.index(output));
//            for (const std::string& input : rule.getInputTargets()) {
//                fileSystem.addFile(input);
//                graph.tillIndex(fileSystem.index(input));
//                graph.addEdgeIncremental(fileSystem.index(input), fileSystem.index(output));
//            }
//        }
//    }
 
}
