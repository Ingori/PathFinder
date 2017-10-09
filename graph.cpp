#include "graph.h"
#include <stdlib.h>
#include <time.h>

Graph::Graph(QObject *parent) : QObject(parent), /*mask(1<<8),*/ start(0), end(0)
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
    int topRow = 0;

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
                top = nods.at(++topRow);
            }
        }
        left = nullptr;
        topRow = i*size_.width();
        top = nods.at(topRow);
    }
}

bool Graph::setSizeField(const QSize &size)
{
    if(size.width() < 0 || size.height() < 0)
        return false;

    size_ = size;

    clearNods();
    createGraph();

    start = end = nullptr;
    emit dataChanged();
    return true;
}

int Graph::setCountBlocks(int count)
{
    int maxCount = size_.width()*size_.height();
    if(count >= maxCount)
    {
        for(Node *node : nods)
            node->setStatus(block);
        start = end = nullptr;
        emit dataChanged();
        return maxCount;
    }

    bool f = count < maxCount/2;
    if(!f) count = maxCount - count;
    for(Node *node : nods)
        node->setStatus(f ? free_ : block);

    double coeff = maxCount > RAND_MAX ? (double)maxCount/RAND_MAX : 1;

    int i = count;
    while(i > 0)
    {
        int ind = ((int)(coeff*rand()))%maxCount;
        if(nods.at(ind)->status() == f ? free_ : block)
        {
            nods[ind]->setStatus(!f ? free_ : block);
            i--;
        }
    }

    start = end = nullptr;
    emit dataChanged();
    return f ? count : maxCount - count;
}

void Graph::setPoint(const QPoint &point)
{
    int ind = index(point);
    if(ind == -1)
        return;

    Node *node = nods.at(ind);
    if(node->status() == block)
        return;

    node->setStatus(strend);

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

    Node *node = nullptr;
    std::unordered_set<Node *> deployed;

    std::queue<Node *> qNods;
    qNods.push(start);
    deployed.insert(start);

    while(!qNods.empty())
    {
        node = qNods.front();
        qNods.pop();

        if(node == end)
        {
            end->setPrevious(node);
            deployed.insert(end);
            break;
        }

        Node *nd = node->nextNode();
        while(nd)
        {
            if(deployed.find(nd) == deployed.end() && nd->status() != block)
            {
                nd->setPrevious(node);
                qNods.push(nd);
                deployed.insert(nd);
            }
            nd = node->nextNode();
        }
    }

    node = end->previous();
    if(node)
        while(node != start)
        {
            node->setStatus(way);
            node = node->previous();
        }
    else
        emit cantFindPath();

    for(Node *node : deployed)
        node->setPrevious(nullptr);
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



Node::Node(int status) : status_(status), previousNode(nullptr)
{
    currentIt = nods.begin();
}

void Node::addNode(Node *node)
{
    if(node && node != this)
        nods.insert(node);

    currentIt = nods.begin();
}

bool Node::deleteNode(Node *node)
{
    auto it = nods.find(node);
    if(it == nods.end())
        return false;

    if(node == previousNode)
        previousNode = nullptr;

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

bool Node::setPrevious(Node *node)
{
    if(!node)
    {
        previousNode = node;
        return true;
    }

    auto it = nods.find(node);
    if(it == nods.end())
        return false;

    previousNode = node;
    return true;
}

