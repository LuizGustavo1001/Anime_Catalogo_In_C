#include <iostream>
#include <fstream>

using namespace std;

struct anime{
	int numeracao;
	string nomeAnime;
	int numEpisodios;
	int numTemporadas;
	int anoLancamento;
	int anoFinalizacao;
	string generoPrincipal;    
	string status;
};

class noh{
	friend class listaDupla;
	private: 
		noh* proximo;
		noh* anterior;
		anime informacoes;    


	public:
		noh(anime i);
};

noh::noh(anime i){
	proximo = NULL;
	anterior = NULL;
	informacoes = i; 

}

class listaDupla{
	private:
		noh* primeiro;
		noh* ultimo;
		int tamanhoLista;



	public:
		listaDupla();
		~listaDupla();
		bool listaVazia();
		
		void insereAnimeVazia(anime info);
		void insereAnimeInicio(anime info);
		void insereAnimeFim(anime info);
		void sobrescreveAnimePosicaoDesejada(int posicaoDesejada, anime dados);
		
		void removeAnimeInicio();
		void removeAnimeFim();
		void removeAnimePosicaoDesejada(int posicaoDesejada);
		void removeAnime(int opcao,int numeracaoDesejada, string nomeDesejado);
		
		void procuraAnimeNome(string nomeDesejado);
		void procuraAnimeStatus(int sD);
		void procuraAnimeAno(int opcao, int anoDesejado);
		
		void imprimeAnime(noh* aux);
		void imprimeCatalogoPorGenero(string generoDesejado);
		void imprimeCatalogo();
		void imprimeIntervaloCatalogo(int inicio, int fim);
		
		void preencherVetor(anime catalogo[]);
		
		void salvarArquivo();
		
		int menores(int opcao);
		int maiores(int opcao);
};

listaDupla::listaDupla(){
	primeiro = NULL;
	ultimo = NULL;
	tamanhoLista =0;

}

listaDupla::~listaDupla(){
	while(! listaVazia()){
		removeAnimeInicio();
	}
	tamanhoLista=0;
}

bool listaDupla::listaVazia(){
	return (tamanhoLista==0);
}


void listaDupla::insereAnimeVazia(anime info){
	noh* novoNoh = new noh(info);
	
	primeiro = novoNoh;
	ultimo = novoNoh;
	tamanhoLista++;
}

void listaDupla::insereAnimeInicio(anime info){
	if(listaVazia()){
		insereAnimeVazia(info);
		}else{
			noh* novoNoh = new noh(info);
			novoNoh -> proximo = primeiro;
			primeiro -> anterior =novoNoh;
			primeiro = novoNoh;
			tamanhoLista++;
		}
}

void listaDupla::insereAnimeFim(anime info){
	if(listaVazia()){
		insereAnimeVazia(info);
			}else{
			noh* novoNoh = new noh(info);
			
			novoNoh -> anterior = ultimo;
			ultimo -> proximo = novoNoh;
			ultimo = novoNoh;
			
			tamanhoLista++;
			}
}

void listaDupla::sobrescreveAnimePosicaoDesejada(int posicaoDesejada, anime dados){
		noh* aux = primeiro;
		
		while(aux->informacoes.numeracao != posicaoDesejada){
			aux = aux -> proximo;
			
			}
		aux->informacoes = dados;
	
	}

void listaDupla::removeAnimeInicio(){
	if(listaVazia()){
		cout << "Erro, impossivel remover em uma lista vazia\n";
		}else{
			if(tamanhoLista==1){
				primeiro = nullptr;
				ultimo = nullptr;
				tamanhoLista=0;

				}else{
					noh* aux= primeiro;
					primeiro = primeiro->proximo;
					primeiro->anterior = nullptr;

					delete aux;
					tamanhoLista--;

					}
			}
	}

void listaDupla::removeAnimeFim(){
	if(listaVazia()){
		cout << "Erro, impossivel remover em uma lista vazia\n";
	}else{
		if(tamanhoLista==1){//removendo na primeira posicao
			primeiro=nullptr;
			ultimo = nullptr;
			tamanhoLista=0;

			}else{
				noh* aux = ultimo;
				ultimo = ultimo -> anterior;
				ultimo -> proximo = nullptr;

				delete aux;
				tamanhoLista--;
				}
	}
}

void listaDupla::removeAnimePosicaoDesejada(int posicaoDesejada){
	if(listaVazia()){
		cout << "Erro: Catalogo vazio\nRetornando ao comeco do codigo\n";
		}else{
			noh* aux = primeiro;
			int posAux=0;
	
			while((posAux != posicaoDesejada)and(aux != nullptr)){
				aux = aux -> proximo;
				posAux++;
				}
			if(aux != nullptr){
				if(posicaoDesejada == 0){
					removeAnimeInicio();
					}else if(posicaoDesejada== tamanhoLista){
						removeAnimeFim();
						}else{
							aux= primeiro;
							posAux=0;
							while(posAux != posicaoDesejada){
								aux->anterior=aux;
								aux= aux -> proximo;
								posAux++;
								}
								aux->anterior->proximo=aux->proximo;
								ultimo->proximo=NULL;
								delete aux;
								tamanhoLista--;
							
							}
				}
			}
	}
	
void listaDupla::removeAnime(int opcao,int numeracaoDesejada, string nomeDesejado){
	noh* aux = primeiro;
	int posAux = 0;
	switch(opcao){
		case 1:{ // remove por nome
			
			while(aux != nullptr and aux->informacoes.nomeAnime != nomeDesejado){
				aux = aux -> proximo;
				posAux++;
				}
			if(aux == nullptr){
				cout << "Erro: anime com nome desejado nao encontrado no catalogo\nRetornando ao comeco do codigo\n";
				}else{
					imprimeAnime(aux);
					
					int respostaSalvarRemocaoNome;
					
					cout << "Deseja mesmo remover?\n";
					cout << "1)Sim\n2)Nao\n";
					cout << "Resposta(1 ou 2): ";
					
					cin >> respostaSalvarRemocaoNome;
					
					switch(respostaSalvarRemocaoNome){
						case 1:{//salvar
							removeAnimePosicaoDesejada(posAux);
							cout << "\nAnime removido com sucesso do catalogo\nRetornando ao comeco do codigo\n";
							salvarArquivo();
							break;
							}
						case 2:{//nao salvar
							cout << "Anime acima nao removido do catalogo\nRetornando ao comeco do codigo\n";
							break;
							}
						default:{
							cout << "Erro: resposta fora do intervalo, retornando ao comeco do codigo\n";
							break;
							}
						}
					}
			
			break;
			}
		case 2:{
			
			while(aux->informacoes.numeracao != numeracaoDesejada){
				aux = aux -> proximo;
				posAux++;
				}
			if(aux == nullptr){
				cout << "Erro: anime com nome desejado nao encontrado no catalogo\nRetornando ao comeco do codigo\n";
				}else{
					imprimeAnime(aux);
					
					int respostaSalvarRemocaoNome;
					
					cout << "Deseja mesmo remover?\n";
					cout << "1)Sim\n2)Nao\n";
					cout << "Resposta(1 ou 2): ";
					
					cin >> respostaSalvarRemocaoNome;
					
					switch(respostaSalvarRemocaoNome){
						case 1:{//salvar
							removeAnimePosicaoDesejada(posAux);
							cout << "\nAnime Removido com sucesso do catalogo\nRetornando ao comeco do codigo\n";
							salvarArquivo();
							break;
							}
						case 2:{//nao salvar
							cout << "Anime acima nao removido do catalogo\nRetornando ao comeco do codigo\n";
							break;
							}
						default:{
							cout << "Erro: resposta fora do intervalo, retornando ao comeco do codigo\n";
							break;
							}
						}
					}
			
			break;
			}
		}
	}

void listaDupla::imprimeCatalogo(){
	noh* aux= primeiro;
	while(aux != NULL){
		imprimeAnime(aux);
		aux = aux -> proximo;
	}
}

void listaDupla::imprimeAnime(noh* aux){
	cout << "[ ";
	cout << aux->informacoes.numeracao << "-> ";
	cout << "Nome: "<<aux->informacoes.nomeAnime << " / ";
	cout << "Temporadas: " << aux->informacoes.numTemporadas << " / ";
	cout << "Episodios: " << aux->informacoes.numEpisodios << " / ";
	cout << "Lancamento: " << aux->informacoes.anoLancamento << " / ";
	cout << "Finalizacao: " << aux->informacoes.anoFinalizacao << " / ";
	cout << "GeneroPrincipal: " << aux->informacoes.generoPrincipal << " / ";
	cout << "Status: " << aux->informacoes.status << " ]"<< endl;
	cout << endl;
}

void listaDupla::imprimeIntervaloCatalogo(int inicio, int fim){
	
	noh*auxInicio = primeiro;
	int posAuxInicio=0;
		
	noh* auxFim = primeiro;
	int posAuxFim=0;
	
	while(posAuxInicio != inicio){
		auxInicio = auxInicio -> proximo;
		posAuxInicio++;
		}
	
	while(posAuxFim != fim){
		auxFim = auxFim -> proximo;
		posAuxFim++;
		}
	
	while(auxInicio != auxFim){
		imprimeAnime(auxInicio);
		auxInicio = auxInicio -> proximo;
		}
}

void listaDupla::procuraAnimeNome(string nomeDesejado){
	noh* aux = primeiro;
	
	while(aux != nullptr and aux->informacoes.nomeAnime != nomeDesejado){
		aux = aux->proximo;
		}
	if(aux ==nullptr){
		cout << "\nErro: anime nao se encontra na lista, tente digitar de outra forma\n";
		}else{
			cout << "\nAnime encontrado na posicao " << aux->informacoes.numeracao << " do catalogo\n";
			imprimeAnime(aux); 
			}
}

void listaDupla::procuraAnimeStatus(int sD){
	string statusDesejado;
	if(sD == 1){// em andamento
		statusDesejado = "Em Andamento";
		}else{
			statusDesejado = "Finalizado";
			}
			
	noh* aux = primeiro;
	
	while(aux != nullptr){
		if(aux->informacoes.status == statusDesejado){
			imprimeAnime(aux);
			}
			aux = aux -> proximo;
		}
	}
	
void listaDupla::procuraAnimeAno(int opcao,int anoDesejado){
	noh* aux = primeiro;
	int qntd=0;
	switch(opcao){
		case 1:{ // ano de lancamento
			while(aux != nullptr){
				if(aux->informacoes.anoLancamento == anoDesejado){
					imprimeAnime(aux);
					qntd++;
					}
				aux = aux -> proximo;
				}
			if(qntd == 0){
				cout << "\nErro: Nenhum anime com o ano de lancamento desejado esta cadastrado no catalogo\nRetornando ao comeco do codigo\n";
				}
	
			break;
			}
		case 2:{//ano de finalizacao
			while(aux != nullptr){
				if(aux->informacoes.anoFinalizacao == anoDesejado){
					imprimeAnime(aux);
					qntd++;
					}
				aux = aux -> proximo;
				}
			if(qntd == 0){
				cout << "\nErro: Nenhum anime com o ano de lancamento desejado esta cadastrado no catalogo\nRetornando ao comeco do codigo\n";
				}
	
			break;
			}
		default:{
			cout << "\nErro: opcao fora do intervalo valido\n Retornando ao comeco do codigo\n";
			break;
			}
		}
	}

void listaDupla::imprimeCatalogoPorGenero(string generoDesejado){
	noh* aux = primeiro;
	int quantidade = 0;
	
	while(aux != nullptr){
		if(aux->informacoes.generoPrincipal == generoDesejado){
			imprimeAnime(aux);
			quantidade++;
			}
		aux = aux -> proximo;
		}
	if(quantidade == 0){
		cout << "\nErro: nenhum anime com o genero desejado foi encontrado na tabela, tente escrever de uma outra forma ou procurar outro genero\n";
		}
}

void listaDupla::preencherVetor( anime catalogo[]){
	noh* temp = primeiro;
	for(int i=0; i<tamanhoLista ; i++){
		catalogo[i] = temp->informacoes;
		temp = temp->proximo;
	}
}

int listaDupla::menores(int opcao){
	noh* aux= primeiro;
	int menor;
	
	switch(opcao){
		case 1:{//ano lancamento
			menor = aux->informacoes.anoLancamento;
			while(aux != nullptr){
				if(aux->informacoes.anoLancamento < menor){
					menor = aux->informacoes.anoLancamento;
					}
					aux = aux -> proximo;
				}
			break;
			}
		case 2:{//ano finalizacao
			menor = aux -> informacoes.anoFinalizacao;
			while(aux != nullptr){
				if((aux->informacoes.anoFinalizacao < menor) and (aux->informacoes.anoFinalizacao != 0)){
					menor = aux->informacoes.anoFinalizacao;
					}
				aux = aux -> proximo;
				}
			break;
			}
		case 3:{ // numero de temporadas
			menor = aux->informacoes.numTemporadas;
			while(aux != nullptr){
				if(aux->informacoes.numTemporadas < menor){
					menor = aux->informacoes.numTemporadas;
					}
				aux= aux->proximo;
				}
			}
			break;
		}
		return menor;
	}

int listaDupla::maiores(int opcao){
	noh* aux;
	int maior;
	
	switch(opcao){
		case 1:{//ano lancamento
			aux = primeiro;
			maior = aux->informacoes.anoLancamento;
			while(aux != nullptr){
				if(aux->informacoes.anoLancamento > maior){
					maior = aux->informacoes.anoLancamento;
					}
					aux = aux -> proximo;
				}
			break;
			}
		case 2:{//ano finalizacao
			aux = primeiro;
			maior = aux -> informacoes.anoFinalizacao;
			while(aux != nullptr){
				if(aux->informacoes.anoFinalizacao > maior){
					maior = aux -> informacoes.anoFinalizacao;
					}
				aux = aux -> proximo;
				}
			break;
			}
		case 3:{ // numero de temporadas
			aux = primeiro;
			maior = aux->informacoes.numTemporadas;
			while(aux != nullptr){
				if(aux->informacoes.numTemporadas > maior){
					maior = aux->informacoes.numTemporadas;
					}
				aux= aux->proximo;
				}
				break;
			}
		}
		return maior;
	}
	
void listaDupla::salvarArquivo(){
	noh* aux = primeiro;
	int contador=1;
	ofstream saida ("Catalogo.csv");
	
	saida << "# Numeracao Nome Número_Temporadas Número_Episódios Ano_Lançamento Ano_Finalização Gênero_Principal Status" << endl;
	saida << "OBS:(anoFinalizacao=0 sera quando o anime ainda nao estiver finalizado)" << endl;
	
	while(aux != nullptr){
		saida << contador << ";";
		saida << '"' << aux->informacoes.nomeAnime << '"' << ";";
		saida << aux->informacoes.numTemporadas << ";";
		saida << aux->informacoes.numEpisodios << ";";
		saida << aux->informacoes.anoLancamento << ";";
		saida << aux->informacoes.anoFinalizacao << ";";
		saida << '"' << aux->informacoes.generoPrincipal << '"' << ";";
		saida << '"' << aux->informacoes.status << '"';
		saida << endl;
		aux = aux -> proximo;
		contador++;
		}
	}

// Função para trocar dois elementos
void trocar(anime &a, anime &b);

// Partição do Quick Sort Nome
int particaoNome(anime vet[], int menor, int maior);

// Função Quick Sort Nome
void quickSortNome(anime vet[], int menor, int maior);

int particaoLancamentos(anime vet[], int menor, int maior);

// Função Quick Sort Nome
void quickSortLancamentos(anime vet[], int menor, int maior);

int particaoGenero(anime vet[], int menor, int maior);

// Função Quick Sort Nome
void quickSortGenero(anime vet[], int menor, int maior);

void mensagemErro();

void menu();


int main(){
	
listaDupla l1;
anime info;

int tamanho=0;

ifstream entrada ("Catalogo.csv");

if(entrada){
	string linha;
	// descartar as 2 linhas de introducao
	getline(entrada, linha);
	getline(entrada, linha);

	}else{
		cout << "\nErro: Nao foi possivel abrir o arquivo\n ";
		}

while(entrada){
	char delimitador1 = ';';
	char delimitador2 = '"';
	string lixo;

	entrada >> info.numeracao;
	entrada.ignore(1, delimitador1);
	getline(entrada, lixo , delimitador2);
	getline(entrada, info.nomeAnime, delimitador2);
	
	entrada.ignore(1, delimitador1);
	entrada >>info.numTemporadas;
	entrada.ignore(1, delimitador1);

	entrada >> info.numEpisodios;
	entrada.ignore(1, delimitador1);

	entrada >> info.anoLancamento;
	entrada.ignore(1, delimitador1);

	entrada >> info.anoFinalizacao;
	entrada.ignore(1, delimitador1);

	getline(entrada, lixo, delimitador2);
	getline(entrada, info.generoPrincipal , delimitador2);
	entrada.ignore(1, delimitador1);
	
	getline(entrada, lixo, delimitador2);
	getline(entrada, info.status , delimitador2);

	tamanho++;
	l1.insereAnimeFim(info);
	}
	l1.removeAnimeFim(); // erro
	
	int resposta;

	do{
		menu();
		cin >> resposta;

		switch(resposta){
			case 1:{//intervalo
				int respostaIntervalo;

				cout << "\n1)Alfabetica\n2)Ultimos lancamentos\n3)Genero\n4)Sem Filtro\n";
				cout << "Resposta(1, 2, 3 ou 4): ";

				cin >> respostaIntervalo;
				
				if(respostaIntervalo <= 0 or respostaIntervalo > 4){
					mensagemErro();
					}else{
						listaDupla listaAux;
						anime *vetorOrdenacao = new anime[tamanho];
				
						l1.preencherVetor(vetorOrdenacao);

						switch(respostaIntervalo){
							case 1:{ // Alfabetica
								quickSortNome(vetorOrdenacao, 0 , tamanho-2);
								for (int i = 0; i < tamanho-1; i++) {
									listaAux.insereAnimeFim(vetorOrdenacao[i]);
									}

								cout << "\nCatalogo ordenado por ordem alfabetica\n";

								break;
							}
							case 2:{ // ultimos lancamentos
								quickSortLancamentos(vetorOrdenacao, 0, tamanho-2);
								for(int i=0; i< tamanho-1 ; i++){
									listaAux.insereAnimeFim(vetorOrdenacao[i]);
									}

								cout << "\nCatalogo ordenado por ultimos lancamentos\n";

								break;
							}
							case 3:{ // genero
								quickSortGenero(vetorOrdenacao, 0, tamanho-2);
								for(int i=0; i<tamanho-1; i++){
									listaAux.insereAnimeFim(vetorOrdenacao[i]);
									}

								cout << "\nCatalogo ordenado por genero\n";

								break;
							}
							case 4:{ // Apenas imprimir
								int respostaIntervaloSemFiltro;
								cout << "\nCatalogo nao ordenado por escolha do usuario\n";
								cout << "1)\nTodo o catalogo sem filtro\n2)Intervalo do catalogo sem filtro\n";
								cout << "Resposta(1 ou 2): ";
								
								cin >> respostaIntervaloSemFiltro;
								
								switch(respostaIntervaloSemFiltro){
									case 1:{// todo o catalogo
										l1.imprimeCatalogo();
										break;
										}
									case 2:{//intervalo
										int c;
										int f;
										
										cout << "Intervalo(Minimo = 1 e Maximo = " << tamanho-1 << ")\n";
						
										cout << "Inicio: ";
										cin >> c;
						
										cout << "Fim: ";
										cin >> f;
										
										if((c < 0) or (c >= tamanho) or (f < c) or (f >= tamanho)){
											mensagemErro();
											}else{
												l1.imprimeIntervaloCatalogo(c-1, f);
												}
									
										break;
										}
									default:{
										mensagemErro();
										break;
										}
									}
								
								break;
							}
						delete[] vetorOrdenacao;
						}	
							if(respostaIntervalo != 4){
								int respostaImprimir;
				
								cout << "\n1)Imprimir todo o catalogo\n2)Imprimir um intervalo determinado\n";
								cout << "Resposta: ";
				
								cin >> respostaImprimir;
				
								switch(respostaImprimir){
									case 1:{
										listaAux.imprimeCatalogo();
										break;
									}
									case 2:{
										int comeco;
										int fim;
										cout << "Intervalo(Minimo = 1 e Maximo = " << tamanho-1 << ")\n";
						
										cout << "Inicio: ";
										cin >> comeco;
						
										cout << "Fim: ";
										cin >> fim;
						
										if((comeco < 0) or (comeco >= tamanho) or (fim < comeco) or (fim >= tamanho)){
											mensagemErro();
											}else if(comeco == fim){//imprimir somente 1 posicao
												listaAux.imprimeIntervaloCatalogo(comeco-1, fim);
												}else{
													listaAux.imprimeIntervaloCatalogo(comeco-1,fim);
													}
						
										break;
									}
									default:{
										mensagemErro();
										break;
										}
								}
								}
							}
							
				break;
			}
			case 2:{ // filtrar
				int respostaFiltrar;
				
				cout << "\n1)Nome\n2)Ano de Lancamento\n3)Ano de Finalizacao\n4)Genero\n5)Numero de Temporadas\n6)Status\n";
				cout << "Resposta(1, 2, 3, 4, 5 ou 6 ): "; 
				
				cin >> respostaFiltrar;
				
				switch(respostaFiltrar){
					case 1:{ //nome
						cout << "\nNome: ";
						cin.ignore();
						getline(cin, info.nomeAnime);
						l1.procuraAnimeNome(info.nomeAnime);
						
						break;
						}
					case 2:{//ano de lancamento
						cout << "\nAno de lancamento\n";
						int menorAnoLancamento = l1.menores(1);
						int maiorAnoLancamento = l1.maiores(1);
						
						cout << "Minimo = " << menorAnoLancamento << " Maior = " << maiorAnoLancamento << endl;
						cout << "Resposta: ";
						
						cin >> info.anoLancamento;
						
						if((info.anoLancamento <= maiorAnoLancamento)and (info.anoLancamento > 0)){
							l1.procuraAnimeAno(1,info.anoLancamento);
							}else{
								mensagemErro();
								}
						
						break;
						}
					case 3:{//ano de finalizacao
						cout << "\nAno de finalizacao:\n";
						int menorAnoFinalizacao = l1.menores(2);
						int maiorAnoFinalizacao = l1.maiores(2);
						cout << "(Minimo = (0 se em andamento) ou " << menorAnoFinalizacao << " | Maior = " << maiorAnoFinalizacao << ")"<< endl;
						cout << "Resposta: ";
						
						cin >> info.anoFinalizacao;
						
						if((info.anoFinalizacao <= maiorAnoFinalizacao) and(info.anoFinalizacao >=0)){
							l1.procuraAnimeAno(2,info.anoFinalizacao);
							}else{
								mensagemErro();
								}
						
						break;
						}
					case 4:{//genero
						cout << "\nGenero: ";
						
						cin.ignore();
						getline(cin,info.generoPrincipal);
						
						l1.imprimeCatalogoPorGenero(info.generoPrincipal);
						
						break;
						}
					case 5:{//numero de temporadas
						cout << "\nNumero de temporadas\n";
						int menorNumTemp = l1.menores(3);
						int maiorNumTemp = l1.maiores(3);
						cout << "Minimo = " << menorNumTemp << " Maior = " << maiorNumTemp << endl;
						
						break;
						}
					case 6:{//status
						cout << "\n1)Em Andamento\n2)Finalizado\n";
						cout << "Resposta(1 ou 2): ";
						int respostaStatus;
						cin >> respostaStatus;
						if(respostaStatus==1 or respostaStatus == 2){
							l1.procuraAnimeStatus(respostaStatus);
							}else{
									mensagemErro();
									}
						
						break;
						}
					default:{
						mensagemErro();
						break;
						}
					}
				break;
				}
			case 3:{ // escrever/sobrescrever
				int respostaMudanca;

				cout << "\n1)Escrever\n2)Sobrescrever\n";
				cout << "Resposta(1 ou 2): "; 

				cin >> respostaMudanca;

				switch(respostaMudanca){
					case 1:{
						int respostaEscrever;

						cout << "\nQuantos novos animes deseja escrever?\n";
						cout << "Resposta: ";

						cin >> respostaEscrever;


						if(respostaEscrever < 0){
							mensagemErro();
							}else{
								for(int i=0; i<respostaEscrever; i++){
									cout << "\nEscreva os dados do "<< i+1 <<"o anime(ate o momento da insercao): \n";;
									info.numeracao = tamanho+i+2;

									cout << "Nome:";
									cin.ignore();
									getline(cin, info.nomeAnime);

									cout <<"Temporadas: ";
									cin >> info.numTemporadas;

									cout << "Episodios: ";
									cin >> info.numEpisodios;

									cout << "Ano de Lancamento: ";
									cin >> info.anoLancamento;

									cout << "Ano de Finalizacao(=0 se Em Andamento): ";
									cin >> info.anoFinalizacao;

									cout << "Genero Principal: ";
									cin.ignore();
									getline(cin, info.generoPrincipal);
									
									if(info.anoFinalizacao == 0){
										info.status = "Em Andamento";
										}else{
											info.status = "Finalizado";
											}
											
									//cout << "Status(Em Andamento ou Finalizado): ";
									//getline(cin, info.status);

									int respostaAlteracoes;

									cout << "\nDeseja salvar as alteracoes?\n";
									cout << "1)Sim\n2)Nao\n";
									cout << "Resposta(1 ou 2): ";

									cin >> respostaAlteracoes;

									switch(respostaAlteracoes){
										case 1:{
										l1.insereAnimeFim(info);
										tamanho++;
										
										l1.salvarArquivo();
											cout << "Anime " << i+1 << " inserido\n";          
											break;
										}
									case 2:{
										cout << "\nResposta nao salva\n";
										break;
									}
										default:{
											mensagemErro();
											break;
										}
									}
									}
							}

							break;
					}  
					case 2:{//sobrescrever
						int posicaoDesejada;
							
						cout << "Qual posicao sera sobrescrevida?\n";
						cout << "Minimo = 1 | Maximo = " << tamanho-1 << endl;
						cout << "Resposta: ";
							
						cin >> posicaoDesejada;
						if((posicaoDesejada >= 1) and (posicaoDesejada < tamanho)){
							cout << "Insira os dados do anime(ate o momento da insercao):\n";
								
							info.numeracao = tamanho+2;

							cout << "Nome:";
							cin.ignore();
							getline(cin, info.nomeAnime);

							cout <<"Temporadas: ";
							cin >> info.numTemporadas;

							cout << "Episodios: ";
							cin >> info.numEpisodios;

							cout << "Ano de Lancamento: ";
							cin >> info.anoLancamento;

							cout << "Ano de Finalizacao(=0 se Em Andamento): ";
							cin >> info.anoFinalizacao;

							cout << "Genero Principal: ";
							cin.ignore();
							getline(cin, info.generoPrincipal);
									
							if(info.anoFinalizacao == 0){
								info.status = "Em Andamento";
								}else{
									info.status = "Finalizado";
									}
								
							int respostaSalvar;
								
							cout << "\nSalvar as alteracoes?\n";
							cout << "1)Sim\n2)Nao\n";
							cout << "Resposta(1 ou 2): ";
								
							cin >> respostaSalvar;
								
							if(respostaSalvar== 1){
								l1.sobrescreveAnimePosicaoDesejada(posicaoDesejada, info);
									
								l1.salvarArquivo();
								cout << "\nAnime sobrescrito na posicao " << posicaoDesejada << " do catalogo\n";
									
								}else if(respostaSalvar==2){
									cout << "\nResposta nao salva\nRetornando ao comeco do codigo\n";
									}else{
										mensagemErro();
										}
								}else{
									mensagemErro();
									}

							break;
					}
					default:{
						mensagemErro();
						break;
					}
				}
				break;
			}
			case 4:{ // remover
				int respostaRemover;
				
				cout << "Remover:\n";
				cout << "1)Nome\n2)Numeracao\n";
				cout << "Resposta(1 ou 2): ";
				
				cin >> respostaRemover;
				
				switch(respostaRemover){
					case 1:{// remover por nome
						cout << "Nome: ";
						cin.ignore();
						getline(cin, info.nomeAnime);
						info.numeracao = 1;
						
						l1.removeAnime(1,info.numeracao,info.nomeAnime);
						break;
						}
					case 2:{//remover por numeracao no catalogo
						cout << "Numeracao: ";
						cin >> info.numeracao;
						if((info.numeracao <= tamanho) and (info.numeracao > 0)){
							info.nomeAnime = "a";
							l1.removeAnime(2,info.numeracao, info.nomeAnime);
							}else{
								cout << "\nErro: numeracao fora do intervalo do catalogo, retornando ao comeco do codigo\n";
								}
						break;
						}
					default:{
						mensagemErro();
						break;
						}
					}
				break;
			}
			case 5:{ // encerrar
				cout << "\nPrograma Finalizado\n";
				break;
				}
			default:{
				mensagemErro();
				break;
			}
		} 
	}while(resposta!= 5);
	return 0;
}

void mensagemErro(){
	cout << "\nErro: resposta FORA do intervalo permitido\n";
	cout << "Retornando ao comeco do codigo\n";
}

void menu(){
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	cout << "|\n|				<CATALOGO DE ANIMES>\n";
	cout << "|\n|1) Mostrar um Intervalo de animes" << endl;
	cout << "|2) Buscar animes por algum filtro" << endl;
	cout << "|3) Escrever/Sobrescrever dados" << endl;
	cout << "|4) Remover Dados" << endl;
	cout << "|5) Encerrar o Programa\n|";
	cout << endl << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	cout << "-> Resposta (1 ate 5): ";
}


// Função para trocar dois elementos
void trocar(anime &a, anime &b){
	anime aux = a;
	a = b;
	b = aux;
}

// Partição do Quick Sort Nome
int particaoNome(anime vet[], int menor, int maior){
	string aux = vet[maior].nomeAnime;
	int i = menor - 1;
	for (int j = menor; j <= maior - 1; j++) {
		if (vet[j].nomeAnime < aux) {
			i++;
			trocar(vet[i], vet[j]);
			}
		}
		trocar(vet[i + 1], vet[maior]);
		return (i + 1);
}

// Função Quick Sort Nome
void quickSortNome(anime vet[], int menor, int maior){
	if (menor < maior){
		int pivo = particaoNome(vet, menor, maior);
		quickSortNome(vet, menor, pivo - 1);
		quickSortNome(vet, pivo + 1, maior);
		}
}

// Partição do Quick Sort Lancamentos
int particaoLancamentos(anime vet[], int menor, int maior){
	int aux = vet[maior].anoLancamento;
	int i = menor - 1;
	for (int j = menor; j <= maior - 1; j++) {
		if (vet[j].anoLancamento > aux){
			i++;
			trocar(vet[i], vet[j]);
			}
		}
		trocar(vet[i + 1], vet[maior]);
		return (i + 1);
}

// Função Quick Sort Lancamentos
void quickSortLancamentos(anime vet[], int menor, int maior){
	if (menor < maior){
		int pivo = particaoLancamentos(vet, menor, maior);
		quickSortLancamentos(vet, menor, pivo - 1);
		quickSortLancamentos(vet, pivo + 1, maior);
		}
}

// Partição do Quick Sort Genero
int particaoGenero(anime vet[], int menor, int maior){
	string aux = vet[maior].generoPrincipal;
	int i = menor - 1;
	for (int j = menor; j <= maior - 1; j++){
		if (vet[j].generoPrincipal < aux){
			i++;
			trocar(vet[i], vet[j]);
			}
		}
		trocar(vet[i + 1], vet[maior]);
		return (i + 1);
}

// Função Quick Sort Genero
void quickSortGenero(anime vet[], int menor, int maior){
	if (menor < maior){
		int pivo = particaoGenero(vet, menor, maior);
		quickSortGenero(vet, menor, pivo - 1);
		quickSortGenero(vet, pivo + 1, maior);
		}
}
