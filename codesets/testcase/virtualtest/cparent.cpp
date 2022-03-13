#include "cparent.h"
#include "debugApp.h"

CParent::CParent()
{

}


void CParent::sleep()
{
    debugApp() <<"parent " << "sleeping...";
}

void CParent::hello()
{
    debugApp() <<"parent " << "hello...";
}

void CParent::noherit()
{
    debugApp() <<"parent " << "noherit...";
}
