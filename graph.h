#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QPoint>

class Node;

class Graph : public QObject
{
    Q_OBJECT
public:
    explicit Graph(int width, int height, QObject *parent = 0);
//    ~Graph() { nods.erase()

    int width() const { return width_; }
    int height() const { return height_; }
    int countNods() const { return width_*height_; }
    int countStep() const { return way.size(); }
    bool isFree(const QPoint &point) const;
//    QPoint atStp(int ind) const;


//    bool setWidthHeight(int width, int height);
    bool setStartEnd(const QPoint &start, const QPoint &end);

    void randomFillGraph(int n);

protected: signals:
    void wayIsFound(bool found);

public slots:
    void refresh();

private:
    void createGraph();
    int index(const QPoint &point) const;

    int width_, height_;
    std::vector<Node *> nods;
    Node *rootNode;

    std::vector<Node *> way;
};



class Node
{
public:
    Node(Node *left, Node *top, Node *right, Node *bottom) :
        left_(left), top_(top), right_(right), bottom_(bottom), free(true) {}

    void setStatus(bool status) { free = status; }
    bool isFree() const { return free; }

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
    bool free;
};

#endif // GRAPH_H
