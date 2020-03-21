#include <list-private.h>

/*
 * Private Functions
 */

data_t* newData(unsigned char *string);
data_t* copyData(data_t* dt);
void deleteData(data_t* dt);
int verifyData(data_t* dt);
int computeDataHash(data_t *data);
int pushListData(list_t*,data_t*);

data_t* newData(unsigned char* string)
{
    if(string == NULL)
        return NULL;

    data_t* nw = calloc(1,sizeof(data_t));
    
    if(nw==NULL)
        return NULL;
    
    nw->str = strdup(string);
    nw->len = strlen(nw->str);
    if (computeDataHash(nw))
        return NULL;
    return nw;
}

data_t* copyData(data_t* dt)
{
    if (dt == NULL)
        return NULL;
    return newData(dt->str);
}

int computeDataHash(data_t* data)
{
    data->strhash = computeHash(data->str,data->len);
    if(data->strhash == NULL)
        return -1;
    return 0;
}

element_t* newElement(data_t* dt)
{
    if (dt==NULL)
        return NULL;
    element_t* ele = calloc(1, sizeof(element_t));
    if (ele == NULL)
        return NULL;
    ele->info = copyData(dt);
    ele->next = NULL;
    ele->prevHash = HASH_NULL;
    ele->hash = NULL;
    return ele;
}

int computeElementHash(element_t* ele)
{
    return mergeHash(ele->prevHash,ele->info->strhash,&ele->hash);
}

int verifyData(data_t* dt)
{
    if(strlen(dt->str) != dt->len)
        return -1;
    
    hash_t* htemp = computeHash(dt->str,dt->len);

    if(compareHash(htemp,dt->strhash))
        return -1;
    deleteHash(htemp);

    return 0;
}

int verifyElement(element_t* ele)
{
    if (verifyData(ele->info))
        return -1;
    
    hash_t* temp;
    if (mergeHash(ele->prevHash,ele->info->strhash,&temp))
        return -1;
    if (compareHash(temp,ele->hash))
        return -1;
    deleteHash(temp);
    return 0;
}

list_t* newList()
{
    list_t* nwlist = calloc(1,sizeof(list_t));
    if(nwlist==NULL)
        return NULL;
    data_t* dt= newData("");
    nwlist->head = nwlist->tail = newElement(dt);
    deleteData(dt);
    nwlist->curr = NULL;
    computeElementHash(nwlist->head);
    return nwlist;
}



int pushListData(list_t* lst , data_t* dt)
{
    if(lst==NULL || dt==NULL)
        return -1;

    element_t* ele = newElement(dt);
    lst->tail->next = ele;
    deleteHash(ele->prevHash);
    ele->prevHash = copyHash(lst->tail->hash);
    lst->tail = ele;
    computeElementHash(lst->tail);
    return 0;
}

int pushListStr(list_t* lst, char* str)
{
    if(lst==NULL || str == NULL)
        return -1;
    data_t* dt = newData(str);
    int res = pushListData(lst,dt);
    deleteData(dt);
    return res;
}

void printList(list_t* lst, int verbosity)
{
    lst->curr = lst->head;
    while(lst->curr)
    {
        char* hash1 = getStrHash(lst->curr->prevHash);
        char* hash2 = getStrHash(lst->curr->hash);
        fprintf(stdout,"Data: %s ;",lst->curr->info->str);
        if(verbosity)
            fprintf(stdout,"Hash: %s ;",hash2);
        fprintf(stdout,"\n");
        free(hash1);
        free(hash2);
        lst->curr = lst->curr->next;
    }
}

int verifyList(list_t* lst)
{
    lst->curr = lst->head;
    while(lst->curr)
    {
        if (lst->curr->next && compareHash(lst->curr->next->prevHash,lst->curr->hash))
            return -1;
        
        hash_t* temp;
        
        if (verifyElement(lst->curr))
            return -1;
        lst->curr = lst->curr->next;
    }
    return 0;
}

void deleteData(data_t* dt)
{
    deleteHash(dt->strhash);
    free(dt->str);
    free(dt);
}

void deleteEle(element_t* ele)
{
    deleteHash(ele->prevHash);
    deleteHash(ele->hash);
    deleteData(ele->info);
    free(ele);
}

void deleteList(list_t* lst)
{
    lst->curr = lst->head;
    while(lst->curr)
    {
        element_t* tmp = lst->curr;
        lst->curr = lst->curr->next;
        deleteEle(tmp);
    }
    lst->head = lst->tail = lst->curr = NULL;
    free(lst);
}