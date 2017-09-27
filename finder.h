#ifndef FINDER_H
#define FINDER_H

#include <QObject>
#include <QPoint>

class Rec;

class Keeper : public QObject
{
    Q_OBJECT
public:
    explicit Keeper(QObject *parent = 0);

    void clearAll();

    bool setHighBlocks(int high);
    bool setWidthBlocks(int width);
    bool setCountBlocks(int count);

    int highBlocks() const { return high_; }
    int widthBlocks() const { return width_; }
    int countBlocks() const { return count_; }

    std::vector<Rec> &getBlocks() { return blocks; }
    std::vector<QPoint> &getWay() { return way; }

signals:

public slots:

private:
    int high_, width_, count_;
    std::vector<Rec> blocks;
    std::vector<QPoint> way;
};

class Rec
{
public:
    Rec(const QPoint &leftTop, const QPoint &rightBottom) : leftTop_(leftTop), rightBottom_(rightBottom) {}

private:
    QPoint leftTop_, rightBottom_;
};



class Finder : public QObject
{
    Q_OBJECT
public:
    explicit Finder(Keeper *keeper, QObject *parent = 0);

signals:

public slots:

private:
    Keeper *keeper_;
};



class CreatorRec : public QObject
{
    Q_OBJECT
public:
    explicit CreatorRec(Keeper *keeper, QObject *parent = 0);

signals:

public slots:

private:
    Keeper *keeper_;
};

#endif // FINDER_H
