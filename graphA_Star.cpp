#include "graphA_Star.h"

//Inicializa as estruturas que serão usadas
//Pre-condicao: id do vértice inicial
//Pos-condicao: A_STAR inicializado
void graphA_Star::initASTAR(string id_ini){
	auxA_Star aux;

	//Zera variavel auxiliar
	aux.id_pai = "";
	aux.is_infinity = true;
	aux.is_start = false;
	aux.id_edge = -1;

	//Atribui a todos os elementos no mapa
	for(map<string,node>::iterator it = this->myGraph->getMap()->begin(); it != this->myGraph->getMap()->end(); ++it){
		A_STAR[it->first]  = aux;
	}

	//Inicializa o vértice inicial
	aux.distancia_acumulada = 0;
	aux.is_infinity = false;
	aux.is_start = true;
	A_STAR[id_ini] = aux;
};

//Condição para executar o relax
//Pre-condicao: id vertice 1, id vertice 2, peso da conexão
//Pos-condicao: se o relax pode ser executado
bool graphA_Star::relax_validation(string id_ini, string id_dest, int weight){
	return (A_STAR.at(id_dest).is_infinity) || (A_STAR.at(id_dest).distancia_acumulada > A_STAR.at(id_ini).distancia_acumulada + weight);
}

//Executa o relax, atualizando a distância acumulado dos mesmos
//Pre-condicao: id vertice 1, id vertice 2, id da aresta
//Pos-condicao: relax
void graphA_Star::relax(string id_ini, string id_dest, int id_path){

	//Obtém todos os vizinhos do id_ini
	list <path> *edge_list = this->myGraph->getNeighbors(id_ini);

	for(list<path>::iterator it = edge_list->begin(); it != edge_list->end(); ++it){
		//Busca pelo informado
		if(it->my_id == id_path){
			//Se possível, realiza o relax
			if( relax_validation(id_ini, id_dest, it->weight) ){
				A_STAR.at(id_dest).id_pai = id_ini;
				A_STAR.at(id_dest).id_edge = id_path;
				A_STAR.at(id_dest).distancia_acumulada = A_STAR.at(id_ini).distancia_acumulada + it->weight;
				A_STAR.at(id_dest).is_infinity = false;
			}
		}
	}
}

//Procura o vértice não explorado com a menor distancia_acumulada
//Pre-condicao: 
//Pos-condicao: id do vértice buscado
string graphA_Star::naoExploradoComMenorHeuristica(){

	bool isFirst = true;
	string pos = "";
	int lower;
	int fx;

	//Itera no mapa

	cout << "\nFronteira: [";
	for(map<string,auxA_Star>::iterator it = this->A_STAR.begin(); it != this->A_STAR.end(); ++it){

		if(it->second.is_explorado == false && it->second.id_pai != "" && myGraph->getHeuristicMap()->count(it->first) != 0){
			cout << (isFirst?"":",") << "{" << it->first <<","<< it->second.distancia_acumulada + myGraph->getHeuristicMap()->at(it->first) << "}";
			if(isFirst){
				pos = it->first;
				// Antes da correção
				// lower = it->second.distancia_acumulada;
				lower = it->second.distancia_acumulada + myGraph->getHeuristicMap()->at(it->first);
				isFirst = false;
			}
			else{
				fx = it->second.distancia_acumulada + myGraph->getHeuristicMap()->at(it->first);
				if( fx <= lower ){
					pos = it->first;
					lower = fx;
				}
			}
		}
	}
	cout << "]" << endl;

	return pos;
}

//Construtor
//Pre-condicao: Grafo original 
//Pos-condicao: myGraph inicializado
graphA_Star::graphA_Star(graph *graph_map){
	this->myGraph = graph_map;
};

//Verifica se o algoritmo pode ser executado
//Pre-condicao:
//Pos-condicao: is_valid atualizado
bool graphA_Star::validate(){
	//Obtem todos as arestas
	list <path> *edge_list = this->myGraph->getAllNeighbors();

	//Verifica se existe alguma negativa
	for(list<path>::iterator it = edge_list->begin(); it != edge_list->end(); ++it){
		if ( it->weight < 0 ) return false;
	}

	return true;
};

//Executa o algoritmo
//Pre-condicao: id que representa o vértice inicial
//Pos-condicao: A_STAR com os valores pós-execução do algoritmo
bool graphA_Star::run(){
	return graphA_Star::run(false);
}
bool graphA_Star::run(bool is_print){
	//Valida grafo
	is_valid = this->validate();
	if(is_valid){

		string node2Explore = myGraph->getInitialNode();

		//Inicializa
		this->initASTAR(node2Explore);

		//Enquanto encontrar um vértice não explorado com distância != infinito
		while(node2Explore != ""){
			visited_nodes++;

			if(is_print){
				cout << "f(x): ";
				if(myGraph->getHeuristicMap()->count(node2Explore) == 0)
					cout << setw(6) << std::left << "";
				else
					cout << setw(6) << std::left << (myGraph->getHeuristicMap()->at(node2Explore) + A_STAR.at(node2Explore).distancia_acumulada);

					cout << "\tVisitando: " << node2Explore << endl;

			} 

			//Se já esta no nó final, encerra a execução
			if(node2Explore == myGraph->getFinalNode()) break;
			//Seta como explorado e não infinito
			A_STAR.at(node2Explore).is_explorado = true;
			A_STAR.at(node2Explore).is_infinity = false;


			//Obtem lista de vizinho
			list <path> *edge_list = this->myGraph->getNeighbors(node2Explore);


			//Realiza relax em todos os vizinhos
			for(list<path>::iterator it = edge_list->begin(); it != edge_list->end(); ++it){
				relax(node2Explore,it->id_dest,it->my_id);
			}

			//Busca próximo vértice pra explorar
			node2Explore = naoExploradoComMenorHeuristica();
		}

	}

	return is_valid;
};

//Imprime a sequencia do nó inicial ao final
//Pré-condicao: Nó final
void graphA_Star::printAux(string id){
	if(id != ""){
		printAux(A_STAR.at(id).id_pai);
		if(A_STAR.at(id).id_pai == ""){
			cout << " (" << id << ")";
		}
		else{
			cout << " " << "---" << myGraph->getNeighbor(A_STAR.at(id).id_edge)->weight << "---> (" << id << ")";
		}
	}
}

//Imprime o resultado do algoritmo, seja como imagem png ou textualmente
//Pre-condicao: Se deseja gerar a imagem
//Pos-condicao: Visualização do resultado do algoritmo
void graphA_Star::print(){
	if(!is_valid){
		cout << "Grafo inválido, contém arrestas negativas" << endl;
		return;
	}

	//Imprime tabela resultante da execução do algoritmo
	cout << "******************************************* A Star *********************************************" << endl;

	cout << "\t";
	if(A_STAR.at(myGraph->getFinalNode()).id_pai != ""){
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

//Destrutor
//Pre-condicao:
//Pos-condicao: Instância deixa de existir
graphA_Star::~graphA_Star(){

};
