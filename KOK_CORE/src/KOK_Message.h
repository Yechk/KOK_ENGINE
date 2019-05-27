#ifndef KOK_MESSAGE
#define KOK_MESSAGE

#include "KOK_Actor.h"
#include <queue>

using namespace std;

struct KOK_Message
{
  unsigned long long subject; //what is this message about?
  MessageData data; //generic pointer to data
  KOK_Actor* target; //where to deliver
  KOK_Actor* sender; //return address

  KOK_Message(unsigned long long s, MessageData d, KOK_Actor* t, KOK_Actor* sd) : subject{s}, data{d}, target{t}, sender{sd} {};
};

class KOK_MailBox
{
public:
  bool DeliverNextMessage();
  inline void AddMessage(KOK_Message m)
  {
    _messages.push(m);
  };

private:
  queue<KOK_Message> _messages;
};

enum MessageFlag
{
  BROADCAST,
  URGENT,
  EXPRESS,
  MEDIA
};

enum DeliverFlag
{
  MARCH,
  INTERLEAVE,
  DUMP
};

class KOK_PostOffice
{
public:

  KOK_PostOffice(unsigned int m) : maxMessagesPerFrame{m} {};

  void QueueMessage(unsigned long long subject, MessageData data, KOK_Actor* target, KOK_Actor* sender, MessageFlag flags);
  void QueueMessage(unsigned long long subject, float data, KOK_Actor* target, KOK_Actor* sender, MessageFlag flags);
  void QueueMessage(unsigned long long subject, double data, KOK_Actor* target, KOK_Actor* sender, MessageFlag flags);
  void QueueMessage(unsigned long long subject, int data, KOK_Actor* target, KOK_Actor* sender, MessageFlag flags);
  void QueueMessage(unsigned long long subject, uint data, KOK_Actor* target, KOK_Actor* sender, MessageFlag flags);
  void QueueMessage(unsigned long long subject, void* data, KOK_Actor* target, KOK_Actor* sender, MessageFlag flags);
  void Update(DeliverFlag flag);
  void Broadcast(vector<KOK_Actor>& recipients);

private:

  unsigned int maxMessagesPerFrame;

  KOK_MailBox _urgent;
  KOK_MailBox _express;
  KOK_MailBox _media;

  queue<KOK_Message> _broadcast;
};

#endif
