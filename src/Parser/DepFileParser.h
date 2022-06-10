//
// Created by Gaurav Dawra on 10/06/22.
//

#ifndef BEAST_DEPFILEPARSER_H
#define BEAST_DEPFILEPARSER_H

#include <string>
#include <vector>

namespace Beast {
	bool parseDepFile(const std::string& file, const std::string& targetName, std::vector<std::string>& outputFiles);
}


#endif //BEAST_DEPFILEPARSER_H
