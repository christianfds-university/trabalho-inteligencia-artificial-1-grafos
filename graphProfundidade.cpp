#include "graphProfundidade.h"

//Converte o id da cor para a palavra
//Pre-condicao: id da cor
//Pos-condicao: string com o nome da cor
string graphProfundidade::getCor(int idCor){
	if(idCor == 0) return "Branco";
	else if(idCor == 1) return "Cinza";
	else if(idCor == 2) return "Preto";
}

//Faz a recursão de visitas ao vértice e seus vizinhos
//Pre-condicao: id do vértice inicial
//Pos-condicao: todas as visitas realizadas na arvore em questão
bool graphProfundidade::visit(string id, bool is_print){
	visited_nodes++;

	this->DFS[id].cor = 1;
	list<path> *vizinhos;

	if(is_print){
		cout << "Visitando: ";
		cout << id << endl;
	}

	if(id != myGraph->getFinalNode()){
		vizinhos = myGraph->getNeighbors(id);
		for(list<path>::iterator it = vizinhos->begin(); it != vizinhos->end(); ++it){

			if(this->DFS[it->id_dest].cor == 0){
				this->DFS[it->id_dest].id_pai = id;
				this->DFS[it->id_dest].id_edge = it->my_id;
				if(visit(it->id_dest, is_print)){
					return true;
				}
			}
		}
	}
	else{
		return true;
	}

	this->DFS[id].cor = 2;
	return false;
}

//Inicializa as estruturas que serão usadas
//Pos-condicao: DFS inicializado
void graphProfundidade::initDFS(){
	auxProfundidade emptyAux;

	//Zera struct auxiliar
	emptyAux.id_pai = "";
	emptyAux.is_start = false;
	emptyAux.cor = 0;

	//Inicializa DFS
	for (map<string,node>::iterator it = this->myGraph->getMap()->begin(); it != this->myGraph->getMap()->end(); ++it){
		DFS[it->first] = emptyAux;
	}

}

//Executa o algoritmo
//Pre-condicao: id que representa o vértice inicial
//Pos-condicao: DFS com os valores pós-execução do algoritmo
void graphProfundidade::run(){
	graphProfundidade::run(false);
}
void graphProfundidade::run(bool is_print){

	//Inicializa o DFS
	initDFS();

	//Define o vértice inicial
	DFS[myGraph->getInitialNode()].is_start = true;

	visit(myGraph->getInitialNode(), is_print);

	if(is_print) cout << endl;

}

//Imprime a sequencia do nó inicial ao final
//Pré-condicao: Nó final
void graphProfundidade::printAux(string id){
	if(id != ""){
		printAux(DFS.at(id).id_pai);
		if(DFS.at(id).id_pai == ""){
			cout << " (" << id << ")";
		}
		else{
			cout << " " << "---" << myGraph->getNeighbor(DFS.at(id).id_edge)->weight << "---> (" << id << ")";
		}
	}
}

//Imprime o resultado do algoritmo, seja como imagem png ou textualmente
//Pos-condicao: Visualização do resultado do algoritmo
void graphProfundidade::print(){
	cout << "******************************************Profundidade******************************************" << endl;

	cout << "\t";
	if(DFS.at(myGraph->getFinalNode()).id_pai != ""){
		printAux(myGraph->getFinalNode());
	}
	else{
		cout << "Não foi possível encontrar um caminho até o nó final";
	}
	cout << endl;
	cout << endl;

	cout << "Nós visitados: " << visited_nodes << endl;
	cout << "************************************************************************************************" << endl;
}

//Construtor
//Pre-condicao: Grafo original 
//Pos-condicao: myGraph inicializado
graphProfundidade::graphProfundidade(graph *graph_map){
	this->myGraph = graph_map;
};

//Destrutor
//Pre-condicao:
//Pos-condicao: Intância deixa de existir
graphProfundidade::~graphProfundidade(){
};
