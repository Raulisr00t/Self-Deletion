#include <Windows.h>
#include <iostream>
#include <winternl.h>
#include <string.h>

#define NewStream L":Raulisr00t"

using namespace std;

BOOL Delete() {
	WCHAR Path[MAX_PATH * 2] = { 0 };
	FILE_DISPOSITION_INFO Delete = { 0 };
	HANDLE hFile = INVALID_HANDLE_VALUE;
	PFILE_RENAME_INFO pRename = nullptr;
	const wchar_t* stream = (const wchar_t*)NewStream;
	SIZE_T sRename = sizeof(FILE_RENAME_INFO) + sizeof(stream);

	pRename = (PFILE_RENAME_INFO)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sRename);
	if (!pRename) {
		wcerr << "[!] Allocation Error" << endl;
		wcerr << "[!] Error:" << GetLastError() << endl;
		return FALSE;
	}

	ZeroMemory(Path, sizeof(Path));
	ZeroMemory(&Delete, sizeof(Delete));

	Delete.DeleteFileW = TRUE;
	pRename->FileNameLength = sizeof(stream);
	RtlCopyMemory(pRename->FileName, stream, sizeof(stream));

	if (GetModuleFileNameW(NULL, Path, MAX_PATH * 2) == 0) {
		wcerr << "[!] File Name Error" << endl;
		wcerr << "[!] Error:" << GetLastError() << endl;
		return FALSE;
	}

	hFile = CreateFileW(Path, DELETE | SYNCHRONIZE, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		wcerr << "[!] Opening File for Deleting Error" << endl;
		wcerr << "[!] Error:" << GetLastError() << endl;
		return FALSE;
	}

	wcout << "[+] Renaming :$DATA to %s  ...", stream;

	if (!SetFileInformationByHandle(hFile, FileRenameInfo, pRename, sRename)) {
		wcerr << "[!] Setting File Info Error" << endl;
		wcerr << "[!] Error:" << GetLastError() << endl;
		return FALSE;
	}
	wcout << "[+] DONE [+]" << endl;

	CloseHandle(hFile);

	hFile = CreateFileW(Path, DELETE | SYNCHRONIZE, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE && GetLastError() == ERROR_FILE_NOT_FOUND) {
		cerr << "[i] Already Deleted" << endl;
		return TRUE;
	}
	if (hFile == INVALID_HANDLE_VALUE) {
		cerr << "[!] Error:" << GetLastError() << endl;
		return FALSE;
	}

	wcout << "[+] DELETING ..." << endl;

	if (!SetFileInformationByHandle(hFile, FileDispositionInfo, &Delete, sizeof(Delete))) {
		cout << "[!] SetFileInformationByHandle [D] Failed With Error : %d \n", GetLastError();
		return FALSE;
	}

	wcout << "[+] DONE " << endl;

	CloseHandle(hFile);

	HeapFree(GetProcessHeap(), 0, pRename);

	return TRUE;
}

int main(int argc, char* argv[]) {
	if (!Delete()) {
		return -1;
	}

	cout << "[+] File Should Be Deleted [+]" << endl;
	cout << "[>>] PRESS <Enter> To Quit ..." << endl;

	cin.ignore();

	return 0;
}
