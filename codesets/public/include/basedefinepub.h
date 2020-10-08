#ifndef BASEDEFINEPUB_H
#define BASEDEFINEPUB_H


#ifndef ARRAYSIZE
#define ARRAYSIZE(A) (unsigned int)(sizeof(A)/sizeof(A[0]))
#endif




#ifndef ARRAYSIZEX
#define ARRAYSIZEX(A) static_cast<unsigned int>(sizeof(A)/sizeof(A[0]))
#endif

#define UNUSED(A) (void)A



/**
  ** Astyle 处理文件超过数量时，弹出是否要处理的告警
  **/
#define ASTYLE_PROC_FILES_MAX (100)

/**
  ** Astyle Recent显示的最大条目
  **/
#define FILES_ASTYLE_RECENT_MAX (30)



#define SHOWCURFUNC debugApp() << __FUNCTION__


#endif // BASEDEFINEPUB_H
