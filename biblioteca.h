#ifndef BIBLIOTECA_H_
#define BIBLIOTECA_H_

#define CODIGO(x) (x*100+1)
#define ERRO_ENTRADA puts("Erro na entrada de dados")
const int MAX_PLACA = 5;
typedef struct CARRO EstruturaCarro;
typedef struct PESSOA EstruturaPessoa;
struct CARRO {
	char placa[7];
	int codigo;
	char modelo[50];
	int ano;
	EstruturaCarro *anterior;
};

struct PESSOA {
	char nome[50];
	int codigo;
	char dataNasc[10];
	char contrato;
	int qtdPlaca;
	EstruturaCarro *dadosDosCarros;

	EstruturaPessoa *proximo;
	EstruturaPessoa *anterior;
};

void menu();
int VerificaSeEhNumero(char c);
int VerificaSeEhletra(char c);
int verificarData(char data[]);
int concatINT(char s[], int inicio, int fim);
void cadastroCarro(EstruturaPessoa **lista);
EstruturaPessoa* cadastroPessoa(EstruturaPessoa **lista);
void imprimeCarro(EstruturaCarro* carro);
void imprimirTudo(EstruturaPessoa* lista);
EstruturaPessoa* procurarPessoaPorCodigo(EstruturaPessoa* lista, int codigo);
int consistePlaca(char placa[]);



#endif /* BIBLIOTECA_H_ */
