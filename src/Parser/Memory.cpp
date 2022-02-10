#include "Error.h"
#include "Memory.h"

namespace Beast {

    MULTI_TYPE SymbolTable::get(const std::string& key) const {
        std::map<std::string, MULTI_TYPE>::const_iterator it = m_LookupTree.find(key);
        if (it == m_LookupTree.end()) return {"$" + key};
        return it->second;
    }

    void SymbolTable::set(const std::string& key, const MULTI_TYPE& value) {
        m_LookupTree[key] = value;
    }

    void SymbolTable::changeTable(const SymbolTable& table) {
        m_LookupTree = table.m_LookupTree;
    }

    ShellCommand::ShellCommand(const std::string& comm) :
        m_Command(comm), Command(Command::SHELL) {
            // blank for now
        }

    void BuildRule::addCommand(const std::string& command) {
        m_Commands.push_back(command);
    }

    BuildFile::BuildFile() {
        // initialize member variables and default global variables here
        set("$", {"$"});
        set("test", 1025);
    }

    void BuildFile::addBuildRule(const BuildRule& rule) {
        // std::cout << "Adding build Rule for : " << rule.getOutputTarget() << std::endl;
        std::string output = rule.getOutputTarget();
        if (m_Index.find(output) == m_Index.end()) {
            m_Index[output] = m_Index.size();
            m_BuildRules.push_back(rule);
        }
        else {
        	// might change later to concatenate two buildRules like in Make
	        RAISE_ERROR_AND_EXIT("multiple build rules for " + output, -1);
        }
        // std::cout << m_BuildRules.size() << std::endl;
        // m_FileNames.insert(rule.getOutputTarget());
        // for (const std::string& file : rule.m_InputTargets) {
        //     m_FileNames.insert(file);
        // }
    }
    const BuildRule* BuildFile::getRule(const std::string& output) const {
        auto index = m_Index.find(output);
        if (index != m_Index.end()) {
            return &m_BuildRules[index->second];
        }
        return nullptr;
    }

}