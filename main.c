#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct st_palestrantes;
struct st_evento;

typedef struct st_palestrantes{
  char nome[30], email[30];
  int codigoP;
  struct st_palestrantes *prox;
}Palestrantes;

typedef struct st_descritor{
  Palestrantes *primeiro;
  int numelemP;
}DesPales;

typedef struct st_evento{
  char nome[30], areaTema[30];
  int codigoE, dia, mes, ano, data;
  struct st_evento *prox;
  struct st_evento *ant;
  DesPales listaSimples;
}Evento;

typedef struct st_descritorEvento{
  Evento *primeiro;
  Evento *ultimo;
  DesPales *lista;
  int numelemEve;
}DesEvento;

int Retorno(){
  int opcao;
  printf("\nDeseja voltar ao menu anterior? ");
  printf("\n1 - Sim");
  printf("\n2 - Não");
  printf("\nOpção: ");
  scanf("%d", &opcao);
  return opcao;
}

int main(void) {
  int opcao, busca;
  Evento *aux, *eventoAtual;
  DesEvento lista;
  lista.numelemEve=0;
  lista.primeiro=NULL;
  lista.ultimo=NULL;

  
  /*Palestrantes *auxPales=NULL;
  aux->listaSimples.primeiro=NULL;
  aux->listaSimples.numelemP=0;
  */
  while(opcao!=6){
    printf("\n\tGERENCIADOR DE EVENTOS ACADÊMICOS\n");
    printf("\n1 - Incluir evento");
    printf("\n2 - Excluir evento");
    printf("\n3 - Listar todos os eventos");
    printf("\n4 - Listar eventos por data");
    printf("\n5 - Gerenciar evento");
    printf("\n6 - Sair");
    printf("\nOpcao: ");
    scanf("%d", &opcao);
    switch(opcao){
      case 1:
        opcao=2;
        while(opcao==2){
          printf("\n\tNovo Evento\n");
          int cod;
          printf("\nDigite o código do evento: ");
          scanf("%d", &cod);
          aux=lista.primeiro;
          while(aux!=NULL){
            if(cod == aux->codigoE){
              printf("\nCódigo já cadastrado!\n");
              break;
            }
            aux=aux->prox;
          }
          if(aux!=NULL){
            break;
          }
          aux=(Evento*) calloc(1, sizeof(Evento));
          aux->listaSimples.primeiro=NULL;
          aux->listaSimples.numelemP=0;
          
          aux->codigoE=cod;
          printf("Digite o nome: ");
          scanf("%s", aux->nome);
          printf("Digite a área temática do evento: ");
          scanf("%s", aux->areaTema);
          printf("Digite a dia do evento(DD): ");
          scanf("%d", &aux->dia);
          if(aux->dia<1 ||aux->dia>32){
            printf("\nDia inválido\n");
            break;
          }
          printf("Digite o mês do evento(MM): ");
          scanf("%d", &aux->mes);
          if(aux->mes<1 ||aux->mes>13){
            printf("\nMês inválido\n");
            break;
          }
          printf("Digite o ano do evento(AAAA): ");
          scanf("%d", &aux->ano);
          if(aux->ano<0){
            printf("\nAno inválido\n");
            break;
          }
          aux->data=(aux->dia)+(aux->mes*30)+(aux->ano*365);
          lista.numelemEve++;
          if(lista.primeiro==NULL){
            lista.primeiro=aux;
            lista.ultimo=aux;
          }else{
            eventoAtual=lista.primeiro;
            if(aux->data<=eventoAtual->data){
              aux->prox=eventoAtual;
              eventoAtual->ant=aux;
              lista.primeiro=aux;
              aux->ant=NULL;
            }else{
              eventoAtual=lista.primeiro;
              while(eventoAtual!=NULL){
                if(aux->data>=eventoAtual->data){
                  eventoAtual=eventoAtual->prox;
                }else{
                  Evento *temp;
                  temp=eventoAtual->ant;
                  temp->prox=aux;
                  eventoAtual->ant=aux;
                  aux->prox=eventoAtual;
                  aux->ant=temp;
                  break;
                }
              }
              if(eventoAtual==NULL){
                aux->ant=lista.ultimo;
                lista.ultimo->prox=aux;
                lista.ultimo=aux;
                aux->prox=NULL;
              }
            }
          }
          opcao=Retorno();
        }
      break;
      case 2:
        if(lista.numelemEve==0){
          printf("\nLista Vazia!\n");
          continue;
        }
        opcao=2;
        while(opcao==2){
          printf("\n\tExcluir Evento\n");
          printf("\nDigite o código do evento: ");
          scanf("%d", &busca);
          aux=lista.primeiro;
          while(aux!=NULL){
            if(aux->codigoE==busca){
              if(lista.numelemEve==1){
                lista.primeiro=NULL;
                lista.ultimo=NULL;
              }else if(aux->ant==NULL){
                lista.primeiro=aux->prox;
                aux->prox->ant=NULL;
              }else if(aux->prox==NULL){
                lista.ultimo=aux->ant;
                aux->ant->prox=NULL;
              }else{
                aux->ant->prox=aux->prox;
                aux->prox->ant=aux->ant;
              }
              Palestrantes *auxP, *temp;
              temp=aux->listaSimples.primeiro;
              while(temp!=NULL){
                auxP=temp;
                temp=temp->prox;
                free(temp);
              }
              lista.numelemEve--;
              printf("\nCurso '%s' excluido com sucesso\n", aux->nome);
              free(aux);
              break;
            }
            aux=aux->prox;
          }
          if(aux==NULL){
            printf("\nCódigo %d não encontrado!\n", busca);
          }
          opcao=Retorno();
        }
      break;
      case 3:
        if(lista.numelemEve==0){
          printf("\nLista Vazia!\n");
          continue;
        }
        opcao=2;
        while(opcao==2){
          aux=lista.primeiro;
          printf("\n\tLISTA DE EVENTOS\n");
          while(aux!=NULL){
            printf("\nNome: %s", aux->nome);
            printf("\nCódigo: %d", aux->codigoE);
            printf("\nÁrea temática: %s", aux->areaTema);
            printf("\nData: %d/%d/%d\n", aux->dia, aux->mes, aux->ano);
            aux=aux->prox;
          }
          printf("\n");
          opcao=Retorno();
        }
      break;
      case 4:
        if(lista.numelemEve==0){
          printf("\nLista Vazia!\n");
          continue;
        }
        opcao=2;
        while(opcao==2){
          int existe=0;
          printf("\n\tListar eventos por data\n");
          printf("\nDigite o mês dos eventos(MM): ");
          scanf("%d", &busca);
          if(busca<1||busca>12){
            printf("\nMês Inválido\n");
            continue;
          }
          aux=lista.primeiro;
          while(aux!=NULL){
            if(aux->mes==busca){
              existe=1;
              printf("\nNome: %s", aux->nome);
              printf("\nCódigo: %d", aux->codigoE);
              printf("\nÁrea temática: %s", aux->areaTema);
              printf("\nData: %d/%d/%d\n", aux->dia, aux->mes, aux->ano);
            }
            aux=aux->prox;
          }
          if(existe==0){
            printf("\nNão existe eventos para o mês %d\n", busca);
          }
          opcao=Retorno();
        }
      break;
      case 5:        
        if(lista.numelemEve==0){
          printf("\nLista Vazia!\n");
          continue;
        }
        Palestrantes *auxPales=NULL;
        opcao=2;
        while(opcao==2){
          printf("\n\tGERENCIAR EVENTO\n");
          printf("\nDigite o código do evento: ");
          scanf("%d", &busca);
          aux=lista.primeiro;
          while(aux!=NULL){
            if(aux->codigoE==busca){
              break;
            }
            aux=aux->prox;
          }
          if(aux==NULL){
            printf("\nCódigo '%d' não encontrado\n", busca);
          }else{
            while(opcao!=4){
              printf("\n\tGerenciando evento '%s' \n", aux->nome);
              printf("\n1 - Cadastrar palestrante");
              printf("\n2 - Excluir palestrante");
              printf("\n3 - Listar palestrantes");
              printf("\n4 - Voltar");
              printf("\nOpção: ");
              scanf("%d", &opcao);
              switch(opcao){
                case 1:
                  opcao=2;
                  while(opcao==2){
                    printf("\n\tNOVO PALESTRANTE\n");
                    int cod;
                    printf("\nDigite o código do palestrante: ");
                    scanf("%d", &cod);
                    auxPales=aux->listaSimples.primeiro;
                    while(auxPales!=NULL){
                      if(auxPales->codigoP==cod){
                        printf("\nCódigo já cadastrado\n");
                        break;
                      }
                      auxPales=auxPales->prox;
                    }
                    if(auxPales!=NULL){
                      break;
                    }
                    
                    auxPales=(Palestrantes*) calloc(1, sizeof(Palestrantes));
                    auxPales->codigoP=cod;
                    printf("Digite o nome do palestrante: ");
                    scanf("%s", auxPales->nome);
                    printf("Digite o e-mail do palestrante: ");
                    scanf("%s", auxPales->email);
   
                    auxPales->prox=NULL;
                    aux->listaSimples.numelemP++;                   
                    
                    Palestrantes *Patual, *Panterior;                
                    Patual=aux->listaSimples.primeiro;
                    
                    if(aux->listaSimples.primeiro==NULL){
                      aux->listaSimples.primeiro=auxPales;
                    }else if(strcmp(auxPales->nome, Patual->nome)<0){
                      auxPales->prox=Patual;
                      Patual=auxPales;
                    }else{
                      Panterior=aux->listaSimples.primeiro;
                      Patual=Patual->prox;
                      while(Patual!=NULL){
                        if(strcmp(auxPales->nome, Patual->nome)<0){
                          Panterior->prox=auxPales;
                          auxPales->prox=Patual;
                          break;
                        }
                        Panterior=Patual;
                        Patual=Patual->prox;
                      }
                      if(Patual==NULL){
                        Panterior->prox=auxPales;
                      }
                    }
                    opcao=Retorno();
                  }
                break;
                case 2:
                  if(aux->listaSimples.numelemP==0){
                    printf("\nLista Vazia!\n");
                    continue;
                  }
                  opcao=2;
                  while(opcao==2){
                    printf("\n\tEXCLUIR PALESTRANTE\n");
                    printf("\nDigite o código do palestrante: ");
                    scanf("%d", &busca);
                    
                    Palestrantes *Patual, *Panterior; 
                    Patual=aux->listaSimples.primeiro;
                    if(busca==Patual->codigoP){
                      aux->listaSimples.primeiro=Patual->prox;
                      printf("\nPalestrante '%s' excluido\n", Patual->nome);
                      free(Patual);
                      aux->listaSimples.numelemP--;
                    }else{
                      Patual=aux->listaSimples.primeiro;
                      while(Patual!=NULL){
                        if(Patual->codigoP==busca){
                          Panterior->prox=Patual->prox;
                          printf("\nPalestrante '%s' excluido\n", Patual->nome);
                          free(Patual);
                          aux->listaSimples.numelemP--;
                          break;
                        }
                        Panterior=Patual;
                        Patual=Patual->prox;
                      }                      
                    }
                    if(Patual==NULL){
                      printf("\nCódigo '%d' não encontrado\n", busca);
                    }
                    opcao=Retorno();
                  }
                break;
                case 3:
                  if(aux->listaSimples.numelemP==0){
                    printf("\nLista Vazia!\n");
                    continue;
                  }
                  opcao=2;
                  while(opcao==2){
                    auxPales=aux->listaSimples.primeiro;
                    printf("\n\tPalestrantes do evento '%s'\n", aux->nome);
                    while(auxPales!=NULL){
                      printf("\nNome: %s", auxPales->nome);
                      printf("\nCódigo: %d", auxPales->codigoP);
                      printf("\nE-mail: %s\n", auxPales->email);
                      auxPales=auxPales->prox;
                    }
                    opcao=Retorno();
                  }
                break;
                case 4:
                  //Opção para voltar
                break;
                default:
                  printf("\nOpção Invalida!\n");
                  printf("Por favor digite uma opção valida\n");
                break;
              }
            } 
          }
          opcao=Retorno();
        }
      break;
      case 6:
        printf("\nAplicação Finalizada!\n");
      break;
      default:
        printf("\nOpção Invalida!\n");
        printf("Por favor digite uma opção valida\n");
      break;
    }
  }
}