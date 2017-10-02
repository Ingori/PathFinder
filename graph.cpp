#include "graph.h"
#include <stdlib.h>
#include <time.h>

Graph::Graph(QObject *parent) : QObject(parent)
{
//    createGraph();
    srand(time(0));
}

Graph::~Graph()
{
    nods.clear();
}

Status Graph::status(const QPoint &point) const
{
    int ind = index(point);
    if(ind == -1)
        return free_;
    return nods.at(ind)->status();
}

void Graph::createGraph()
{
    Node *left, *top;
    left = top = 0;

    for(int i = 0; i < size_.height(); i++)
    {
        for(int j = 0; j < size_.width(); j++)
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
        top = nods.at(i*size_.width());
    }
}

void Graph::setSizeField(const QSize &size)
{
//    if(!(size.width() > 0 && size.height() > 0))
//        return false;

//    width_ = width;
//    height_ = height;dataChange

    size_ = size;

    nods.clear();
    createGraph();

    emit dataChanged();
}

void Graph::setCountBlocks(int count)
{
    int maxCount = size_.width()*size_.height();
    if(count >= maxCount)
    {
        for(Node *node : nods)
            node->setStatus(block);
        return;
    }

    bool f = count < maxCount/2;
    if(!f) count = maxCount - count;
    for(Node *node : nods)
        node->setStatus(f ? free_ : block);

    while(count > 0)
    {
        int ind = rand()%maxCount;
        if(nods.at(ind)->status() == free_)
        {
            nods[ind]->setStatus(!f ? free_ : block);
            count--;
        }
    }

    emit dataChanged();
}

void Graph::setStartEnd(const QPoint &start, const QPoint &end)
{
    int indStart = index(start);
    int indEnd = index(end);
    if(indStart == -1 || indEnd == -1)
        return ;

    Node *startN = nods.at(indStart);
    Node *endN = nods.at(indEnd);

    if(startN->status() != free_ || endN->status() != free_)
        return;

    /**/

    emit dataChanged();
}

int Graph::index(const QPoint &point) const
{
    int x = point.x();
    int y = point.y();

    if(!(x >= 0 && x < size_.width()))
        return -1;
    if(!(y >= 0 && y < size_.height()))
        return -1;

    return y*size_.width() + x;
}
