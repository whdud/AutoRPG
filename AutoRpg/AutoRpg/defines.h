#pragma once

#define GET_SINGLE(classname) classname::GetInstance()

// TSharedPtr ���ø� ����
template <typename T>
using TSharedPtr = std::shared_ptr<T>;

// TSharedRef ���ø� ���� (TSharedPtr�� �����ϰ� ����)
template <typename T>
using TSharedRef = TSharedPtr<T>;

// TWeakPtr ���ø� ����
template <typename T>
using TWeakPtr = std::weak_ptr<T>;


#define SAFE_DELETE(ptr)  			  \
	if (ptr)						  \
	{								  \
		delete ptr;					  \
		ptr = nullptr;				  \
	}								  \