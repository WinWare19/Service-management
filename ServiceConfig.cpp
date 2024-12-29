#include <Windows.h>
#include <winsvc.h>
#include <iostream>

typedef enum tagCONFIG_CLASS {
	SERVICE_CONFIG_DISPLAY_NAME,
	SERVICE_CONFIG_TYPE,
	SERVICE_CONFIG_START_TYPE,
	SERVICE_CONFIG_EXE_PATH,
	SERVICE_CONFIG_DEPENDENCIES,
	SERVICE_CONFIG_LOAD_ORDER_GROUP,
	SERVICE_CONFIG_TAG_ID,
	SERVICE_CONFIG_SECURITY_CONTEXT,
	SERVICE_CONFIG_PASSWORD
}CONFIG_CLASS, *PCONFIG_CLASS, *LPCONFIG_CLASS;

BOOLEAN __stdcall InstallNewService(LPCWSTR, LPCWSTR, LPCWSTR);
BOOLEAN __stdcall UninstallService(LPCWSTR);
BOOLEAN __stdcall ConfigService(LPCWSTR, CONFIG_CLASS, LPBYTE);
BOOLEAN __stdcall DenyServiceStopAndDelete(LPCWSTR);
BOOLEAN __stdcall ChangeConsoleTextAttributes(DWORD);
BOOLEAN __stdcall Menu();
BOOLEAN __stdcall LaunchService(LPCWSTR);
BOOLEAN __stdcall StopService(LPCWSTR);

INT main() {
	Menu();
	UINT choice = 0xffffffff;
	WCHAR buffers[0x3][100];
	while (0x1) {
		while (choice > 0xf || choice < 0) {
			printf_s("> enter a valid option code: ");
			scanf_s("%d", &choice);
		}
		if (choice == 0xf) break;
		std::wcin.get();
		switch (choice) {
			case 0x0: {
				printf_s("  > service name: ");
				std::wcin.getline(buffers[0x0], 100);
				printf_s("  > display name: ");
				std::wcin.getline(buffers[0x1], 100);
				printf_s("  > executable full path: ");
				std::wcin.getline(buffers[0x2], 100);
				if (InstallNewService(buffers[0x0], buffers[0x1], buffers[0x2])) {
					ChangeConsoleTextAttributes(FOREGROUND_GREEN);
					wprintf_s(L"  service <%s> installed successfully\n", buffers[0x0]);
					ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				}
			}break;
			case 0x1: {
				printf_s("  > service name: ");
				std::wcin.getline(buffers[0x0], 100);
				if(UninstallService(buffers[0x0])) {
					ChangeConsoleTextAttributes(FOREGROUND_GREEN);
					wprintf_s(L"  service <%s> uninstalled successfully\n", buffers[0x0]);
					ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				}
			}break;
			case 0x2: {
				printf_s("  > service name: ");
				std::wcin.getline(buffers[0x0], 100);
				printf_s("  > new display name: ");
				std::wcin.getline(buffers[0x1], 100);
				if(ConfigService(buffers[0x0], SERVICE_CONFIG_DISPLAY_NAME,(LPBYTE)buffers[0x1])) {
					ChangeConsoleTextAttributes(FOREGROUND_GREEN);
					wprintf_s(L"  service <%s> display name successfully updated to <%s>\n", buffers[0x0], buffers[0x1]);
					ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				}
			}break;
			case 0x3: {
				printf_s("  > service name: ");
				std::wcin.getline(buffers[0x0], 100);
				printf_s("  > new service type: ");
				DWORD type;
				std::wcin >> type;
				if(ConfigService(buffers[0x0], SERVICE_CONFIG_TYPE, (LPBYTE)&type)) {
					ChangeConsoleTextAttributes(FOREGROUND_GREEN);
					wprintf_s(L"  service <%s> type updated successfully to <%d> \n", buffers[0x0], type);
					ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				}
			}break;
			case 0x4: {
				printf_s("  > service name: ");
				std::wcin.getline(buffers[0x0], 100);
				printf_s("  > new service start type: ");
				DWORD start_type;
				std::wcin >> start_type;
				if(ConfigService(buffers[0x0], SERVICE_CONFIG_START_TYPE, (LPBYTE)&start_type)) {
					ChangeConsoleTextAttributes(FOREGROUND_GREEN);
					wprintf_s(L"  service <%s> start type updated successfully to <%d>\n", buffers[0x0], start_type);
					ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				}
			}break;
			case 0x5: {
				printf_s("  > service name: ");
				std::wcin.getline(buffers[0x0], 100);
				printf_s("  > new load order group: ");
				std::wcin.getline(buffers[0x1], 100);
				if(ConfigService(buffers[0x0], SERVICE_CONFIG_LOAD_ORDER_GROUP, (LPBYTE)buffers[0x1])) {
					ChangeConsoleTextAttributes(FOREGROUND_GREEN);
					wprintf_s(L"  service <%s> load order group updated successfully to <%s>\n", buffers[0x0], buffers[0x1]);
					ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				}
			}break;
			case 0x6: {
				printf_s("  > service name: ");
				std::wcin.getline(buffers[0x0], 100);
				printf_s("  > new tag id: ");
				DWORD tag_id;
				std::wcin >> tag_id;
				if(ConfigService(buffers[0x0], SERVICE_CONFIG_TAG_ID, (LPBYTE)&tag_id)) {
					ChangeConsoleTextAttributes(FOREGROUND_GREEN);
					wprintf_s(L"  service <%s> tag id updateded successfully to <%d>\n", buffers[0x0], tag_id);
					ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				}
			}break;
			case 0x7: {
				printf_s("  > service name: ");
				std::wcin.getline(buffers[0x0], 100);
				printf_s("  > new dependency list: ");
				std::wcin.getline(buffers[0x1], 100);
				if(ConfigService(buffers[0x0], SERVICE_CONFIG_DEPENDENCIES, (LPBYTE)buffers[0x1])) {
					ChangeConsoleTextAttributes(FOREGROUND_GREEN);
					wprintf_s(L"  service 0<%s> dependency list updated successfully to <%s>\n", buffers[0x0], buffers[0x1]);
					ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				}
			}break;
			case 0x8: {
				printf_s("  > service name: ");
				std::wcin.getline(buffers[0x0], 100);
				printf_s("  > new executable path: ");
				std::wcin.getline(buffers[0x1], 100);
				if(ConfigService(buffers[0x0], SERVICE_CONFIG_EXE_PATH, (LPBYTE)buffers[0x1])) {
					ChangeConsoleTextAttributes(FOREGROUND_GREEN);
					wprintf_s(L"  service <%s> executable path updated successfully to <%s>\n", buffers[0x0], buffers[0x1]);
					ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				}
			}break;
			case 0x9: {
				printf_s("  > service name: ");
				std::wcin.getline(buffers[0x0], 100);
				printf_s("  > new account name: ");
				std::wcin.getline(buffers[0x1], 100);
				if(ConfigService(buffers[0x0], SERVICE_CONFIG_SECURITY_CONTEXT, (LPBYTE)buffers[0x1])) {
					ChangeConsoleTextAttributes(FOREGROUND_GREEN);
					wprintf_s(L"  service <%s> account name updated successfully to <%s>\n", buffers[0x0], buffers[0x1]);
					ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				}
			}break;
			case 0xa: {
				printf_s("  > service name: ");
				std::wcin.getline(buffers[0x0], 100);
				printf_s("  > new password: ");
				std::wcin.getline(buffers[0x1], 100);
				if(ConfigService(buffers[0x0], SERVICE_CONFIG_PASSWORD, (LPBYTE)buffers[0x1])) {
					ChangeConsoleTextAttributes(FOREGROUND_GREEN);
					wprintf_s(L"  service <%s> password updated successfully to <*******>\n", buffers[0x0]);
					ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				}
			}break;
			case 0xb: {
				printf_s("  > service name: ");
				std::wcin.getline(buffers[0x0], 100);
				if (DenyServiceStopAndDelete(buffers[0x0])) {
					ChangeConsoleTextAttributes(FOREGROUND_GREEN);
					wprintf_s(L"  These access rights are successfully denied for everyone for service <%s> :\n", buffers[0x0]);
					wprintf_s(L"    1) SERVICE_STOP\n    2) DELETE\n");
					ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				}
			}break;
			case 0xc: {
				system("cls");
				Menu();
			}break;
			case 0xd: {
				printf_s("  > service name: ");
				std::wcin.getline(buffers[0x0], 100);
				if (LaunchService(buffers[0x0])) {
					ChangeConsoleTextAttributes(FOREGROUND_GREEN);
					wprintf_s(L"  service <%s> started successfully\n", buffers[0x0]);
					ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				}
			}break;
			case 0xe: {
				printf_s("  > service name: ");
				std::wcin.getline(buffers[0x0], 100);
				if (StopService(buffers[0x0])) {
					ChangeConsoleTextAttributes(FOREGROUND_GREEN);
					wprintf_s(L"  service <%s> stopped successfully\n", buffers[0x0]);
					ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				}
			}break;
		}
		choice = 0xffffffff;
		for (UINT i = 0x0; i < 0x3; i++) ZeroMemory(buffers[i], 100);
	}
	return 0x0;
}

BOOLEAN __stdcall InstallNewService(LPCWSTR name, LPCWSTR display_name, LPCWSTR exe_path) {
	if (!name || !lstrlenW(name) || !display_name || !lstrlenW(display_name) || !exe_path || !lstrlenW(exe_path)) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: invalid parameter(s)\n");
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		SetLastError(ERROR_INVALID_PARAMETER);
		return 0x0;
	}
	SC_HANDLE SCManager = OpenSCManagerW(NULL, SERVICES_ACTIVE_DATABASEW, SC_MANAGER_CREATE_SERVICE);
	if (!SCManager) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: OpenSCManagerW() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		return 0x0;
	} 
	SC_HANDLE service = CreateServiceW(SCManager, name, display_name, SERVICE_ALL_ACCESS, SERVICE_WIN32_SHARE_PROCESS, SERVICE_DEMAND_START,
		SERVICE_ERROR_NORMAL, exe_path, NULL, NULL, NULL, NULL, 0x0);
	if (!service) {
		CloseServiceHandle(SCManager);
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: CreateServiceW() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		return 0x0;
	}
	CloseServiceHandle(service);
	CloseServiceHandle(SCManager);
	return 0x1;
}
BOOLEAN __stdcall UninstallService(LPCWSTR name) {
	if (!name || !lstrlenW(name)) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: invalid parameter(s)\n");
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		SetLastError(ERROR_INVALID_PARAMETER);
		return 0x0;
	}
	SC_HANDLE SCManager = OpenSCManagerW(NULL, SERVICES_ACTIVE_DATABASEW, SC_MANAGER_ALL_ACCESS);
	if (!SCManager) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: OpenSCManagerW() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		return 0x0;
	}
	SC_HANDLE service = OpenServiceW(SCManager, name, DELETE);
	if (!service) {
		CloseServiceHandle(SCManager);
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: OpenServiceW() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		return 0x0;
	}
	BOOLEAN return_value = DeleteService(service);
	if (!return_value) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: DeleteService() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	}
	CloseServiceHandle(service);
	CloseServiceHandle(SCManager);
	return return_value;
}
BOOLEAN __stdcall ConfigService(LPCWSTR name, CONFIG_CLASS info_class, LPBYTE new_data) {
	if (!name || !lstrlenW(name) || !new_data) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: invalid parameter(s)\n");
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		SetLastError(ERROR_INVALID_PARAMETER);
		return 0x0;
	}
	SC_HANDLE SCManager = OpenSCManagerW(NULL, SERVICES_ACTIVE_DATABASEW, SC_MANAGER_ALL_ACCESS);
	if (!SCManager) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: OpenSCManagerW() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		return 0x0;
	}
	SC_HANDLE service = OpenServiceW(SCManager, name, SERVICE_CHANGE_CONFIG);
	if (!service) {
		CloseServiceHandle(SCManager);
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: OpenServiceW() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		return 0x0;
	}
	BOOLEAN return_value = 0x1;
	switch (info_class) {
		case SERVICE_CONFIG_DISPLAY_NAME: {
			if (!ChangeServiceConfigW(service, SERVICE_NO_CHANGE, SERVICE_NO_CHANGE, SERVICE_NO_CHANGE, NULL, NULL, NULL,
				NULL, NULL, NULL, (LPCWSTR)new_data)) {
				return_value = 0x0;
				ChangeConsoleTextAttributes(FOREGROUND_RED);
				printf_s("  ERROR: ChangeServiceConfigW() failed with %d\n", GetLastError());
				ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
		}break;
		case SERVICE_CONFIG_TYPE: {
			if (!ChangeServiceConfigW(service, *(DWORD*)new_data, SERVICE_NO_CHANGE, SERVICE_NO_CHANGE, NULL, NULL, NULL,
				NULL, NULL, NULL, NULL)) {
				return_value = 0x0;
				ChangeConsoleTextAttributes(FOREGROUND_RED);
				printf_s("  ERROR: ChangeServiceConfigW() failed with %d\n", GetLastError());
				ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
		}break;
		case SERVICE_CONFIG_START_TYPE: {
			if (!ChangeServiceConfigW(service, SERVICE_NO_CHANGE, *(DWORD*)new_data, SERVICE_NO_CHANGE, NULL, NULL, NULL,
				NULL, NULL, NULL, NULL)) {
				return_value = 0x0;
				ChangeConsoleTextAttributes(FOREGROUND_RED);
				printf_s("  ERROR: ChangeServiceConfigW() failed with %d\n", GetLastError());
				ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
		}break;
		case SERVICE_CONFIG_DEPENDENCIES: {
			if (!ChangeServiceConfigW(service, SERVICE_NO_CHANGE, SERVICE_NO_CHANGE, SERVICE_NO_CHANGE, NULL, NULL, NULL,
				(LPCWSTR)new_data, NULL, NULL, NULL)) {
				return_value = 0x0;
				ChangeConsoleTextAttributes(FOREGROUND_RED);
				printf_s("  ERROR: ChangeServiceConfigW() failed with %d\n", GetLastError());
				ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
		}break;
		case SERVICE_CONFIG_LOAD_ORDER_GROUP: {
			if (!ChangeServiceConfigW(service, SERVICE_NO_CHANGE, SERVICE_NO_CHANGE, SERVICE_NO_CHANGE, NULL, (LPCWSTR)new_data, NULL,
				NULL, NULL, NULL, NULL)) {
				return_value = 0x0;
				ChangeConsoleTextAttributes(FOREGROUND_RED);
				printf_s("  ERROR: ChangeServiceConfigW() failed with %d\n", GetLastError());
				ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
		}break;
		case SERVICE_CONFIG_TAG_ID: {
			if (!ChangeServiceConfigW(service, SERVICE_NO_CHANGE, SERVICE_NO_CHANGE, SERVICE_NO_CHANGE, NULL, NULL, (LPDWORD)new_data,
				NULL, NULL, NULL, NULL)) {
				return_value = 0x0;
				ChangeConsoleTextAttributes(FOREGROUND_RED);
				printf_s("  ERROR: ChangeServiceConfigW() failed with %d\n", GetLastError());
				ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
		}break;
		case SERVICE_CONFIG_SECURITY_CONTEXT: {
			if (!ChangeServiceConfigW(service, SERVICE_NO_CHANGE, SERVICE_NO_CHANGE, SERVICE_NO_CHANGE, NULL, NULL, NULL,
				NULL, (LPCWSTR)new_data, NULL, NULL)) {
				return_value = 0x0;
				ChangeConsoleTextAttributes(FOREGROUND_RED);
				printf_s("  ERROR: ChangeServiceConfigW() failed with %d\n", GetLastError());
				ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
		}break;
		case SERVICE_CONFIG_PASSWORD: {
			if (!ChangeServiceConfigW(service, SERVICE_NO_CHANGE, SERVICE_NO_CHANGE, SERVICE_NO_CHANGE, NULL, NULL, NULL,
				NULL, NULL, (LPCWSTR)new_data, NULL)) {
				return_value = 0x0;
				ChangeConsoleTextAttributes(FOREGROUND_RED);
				printf_s("  ERROR: ChangeServiceConfigW() failed with %d\n", GetLastError());
				ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
		}break;
		case SERVICE_CONFIG_EXE_PATH: {
			if (!ChangeServiceConfigW(service, SERVICE_NO_CHANGE, SERVICE_NO_CHANGE, SERVICE_NO_CHANGE, (LPCWSTR)new_data, NULL, NULL,
				NULL, NULL, NULL, NULL)) {
				return_value = 0x0;
				ChangeConsoleTextAttributes(FOREGROUND_RED);
				printf_s("  ERROR: ChangeServiceConfigW() failed with %d\n", GetLastError());
				ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
		}break;
	}
	CloseServiceHandle(service);
	CloseServiceHandle(SCManager);
	return return_value;
}
BOOLEAN __stdcall DenyServiceStopAndDelete(LPCWSTR name) {
	if (!name || !lstrlenW(name)) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: invalid parameter(s)\n");
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		SetLastError(ERROR_INVALID_PARAMETER);
		return 0x0;
	}
	SC_HANDLE SCManager = OpenSCManagerW(NULL, SERVICES_ACTIVE_DATABASEW, SC_MANAGER_ALL_ACCESS);
	if (!SCManager) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: OpenSCManagerW() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		return 0x0;
	}
	SC_HANDLE service = OpenServiceW(SCManager, name, READ_CONTROL | WRITE_DAC);
	if (!service) {
		CloseServiceHandle(SCManager);
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: OpenServiceW() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		return 0x0;
	}
	PSID everyone_sid = NULL;
	SID_IDENTIFIER_AUTHORITY auth = SECURITY_WORLD_SID_AUTHORITY;
	if (!AllocateAndInitializeSid(&auth, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, &everyone_sid)) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: AllocateAndInitializeSid() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		CloseServiceHandle(service);
		CloseServiceHandle(SCManager);
		return 0x0;
	}
	BOOLEAN return_value = 0x1;
	DWORD needed_bytes = 0x0;
	QueryServiceObjectSecurity(service, DACL_SECURITY_INFORMATION, NULL, 0x0, &needed_bytes);
	PSECURITY_DESCRIPTOR sd = (PSECURITY_DESCRIPTOR)HeapAlloc(GetProcessHeap(), 0x8, needed_bytes);
	if (!QueryServiceObjectSecurity(service, DACL_SECURITY_INFORMATION, sd, needed_bytes, &needed_bytes)) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: QueryServiceObjectSecurity() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		HeapFree(GetProcessHeap(), 0x0, sd);
		FreeSid(everyone_sid);
		CloseServiceHandle(service);
		CloseServiceHandle(SCManager);
		return 0x0;
	}
	PSECURITY_DESCRIPTOR absolute_sd = NULL;
	needed_bytes = 0x0;
	DWORD unused[4] = { 0 };
	MakeAbsoluteSD(sd, absolute_sd, &needed_bytes, NULL, &unused[0], NULL, &unused[1], NULL, &unused[2], NULL, &unused[3]);
	absolute_sd = (PSECURITY_DESCRIPTOR)HeapAlloc(GetProcessHeap(), 0x8, needed_bytes);
	LPBYTE u_buffers[4] = { 0 };
	for (UINT i = 0; i < 4; i++) u_buffers[i] = (LPBYTE)HeapAlloc(GetProcessHeap(), 0x8, unused[i]);
	if (!MakeAbsoluteSD(sd, absolute_sd, &needed_bytes, (PACL)u_buffers[0], &unused[0], (PACL)u_buffers[1], &unused[1],
		(PSID)u_buffers[2], &unused[2], (PSID)u_buffers[3], &unused[3])) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: MakeAbsoluteSD() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		HeapFree(GetProcessHeap(), 0x0, sd);
		FreeSid(everyone_sid);
		CloseServiceHandle(service);
		CloseServiceHandle(SCManager);
		return 0x0;
	}
	for (UINT i = 0; i < 4; i++) HeapFree(GetProcessHeap(), 0x0, u_buffers[i]);
	PACL dacl = NULL;
	BOOL dacl_present = FALSE;
	BOOL default_dacl = FALSE;
	if (!GetSecurityDescriptorDacl(absolute_sd, &dacl_present, &dacl, &default_dacl) || !dacl) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: GetSecurityDescriptorDacl() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		HeapFree(GetProcessHeap(), 0x0, absolute_sd);
		HeapFree(GetProcessHeap(), 0x0, sd);
		FreeSid(everyone_sid);
		CloseServiceHandle(service);
		CloseServiceHandle(SCManager);
		return 0x0;
	}
	ACL_SIZE_INFORMATION dacl_size = { 0 };
	if (!GetAclInformation(dacl, &dacl_size, sizeof(ACL_SIZE_INFORMATION), AclSizeInformation)) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: GetAclInformation() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		HeapFree(GetProcessHeap(), 0x0, absolute_sd);
		HeapFree(GetProcessHeap(), 0x0, sd);
		FreeSid(everyone_sid);
		CloseServiceHandle(service);
		CloseServiceHandle(SCManager);
		return 0x0;
	}
	DWORD size = dacl_size.AclBytesInUse + sizeof(ACCESS_DENIED_ACE) - 4 + GetLengthSid(everyone_sid);
	PACL new_dacl = (PACL)HeapAlloc(GetProcessHeap(), 0x8, size);
	if (!InitializeAcl(new_dacl, size, ACL_REVISION)) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: InitializeAcl() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		HeapFree(GetProcessHeap(), 0x0, absolute_sd);
		HeapFree(GetProcessHeap(), 0x0, new_dacl);
		HeapFree(GetProcessHeap(), 0x0, sd);
		FreeSid(everyone_sid);
		CloseServiceHandle(service);
		CloseServiceHandle(SCManager);
		return 0x0;
	}
	if (!AddAccessDeniedAce(new_dacl, ACL_REVISION, DELETE | SERVICE_STOP | SERVICE_PAUSE_CONTINUE, 
		everyone_sid)) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: AddAccessDeniedAce(0) failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		HeapFree(GetProcessHeap(), 0x0, absolute_sd);
		HeapFree(GetProcessHeap(), 0x0, new_dacl);
		HeapFree(GetProcessHeap(), 0x0, sd);
		FreeSid(everyone_sid);
		CloseServiceHandle(service);
		CloseServiceHandle(SCManager);
		return 0x0;
	}
	for (UINT i = 0; i < dacl_size.AceCount; i++) {
		ACE_HEADER* ace_hdr = NULL;
		if (!GetAce(dacl, i, (LPVOID*)&ace_hdr)) continue;
		if (ace_hdr->AceType == ACCESS_ALLOWED_ACE_TYPE) {
			ACCESS_ALLOWED_ACE* ace = (ACCESS_ALLOWED_ACE*)ace_hdr;
			if (!AddAccessAllowedAce(new_dacl, ACL_REVISION, ace->Mask, (PSID)((LPBYTE)ace + sizeof(ACE_HEADER) + 4))) {
				ChangeConsoleTextAttributes(FOREGROUND_RED);
				printf_s("  ERROR: AddAccessAllowedAce(%d) failed with %d\n",i, GetLastError());
				ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
		}
		else if (ace_hdr->AceType == ACCESS_DENIED_ACE_TYPE) {
			ACCESS_DENIED_ACE* ace = (ACCESS_DENIED_ACE*)ace_hdr;
			if (!AddAccessDeniedAce(new_dacl, ACL_REVISION, ace->Mask, (PSID)((LPBYTE)ace + sizeof(ACE_HEADER) + 4))) {
				ChangeConsoleTextAttributes(FOREGROUND_RED);
				printf_s("  ERROR: AddAccessDeniedAce(%d) failed with %d\n",i, GetLastError());
				ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
		}
	}
	if (!SetSecurityDescriptorDacl(absolute_sd, TRUE, new_dacl, FALSE)) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: SetSecurityDescriptorDacl() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		HeapFree(GetProcessHeap(), 0x0, absolute_sd);
		HeapFree(GetProcessHeap(), 0x0, new_dacl);
		HeapFree(GetProcessHeap(), 0x0, sd);
		FreeSid(everyone_sid);
		CloseServiceHandle(service);
		CloseServiceHandle(SCManager);
		return 0x0;
	}
	if (!SetServiceObjectSecurity(service, DACL_SECURITY_INFORMATION, absolute_sd)) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: SetServiceObjectSecurity() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		return_value = 0x0;
	}
	HeapFree(GetProcessHeap(), 0x0, absolute_sd);
	HeapFree(GetProcessHeap(), 0x0, new_dacl);
	HeapFree(GetProcessHeap(), 0x0, sd);
	FreeSid(everyone_sid);
	CloseServiceHandle(service);
	CloseServiceHandle(SCManager);

	return return_value;
}
BOOLEAN __stdcall ChangeConsoleTextAttributes(DWORD text_attrs) {
	HANDLE active_screen_buffer = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!active_screen_buffer) {
		printf_s("GetStdHandle() failed with %d\n", GetLastError());
		return 0x0;
	}
	if (!SetConsoleTextAttribute(active_screen_buffer, text_attrs)) {
		printf_s("SetConsoleTextAttribute() failed with %d\n", GetLastError());
		return 0x0;
	}
	return 0x1;
}
BOOLEAN __stdcall Menu() {
	printf_s("Welcome to the service management tool: \n\n");
	LPCSTR options[] = { "Install service", "Uninstall service", "Change service display name", "Change service type", "Change service start type",
		"Change service load order group", "Change service tag id", "Change service dependency list", "Change service execuable path",
		"Change service account name (security context)", "change service password", "Deny <DELETE, SERVICE_STOP> access rights", "cls", "Start service",
		"Stop service", "Exit" };
	for (UINT i = 0x0; i < 0x10; i++) printf_s("%d) %s\n", i, options[i]);
	printf_s("\n\n");
	return 0x1;
}
BOOLEAN __stdcall LaunchService(LPCWSTR service_name) {
	if (!service_name || !lstrlenW(service_name)) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: invalid parameter(s)\n");
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		SetLastError(ERROR_INVALID_PARAMETER);
		return 0x0;
	}
	SC_HANDLE SCManager = OpenSCManagerW(NULL, SERVICES_ACTIVE_DATABASEW, SC_MANAGER_ALL_ACCESS);
	if (!SCManager) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: OpenSCManagerW() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		return 0x0;
	}
	SC_HANDLE service = OpenServiceW(SCManager, service_name, SERVICE_START | SERVICE_QUERY_STATUS);
	if (!service) {
		CloseServiceHandle(SCManager);
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: CreateServiceW() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		return 0x0;
	}
	SERVICE_STATUS current_status = { 0x0 };
	if (!QueryServiceStatus(service, &current_status)) {
		CloseServiceHandle(service);
		CloseServiceHandle(SCManager);
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: QueryServiceStatus(0x0) failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		return 0x0;
	}
	if (current_status.dwCurrentState != SERVICE_STOPPED) {
		CloseServiceHandle(service);
		CloseServiceHandle(SCManager);
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		wprintf_s(L"  ERROR: service <%s> is already started\n", service_name);
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		return 0x0;
	}
	if (!StartServiceW(service, 0x0, NULL)) {
		CloseServiceHandle(service);
		CloseServiceHandle(SCManager);
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: StartServiceW() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		return 0x0;
	}
	if (!QueryServiceStatus(service, &current_status)) {
		CloseServiceHandle(service);
		CloseServiceHandle(SCManager);
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: QueryServiceStatus(0x1) failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		return 0x0;
	}
	DWORD recent_checkpoint = current_status.dwCheckPoint;
	BOOLEAN return_value = 0x1;
	if (current_status.dwCurrentState == SERVICE_START_PENDING) {
		while (0x1) {
			Sleep(current_status.dwWaitHint);
			if (!QueryServiceStatus(service, &current_status)) {
				CloseServiceHandle(service);
				CloseServiceHandle(SCManager);
				ChangeConsoleTextAttributes(FOREGROUND_RED);
				printf_s("  ERROR: QueryServiceStatus(0x2) failed with %d\n", GetLastError());
				ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				return 0x0;
			}
			if (current_status.dwCurrentState == SERVICE_RUNNING) break;
			if (current_status.dwCheckPoint > recent_checkpoint) recent_checkpoint = current_status.dwCheckPoint;
			else {
				ChangeConsoleTextAttributes(FOREGROUND_RED);
				wprintf_s(L"  ERROR: <%s> failed to start\n", service_name);
				ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				return_value = 0x0;
				break;
			}
		}
	}
	CloseServiceHandle(service);
	CloseServiceHandle(SCManager);
	return return_value;
}
BOOLEAN __stdcall StopService(LPCWSTR service_name) {
	if (!service_name || !lstrlenW(service_name)) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: invalid parameter(s)\n");
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		SetLastError(ERROR_INVALID_PARAMETER);
		return 0x0;
	}
	SC_HANDLE SCManager = OpenSCManagerW(NULL, SERVICES_ACTIVE_DATABASEW, SC_MANAGER_ALL_ACCESS);
	if (!SCManager) {
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: OpenSCManagerW() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		return 0x0;
	}
	SC_HANDLE service = OpenServiceW(SCManager, service_name, SERVICE_STOP | SERVICE_QUERY_STATUS);
	if (!service) {
		CloseServiceHandle(SCManager);
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: CreateServiceW() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		return 0x0;
	}
	SERVICE_STATUS current_status = { 0x0 };
	if (!QueryServiceStatus(service, &current_status)) {
		CloseServiceHandle(service);
		CloseServiceHandle(SCManager);
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: QueryServiceStatus(0x0) failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		return 0x0;
	}
	if (current_status.dwCurrentState == SERVICE_STOPPED || current_status.dwCurrentState == SERVICE_STOP_PENDING) {
		CloseServiceHandle(service);
		CloseServiceHandle(SCManager);
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		wprintf_s(L"  ERROR: service <%s> is already stopped or is about to stop\n", service_name);
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		return 0x0;
	}
	if (!ControlService(service, SERVICE_CONTROL_STOP, &current_status)) {
		CloseServiceHandle(service);
		CloseServiceHandle(SCManager);
		ChangeConsoleTextAttributes(FOREGROUND_RED);
		printf_s("  ERROR: ControlService() failed with %d\n", GetLastError());
		ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		return 0x0;
	}

	if (current_status.dwCurrentState == SERVICE_STOP_PENDING) {
		DWORD recent_checkpoint = current_status.dwCheckPoint;
		while (0x1) {
			Sleep(current_status.dwWaitHint);
			if (!QueryServiceStatus(service, &current_status)) {
				CloseServiceHandle(service);
				CloseServiceHandle(SCManager);
				ChangeConsoleTextAttributes(FOREGROUND_RED);
				printf_s("  ERROR: QueryServiceStatus(0x1) failed with %d\n", GetLastError());
				ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				return 0x0;
			}
			if (current_status.dwCurrentState == SERVICE_STOPPED) break;
			if (current_status.dwCurrentState > recent_checkpoint) recent_checkpoint = current_status.dwCheckPoint;
			else {
				ChangeConsoleTextAttributes(FOREGROUND_RED);
				wprintf_s(L"  ERROR: <%s> failed to stop\n", service_name);
				ChangeConsoleTextAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				break;
			}
		}
	}

	CloseServiceHandle(service);
	CloseServiceHandle(SCManager);
	return 0x1;
}