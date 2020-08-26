# -*- coding: utf-8 -*-

import pymysql.cursors
from datetime import datetime

def initDatabase(host, usr, pwd, port, charset):
    # 连接数据库
    connect = pymysql.Connect(
        host=host,
        user=usr,
        passwd=pwd,
        port=port,
        # db=databasename,
        charset=charset
    )
    return  connect


def createDataBase(cursor,connect, databasename):
    try:
        # 执行 SQL 语句
        sql = 'create database if not exists %s' % databasename
        cursor.execute(sql)
        # 提交修改
        connect.commit()
        print("creat database ok,", databasename)
    except Exception as e:
        # 发生错误时回滚
        connect.rollback()
        print("create database failed, reason:", e)


def selectDataBase(connect, databasename):
    connect.select_db(databasename)

##创建表，输入参数:
#cursor: 游标
#connect: 连接信息
#tablename: 表名
#midexpress: 中间表达式
def createTablePub(cursor, connect, tablename, midexpress):
    print("------------------------")
    print ("tablename:%s" % tablename)

    sql = '''
        CREATE TABLE `%s` (
        `id` int(200) unsigned NOT NULL AUTO_INCREMENT,
        `name` varchar(200) NOT NULL COMMENT 'keyword',
        `content` varchar(10000) NOT NULL COMMENT 'content for show',
        PRIMARY KEY (`id`),
        UNIQUE KEY `name_UNIQUE` (`name`)
    ) ENGINE=InnoDB AUTO_INCREMENT=1051 DEFAULT CHARSET=utf8mb4;
      ''' % (tablename)



    print ("sql:%s" % sql)
    try:
        # 执行 SQL 语句
        # cursor.execute("drop table if exists trade")
        cursor.execute(sql)
        # 提交修改
        connect.commit()
        # print("creat table ok")
    except Exception as e:
        # 发生错误时回滚
        connect.rollback()
        print("create table failed, reason:", e)


def createTable(cursor, connect, tablename):
    try:
        sql = '''`name` varchar(1000) NOT NULL COMMENT 'keyword',
      `content` varchar(10000) NOT NULL COMMENT 'content for show' ,
      '''
        print ("sql:%s" % sql)
        print ("tablename:%s" % tablename)

        createTablePub(cursor, connect, tablename, sql)
    except Exception as e:
        # 发生错误时回滚
        connect.rollback()
        print("create table failed, reason:", e)


def insertTable(cursor,connect, tablename):
    # 插入数据
    for i in range(100):
        try:
            sql = '''INSERT INTO ''' + tablename + ''' (name, content) VALUES ( "%s", "%s")'''
            data = ('test' + str(i * 12), '13512345678')
            cursor.execute(sql % data)
            connect.commit()
            print('成功插入', cursor.rowcount, '条数据, curpos:', i + 1)
        except Exception as e :
            print('失败插入', cursor.rowcount, '条数据, reason:', e, 'curpos', i + 1)

#data format
# data = ('test' + str(i * 12), '13512345678')
def insertTableData(cursor,connect, tablename,data):
    # 插入数据
    try:
        name, content = data
        newname = name.replace('"', '""')
        newcontent = content.replace('"','""')
        newdata = (newname, newcontent)
        sql = '''INSERT INTO ''' + tablename + ''' (name, content) VALUES ( "%s", "%s")'''
        # data = ('test' + str(i * 12), '13512345678')
        cursor.execute(sql % newdata)
        connect.commit()
        print('成功插入', cursor.rowcount, '条数据, curpos:',1)
        return  True
    except Exception as e :
        print('失败插入', cursor.rowcount, '条数据, reason:', e, 'curpos', 1)
        return  False



def insertTableDataNameWithTime(cursor,connect, tablename,data):
    # 插入数据
    try:
        # print(data)
        # print(data[0])
        # print(data[1])
        name, content = data
        name2 = name + ' ' * 20 +str(datetime.now())
        print(name2)
        print(content)
        newdata = (name2, content)
        return  insertTableData(cursor,connect, tablename,newdata)
    except Exception as e :
        print('失败插入', cursor.rowcount, '条数据, reason:', e, 'curpos', 1)
        return  False



def modifyTable(cursor,connect, tablename):
    # 修改数据
    sql = "UPDATE " + tablename + " SET content = '%s' WHERE content = '%s' "
    data = ('13512345678 * 2', '13512345678')
    cursor.execute(sql % data)
    connect.commit()
    print('成功修改', cursor.rowcount, '条数据')




def searchTale(cursor,connect, tablename):
    # 查询数据
    sql = "SELECT name,content FROM " + tablename + " WHERE content = '%s' "
    data = ('13512345678',)
    cursor.execute(sql % data)
    # for row in cursor.fetchall():
    #     print("Name:%s\tSaving:%.2f" % row)
    print('共查找出', cursor.rowcount, '条数据')

def deleteTable(cursor,connect, tablename):
    # 删除数据
    sql = "DELETE FROM " + tablename + " WHERE content = '%s' LIMIT %d"
    data = ('13512345678', 1)
    cursor.execute(sql % data)
    connect.commit()
    print('成功删除', cursor.rowcount, '条数据')

def atomCommit(cursor,connect, tablename):
    # 事务处理
    sql_1 = "UPDATE " + tablename + " SET content = content + 1000 WHERE content = '18012345678' "
    sql_2 = "UPDATE " + tablename + " SET content = content + 1000 WHERE content = '18012345678' "
    sql_3 = "UPDATE " + tablename + " SET content = content + 2000 WHERE content = '18012345678' "

    try:
        cursor.execute(sql_1)  # 储蓄增加1000
        cursor.execute(sql_2)  # 支出增加1000
        cursor.execute(sql_3)  # 收入增加2000
    except Exception as e:
        connect.rollback()  # 事务回滚
        print('事务处理失败', e)
    else:
        connect.commit()  # 事务提交
        print('事务处理成功', cursor.rowcount)

def closeDatabase(cursor, connect):
    # 关闭连接
    cursor.close()
    connect.close()



def one_pymysql_test(databasename,tablename, host, usr,pwd,port,charset):
    ##################################### main functions#######################
    connect = initDatabase(host, usr, pwd,port,charset)
    # 获取游标
    cursor = connect.cursor()
    createDataBase(cursor, connect, databasename)
    selectDataBase(connect, databasename)
    createTable(cursor, connect, tablename)
    insertTable(cursor, connect, tablename)
    modifyTable(cursor, connect, tablename)
    searchTale(cursor, connect, tablename)
    deleteTable(cursor, connect, tablename)
    atomCommit(cursor, connect, tablename)
    closeDatabase(cursor, connect)


def insert_content(databasename,tablename, host, usr,pwd,port,charset,data):
    ##################################### main functions#######################
    connect = initDatabase(host, usr, pwd,port,charset)
    # 获取游标
    cursor = connect.cursor()
    createDataBase(cursor, connect, databasename)
    selectDataBase(connect, databasename)
    createTable(cursor, connect, tablename)
    retval = insertTableData(cursor, connect, tablename, data)
    closeDatabase(cursor, connect)
    return retval


def insert_contentNameWithTime(databasename,tablename, host, usr,pwd,port,charset,data):
    ##################################### main functions#######################
    connect = initDatabase(host, usr, pwd,port,charset)
    # 获取游标
    cursor = connect.cursor()
    createDataBase(cursor, connect, databasename)
    selectDataBase(connect, databasename)
    createTable(cursor, connect, tablename)
    retval = insertTableDataNameWithTime(cursor, connect, tablename, data)
    closeDatabase(cursor, connect)
    return retval



def test_insert_contet(data=('Qt si good', 'Qt是什么内容呢')):
    insert_content('alldb', 'abc', 'localhost', 'root', 'Zzerp123', 3306, 'utf8',
                   data)

def default_insert_contetNameWithTime(databasename='alldb',
                                      tablename='abc',
                                      host='localhost',
                                      usr='root',
                                      pwd='Zzerp123',
                                      port=3306,
                                      charset='utf8',
                                      data=('Qt si good', 'Qt是什么内容呢'),
                                      namewithtime=True):
    if(namewithtime> 0):
        return  insert_contentNameWithTime(databasename, tablename,host , usr,pwd ,port ,charset ,
                                           data)
    else:
        return insert_content(databasename, tablename,host , usr,pwd ,port ,charset ,
                              data)


if __name__ == '__main__':
    # one_pymysql_test('python10','a6', 'localhost', 'root', 'Zzerp123',3306,'utf8')
    # test_insert_contet(data=('Qt si good11', 'Qt是什么内容呢'))
    default_insert_contetNameWithTime(data=('Qt si good22', 'Qt是什么内容呢'))
    # default_insert_contetNameWithTime(data=('Qt si good22', 'Qt是什么内容呢'), namewithtime=False)
    # print(str(datetime.now()))