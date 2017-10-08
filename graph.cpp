#include "graph.h"
#include <stdlib.h>
#include <time.h>

Graph::Graph(QObject *parent) : QObject(parent), mask(1<<8), start(0), end(0)
{
    srand(time(0));
}

Graph::~Graph()
{
    clearNods();
}

Status Graph::status(const QPoint &point) const
{
    int ind = index(point);
    if(ind == -1)
        return free_;
    return (Status)nods.at(ind)->status();
}

void Graph::createGraph()
{
    Node *left, *top;
    left = top = nullptr;

    for(int i = 0; i < size_.height(); i++)
    {
        for(int j = 0; j < size_.width(); j++)
        {
            Node *node = new Node(free_);
            node->addNode(left);
            node->addNode(top);
            nods.push_back(node);

            if(left)
                left->addNode(node);
            left = node;

            if(top)
            {
                top->addNode(node);
                top = nods.at(i*size_.width() + j);
            }
        }
        left = nullptr;
        top = nods.at(i*size_.width());
    }
}

void Graph::setSizeField(const QSize &size)
{
    if(size.width() < 0 || size.height() < 0)
        return;

    size_ = size;

    clearNods();
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
        if(nods.at(ind)->status() == f ? free_ : block)
        {
            nods[ind]->setStatus(!f ? free_ : block);
            count--;
        }
    }

    emit dataChanged();
}

void Graph::setPoint(const QPoint &point)
{
    int ind = index(point);
    if(ind == -1)
        return;

    Node *node = nods.at(ind);
    if(node->status() == block)
        return;

    if(!start)
        start = node;
    else if(!end)
    {
        end = node;
        findPath(start, end);
        start = end = nullptr;
    }

    emit dataChanged();
}

void Graph::findPath(Node *start, Node *end)
{
    if(!start || !end)
        return;

    std::queue<Node *> qNods;

    setDeployed(start);
    qNods.push(start);


    while()
    {
    Node *node = qNods.front();
    qNods.pop();

    int st
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

void Graph::clearNods()
{
    for(auto node : nods)
        delete node;
    nods.clear();
}

void Graph::isolateNode(Node *node)
{
    Node *neighbor = node->nextNode();
    while(neighbor)
    {
        neighbor->deleteNode(node);
        neighbor = node->nextNode();
        node->deleteNode(neighbor);
    }
}

void Graph::setDeployed(Node *node)
{
    node->setStatus(node->status() & mask);
}

void Graph::resetDeployed(Node *node)
{
    node->setStatus(node->status() & ~mask);
}

bool Graph::isDeployed(const Node *node) const
{
    return node->status() & mask;
}



Node::Node(int status) : status_(status)
{
    currentIt = nods.begin();
}

void Node::addNode(Node *node)
{
    if(node && node != this)
        nods.insert(node);
}

bool Node::deleteNode(Node *node)
{
    auto it = nods.find(node);
    if(it == nods.end())
        return false;

    if(currentIt == it)
        currentIt++;

    nods.erase(it);
    return true;
}

Node *Node::nextNode()
{
    if(currentIt != nods.end())
        return *currentIt++;

    currentIt = nods.begin();
    return nullptr;
}
