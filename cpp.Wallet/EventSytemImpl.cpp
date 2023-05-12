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

int32_t Subscriber::impl::m_pubId = 0;

Subscriber::Subscriber(Publisher& pub) :
	pimpl(std::make_unique<impl>(pub))
{ }
Subscriber::Subscriber(const Subscriber& other) :
	pimpl(std::make_unique<impl>(other))
{ }
Subscriber& Subscriber::operator=(const Subscriber& rhs)
{
	if (this != &rhs)
		pimpl.reset(new impl(*rhs.pimpl));
	return *this;
}
Subscriber::Subscriber(Subscriber&& other) noexcept :
	pimpl(std::move(other.pimpl))
{ }
Subscriber& Subscriber::operator=(Subscriber&& rhs) noexcept
{
	if (this != &rhs)
		pimpl = std::move(rhs.pimpl);
	return *this;
}

Subscriber::~Subscriber() { }

void Subscriber::update(const std::string& messageByPub) { pimpl->update(messageByPub); }
int32_t Subscriber::getId() const { return pimpl->getId(); }


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

Publisher::Publisher(const std::string& name) :
	pimpl(std::make_unique<impl>(name))
{ }
Publisher::~Publisher() { }

Publisher::Publisher(const Publisher& other) :
	pimpl(std::make_unique<impl>(other))
{ }
Publisher& Publisher::operator=(const Publisher& rhs)
{
	if (this != &rhs)
		pimpl.reset(new impl(*rhs.pimpl));
	return *this;
}
Publisher::Publisher(Publisher&& other) noexcept :
	pimpl(std::move(other.pimpl))
{ }
Publisher& Publisher::operator=(Publisher&& rhs) noexcept
{
	if (this != &rhs)
		pimpl = std::move(rhs.pimpl);
	return *this;
}

void Publisher::addSub(Subscriber* sub) { pimpl->addSub(sub); }
void Publisher::removeSub(Subscriber* sub) { pimpl->removeSub(sub); }
void Publisher::updateState(const std::string& str) { pimpl->updateState(str); }
void Publisher::notify() { pimpl->notify(); }