#include <stdio.h>
#include <stdlib.h>

// Lista Circular

typedef struct no
{
    int valor;
    struct no *proximo;
} No;

typedef struct
{
    No *inicio;
    No *fim; // Criado para saber quando o proximo sera o inicio da lista
    int tam;
} Lista;

void criar (Lista *lista)
{
    lista->inicio = NULL;
    lista->fim = NULL; // Sera Null pq n tem nada dentro da lista, ela acabou de ser criada
    lista->tam = 0;
}

void inserir_inicio(Lista *lista, int num)
{
    No *novo = malloc(sizeof(No));

    if(novo) // Se a locação de memoria for feita com sucesso, execute isso:
    {
        novo->valor = num; // O novo valor recebe o numero que queremos inserir
        novo->proximo = lista->inicio; // Proximo indicara para o inicio da nossa lista
        lista->inicio = novo; // O inicio da lista, sera o novo nó criado
        if(lista->fim == NULL) // Verifica se o fim é NULL, ou seja, não tem nada na frente dele
        {
            lista->fim = novo;
        }
        else
        {
            lista->fim->proximo = lista->inicio; // Vai apontar para o lista->inicio que recebeu antes
                                                 // o novo nó
        }
        lista->tam++;
    }
    else // Caso contrario, printe na tela um erro:
    {
        printf("\nErro ao alocar espaco de memoria\n");
    }
}

void inserir_fim(Lista *lista, int num)
{
    No *novo = malloc(sizeof(No));

    if(novo)
    {
        novo->valor = num;
        if(lista->inicio == NULL) // Se for o primeiro elemento da lista
        {
            lista->inicio = novo; // Inicio da lista recebe o novo nó
            lista->fim = novo; // Fim recebe o novo nó
            lista->fim->proximo = lista->inicio; // O proximo fim, vai indicar para o inicio da lista
        }
        else // Caso não for o primeiro
        {
            lista->fim->proximo = novo; // O que antes era o ultimo elemento da lista vai indicar para o novo nó
            lista->fim = novo; // O fim da lista vai ser o novo nó criado
            // lista->fim->proximo = lista->inicio; tem essa maneira de fazer
            novo->proximo = lista->inicio; // Novo nó agora vai apontar para o inicio da lista, pois agora ele
                                           // é o ultimo elemento da lista;
        }
        lista->tam++;
    }
    else
    {
        printf("\nErro ao alocar memoria!\n");
    }

}

void inserir_ordenado(Lista *lista, int num)
{
    No *aux, *novo = malloc(sizeof(No));

    if(novo)
    {
        novo->valor = num;
        if(lista->inicio == NULL) // Se for o primeiro elemento da lista
        {
            lista->inicio = novo; // Inicio da lista recebe o novo nó
            lista->fim = novo;  // Fim também vai receber o novo nó
            lista->fim->proximo = lista->inicio; // Fim->proximo indica para o inicio da lista
        }
        else if(novo->valor < lista->inicio->valor) // Se o novo nó tiver valor menor que o primeiro nó
        {
            novo->valor = num; // O novo valor recebe o numero que queremos inserir
            novo->proximo = lista->inicio; // Proximo indicara para o inicio da nossa lista
            lista->inicio = novo; // O inicio da lista, sera o novo nó criado
            if(lista->fim == NULL) // Verifica se o fim é NULL, ou seja, não tem nada na frente dele
            {
                lista->fim = novo;
            }
            else
            {
                lista->fim->proximo = lista->inicio; // Vai apontar para o lista->inicio que recebeu antes
                                                 // o novo nó
            }
        }
        else // Se a lista não for NULL e o valor do inicio é menor que o novo valor, execute isso:
        {
            aux = lista->inicio;
            while(aux->proximo != lista->inicio && novo->valor > aux->proximo->valor) // O Auxiliar vai percorrer toda a lista
                                                                                      // enquanto não for o inicio da lista, pois
                                                                                      // agora o ultimo elemento está apontando para
                                                                                      // o inicio da lista. E enquanto o valor que eu
                                                                                      // quero inserir for maior que o valor do proximo
                                                                                      // nó, procure até achar alguem que seja maior ou
                                                                                      // até chegar no final da lista.
            {
                aux = aux->proximo;
            }
            if(aux->proximo == lista->inicio) // Se o auxiliar proximo estiver apontando
                                              // para o inicio da lista, quer dizer que estamos no final da lista
            {
                lista->fim->proximo = novo; // O que antes era o ultimo elemento da lista vai indicar para o novo nó
                lista->fim = novo; // O fim da lista vai ser o novo nó criado
                // lista->fim->proximo = lista->inicio; tem essa maneira de fazer
                novo->proximo = lista->inicio; // Novo nó agora vai apontar para o inicio da lista, pois agora ele
                                               // é o ultimo elemento da lista;
            }
            else // Se não for o ultimo elemento da lista
            {
                novo->proximo = aux->proximo; //
                aux->proximo = novo;
            }
        }
        lista->tam++;
    }
    else
    {
        printf("\nErro ao alocar memoria!\n");
    }
}

No* remover (Lista *lista, int num)
{
    No *aux, *remover = NULL;

    if(lista->inicio) // Verifica se a lista existe
    {
        if(lista->inicio == lista->fim && lista->inicio->valor == num) // Verifica se existe só um nó na lista e se o valor do
                                                                       // inicio bate com o numero digitado
        {
            remover = lista->inicio; // Remover recebe o inicio da lista
            lista->inicio = NULL;
            lista->fim = NULL; // Não vai existir mais nada na lista, por isso que tanto o inicio e o fim ficam nulos
            lista->tam--;  // Tam-- pois estamos removendo um nó
        }
        else if(lista->inicio->valor == num) // Se o inicio da lista não for igual o fim, verifique
                                            // se o primeiro valor da lista é igual ao numero digitado.
        {
            remover = lista->inicio; // Remover recebe o inicio da lista
            lista->inicio = remover->proximo; // O inicio agora vai indicar para o proximo elemento, apos ser removido
            lista->fim->proximo = lista->inicio; // Fim->proximo agora vai indicar para o incio da lista, apos o primeiro
                                                 // elemento ser removido
            lista->tam--;
        }
        else
        {
            aux = lista->inicio; // Auxiliar recebe o inicio da lista
            while(aux->proximo != lista->inicio && aux->proximo->valor != num)  // O Auxiliar vai percorrer toda a lista
                                                                                // enquanto não for o inicio da lista, pois
                                                                                // agora o ultimo elemento está apontando para
                                                                                // o inicio da lista. E enquanto o valor que está
                                                                                // na lista for diferente do numero digitado, o
                                                                                // programa vai ficar procurando
            {
                aux = aux->proximo;
            }
            if(aux->proximo->valor == num) // Se o valor encontrado é igual o numero digitado, entre no if
            {
                if(lista->fim == aux->proximo) // Se o ponteiro proximo auxiliar esta apontando para o ultimo nó da lista
                {
                    remover = aux->proximo; // Remover recebe o endereço do ultimo nó
                    aux->proximo = remover->proximo; // Auxiliar proximo vai apontar para o nó seguinte
                    lista->fim = aux; // O ultimo nó da lista agora é o auxiliar
                }
                else
                {
                    remover = aux->proximo; // Remover recebe o endereço do nó que deseja remover
                    aux->proximo = remover->proximo; // Auxiliar proximo vai apontar para o nó seguinte
                }
                lista->tam--;
            }
        }
    }
    return remover;
}

No* buscar(Lista *lista, int num)
{
    No *aux;
    aux = lista->inicio; //Auxiliar recebe o inicio da lista

    if(aux) // Verifica se a lista existe
    {
        do
        {
            // Vai ficar procurando um nó com o mesmo valor do numero digitado, após encontrar esse valor
            // vai cair dentro do if e irá retornar o nó para o auxiliar
            if(aux->valor == num)
            {
                return aux;
            }
            aux = aux->proximo;
        }while(aux != lista->inicio); // Enquanto aux for diferente do inicio da lista, ou seja, percorra toda a lista
                                      // até cair no ponteiro fim->proximo
    }
    else
    {
        printf("\nA Lista nao foi criada!\n");
    }
}

void imprimir(Lista lista)
{
    No *no = lista.inicio;
    printf("\n\t Lista tamanho: %d", lista.tam);
    if(no) // Verifica se a lista não está vazia
    {
        do
        {
            printf("\n%d ", no->valor);
            no = no->proximo;
        }while(no != lista.inicio); // Vai percorrer toda lista até chegar no fim->proximo
        printf("\nInicio: %d\n", no->valor); // Só para comprovar que voltou para o inicio
    }
    printf("\n\n");
}

int main(void)
{
    Lista lista;
    No *removido;
    int opcao, num;

    criar(&lista);

    do
    {
        printf("\n ----- MENU -----");
        printf("\n1 - Adicionar no Inicio");
        printf("\n2 - Adicionar no Final");
        printf("\n3 - Adicionar em Forma Ordenada");
        printf("\n4 - Remover");
        printf("\n5 - Buscar");
        printf("\n6 - Listar");
        printf("\n0 - Sair");
        printf("\nSelecione uma opcao: ");
        if (scanf("%d", &opcao) != 1) // Verifica se o que foi digitado é um numero
        {
            printf("\nSelecione uma opcao existente!");
            while (getchar() != '\n');
            continue;
        }
        fflush(stdin);

        switch (opcao)
        {
        case 1:
            printf("\nDigite um valor: ");
            scanf("%d", &num);
            inserir_inicio(&lista, num);
            printf("\n\nPressione Enter para voltar ao Menu");
            getchar();
            system("cls");
            break;
        case 2:
            printf("\nDigite um valor: ");
            scanf("%d", &num);
            inserir_fim(&lista, num);
            printf("\n\nPressione Enter para voltar ao Menu");
            getchar();
            system("cls");
            break;
        case 3:
            printf("\nDigite um valor: ");
            scanf("%d", &num);
            inserir_ordenado(&lista, num);
            printf("\n\nPressione Enter para voltar ao Menu");
            getchar();
            break;
        case 4:
            printf("\nDigite o valor a ser removido: ");
            scanf("%d", &num);
            removido = remover(&lista, num);
            free(removido);
            printf("\n\nPressione Enter para voltar ao Menu");
            getchar();
            break;
        case 5:
            printf("\n\nDigite o valor a ser buscado: ");
            scanf("%d", &num);
            buscar(&lista, num);
            printf("\n\nPressione Enter para voltar ao Menu");
            getchar();
            break;
        case 6:
            imprimir(lista);
            printf("\n\nPressione Enter para voltar ao Menu");
            getchar();
            break;
        case 0:
            printf("\nSaindo do Programa...");
            printf("\nObrigado por usar! :)");
            return 0;
        default:
            printf("\nSelecione uma opcao existente!");
        }
    } while(opcao != 0);

return 0;
}
