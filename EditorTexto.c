#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Conio.h>
#include <unistd.h>
/****
 * Editor de Texto
 * Alunos : Leandro,Caique,Gabriel
 */
#define MAX_TAM 30

//Estrutura da lista duplamente encadeada
typedef struct Node
{
     char content[MAX_TAM + 1]; //Linha de texto com no maximo 30 caracteres
     struct Node *prev;
     struct Node *next;
}Node;

//Inicia a lista
Node *criar_nodo(const char *text)
{
     Node *novo = (Node *)malloc(sizeof(Node)); //alocar memoria
     if(!novo) //Erro em alocar memoria
     {
          printf("ERRO!!");
          exit(1);    
     }
     strncpy(novo -> content, text, MAX_TAM);
     novo -> content[MAX_TAM] = '\0'; //Garante terminacao da string
     novo -> prev = NULL;
     novo -> next = NULL;
     return novo;
}

//Funcao para adicionar a linha
void add_linha(Node **head, Node **tail, const char *text)
{
     Node *novo = criar_nodo(text);
     if(*tail)
     {
          (*tail)->next = novo;
          novo->prev = *tail;
          *tail = novo;     
     }
     else
     {
          *head = *tail = novo;
     }
}

void display_conteudo(Node *head, Node *cursor) {
     system("cls");
     printf("Modo de Comando:\n 'i' para inserir\n'j' para voltar linha\n 'l' para avançar linha\n 'k' adiciona linh\n ':w' salvar arquivo\n ':q'fecha o programa\n");
     printf("--- Conteudo do Arquivo ---\n");
     Node *atual = head;
     while (atual) {
          if (atual == cursor) {
               printf("> %s\n", atual->content);//linha onde esta o cursor
          } else {
               printf(" %s\n", atual->content);
          }
          atual = atual->next;
     }
     printf("------------------\n");
}
//Mover cursos
Node* mover_cursor(Node *cursor, int passos)
{
     if (passos > 0 && cursor ->next) {
          return cursor->next;
     } else if (passos < 0 && cursor ->prev) {
          return cursor -> prev;
     }
     return cursor;              
}
//Salvar arquivo
void salvar_arquivo(Node *head, const char *fileName)
{
 FILE *file = fopen(fileName, "w"); //abre o arquivo
 
 if(!file) //Verifica se  diferente do arquivo 
 {
  printf("Erro ao abrir o arquivo\n");
  return;
 }
 
 Node *atual = head;
 while(atual)
 {
  fprintf(file, "%s\n", atual -> content);
  atual = atual -> next;           
 }
 
 fclose(file);
 printf("Arquivo salvo como '%s'\n", fileName);
}


//Funcao principal/Menu
int main()
{
     Node *head = NULL, *tail = NULL, *cursor = NULL; //funcoes que se relacionam ao nodo, sendu uma delas o cursor
     char buffer[MAX_TAM + 1];
     char fileName[100] = "arquivo.txt";
     int op = 1;

     add_linha(&head, &tail, "");
     cursor = head;
 
     while (op) {
          display_conteudo(head,cursor);
          char c = getch();

          if ( c == 'i') {
          printf("\n Digite o Texto (Maximo 30 caracteres)\n");
          printf("> ");
          fgets(buffer, MAX_TAM + 1, stdin); //Le a string
          buffer[strcspn(buffer,"\n")] = '\0'; //Remove o '\n'
          strncpy(cursor->content, buffer, MAX_TAM);
            cursor->content[MAX_TAM] = '\0';
     } else if (c == ':') {
          printf(":");
          char command = getch();
          if (command == 'q') { // comando sair
               op = 0;
          } else if (command == 'w') { // Salvar
               salvar_arquivo(head, fileName);
          }
     } else if (c == 'l') { // proxima linha
          cursor = mover_cursor(cursor, 1);
     } else if (c == 'j') {// volta linha
          cursor = mover_cursor(cursor, -1);
     } else if (c == 'k') { // adiciona nova linha
          Node *novo = criar_nodo("");
          novo->next = cursor->next;
          novo->prev = cursor;
          if (cursor->next) {
               cursor->next->prev = novo;
          } else {
               tail = novo;
          }
          cursor->next = novo;
          cursor = novo;
     } 
}

     while (head) // limpar memoria
     {
          Node *temp = head;
          head = head->next;
          free(temp);
     }
     return 0;
}
     
