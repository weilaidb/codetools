#include "csystempub.h"

CSystemPub::CSystemPub()
{

}

void CSystemPub::execCmd(const char *command)
{
    if(command == NULL) return ;
    /**
WinExec 的windows 调用，可以通过参数SW_HIDE隐藏命令行黑窗口
并且命令的路径是可以带括号的
*/
//    WinExec(command,SW_HIDE);
    ShellExecuteA (NULL,"open",command,NULL,NULL,SW_SHOW);
}
