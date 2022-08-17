#pragma once
namespace Util
{

	void Replace(string* str, string comp, string rep);
	void Replace(wstring* str, wstring comp, wstring rep);

	wstring ToWString(string value);
	string ToString(wstring value);

	float NormalizeAngle(float angle);
	Vector3 NormalizeAngles(Vector3 angles);
	Vector3 QuaternionToYawPtichRoll(Quaternion q1);


	bool RayIntersectTri(IN Ray WRay, IN GameObject* Target, OUT Vector3& HitPoint);
	bool RayIntersectTriNear(IN Ray WRay, IN GameObject* Target, OUT Vector3& HitPoint);
	Ray MouseToRay(Vector3 Mouse, Camera* Cam);
}