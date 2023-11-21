
#include <stdio.h>
#include <stdlib.h>

struct proc_info
{
  int cpub;
  int atime;
  int flag;
} proc[20];

struct rqnode
 { int pid;
   struct rqnode *link;
 } *first=NULL, *curr, *prev, *last;

struct ganttchart
{
  int stime;
  int pid;
  int etime;
} gchart[20];

int i,n,ctime,gi=0,wtime[20]={0},ttime[20]={0};

void getprocs();
void start();
void addprocq();
void attachtoq(int);
void addgchart(int);
void dispgchart();
void calc_times();
void disptimes();

void main()
{ 
  getprocs();
  ctime=0; //set current time to 0
 
  start();
  dispgchart();
  disptimes();
}

void getprocs()
{ printf("\nHow many processes: "); scanf("%d",&n);
  printf("\nPID\tCPUB\tA.TIME\n");
  for (i=1; i<=n; i++)
  { printf("%d\t",i);
    scanf("%d%d",&proc[i].cpub,&proc[i].atime);
    proc[i].flag=0;
   }

}

void start(){
  int pid;
  addprocq();
  pid=getfirstproc();
  while(!finished()){
   if(pid!=-1){
    addgchart(pid);
    ctime++;
    proc[pid].cpub--;
    if(proc[pid].cpub==0){
     ttime[pid]+=(ctime-proc[pid].atime);
     if(proc[pid].flag==0){
      proc[pid].atime=ctime+2;
      ttime[pid]+=2;
      proc[pid].cpub=rand()%10;
      printf("\nProces %d with cpub %d arrive at %d",pid,proc[pid].cpub,proc[pid].atime);
      proc[pid].flag=1;
     }
     pid=getfirstproc();
    }
   }
   else{
    ctime++;
    pid=getfirstproc();
   }
   addprocq();
  }
  gchart[gi].etime=ctime;
}

void addprocq(){
  for(i=1;i<=n;i++){
    if(proc[i].atime==ctime)
    attachtoq(i);
   }
}

void attachtoq(int pid){
 curr=(struct rqnode *)malloc(sizeof(struct rqnode));
 curr->pid=pid;curr->link=NULL;
 if(first==NULL)
   first=curr;
 else
   last->link=curr;
 last=curr;
}

int finished(){
  for(i=1;i<=n;i++){
    if(proc[i].cpub!=0)
    return(0);
  }
  return(1);
}
int getfirstproc(){
  int pid;
  if(first==NULL)
    return(-1);
  pid=first->pid;
  curr=first;
  first=first->link;
  free(curr);
  return(pid);

}

void addgchart(int pid){
  static int ppid=-1;
  if(ppid!=pid){
    gchart[++gi].pid=pid;
    gchart[gi].stime=ctime;
    gchart[gi-1].etime=gchart[gi].stime;
    wtime[pid]+=(ctime-getetime(pid));
    ppid=pid;
 }
}

void dispgchart(){
  printf("\n");
  for(i=1;i<=gi;i++)
    printf("|----");
  printf("|\n");

  for(i=1;i<=gi;i++)
    printf("| %d  ",gchart[i].pid);
  printf("|\n");

  for(i=1;i<=gi;i++)
    printf("|----");
  printf("|\n");

  for(i=1;i<=gi;i++)
   printf("%d    ",gchart[i].stime);
  printf("%d\n",gchart[gi].etime);
}

getetime(int pid){
  for(i=gi-1;i>=1;i--)
  if(gchart[i].pid==pid)
    return(gchart[i].etime);
  return(proc[pid].atime);
}

void disptimes(){
  int sumwt=0,sumtt=0,pid;
  printf("\n**Waiting Time**");
  printf("\nPID\tWtime");
  for(i=1;i<=n;i++){
    printf("\n%d\t%d",i,wtime[i]);
    sumwt+=wtime[i];
  }
  printf("\nAverage:%.2f",(float)sumwt/n);

  printf("\n**Turnaround Time**");
  printf("\nPID\t ttime");
  for(i=1;i<=n;i++){
    printf("\n%d\t%d",i,ttime[i]);
    sumtt+=ttime[i];
  }
  printf("\nAverage:%.2f",(float)sumtt/n); 
}