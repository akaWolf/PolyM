#include "Msg.hpp"

#include <cmsis-plus/estd/mutex>

using namespace os::estd;

namespace PolyM {

namespace {

MsgUID generateUniqueId()
{
	static mutex uidMutex;
	lock_guard<mutex> lock(uidMutex);
	static MsgUID i(0);
	return ++i;
}

}

Msg::Msg(int msgId)
	: msgId_(msgId), uniqueId_(generateUniqueId())
{
}

std::unique_ptr<Msg> Msg::move()
{
	return std::unique_ptr<Msg>(new Msg(std::move(*this)));
}

int Msg::getMsgId() const
{
	return msgId_;
}

MsgUID Msg::getUniqueId() const
{
	return uniqueId_;
}

}
