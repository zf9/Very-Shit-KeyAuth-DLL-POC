#pragma once
#include "./wnetwrap.h"
#include "./json.hpp"
#include "./skCrypter.h"

std::string get_hwid();


using json = nlohmann::json;

std::string KeyAuthOwherID = "";
std::string KeyAuthAppName = "Test";


bool FirstStart = true;
bool LoggedIn = false;
std::string Text;
std::string KeyAuth_message;
std::string KeyAuth_sessionid;

auto KeyAuth_init_URL = skCrypt("https://keyauth.win/api/1.2/?type=init&ver=1.0&name=Test&ownerid=XIT7yh4Z0R");
char KeyAuth_USER_Key_char[64] = "";
std::string KeyAuth_USER_HWID = get_hwid();
std::string KeyAuth_USER_Key_str(KeyAuth_USER_Key_char);
#include <atlsecurity.h> 


std::string get_hwid() {
	ATL::CAccessToken accessToken;
	ATL::CSid currentUserSid;
	if (accessToken.GetProcessToken(TOKEN_READ | TOKEN_QUERY) &&
		accessToken.GetUser(&currentUserSid))
		return std::string(CT2A(currentUserSid.Sid()));
	return "none";
} // Stolen From https://github.com/KeyAuth/keyauth-cpp-library/blob/main/utils.cpp#L3-L12