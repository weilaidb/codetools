#ifndef CTREEPUB_H
#define CTREEPUB_H
#include <QMap>
#include <QMenu>

/**
 * 红黑树为二叉树，不适用于多级菜单
 * 应该使用多叉树
 *
 *
 */

typedef struct T_SubNode{
    bool m_isMenu;  //是否为菜单节点
    QString m_name; //节点名称
    QString m_parent; //父节点名称
    QString m_path; //节点路径
    quint8  m_mode;//操作模式
    union{
        QMenu *m_pMenu;
        QAction *m_pAction;
    }u;
}T_SubNode, *P_SubNode;




class CTreePub
{
public:
    CTreePub();
    static void procSubNode(QString filename);
    static void initSubNode(T_SubNode &node);
    static void printSubNode(T_SubNode &node);
    static bool setSubNode(T_SubNode &node, bool isMenu, QString path);
    static void freeSubNode(T_SubNode &node);
    static void showMenuSubNode();
    static QMenu *getTreeMenu(QString rootname);
    static void freeTreeMenu();
    static void procMenuAction(QMenu *pMenu, T_SubNode &tNode);

private:
    static QMap<QString, T_SubNode> m_menuSubNode;
    static QMap<QString, T_SubNode>::iterator m_menuIter;
    static QMap<QString, T_SubNode>::iterator m_menuFindIter;
    static QMenu *m_RootMenu;
};


#endif // CTREEPUB_H
