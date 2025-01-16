#pragma once

#define GET_SINGLE(classname) classname::GetInstance()

// TSharedPtr 이걸로 쉐어드포인터사용 ㄱㄱ
template <typename T>
using TSharedPtr = std::shared_ptr<T>;

// TSharedRef
template <typename T>
using TSharedRef = TSharedPtr<T>;

// TWeakPtr
template <typename T>
using TWeakPtr = std::weak_ptr<T>;


#define SAFE_DELETE(ptr)  			  \
	if (ptr)						  \
	{								  \
		delete ptr;					  \
		ptr = nullptr;				  \
	}								  \