//
// Created by Gaurav Dawra on 10/06/22.
//

#include "DepFileParser.h"
#include <sstream>
#include <fstream>

namespace Beast {
	
	bool parseDepFile(const std::string& fileName, const std::string& targetName, std::vector<std::string>& inputFiles) {
		const int SPECULATED_TOKEN_LEN = 5;
		std::ifstream file(fileName);
		std::stringstream stream;
		stream << file.rdbuf();
		std::string content = stream.str();
		// file reading done till here
		int32_t tokNum = 0;
		bool inputStarted = false;
//		std::string curOutputToken = "";
		inputFiles.clear();
		std::vector<std::string> outputFiles;
		std::vector<std::string> *addTo = &outputFiles;

		for (size_t i = 0; i < content.length(); i++) {
			if (addTo->size() - 1 != tokNum) {
				addTo->emplace_back();
				addTo->back().reserve(SPECULATED_TOKEN_LEN);
			}
			
			if (content[i] == '\\' && i + 1 < content.length()) {
				if (content[i + 1] == '\n') {
					i++;
				}
				else if (content[i + 1] == ' ') {
					addTo->back() += ' ';
					i++;
				} else {
					addTo->back() += '\\';
				}
			} else if (content[i] == ' ' || content[i] == '\n' || content[i] == '\t') {
				char toIgnore = content[i];
				while (i < content.length() && content[i] == toIgnore) i++;
				i--;
				tokNum++;
			} else if (!inputStarted && content[i] == ':') {
				inputStarted = true;
				tokNum = 0;
				addTo = &inputFiles;
			} else {
				addTo->back() += content[i];
			}
		
		}

		for (const std::string& output : outputFiles) {
			if (targetName == output) return true;
		}
		return false;
	}
	
}