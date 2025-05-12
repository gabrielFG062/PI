#include <stdio.h>
#include <string.h>

#define MAX 100
#define STR 50

typedef struct {
    char nome[STR], descricao[STR * 4], categoria[STR];
    float preco;
    int avaliacao, disponivel;
} Servico;

typedef struct {
    char nome[STR], email[STR], telefone[15], localizacao[STR];
    Servico servicos[MAX];
    int num_servicos;
    float avaliacao_media;
} Autonomo;

typedef struct {
    char nome[STR], email[STR], telefone[15], localizacao[STR];
    Servico servicos_contratados[MAX];
    int num_servicos;
} Cliente;

void ler_string(char *msg, char *dest, int size) {
    printf("%s", msg);
    fgets(dest, size, stdin);
    dest[strcspn(dest, "\n")] = '\0';
}

void exibir_servico(Servico s) {
    printf("\n--- %s (%s) ---\nDescrição: %s\nPreço: R$%.2f\nAvaliação: %d/5\n%s\n",
           s.nome, s.categoria, s.descricao, s.preco, s.avaliacao,
           s.disponivel ? "Disponível" : "Indisponível");
}

void exibir_autonomo(Autonomo a) {
    printf("\n=== %s ===\nContato: %s | %s\nLocal: %s\nAvaliação: %.1f/5\n",
           a.nome, a.email, a.telefone, a.localizacao, a.avaliacao_media);
    for (int i = 0; i < a.num_servicos; i++)
        exibir_servico(a.servicos[i]);
}

void buscar_categoria(Autonomo aut[], int total, char cat[]) {
    printf("\n--- Categoria: %s ---\n", cat);
    for (int i = 0; i < total; i++)
        for (int j = 0; j < aut[i].num_servicos; j++)
            if (strcmp(aut[i].servicos[j].categoria, cat) == 0 && aut[i].servicos[j].disponivel)
                exibir_autonomo(aut[i]);
}

Cliente cadastrar_cliente() {
    Cliente c;
    printf("\n--- Cadastro ---\n");
    ler_string("Nome: ", c.nome, STR);
    ler_string("Email: ", c.email, STR);
    ler_string("Telefone: ", c.telefone, 15);
    ler_string("Localização: ", c.localizacao, STR);
    c.num_servicos = 0;
    printf("Cadastro realizado!\n");
    return c;
}

void filtrar_preco(Autonomo aut[], int total, float max) {
    printf("\n--- Serviços até R$%.2f ---\n", max);
    for (int i = 0; i < total; i++)
        for (int j = 0; j < aut[i].num_servicos; j++)
            if (aut[i].servicos[j].preco <= max && aut[i].servicos[j].disponivel)
                exibir_autonomo(aut[i]);
}

void menu() {
    printf("\n=== Plataforma Autônomos ===\n"
           "1. Buscar por categoria\n2. Filtrar por preço\n"
           "3. Todos os serviços\n4. Cadastrar cliente\n5. Sair\nOpção: ");
}

int main() {
    Autonomo aut[] = {
        {"João Silva", "joao@email.com", "11987654321", "São Paulo", {}, 0, 4.5},
        {"Maria Souza", "maria@email.com", "21987654321", "Rio de Janeiro", {}, 0, 4.8},
        {"Carlos Oliveira", "carlos@email.com", "31987654321", "Belo Horizonte", {}, 0, 4.2}
    };

    Servico s[] = {
        {"Design de Logo", "Criação de logo profissional", "Design", 150.0, 5, 1},
        {"Desenvolvimento Web", "Criação de sites responsivos", "TI", 1200.0, 4, 1},
        {"Encanador", "Serviços de encanamento", "Reforma", 80.0, 5, 1}
    };

    for (int i = 0; i < 3; i++) {
        aut[i].servicos[0] = s[i];
        aut[i].num_servicos = 1;
    }

    Cliente cliente;
    int op;
    float preco;
    char cat[STR];

    do {
        menu();
        scanf("%d", &op); getchar();

        switch (op) {
            case 1:
                ler_string("Categoria: ", cat, STR);
                buscar_categoria(aut, 3, cat);
                break;
            case 2:
                printf("Preço máximo: ");
                scanf("%f", &preco); getchar();
                filtrar_preco(aut, 3, preco);
                break;
            case 3:
                for (int i = 0; i < 3; i++) exibir_autonomo(aut[i]);
                break;
            case 4:
                cliente = cadastrar_cliente();
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (op != 5);

    return 0;
}
