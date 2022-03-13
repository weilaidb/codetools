#include "cson.h"
#include "cparent.h"
#include "cgrandmaster.h"
#include "gmock/gmock.h"


using namespace ::testing;


class AnCSonTest: public Test {
public:
   CSon obj;
   CParent parobj;
   CSon *pObj;
   CParent *pParobj;
//   CGrandMaster grandobj;

   void SetUp() {

   }

   void TearDown() {

   }
};


TEST_F(AnCSonTest, Hello) {
    obj.hello();
    obj.sleep();
    obj.iamson();
    obj.song();
    obj.noherit();


    parobj.hello();
    parobj.sleep();
    parobj.song();
    parobj.noherit();

    pParobj = &obj;
    pParobj->hello();
    pParobj->sleep();
    pParobj->noherit();
    pParobj->song();

//    pObj = &pParobj;
//    pObj->hello();
//    pObj->sleep();

   //ASSERT_THAT(address, Eq());
   //ASSERT_TRUE(address == Eq());
   //ASSERT_FALSE(address == Eq());
   //ASSERT_FALSE(address == Ge());
   //ASSERT_FALSE(address == Le());
}

