
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

char nome[100];
int cpf;
int telefone;
char email;
int cep;
char end[100];

FILE *fp;

int main()
{
setlocale(LC_ALL, "Portuguese");
int ano, nascimento;
int resp_subtracao;
char doenca[100];

struct tm *data_hora_atual;

  time_t segundos;

  time(&segundos);

  data_hora_atual = localtime(&segundos);

    int total_contas = 0, arq_tamanho = 0, op = 0, i;

    struct usuarios_infos {
        char login[10];
        char senha[10];
    };

    struct usuarios_infos usuario_cadastrado, *lista_de_contas;


    FILE* logs;

    while (op != 3){

        printf("\n *** SISTEMA DE CONTROLE COVID19 *** \n");


        printf("\n 1 - Cadastrar nova conta\n");
        printf(" 2 - Fazer login\n");
        printf(" 3 - Sair\n");

        printf("\nESCOLHA A OPÇÃO: ");
        scanf("%d%*c", &op);

        switch(op){
            case 1:
                logs = fopen ("contas.txt","a");
                if(logs == NULL)
                {
                    printf("\nErro ao tentar abrir o arquivo.\n\n");
                }
                else
                {
                    memset(&usuario_cadastrado,0,sizeof(struct usuarios_infos));
                    printf("Cadastrar usuario: ");
                    scanf("%s", usuario_cadastrado.login);
                    printf("Cadastrar senha: ");
                    scanf("%s", usuario_cadastrado.senha);
                    fwrite(&usuario_cadastrado, sizeof usuario_cadastrado, 1, logs);
                    fclose(logs);
                }
                break;

            case 2:
                memset(&usuario_cadastrado, 0, sizeof(struct usuarios_infos));
                printf("\nUSUÁRIO: ");
                scanf("%s", usuario_cadastrado.login);
                printf("SENHA: ");
                scanf("%s", usuario_cadastrado.senha);

                logs = fopen ("contas.txt","rb");
                if(logs == NULL)
                {
                    printf("\nErro ao tentar abrir o arquivo.\n\n");
                }
                else
                {
                    fseek(logs,0,SEEK_END);
                    arq_tamanho = ftell(logs);
                    total_contas = arq_tamanho / sizeof (struct usuarios_infos);
                    rewind(logs);
                    lista_de_contas = malloc(arq_tamanho);
                    if(fread(lista_de_contas, sizeof usuario_cadastrado, total_contas, logs) != total_contas)
                    {
                        printf("Falha ao tentar ler contas\n");
                        fclose(logs);
                        free(lista_de_contas);
                        return 1;
                    }
                    fclose(logs);
                    for (i=0; i<total_contas; i++){
                        if(memcmp(&usuario_cadastrado, &lista_de_contas[i], sizeof(struct usuarios_infos)) == 0)
                        {
                            printf("\n ACESSO LIBERADO... \n");


                            printf("\n ENTRE COM AS INFORMAÇÕES DO PACIENTE \n");

                            printf(" \n Ano atual: ");
                            scanf("%d", &ano);

                            printf(" Nome: ");
                            scanf(" %[^\n]d ", &nome);

                            printf(" Ano nascimento (1900): ");
                            scanf("%d", &nascimento);

                            resp_subtracao = ano-nascimento;
                            printf(" Idade: %d\n", resp_subtracao);

                            printf(" Endereço: ");
                            scanf(" %[^\n]d ", &end);

                            printf(" CPF: ");
                            scanf(" %[^\n]d " , &cpf);

                            printf(" Telefone: ");
                            scanf(" %[^\n]d ", &telefone);

                            printf(" E-mail: ");
                            scanf("%s", &email);

                            printf(" CEP: ");
                            scanf(" %[^\n]d ", &cep);

                            if (resp_subtracao <=65)
                            {
      		                      printf("\n PACIENTE NÃO ESTÁ NO GRUPO DE RISCO \n ");
                                printf("\n GERADO APENAS DADOS PARA REGISTRO DO CASO \n");

                                FILE *paci_arq;

                                paci_arq = fopen("Acompanhamento Paciente", "w");

                                fprintf(paci_arq,"\n\nDADOS PARA APENAS CONTROLE DO PACIENTE\n\n");

                                fprintf(paci_arq, "%s", "Nome: ");
                                fprintf(paci_arq, "%s\n", nome);

                                fprintf(paci_arq, "\n%s", "Idade: ");
                                fprintf(paci_arq,"%d", resp_subtracao);

                                fprintf(paci_arq, "\n%s", "CEP: ");
                                fprintf(paci_arq,"%d", cep);

                                fprintf(paci_arq,"\nData do diagnóstico: %d/", data_hora_atual->tm_mday);
                                fprintf(paci_arq,"%d/",data_hora_atual->tm_mon+1); //mês
                                fprintf(paci_arq,"%d\n\n",data_hora_atual->tm_year+1900); //ano

                                fclose(paci_arq);
      	                    }
	                          else
      	                    {
      		                  printf("\n*** PACIENTE DO GRUPO DE RISCO *** \n");

                                FILE *pont_arq;


                                pont_arq = fopen("Paciente Comorbidade", "w");

                                fprintf(pont_arq,"\n\nDADOS PARA CONTROLE DO PACIENTE COM COMORBIDADE\n\n");

                                printf("\n Digite a comorbidade: ");
                                scanf(" %[^\n]d ", &doenca);

                                fprintf(pont_arq, "%s", "Nome: ");
                                fprintf(pont_arq, "%s\n", nome);

                                fprintf(pont_arq, "\n%s", "Idade: ");
                                fprintf(pont_arq, "%d", resp_subtracao);

                                fprintf(pont_arq, "\n%s", "Comorbidade: ");
                                fprintf(pont_arq, "%s", doenca);

                                fprintf(pont_arq, "\n%s", "CEP: ");
                                fprintf(pont_arq,"%d", cep);

                                fprintf(pont_arq,"\nData do diagnóstico: %d/", data_hora_atual->tm_mday);
                                fprintf(pont_arq,"%d/",data_hora_atual->tm_mon+1); //mês
                                fprintf(pont_arq,"%d\n\n",data_hora_atual->tm_year+1900); //ano

                                fclose(pont_arq);

                             printf("\n\n ++ GERADO DADOS DO PACIENTE PARA A SECRETARIA DA SAÚDE ++ \n\n\n");

      	                    }
                            break;
                        }

                    }
                    if(i == total_contas)
                    {
                        printf("\n ACESSO NEGADO...\n");
                    }
                    free(lista_de_contas);
                }
                break;


            case 3:
                printf("\n OBRIGADO POR USAR O SISTEMA \n");
                break;


            default:
                printf("\n Opcao invalida!\n");
        }
    }

    return 0;
}
