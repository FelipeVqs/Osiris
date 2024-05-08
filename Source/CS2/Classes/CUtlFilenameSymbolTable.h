#pragma once

#include <string>
#include <unordered_map>

namespace cs2 {

using FileNameHandle_t = std::string*;

struct CUtlFilenameSymbolTable {
    using String = std::string& (CUtlFilenameSymbolTable* thisptr, const FileNameHandle_t* handle, char* buf, int buflen);
    std::unordered_map<FileNameHandle_t, std::string> filenameTable;
};

} // namespace cs2
