#ifndef FINDER_H
#define FINDER_H

#include <QObject>
#include <QRect>
#include <QPoint>

class Keeper : public QObject
{
    Q_OBJECT
public:
    explicit Keeper(QObject *parent = 0);

    void clearAll();

    bool setRectField(const QRect &rect);
    bool setRectBlocks(const QRect &rect);
    bool setCountBlocks(int count);
    bool setStartEndWay(const QPoint &pointStart, const QPoint &pointEnd);

    QRect rectField() const { return field; }
    QRect rectBlocks() const { return block; }
    int countBlocks() const { return count_; }
    QPoint startPoint() const { return startWay_; }
    QPoint endPoint() const { return endWay_; }

    std::vector<QRect> &getBlocks() { return blocks; }
    std::vector<QPoint> &getWay() { return way; }

signals:

public slots://хранитель отвечает что актуально, а что нет(что нужно изменить)

private:
    int count_;
    QRect field, block;
    QPoint startWay_, endWay_;
    std::vector<QRect> blocks;
    std::vector<QPoint> way;
};



class Finder : public QObject
{
    Q_OBJECT
public:
    explicit Finder(Keeper *keeper, QObject *parent = 0);

protected: signals:
    void endWork();

public slots:
    void findWay();

private:
    Keeper *const keeper_;
};



class CreatorRec : public QObject
{
    Q_OBJECT
public:
    explicit CreatorRec(Keeper *keeper, QObject *parent = 0);

protected: signals:
    void endWork();

public slots:
    void generateBlocks();

private:
    Keeper *const keeper_;
};

#endif // FINDER_H
