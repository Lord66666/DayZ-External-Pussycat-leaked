#pragma once
#include <Windows.h>
#include <string>
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_dx9.h"
#include "Imgui/imgui_internal.h"
#include "Imgui/imgui_impl_win32.h"

#pragma warning(disable : 4244)
#pragma warning(disable : 4267)
#pragma warning(disable : 4305)

typedef struct
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
}RGBA;

class Color
{
public:
	RGBA red = { 255,0,0,255 };
	RGBA Magenta = { 255,0,255,255 };
	RGBA yellow = { 255,255,0,255 };
	RGBA grayblue = { 128,255,255,255 };
	RGBA green = { 128,224,0,255 };
	RGBA darkgreen = { 0,255,128,255 };
	RGBA brown = { 192,96,0,255 };
	RGBA pink = { 255,168,255,255 };
	RGBA DarkYellow = { 216,216,0,255 };
	RGBA SilverWhite = { 236,236,236,255 };
	RGBA purple = { 144,0,255,255 };
	RGBA allitems = { 0,128,255,255 };
	RGBA Navy = { 88,48,224,255 };
	RGBA skyblue = { 0,136,255,255 };
	RGBA graygreen = { 128,160,128,255 };
	RGBA blue = { 0,96,255,255 };
	RGBA orange = { 255,128,0,255 };
	RGBA peachred = { 255,80,128,255 };
	RGBA reds = { 255,128,192,255 };
	RGBA darkgray = { 96,96,96,255 };
	RGBA Navys = { 0,0,128,255 };
	RGBA darkgreens = { 0,128,0,255 };
	RGBA darkblue = { 0,128,128,255 };
	RGBA redbrown = { 128,0,0,255 };
	RGBA purplered = { 128,0,128,255 };
	RGBA greens = { 0,255,0,255 };
	RGBA envy = { 0,255,255,255 };
	RGBA black = { 0,0,0,255 };
	RGBA gray = { 128,128,128,255 };
	RGBA white = { 255,255,255,255 };
	RGBA blues = { 30,144,255,255 };
	RGBA lightblue = { 135,206,250,255 };
	RGBA Scarlet = { 220, 20, 60, 255 };
	RGBA white_ = { 255,255,255,255 };
	RGBA gray_ = { 128,128,128,255 };
	RGBA black_ = { 0,0,0,255 };
	RGBA red_ = { 255,0,0,255 };
	RGBA Magenta_ = { 255,0,255,255 };
	RGBA yellow_ = { 255,255,0,255 };
	RGBA grayblue_ = { 128,128,255,255 };
	RGBA green_ = { 128,224,0,255 };
	RGBA darkgreen_ = { 0,224,128,255 };
	RGBA brown_ = { 192,96,0,255 };
	RGBA pink_ = { 255,168,255,255 };
	RGBA darkyellow_ = { 216,216,0,255 };
	RGBA silverwhite_ = { 236,236,236,255 };
	RGBA purple_ = { 144,0,255,255 };
	RGBA Blue_ = { 88,48,224,255 };
	RGBA skyblue_ = { 0,136,255,255 };
	RGBA graygreen_ = { 128,160,128,255 };
	RGBA blue_ = { 0,96,192,255 };
	RGBA orange_ = { 255,128,0,255 };
	RGBA pinks_ = { 255,80,128,255 };
	RGBA Fuhong_ = { 255,128,192,255 };
	RGBA darkgray_ = { 96,96,96,255 };
	RGBA Navy_ = { 0,0,128,255 };
	RGBA darkgreens_ = { 0,128,0,255 };
	RGBA darkblue_ = { 0,128,128,255 };
	RGBA redbrown_ = { 128,0,0,255 };
	RGBA purplered_ = { 128,0,128,255 };
	RGBA greens_ = { 0,255,0,255 };
	RGBA envy_ = { 0,255,255,255 };

	RGBA glassblack = { 0, 0, 0, 128 };
	RGBA GlassBlue = { 65,105,225,128 };
	RGBA glassyellow = { 255,255,0,255 };
	RGBA glass = { 200,200,200,60 };

	RGBA filled = { 0, 0, 0, 150 };

	RGBA Plum = { 255,160,255,255 };

	RGBA rainbow() {

		static float x = 0, y = 0;
		static float r = 0, g = 0, b = 0;

		if (y >= 0.0f && y < 255.0f) {
			r = 255.0f;
			g = 0.0f;
			b = x;
		}
		else if (y >= 255.0f && y < 510.0f) {
			r = 255.0f - x;
			g = 0.0f;
			b = 255.0f;
		}
		else if (y >= 510.0f && y < 765.0f) {
			r = 0.0f;
			g = x;
			b = 255.0f;
		}
		else if (y >= 765.0f && y < 1020.0f) {
			r = 0.0f;
			g = 255.0f;
			b = 255.0f - x;
		}
		else if (y >= 1020.0f && y < 1275.0f) {
			r = x;
			g = 255.0f;
			b = 0.0f;
		}
		else if (y >= 1275.0f && y < 1530.0f) {
			r = 255.0f;
			g = 255.0f - x;
			b = 0.0f;
		}

		x += 0.3f; //increase this value to switch colors faster
		if (x >= 255.0f)
			x = 0.0f;

		y += 0.3f; //increase this value to switch colors faster
		if (y > 1530.0f)
			y = 0.0f;


		return RGBA{ (DWORD)r, (DWORD)g, (DWORD)b, 255 };
	}

};

inline Color Col;

static std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

static std::string WStringToUTF8(const wchar_t* lpwcszWString)
{
	char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}
static std::wstring MBytesToWString(const char* lpcszString)
{
	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t*)pUnicode;
	delete[] pUnicode;
	return wString;
}

static void DrawString(float fontSize, int x, int y, RGBA* color, bool bCenter, bool stroke, const char* pText, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);

	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(buf);
		x = x - static_cast<int>(textSize.x / 2);
		y = y - static_cast<int>(textSize.y);
	}

	if (stroke)
	{
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), buf);
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), buf);
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), buf);
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), buf);
	}

	ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), buf);
}


static void DrawCircle(int x, int y, int radius, RGBA* color, int segments)
{
	ImGui::GetOverlayDrawList()->AddCircle(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), segments);
}

static void DrawCircleFilled(int x, int y, int radius, RGBA* color, int segments)
{
	ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), segments);
}

static void DrawFilledRect(int x, int y, int w, int h, RGBA* color)
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0);
}

static void DrawLine(int x1, int y1, int x2, int y2, RGBA* color, int thickness)
{
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), thickness);
}

static void DrawCorneredBox(int X, int Y, int W, int H, const ImU32& color, int thickness)
{
	float lineW = (W / 3);
	float lineH = (H / 3);

	////black outlines
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);

	//corners
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
}

static void DrawNewText(int x, int y, RGBA* color, const char* str)
{
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), str);
}

static void DrawStringWithBackGround(int x, int y, RGBA* back_color, RGBA* main_color, const char* pText, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);

	const ImVec2 text_dimension = ImGui::CalcTextSize(buf);
	const float text_width = text_dimension.x + 5.f;
	float mid_width = x - (text_width / 2.f);

	// Ensure the text doesn't go beyond the screen boundaries
	if (mid_width + text_width > ImGui::GetIO().DisplaySize.x) {
		mid_width = ImGui::GetIO().DisplaySize.x - text_width;
	}
	if (mid_width < 0) {
		mid_width = 0;
	}

	// Ensure DrawFilledRect doesn't go beyond the screen boundaries
	float rect_width = text_width + 10.f;
	if (mid_width + rect_width > ImGui::GetIO().DisplaySize.x) {
		rect_width = ImGui::GetIO().DisplaySize.x - mid_width;
	}

	DrawFilledRect(mid_width + 2.f, y - 25.f, rect_width, text_dimension.y + 5.f, back_color);
	DrawNewText(mid_width + 6.f, (y - 25.f) + 2.f, main_color, buf);
}


static void DrawPlayerBar(int x, int y, RGBA* back_color, RGBA* main_color, const char* pText, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());

	const ImVec2 text_dimension = ImGui::CalcTextSize(text.c_str());
	const float text_width = text_dimension.x + 5.f;
	const float mid_width = x - (text_width / 2.f);
	RGBA green_color = { 128,224,0,255 };

	DrawFilledRect(mid_width + 2.f, y - 25.f, text_width + 10.f, text_dimension.y + 5.f, back_color);
	DrawLine(mid_width, y - 25.f, mid_width, (y - 25.f) + text_dimension.y + 5.f, &green_color, 3.f);
	DrawNewText(mid_width + 6.f, (y - 25.f) + 2.f, main_color, text.c_str());

}

static void DrawMenuBar(int x, int y, RGBA* back_color, RGBA* main_color, const char* pText, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());

	const ImVec2 text_dimension = ImGui::CalcTextSize(text.c_str());
	const float text_width = text_dimension.x + 5.f;
	float mid_width = x - (text_width / 2.f);

	// Ensure the text doesn't go beyond the screen boundaries
	if (mid_width + text_width > ImGui::GetIO().DisplaySize.x) {
		mid_width = ImGui::GetIO().DisplaySize.x - text_width;
	}
	if (mid_width < 0) {
		mid_width = 0;
	}

	RGBA green_color = { 128, 224, 0, 255 };

	// Ensure DrawFilledRect doesn't go beyond the screen boundaries
	float rect_width = text_width + 10.f;
	if (mid_width + rect_width > ImGui::GetIO().DisplaySize.x) {
		rect_width = ImGui::GetIO().DisplaySize.x - mid_width;
	}

	DrawFilledRect(mid_width + 2.f, y - 25.f, rect_width, text_dimension.y + 5.f, back_color);
	DrawLine(mid_width, y - 25.f, mid_width, (y - 25.f) + text_dimension.y + 5.f, &green_color, 4.f);
	DrawNewText(mid_width + 6.f, (y - 25.f) + 2.f, main_color, text.c_str());
}

static void DrawsSilentBar(int x, int y, RGBA* back_color, RGBA* main_color, const char* pText, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());

	const ImVec2 text_dimension = ImGui::CalcTextSize(text.c_str());
	const float text_width = text_dimension.x + 5.f;
	float mid_width = x - (text_width / 2.f);

	// Ensure the text doesn't go beyond the screen boundaries
	if (mid_width + text_width > ImGui::GetIO().DisplaySize.x) {
		mid_width = ImGui::GetIO().DisplaySize.x - text_width;
	}
	if (mid_width < 0) {
		mid_width = 0;
	}

	RGBA gray_color = { 128, 128, 128, 255 };

	DrawFilledRect(mid_width + 2.f, y - 25.f, text_width + 10.f, text_dimension.y + 5.f, back_color);
	DrawLine(mid_width, y - 25.f, mid_width, (y - 25.f) + text_dimension.y + 5.f, &gray_color, 4.f);
	DrawNewText(mid_width + 6.f, (y - 25.f) + 2.f, main_color, text.c_str());
}

static void DrawWarningBar(int x, int y, RGBA* back_color, RGBA* main_color, const char* pText, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());

	const ImVec2 text_dimension = ImGui::CalcTextSize(text.c_str());
	const float text_width = text_dimension.x + 5.f;
	float mid_width = x - (text_width / 2.f);

	// Ensure the text doesn't go beyond the screen boundaries
	if (mid_width + text_width > ImGui::GetIO().DisplaySize.x) {
		mid_width = ImGui::GetIO().DisplaySize.x - text_width;
	}
	if (mid_width < 0) {
		mid_width = 0;
	}

	RGBA red_color = { 255, 0, 0, 255 };

	// Ensure DrawFilledRect doesn't go beyond the screen boundaries
	float rect_width = text_width + 10.f;
	if (mid_width + rect_width > ImGui::GetIO().DisplaySize.x) {
		rect_width = ImGui::GetIO().DisplaySize.x - mid_width;
	}

	DrawFilledRect(mid_width + 2.f, y - 25.f, rect_width, text_dimension.y + 5.f, back_color);
	DrawLine(mid_width, y - 25.f, mid_width, (y - 25.f) + text_dimension.y + 5.f, &red_color, 3.f);
	DrawLine(mid_width + rect_width, y - 25.f, mid_width + rect_width, (y - 25.f) + text_dimension.y + 5.f, &red_color, 3.f);  // Add this line
	DrawNewText(mid_width + 6.f, (y - 25.f) + 2.f, main_color, text.c_str());
}

static void DrawCornerBox(int x, int y, int w, int h, int borderPx, RGBA* color)
{
	DrawFilledRect(x + borderPx, y, w / 3, borderPx, color); //top 
	DrawFilledRect(x + w - w / 3 + borderPx, y, w / 3, borderPx, color); //top 
	DrawFilledRect(x, y, borderPx, h / 3, color); //left 
	DrawFilledRect(x, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color); //left 
	DrawFilledRect(x + borderPx, y + h + borderPx, w / 3, borderPx, color); //bottom 
	DrawFilledRect(x + w - w / 3 + borderPx, y + h + borderPx, w / 3, borderPx, color); //bottom 
	DrawFilledRect(x + w + borderPx, y, borderPx, h / 3, color);//right 
	DrawFilledRect(x + w + borderPx, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color);//right 
}