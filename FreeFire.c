#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    return 0;
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10 

// Estrutura que representa um item do inventário
typedef struct {
    char nome[30];
    char categoria[20]; // Ex: arma, munição, cura, ferramenta
    int quantidade;
} Item;

// Variáveis globais para o inventário
Item mochila[MAX_ITENS];
int totalItens = 0;

// Exibe o menu principal para o jogador
void exibirMenu() {
    printf("\n--- 🎒 Inventário Inicial (Mochila) ---\n");
    printf("1. Cadastrar Novo Item (Coletar Loot)\n");
    printf("2. Remover Item (Descartar Loot)\n");
    printf("3. Buscar Item por Nome\n");
    printf("4. Sair do Jogo\n");
    printf("---------------------------------------\n");
    printf("Itens na Mochila: %d/%d\n", totalItens, MAX_ITENS);
    printf("Escolha uma opção: ");
}

// Lista todos os itens que estão na mochila
void listarItens() {
    printf("\n--- 📜 Itens Atuais na Mochila ---\n");

    if (totalItens == 0) {
        printf("A mochila está vazia. Colete alguns itens!\n");
        printf("---------------------------------------\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("  [%d] Nome: %s, Tipo: %s, Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].categoria, mochila[i].quantidade);
    }
    printf("-----------------------------------\n");
}

// Função para inserir um novo item na mochila
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n⚠️ ATENÇÃO: A mochila está cheia! Não é possível coletar mais loot.\n");
        return;
    }

    printf("\n--- ➕ Cadastro de Novo Item ---\n");

    printf("Informe o nome do item (máx 29 caracteres): ");
    scanf("%29s", mochila[totalItens].nome);

    printf("Informe o tipo do item (ex: arma, munição, cura): ");
    scanf("%19s", mochila[totalItens].categoria);

    printf("Informe a quantidade: ");
    while (scanf("%d", &mochila[totalItens].quantidade) != 1) {
        while(getchar() != '\n');
        printf("Entrada inválida. Digite um número inteiro: ");
    }

    printf("\n✅ Item '%s' cadastrado com sucesso na mochila!\n",
           mochila[totalItens].nome);

    totalItens++;

    listarItens();
}

// Função para buscar um item pelo nome (busca linear)
int localizarItem(const char *chaveBusca) {
    for (int i = 0; i < totalItens; i++) {
        if (strcasecmp(mochila[i].nome, chaveBusca) == 0) {
            return i;
        }
    }
    return -1;
}

// Remoção de item pelo nome
void removerItem() {
    if (totalItens == 0) {
        printf("\n⚠️ A mochila está vazia. Nada para remover.\n");
        return;
    }

    char alvo[30];
    printf("\n--- ➖ Remoção de Item ---\n");
    printf("Informe o NOME do item que deseja descartar: ");
    scanf("%29s", alvo);

    int indice = localizarItem(alvo);

    if (indice != -1) {
        for (int i = indice; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }

        totalItens--;

        printf("\n✅ Item '%s' descartado com sucesso da mochila!\n", alvo);
    } else {
        printf("\n❌ ERRO: Item '%s' não encontrado na mochila.\n", alvo);
    }

    listarItens();
}

// Interface de busca para o jogador
void buscarItemInterface() {
    if (totalItens == 0) {
        printf("\n⚠️ A mochila está vazia. Nada para buscar.\n");
        return;
    }

    char chavePesquisa[30];
    printf("\n--- 🔍 Busca de Item ---\n");
    printf("Informe o NOME do item que deseja localizar: ");
    scanf("%29s", chavePesquisa);

    int indice = localizarItem(chavePesquisa);

    if (indice != -1) {
        Item encontrado = mochila[indice];
        printf("\n✅ Item '%s' encontrado na mochila!\n", chavePesquisa);
        printf("Detalhes:\n");
        printf("  -> Nome: %s\n", encontrado.nome);
        printf("  -> Tipo: %s\n", encontrado.categoria);
        printf("  -> Quantidade: %d\n", encontrado.quantidade);
    } else {
        printf("\n❌ Item '%s' não encontrado na mochila.\n", chavePesquisa);
    }
}

int main() {
    int escolha;

    printf("Iniciando a Simulação de Inventário de Loot...\n");

    do {
        exibirMenu();

        if (scanf("%d", &escolha) != 1) {
            while(getchar() != '\n');
            escolha = 0;
        }

        switch (escolha) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: buscarItemInterface(); break;
            case 4:
                printf("\n👋 Jogo Encerrado. Obrigado por usar o sistema de Inventário!\n");
                break;
            default:
                printf("\n❌ Opção inválida. Tente novamente.\n");
                break;
        }

    } while (escolha != 4);

    return 0;
}
