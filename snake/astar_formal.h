#ifndef ASTAR_FORMAL_H
#define ASTAR_FORMAL_H

#include <vector>
#include "string.h"
using namespace std;

struct MyPoint
{
    int x;
    int y;
    int f,g,h;
};

struct MyNode
{
    MyPoint pos;
    MyNode *pParent;
    vector <MyNode*> pChild;
    MyNode();


};


//定义Class
class Astar
{
public:
    //Astar();
    //2.始末点
    MyPoint begPos;
    MyPoint endPos;

    vector<MyNode*> openList;
    vector<MyNode*> closeList;

    vector<MyNode*>::iterator item;
    vector<MyNode*>::iterator itemMin;

    //4当前点，试探点
    MyNode *currPos;
    MyNode *nextPos;

    void setBeginPos(int x,int y);
    void setEndPos(int x,int y);
    bool canWalk(MyNode* p);  //判断点是否可行
    void creatNextPos();       //判断是否添加进openlist
    void getG(MyNode *pos);
    void getH(MyNode * pos);
    void getF(MyNode * pos);
    void selectMin();


};

#endif // ASTAR_FORMAL_H
