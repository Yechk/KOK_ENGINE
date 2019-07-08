#include "KOK_Message.h"
#include "KOK_Actor.h"

#include "string.h"

#include <queue>

using namespace std;

bool KOK_MailBox::DeliverNextMessage()
{
  if(_messages.empty()) return false;

  KOK_Message m = _messages.front();

  m.target->DeliverMessage(m.subject, m.data, m.sender);
  _messages.pop();

  return true;
}

void KOK_PostOffice::QueueMessage(string subject, MessageData data, KOK_Actor* target, KOK_Actor* sender, MessageFlag flags)
{
  KOK_Message m = KOK_Message(subject, data, target, sender);
  if (flags == BROADCAST) _broadcast.push(m);
  if (flags == URGENT) _urgent.AddMessage(m);
  if (flags == EXPRESS) _express.AddMessage(m);
  if (flags == MEDIA) _media.AddMessage(m);
}

void KOK_PostOffice::QueueMessage(string subject, float data, KOK_Actor* target, KOK_Actor* sender, MessageFlag flags)
{
  MessageData t;
  t.f = data;

  QueueMessage(subject, t, target, sender, flags);
}

void KOK_PostOffice::QueueMessage(string subject, double data, KOK_Actor* target, KOK_Actor* sender, MessageFlag flags)
{
  MessageData t;
  t.d = data;

  QueueMessage(subject, t, target, sender, flags);
}

void KOK_PostOffice::QueueMessage(string subject, int data, KOK_Actor* target, KOK_Actor* sender, MessageFlag flags)
{
  MessageData t;
  t.i = data;

  QueueMessage(subject, t, target, sender, flags);
}

void KOK_PostOffice::QueueMessage(string subject, uint data, KOK_Actor* target, KOK_Actor* sender, MessageFlag flags)
{
  MessageData t;
  t.ui = data;

  QueueMessage(subject, t, target, sender, flags);
}

void KOK_PostOffice::QueueMessage(string subject, void* data, KOK_Actor* target, KOK_Actor* sender, MessageFlag flags)
{
  MessageData t;
  t.p = data;

  QueueMessage(subject, t, target, sender, flags);
}

void KOK_PostOffice::Update(DeliverFlag flag)
{
  unsigned int sent = 0;

  if(flag == DUMP)
  {
    while(_urgent.DeliverNextMessage());

    return;
  }

  if(flag == MARCH)
  {
    while(sent < maxMessagesPerFrame && _urgent.DeliverNextMessage())
    {
      sent += 1;
    }

    while(sent < maxMessagesPerFrame && _express.DeliverNextMessage())
    {
      sent += 1;
    }

    while(sent < maxMessagesPerFrame && _media.DeliverNextMessage())
    {
      sent += 1;
    }

    return;
  }

  if(flag == INTERLEAVE)
  {
    while(sent < maxMessagesPerFrame)
    {
      sent = 0;

      if(_urgent.DeliverNextMessage()) sent += 1;
      if(_urgent.DeliverNextMessage()) sent += 1;
      if(_urgent.DeliverNextMessage()) sent += 1;

      if(_express.DeliverNextMessage()) sent += 1;
      if(_express.DeliverNextMessage()) sent += 1;

      if(_media.DeliverNextMessage()) sent += 1;

      if(sent == 0) return;
    }

    return;
  }
}

void KOK_PostOffice::Broadcast(vector<KOK_Actor>& recipients)
{

  while(!_broadcast.empty())
  {
    KOK_Message m = _broadcast.front();

    for(int i = 0; i < recipients.size(); i++) recipients[i].DeliverMessage(m.subject, m.data, m.sender);
    _broadcast.pop();
  }
}
