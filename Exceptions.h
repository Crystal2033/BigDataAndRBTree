#pragma once
#include <iostream>
class Exception : public std::exception
{
protected:
	std::string error_msg;
public:
	virtual const char* what() const override = 0;
	virtual ~Exception() = default;
};

//===================================================================================
//===================================================================================
//===================================================================================

#pragma region Exceptions
template <typename TKey>
class KeyNotFoundException : public Exception
{
private: 
	TKey key_error;
public:
	KeyNotFoundException(const std::string&, TKey);
	const char* what() const override { return error_msg.c_str(); }
	TKey get_error_key() const { return key_error; }
};

template <typename TKey>
KeyNotFoundException<TKey>::KeyNotFoundException(const std::string& str, TKey key)
{
	key_error = key;
	error_msg = str;
}
//===================================================================================
//===================================================================================
//===================================================================================

template <typename TKey>
class KeyAlreadyExistsException : public Exception  //probably don`t need
{
private:
	TKey key_error;
public:
	KeyAlreadyExistsException(const std::string&, TKey);
	const char* what() const override { return error_msg.c_str(); }
	TKey get_error_key() const { return key_error; }
};

template <typename TKey>
KeyAlreadyExistsException<TKey>::KeyAlreadyExistsException(const std::string& str, TKey key)
{
	key_error = key;
	error_msg = str;
}




//===================================================================================
//===================================================================================
//===================================================================================

class DeliveryNullException : public Exception
{
private:

public:
	DeliveryNullException(const std::string&);
	const char* what() const override { return error_msg.c_str(); }
};
DeliveryNullException::DeliveryNullException(const std::string& str)
{
	error_msg = str;
}


//===================================================================================
//===================================================================================
//===================================================================================


class ComparatorNullException : public Exception
{
private:

public:
	ComparatorNullException(const std::string&);
	const char* what() const override { return error_msg.c_str(); }
};
ComparatorNullException::ComparatorNullException(const std::string& str)
{
	error_msg = str;
}

class NullException : public Exception
{
private:

public:
	NullException(const std::string&);
	const char* what() const override { return error_msg.c_str(); }
};
NullException::NullException(const std::string& str)
{
	error_msg = str;
}
#pragma endregion