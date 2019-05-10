#ifndef GRAPHPROFUNDIDADE_H
#define GRAPHPROFUNDIDADE_H

#include <iostream>
#include <iomanip>
#include <time.h>
#include <string>
#include <list>
#include <map>
#include "graph.h"

using namespace std;

struct auxProfundidade{
	//0 == branco, 1 == cinza, 2 == preto
	int cor;
	
	string id_pai;

	//Id da aresta que leva até este vertice
	int id_edge;

	//Indica se é vértice inicial
	bool is_start;
	
};

class graphProfundidade{

private:
	//Grafo original
	graph *myGraph;
	//Mapa de estruturas que representam os vertices, de acordo com a chave
	map <string,auxProfundidade> DFS;

	//Nós visitados
	unsigned int visited_nodes = 0;

	//Converte o id da cor para a palavra
	//Pre-condicao: id da cor
	//Pos-condicao: string com o nome da cor
	string getCor(int idCor);

	//Faz a recursão de visitas ao vértice e seus vizinhos, atualizando seus timestamps e cores
	//Pre-condicao: id do vértice inicial
	//Pos-condicao: todas as visitas realizadas na arvore em questão
	bool visit(string id, bool is_print);

	//Inicializa as estruturas que serão usadas
	//Pos-condicao: DFS inicializado
	void initDFS();

public:

	//Construtor
	//Pre-condicao: Grafo original 
	//Pos-condicao: myGraph inicializado
	graphProfundidade(graph *graph_map);;

	//Executa o algoritmo
	//Pos-condicao: DFS com os valores pós-execução do algoritmo
	void run();
	void run(bool is_print);

	//Imprime a sequencia do nó inicial ao final
	//Pré-condicao: Nó final
	void printAux(string id);

	//Imprime o resultado do algoritmo
	//Pos-condicao: Visualização do resultado do algoritmo
	void print();

	//Destrutor
	//Pre-condicao:
	//Pos-condicao: Instância deixa de existir
	~graphProfundidade();;
	
};

#endif //GRAPHPROFUNDIDADE_H