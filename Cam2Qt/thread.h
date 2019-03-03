#ifndef THREAD_H
#define THREAD_H

#include <QThread>

class Thread final : public QThread {

public:
    ~Thread() {
        quit();
        wait();
    }
};

#endif // THREAD_H
