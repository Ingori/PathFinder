#include "graph.h"
#include <stdlib.h>
#include <time.h>

Graph::Graph(int width, int height, QObject *parent) : QObject(parent), width_(width), height_(height)
{
    createGraph();
    srand(time(0));
}

Graph::~Graph()
{
    nods.clear();
}

bool Graph::isFree(const QPoint &point) const
{
    int ind = index(point);
    if(ind == -1)
        return false;
    return nods.at(ind)->isFree();
}

//QPoint Graph::atStp(int ind) const
//{
//    return way.at(ind);
//}

bool Graph::setStartEnd(const QPoint &start, const QPoint &end)
{
    int indStart = index(start);
    int indEnd = index(end);
    if(indStart == -1 || indEnd == -1)
        return false;

    Node *startN = nods.at(indStart);
    Node *endN = nods.at(indEnd);

    if(!startN->isFree() || !endN->isFree())
        return false;

    /**/
}

bool Graph::setWidthHeight(int width, int height)
{
    if(!(width > 0 && height > 0))
        return false;

    width_ = width;
    height_ = height;

    nods.clear();
    createGraph();
}

void Graph::refresh()
{

}

void Graph::createGraph()
{
    Node *left, *top;
    left = top = 0;

    for(int i = 0; i < height_; i++)
    {
        for(int j = 0; j < width_; j++)
        {
            Node *node = new Node(left, top, 0, 0);
            nods.push_back(node);

            if(left)
                left->setRight(node);
            left = node;

            if(top)
            {
                top->setBottom(node);
                top = top->right();
            }
        }
        left = 0;
        top = nods.at(i*width_);
    }
}

void Graph::randomFillGraph(int n)
{
    int count = width_*height_;
    if(n >= count)
    {
        for(Node *node : nods)
            node->setStatus(false);
        return;
    }

    bool f = n < count/2;
    if(!f) n = count - n;
    for(Node *node : nods)
        node->setStatus(f);

    while(n > 0)
    {
        int ind = rand()%count;
        if(nods.at(ind)->isFree() == f)
        {
            nods[ind]->setStatus(!f);
            n--;
        }
    }
}

int Graph::index(const QPoint &point) const
{
    int x = point.x();
    int y = point.y();

    if(!(x >= 0 && x < width_))
        return -1;
    if(!(y >= 0 && y < height_))
        return -1;

    return y*width_ + x;
}
