#ifndef TEST_H
#define TEST_H
#include <QObject>
#include <QDebug>

class test : public QObject {
    Q_OBJECT
public:
    explicit test(QObject *parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void processNumber(int number) {
        number *= 3;
        qDebug() << "Received number from QML:" << number;
        emit numberProcessed("Your input *3 is: " + QString::number(number));
    }

    Q_INVOKABLE void processNumber2(int number) {
        number /= 3;
        qDebug() << "Received number from QML:" << number;
        emit numberProcessed2("Your input /3 is: " + QString::number(number));
    }

signals:
    void numberProcessed(QString result);
    void numberProcessed2(QString result);
};

#endif // TEST_H
