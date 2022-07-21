#include "framework.h"

//////////////////////////////////////////////////////////////////////////
///@brief �ش� ���ڿ����� comp ���ڸ� rep�� ����
///@param str : üũ�Ϸ��� ���ڿ�
///@param comp : �񱳹��ڿ�
///@param rep : �ٲܹ��ڿ�
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
///@brief string���� wstring������ ����
///@param value : ��ȯ�� ���ڿ�
///@return ��ȯ �Ϸ� ���ڿ�
//////////////////////////////////////////////////////////////////////////
wstring Util::ToWString(string value)
{
	wstring temp = L"";
	temp.assign(value.begin(), value.end());

	return temp;
}

//////////////////////////////////////////////////////////////////////////
///@brief wstring���� string������ ����
///@param value : ��ȯ�� ���ڿ�
///@return ��ȯ �Ϸ� ���ڿ�
//////////////////////////////////////////////////////////////////////////
string Util::ToString(wstring value)
{
	string temp = "";
	temp.assign(value.begin(), value.end());

	return temp;
}

bool Util::RayIntersectTri(Ray WRay, GameObject* Target, OUT Vector3& HitPoint)
{
	if (not Target->mesh) return false;

	Matrix inverse = Target->W.Invert();

	WRay.direction = Vector3::TransformNormal(WRay.direction, inverse);
	WRay.direction.Normalize();

	WRay.position = Vector3::Transform(WRay.position, inverse);

	for (UINT i = 0; i < Target->mesh->GetIndexCount(); i += 3)
	{
		Vector3 v[3];
		v[0] = Target->mesh->GetVertexPosition(i);
		v[1] = Target->mesh->GetVertexPosition(i + 1);
		v[2] = Target->mesh->GetVertexPosition(i + 2);

		float Dis;
		if (WRay.Intersects(v[0], v[1], v[2], Dis))
		{
			//��Į�� x����
			HitPoint = WRay.position + (WRay.direction * Dis);
			// �ٽ� W�� ��ȯ
			HitPoint = Vector3::Transform(HitPoint, Target->W);
			return true;
		}
	}

	return false;
}
