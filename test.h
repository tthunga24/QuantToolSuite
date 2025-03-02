#ifndef TEST_H
#define TEST_H
#include <QObject>
#include <QDebug>

class test : public QObject {
    Q_OBJECT
public:
    explicit test(QObject *parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void processNumber(int number) {
        number *= 2;
        qDebug() << "Received number from QML:" << number;
        emit numberProcessed("Your input *2 is: " + QString::number(number));
    }

signals:
    void numberProcessed(QString result);
};

#endif // TEST_H
