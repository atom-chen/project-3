#ifndef __ASSETS_UPDATE_MGR_H__
#define __ASSETS_UPDATE_MGR_H__

#include <string>
#include "cocos2d.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

typedef void(*func)(void * p);

class download_param : public CCObject
{
	download_param():timeout(30),trytime(1),use_base64(false),use_resume(false),ret(false),download_finish_func(NULL),script_download_finish_func(NULL) {}
public:
	std::string src;	//�����ļ���url
	std::string des;	//�����ļ���·��
	std::string sub_path;	//�����ļ�����·��
	std::string filename;	//�����ļ�������
	int timeout;	//��������ĳ�ʱʱ��
	int trytime;	//��������ʧ�����Դ���
	bool use_base64;	//�Ƿ�ת����base64������ļ���
	bool use_resume;	//�Ƿ�ʹ�öϵ����£�md5�ļ����ܶϵ�����
	bool ret;	//���ؽ���֮���ж��ǳɹ�����ʧ��
	func download_finish_func;	//���ؽ���֮����õ�c�ص�����
	CCCallFunc* script_download_finish_func;	//���ؽ���֮����õĽű��ص�����

	static download_param * create()
	{
		download_param * pobj = new download_param();
		if (pobj)
		{
			pobj->autorelease();
		}
		return pobj;
	}

	//����Ǹ�lua�õ�
	static download_param * create(std::string _src, std::string _des, std::string _sub_path, std::string _filename,
			int _timeout, int _trytime, bool _use_base64, bool _use_resume, CCCallFunc* _script_download_finish_func)
	{
		download_param * pobj = new download_param();
		if (pobj)
		{
			pobj->src = _src;
			pobj->des = _des;
			pobj->sub_path = _sub_path;
			pobj->filename = _filename;
			pobj->timeout = _timeout;
			pobj->trytime = _trytime;
			pobj->use_base64 = _use_base64;
			pobj->use_resume = _use_resume;
			pobj->download_finish_func = NULL;
			pobj->script_download_finish_func = _script_download_finish_func;

			pobj->autorelease();
		}
		return pobj;
	}

	bool getRet() const
	{
		return ret;
	}
};

class update_param : public CCObject
{
	update_param():timeout(30),trytime(1),ret(false) {}
public:
	std::string resource_path;	//��ǰʹ�õ���Դ·��
	std::string download_path;	//�����ļ���ʱ����·��
	std::string src;	//�������ӵ�url
	std::string md5_file;	//md5�ļ�������
	std::vector<std::string> des;	//md5��ƥ����ļ�����
	int timeout;	//���صĵ�������ĳ�ʱʱ��
	int trytime;	//���صĵ�������ʧ�����Դ���
	bool ret;	//���½���֮���ж��ǳɹ�����ʧ��

	static update_param * create()
	{
		update_param * pobj = new update_param();
		if (pobj)
		{
			pobj->autorelease();
		}
		return pobj;
	}

	//����Ǹ�lua�õ�
	static update_param * create(std::string _resource_path, std::string _download_path, std::string _src, std::string _md5_file, int _timeout, int _trytime)
	{
		update_param * pobj = new update_param();
		if (pobj)
		{
			pobj->resource_path = _resource_path;
			pobj->download_path = _download_path;
			pobj->src = _src;
			pobj->md5_file = _md5_file;
			pobj->timeout = _timeout;
			pobj->trytime = _trytime;
			pobj->autorelease();
		}
		return pobj;
	}

	bool getRet() const
	{
		return ret;
	}
};

class AssetsUpdateManager
{
	enum AUM_STAT
	{
		AUMS_INIT,
		AUMS_UPDATE_MD5FILE,
		AUMS_UPDATE_MD5FILE_OK,
		AUMS_UPDATE_ONE_FILE,
		AUMS_UPDATE_ONE_FILE_OK,
		AUMS_UPDATE_OK,
		AUMS_UPDATE_FAILED,
	}m_stat;

	AssetsUpdateManager():m_stat(AUMS_INIT) {}

public:
	static AssetsUpdateManager* GetInstance()
	{
		static AssetsUpdateManager _stub;
		return &_stub;
	}

	bool IsExistDir(const char* szDir);
	bool createDir(const char *path);
	bool MakeDir(const char* dir,int r);
	bool deleteDir(const std::string& src);
	bool copyFiles(std::string src,std::string des);

	//����������������û�п����µ��̣߳������������Ļ��Ῠס���õ��߳�
	void downLoad(download_param * pdp);

	//����һ���µ��߳�ȥ����downLoad����
	void newThreadDownLoad(download_param * pdp);

	//��tick��ߵ��ø�����Դ,����false����û��������
	bool CheckUpdate(update_param * pup);
	void onFileDownLoadFinish(void * p);
    
    std::string GetDocumentPath();
    std::string GetTmpPath();
    std::string GetCachePath();

private:
	bool UnCompressFile(const std::string & src, const std::string & des);
	bool CheckMD5(update_param * pup);
	bool generateLocalMd5List(const std::string& root,std::map<std::string,std::string>& md5map,const std::string& baseDir);
};

#endif