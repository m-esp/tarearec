#include "io/io.hpp"
#include "graph.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

void displayMenu() {
    std::cout << "\n--- Menú de Opciones ---" << std::endl;
    std::cout << "1. loadGraph <archivo>: Cargar un grafo desde un archivo." << std::endl;
    std::cout << "2. dijkstra <inicio> <fin>: Calcular el camino más corto entre dos vértices." << std::endl;
    std::cout << "3. showGraph: Mostrar la lista de adyacencia del grafo cargado." << std::endl;
    std::cout << "4. exportPath <archivo>: Guardar el resultado del último cálculo en un archivo." << std::endl;
    std::cout << "5. clearGraph: Reiniciar el grafo cargado." << std::endl;
    std::cout << "6. exit: Salir del programa." << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
}

void showGraph(const io::AdjacencyList &graph) {
    std::cout << "Lista de Adyacencia del Grafo:" << std::endl;
    for (int i = 0; i < graph.size(); ++i) {
        std::cout << "Vértice " << i + 1 << ": ";
        for (const auto &neighbor : graph[i]) {
            std::cout << "(" << neighbor.first + 1 << ", " << neighbor.second << ") ";
        }
        std::cout << std::endl;
    }
}

void exportPath(const DijkstraResult &result, const std::string &filename) {
    if (result.totalCost == -1) {
        std::cout << "No hay un resultado válido para exportar." << std::endl;
        return;
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error al abrir el archivo para escribir: " << filename << std::endl;
        return;
    }

    file << "Camino más corto: ";
    for (int v : result.path) {
        file << (v + 1) << " ";
    }
    file << "\nCosto total: " << result.totalCost << std::endl;

    file.close();
    std::cout << "Resultado exportado exitosamente al archivo: " << filename << std::endl;
}

int main() {
    io::AdjacencyList graph;
    int numVertices = 0;
    bool graphLoaded = false;
    DijkstraResult lastResult = {{}, -1};

    std::string command;
    while (true) {
        displayMenu();
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command.rfind("loadGraph", 0) == 0) {
            std::string filename = command.substr(10);
            if (filename.empty()) {
                std::cout << "Error: Debes especificar el nombre del archivo." << std::endl;
                continue;
            }

            graph = io::loadGraph(filename, numVertices);
            if (!graph.empty()) {
                graphLoaded = true;
                lastResult = {{}, -1}; // Reiniciar el último resultado
                std::cout << "Grafo cargado exitosamente. Número de vértices: " << numVertices << "." << std::endl;
            } else {
                std::cout << "Error al cargar el grafo. Verifica el archivo." << std::endl;
            }
        } else if (command == "showGraph") {
            if (!graphLoaded) {
                std::cout << "Primero debes cargar un grafo con 'loadGraph'." << std::endl;
            } else {
                showGraph(graph);
            }
        } else if (command.rfind("dijkstra", 0) == 0) {
            if (!graphLoaded) {
                std::cout << "Primero debes cargar un grafo con 'loadGraph'." << std::endl;
                continue;
            }

            std::istringstream iss(command.substr(9));
            int start, end;
            if (!(iss >> start >> end)) {
                std::cout << "Error: Formato incorrecto. Usa 'dijkstra <inicio> <fin>'." << std::endl;
                continue;
            }

            if (start < 1 || start > numVertices || end < 1 || end > numVertices) {
                std::cout << "Error: Los vértices deben estar entre 1 y " << numVertices << "." << std::endl;
                continue;
            }

            lastResult = dijkstra(graph, start - 1, end - 1);

            if (lastResult.totalCost != -1) {
                std::cout << "Camino más corto: ";
                for (int v : lastResult.path) {
                    std::cout << (v + 1) << " ";
                }
                std::cout << "\nCosto total: " << lastResult.totalCost << "." << std::endl;
            } else {
                std::cout << "No hay camino entre los vértices " << start << " y " << end << "." << std::endl;
            }
        } else if (command.rfind("exportPath", 0) == 0) {
            std::string filename = command.substr(11);
            if (filename.empty()) {
                std::cout << "Error: Debes especificar el nombre del archivo." << std::endl;
            } else {
                exportPath(lastResult, filename);
            }
        } else if (command == "clearGraph") {
            if (graphLoaded) {
                graph.clear();
                numVertices = 0;
                graphLoaded = false;
                lastResult = {{}, -1};
                std::cout << "Grafo reiniciado exitosamente." << std::endl;
            } else {
                std::cout << "No hay un grafo cargado para reiniciar." << std::endl;
            }
        } else if (command == "exit") {
            std::cout << "Saliendo del programa. ¡Hasta luego!" << std::endl;
            break;
        } else {
            std::cout << "Comando no reconocido. Intenta de nuevo." << std::endl;
        }
    }

    return 0;
}
