#pragma once
namespace Util
{

	void Replace(string* str, string comp, string rep);
	void Replace(wstring* str, wstring comp, wstring rep);

	wstring ToWString(string value);
	string ToString(wstring value);

	bool RayIntersectTri(Ray WRay, GameObject* Target, OUT Vector3& HitPoint);
}