#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <string>
#include <list>
#include <map>
#include "utils.cpp"

using namespace std;

typedef struct {
	int my_id;
	string id_orig;
	string id_dest;
	int weight;
} path;

typedef struct {
	string my_id;
	list <path> neighbors;
} node;


class graph{

	private:
		//Mapa de nós
		map <string,node> graph_map;
		//Mapa de heuristicas
		map <string,int> heuristic_map;

		//Lista de arestas
		list <path> edge_list;

		//Informa se o grafo é orientado
		bool is_orientado = false;

		//Nó inicial
		string initial_node;
		//Nó final
		string final_node;

	public:
		//Construtor
		graph();

		//Destrutor
		~graph();

		//Insere um nó no grafo
		//Pré-condição: id do nó
		void insertNode(string my_id);

		//Retorna aresta de acordo com o id da mesma
		//Pré-condição: id da aresta
		//Pós-condição: aresta
		path *getNeighbor(int id);

		//Insere uma aresta para um nó vizinho
		//Pré-condição: Nó inicial, peso da aresta, nó final
		void insertNeighbor(string id_node, int weight, string id_neighbor);

		//Imprime todos os nós, suas arestas e heuristica até o nó final
		//Pós-condição: Nós, arestas e heuristicas impressas na tela
		void printNodes();

		//Le um arquivo de entrada
		//Pré-condição: Nome do arquivo
		//Pós-condição: Mapas heuristico, de nós e lista de aresta inicializadas
		bool readInput(string fileName);

		//Retorna mapa de nós
		//Pós-condição: mapa de nós
		map <string,node> * getMap();

		//Retorna mapa das heuristicas do grafo
		//Pós-condição: mapa heuristico
		map <string,int> * getHeuristicMap();

		//Retorna lista de todas as arestas de um nó
		//Pós-condição: lista de arestas
		list <path> * getNeighbors(string id);

		//Retorna lista de todas as arestas
		//Pós-condição: lista de arestas
		list <path> * getAllNeighbors();

		//Define se o grafo será orientado
		//Pré-condição: is_orientado
		void setIsOrientado(bool option);

		//Limpa mapas e lista de arestas
		//Pós-condição: Grafo vazio
		void clear();

		//Retorna se o nó é orientado
		//Pós-condição: is_orientado
		bool getIsOrientado();

		//Retorna o nó inicial
		//Pós-condição: Nó inicial
		string getInitialNode();

		//Retorna o nó final
		//Pós-condição: Nó final
		string getFinalNode();
};

#endif //GRAPH_H