#pragma once
#include "MySTL_Macro.h"
#include <cstring>
#include <utility>

template<typename _Ty>
class Vector {
	const static size_t s_BaseCapacity = 16;
public:
	Vector<_Ty>() { m_pContainer = Allocate(m_iCapacity); }
	~Vector<_Ty>() { Deallocate(m_pContainer, m_iSize); m_iSize = 0; }
	_Ty& operator[](int iIndex) {
		return m_pContainer[iIndex];
	}
	size_t size() { return m_iSize; }
	size_t capacity() { return m_iCapacity; }
	bool empty() { return 0 == m_iSize; }
	void clear();

	template<typename... Args>
	void emplace_back(Args&&... args);
	void push_back(const _Ty& iValue);
	void push_back(_Ty&& iValue);


	void pop_back();
private:
	template<typename... Args>
	void Emplace_One_At_Back(Args&&... args);
	void Reallocate(size_t iSize);
	void Deallocate(_Ty* pContainer, size_t iCapacity);
	_Ty* Allocate(size_t iSize);

	size_t m_iSize = 0;
	size_t m_iCapacity = s_BaseCapacity;
	_Ty* m_pContainer = nullptr;
};

template<typename _Ty>
inline void Vector<_Ty>::clear() {
	for (size_t i = 0; i < m_iSize; ++i) {
		m_pContainer[i].~_Ty();
	}
	memset(m_pContainer, 0, sizeof(_Ty) * m_iSize);
	m_iSize = 0;
}

template<typename _Ty>
template<typename ...Args>
inline void Vector<_Ty>::emplace_back(Args&&... args) {
	Emplace_One_At_Back(std::forward<Args>(args)...);
}

template<typename _Ty>
inline void Vector<_Ty>::push_back(const _Ty& iValue) {
	Emplace_One_At_Back(iValue);
}

template<typename _Ty>
inline void Vector<_Ty>::push_back(_Ty&& iValue) {
	Emplace_One_At_Back(std::move(iValue));
}

template<typename _Ty>
template<typename ...Args>
inline void Vector<_Ty>::Emplace_One_At_Back(Args&&... args) {
	if (m_iSize >= m_iCapacity) {
		Reallocate(m_iCapacity + (m_iCapacity >> 1));
	}
	PLACEMENT_NEW((m_pContainer + m_iSize), _Ty(std::forward<Args>(args)...));
	++m_iSize;
}

template<typename _Ty>
inline void Vector<_Ty>::pop_back() {
    if (0 == m_iSize) {
        return;
    }
    --m_iSize;
	m_pContainer[m_iSize].~_Ty();
    memset(&m_pContainer[m_iSize], 0, sizeof(_Ty));
}

template<typename _Ty>
inline void Vector<_Ty>::Reallocate(size_t iNewCapacity) {
	_Ty* pNewContainer = Allocate(iNewCapacity);
	{
		for (size_t i = 0; i < m_iSize; ++i) {
			PLACEMENT_NEW((pNewContainer + i), _Ty(std::move(m_pContainer[i])));
			m_pContainer[i].~_Ty();
		}
		ALIGNED_DELETE(m_pContainer, alignof(_Ty));
	}
	m_pContainer = pNewContainer;
	m_iCapacity = iNewCapacity;
}

template<typename _Ty>
inline void Vector<_Ty>::Deallocate(_Ty* pContainer, size_t iActiveSize) {
	if (nullptr == pContainer) {
		return;
	}
	if (0 != iActiveSize) {
		for (size_t i = 0; i < iActiveSize; ++i) {
			pContainer[i].~_Ty();
		}
	}
	ALIGNED_DELETE(pContainer, alignof(_Ty));
	pContainer = nullptr;
}

template<typename _Ty>
inline _Ty* Vector<_Ty>::Allocate(size_t iSize)
{
	size_t iByteSize = sizeof(_Ty) * iSize;
	size_t iAlignSize = alignof(_Ty);
	_Ty* pBuffer = static_cast<_Ty*>(ALIGNED_NEW(iByteSize, iAlignSize));
	return pBuffer;
}
