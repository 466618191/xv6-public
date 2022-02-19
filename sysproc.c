#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}
/*

|         |   
|_________|
|_________|
|__status_|  1
|_pid_____| 0







*/
int
sys_exit2(void)
{                                               
               
int status;
if(argint(0,&status)<0)
{
  return -1;
}
exit2(status);
return 0;


  // exit();
  // return 0;  // not reached
}
/////////////////////////////////////////////////////////////////

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}


int
sys_wait(void)
{
  int* status;
  //get a pointer
  if(argptr(0,(void*)&status, sizeof(status)) < 0){
    return -1;
  }

  return wait(status);
}

int 
sys_waitpid(void)
{
  int *status;
int pid;
int option=0;
// for pointer
if(argptr(1,(void*)&status, sizeof(status)) < 0){
    return -1;
  }


// for argument:
if(argint(0,&pid)<0)
{
  return -1;
}
return waitpid(pid,status,option);

}



int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
int
sys_add(void)
{
int a =1;
int b=2020;
return a+b;


}

int
sys_setpriority(void)
{
  int prior;
  //like lab 1 grab argument form position 0
  if(argint(0, &prior) < 0){
    return -1;
  }
  return setpriority(prior);
}

int
sys_get_prior(void)
{
  return get_prior();
}
