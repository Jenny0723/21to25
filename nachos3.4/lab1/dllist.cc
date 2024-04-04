#include "dllist.h"
#include "copyright.h"
#include "system.h"

DLLElement::DLLElement(void *itemPtr, int sortKey) // initialize a list element
{
    item = itemPtr;
    key = sortKey;
    next = NULL;
    prev = NULL;
}
/*
DLList::DLLIst()    // initialize the list
{
    first = NULL;
    last = NULL;
    err_type = 0;
}*/

DLList::DLList(int type)
{
    first = NULL;
    last = NULL;
    err_type = type;
}

DLList::~DLList()   // de-allocate the list
{
    while(Remove(NULL) != NULL)
        ;
}

void DLList::Prepend(void *item)    // add to head of list (set key = min_key-1)
{
    DLLElement *elm = new DLLElement(item, 0);
    if(IsEmpty())
    {
        first = elm;
        last = elm;
    }
    else
    {
        elm -> key = first -> key - 1;
        elm -> next = first;
        elm -> prev = NULL;
        first -> prev = elm;
        first = elm;
    }
}
void DLList::Append(void *item)     // add to tail of list (set key = max_key+1)
{
    DLLElement *elm = new DLLElement(item, 0);
    if(IsEmpty())
    {
        first = elm;
        last = elm;
    }
    else
    {
        elm -> key = last -> key + 1;
        elm -> next = NULL;
        elm -> prev = last;
        last -> next = elm;
        last = elm;
    }
}

void *DLList::Remove(int *keyPtr)   // remove from head of list
{
    DLLElement *element;
    if (IsEmpty())
    {
        return NULL;
    }
    void *retitem;
    element = first;
    *keyPtr = first -> key;
    if (err_type == 1)
    {
        // printf("Remove error\n");
        currentThread -> Yield();
    }
    retitem = element -> item;
    if (first == last)
    {
        first = NULL;
        last = NULL;
    }
    else
    {
        if (err_type == 1)
        {
            // printf("Remove error\n");
            currentThread -> Yield();
        }
        first = element -> next;
        first -> prev = NULL;
    }
    delete element;
    return retitem;
}

bool DLList::IsEmpty()              // return true if list has elements
{                           // routines to put/get items on/off list in order (sorted by key)
    if ((first == NULL) && (last == NULL))
        return true;
    else if ((first != NULL) && (last != NULL))
        return false;
    else
        printf("error! either the first or the last is NULL!\n");
    return false;
}                          
void DLList::SortedInsert(void *item, int sortKey)
{
    DLLElement *insertItem = new DLLElement(item, sortKey);
    DLLElement *ptr = first;
    if (IsEmpty())
    {
        first = insertItem;
        if (err_type == 2)
        {
            // printf("SortedInsert error, first != last\n");
            currentThread -> Yield();
        }
        last = insertItem;
    }
    else
    {
        for (;ptr != NULL; ptr = ptr -> next)
            if(ptr -> key > sortKey) break;
        
        if (err_type == 3)
        {
            // printf("SortedInsert error, the position lost\n");
            currentThread -> Yield();
        }
        if (ptr == NULL)
        {
            insertItem -> prev = last;
            last -> next = insertItem;
            last = insertItem;
            last -> next = NULL;
        }
        else
        {
            if (ptr == first)
            {
                insertItem -> next = first;
                first -> prev = insertItem;
                first = insertItem;
                first -> prev = NULL;
            }
            else
            {
                ptr -> prev -> next = insertItem;
                insertItem -> prev = ptr -> prev;
                if (err_type == 4)
                {
                    // printf("SortedInsert error, sort error\n");
                    currentThread -> Yield();
                }
                insertItem -> next = ptr;
                ptr -> prev = insertItem;
            }
        }
    }
}

void *DLList::SortedRemove(int sortKey)         // remove first item with key==sortKey
{
    DLLElement *ptr = first;
    if (IsEmpty())
        return NULL;
    for (;ptr!=NULL; ptr = ptr -> next)
    {
        if (ptr -> key > sortKey) break;
        if (ptr == NULL)
        {
            printf("Remove error! No such a key!");
            return NULL;
        }

        if(ptr -> key == sortKey)
        {       
            if (ptr == first)
            {
                first = first -> next;
                first -> prev = NULL;
            }
            else if (ptr == last)
            {
                last = last -> prev;
                last -> next = NULL;
            }
            else
            {
                ptr -> prev -> next = ptr -> next;
                ptr -> next -> prev = ptr -> prev;
            }
        }
    }
    return ptr -> item;
}


void DLList::ShowList() {
    if (IsEmpty()) {
        printf("Queue is empty\n");
    } else {
        DLLElement *current = first;
        while (current != NULL) {
            printf("%d ", current->key);
            // printf("Item: %p", current->item);
            current = current->next;
        }
        printf("\n");
    }
}