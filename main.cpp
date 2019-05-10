#include <iostream>
#include <iomanip>
#include <string>
#include "graph.h"
#include "graphProfundidade.h"
#include "graphA_Star.h"

using namespace std;

int main(int argc, char const *argv[]) {

	graph *myGraph = new graph;

	while (1){
		int op;

		system("clear");

		cout << "---------------------------------------" << endl;
		cout << "|" << setw(3) << std::right << 0 << "\t" << setw(30) << std::right << "Carregar grafo" << "|" << endl;
		cout << "|" << "-------------------------------------" << "|" <<endl;
		cout << "|" << setw(3) << std::right << 1 << "\t" << setw(30) << std::right << "Executar Profundidade com BT" << "|" << endl;
		cout << "|" << setw(3) << std::right << 2 << "\t" << setw(30) << std::right << "Executar A*" << "|" << endl;
		cout << "|" << "-------------------------------------" << "|" <<endl;
		cout << "|" << setw(3) << std::right << 3 << "\t" << setw(30) << std::right << "Imprime Nodes" << "|" << endl;
		cout << "|" << "-------------------------------------" << "|" <<endl;
		cout << "|" << setw(3) << std::right << -1 << "\t" << setw(30) << std::right << "Sair" << "|" << endl;
		cout << "---------------------------------------" << endl << endl;
		
		cout << "Selecione uma opcao: ";
		cin  >> op;

		if (op == 0){

			myGraph->clear();

			string input = "";
			cout << "Insira o nome do arquivo a ser lido:" << endl;
			cin  >> input;

			if(myGraph->readInput(input))
				cout << "Arquivo lido com sucesso!" << endl;
			else
				cout << "Falha na leitura do arquivo!" << endl;


		}
		else if (op == 1){

			//Busca em profundidade
			graphProfundidade *DFS = new graphProfundidade(myGraph);

			DFS->run(true);
			DFS->print();

			delete DFS;

		}
		else if (op == 2){

			// Busca A*
			graphA_Star *A = new graphA_Star(myGraph);

			A->run(true);
			A->print();

			delete A;

		}
		else if (op == 3){

			myGraph->printNodes();

		}

		cout << "<Pressione ENTER p/ continuar>" << endl;
		cin.get();
		cin.get();


		if(op == -1) break;

	};



	delete myGraph;

	return 0;
}