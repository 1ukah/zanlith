#include <iostream>
#include "kernelinterface.hpp"
#include "offsets.hpp"

int main()
{
    KernelInterface Driver = KernelInterface("\\\\.\\zanlith");

    ULONG address = Driver.GetClientAddress();
    ULONG processid = Driver.GetProcessID();

    std::cout << "Address: " << address << std::endl;
    std::cout << "ProcessID: " << processid << std::endl;

    while (true)
    {
        if (GetAsyncKeyState(VK_END) & 1)
            return false;

        uint32_t localPlayerAddr = Driver.ReadVirtualMemory<uint32_t>(processid, address + hazedumper::signatures::dwLocalPlayer, sizeof(uint32_t));
        Driver.WriteVirtualMemory(processid, localPlayerAddr + hazedumper::netvars::m_flFlashMaxAlpha, 0.f, sizeof(0.f));
    }
}