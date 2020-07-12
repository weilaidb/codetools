#include "creturnpub.h"

#define STR_ERROR ("error")
#define STR_ERROR_CFGFILE_NOEXIST ("the config file or config not exist")

CReturnPub::CReturnPub()
{

}

QString CReturnPub::strError()
{
    return STR_ERROR;
}

QString CReturnPub::strConfigFileNoExist()
{
    return STR_ERROR_CFGFILE_NOEXIST;
}




