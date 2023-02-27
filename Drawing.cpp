#include "Drawing.h"

LPCSTR Drawing::lpWindowName = "ImGui Standalone";
ImVec2 Drawing::vWindowSize = { 500, 500 };
ImGuiWindowFlags Drawing::WindowFlags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize;
bool Drawing::bDraw = true;

void Drawing::Active()
{
	bDraw = true;
}

bool Drawing::isActive()
{
	return bDraw == true;
}

#include "./Header.h"

void LoginThing()
{
	std::string KeyAuth_USER_Key_str(KeyAuth_USER_Key_char);
	std::string KeyAuth_license_URL = "https://keyauth.win/api/1.2/?type=license&key=" + KeyAuth_USER_Key_str + "&hwid=" + KeyAuth_USER_HWID + "&sessionid=" + KeyAuth_sessionid + "&name=Test&ownerid=XXX";
	wrap::Response r1 = wrap::HttpsRequest(wrap::Url{ KeyAuth_license_URL.c_str() }, wrap::Method{ "POST" });
	Text = r1.text;
	json data1 = json::parse(r1.text);
	KeyAuth_message = data1.value("message", "Not Found");
	if (KeyAuth_message == "Logged in!") {
		LoggedIn = true;
	}
	MessageBoxA(NULL, Text.c_str(), "Test", MB_ICONEXCLAMATION | MB_OK);
}

void Drawing::Draw()
{
	if (FirstStart == true){

		wrap::Response r = wrap::HttpsRequest(wrap::Url{ KeyAuth_init_URL.decrypt() }, wrap::Method{"POST"});
		KeyAuth_init_URL.encrypt();
		Text = r.text;
		json data = json::parse(r.text);
		KeyAuth_message = data.value("message", "Not Found");
		KeyAuth_sessionid = data.value("sessionid", "Not Found");
		if (KeyAuth_message != "Initialized"){
			LoggedIn = true;
		}
		MessageBoxA(NULL, Text.c_str(), "Test", MB_ICONEXCLAMATION | MB_OK);

		FirstStart = false;
	}
	if (isActive())
	{
		ImGui::SetNextWindowSize(vWindowSize);
		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::Begin(lpWindowName, &bDraw, WindowFlags);
		{
			if (LoggedIn == true)
			{
				ImGui::Text(Text.c_str());
			}
			else if (LoggedIn == false)
			{
				ImGui::InputText("Enter Licence:", KeyAuth_USER_Key_char, IM_ARRAYSIZE(KeyAuth_USER_Key_char));
				ImGui::Text(Text.c_str());

				if (ImGui::Button("Click Me"))
				{
					LoginThing();
				}
			}
		}
		ImGui::End();
	}

	#ifdef _WINDLL
	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDraw = !bDraw;
	#endif
}
