#ifndef PROTOCOL_HANDLER_H
#define PROTOCOL_HANDLER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <winsock2.h>
#include "Device.h"
#include "EnvironmentParameter.h"

class SessionInfo
{
private:
	std::string username;
	bool isLogin;
	std::string remainMessage;
	std::vector<std::string> messageQueue;
	SOCKET connSock;
public:
	SessionInfo(SOCKET connSock);
	SessionInfo();

	std::string getUsername();
	void setUsername(std::string username);
	bool getLoginStatus();
	void setLoginStatus(bool loginStatus);
	void reset();
};

class ProtocolHandler
{
public:
	static const std::string MESSAGE_TYPE_NOT_EXIST;
	static const std::string MESSAGE_INVALID_FORMAT;
	static const std::string USER_LOGIN_OK;
	static const std::string USER_LOGGED_IN;
	static const std::string USER_ACCOUNT_ALREADY_LOGIN;
	static const std::string USER_INVALID_CREDENTIALS;
	static const std::string PASSWD_OK;
	static const std::string USER_NOT_LOGIN;
	static const std::string PASSWD_FAILED;
	static const std::string PASSWD_PASSWORD_NOT_CHANGE;
	static const std::string BYE_OK;
	static const std::string SET_OK;
	static const std::string SET_INVALID_DEVICE_ID;
	static const std::string SET_INVALID_PARAMETER_NAME;
	static const std::string SET_INVALID_VALUE;
	static const std::string ADDTIME_P_OK;
	static const std::string ADDTIME_P_INVALID_DEVICE_ID;
	static const std::string ADDTIME_P_INVALID_FORMAT_VALUE;
	static const std::string ADDTIME_P_VALUE_ALREADY_EXIST;
	static const std::string RMVTIME_P_INVALID_VALUE_ID;
	static const std::string GET_OK;
	static const std::string GET_INVALID_PARAMETER;
	static const std::string COMMAND_OK;
	static const std::string COMMAND_INVALID_PARAMETER;
	static std::unordered_map<std::string, std::pair<std::string, bool>> accounts;
	static CRITICAL_SECTION criticalAccount;
	static std::vector<Device> devices;
	static CRITICAL_SECTION criticalDevice;
	static std::vector<EnvironmentParameter> evParams;

	static std::string handleMessage(std::string message, SessionInfo& session);
	static std::string handleUserMessage(std::string username, std::string password, SessionInfo& session);
	static std::string handlePasswdMessage(std::string currentPasswd, std::string newPasswd, std::string confirmPasswd, SessionInfo& session);
	static std::string handleByeMessage(SessionInfo& session);
	static std::string handleSetMessage(int deviceId, std::string paramName, std::string paramValue);
	static std::string handleAddTimePMessage(int deviceId, std::string paramValue);
};

#endif // !PROTOCOL_HANDLER_H
