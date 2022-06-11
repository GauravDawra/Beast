//
// Created by Gaurav Dawra on 23/12/21.
//

// in the future have to include something to detect if the
// same file has been given away with with multiple names

#include "Filesystem.h"
#include <chrono>

namespace Beast {
    File::File(const std::string& file) : m_Name(file), m_Path(file) {
        m_Exists = std::filesystem::exists(m_Path);
        calculateTimestamp();
    }

    void File::calculateTimestamp() {
        if (m_Exists) {
            auto writeTime = std::filesystem::last_write_time(m_Name);
//	        auto writeTime = std::chrono::time_point_cast<std::chrono::milliseconds>(std::filesystem::last_write_time(m_Name));
//		#ifdef __clang__
	        m_LastModified = std::time_t(std::chrono::duration_cast<std::chrono::seconds>(writeTime.time_since_epoch()).count()); // std::filesystem::_FilesystemClock::to_time_t(writeTime);
//			LOG_INFO(std::to_string(m_LastModified));
//		#elif __GNUC__
//	        m_LastModified = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(writeTime));
//		#else
//            RAISE_ERROR_AND_EXIT("Unsupported compiler", -1);
//		#endif
            // m_LastModified = decltype(writeTime)::clock::to_time_t(writeTime);
			// // different options to turn last_write_time into time_t
        }
        else {
            m_LastModified = 0; // assigning 0 timestamp if file is not found
        }
    }

    void File::refresh() {
        m_Exists = std::filesystem::exists(m_Path);
        calculateTimestamp();
    }

    FileSystem::FileSystem(int expectedSize) : m_Size(0) {
        if (expectedSize) {
            m_Files.reserve(expectedSize);
        }
    }
    FileSystem::FileSystem(const BuildFile &buildFile) : m_Size(0) {
    	// not for this constructor, this constructor needs to ensure that
    	// there is an identity mapping between buildFile's BuildRule's and
    	// FileSystem's File's
    	const std::vector<BuildRule>& rules = buildFile.getRules();
    	m_Files.reserve(rules.size());
    	for (BuildFile::index_t i = 0; i < rules.size(); i++) {
    		addFile(rules[i].getOutputTarget());
    	} // this will ensure identity mapping between BuildFile rules and FileSystem files
    	m_NumTargets = rules.size();
        for (BuildFile::index_t i = 0; i < rules.size(); i++) {
        	auto outStamp = getReference(i)->timeStamp();
            for (const std::string& input : rules[i].getInputTargets()) {
                auto inputIndex = addFile(input);
                if (getReference(inputIndex)->timeStamp() > outStamp) {
                	rules[i].setToBuild();
                }
            }
        }
    }
//    FileSystem::FileSystem(const BuildFile &buildFile, Graph& graph) : m_Size(0) {
//        for (const BuildRule& rule : buildFile.getRules()) {
//            const std::string& output = rule.getOutputTarget();
//            addFile(output);
//            graph.tillIndex(index(output));
//            for (const std::string& input : rule.getInputTargets()) {
//                addFile(input);
//                graph.tillIndex(index(input));
//                graph.addEdgeIncremental(index(input), index(output));
//            }
//        }
//    }
    FileSystem::index_t FileSystem::index(const std::string& fileName) const {
        auto it = m_Index.find(fileName);
        if (it != m_Index.end()) {
            return it -> second;
        }
        return -1;
    }
    
	std::string FileSystem::name(const index_t &index) const {
    	if (index >= 0 && index < m_Size) {
    		return m_Files[index]->name();
    	}
    	else {
    		return "";
    	}
    }
    
    FileSystem::index_t FileSystem::addFile(const std::string& fileName, index_t index) {
    	auto it = m_Index.find(fileName);
	    if (it == m_Index.end()) {
		    m_Index[fileName] = m_Size++;
		    m_Files.push_back(new File(fileName));
		    return m_Size - 1; // NOT THREAD SAFE
	    }
	    return it->second;
    }

    FileSystem::constFileRef FileSystem::getReference(const std::string &fileName) const {
        index_t curIndex = index(fileName);
        if (curIndex != -1) {
            return m_Files[curIndex];
        }
        return nullptr;
    }

    FileSystem::~FileSystem() {
        for (fileRef &ref : m_Files) {
            delete ref;
        }
    }

    FileSystem::fileRef FileSystem::getReference(index_t index) const {
        if (index >= 0 && index < m_Size) {
            return m_Files[index];
        }
        return nullptr;
    }
}