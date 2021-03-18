#include "cson.h"
#include "debugApp.h"

CSon::CSon()
{

}

void CSon::sleep()
{
    debugApp() <<"son " << "sleeping...";
}

void CSon::hello()
{
    debugApp() <<"son " << "hello...";
}

void CSon::iamson()
{
    debugApp() <<"i am son ";
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
     * 4）虚函数的好处是只用定义了基类指针，就可以随便指向各个派生对象，并调用派生的数据
     */


    CParent *pParent = NULL;
    CSon *pSon = NULL;
    CGrandMaster *pGrandM = NULL;
//    CGrandMaster grandmaster;
    CParent parent;
    CSon son1;
    pParent = &son1;
    pParent->sleep();
    pParent->hello();


    pSon = &son1;
    pSon->sleep();
    pSon->hello();
    pSon->iamson();


    pGrandM = &parent;
    pGrandM->song();
    pGrandM->hello();

    pGrandM = &son1;
    pGrandM->song();
    pGrandM->hello();
//    pGrandM->sleep();

//错误
//    pSon = &parent;
//    pSon->sleep();

    /**
     * 纯虚函数
     * 1）如果parent定义了此函数，而son没有定义，则无论是基类还是派生类的结果都是parent的数据
     * 2）如果son定义了此函数，而parent也定义了，则无论是基类还是派生类的结果都是son的数据
     * 3) 派生类继承的纯虚函数没有实现，则无法实例化
     * 4) 纯虚函数不需要初始化
     * 5) 纯虚函数的指针，指向派生类时，只能调用纯虚函数中已经定义的，不能调用派生类中的接口
     */

    return 0;
}

#endif
