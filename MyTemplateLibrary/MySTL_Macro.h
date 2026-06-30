#pragma once
#include <new>
// https://en.cppreference.com/cpp/language/new // Placement 참고
// https://learn.microsoft.com/ko-kr/cpp/cpp/new-operator-cpp?view=msvc-170 // MSDN은 모든것을 알고 있다. ( 단지 우리가 못알아 봤을 뿐 )
#define PLACEMENT_NEW(iAddress, Initializer) new (iAddress) Initializer
#define ALIGNED_NEW(iByteSize, iAlignSize) operator new (iByteSize, std::align_val_t(iAlignSize))
#define ALIGNED_DELETE(iAddress, iAlignSize) operator delete (iAddress, std::align_val_t(iAlignSize))
