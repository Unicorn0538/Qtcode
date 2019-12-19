#ifndef FINDROAD_H
#define FINDROAD_H

#include <stack>
#include <iostream>
using namespace std;
#define  NUM 81
#define MAX_PATH 81
struct Node
{
    int key;
    int flag;
    Node()
    {
        flag=0;
    }
};
class Graph
{
public:
    int resultPath[MAX_PATH][NUM];
    int result[NUM+1];
    Node headNode;//起始节点
    Node endNode;//终止节点
    stack<Node> tempStack;
    int pathNum;
    int nPos;
    bool Mark[NUM];
public:
    Graph()
    {
        for (int i=0;i<NUM;i++)
        {
            for (int j=0;j<MAX_PATH;j++)
            {
                resultPath[i][j]=0;
            }
            result[i]=0;
            Mark[i]=false;
        }
        result[NUM]=0;
        pathNum=0;
        nPos=0;
    }

    void FIND(int path[NUM][NUM],int num1,int num2)
    {
        Node startNodeKey,endNodeKey;
        startNodeKey.key = num1+1;
        startNodeKey.flag = 1;
        endNodeKey.key = num2+1;
        FindAllPath(path,startNodeKey,endNodeKey);
    }
    void FindAllPath(int Matrix[NUM][NUM],Node startNodeKey,Node endNodeKey)
    {
        result[nPos]=startNodeKey.key;
        Mark[startNodeKey.key-1]=true;
        nPos++;
        while(nPos!=0)
        {
            int tempVal=result[nPos-1];
            if (tempVal==endNodeKey.key)
            {
                for (int j=0;j<nPos;j++)
                {
                    resultPath[pathNum][j]=result[j]-1;
                }
                nPos--;
                result[nPos]=0;
                pathNum++;
                Mark[endNodeKey.key-1]=false;
                break;
            }
            while(startNodeKey.flag<NUM)
            {
                if (Matrix[tempVal-1][startNodeKey.flag]==1)
                {
                    if (Mark[startNodeKey.flag]==false)
                    {
                        Node tempNode;
                        tempNode.key=startNodeKey.flag+1;
                        FindAllPath(Matrix,tempNode,endNodeKey);
                    }
                }
                startNodeKey.flag++;
            }
            if (startNodeKey.flag==NUM)
            {
                nPos--;
                startNodeKey.flag=0;
                result[nPos]=0;
                Mark[startNodeKey.key-1]=false;
                break;
            }
        }
    }
};


#endif // FINDROAD_H
