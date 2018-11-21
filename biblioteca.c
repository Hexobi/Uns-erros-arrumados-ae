#include "biblioteca.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

void interfaceUsuario() {
	EstruturaPessoa* lista = NULL;
	char menu;
	int submenu;
	do {
		printf("\nDigite qual a opcao desejada");
		printf("\nA-Inserir cliente");
		printf("\nB-Excluir cliente");
		printf("\nC-Relatorios");
		printf("\nD-Finalizar\n");
		scanf("%c", &menu);
		fflush(stdin);
		switch (menu) {
		case 'A':
			lista = cadastroPessoa(&lista);
			break;
		case 'B':
			puts("\nQual Deseja Excluir?");
			puts("\n1- Exclusao de cliente");
			puts("\n2- Exclusao de placa\n");
			scanf("%d", &submenu);
			fflush(stdin);
			switch (submenu) {
			case 1:
				break;
			case 2:
				break;
			default:
				printf("\nInvalido");
				break;
			}
			break;
			case 'C':
				puts("\nQual Deseja Exibir?");
				puts("\n1- Listar todos os clientes");
				puts("\n2- Listar dados do cliente");
				puts("\n3- Listar clientes por contrato\n");
				scanf("%d", &submenu);
				fflush(stdin);
				switch (submenu) {
				case 1:
					imprimirTudo(lista);
					break;
				case 2:
					puts("Digite o codigo do cliente: \n");
					int codigo = 0;
					scanf("%d", &codigo);
					fflush(stdin);
					procurarPessoaPorCodigo(lista, codigo);
					break;
				case 3:
					break;
				default:
					puts("digite somete uma das opcoes");
					break;
				}
				break;
				case 'D':
					break;
				default:
					printf("\nInvalido");
					break;
		}

	} while (menu != 'D');
}

int VerificaSeEhNumero(char c) {
	if ((c <= 57 && c >= 48)) {
		return 1;
	} else
		return 0;
}
int VerificaSeEhLetra(char c) {
	if ((c <= 90 && c >= 65) || (c >= 97 && c <= 122)) {
		return 1;
	} else
		return 0;
}
int verificarData(char data[]) {

	int idade, dia, mes, ano;
	time_t now;
	time(&now);
	struct tm *tm = localtime(&now);
	// 01/34/6789
	if (data[2] == '/' && data[5] == '/') {
		//char* tmp = (char*) malloc(4 * sizeof(char));

		dia = concatINT(data, 0, 1); //(char[], INICIO,FIM)

		mes = concatINT(data, 3, 4);

		ano = concatINT(data, 6, 9);

		idade = (tm->tm_year + 1900) - (ano);

		if (tm->tm_mon < mes) {
			idade--;
		} else if (mes == tm->tm_mon && tm->tm_mday < dia) {
			idade--;
		}
		printf("idade atual %d", idade);
	}
	return idade;
}
int concatINT(char s[], int inicio, int fim) {
	int r = 0;
	int cont = 1;
	int i;
	int total = fim - inicio;
	cont = pow(10, total);
	for (i = inicio; i <= fim; i++) {
		int c = (s[i] - '0'); //converte o char em numero inteiro
		c *= cont;
		r += c;
		cont /= 10;
	}
	return r;
}

void cadastroCarro(EstruturaPessoa **lista) {

	EstruturaCarro *novo = (EstruturaCarro*) malloc(sizeof(EstruturaCarro));
	int x = 0;
	int errado = 1;
	while (errado) {
		puts("Digite a Placa do carro: ");
		fflush(stdin);
		gets(novo->placa);
		errado = consistePlaca(novo->placa);
		if (errado) {
			ERRO_ENTRADA;
		}
	}
	errado = 1;
	while (errado) {
		puts("Digite o ano do carro");
		scanf("%d", &novo->ano);
		fflush(stdin);
		errado = (novo->ano < 1950 && novo->ano > 2018);

		if (errado)
			ERRO_ENTRADA;

	}
	puts("Digite o modelo do carro");
	gets(novo->modelo);
	fflush(stdin);

	if ((*lista)->dadosDosCarros == NULL) {
		puts("Lista vazia");
		novo->anterior = NULL;

		x = concatINT(novo->placa, 3, 6);
		x = CODIGO(x);
		novo->codigo = CODIGO(x);

		(*lista)->dadosDosCarros = novo;
		(*lista)->codigo = x;

	} else {
		novo->anterior = (*lista)->dadosDosCarros;
		int tmp = (*lista)->dadosDosCarros->codigo;
		novo->codigo = tmp++;
		(*lista)->dadosDosCarros = novo;
	}

	puts("Carro cadastrado com sucesso");
}

EstruturaPessoa* cadastroPessoa(EstruturaPessoa **lista) {
	EstruturaPessoa *novo = (EstruturaPessoa*) malloc(sizeof(EstruturaPessoa));
	novo->dadosDosCarros = NULL;
	int idade = 0;
	do {
		printf("\nDigite seu nome\n");
		gets(novo->nome);
		if (strcmp(novo->nome, "\0") == 0) {
			puts("\nNome invalido");
		}
	} while (strcmp(novo->nome, "\0") == 0);
	do {
		puts("\nDigite sua data de nascimento DD/MM/AAAA\n");
		gets(novo->dataNasc);
		idade = verificarData(novo->dataNasc);

		if (idade < 18 || idade >= 100) {
			puts("\nidade invalida");
		}
	} while (idade < 18 || idade >= 100);
	do {
		printf("\nQual o tipo do contrato?");
		printf("\nD- Diaria");
		printf("\nP- Parcial");
		printf("\nM- Mensal\n");
		scanf("%c", &novo->contrato);
		if (novo->contrato != 'D' && novo->contrato != 'P'
				&& novo->contrato != 'M') {
			printf("\nTipo de contrato invalido\n");
		}
	} while (novo->contrato != 'D' && novo->contrato != 'P'
			&& novo->contrato != 'M');

	do {
		puts("\nQuantidade de placas?\n");
		scanf("%d", &novo->qtdPlaca);
		fflush(stdin);
		if ((novo->qtdPlaca) > MAX_PLACA || (novo->qtdPlaca) < 1) {
			printf(
					"nao deve ter mais do que %d placas\nPelo menos uma placa deve ser cadastrada!",
					MAX_PLACA);
		}
	} while ((novo->qtdPlaca) > MAX_PLACA || (novo->qtdPlaca) < 1);
	int i;
	for (i = 0; i < (novo->qtdPlaca); i++) {
		cadastroCarro(&novo);
	}
	if ((*lista) == NULL) {
		(lista) = &novo;
		(*lista)->proximo = NULL;
	} else {
		novo->anterior = (*lista);
		novo->proximo = NULL;

		(*lista)->proximo = novo;
	}

	puts("Cliente Cadastrado com Sucesso!");
	return *lista;
}
void ExcluirPessoa(EstruturaPessoa** pessoa) {
	(*pessoa)->anterior->proximo = (*pessoa)->proximo; // indica que o proximo do item excluido sera
	//o proximo do item anterior a ele, tomando seu lugar

	(*pessoa)->proximo			//indica que o item anterior ao excluido sera
			->anterior = (*pessoa)->anterior; // o anterior ao proximo item dele, tomando seu lugar

	//ficando sem referencia, o item nao pode ser mais encontrado na lista
	(*pessoa) = (*pessoa)->proximo; //passamos para o proximo da lista, e perdemos a referencia ao item excluido.
}
void imprimeCarro(EstruturaCarro* carro) {
	if (carro != NULL) {
		printf("Placa: %s\n", carro->placa);
		printf("Codigo : %d\n", carro->codigo);
		printf("Ano: %d\n", carro->ano);
		printf("Modelo: %s\n", carro->modelo);
		imprimeCarro(carro->anterior); // volta o ponteiro para os dados do carro anterior

	}
}
void imprimirTudo(EstruturaPessoa* lista) {
	if (lista != NULL) {

		printf("\n\nNOME: %s\n", lista->nome);
		printf("\nCodigo : %d", lista->codigo);
		printf("\nData de Nasc: %s", lista->dataNasc);
		printf("\nContrato: %c", lista->contrato);
		printf("\nQuantidade de Placas: %d", lista->qtdPlaca);
		EstruturaCarro* tmp = lista->dadosDosCarros;
		printf("\n---------------");
		printf("\n----CARROS-----\n");
		imprimeCarro(tmp);
		printf("----------------------\n");
		printf("----FIM DOS CARROS----\n");
		imprimirTudo(lista->proximo);

	}
}

EstruturaPessoa* procurarPessoaPorCodigo(EstruturaPessoa* lista, int codigo) {
	if ((lista) == NULL) {
		puts("Lista Vazia");
		return NULL;
	} else if (lista->codigo == codigo) {
		puts("\nNOME: ");
		puts(lista->nome);
		puts("\nData Nascimento: ");
		puts(lista->dataNasc);
		return lista;
	} else{
		return procurarPessoaPorCodigo(lista->proximo, codigo);
	}

}
int consistePlaca(char placa[]) {
	int i = 0;
	for (i = 0; i < 3; i++) {
		if (!VerificaSeEhLetra(placa[i])) {
			return 1;
		}
	}
	for (i = 3; i < 7; i++) {
		if (!VerificaSeEhNumero(placa[i])) {
			return 1;
		}
	}
	return 0;
}




