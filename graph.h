#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QSize>
#include <QPoint>

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

public slots:
    void setSizeField(const QSize &size);
    void setCountBlocks(int count);
    void setStartEnd(const QPoint &start, const QPoint &end);

protected: signals:
    void dataChanged();

private:
    void createGraph();
    int index(const QPoint &point) const;

    QSize size_;
    int width_, height_;
    std::vector<Node *> nods;

//    std::vector<Node *> way;
};



class Node
{
public:
    Node(Node *left, Node *top, Node *right, Node *bottom) :
        left_(left), top_(top), right_(right), bottom_(bottom), status_(free_) {}

    void setStatus(Status status) { status_ = status; }
    Status status() const { return status_; }

    void setLeft(Node *left) { left_ = left; }
    void setTop(Node *top) { top_ = top; }
    void setRight(Node *right) { right_ = right; }
    void setBottom(Node *bottom) { bottom_ = bottom; }

    Node *left() const { return left_; }
    Node *top() const { return top_; }
    Node *right() const { return right_; }
    Node *bottom() const { return bottom_; }

private:
    Node *left_, *top_, *right_, *bottom_;
    Status status_;
};

#endif // GRAPH_H
