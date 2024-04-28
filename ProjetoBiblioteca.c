#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

typedef struct{
	char id[5];
	char titulo[50];
	int paginas;
}Biblioteca;

void troca(Biblioteca livro[], int j, int aux){
	Biblioteca agora = livro[j];
	livro[j] = livro[aux];
	livro[aux] = agora;
}

void bubble(Biblioteca livro[], int tamanho){
	int i, j;
	for(i =0; i < tamanho -1; i++){
		for(j = 0; j < tamanho -1; j++){
			if(strcmp(livro[j].id, livro[j+1].id) > 0)
				troca(livro, j, j+1);
		}
	}
}

int pesquisa(Biblioteca livro[], int tamanho, char desejado[5]){
	int meio;
	int superior = tamanho - 1;
	int inferior = 0;
	while(inferior <= superior){
		meio = (inferior + superior) / 2;
		if(strcmp(livro[meio].id, desejado) == 0)
			return meio;
		else if(strcmp(livro[meio].id, desejado) < 0)
			inferior = meio + 1;
		else
			superior = meio - 1;		
	}
	return -1;
}

void inserirLivro(Biblioteca *livro, int *tamanho){
	printf("Digite o c�digo do livro: ");
	scanf("%s", livro[*tamanho].id);
	printf("Digite o titulo do livro: ");
	getchar();
	fgets(livro[*tamanho].titulo, sizeof(livro[*tamanho].titulo), stdin);
	printf("Digite o numero de p�ginas: ");
	scanf("%d", & livro[*tamanho].paginas);
	(*tamanho)++; 
}

void mostraPesquisa(Biblioteca p){
	printf("\nLivro: %s\t Quantidade de paginas: %d\n", p.titulo, p.paginas);
}

void livrosCadastrados(Biblioteca livros[], int tamanho){
	int i;
	for(i = 0; i < tamanho; i++){
		printf("\nCodigo: %s", livros[i].id);
		printf("\nTitulo: %s",livros[i].titulo);
		printf("P�ginas: %d", livros[i].paginas);
		printf("\n");
	}
}

void removerLivro(Biblioteca livro[], int *tamanho, char codigo[5]) {
    int i, posicao;
    posicao = pesquisa(livro, *tamanho, codigo);

    if (posicao == -1) {
        printf("Livro n�o encontrado\n");
        return;
    }

    for (i = posicao; i < *tamanho - 1; i++) {
        strcpy(livro[i].id, livro[i + 1].id);
        strcpy(livro[i].titulo, livro[i + 1].titulo);
        livro[i].paginas = livro[i + 1].paginas;
    }

    (*tamanho)--; 
    printf("Livro removido com sucesso\n");
}


void executarMenu(Biblioteca livro[], int *tamanho) {
    int escolha;
    char desejado[5];
    char removido[5];
    int posicao;
    char Resp;

    do {
        printf("\nSelecione uma opcao:\n");
        printf("1. Pesquisar livro por ID\n");
        printf("2. Inserir livro\n");
        printf("3. Livros cadastrados\n");
        printf("4. Excluir livro\n");
        printf("5. Sair\n");
        printf("Opcao: ");
        scanf("%d", &escolha);
        getchar(); 

        switch (escolha) {
            case 1:
                printf("\nDigite o c�digo do livro: ");
                scanf("%s", desejado);
                posicao = pesquisa(livro, *tamanho, desejado);
                printf("\nProduto Selecionado: ");
                if (posicao == -1)
                    printf("\nProduto n�o encontrado\n");
                else
                    mostraPesquisa(livro[posicao]);
                break;

            case 2:
                inserirLivro(livro, tamanho);
                break;
                
            case 3:
                livrosCadastrados(livro, *tamanho);
                break;    
                
			case 4:
			printf("\nDigite o c�digo do livro a ser removido: ");
			scanf("%s", removido);
			removerLivro(livro, tamanho, removido);
		   	break;
				
            case 5:
                printf("\nSaindo.");
                exit(0); 
                break;

            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                break;
        }
        printf("\nDeseja fazer outra operacao? (S/N): ");
        scanf(" %c", &Resp);
        getchar(); 
    } while (Resp == 'S' || Resp == 's');
}

int main(){
	setlocale(LC_ALL,"Portuguese");
	Biblioteca livro[] = {{"159", "Harry Potter e o Calice de Fogo", 534},
						  {"009", "Narnia - A ultima batalha", 249},
						  {"113", "Eu, Robo - Isaac Asimov", 317},
						  {"004", "A menina que roubava livros", 611},
						  {"631", "Os ceifadores", 264}}; 
	int posicao;
	int escolha;
	char removido[5];
	char desejado[5];
	char Resp;
	int tamanho = sizeof(livro) / sizeof(livro[0]);
	
	bubble(livro, tamanho);
	
	executarMenu(livro, &tamanho);

    return 0;
}	

