#ifndef graphA_Star_H
#define graphA_Star_H

#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <map>
#include <set>
#include "graph.h"

using namespace std;

struct auxA_Star{
	string id_pai;

	//Id da aresta que leva até este vertice
	int id_edge;
	//Indica se é vértice inicial
	bool is_start;

	//Indica se um vértice já foi explorado
	bool is_explorado = false;

	//Distancia do vértice inicial até o atual
	int distancia_acumulada = 0;

	//Indica que um vértice tem peso infinito
	bool is_infinity;
};

class graphA_Star{
private:
	//Grafo original
	graph *myGraph;
	//Mapa de estruturas que representam os vertices, de acordo com a chave
	map <string,auxA_Star> A_STAR;

	//Nós visitados
	unsigned int visited_nodes = 0;

	//Indica se o algoritmo é valido para o grafo indicado
	bool is_valid;

	//Inicializa as estruturas que serão usadas
	//Pre-condicao: id do vértice inicial
	//Pos-condicao: A_STAR inicializado
	void initASTAR(string id_ini);

	//Condição para executar o relax
	//Pre-condicao: id vertice 1, id vertice 2, peso da conexão
	//Pos-condicao: se o relax pode ser executado
	bool relax_validation(string id_ini, string id_dest, int weight);

	//Executa o relax
	//Pre-condicao: id vertice 1, id vertice 2, id da aresta
	//Pos-condicao: relax
	void relax(string id_ini, string id_dest, int id_path);

	//Procura o vértice não explorado com a menor distancia
	//Pre-condicao: 
	//Pos-condicao: id do vértice buscado
	string naoExploradoComMenorHeuristica();

public:

	//Construtor
	//Pre-condicao: Grafo original 
	//Pos-condicao: myGraph inicializado
	graphA_Star(graph *graph_map);

	//Verifica se o algoritmo pode ser executado
	//Pre-condicao:
	//Pos-condicao: is_valid atualizado
	bool validate();

	//Executa o algoritmo
	//Pre-condicao: id que representa o vértice inicial
	//Pos-condicao: A_STAR com os valores pós-execução do algoritmo
	bool run(bool is_print);
	bool run();

	//Imprime a sequencia do nó inicial ao final
	//Pré-condicao: Nó final
	void printAux(string id);

	//Imprime o resultado do algoritmo, seja como imagem png ou textualmente
	//Pre-condicao: Se deseja gerar a imagem
	//Pos-condicao: Visualização do resultado do algoritmo
	void print();

	//Destrutor
	//Pre-condicao:
	//Pos-condicao: Instância deixa de existir
	~graphA_Star();
	
};

#endif //graphA_Star_H