#ifndef IO_IO_HPP
#define IO_IO_HPP
#include <iostream>
#include <vector>
#include <utility>
#include <string>

namespace io {
    using AdjacencyList = std::vector<std::vector<std::pair<int, int>>>;

    void readTextFile(const std::string &filename);
    AdjacencyList loadGraph(const std::string &filename, int &numVertices);
}

#endif
