#include "pch.h"
#include "EventSytem.h"

using namespace eventSystem;

class Subscriber::impl
{
	friend class Publisher;
private:
	std::string m_messageByPub = "test";
	Publisher& m_pub;
	static int32_t m_pubId;
	int32_t m_currentId;
public:
	impl(Publisher& pub) : m_pub(pub)
	{
		m_currentId = ++m_pubId;
	}
	impl(const Subscriber& other) : 
		m_currentId(other.pimpl->m_currentId), m_messageByPub(other.pimpl->m_messageByPub), m_pub(other.pimpl->m_pub)
	{ }
	~impl() { }
public:
	void update(const std::string& messageByPub)
	{
		// dfjkgh
	}
	int32_t getId() const { return m_currentId; }
};


//////////////////////////////////////////////////////////////////////////////////////////////


class Publisher::impl
{
	friend class Subscriber;
private:
	std::string m_name = "test";
	std::list<Subscriber*> m_subs;
public:
	impl(const std::string& name) : m_name(name) {  }
	impl(const Publisher& other) :
		m_subs(other.pimpl->m_subs), m_name(other.pimpl->m_name)
	{ }
	~impl() { }
public:
	void addSub(Subscriber* sub) { m_subs.push_back(sub); }
	void removeSub(Subscriber* sub) { m_subs.remove(sub); }
	void updateState(const std::string& str)
	{
		m_name = str;
		notify();
	}
	void notify() { for (auto c : m_subs) c->update(m_name); }

};
