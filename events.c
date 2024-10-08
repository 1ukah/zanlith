#pragma warning (disable : 4047 4311)

#include "events.h"
#include "messages.h"
#include "data.h"
#include "utils.h"

PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo)
{
	//DebugMessage("ImageLoaded: %ls \n", FullImageName->Buffer);

	if (wcsstr(FullImageName->Buffer, L"\\Counter-Strike Global Offensive\\csgo\\bin\\client.dll"))
	{
		DebugMessage("CSGO's client.dll found!");
		CSGOClientDLLAddress = ImageInfo->ImageBase;
		ProcessID = (ULONG)ProcessId;

		DebugMessage("ProcessID: %d \n", ProcessId);
	}

	return STATUS_SUCCESS;
}