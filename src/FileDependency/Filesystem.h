//
// Created by Gaurav Dawra on 23/12/21.
//

#ifndef BEAST_FILESYSTEM_H
#define BEAST_FILESYSTEM_H

#include <string>
#include <filesystem>
#include <map>
#include <vector>
#include "Memory.h"

namespace Beast {

    class File {
    public:
        File(const std::string& file);
        void calculateTimestamp();
        void refresh();
        inline std::string name() const {
            return m_Name;
        }
        inline time_t timeStamp() const {
            return m_LastModified;
        }
        inline bool exists() const {
            return m_Exists;
        }
    private:
        const std::string m_Name;
        const std::filesystem::path m_Path;
        bool m_Exists;
        time_t m_LastModified;
    };

    class FileSystem {
    public:
        using fileRef      = File*;
        using constFileRef = const File*;
        FileSystem(int expectedSize = 0);
        FileSystem(const BuildFile& buildFile);

//        FileSystem(const BuildFile &buildFile, Beast::Graph &graph);

        int index(const std::string& fileName) const;
        void addFile(const std::string& fileName);
        constFileRef getReference(const std::string& fileName) const;
        fileRef getReference(int index) const;
        inline int size() const {
            return m_Size;
        }
        ~FileSystem();
    private:
        int m_Size;
        std::map<std::string, int> m_Index;
        std::vector<fileRef> m_Files;
    };

}
#endif //BEAST_FILESYSTEM_H
