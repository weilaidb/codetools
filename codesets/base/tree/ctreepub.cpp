#include "ctreepub.h"
#include "csignpub.h"
#include "debugApp.h"
#include "cexpresspub.h"
#include "cstringpub.h"
#include "cmsgtips.h"
#include<stdio.h>

QMap<QString, T_SubNode> CTreePub::m_menuSubNode;
QMap<QString, T_SubNode>::Iterator CTreePub::m_menuIter;
QMap<QString, T_SubNode>::Iterator CTreePub::m_menuFindIter;
QMenu *CTreePub::m_RootMenu = nullptr;


CTreePub::CTreePub()
{
}



void CTreePub::procSubNode(QString filename)
{
    int pos = 0;
    QString strKey = filename;
    T_SubNode tNode;
    initSubNode(tNode);

    pos = strKey.lastIndexOf(CSignPub::signLXie());
    debugApp() << "pos:" << pos <<" , "<< strKey;
    m_menuIter = m_menuSubNode.find(strKey);
    if((m_menuSubNode.end() == m_menuIter)
            && setSubNode(tNode, false, strKey))
    {
        m_menuSubNode.insert(strKey, tNode);
    }

    while(-1 != pos)
    {
        strKey = strKey.mid(0,pos);
        pos = strKey.lastIndexOf(CSignPub::signLXie());
        debugApp() << "pos:" << pos <<" , "<< strKey;
        m_menuIter = m_menuSubNode.find(strKey);
        if((m_menuSubNode.end() == m_menuSubNode.find(strKey))
                && setSubNode(tNode, true, strKey))
        {
            m_menuSubNode.insert(strKey, tNode);
        }
    }

    //    showMenuSubNode();

}


void CTreePub::initSubNode(T_SubNode &node)
{
    node.m_path.clear();
    node.m_name.clear();
    node.m_parent.clear();
    node.m_isMenu = false;
    node.u.m_pMenu = nullptr;
    node.u.m_pAction = nullptr;
}

void CTreePub::printSubNode(T_SubNode &node)
{
    debugApp() << "isMenu:" << node.m_isMenu << ", name:" << node.m_name << ", path:" << node.m_path
               << ", parent:" << node.m_parent  ;
}

bool CTreePub::setSubNode(T_SubNode &node, bool isMenu, QString path)
{
    node.m_path = path;
    int pos = path.lastIndexOf(CSignPub::signLXie());
    if(-1 != pos)
    {
        node.m_name = path.mid(pos + 1,path.length());
        node.m_parent = path.mid(0, pos);
    }
    else
    {
        node.m_name = path;
        node.m_parent = CStringPub::emptyString();
    }
    node.m_isMenu = isMenu;
    //检测不是菜单的时，path是否包含Xie
    if (CExpressPub::isFalse(isMenu))
    {
        if(CExpressPub::isIndexXieLine(node.m_name))
        {
            return false;
        }
    }

    return true;
}


void CTreePub::showMenuSubNode()
{
    debugApp() << "show menu subnoce";
    for(m_menuIter = m_menuSubNode.begin(); m_menuIter != m_menuSubNode.end(); m_menuIter++)
    {
        T_SubNode tNode;
        initSubNode(tNode);
        tNode = m_menuIter.value();
        printSubNode(tNode);
    }
}

QMenu *CTreePub::getTreeMenu(QString rootname)
{
    m_RootMenu = new QMenu(rootname);
    for(m_menuIter = m_menuSubNode.begin(); m_menuIter != m_menuSubNode.end(); m_menuIter++)
    {
        T_SubNode &tNode = m_menuIter.value();
        /**
  *生成多级菜单
  *根路径
  */
//        printSubNode(tNode);
        if(CExpressPub::isZero(tNode.m_parent.length()))
        {
            if(tNode.m_isMenu)
            {
                tNode.u.m_pMenu = new QMenu(tNode.m_name);
                m_RootMenu->addMenu(tNode.u.m_pMenu);
            }
            else
            {
                tNode.u.m_pAction = new QAction(tNode.m_name);
                m_RootMenu->addAction(tNode.u.m_pAction);
            }
            debugApp() << "root:" << tNode.m_name;
            continue;
        }

        /**
          * 处理其它节点
          * 在父菜单上添加子菜单或子项
          **/
        m_menuFindIter = m_menuSubNode.find(tNode.m_parent);
        if(m_menuIter != m_menuSubNode.end())
        {
            if(tNode.m_isMenu)
            {
                QMenu *pMenu = new QMenu(tNode.m_name);
                tNode.u.m_pMenu = pMenu;
                m_menuFindIter.value().u.m_pMenu->addMenu(pMenu);
                debugApp() << "m_isMenu";
            }
            else
            {
                QAction *pAction = new QAction(tNode.m_name);
                tNode.u.m_pAction = pAction;
                //如果父节点也为根节点，不处理，可提示用户异常
                if(m_menuFindIter.value().u.m_pMenu && m_menuFindIter.value().m_isMenu)
                {
                    m_menuFindIter.value().u.m_pMenu->addAction(pAction);
                    debugApp() << "m_isAction";
                }
                else
                {
                    debugApp() << "parent is not a menu";
                    ShowTipsInfo(QString("%1 node invalid!!").arg(tNode.m_path));
                }
            }
        }
        else
        {
            debugApp() << "parent menu no exist!!";
        }
    }

    return m_RootMenu;
}


void CTreePub::freeTreeMenu()
{
    delete m_RootMenu;
    for(m_menuIter = m_menuSubNode.begin(); m_menuIter != m_menuSubNode.end(); m_menuIter++)
    {
        T_SubNode &tNode = m_menuIter.value();
        freeSubNode(tNode);
    }
    m_menuSubNode.clear();

}

void CTreePub::freeSubNode(T_SubNode &node)
{
    node.m_name.clear();
    node.m_path.clear();
    node.m_parent.clear();
    if(node.u.m_pMenu)
    {
        delete node.u.m_pMenu;
        node.u.m_pMenu = nullptr;
    }

    if(node.u.m_pAction)
    {
        delete node.u.m_pAction;
        node.u.m_pAction = nullptr;
    }

}


