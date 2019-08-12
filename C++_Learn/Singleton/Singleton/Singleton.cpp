#include <iostream>


// 饿汉模式

//class Singleton {
//public:
//	static Singleton* GetInstance() {
//		return &m_instance;
//	}
//
//private:
//	
//	Singleton() {};
//	// C++98 防拷贝 防赋值 只声明不实现
//	// Singleton(Singleton const&);
//	// Singleton& operator=(Singleton const&);
//
//	// C++ 11 delete
//	Singleton(Singleton const&) = delete;
//	Singleton& operator=(Singleton const&) = delete;
//
//	static Singleton m_instance;
//};
//
//Singleton Singleton::m_instance;

#include <mutex>
#include <thread>

class Singleton {
public:

	static Singleton* GetInstance() {
		if (nullptr == m_pInstance) {
			m_mtx.lock();
			if (nullptr == m_pInstance) {
				m_pInstance = new Singleton();
			}
			m_mtx.unlock();
		}
		return m_pInstance;
	}

	class CGarbo {
	public:
		~CGarbo() {
			if (Singleton::m_pInstance) {
				delete Singleton::m_pInstance;
			}
		}
	};

	static CGarbo Garbo;

private:
	Singleton() {};
	//Singleton(Singleton const&);
	//Singleton& operator=(Singleton const&);
	
	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&) = delete;
	static std::mutex m_mtx;
	static Singleton* m_pInstance;
};

Singleton* Singleton::m_pInstance = nullptr;
std::mutex Singleton::m_mtx;
Singleton::CGarbo Garbo;
