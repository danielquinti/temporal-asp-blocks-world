#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "queue.h"
#define MAXLINE 4096

QUEUE t,ini=qEMPTY,goal=qEMPTY;
char quiet=0;

int cmpTowers(void *a,void *b) {
  int x=*qFirst(*(QUEUE *)a,int);
  int y=*qFirst(*(QUEUE *)b,int);
  if (x<y) return -1;
  if (x>y) return 1;
  return 0;
}

QUEUE get_tower(char *line) {
  QUEUE q=qEMPTY;
  char *p;
  int n;
  for (p=strtok(line," \n"); p!=NULL ; p=strtok(NULL," \n")) {
    n=atoi(p); qPUSH(&q,&n,int);
  }
  return q;
}

int printInt(QUEUE q,void *data) {
  printf("%d ",*qFirst(q,int));
  return 0;
}
void print_tower(QUEUE t) {
  unsigned int n;
  int *a,i;
  a=(int*)Queue2Array(t,sizeof(int),&n);
  for (i=n-1;i>=0;i--)
    printf("%d ",a[i]);
  printf("\n");
}

int printTower(QUEUE q,void *data) { 
  print_tower(*qFirst(q,QUEUE));
  return 0;
}

void print_state(QUEUE q) {
  if (quiet) return;
  qBrowse(q,printTower,NULL); printf("\n");
}

void execute_action(QUEUE *q,char *line) {
  char *p=strtok(line,"(");
  int a,b,c;
  QUEUE towers=qEMPTY,t,ta,tb;
  t=ta=tb=qEMPTY;
  p=strtok(NULL,","); a=atoi(p);
  p=strtok(NULL,")"); b=atoi(p);
  if(!quiet) printf("move %d -> %d\n",a,b);
  while (!qIsEmpty(*q)) {
    qPOP(q,&t,QUEUE);
    c=*qFirst(t,int);
    if (c==a) ta=t;
    else if (c==b) tb=t;
    else qInsertLast(&towers,&t,sizeof(QUEUE));			
  }
  if (qIsEmpty(ta)) {
    printf("block %d is not clear\n",a); exit(0);
  }
  qPOP(&ta,&c,int);
  if (!qIsEmpty(ta))
    qOrderedInsert(&towers,&ta,sizeof(QUEUE),cmpTowers,0);
  qPUSH(&tb,&c,int);
  qOrderedInsert(&towers,&tb,sizeof(QUEUE),cmpTowers,0);
  *q=towers;
}


int main (int argc,char *argv[]) {
  char *fileName;
  char line[MAXLINE];
  int n,a,b;
  FILE *f;
  QUEUE t2;
  
  if (argc<3 || argc>4 || (argc==4 && strcmp(argv[3],"-q")!=0))
    { printf("checker <domainfile> <solutionfile> [-q]\n"); exit(1); }
  if (argc==4) quiet=1;
  fileName=argv[1];
  if ((f=fopen(argv[1],"r"))==NULL)
  { printf("Error opening file %s\n",fileName); exit(1); }
  fscanf(f,"%d\n",&n);
  while (fgets(line,MAXLINE,f)!=NULL) {
    t=get_tower(line);
    if (qIsEmpty(t)) break;
    qOrderedInsert(&ini,&t,sizeof(QUEUE),cmpTowers,0);
  }
  while (fgets(line,MAXLINE,f)!=NULL) {
    t=get_tower(line);
    qOrderedInsert(&goal,&t,sizeof(QUEUE),cmpTowers,0);
  }
  fclose(f);
  fileName=argv[1];
  if ((f=fopen(argv[2],"r"))==NULL)
  { printf("Error opening file %s\n",fileName); exit(1); }
  print_state(ini);
  while (fgets(line,MAXLINE,f)!=NULL) {
    execute_action(&ini,line);
    print_state(ini);
  }
  fclose(f);
  while (!qIsEmpty(ini)) {
    qPOP(&ini,&t,QUEUE);
    if (qIsEmpty(goal)) {
      printf("Final state is not goal.\n"); exit(0);
    }
    qPOP(&goal,&t2,QUEUE);
    while (!qIsEmpty(t)) {
      qPOP(&t,&a,int);
      if (qIsEmpty(t2)) {
        printf("Final state is not goal.\n"); exit(0);
      }
      qPOP(&t2,&b,int);
      if (a!=b) {
        printf("Final state is not goal.\n"); exit(0);
      }
    }
  }
  printf("Solution ok.\n");
  return 0;
}
