#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include "graph.h"

//Construtor
graph::graph(){
};

//Destrutor
graph::~graph(){
	this->clear();
};

//Insere um nó no grafo
//Pré-condição: id do nó
void graph::insertNode(string my_id){
	this->graph_map[my_id].my_id = my_id;
}

//Retorna aresta de acordo com o id da mesma
//Pré-condição: id da aresta
//Pós-condição: aresta
path *graph::getNeighbor(int id){

	for(list<path>::iterator it = this->edge_list.begin(); it != this->edge_list.end(); ++it){
		if(it->my_id == id) return &(*it);
	}

	return NULL;
}

//Insere uma aresta para um nó vizinho
//Pré-condição: Nó inicial, peso da aresta, nó final
void graph::insertNeighbor(string id_node, int weight, string id_neighbor){
	path nPath;

	nPath.my_id = edge_list.size();
	nPath.id_orig = id_node;
	nPath.id_dest = id_neighbor;
	nPath.weight = weight;

	this->graph_map[id_node].neighbors.push_back(nPath);

	this->edge_list.push_back(nPath);

	if(! this->is_orientado){
		nPath.id_orig = id_neighbor;
		nPath.id_dest = id_node;
		this->graph_map[id_neighbor].neighbors.push_back(nPath);
	}
}

//Imprime todos os nós, suas arestas e heuristica até o nó final
//Pós-condição: Nós, arestas e heuristicas impressas na tela
void graph::printNodes(){
	for (map<string,node>::iterator it_map = this->graph_map.begin(); it_map != this->graph_map.end(); ++it_map){
		cout << "Nome: " << it_map->second.my_id << endl;
		cout << "Heuristica: " <<  heuristic_map.at(it_map->second.my_id) << endl;
		cout << "Vizinhos: " << endl;

		for (list<path>::iterator it_list = it_map->second.neighbors.begin(); it_list != it_map->second.neighbors.end(); ++it_list){
			cout << "\t" << "Destino: " << it_list->id_dest << endl << "\tPeso: " << it_list->weight << endl << endl;
		}

		cout << endl << endl;

	}
}

//Le um arquivo de entrada
//Pré-condição: Nome do arquivo
//Pós-condição: Mapas heuristico, de nós e lista de aresta inicializadas
bool graph::readInput(string fileName){

	try{
		this->clear();

		ifstream fin;

		fin.open(fileName,std::ifstream::in);

		//Verifica se o arquivo foi aberto
		if( fin.is_open() ) {
			string read_str;
			int pos_identificador;
			list <string> params;

			while( ! fin.eof() ) {
				//Percore todas as linhas do arquivo
				getline(fin,read_str);

				//Procura pelos identificadores '(' e ')'
				if((pos_identificador = read_str.find("(")) != string::npos && read_str.find(")") != string::npos) {

					//Obtem a tag que precede o '('
					string tag = read_str.substr(0,pos_identificador);

					//Lista de parametros
					params.clear();
					params = utils::tokenizeStr(read_str.substr( pos_identificador + 1, read_str.find(')') - pos_identificador - 1), ",");
					if ( tag == "inicial") {
						this->initial_node = params.front();
						utils::trim(this->initial_node);
						insertNode(params.front());
					}
					else if ( tag == "final") {
						this->final_node = params.front();
						utils::trim(this->final_node);
						insertNode(params.front());
					}
					else if ( tag == "caminho") {
						string n1 = params.front();
						params.pop_front();
						string n2 = params.front();
						params.pop_front();

						utils::trim(n1);
						utils::trim(n2);

						insertNode(n1);
						insertNode(n2);

						insertNeighbor(n1,stoi(params.front()),n2);
					}
					else if ( tag == "h") {
						string n1 = params.front();
						params.pop_front();
						string n2 = params.front();
						params.pop_front();

						utils::trim(n1);
						utils::trim(n2);

						if(n2 != this->final_node){
							cout << "\nHeuristica não apontando para o nó final" << endl;
							this->clear();
							return false;
						}

						heuristic_map[n1] = stoi(params.front());
					}
					
				}
			}

			fin.close();
			return true;
		}
		return false;
	}
	catch(exception& e){
		return false;
	}
}

//Retorna mapa de nós
//Pós-condição: mapa de nós
map <string,node> * graph::getMap(){
	return &this->graph_map;
}

//Retorna mapa das heuristicas do grafo
//Pós-condição: mapa heuristico
map <string,int> * graph::getHeuristicMap(){
	return &this->heuristic_map;
}

//Retorna lista de todas as arestas de um nó
//Pós-condição: lista de arestas
list <path> * graph::getNeighbors(string id){
	return &this->graph_map[id].neighbors;
}

//Retorna lista de todas as arestas
//Pós-condição: lista de arestas
list <path> * graph::getAllNeighbors(){
	return &this->edge_list;
}

//Define se o grafo será orientado
//Pré-condição: is_orientado
void graph::setIsOrientado(bool option){
	this->is_orientado = option;
}

//Limpa mapas e lista de arestas
//Pós-condição: Grafo vazio
void graph::clear(){
	for (map<string,node>::iterator it = this->graph_map.begin(); it != this->graph_map.end(); ++it){
		it->second.neighbors.clear();
	}
	this->graph_map.clear();
	this->heuristic_map.clear();
	this->edge_list.clear();
}

//Retorna se o nó é orientado
//Pós-condição: is_orientado
bool graph::getIsOrientado(){
	return is_orientado;
}

//Retorna o nó inicial
//Pós-condição: Nó inicial
string graph::getInitialNode(){
	return initial_node;
}

//Retorna o nó final
//Pós-condição: Nó final
string graph::getFinalNode(){
	return final_node;
}