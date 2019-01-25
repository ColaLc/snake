#include <iostream>
#include "astar_formal.h"
using namespace std;

int myMap[35][30]={0};

MyNode::MyNode()
{
   // pParent=NULL;


}

void Astar::setBeginPos(int x, int y)
{
    begPos.x=x;
    begPos.y=y;
    currPos=new MyNode;
    currPos->pos=begPos;
    currPos->pParent=NULL;
    openList.push_back(currPos);

}
void Astar::setEndPos(int x, int y)
{
    endPos.x=x;
    endPos.y=y;

}
bool Astar::canWalk(MyNode *p)
{


    for(unsigned int i=0;i<closeList.size();i++)
    {
        if((p->pos.x==closeList[i]->pos.x)&&(p->pos.y==closeList[i]->pos.y))
        {
                return false;
        }
    }
    for(unsigned int i=0;i<openList.size();i++)
    {
        if((p->pos.x==openList[i]->pos.x)&&(p->pos.y==openList[i]->pos.y))
        {
            return false;
        }
    }

    if(p->pos.x<0 || p->pos.y<0 ||p->pos.x>34 ||p->pos.y>29 )
        return false;
    else
        if(myMap[p->pos.x][p->pos.y]==1)
            return false;

//    else
        return true;
}

void Astar::creatNextPos()
{

    for(int i=0;i<4;i++)
    {
        nextPos=new MyNode;
        //memset(nextPos,0,sizeof(nextPos));
        nextPos->pos=currPos->pos;
        switch(i)
        {
        case 0:
            nextPos->pos.y--;
            nextPos->pos.g+=1;
            break;
        case 1:
            nextPos->pos.y++;
            nextPos->pos.g+=1;
            //cout<<nextPos.x;
            break;
        case 2:
            nextPos->pos.x--;
            nextPos->pos.g+=1;
            break;

        case 3:
            nextPos->pos.x++;
            nextPos->pos.g+=1;
            break;
        default:
            break;
        }
        if(canWalk(nextPos)==true)
        {
            getF(nextPos);
            currPos->pChild.push_back(nextPos);
            //nextPos->pParent=new MyNode;
            nextPos->pParent=currPos;
            openList.push_back(nextPos);
        }
    }
}

void Astar::getG(MyNode *pos)
{
    int n;
    int x = (begPos.x > pos->pos.x)?(begPos.x-pos->pos.x):(pos->pos.x-begPos.x);
    int y = (begPos.y > pos->pos.y)?(begPos.y-pos->pos.y):(pos->pos.y-begPos.y);
    n=x+y;
    pos->pos.g=n;
}

void Astar::getH(MyNode * pos)
{
    int n;
    int x = (endPos.x > pos->pos.x)?(endPos.x-pos->pos.x):(pos->pos.x-endPos.x);
    int y = (endPos.y > pos->pos.y)?(endPos.y-pos->pos.y):(pos->pos.y-endPos.y);
    n=x+y;
    pos->pos.h=n;
}

void Astar::getF(MyNode * pos)
{
    getG(pos);
    getH(pos);
    pos->pos.f=pos->pos.g+pos->pos.h;
}

void Astar::selectMin()
{

    item = openList.begin();
    itemMin=item;
    for(item=openList.begin();item!=openList.end();item++)
    {
        if( (*itemMin)->pos.f > (*item)->pos.f )
        {
            itemMin=item;
        }
    }
    //
    closeList.push_back(currPos);
    currPos=(*itemMin);
    openList.erase(itemMin);

}


/*int main(int argc, char *argv[])
{

    Astar a;
    a.setBeginPos(3,3);
    a.setEndPos(3,5);
    while(1)
    {
        a.creatNextPos();
        a.selectMin();

        if(a.currPos->pos.x==a.endPos.x  &&  a.currPos->pos.y==a.endPos.y)      //找到终点
        {
            cout<<"find:  "<<endl;
            while(a.currPos->pParent)
            {
               cout<<a.currPos->pos.x<<","<<a.currPos->pos.y<<endl;
               a.currPos=a.currPos->pParent;
            }
            break;
        }
        if (a.openList.size() == 0 )  //无法找到
        {
                cout<<"no find"<<endl;
                break;
        }

    }

    return 0;
}
*/



