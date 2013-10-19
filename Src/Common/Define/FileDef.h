/********************************************************************************
 *	�ļ�����	FileDef.h
 *	ȫ·����	d:\Prj\Server\Server\Base\FileDef.h
 *	�����ˣ�	����
 *	����ʱ�䣺	2005 �� 11 �� 6 ��	18:26
 *
 *	����˵����	���е������ļ��ĺ궨��
 *	�޸ļ�¼��
*********************************************************************************/

#ifndef __FILEDEF_H__
#define __FILEDEF_H__

//#define FILE_SERVER_VERSION					"K:/�ɼ�˼��/Versions/sn.txt"

//Config Ŀ¼

#define FILE_CONFIG_INFO					"../Config/ConfigInfo.ini"
#define FILE_SERVER_INFO					"../Config/ServerInfo.ini"

// ����

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