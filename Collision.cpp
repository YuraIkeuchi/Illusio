#include "Collision.h"

#include <d3dcompiler.h>
#include <DirectXTex.h>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

//\‘¢‘Ì
struct BoxVertex
{
	float Up;
	float Down;
	float Left;
	float Right;
};

bool  Collision::BoxCollision_Down(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2) {
	BoxVertex Object1;
	BoxVertex Object2;

	//object1‚Ì‰E’¸“_
	Object1.Right = object1.x + radius1.x * 2;
	//object1‚Ì¶’¸“_
	Object1.Left = object1.x;
	//object1‚Ìã’¸“_
	Object1.Up = object1.y + radius1.y;
	//object1‚Ì‰º’¸“_
	Object1.Down = object1.y - radius1.y;

	//object1‚Ì¶’¸“_
	Object2.Left = object2.x;
	//object1‚Ì‰E’¸“_
	Object2.Right = object2.x + radius2.x * 2;
	//object1‚Ì‰º’¸“_
	Object2.Down = object2.y - radius2.y;
	//object1‚Ìã’¸“_
	Object2.Up = Object2.Down + 1;
	//¨‚P‚Æ¶‚Q@¨‚Q‚Æ¶‚P@ã‚P‚Æ‰º‚Q@ã‚Q‚Æ‰º‚P
	return Object1.Right > Object2.Left && Object2.Right > Object1.Left && Object1.Up >= Object2.Down && Object2.Up >= Object1.Down;
}

bool Collision::BoxCollision_Up(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2) {
	BoxVertex Object1;
	BoxVertex Object2;

	//object1‚Ì‰E’¸“_
	Object1.Right = object1.x + radius1.x * 2;
	//object1‚Ì¶’¸“_
	Object1.Left = object1.x;
	//object1‚Ìã’¸“_
	Object1.Up = object1.y + radius1.y;
	//object1‚Ì‰º’¸“_
	Object1.Down = object1.y - radius1.y;

	//object1‚Ì¶’¸“_
	Object2.Left = object2.x;
	//object1‚Ì‰E’¸“_
	Object2.Right = object2.x + radius2.x * 2;
	//object1‚Ìã’¸“_
	Object2.Up = object2.y + radius2.y;
	//object1‚Ì‰º’¸“_
	Object2.Down = Object2.Up - 1;
	//¨‚P‚Æ¶‚Q@¨‚Q‚Æ¶‚P@ã‚P‚Æ‰º‚Q@ã‚Q‚Æ‰º‚P
	return Object1.Right > Object2.Left && Object2.Right > Object1.Left && Object1.Up >= Object2.Down && Object2.Up >= Object1.Down;
}

bool Collision::BoxCollision_Left(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2) {
	BoxVertex Object1;
	BoxVertex Object2;

	//object1‚Ì‰E’¸“_
	Object1.Right = object1.x + radius1.x;
	//object1‚Ì¶’¸“_
	Object1.Left = object1.x;
	//object1‚Ìã’¸“_
	Object1.Up = object1.y + radius1.y;
	//object1‚Ì‰º’¸“_
	Object1.Down = object1.y - radius1.y;

	//object1‚Ì¶’¸“_
	Object2.Left = object2.x;
	//object1‚Ì‰E’¸“_
	Object2.Right = Object2.Left + 1;
	//object1‚Ì‰º’¸“_
	Object2.Down = object2.y - radius2.y + 0.5;
	//object1‚Ìã’¸“_
	Object2.Up = object2.y + radius2.y - 0.5;

	//¨‚P‚Æ¶‚Q@¨‚Q‚Æ¶‚P@ã‚P‚Æ‰º‚Q@ã‚Q‚Æ‰º‚P
	return Object1.Right > Object2.Left && Object2.Right > Object1.Left && Object1.Up >= Object2.Down && Object2.Up >= Object1.Down;
}

bool Collision::BoxCollision_Right(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2) {
	BoxVertex Object1;
	BoxVertex Object2;

	//object1‚Ì‰E’¸“_
	Object1.Right = object1.x + radius1.x;
	//object1‚Ì¶’¸“_
	Object1.Left = object1.x;
	//object1‚Ìã’¸“_
	Object1.Up = object1.y + radius1.y;
	//object1‚Ì‰º’¸“_
	Object1.Down = object1.y - radius1.y;

	//object1‚Ì‰E’¸“_
	Object2.Right = object2.x + radius2.x;
	//object1‚Ì¶’¸“_
	Object2.Left = Object2.Right - 1;
	//object1‚Ì‰º’¸“_
	Object2.Down = object2.y - radius2.y + 0.5;
	//object1‚Ìã’¸“_
	Object2.Up = object2.y + radius2.y - 0.5;

	//¨‚P‚Æ¶‚Q@¨‚Q‚Æ¶‚P@ã‚P‚Æ‰º‚Q@ã‚Q‚Æ‰º‚P
	return Object1.Right > Object2.Left && Object2.Right > Object1.Left && Object1.Up >= Object2.Down && Object2.Up >= Object1.Down;
}

bool Collision::CircleCollision(const float& X1, const float& Y1, const float& R1, const float& X2, const float& Y2, const float& R2) {
	int a = X1 - X2;
	int b = Y1 - Y2;
	int distance = sqrtf(a * a + b * b);
	int radius = R1 + R2;
	if (distance <= radius) {
		return true;
	} else {
		return false;
	}

	return true;
}

