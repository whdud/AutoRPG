
//GameManager::GetInstance()->하기가 귀찮아서
//GET_SINGLE(GameManager)으로 define!!!
//한글 안깨지나?
#define GET_SINGLE(classname) classname::GetInstance()

#define SAFE_DELETE(ptr)  			  \
	if (ptr)						  \
	{								  \
		delete ptr;					  \
		ptr = nullptr;				  \
	}								  \