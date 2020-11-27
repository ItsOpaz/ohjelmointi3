#include <QtTest>
#include <QString>
#include <QPair>
#include <sstream>

#include <statistics.h>

class GameTest : public QObject
{
    Q_OBJECT

public:
    GameTest();

private Q_SLOTS:
    void add_points();
    void add_negative_points();
    void add_zero_points();
    void set_info();
    void reduce_life();
    void check_score();

};

GameTest::GameTest()
{
}

void GameTest::add_points(){
    Students::statistics stats;
    QCOMPARE(stats.get_score().second, 0);
    stats.increase_score(10);
    QCOMPARE(stats.get_score().second, 10);
}

void GameTest::add_negative_points(){
    Students::statistics stats;
    QCOMPARE(stats.get_score().second, 0);
    stats.increase_score(-10);
    QCOMPARE(stats.get_score().second, -10);
}

void GameTest::add_zero_points(){
    Students::statistics stats;
    QCOMPARE(stats.get_score().second, 0);
    stats.increase_score(0);
    QCOMPARE(stats.get_score().second, 0);
}

void GameTest::set_info(){
    Students::statistics stats;
    QString name = "TestName";
    QString diff = "TestDiff";
    stats.set_info(name, diff);
    QCOMPARE(stats.getDifficulty(), diff);
    // Test name
}

void GameTest::reduce_life(){
    Students::statistics stats;
    int init_lifes = 3;
    QCOMPARE(stats.get_lifes(), init_lifes);
    stats.reduce_lifes();
    QCOMPARE(stats.get_lifes(), init_lifes-1);
}

void GameTest::check_score(){
    Students::statistics stats;
    QString name = "TestName";
    QString diff = "TestDiff";
    std::pair<QString, int> init_info = {name, 0};
    stats.set_info(name, diff);
    QCOMPARE(stats.get_score(), init_info);
    stats.increase_score(10);
    std::pair<QString, int> result_info = {name, 10};
    QCOMPARE(stats.get_score(), result_info);
}


QTEST_APPLESS_MAIN(GameTest)

#include "tst_gametest.moc"
