	//单例

template<typename T>
class Singleton {
private:
	static T* _t;

public:
	Singleton() {
	}
	~Singleton() {
	}

	static T* Instant() {
		if (NULL == _t) 
			_t = new T();

		return _t;
	}

	static void release()
	{
		delete _t;
		_t = NULL;
	}

};
template<typename T>
T* Singleton<T>::_t = NULL;
