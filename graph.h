#ifndef GRAPH_H
#define GRAPH_H

#include <queue>
#include <unordered_set>
#include <QSize>
#include <QPoint>

#include <QDebug>

enum Status { free_, block, way, strend };
class Node;

class Graph : public QObject
{
    Q_OBJECT
public:
    explicit Graph(QObject *parent = 0);
    ~Graph();

    Status status(const QPoint &point) const;
    QSize size() const { return size_; }

    bool setSizeField(const QSize &size);
    int setCountBlocks(int count);
    void setPoint(const QPoint &point);

private: signals:
    void dataChanged();
    void cantFindPath();

private:
    void createGraph();
    void findPath(Node *start, Node *end);
    int index(const QPoint &point) const;
    void clearNods();

    QSize size_;
    std::vector<Node *> nods;
    Node *start, *end;
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

    bool setPrevious(Node *node);
    Node *previous() const { return previousNode; }

private:
    std::unordered_set<Node *> nods;
    std::unordered_set<Node *>::iterator currentIt;
    int status_;
    Node *previousNode;
};

#endif // GRAPH_H
