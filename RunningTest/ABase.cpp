#include "ABase.h"
#include <iostream>
#include <string>
#include <cassert>
#include <cstdint>

using std::cout;
using std::endl;

std::string ParseToString(std::uintptr_t pointer)
{
	const std::uintptr_t uAddr = pointer;
	std::string strAddr(16, '0');
	static const char szHex[] = "0123456789ABCDEF";

	for (int i = 15; i >= 0; --i)
	{
		strAddr[static_cast<size_t>(15 - i)] = szHex[(uAddr >> (i * 4)) & 0xFu];
	}

	return strAddr;
}

ABase::ABase() {
	cout << Address() << "\t" << "A Construct" << endl;
}

ABase::~ABase() {
	cout << Address() << "\t" << "A Destroy" << endl;
}

ABase::ABase(int iValue) : m_iValue(iValue) {
	cout << Address() << "\t" << "A Construct with Value: " << GetValue() << endl;
}

ABase::ABase(const ABase& other) : m_iValue(other.GetValue()) {
	cout << Address() << "\t" << "A Copy Construct" << endl;
}

ABase::ABase(ABase&& other) : m_iValue(other.GetValue()) {
	cout << Address() << "\t" << "A Move Construct" << endl;
	other.SetValue(0);
}
ABase& ABase::operator=(const ABase& other) {
	cout << Address() << "\t" << "A Copy Assign" << endl;
	cout << "LHS Value: " << GetValue() << endl;
	cout << "RHS Value: " << other.GetValue() << endl;
	SetValue(other.GetValue());
	return *this;
}
ABase& ABase::operator=(ABase&& other) {
	cout << Address() << "\t" << "A Move Assign" << endl;
	cout << "LHS Value: " << GetValue() << endl;
	cout << "RHS Value: " << other.GetValue() << endl;
	assert(this != &other);
	SetValue(other.GetValue());
	other.SetValue(0);
	return *this;
}

void ABase::Print() const {
	cout << Address() << "\t" << "A Value: " << GetValue() << endl;
}

int ABase::GetValue() const {
	return m_iValue; 
}

void ABase::SetValue(const int iValue) {
	m_iValue = iValue;
}

std::string ABase::Address() const
{
	const auto uAddr = reinterpret_cast<std::uintptr_t>(this);
	std::string strAddr(16, '0');
	static const char szHex[] = "0123456789ABCDEF";
	for (int i = 15; i >= 0; --i)
		strAddr[15 - i] = szHex[(uAddr >> (i * 4)) & 0xFu];
	return strAddr;
}
