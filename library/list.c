#include <list-private.h>

/*
 * Private Functions
 */

data_t* newData(unsigned char *string);
// data_t* copyData(data_t* dt);
void deleteData(data_t* dt);
int verifyData(data_t* dt);
int computeDataHash(data_t *data);
int pushListData(list_t*,data_t*);
void deleteEle(element_t* ele);

data_t* newData(unsigned char* string)
{
    if(string == NULL)
        return NULL;

    data_t* nw = calloc(1,sizeof(data_t));
    
    if(nw==NULL)
        return NULL;
    
    strlcpy(nw->str,string,MAX_DATA_LENGTH);
    nw->len = strlen(nw->str);
    if (computeDataHash(nw))
        return NULL;
    return nw;
}

int copyData(data_t* output, data_t* input)
{
    if (input == NULL || output == NULL)
        return -1;
    strncpy(output->str,input->str,MAX_DATA_LENGTH);
    output->len = input->len;
    copyHash(&(output->strhash),&(input->strhash));
    return 0;
}

int computeDataHash(data_t* data)
{
    hash_t* hsh = computeHash(data->str,data->len);
    copyHash(&(data->strhash),hsh);
    deleteHash(hsh);
    return 0;
}

element_t* newElement(data_t* dt)
{
    if (dt==NULL)
        return NULL;
    element_t* ele = calloc(1, sizeof(element_t));
    if (ele == NULL)
        return NULL;
    copyData(&(ele->info),dt);
    hash_t* nl = HASH_NULL;
    copyHash(&(ele->prevHash),nl);
    deleteHash(nl);
    return ele;
}

int computeElementHash(element_t* ele)
{
    return mergeHash(&(ele->prevHash),&(ele->info.strhash),&(ele->hash));
}

int verifyData(data_t* dt)
{
    if(strlen(dt->str) != dt->len)
        return -1;
    
    hash_t* htemp = computeHash(dt->str,dt->len);

    if(compareHash(htemp,&(dt->strhash)))
        return -1;
    deleteHash(htemp);

    return 0;
}

int verifyElement(element_t* ele)
{
    if (verifyData(&(ele->info)))
        return -1;
    
    hash_t* temp = newHash();
    if (mergeHash(&(ele->prevHash),&(ele->info.strhash),temp))
        return -1;
    if (compareHash(temp,&(ele->hash)))
        return -1;
    deleteHash(temp);
    return 0;
}
int copyElement(element_t* output,element_t* input)
{
    if (input==NULL || output == NULL)
        return -1;
    copyHash(&(output->prevHash),&(input->prevHash));
    copyData(&(output->info),&(input->info));
    copyHash(&(output->hash),&(input->hash));
    return 0;
}



lelement_t* newLElement(data_t* dt)
{
    lelement_t* lelt = calloc(1,sizeof(lelement_t));
    element_t* ele = newElement(dt);
    copyElement(&(lelt->elem),ele);
    deleteEle(ele);
    return lelt;
}

list_t* newList()
{
    list_t* nwlist = calloc(1,sizeof(list_t));
    if(nwlist==NULL)
        return NULL;
    data_t* dt= newData("");
    nwlist->head = nwlist->tail = newLElement(dt);
    deleteData(dt);
    nwlist->curr = NULL;
    computeElementHash(&((nwlist->head)->elem));
    return nwlist;
}



int pushListData(list_t* lst , data_t* dt)
{
    if(lst==NULL || dt==NULL)
        return -1;

    lelement_t* ele = newLElement(dt);
    lst->tail->next = ele;
    copyHash(&(ele->elem.prevHash),&(lst->tail->elem.hash));
    lst->tail = ele;
    computeElementHash(&(lst->tail->elem));
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
        char* hash1 = getStrHash(&(lst->curr->elem.prevHash));
        char* hash2 = getStrHash(&(lst->curr->elem.hash));
        fprintf(stdout,"Data: %s ;",lst->curr->elem.info.str);
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
        if (lst->curr->next && compareHash(&(lst->curr->next->elem.prevHash),&(lst->curr->elem.hash)))
            return -1;
        
        hash_t* temp;
        
        if (verifyElement(&(lst->curr->elem)))
            return -1;
        lst->curr = lst->curr->next;
    }
    return 0;
}

void deleteData(data_t* dt)
{
    free(dt);
}

void deleteEle(element_t* ele)
{
    free(ele);
}

void deleteLEle(lelement_t *lelem)
{
    free(lelem);
}

void deleteList(list_t* lst)
{
    lst->curr = lst->head;
    while(lst->curr)
    {
        lelement_t* tmp = lst->curr;
        lst->curr = lst->curr->next;
        deleteLEle(tmp);
    }
    lst->head = lst->tail = lst->curr = NULL;
    free(lst);
}