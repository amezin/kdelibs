#include <QtDebug>
#include <QCoreApplication>

#include <Weaver/ThreadWeaver.h>
#include <Weaver/Lambda.h>

using namespace ThreadWeaver;

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    Weaver::instance()->enqueue(JobPointer(new Lambda( []() { qDebug() << "Hello World!"; } )));
    Weaver::instance()->finish();
}
