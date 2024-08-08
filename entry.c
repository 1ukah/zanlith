#pragma warning (disable : 4047 4024)

#include "entry.h"
#include "messages.h"
#include "events.h"
#include "data.h"
#include "communication.h"
#include "utils.h"

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
	UNREFERENCED_PARAMETER(pRegistryPath);

	//auto kernelBase = GetKernelBaseAddr(pDriverObject);

	pDriverObject->DriverUnload = UnloadDriver;

	DebugMessage("========== > Driver LOADED! < ==========");

	PsSetLoadImageNotifyRoutine(ImageLoadCallback);

	RtlInitUnicodeString(&dev, L"\\Device\\zanlith");
	RtlInitUnicodeString(&dos, L"\\DosDevices\\zanlith");

	IoCreateDevice(pDriverObject, 0, &dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);
	IoCreateSymbolicLink(&dos, &dev);

	pDriverObject->MajorFunction[IRP_MJ_CREATE] = CreateCall;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = CloseCall;
	pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IoControl;

	pDeviceObject->Flags |= DO_DIRECT_IO;
	pDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

	return STATUS_SUCCESS;
}

NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject)
{
	UNREFERENCED_PARAMETER(pDriverObject);

	DebugMessage("========== > Driver UNLOADED! < ==========");

	IoDeleteSymbolicLink(&dos);
	IoDeleteDevice(pDriverObject->DeviceObject);

	PsRemoveLoadImageNotifyRoutine(ImageLoadCallback);

	return STATUS_SUCCESS;
}
