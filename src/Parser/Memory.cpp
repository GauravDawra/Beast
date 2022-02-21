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
    
	bool SymbolTable::exists(const std::string& key) const {
        if(m_LookupTree.find(key) != m_LookupTree.end())
        	return true;
        return false;
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
    
	void BuildRule::setDependencies(const std::string &output, const std::vector<std::string> &inputs) {
		m_OutputTarget = output;
		m_InputTargets = inputs;
		set("out", output);
		for (int i = 1; i <= inputs.size(); i++) {
			set(std::to_string(i), inputs[i-1]);
		}
    }
    
	void BuildRule::resolveCommands(const SymbolTable &baseTable) {
    	static char DEREF_CHAR = '$'; // character used for dereferencing in commands
    	for (std::string& command : m_Commands) {
			std::string ans;
			for(int i=0;i<command.length();i++) {
				if(command[i] == DEREF_CHAR) {
					if(i + 1 == command.length()) break;
					if (command[i+1] == '(') {
						int j = i;
						while(j < command.length() and command[j] != ')')
							j++;
						if (j == command.length()){
							RAISE_ERROR_AND_EXIT("irregular dereference in command - " + command, -1);
						}
						std::string variable = command.substr(i+2, j-(i+2));
						if(exists(variable)) {
							ans += toString(get(variable));
						} else if(baseTable.exists(variable)) {
							ans += toString(baseTable.get(variable));
						} else {
							ans += command.substr(i, j-i+1); // let it be in the dereference form
						}
						i = j;
					}
					else { // single letter dereference
						std::string variable = std::string(1, command[i+1]);
						if(exists(variable)) {
							ans += toString(get(variable));
						} else if(baseTable.exists(variable)) {
							ans += toString(baseTable.get(variable));
						} else { // if symbol not found
							ans += DEREF_CHAR;
							ans += variable; // adding command[i+1]
						}
						i++;
					}
				}
				else { // if not a dereference
					ans += command[i];
				}
			}
			command = ans;
		}
	}
    
    BuildFile::BuildFile() {
        // initialize member variables and default global variables here
        set("$", "$"); // to allow escaping $ character
//        set("currentDir", ) // set currentDir later
    }

    void BuildFile::addBuildRule(const BuildRule& rule) {
        std::string output = rule.getOutputTarget();
        if (m_Index.find(output) == m_Index.end()) {
            m_Index[output] = m_Index.size();
            m_BuildRules.push_back(rule);
        }
        else {
        	// might change later to concatenate two buildRules like in Make
	        RAISE_ERROR_AND_EXIT("multiple build rules for " + output, -1);
        }
    }
	
	void BuildFile::resolveBuildRules() {
    	for(BuildRule& rule : m_BuildRules) {
    		rule.resolveCommands(*this);
    	}
    }
    
    const BuildRule* BuildFile::getRule(const std::string& output) const {
        auto index = m_Index.find(output);
        if (index != m_Index.end()) {
            return &m_BuildRules[index->second];
        }
        return nullptr;
    }
}