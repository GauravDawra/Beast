#pragma once

#include <map>
#include <vector>
#include "variable_type.h"
//#include <iostream>
#include <set>
#include "Logger.h"

namespace Beast {

    class SymbolTable {
    public:
        using iterator = typename std::map<std::string, MULTI_TYPE>::const_iterator;
        using DEFAULT_TABLE = SymbolTable();
        SymbolTable();
        MULTI_TYPE get(const std::string& key) const;
        void set(const std::string& key, const MULTI_TYPE& value);
        bool exists(const std::string& key) const;
        void resolve(std::string &name, const SymbolTable& baseTable) const;
        inline void clear() {
            m_LookupTree.clear();
        }
        inline int size() const {
            return m_LookupTree.size();
        }
        inline iterator begin() const {
            return m_LookupTree.begin();
        }
        inline iterator end() const {
            return m_LookupTree.end();
        }
    protected:
        void changeTable(const SymbolTable& table);
    private:
        std::map<std::string, MULTI_TYPE> m_LookupTree;
    };

    class Command {
    public:
        enum type {
            SHELL = 0, // shell command
            FUNCTION   // function call
        };
        Command(const type& t) {
            m_type = t;
        }
        inline type getType() {
            return m_type;
        }
    protected:
        type m_type;

    // private:
    //     std::string m_data;
    };

    class ShellCommand : public Command {
    public:
        ShellCommand(const std::string& comm);
    private:
        std::string m_Command;
    };

    class BuildRule : public SymbolTable {
    public:
        void addCommand(const std::string& command);
        void setDependencies(const std::string& output, const std::vector<std::string>& inputs);
        inline void setCommands(const std::vector<std::string>& commands) {
			LOG_DEBUG("setting commands for " + getOutputTarget());
            m_Commands = commands;
            LOG_DEBUG( "Number of commands in " + getOutputTarget() + ": " + std::to_string(m_Commands.size()));
        }
        
        inline void setTable(const SymbolTable& table) {
            changeTable(table);
        }

        inline std::string getOutputTarget() const {
            return m_OutputTarget;
        }
//        friend class BuildFile;
        inline const std::vector<std::string>& getInputTargets() const {
            return m_InputTargets;
        }
        inline const std::vector<std::string>& getCommands() const {
            return m_Commands;
        }
        inline bool isBuilt() const {
        	return m_Built;
        }
        inline void setToBuild() const {
        	m_ToBuild = true;
        }
        inline bool toBuild() const {
        	return m_ToBuild;
        }
        void resolveDepFile();
        void resolveCommands(const SymbolTable& baseTable);
//        std::string build(int &exitStatus) const;
	    void build(int &exitStatus) const;
    private:
	    std::string m_OutputTarget;
	    std::vector<std::string> m_InputTargets;
	    std::vector<std::string> m_Commands;
	    mutable bool m_Built = false;
	    mutable bool m_ToBuild = false;
    };
    
    class BuildFile : public SymbolTable {
    public:
    	using ruleRef      = BuildRule*;
    	using constRuleRef = const BuildRule*;
    	using index_t      = int32_t;
        BuildFile();
	    void addBuildRule(const BuildRule& rule);
	    void resolveBuildRules();
	    inline const std::vector<BuildRule>& getRules() const {
            return m_BuildRules;
        }
        
        index_t index(const std::string& output) const;
        constRuleRef getRule(const std::string& output) const;
        constRuleRef getRule(const index_t& index) const;
	    inline index_t numRules() const {
		    return m_BuildRules.size();
	    }
    private:
        std::vector<BuildRule> m_BuildRules;
        std::map<std::string, index_t> m_Index;
    };
}