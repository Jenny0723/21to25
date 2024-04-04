#include <stdlib.h>
#include "copyright.h"
#include "dllist.h"
#include "system.h"
#include <time.h>

void Insert(int t, int n, DLList *dllist)
{
    int i, ll;
    srand(time(0));
    for (i=0; i<n; i++)
    {
        ll = rand()%101;	
	    printf("Thread %d : inserted key=%d.........\n", t, ll);
        dllist -> SortedInsert(NULL, ll);
        printf("Thread %d : inserted key=%d complete\n", t, ll);
        dllist -> ShowList();
    }
    // dllist -> ShowList();
}

void Remove(int t, int n, DLList *dllist)
{
    int i, keyll;
    for (i=0; i<n; i++)
    {
        // printf("Thread %d : removed key=%d.........\n", t, keyll);
        printf("Thread %d : removed key............\n", t);
        dllist -> Remove(&keyll);
        printf("Thread %d : removed key=%d complete\n", t, keyll);
        dllist -> ShowList();
    }
    //  dllist -> ShowList();
}
