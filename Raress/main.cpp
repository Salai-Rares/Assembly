#include <windows.h>
#include <iostream>
using namespace std;
#include <tchar.h>
#include <psapi.h>
#include <cstdlib>
#include <stdint.h>
#include <intrin.h>
#include <synchapi.h>
#include <winbase.h>
#include <processthreadsapi.h >
void procInfo() {
	unsigned long int eflags1, eflags2;
	char vendorID[13];
	unsigned long int success = 0;
	unsigned long int modelNum, FamilyCODE, ExtMODE, procTYPE, extFam, start;
	unsigned long int brandID, prop, proccount, ca, cb, cc, cd;
	__asm {
		pushfd
		pop eax; preluare EFLAGS
		mov eflags1, eax
		xor eax, 00200000h
		mov eflags2, eax 
		push eax
		popfd 
		pushfd
		pop eax
		cmp eax, eflags2
		je SUCCESS
		jmp CONTINUE
		SUCCESS : mov success, 1
		mov eax, 00h
		cpuid; setare info cerută în eax
		CONTINUE : mov eax, eflags1
		mov eax, 0
		cpuid
		mov DWORD PTR vendorID, ebx
		mov DWORD PTR vendorID + 4, edx
		mov DWORD PTR vendorID + 8, ecx
		mov eax, 1
		cpuid
		mov modelNum, eax
		and modelNum, 0F0h
		mov FamilyCODE, eax
		and FamilyCODE, 0F00h
		mov procTYPE, eax
		and procTYPE, 3000h
		mov ExtMODE, eax
		and ExtMODE, 0F0000h
		mov extFam, eax
		and extFam, 0FF00000h
		mov brandID, ebx
		and brandID, 380h
		mov prop, edx
		and prop, 0Fh
		mov eax, 0Bh
		mov ecx, 0
		cpuid
		mov proccount, ebx
		and proccount, 0FFh
		mov eax, 2
		cpuid
		mov ca, eax
		mov cb, ebx
		mov cc, ecx
		mov cd, edx
	}
	if (success != 0) {
		printf("EFLAGS initial si cel modificat sunt egale.\n");
	}
	else {
		printf("EFLAGS initial si cel modificat nu sunt egale.\n\n");
	}
	vendorID[12] = '\0';
	cout << "Vendor ID: " << vendorID << "\n\n";
	modelNum >>= 4;
	FamilyCODE >>= 8;
	procTYPE >>= 12;
	ExtMODE >>= 16;
	extFam >>= 20;
	cout << "Model Number: " << modelNum << "\n";
	cout << "Family Code: " << FamilyCODE << "\n";
	cout << "Extended Mode: " << ExtMODE << "\n";
	cout << "Processor Type: " << procTYPE << "\n";
	cout << "Extended Family: " << extFam << "\n";
	brandID >>= 7;
	cout << "Brand ID: " << brandID << "\n\n";
	cout << "Flags FPU, VME, DE, PSE: " << prop << "\n\n";
	cout << "No. procesoare logice: " << proccount << "\n\n";
	cout << "Info. despre cache: \n" << std::hex << ca << "\n" << std::hex << cb <<
		"\n" << std::hex << cc << "\n" << std::hex << cd << "\n\n";
}
int _tmain(int argc, _TCHAR* argv[])
{
	procInfo();
}