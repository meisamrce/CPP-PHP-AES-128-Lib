#include <iostream>
#include "AES.h"
#include "base64.h"

using namespace std;


const char g_key[17] = "0123456789012345";
const char g_iv[17] = "0123456789012345";
string EncryptionAES(const string& strSrc) 
{
	size_t length = strSrc.length();
	int block_num = length / BLOCK_SIZE + 1;
	char* szDataIn = new char[block_num * BLOCK_SIZE + 1];
	memset(szDataIn, 0x00, block_num * BLOCK_SIZE + 1);
	strcpy(szDataIn, strSrc.c_str());
 
	int k = length % BLOCK_SIZE;
	int j = length / BLOCK_SIZE;
	int padding = BLOCK_SIZE - k;
	for (int i = 0; i < padding; i++)
	{
		szDataIn[j * BLOCK_SIZE + k + i] = padding;
	}
	szDataIn[block_num * BLOCK_SIZE] = '\0';
 
	char *szDataOut = new char[block_num * BLOCK_SIZE + 1];
	memset(szDataOut, 0, block_num * BLOCK_SIZE + 1);
 
	AES aes;
	aes.MakeKey(g_key, g_iv, 16, 16);
	aes.Encrypt(szDataIn, szDataOut, block_num * BLOCK_SIZE, AES::CBC);
	string str = base64_encode((unsigned char*) szDataOut,
			block_num * BLOCK_SIZE);
	delete[] szDataIn;
	delete[] szDataOut;
	return str;
}
string DecryptionAES(const string& strSrc) 
{
	string strData = base64_decode(strSrc);
	size_t length = strData.length();
	char *szDataIn = new char[length + 1];
	memcpy(szDataIn, strData.c_str(), length+1);
	char *szDataOut = new char[length + 1];
	memcpy(szDataOut, strData.c_str(), length+1);
 
	AES aes;
	aes.MakeKey(g_key, g_iv, 16, 16);
	aes.Decrypt(szDataIn, szDataOut, length, AES::CBC);
 
	if (0x00 < szDataOut[length - 1] <= 0x16)
	{
		int tmp = szDataOut[length - 1];
		for (int i = length - 1; i >= length - tmp; i--)
		{
			if (szDataOut[i] != tmp)
			{
				memset(szDataOut, 0, length);
				cout << "q" << endl;
				break;
			}
			else
				szDataOut[i] = 0;
		}
	}
	string strDest(szDataOut);
	delete[] szDataIn;
	delete[] szDataOut;
	return strDest;
}

int main(int argc, char **argv)
{
	string str1 = "@dorsateam";
	cout << "text: " << str1 << endl;
	string str2 = EncryptionAES(str1);
	cout << "Encryption: " << str2 << endl;
	string str3 = DecryptionAES(str2);
	cout << "Decryption: " << str3 << endl;
}