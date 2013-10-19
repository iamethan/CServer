#ifndef INSTANCEMANAGER_H
#define INSTANCEMANAGER_H

template <typename T, int nSize>
class InstanceManager_T
{
	public:
		InstanceManager_T();
		~InstanceManager_T();
		bool Init(void);
		T const* GetInstanceById(int const nId);
		void RegisterInstance(int nID, T* pLogic);
	private:
		bool m_bReady;
		T* m_apInstances[nSize];
};
template <typename T, int nSize>
InstanceManager_T<T, nSize>::InstanceManager_T()
{
	memset((void*)m_apInstances, 0, sizeof(m_apInstances));
	m_bReady = Init();
};

template <typename T, int nSize>
inline bool InstanceManager_T<T, nSize>::Init(void)
{
	return FALSE;
};

template <typename T, int nSize>
inline InstanceManager_T<T, nSize>::~InstanceManager_T()
{
	m_bReady = FALSE;
	for(int i=0;nSize>i;++i)
	{
		delete m_apInstances[i];
		m_apInstances[i]=NULL;
	};
};

template<typename T, int nSize>
inline T const* InstanceManager_T<T, nSize>::GetInstanceById(int const nId)
{
	if(0<=nId && nSize>nId && true==m_bReady)
	{
		return m_apInstances[nId];
	}
	return NULL;
}

template<typename T, int nSize>
inline void InstanceManager_T<T, nSize>::RegisterInstance(int nID, T* pInstance)
{
	if(NULL==m_apInstances[nID])
	{
		m_apInstances[nID]=pInstance;
	}
	else
	{
		throw("Two instance use a same slot!!!!");
	}
}
#define REGISTER_INSTANCE(INSTANCE) {RegisterInstance(INSTANCE::ID, (new (INSTANCE)));}

#endif //INSTANCEMANAGER_H

