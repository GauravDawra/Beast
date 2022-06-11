#include "Error.h"
#include "Memory.h"
#include "Shell.h"
#include "DepFileParser.h"

namespace Beast {

	SymbolTable::SymbolTable() {
		
	}

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
	
	void SymbolTable::resolve(std::string &name, const SymbolTable& baseTable) const {
		static char DEREF_CHAR = '$'; // character used for dereferencing in commands
		std::string ans;
		for(int i=0;i<name.length();i++) {
			if(name[i] == DEREF_CHAR) {
				if(i + 1 == name.length()) break;
				if (name[i+1] == '(') {
					int j = i;
					while(j < name.length() and name[j] != ')')
						j++;
					if (j == name.length()){
						RAISE_ERROR_AND_EXIT("irregular dereference in name - " + name, -1);
					}
					std::string variable = name.substr(i+2, j-(i+2));
					if(exists(variable)) {
						ans += toString(get(variable));
					} else if(baseTable.exists(variable)) {
						ans += toString(baseTable.get(variable));
					} else {
						ans += name.substr(i, j-i+1); // let it be in the dereference form
					}
					i = j;
				}
				else { // single letter dereference
					std::string variable = std::string(1, name[i+1]);
					if(exists(variable)) {
						ans += toString(get(variable));
					} else if(baseTable.exists(variable)) {
						ans += toString(baseTable.get(variable));
					} else { // if symbol not found
						ans += DEREF_CHAR;
						ans += variable; // adding name[i+1]
					}
					i++;
				}
			}
			else { // if not a dereference
				ans += name[i];
			}
		}
		name = ans;
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
    
	void BuildRule::resolveDepFile() {
		if (exists("dep")) {

			std::vector<std::string> depFiles;
			if(parseDepFile(toString(get("dep")), m_OutputTarget, depFiles)) {
				for (const auto& file : depFiles) {
					if (file.length()) {
						m_InputTargets.push_back(file);
					}
				}
			}
			
		}
	}
	
	void BuildRule::resolveCommands(const SymbolTable &baseTable) {
    	for (std::string& command : m_Commands) {
		    resolve(command, baseTable);
	    }
	}
	
	std::string BuildRule::build(int &exitStatus) const {
		std::string output = executeCommands(m_Commands, exitStatus);
		m_Built = true;
		return output;
	}
	
//	void BuildRule::resolveCommand(const SymbolTable& baseTable, std::string& command) {
//		static char DEREF_CHAR = '$'; // character used for dereferencing in commands
//		std::string ans;
//		for(int i=0;i<command.length();i++) {
//			if(command[i] == DEREF_CHAR) {
//				if(i + 1 == command.length()) break;
//				if (command[i+1] == '(') {
//					int j = i;
//					while(j < command.length() and command[j] != ')')
//						j++;
//					if (j == command.length()){
//						RAISE_ERROR_AND_EXIT("irregular dereference in name - " + command, -1);
//					}
//					std::string variable = command.substr(i+2, j-(i+2));
//					if(exists(variable)) {
//						ans += toString(get(variable));
//					} else if(baseTable.exists(variable)) {
//						ans += toString(baseTable.get(variable));
//					} else {
//						ans += command.substr(i, j-i+1); // let it be in the dereference form
//					}
//					i = j;
//				}
//				else { // single letter dereference
//					std::string variable = std::string(1, command[i+1]);
//					if(exists(variable)) {
//						ans += toString(get(variable));
//					} else if(baseTable.exists(variable)) {
//						ans += toString(baseTable.get(variable));
//					} else { // if symbol not found
//						ans += DEREF_CHAR;
//						ans += variable; // adding name[i+1]
//					}
//					i++;
//				}
//			}
//			else { // if not a dereference
//				ans += command[i];
//			}
//		}
//		command = ans;
//    }
	
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
		// this function defines what protocol needs to be followed while
		// resolving Build rules, like adding dependencies given in .d files
		// resolving variable dereferences etc.

    	for(BuildRule& rule : m_BuildRules) {
		    rule.resolveDepFile();
		    rule.resolveCommands(*this);
    	}

    }
	
	BuildFile::index_t BuildFile::index(const std::string& output) const {
		auto index_iter = m_Index.find(output);
		if (index_iter != m_Index.end()) {
			return index_iter->second;
		}
		return -1;
	}
    
    BuildFile::constRuleRef BuildFile::getRule(const std::string& output) const {
        auto index_iter = m_Index.find(output);
        if (index_iter != m_Index.end()) {
            return &(m_BuildRules[index_iter->second]);
        }
        return nullptr;
    }
	
	BuildFile::constRuleRef BuildFile::getRule(const index_t& index) const {
		if (index >= 0 && index < m_BuildRules.size()) {
			return &(m_BuildRules[index]);
		}
		return nullptr;
	}
}