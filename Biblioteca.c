#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct St_Livro
{
  char Nome[50];
  char Autor[50];
  int Codigo;
  struct St_Livro *Dir;
  struct St_Livro *Esq;
  struct St_Livro *Pai;
} Livro;

Livro *Arvore;

void ExibeArvore(Livro *Al, int Nivel)
{
  for (int cont = 0; cont < Nivel; cont++)
  {
    printf("--");
  }
  printf("> %s\n%s\n%d\n", Al->Nome, Al->Autor, Al->Codigo);
  if (Al->Esq != NULL)
  {
    ExibeArvore(Al->Esq, Nivel + 1);
  }
  if (Al->Dir != NULL)
  {
    ExibeArvore(Al->Dir, Nivel + 1);
  }
}

void ExibeArvoreNome(Livro *Al, char *nome, int *confirmar)
{
  if (strcmp(nome, Al->Nome) == 0)
  {
    printf("\n*****************LIVRO ENCONTRADO*********************\n");
    printf("\nNome: %s\n\nAutor: %s\nID: %d\n\n", Al->Nome, Al->Autor,
           Al->Codigo);
    printf("\n*****************************************************\n");
    printf("\n-----------------------------------------------------\n");
    printf("=====================================================\n");
    *confirmar = 1;
  }
  if (Al->Esq != NULL)
  {
    ExibeArvoreNome(Al->Esq, nome, confirmar);
  }
  if (Al->Dir != NULL)
  {
    ExibeArvoreNome(Al->Dir, nome, confirmar);
  }
}

void InsereElementoArvore(Livro *Raiz, Livro *Novo)
{
  if (Raiz == NULL)
  {
    Arvore = Novo;
    return;
  }
  Livro *Aux = Raiz;
  int Rep = 1;
  while (Rep == 1)
  {
    if (Aux->Codigo == Novo->Codigo)
    {
      printf("Livro ja cadastrado!\n");
      return;
    }
    if (Novo->Codigo > Aux->Codigo)
    {
      if (Aux->Dir == NULL)
      {
        Aux->Dir = Novo;
        Novo->Pai = Aux;
        Rep = 0;
      }
      else
      {
        Aux = Aux->Dir;
      }
    }
    else
    {
      if (Aux->Esq == NULL)
      {
        Aux->Esq = Novo;
        Novo->Pai = Aux;
        Rep = 0;
      }
      else
      {
        Aux = Aux->Esq;
      }
    }
  }
}

Livro *BuscaElementoArvore(Livro *Raiz, int InfoBusca)
{
  if (Raiz == NULL)
  {
    return NULL;
  }
  Livro *Aux = Raiz;
  while (Aux != NULL)
  {
    if (Aux->Codigo == InfoBusca)
    {
      return Aux;
    }
    if (InfoBusca > Aux->Codigo)
    {
      Aux = Aux->Dir;
    }
    else
    {
      Aux = Aux->Esq;
    }
  }
  return NULL;
}

int NoFolha(Livro *Elemento)
{
  if ((Elemento->Dir == NULL) && (Elemento->Esq == NULL))
  {
    return 1;
  }
  return 0;
}

void ExcluiRaizArvore(Livro *Raiz)
{
  Livro *Excluir = Raiz;
  if (NoFolha(Excluir))
  {
    printf("\n*****************LIVRO EXCLUÍDO**********************\n");
    printf("\nNome: %s\nAutor: %s\nID: %d\n\n", Excluir->Nome, Excluir->Autor,
           Excluir->Codigo);
    printf("\n*****************************************************\n");
    printf("\n-----------------------------------------------------\n");
    printf("=====================================================\n");
    free(Excluir);
    Arvore = NULL;
    return;
  }
  if ((Excluir->Esq == NULL && Excluir->Dir != NULL) ||
      (Excluir->Esq != NULL && Excluir->Dir == NULL))
  {
    if (Excluir->Esq == NULL)
    {
      Arvore = Excluir->Dir;
      Arvore->Pai = NULL;
    }
    else
    {
      Arvore = Excluir->Esq;
      Arvore->Pai = NULL;
    }
    printf("\n*****************LIVRO EXCLUÍDO**********************\n");
    printf("\nNome: %s\nAutor: %s\nID: %d\n\n", Excluir->Nome, Excluir->Autor,
           Excluir->Codigo);
    printf("\n*****************************************************\n");
    printf("\n-----------------------------------------------------\n");
    printf("=====================================================\n");
    free(Excluir);
    return;
  }
  if (NoFolha(Excluir->Dir))
  {
    Livro *Sub = Excluir->Dir;
    Sub->Esq = Excluir->Esq;
    Sub->Pai = NULL;
    Arvore = Sub;
    printf("\n*****************LIVRO EXCLUÍDO**********************\n");
    printf("\nNome: %s\nAutor: %s\nID: %d\n\n", Excluir->Nome, Excluir->Autor,
           Excluir->Codigo);
    printf("\n*****************************************************\n");
    printf("\n-----------------------------------------------------\n");
    printf("=====================================================\n");
    free(Excluir);
    return;
  }
  if (NoFolha(Excluir->Esq))
  {
    Livro *Sub = Excluir->Esq;
    Sub->Dir = Excluir->Dir;
    Sub->Pai = NULL;
    Arvore = Sub;
    printf("\n*****************LIVRO EXCLUÍDO**********************\n");
    printf("\nNome: %s\nAutor: %s\nID: %d\n\n", Excluir->Nome, Excluir->Autor,
           Excluir->Codigo);
    printf("\n*****************************************************\n");
    printf("\n-----------------------------------------------------\n");
    printf("=====================================================\n");
    free(Excluir);
    return;
  }
  Livro *Temp = Excluir->Esq;
  while (Temp->Dir != NULL)
  {
    Temp = Temp->Dir;
  }
  Livro *PaiTemp = Temp->Pai;
  if (Temp->Esq != NULL)
  {
    PaiTemp->Dir = Temp->Esq;
  }
  else
  {
    PaiTemp->Dir = NULL;
  }
  Temp->Dir = Excluir->Dir;
  Temp->Esq = Excluir->Esq;
  Temp->Pai = NULL;
  Arvore = Temp;
  printf("\n*****************LIVRO EXCLUÍDO**********************\n");
  printf("\nNome: %s\nAutor: %s\nID: %d\n\n", Excluir->Nome, Excluir->Autor,
         Excluir->Codigo);
  printf("\n*****************************************************\n");
  printf("\n-----------------------------------------------------\n");
  printf("=====================================================\n");
  free(Excluir);
  return;
}

int ElemDireita(Livro *Acima, Livro *Elemento)
{
  if (Acima->Codigo > Elemento->Codigo)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

void ExcluiElementoArvore(Livro *Raiz, int InfoBusca)
{
  Livro *Excluir;
  Excluir = BuscaElementoArvore(Raiz, InfoBusca);
  if (Excluir == NULL)
  {
    printf("Elemento não encontrado!\n");
    return;
  }
  else
  {
    if (Excluir->Codigo == Raiz->Codigo)
    {
      ExcluiRaizArvore(Raiz);
      return;
    }
    if (NoFolha(Excluir))
    {
      Livro *Aux = Excluir->Pai;
      if (Aux->Codigo > Excluir->Codigo)
      {
        Aux->Esq = NULL;
      }
      else
      {
        Aux->Dir = NULL;
      }
      printf("\n*****************LIVRO EXCLUÍDO**********************\n");
      printf("\nNome: %s\nAutor: %s\nID: %d\n\n", Excluir->Nome, Excluir->Autor,
             Excluir->Codigo);
      printf("\n*****************************************************\n");
      printf("\n-----------------------------------------------------\n");
      printf("=====================================================\n");
      free(Excluir);
      return;
    }
    if ((Excluir->Esq == NULL && Excluir->Dir != NULL) ||
        (Excluir->Esq != NULL && Excluir->Dir == NULL))
    {
      Livro *Aux = Excluir->Pai;
      if (Excluir->Esq == NULL)
      {
        if (Aux->Codigo > Excluir->Codigo)
        {
          Aux->Esq = Excluir->Dir;
        }
        else
        {
          Aux->Dir = Excluir->Dir;
        }
      }
      else
      {
        if (Aux->Codigo > Excluir->Codigo)
        {
          Aux->Esq = Excluir->Esq;
        }
        else
        {
          Aux->Dir = Excluir->Esq;
        }
      }
      printf("\n*****************LIVRO EXCLUÍDO**********************\n");
      printf("\nNome: %s\nAutor: %s\nID: %d\n\n", Excluir->Nome, Excluir->Autor,
             Excluir->Codigo);
      printf("\n*****************************************************\n");
      printf("\n-----------------------------------------------------\n");
      printf("=====================================================\n");
      free(Excluir);
      return;
    }
    Livro *Aux = Excluir->Pai;
    if (NoFolha(Excluir->Dir))
    {
      Livro *Subst = Excluir->Dir;
      if (ElemDireita(Aux, Excluir))
      {
        Aux->Dir = Subst;
      }
      else
      {
        Aux->Esq = Subst;
      }
      Subst->Esq = Excluir->Esq;
      printf("\n*****************LIVRO EXCLUÍDO**********************\n");
      printf("\nNome: %s\nAutor: %s\nID: %d\n\n", Excluir->Nome, Excluir->Autor,
             Excluir->Codigo);
      printf("\n*****************************************************\n");
      printf("\n-----------------------------------------------------\n");
      printf("=====================================================\n");
      free(Excluir);
      return;
    }
    if (NoFolha(Excluir->Esq))
    {
      Livro *Subst = Excluir->Esq;
      if (ElemDireita(Aux, Excluir))
      {
        Aux->Dir = Subst;
      }
      else
      {
        Aux->Esq = Subst;
      }
      Subst->Dir = Excluir->Dir;
      printf("\n*****************LIVRO EXCLUÍDO**********************\n");
      printf("\nNome: %s\nAutor: %s\nID: %d\n\n", Excluir->Nome, Excluir->Autor,
             Excluir->Codigo);
      printf("\n*****************************************************\n");
      printf("\n-----------------------------------------------------\n");
      printf("=====================================================\n");
      free(Excluir);
      return;
    }
    Livro *Temp = Excluir->Esq;
    while (Temp->Dir != NULL)
    {
      Temp = Temp->Dir;
    }
    Livro *PaiTemp = Temp->Pai;
    if (Temp->Esq != NULL)
    {
      PaiTemp->Dir = Temp->Esq;
    }
    else
    {
      PaiTemp->Dir = NULL;
    }
    Temp->Dir = Excluir->Dir;
    Temp->Esq = Excluir->Esq;
    Temp->Pai = Excluir->Pai;

    if (ElemDireita(Aux, Excluir))
    {
      Aux->Dir = Temp;
    }
    else
    {
      Aux->Esq = Temp;
    }
    printf("\n*****************LIVRO EXCLUÍDO**********************\n");
    printf("\nNome: %s\nAutor: %s\nID: %d\n\n", Excluir->Nome, Excluir->Autor,
           Excluir->Codigo);
    printf("\n*****************************************************\n");
    printf("\n-----------------------------------------------------\n");
    printf("=====================================================\n");
    free(Excluir);
    return;
  }
}

int main()
{
  setlocale(LC_ALL, "Portuguese");
  int i = 0;
  int j = 0;
  int criterio;
  int p;
  char n[50];
  Livro *L1;
  int confirmar;

  printf("=====================================================\n");
  printf("------------------TELA DE CADASTRO-------------------\n");
  printf("\nFazer cadastro? (1 - SIM \t 2 - NÃO)\n");
  printf("\n");
  scanf("%d", &i);
  printf("\n");
  printf("-----------------------------------------------------\n");
  printf("=====================================================\n");

  if (i == 2)
  {
    printf("-----------------------------------------------------\n");
    printf("\nProcedimento encerrado. Tenha um bom dia!\n");
    printf("\n");
    printf("-----------------------------------------------------\n");
    printf("=====================================================\n");
    return 0;
  }
  while (i != 5)
  {
    printf("\n\n");
    printf("=====================================================\n");
    printf("----------------------CADASTRO-----------------------\n");
    printf("\n1 - Cadastrar \t 2 - Excluir \t 3 - Exibir\n \n4 - Buscar "
           "\t \t 5 - Sair\n\n");
    scanf("%d", &i);
    printf("\n-----------------------------------------------------\n");
    printf("=====================================================\n");

    if (i == 5)
    {
      printf("-----------------------------------------------------\n");
      printf("\nProcedimento encerrado. Tenha um bom dia!\n");
      printf("\n");
      printf("-----------------------------------------------------\n");
      printf("=====================================================\n");
      return 0;
    }

    switch (i)
    {
    case 1:
      printf("\n\n");
      printf("=====================================================\n");
      printf("----------------------CADASTRO-----------------------\n");
      L1 = (Livro *)malloc(sizeof(Livro));
      L1->Esq = NULL;
      L1->Dir = NULL;
      L1->Pai = NULL;
      printf("\nNome: ");
      getchar();
      fgets(L1->Nome, sizeof(L1->Nome), stdin);
      printf("\nAutor: ");
      fgets(L1->Autor, sizeof(L1->Autor), stdin);
      printf("\nID: ");
      scanf("%d", &L1->Codigo);
      InsereElementoArvore(Arvore, L1);
      printf("\n-----------------------------------------------------\n");
      printf("=====================================================\n");
      break;

    case 2:
      if (Arvore == NULL)
      {
      }
      else
      {
        printf("\n\n");
        printf("=====================================================\n");
        printf("------------------TELA DE EXCLUSÃO-------------------\n");
        printf("\nDigite o número do Livro que deseja excluir: \n");
        scanf("%d", &p);
        ExcluiElementoArvore(Arvore, p);
        break;
      }

    case 3:
      if (Arvore == NULL)
      {
        printf("\n\t\t\t----------------------------\n");
        printf("\t\t\tNenhum Livro foi cadastrado!");
        printf("\n\t\t\t----------------------------\n");
      }
      else
      {
        printf("\n\n");
        printf("=====================================================\n");
        printf("------------------TELA DE EXIBIÇÃO------------------\n");
        ExibeArvore(Arvore, 0);
      }
      break;

    case 4:
      if (Arvore == NULL)
      {
        printf("\n\t\t\t----------------------------\n");
        printf("\t\t\tNenhum livro foi cadastrado!");
        printf("\n\t\t\t----------------------------\n");
      }
      else
      {
        printf("\n\n");
        printf("=====================================================\n");
        printf("------------------TELA DE BUSCA------------------\n");
        printf("\nDeseja buscar por:\n\n1 - Nome\t\t2 - Código\n\n");
        scanf("%d", &criterio);
        if (criterio == 1)
        {
          printf("\nDigite o nome:");
          getchar();
          fgets(n, sizeof(n), stdin);
          ExibeArvoreNome(Arvore, n, &confirmar);
          if (confirmar == 0)
          {
            printf("\n\t\t\t----------------------------\n");
            printf("Livro não encontrado!");
            printf("\n\t\t\t----------------------------\n");
          }
          confirmar = 0;
          printf("\n-----------------------------------------------------\n");
          printf("=====================================================\n");
        }
        if (criterio == 2)
        {
          printf("\nDigite o código:");
          scanf("%d", &p);
          L1 = BuscaElementoArvore(Arvore, p);
          if (L1 == NULL)
          {
            printf("\n\t\t\t----------------------------\n");
            printf("Livro não encontrado!");
            printf("\n\t\t\t----------------------------\n");
          }
          else
          {
            printf(
                "\n*****************LIVRO ENCONTRADO*********************\n");
            printf("\nNome: %s\nAutor: %s\nID: %d\n\n", L1->Nome, L1->Autor,
                   L1->Codigo);
            printf("\n*****************************************************\n");
            printf("\n-----------------------------------------------------\n");
            printf("=====================================================\n");
            printf("\n-----------------------------------------------------\n");
            printf("=====================================================\n");
          }
        }
        break;
      }
    }
  }
  return 0;
}