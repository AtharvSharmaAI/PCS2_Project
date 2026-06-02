#include "types.h"      
#include "user.h"
#include "stat.h"

int main(int argc, char *argv[]) 
{ 
    //printf(1, "Hey, I am trying xv6\n"); 
    printf(1 , "memory size is %d\n", memsize());
    printf(1, "Virtual Pages are %d\n", vpage());
    printf(1, "No of entries in page table is %d\n", pagetable_entries());
    exit();
}
