#include "cson.h"
#include "debugApp.h"

CSon::CSon()
{

}

void CSon::sleep()
{
    debugApp() <<"son " << "sleeping...";
}


#if 0

int main(int argc, char **argv)
{
    qDebug() << "hello";
//各自睡各自的，定义不定义virtual没啥区别呢
//    CSon son;
//    son.sleep();

//    CParent parent;
//    parent.sleep();

    /**
     * 明白了吗？
     * 定义的基类指针
     * 1)若没有虚函数，基类指向子类对象时，运行的结果仍然是父类的数据
     * 2)若定义虚函数，基类指向子类对象时，运行的结果是子类的数据
     * 3)子类无法指向父类的指针，结果的不确定性，不论是否定义为虚函数
     */
    CParent *pParent = NULL;
    CSon *pSon = NULL;
    CParent parent;
    CSon son1;
    pParent = &son1;
    pParent->sleep();


    pSon = &son1;
    pSon->sleep();

//错误
//    pSon = &parent;
//    pSon->sleep();


    return 0;
}

#endif
