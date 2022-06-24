#include "framework.h"

//////////////////////////////////////////////////////////////////////////
///@brief 해당 문자열에서 comp 문자를 rep로 변경
///@param str : 체크하려는 문자열
///@param comp : 비교문자열
///@param rep : 바꿀문자열
//////////////////////////////////////////////////////////////////////////
void Util::Replace(string* str, string comp, string rep)
{
	string temp = *str;

	size_t start_pos = 0;
	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
	{
		temp.replace(start_pos, comp.length(), rep);
		start_pos += rep.length();
	}

	*str = temp;
}

void Util::Replace(wstring* str, wstring comp, wstring rep)
{
	wstring temp = *str;

	size_t start_pos = 0;
	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
	{
		temp.replace(start_pos, comp.length(), rep);
		start_pos += rep.length();
	}

	*str = temp;
}

//////////////////////////////////////////////////////////////////////////
///@brief string형을 wstring형으로 변경
///@param value : 변환할 문자열
///@return 변환 완료 문자열
//////////////////////////////////////////////////////////////////////////
wstring Util::ToWString(string value)
{
	wstring temp = L"";
	temp.assign(value.begin(), value.end());

	return temp;
}

//////////////////////////////////////////////////////////////////////////
///@brief wstring형을 string형으로 변경
///@param value : 변환할 문자열
///@return 변환 완료 문자열
//////////////////////////////////////////////////////////////////////////
string Util::ToString(wstring value)
{
	string temp = "";
	temp.assign(value.begin(), value.end());

	return temp;
}