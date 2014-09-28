#include <WStrToUTF8.h>

#ifdef WIN32
#include "gnoctets.h"
#else
#include "octets.h"
#endif

int Utf8ToWStr(const char* pInput, char* pOutput)  
{  
	int outputSize = 0; //��¼ת�����Unicode�ַ������ֽ���  

	char *tmp = pOutput; //��ʱ���������ڱ�������ַ���  
	while (*pInput)  
	{  
		if (*pInput > 0x00 && *pInput <= 0x7F) //�����ֽ�UTF8�ַ���Ӣ����ĸ�����֣�  
		{  
			*tmp = *pInput;  
			tmp++;  
			*tmp = 0; //С�˷���ʾ���ڸߵ�ַ�0  
		}  
		else if (((*pInput) & 0xE0) == 0xC0) //����˫�ֽ�UTF8�ַ�  
		{  
			char high = *pInput;  
			pInput++;  
			char low = *pInput;  
			if ((low & 0xC0) != 0x80)  //����Ƿ�Ϊ�Ϸ���UTF8�ַ���ʾ  
			{  
				return -1; //��������򱨴�  
			}  

			*tmp = (high << 6) + (low & 0x3F);  
			tmp++;  
			*tmp = (high >> 2) & 0x07;  
		}  
		else if (((*pInput) & 0xF0) == 0xE0) //�������ֽ�UTF8�ַ�  
		{  
			char high = *pInput;  
			pInput++;  
			char middle = *pInput;  
			pInput++;  
			char low = *pInput;  
			if (((middle & 0xC0) != 0x80) || ((low & 0xC0) != 0x80))  
			{  
				return -1;  
			}  
			*tmp = (middle << 6) + (low & 0x7F);  
			tmp++;  
			*tmp = (high << 4) + ((middle >> 2) & 0x0F);   
		}  
		else //���������ֽ�����UTF8�ַ������д���  
		{  
			return -1;  
		}  
		pInput ++;  
		tmp ++;  
		outputSize += 2;  
	}  
	*tmp = 0;  
	tmp++;  
	*tmp = 0;  
	return outputSize;  
}  

int Utf8ToWStr(const char* pInput, std::vector<char> &result)
{
	result.resize((strlen(pInput)+1)*2);
	return Utf8ToWStr(pInput, &result.front());
}

int Utf8ToWStr(const std::string &src, std::vector<char> &result)
{
	result.resize((src.size()+1)*2);
	return Utf8ToWStr(src.c_str(), &result.front());
}

//! convert from wstring to UTF8 using self-coding-converting

void WStrToUTF8(std::string& dest, const unsigned short* src, int size)
{
	dest.clear();
	for (int i = 0; i < size; i++)
	{
		unsigned short w = src[i];
		if (w <= 0x7f)
			dest.push_back((char)w);
		else if (w <= 0x7ff)
		{
			dest.push_back(0xc0 | ((w >> 6)& 0x1f));
			dest.push_back(0x80| (w & 0x3f));
		}
		else if (w <= 0xffff)
		{
			dest.push_back(0xe0 | ((w >> 12)& 0x0f));
			dest.push_back(0x80| ((w >> 6) & 0x3f));
			dest.push_back(0x80| (w & 0x3f));
		}
		//else if (sizeof(wchar_t) > 2 && w <= 0x10ffff)
		//{
		//	dest.push_back(0xf0 | ((w >> 18)& 0x07)); // wchar_t 4-bytes situation
		//	dest.push_back(0x80| ((w >> 12) & 0x3f));
		//	dest.push_back(0x80| ((w >> 6) & 0x3f));
		//	dest.push_back(0x80| (w & 0x3f));
		//}
		else
			dest.push_back('?');
	}
}

//! simple warpper
std::string WStrToUTF8(const unsigned short* str, int size)
{
	std::string result;
	WStrToUTF8(result, str, size);
	return result;
}

std::string WStrToUTF8(const GNET::Octets &o)
{
	return WStrToUTF8((const unsigned short*)o.begin(), o.size() / sizeof(unsigned short));
}