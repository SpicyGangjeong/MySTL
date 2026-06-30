#pragma once
#include <string>

class ABase {
public:
	ABase();
	~ABase();
	explicit ABase(int iValue);

	ABase(const ABase& other);				// 복사 생성자 명시
	ABase(ABase&& other);					// 이동 생성자 명시

public:
	ABase& operator=(const ABase& other);	// 복사 할당자 명시
	ABase& operator=(ABase&& other);		// 이동 할당자 명시

public:
	void		Print()		const;
	int			GetValue()	const;
	void		SetValue(const int);

private:
	int m_iValue = 0;

private:
	std::string	Address()	const;
};
