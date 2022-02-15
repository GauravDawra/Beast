#pragma once

#include <map>
#include <vector>
#include "variable_type.h"
#include <iostream>
#include <set>
#include "Logger.h"

namespace Beast {

    class SymbolTable {
    public:
        using iterator = typename std::map<std::string, MULTI_TYPE>::const_iterator;
        MULTI_TYPE get(const std::string& key) const;
        void set(const std::string& key, const MULTI_TYPE& value);
        bool exists(const std::string& key) const;
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
        // BuildRule() = delete;
        inline void setDependencies(const std::string& output, const std::vector<std::string>& inputs) {
            m_OutputTarget = output;
            m_InputTargets = inputs;
        }
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
        void resolveCommands(const SymbolTable& baseTable);
    private:
        std::string m_OutputTarget;
        std::vector<std::string> m_InputTargets;
        std::vector<std::string> m_Commands;
    };
    
    class BuildFile : public SymbolTable {
    public:
        BuildFile();
	    void addBuildRule(const BuildRule& rule);
	    void resolveBuildRules();
	    inline const std::vector<BuildRule>& getRules() const {
            return m_BuildRules;
        }
	    const BuildRule* getRule(const std::string& output) const;
    private:
        std::vector<BuildRule> m_BuildRules;
        std::map<std::string, int> m_Index;
        // std::vector<int> m_Index;
        // std::set<std::string> m_FileNames;
    };

    // class Function {
    // public:
        
    // private:
    //     SymbolTable m_LocalVariables;
    //     std::vector<Command> m_Commands;
    // };

}