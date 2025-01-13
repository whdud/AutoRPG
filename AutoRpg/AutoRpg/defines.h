
//GameManager::GetInstance()->하기가 귀찮아서
//GET_SINGLE(GameManager)으로 define!!!
//한글 안깨지나?
#define GET_SINGLE(classname) classname::GetInstance()

// TSharedPtr 템플릿 정의
template <typename T>
using TSharedPtr = std::shared_ptr<T>;

// TSharedRef 템플릿 정의 (TSharedPtr와 동일하게 동작)
template <typename T>
using TSharedRef = TSharedPtr<T>;

// TWeakPtr 템플릿 정의
template <typename T>
using TWeakPtr = std::weak_ptr<T>;


#define SAFE_DELETE(ptr)  			  \
	if (ptr)						  \
	{								  \
		delete ptr;					  \
		ptr = nullptr;				  \
	}								  \