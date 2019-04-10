#include"mxml.h"
#include<stdio.h>

int main()
{
    FILE* fp = fopen("test.xml","r");
    // jiazai xml
    mxml_node_t* xml = mxmlLoadFile(NULL,fp,MXML_NO_CALLBACK);
    mxml_node_t* book = NULL;
    mxml_node_t* author = NULL;
    // find note
    book = mxmlFindElement(xml,xml,"book","id",NULL,MXML_DESCEND);
        //get attr
    author = mxmlFindElement(book,xml,"author",NULL,NULL,MXML_DESCEND);
    if(author == NULL)
    {
        printf("author error\n");
    }
    else
    {
        printf("book id is:%s\n",mxmlElementGetAttr(book,"id"));
        printf("author is:%s\n",mxmlGetText(author,NULL));
        book = mxmlFindElement(xml,xml,"book","id",NULL,MXML_DESCEND);
    }
    mxmlDelete(xml);
    fclose(fp);
    return 0;
}

