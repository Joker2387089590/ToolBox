#include <filesystem>
#include <iostream>
#include <Windows.h>

namespace
{
void printLastError()
{
	auto ec = ::GetLastError();
	union {
		::LPWSTR* buffer;
		::LPWSTR lpBuffer;
	};
	buffer = &lpBuffer;
	::FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER |
					 FORMAT_MESSAGE_FROM_SYSTEM |
					 FORMAT_MESSAGE_IGNORE_INSERTS,
					 nullptr,
					 ec,
					 MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					 lpBuffer,
					 0, NULL);
	std::wcout << lpBuffer << std::endl;
	::LocalFree(lpBuffer);
}

namespace fs = std::filesystem;
bool create(const fs::path& symbol, const fs::path& target)
{
	std::error_code ec;
	::DWORD flag = fs::is_directory(target, ec) ? SYMBOLIC_LINK_FLAG_DIRECTORY : 0;
	if(ec) return false;

	bool success = !!::CreateSymbolicLinkW(symbol.generic_wstring().c_str(),
										   target.generic_wstring().c_str(),
										   flag);
#ifndef NDEBUG
	if(!success) printLastError();
#endif
	return success;
}
}

int main(int argc, char* argv[])
{
	switch (argc)
	{
	case 1:
		return create("./test.exe", "LinkMaker.exe") ? 0 : 1;
	case 3:
		return create(argv[1], argv[2]) ? 0 : 1;
	default:
		return 2;
	}
}
