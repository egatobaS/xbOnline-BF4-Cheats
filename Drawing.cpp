#include "main.h"

UIRender::UIRender()
{
	StackData = 0;
	isDrawigSolid = false;
	SelectedSolidStyle = NULL;
	SelectedMovingStyle = NULL;
}

void UIRender::SetSolidTextStyle(int Data)
{
	StackData = Data;
	isDrawigSolid = true;
	SelectedSolidStyle = (SolidTextStyle*)*(int*)(*(int*)(Data + 0x14) + 0xA0);;
}

void UIRender::SetMovingTextStyle(int Data)
{
	StackData = Data;
	isDrawigSolid = false;
	SelectedMovingStyle = (MovingTextStyle*)*(int*)(*(int*)(Data + 0x14) + 0xA0);;;
}

void UIRender::SetColor(Vector4* color)
{
	if (isDrawigSolid)
	{
		SelectedSolidStyle->Color_R = color->x;
		SelectedSolidStyle->Color_G = color->y;
		SelectedSolidStyle->Color_B = color->z;
		SelectedSolidStyle->Color_A = color->a;
	}
	else
	{
		SelectedMovingStyle->Glow_R = color->x;
		SelectedMovingStyle->Glow_G = color->y;
		SelectedMovingStyle->Glow_B = color->z;
		SelectedMovingStyle->Glow_A = color->a;
	}
}

void UIRender::SetGlow(Vector4* color, float Intensity)
{
	if (isDrawigSolid)
	{
		SelectedSolidStyle->Glow_R = color->x;
		SelectedSolidStyle->Glow_G = color->y;
		SelectedSolidStyle->Glow_B = color->z;
		SelectedSolidStyle->Glow_A = color->a;

		SelectedSolidStyle->glow_Intensity = Intensity;
	}
	else
	{
		SelectedMovingStyle->Glow_R = color->x;
		SelectedMovingStyle->Glow_G = color->y;
		SelectedMovingStyle->Glow_B = color->z;
		SelectedMovingStyle->Glow_A = color->a;
	}
}

void UIRender::SetScale(float Scale)
{
	if (isDrawigSolid)
		SelectedSolidStyle->Scale = Scale;
	else
		SelectedMovingStyle->Scale = Scale;
}

void UIRender::DrawText(const char* Text, float FontScale, Vector4* Coords, Vector4* Color, Vector4* GlowColor, float GlowScale, int Halign, int Valign)
{
	if (!MmIsAddressValid((void*)Text))
		return;

	unsigned char Data[0x1000] = { 0 };

	if (!StackData || ((isDrawigSolid && !SelectedSolidStyle) || (!isDrawigSolid && !SelectedMovingStyle))) return;

	memcpy(Data, isDrawigSolid ? (void*)SelectedSolidStyle : (void*)SelectedMovingStyle, 0x1000);

	Vector4 Nothing = Vector4(0, 0, 0, 0);

	SetScale(FontScale);

	if (Color)
		SetColor(Color);

	if (GlowColor)
		SetGlow(GlowColor, GlowScale);
	else
		SetGlow(&Nothing, 0);

	int TextHandle = create(*(int*)(StackData + 0x58) + 0x2A8, Text, (isDrawigSolid) ? (int)SelectedSolidStyle : (int)SelectedMovingStyle);

	setAlignment(TextHandle, Halign, Valign);

	setText(TextHandle, Text, true);

	drawText(*(int*)(0x8991B90C), TextHandle, Coords, 1.0f);

	memcpy(isDrawigSolid ? (void*)SelectedSolidStyle : (void*)SelectedMovingStyle, Data, 0x1000);
}

void UIRender::DrawRect(float x, float y, float width, float height, Vector4* color)
{
	Vector4 box = Vector4(x, y, x + width, y + height);
	Vector4 _color = Vector4(color->x, color->y, color->z, color->a);

	drawRect(*(int*)(0x8991B90C), &box, &_color, 0xAD00000009);
}