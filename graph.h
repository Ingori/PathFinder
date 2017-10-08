#ifndef GRAPH_H
#define GRAPH_H

#include <queue>
#include <unordered_set>
//#include <set>
#include <QSize>
#include <QPoint>

#include <QDebug>

enum Status { free_, block, way };
class Node;

class Graph : public QObject
{
    Q_OBJECT
public:
    explicit Graph(QObject *parent = 0);
    ~Graph();

    Status status(const QPoint &point) const;
    QSize size() const { return size_; }

    void setSizeField(const QSize &size);
    void setCountBlocks(int count);
    void setPoint(const QPoint &point);

private: signals:
    void dataChanged();

private:
    void createGraph();
    void findPath(Node *start, Node *end);
    int index(const QPoint &point) const;
    void clearNods();
    void isolateNode(Node *node);

    void setDeployed(Node *node);
    void resetDeployed(Node *node);
    bool isDeployed(const Node *node) const;
    const int mask;

    QSize size_;
    int width_, height_;
    std::vector<Node *> nods;

    Node *start, *end;
    std::queue<Node *> queueNods;
};



class Node
{
public:
    Node(int status);

    void setStatus(int status) { status_ = status; }
    int status() const { return status_; }

    void addNode(Node *node);
    bool deleteNode(Node *node);
    Node *nextNode();
    bool hasNode() const { return !nods.empty(); }

private:
    std::unordered_set<Node *> nods;
    std::unordered_set<Node *>::iterator currentIt;
    int status_;
};

#endif // GRAPH_H
