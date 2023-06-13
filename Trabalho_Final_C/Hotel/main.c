#include <stdio.h>
#include <stdlib.h>

/* "Desculpe professor estou com muito sono e não sou muito bom em ficar comentando código.
Não acho que ele esteja bom, da pra melhorar muito mas infelizmente to sem tempo, então vai ser isso mesmo
na próxima eu faço um sistema melhor." */

typedef struct 
{
    char nome[50], cpf[20], email[50], tel[15];
    int idade, quarto, id;
} Hospede;

Hospede list_hospedes[15];
int qtd_registro = 0, qtd_quartos[15], id_registro = 0;

void salvar_arquivo()
{
    FILE *arquivo = fopen("bancodedados.txt", "w");

    if (arquivo) {
        fprintf(arquivo, "%d\n", qtd_registro);
        fprintf(arquivo, "%d\n", id_registro);
        for (int i=0; i < 15; i++) {
            fprintf(arquivo, "%d\n", qtd_quartos[i]);
        }
        for (int i=0; i < qtd_registro; i++) {
            fprintf(arquivo, "%s", list_hospedes[i].nome);
            fprintf(arquivo, "%s", list_hospedes[i].cpf);
            fprintf(arquivo, "%s", list_hospedes[i].email);
            fprintf(arquivo, "%s", list_hospedes[i].tel);
            fprintf(arquivo, "%d\n", list_hospedes[i].idade);
            fprintf(arquivo, "%d\n", list_hospedes[i].quarto);
            fprintf(arquivo, "%d\n", list_hospedes[i].id);
        }
    } else {
        printf("\nERRO AO ABRIR O ARQUIVO\n");
    }
    fclose(arquivo);
}

void carregar_arquivo()
{
    FILE *arquivo = fopen("bancodedados.txt", "r");

    if (arquivo) {
        fscanf(arquivo, "%d\n", &qtd_registro);
        fscanf(arquivo, "%d\n", &id_registro);
        for (int i=0; i < 15; i++) {
            fscanf(arquivo, "%d\n", &qtd_quartos[i]);
        }
        for (int i=0; i < qtd_registro; i++) {
            fgets(list_hospedes[i].nome, 50, arquivo);
            fgets(list_hospedes[i].cpf, 20, arquivo);
            fgets(list_hospedes[i].email, 40, arquivo);
            fgets(list_hospedes[i].tel, 15, arquivo);
            fscanf(arquivo, "%d\n", &list_hospedes[i].idade);
            fscanf(arquivo, "%d\n", &list_hospedes[i].quarto);
            fscanf(arquivo, "%d\n", &list_hospedes[i].id);
        }
    } else {
        printf("\nERRO AO ABRIR O ARQUIVO\n");
    }
    fclose(arquivo);
}

int buscar_id(int id) //Recebe um id inteiro como parametro e retorna o indice do cliente caso esteja cadastrado...
{
    for (int i = 0; i < qtd_registro; i++) {
        if (id == list_hospedes[i].id) {
            return i;
        }
    }
    return -1;
}

void total_pagamento(int dias, double *total)
{
    *total = 121.90 * dias;
}

int quartos() //Função que gera e retorna um quarto de forma aleatoria para um cliente novo cadastrado na pousada...
{
    int id = 1;
    for (int i = 0; i < 15; i++) {
        if (qtd_quartos[i] == 0) {
            qtd_quartos[i] = id;
            i = 15;
        } else {
            id++;
        }
    }
    return id;
}

void ficha_hospede(int i) //Função para listar uma ficha com dados de cada hospede, recebendo uma passagem por valor...
{
    printf("| Nome: %s", list_hospedes[i].nome);
    printf("| Cpf: %s", list_hospedes[i].cpf);
    printf("| Email: %s", list_hospedes[i].email);
    printf("| Telefone: %s", list_hospedes[i].tel);
    printf("| Id: %d\n", list_hospedes[i].id);
    printf("| Quarto: %d", list_hospedes[i].quarto);
    printf("\n=================================\n");
}

void excluir() //Exclui um hospede da pousada e faz os calculos da despeza total de acordo com os dias hospedado...
{
    int id, dias;
    double total;
    printf("\n=================================\n");
    printf("|       CHECKOUT DO HOSPEDE      |");
    printf("\n=================================\n");
    printf("| Id: ");
    scanf("%d",&id);
    int aux = buscar_id(id);
    if (aux != -1) {
        printf("=================================\n");
        printf("| Dias Hospedado: ");
        scanf("%d", &dias);
        total_pagamento(dias, &total);
        printf("=================================\n");
        printf("|   CHECKOUT CONCLUIDO - FICHA   |");
        printf("\n=================================\n");
        printf("| Dias Hospedado: %d\n", dias);
        printf("| Total a Pagar: R$%.2f\n", total);
        ficha_hospede(aux);

        qtd_quartos[list_hospedes[aux].quarto-1] = 0;
        list_hospedes[aux] = list_hospedes[qtd_registro-1];
        qtd_registro--;
    } else {
        printf("=================================\n");
        printf("|      HOSPEDE NAO ENCONTRADO    |");
        printf("\n=================================\n");
    }
}

void editar() //Altera todas as informações de um cliente cadastrado na pousada...
{
    int id;
    printf("\n=================================\n");
    printf("|    EDITAR DADOS DO HOSPEDE     |");
    printf("\n=================================\n");
    printf("| Id: ");
    scanf("%d",&id);
    int aux = buscar_id(id);
    if (aux != -1) {
        printf("=================================\n");
        scanf("%*c");
        printf("| Nome Completo: ");
        fgets(list_hospedes[aux].nome, 50, stdin);
        printf("| Cpf: ");
        fgets(list_hospedes[aux].cpf, 20, stdin);
        printf("| Email: ");
        fgets(list_hospedes[aux].email, 50, stdin);
        printf("| Telefone: ");
        fgets(list_hospedes[aux].tel, 15, stdin);
        printf("\n=================================\n");
        printf("|  ALTERACAO CONCLUIDA - FICHA   |");
        printf("\n=================================\n");
        ficha_hospede(aux);
    } else {
        printf("=================================\n");
        printf("|      HOSPEDE NAO ENCONTRADO    |");
        printf("\n=================================\n");
    }
}

void localizar() //Localiza um hospede atraves do id...
{
    int id;
    printf("\n=================================\n");
    printf("|        LOCALIZAR HOSPEDE       |");
    printf("\n=================================\n");
    printf("| Id: ");
    scanf("%d",&id);
    int aux = buscar_id(id);
    if (aux != -1) {
        printf("=================================\n");
        ficha_hospede(aux);
    } else {
        printf("=================================\n");
        printf("|      HOSPEDE NAO ENCONTRADO    |");
        printf("\n=================================\n");
    }
}

void listagem() { //Função para listar todos os hospedes cadastrados na pousada....
    if (qtd_registro > 0) {
        printf("\n=================================\n");
        printf("|       LISTA DE HOSPEDES        |");
        printf("\n=================================\n");
        for (int i = 0; i < qtd_registro; i++){
            ficha_hospede(i);
        }
    } else {
        printf("\n=================================\n");
        printf("|      NAO POSSUI REGISTROS      |");
        printf("\n=================================\n");
    }
}

void cadastrar() //Função para cadastrar hospede na pousada....
{
    printf("\n=================================\n");
    printf("|       CADASTRAR HOSPEDE        |");
    printf("\n=================================\n");

    printf("| Idade: ");
    int aux;
    scanf("%d", &aux);

    if (aux >= 18) {
        list_hospedes[qtd_registro].idade = aux;
        id_registro++;
        scanf("%*c");
        printf("| Nome Completo: ");
        fgets(list_hospedes[qtd_registro].nome, 50, stdin);
        printf("| Cpf: ");
        fgets(list_hospedes[qtd_registro].cpf, 20, stdin);
        printf("| Email: ");
        fgets(list_hospedes[qtd_registro].email, 50, stdin);
        printf("| Telefone: ");
        fgets(list_hospedes[qtd_registro].tel, 15, stdin);
        list_hospedes[qtd_registro].id = id_registro;
        list_hospedes[qtd_registro].quarto = quartos();

        printf("\n=================================\n");
        printf("|   CADASTRO CONCLUIDO - FICHA   |");
        printf("\n=================================\n");
        ficha_hospede(qtd_registro);
        qtd_registro++;
    } else {
        printf("\n=================================\n");
        printf("|  CADASTRO NEGADO PARA MENORES  |");
        printf("\n=================================\n");
    }
}

int main()
{
    int option = 1;
    carregar_arquivo();
    while (option != 0) {
        printf("\n==================================\n");
        printf("=========| POUSADA STRUCT |=======");
        printf("\n==================================\n");
        printf("[1] Check-in\t[4] Editar\n");
        printf("[2] Listagem\t[5] Check-out\n");
        printf("[3] Localizar\t[0] Finalizar");
        printf("\n==================================\n");
        printf("Opcao: ");
        scanf("%i", &option);

        switch (option) {
            case 1:
                if (qtd_registro >= 15) {
                    printf("\n====================================\n");
                    printf("| NAO HA VAGAS DISPONIVEIS NO MOMENTO |");
                    printf("\n====================================\n");
                } else {
                    cadastrar();
                }
                break;
            case 2:
                listagem();
                break;
            case 3:
                localizar();
                break;
            case 4:
                editar();
                break;
            case 5:
                excluir();
                break;
            case 0:
                printf("\n====================================\n");
                printf("| PROGRAMA FINALIZADO - VOLTE SEMPRE |");
                printf("\n====================================\n");
                break;
            default:
                printf("\n=================================\n");
                printf("|         OPCAO INVALIDA         |");
                printf("\n=================================\n");
                break;
        };
    };
    salvar_arquivo();
    return 0;
}
