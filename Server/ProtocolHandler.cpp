#include "ProtocolHandler.h"

const std::string ProtocolHandler::MESSAGE_TYPE_NOT_EXIST = "99";
const std::string ProtocolHandler::MESSAGE_INVALID_FORMAT = "98";
const std::string ProtocolHandler::USER_LOGIN_OK = "10";
const std::string ProtocolHandler::USER_LOGGED_IN = "11";
const std::string ProtocolHandler::USER_ACCOUNT_ALREADY_LOGIN = "12";
const std::string ProtocolHandler::USER_INVALID_CREDENTIALS = "13";
const std::string ProtocolHandler::PASSWD_OK = "20";
const std::string ProtocolHandler::USER_NOT_LOGIN = "21";
const std::string ProtocolHandler::PASSWD_FAILED = "22";
const std::string ProtocolHandler::PASSWD_PASSWORD_NOT_CHANGE = "23";
const std::string ProtocolHandler::BYE_OK = "30";
const std::string ProtocolHandler::SET_OK = "40";
const std::string ProtocolHandler::SET_INVALID_DEVICE_ID = "41";
const std::string ProtocolHandler::SET_INVALID_PARAMETER_NAME = "42";
const std::string ProtocolHandler::SET_INVALID_VALUE = "43";
const std::string ProtocolHandler::ADDTIME_P_OK = "50";
const std::string ProtocolHandler::ADDTIME_P_INVALID_DEVICE_ID = "51";
const std::string ProtocolHandler::ADDTIME_P_INVALID_FORMAT_VALUE = "52";
const std::string ProtocolHandler::ADDTIME_P_VALUE_ALREADY_EXIST = "53";
const std::string ProtocolHandler::RMVTIME_P_INVALID_VALUE_ID = "54";
const std::string ProtocolHandler::GET_OK = "70";
const std::string ProtocolHandler::GET_INVALID_PARAMETER = "71";
const std::string ProtocolHandler::COMMAND_OK = "80";
const std::string ProtocolHandler::COMMAND_INVALID_PARAMETER = "81";

std::unordered_map<std::string, std::pair<std::string, bool>> ProtocolHandler::accounts;
CRITICAL_SECTION ProtocolHandler::criticalAccount;
std::vector<Device> ProtocolHandler::devices;
CRITICAL_SECTION ProtocolHandler::criticalDevice;
std::vector<EnvironmentParameter> ProtocolHandler::evParams;

std::string ProtocolHandler::handleMessage(std::string message, SessionInfo& session)
{
	return handleUserMessage("ad", "ad", session);
}

std::string ProtocolHandler::handleUserMessage(std::string username, std::string password, SessionInfo& session)
{
	//if the user who owns this message handler object is already login-ed.
	if (session.getLoginStatus())
	{
		return USER_LOGGED_IN;
	}

	EnterCriticalSection(&criticalAccount);
	//get account status by username in hash table
	std::unordered_map<std::string, std::pair<std::string, bool>>::iterator account = accounts.find(username);
	if (account == accounts.end()) //account not found
	{
		return USER_INVALID_CREDENTIALS;
	}

	if (account->second.second) //account is already logged in in another client
	{
		return USER_ACCOUNT_ALREADY_LOGIN;
	}

	if (password != account->second.first)
	{
		return USER_INVALID_CREDENTIALS;
	}

	account->second.second = true;
	LeaveCriticalSection(&criticalAccount);
	session.setLoginStatus(true);
	session.setUsername(username);
	return USER_LOGIN_OK;
}

std::string ProtocolHandler::handlePasswdMessage(std::string currentPasswd, std::string newPasswd, std::string confirmPasswd, SessionInfo& session)
{
	EnterCriticalSection(&criticalAccount);
	//get account status by username in hash table
	std::unordered_map<std::string, std::pair<std::string, bool>>::iterator account = accounts.find(session.getUsername());
	if (account == accounts.end()) //account not found
	{
		return USER_INVALID_CREDENTIALS;
	}

	if (account->second.first != currentPasswd)
	{
		return PASSWD_FAILED;
	}

	if (newPasswd != currentPasswd)
	{
		return PASSWD_FAILED;
	}

	if (currentPasswd == newPasswd)
	{
		return PASSWD_PASSWORD_NOT_CHANGE;
	}

	account->second.first = newPasswd;
	LeaveCriticalSection(&criticalAccount);
	return PASSWD_OK;
}

std::string ProtocolHandler::handleByeMessage(SessionInfo & session)
{
	session.reset();
	return BYE_OK;
}

std::string ProtocolHandler::handleSetMessage(int deviceId, std::string paramName, std::string paramValue)
{
	if (deviceId < 0 || deviceId >= devices.size())
		return SET_INVALID_DEVICE_ID;
	if (!devices[deviceId].isParameterExist(paramName))
		return SET_INVALID_PARAMETER_NAME;
	if (!devices[deviceId].setParameter(paramName, paramValue))
		return SET_INVALID_VALUE;
	return SET_OK;
}

std::string ProtocolHandler::handleAddTimePMessage(int deviceId, std::string paramValue)
{
	if (deviceId < 0 || deviceId >= devices.size())
		return ADDTIME_P_INVALID_DEVICE_ID;
	if (devices[deviceId].)
	return std::string();
}



SessionInfo::SessionInfo(SOCKET connSock)
	: connSock(connSock)
{
	username = "";
	isLogin = false;
	remainMessage = "";
}

SessionInfo::SessionInfo()
{
	username = "";
	isLogin = false;
	remainMessage = "";
	connSock = 0;
}

std::string SessionInfo::getUsername()
{
	return username;
}

void SessionInfo::setUsername(std::string username)
{
	this->username = username;
}

bool SessionInfo::getLoginStatus()
{
	return isLogin;
}

void SessionInfo::setLoginStatus(bool loginStatus)
{
	isLogin = loginStatus;
}

void SessionInfo::reset()
{
	username = "";
	isLogin = false;
	remainMessage = "";
	connSock = 0;
}
