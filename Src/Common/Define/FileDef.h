/********************************************************************************
 *	文件名：	FileDef.h
 *	全路径：	d:\Prj\Server\Server\Base\FileDef.h
 *	创建人：	胡繁
 *	创建时间：	2005 年 11 月 6 日	18:26
 *
 *	功能说明：	所有的配置文件的宏定义
 *	修改记录：
*********************************************************************************/

#ifndef __FILEDEF_H__
#define __FILEDEF_H__

//#define FILE_SERVER_VERSION					"K:/成吉思汗/Versions/sn.txt"

//Config 目录

#define FILE_CONFIG_INFO					"../Config/ConfigInfo.ini"
#define FILE_SERVER_INFO					"../Config/ServerInfo.ini"

// 其他

#define FILE_AI_SCRIPT						"../Public/Data/AIScript.tab"
#define FILE_SCRIPT							"../Public/Data/Script.tab"

#define PATH_AI_SCRIPT						"../Public/Data/AIScript/"
#define PATH_SCENE							"./scene/"



#define GET_FULL_PATH(fullpath, filepath, filename)	do { \
		sprintf(fullpath, "%s%s", (filepath), (filename)); \
	} while (0)

#define GET_AI_SCRIPT_FULL_PATH(fullpath, filename) GET_FULL_PATH(fullpath, PATH_AI_SCRIPT, (filename))
#define GET_SCENE_FULL_PATH(fullpath, filename) GET_FULL_PATH(fullpath, PATH_SCENE, (filename))
#endif // __FILEDEF_H__