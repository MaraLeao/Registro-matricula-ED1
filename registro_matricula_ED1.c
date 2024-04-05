/*TRABALHO ESTRUTURA DE DADOS 1

Desenvolver um programa em C que apresente um menu com as opções a seguir, realizadas por um algoritmos de LISTA SEQUENCIA ORDENADA para registrar o RGM e LISTA ENCADEADA para regsitrar as materias de cada RGM:

Criar lista - 
Inserir RGM - 
Mostrar os RGMs e as respectivas disciplinas - 
Buscar o aluno pelo RGM - 
Remover um aluno - 
Mostrar a lista após a remoção -
Sair - 

*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include 	<locale.h>

#define	MAX 60

typedef struct disciplina {
    char    nome_disciplina[50];
    int     nota;
} t_disciplina;

typedef struct no {
    t_disciplina dado;  // elemento contendo os dados
    struct no * prox; // ponteiro para o proximo elemento
} t_no; 

typedef t_no * t_lista;  

typedef struct rgm {
	char	            matricula[10];
    struct disciplina * t_disciplina;
} Registro_matricula;

typedef struct l {
	Registro_matricula	alunos[MAX];
	int	qtd_alunos;
} Lista;

Lista	criar() {
	Lista l;
	
	l.qtd_alunos = -1;
	
	return l;
}

int	isVazia(Lista * l){
	return (l->qtd_alunos == -1);
}

int	isCheia (Lista * l) {
	return (l->qtd_alunos == (MAX -1));
}

int	getQuantidade(Lista * l) {
	return (l->qtd_alunos + 1);
}

int deslocaDireita(Lista * l, int pos) {
    int i;

    for (i = l->qtd_alunos + 1; i>pos; i--) {
        l->alunos[i] = l->alunos[i-1];
    }
}

int inserirPos (Lista * l, int pos, Registro_matricula dado) {
    if (isCheia(l) || (pos > l->qtd_alunos + 1) || (pos < 0))
        return 0;

    deslocaDireita(l, pos);
    l->alunos[pos] = dado;
    (l->qtd_alunos)++;
    return 1;
}

int deslocaEsquerda(Lista * l, int pos) {
    int i;

    for (i = pos; i < l->qtd_alunos ; i++) {
        l->alunos[i] = l->alunos[i+1];
    }        
}

int getPosRGM(Lista * l, char matricula[]) {
	int i;
	for (i = 0; i <= l->qtd_alunos; i++) {
		if (strcmp(l->alunos[i].matricula, matricula) == 0)
			return i;
	}
			
	return -1;
}

int removeRGM(Lista * l, char rgm[]) {
    int pos = getPosRGM(l, rgm);

    if ((pos > l->qtd_alunos) || (pos < 0))
        return 0;

    deslocaEsquerda(l, pos);
    (l->qtd_alunos)--;
    
    return 1;
}

int getPosRGMInserirOrd(Lista * l, char matricula[]) {
    int i;
    
    for (i = l->qtd_alunos; i >= 0; i--) {
        if (strcmp(l->alunos[i].matricula, matricula) < 0) {
            return i + 1;
        } 

        else if (strcmp(l->alunos[i].matricula, matricula) == 0) {

            int count = 1;
            while (l->alunos[i].matricula[count] == matricula[count] && l->alunos[i].matricula[count] != '\0' && matricula[count] != '\0') {
                count++;
            }

            if (l->alunos[i].matricula[count] < matricula[count]) {
                return i + 1;
            }
        }
    }

    return 0;
}

int inserirOrdenada (Lista * l, Registro_matricula dado) {
	int pos;
	
    if (isCheia(l)) {
        return 0;
    }
        
	if (isVazia(l)) {
        pos = 0;
    } else {
        pos = getPosRGMInserirOrd(l, dado.matricula);
    }
	
	inserirPos(l, pos, dado);	

    return 1;
}

// t_no * getNo(t_lista lista, int pos) {
//     // Retorna 0 se posicao invalida. Do contrario, retorna o elemento
//     int n = 0;

//     if (pos<0)
//         return 0; // erro: posicao invalida

//     while (lista != NULL) {
//         if (n==pos)
//             return lista;
//         lista = lista->prox;
//         n++;
//     }
//     return 0; // erro: posicao invalida
// }

// int getTamanhoDis(t_lista lista) {
//     int n = 0;
//     while (lista != NULL) {
//         lista = lista->prox;
//         n++;
//     }
//     return n;
// }

// t_disciplina * getDisciplina(t_lista lista, int pos) {
//     t_no * no = getNo(lista, pos);
//     if (no != NULL)
//         return &(no->dado);
//     else
//         return NULL;
// }

// int inserirDis(t_lista *lista, int pos, t_disciplina dado) {
//     t_no * p, * novo;

//     // inserção na primeira posicao ou em lista vazia
//     if (pos == 0) {
//         novo = criaNo();
//         if (novo == NULL)
//             return 0; // erro: memoria insuficiente
//         novo->dado = dado;
//         novo->prox = *lista;
//         *lista = novo;
//         return 1;
//     }
//     // insercao apos a primeira posicao em lista nao vazia
//     p = getNo(*lista, pos-1);
//     if (p == NULL)
//          return 0; // erro: posicao invalida 
//     novo = criaNo();
//     if (novo == NULL)
//         return 0; // erro: memoria insuficiente
//     novo->dado = dado;
//     novo->prox = p->prox;
//     p->prox = novo;

//     return 1;
// }

// void mostraLista(t_lista lista) {
// 	int cnt = 0;
	
// 	while(lista != NULL) {
// 		printf("Elemento [%d] tem [%s]\n", ++cnt, lista->dado.nome_disciplina);
// 		lista = lista->prox;
// 	}
	
// 	if(!cnt)
// 		printf("Lista vazia\n");
// }


// int remover(t_lista * lista, int pos) {
//     t_no * anterior,  *p;
//     if (isVazia(*lista)) return 0; // erro: lista vazia
//     if (pos<0) return 0; // erro: posicao invalida

//     // remocao da primeira posicao em lista nao vazia
//     if (pos == 0) {
//         p = *lista;
//         *lista = p->prox;
//     } else { // remocao em qualquer posicao
//         anterior = getNo(*lista, pos-1);
//         if (anterior == NULL)
//             return 0; // erro: posicao invalida
//         p = anterior->prox;
//         if (p == NULL)
//             return 0; // erro: posicao invalida
//         anterior->prox = p->prox;
//     }
//     free(p);
//     return 1;
// }

void mostrar(Lista * l){
	
	int i;
	
	printf("Minha lista de alunos\n");
	for(i = 0; i <= l->qtd_alunos; i++) {
		printf("Rgm: %s\n", l->alunos[i].matricula);
	}
}

int buscar(Lista *l, char str[], int rgm) {
    return getPosRGM(l, str);
}

int	main() {
	setlocale(0,"Portuguese");
	
	Lista	myLista;
	Registro_matricula rgm;
    t_disciplina mDis;
	t_lista	mLista = NULL;
	t_no *	mNo;
	t_lista	aux = NULL;

    int opt, posOrdenada, i;
    int busca = -1;
	char resp = 's';
    int menu = 0;
    char reg_matricula[10];
    char tel[50];
    int quit = 0;
	
	myLista = criar();

    while(quit != 1) {
        switch (menu)
        {
            case 0:
                printf("\nBem vindo a sua agenda!\n1 - Mostrar matriculas\n2 - Adicionar matriculas\n3 - Apagar matriculas\n4 - Buscar matriculas\n5 - Sair\n");
                printf("Digite a opção: ");
                scanf(" %d", &menu);
                break;

            case 1:
                mostrar(&myLista);
                menu = 0;
                break;

            case 2:
                while(resp == 's') {
                    printf("RGM:");
                    scanf("%49s", rgm.matricula);
                    inserirOrdenada(&myLista, rgm);

                    // printf("Nome da disciplina: ");
                    // scand("%49", &(mDis));

                    // posOrdenada = getPosicaoInsercaoOrdenada(mLista, mDis);
		            // inserir(&mLista, posOrdenada, mDis);
                    
                    
                    printf("Deseja continuar s/n\n");
                    scanf("\n%c", &resp); 
                }
                resp = 's';
                menu = 0;
                break;

            case 3:
                while (resp == 's') {
                    printf("Digite o RGM para apagar a matricula\n>>");
                    
                    scanf("%9s", reg_matricula); 
                    removeRGM(&myLista, reg_matricula);
                    
                    printf("Deseja continuar s/n\n");
                    scanf("\n%c", &resp); 
                }

                menu = 0;
            break;

            case 4:
                printf("Digite o RGM para buscar\n>>");
                
                scanf("%49s", reg_matricula); 
                
                if ((busca = buscar(&myLista, reg_matricula, 1)) != -1) {
                    printf("Rgm: %s\t", myLista.alunos[busca].matricula);
                }

                menu = 0;
            break;

            case 5:
                quit = 1;
                printf("Bye");
            break;

            default:
                printf("\nDigite um dos numeros do menu\n");
                menu = 0;
            break;
        
        }
        
    }
}