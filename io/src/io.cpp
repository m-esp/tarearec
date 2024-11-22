#include "io/io.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

namespace io {

    void readTextFile(const std::string &filename) {
        std::ifstream f_in(filename);
        char symbol = '\0';
        if (f_in.is_open()) {
            while (f_in.get(symbol)) {
                std::cout << symbol;
            }
            std::cout << std::endl;
        } else {
            std::cout << "Error al leer " << filename << std::endl;
        }
        f_in.close();
    }

    AdjacencyList loadGraph(const std::string &filename, int &numVertices) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error al abrir el archivo: " << filename << std::endl;
            return {};
        }

        AdjacencyList adjacencyList;
        std::string line;
        numVertices = 0;

        // Leer número de vértices
        if (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string key;
            int vertices;
            if (iss >> key >> vertices && key == "n_vertex:") {
                numVertices = vertices;
                adjacencyList.resize(numVertices); // Inicializar lista de adyacencia
            } else {
                std::cerr << "Formato incorrecto en la línea de número de vértices." << std::endl;
                return {};
            }
        }

        // Leer las aristas
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string key;
            int v1, v2, weight;
            if (iss >> key >> v1 >> v2 >> weight && key.find("edge_") == 0) {
                // Convertir a índice base 0
                v1 -= 1;
                v2 -= 1;
                if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices) {
                    adjacencyList[v1].emplace_back(v2, weight);
                    adjacencyList[v2].emplace_back(v1, weight); // Si el grafo es no dirigido
                } else {
                    std::cerr << "Índices de vértices fuera de rango: " << v1 << ", " << v2 << std::endl;
                }
            } else {
                std::cerr << "Formato incorrecto en la línea de arista: " << line << std::endl;
            }
        }

        file.close();
        return adjacencyList;
    }
}
