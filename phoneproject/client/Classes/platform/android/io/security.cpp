
#include "security.h"
#include "sha256.h"

namespace GNET
{

Security::Map& Security::GetMap()
{
	// ������GetMap���棬ȷ���ڵ���GetMapʱ��static �����϶�����ʼ����
	// ���������������cpp�У�ȷ��share.lib���Ա���ȷ���ӡ�
	static Security::Map map;
	return map;
}

int Random::fd = Random::Init();
static Random          __Random(RANDOM);
static NullSecurity    __NullSecurity_stub(NULLSECURITY);
static ARCFourSecurity __ARCFourSecurity_stub(ARCFOURSECURITY);
static MD5Hash         __MD5Hash_stub(MD5HASH);
static HMAC_MD5Hash    __HMAC_MD5Hash_stub(HMAC_MD5HASH);
static CompressARCFourSecurity  __CompressARCFourSecurity_stub(COMPRESSARCFOURSECURITY);
static DecompressARCFourSecurity  __DecompressARCFourSecurity_stub(DECOMPRESSARCFOURSECURITY);
static SHA256Hash         __SHA256Hash_stub(SHA256HASH);
//int64_t CompressARCFourSecurity::srcsize = 0;
//int64_t CompressARCFourSecurity::dstsize = 0;

    void SHA256Hash::init()
	{
		SHA256_Init(&alginfo);
	}
	Octets& SHA256Hash::Update(Octets &o)
	{
		SHA256_Update(&alginfo, (unsigned char*)o.begin(), o.size());
		return o;
	}
	Octets& SHA256Hash::Final(Octets &digest)
	{
		digest.resize(SHA256_DIGEST_VALUELEN);
		SHA256_Final(&alginfo, (unsigned char*)digest.begin());
		return digest;
	}
};
