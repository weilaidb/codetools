#include "cparent.h"
#include "debugApp.h"

CParent::CParent()
{

}


void CParent::sleep()
{
    debugApp() <<"parent " << "sleeping...";
}
