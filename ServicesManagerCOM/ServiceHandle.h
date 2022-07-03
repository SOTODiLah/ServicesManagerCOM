#pragma once

#include <Windows.h>
#include <functional>

class CServiceHandle
{
	SC_HANDLE _handle = nullptr;

	void Close()
	{
		if (_handle != nullptr)
			::CloseServiceHandle(_handle);
	}

public:
	CServiceHandle(SC_HANDLE const handle = nullptr) noexcept :_handle(handle) {}

	CServiceHandle(CServiceHandle&& other) noexcept : _handle(std::move(other._handle)) {}

	CServiceHandle& operator=(SC_HANDLE const handle)
	{
		if (_handle != handle)
		{
			Close();

			_handle = handle;
		}

		return *this;
	}

	CServiceHandle& operator=(CServiceHandle&& other)
	{
		if (this != &other)
		{
			_handle = std::move(other._handle);
			other._handle = nullptr;
		}

		return *this;
	}

	operator SC_HANDLE() const noexcept { return _handle; }

	explicit operator bool() const noexcept { return _handle != nullptr; }

	~CServiceHandle()
	{
		Close();
	}
};