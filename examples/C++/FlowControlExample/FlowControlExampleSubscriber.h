/*************************************************************************
 * Copyright (c) 2013 eProsima. All rights reserved.
 *
 * This generated file is licensed to you under the terms described in the
 * fastcdr_LICENSE file included in this fastcdr distribution.
 *
 *************************************************************************
 * 
 * @file FlowControlExampleSubscriber.h
 * This header file contains the declaration of the subscriber functions.
 *
 * This file was generated by the tool fastcdrgen.
 */


#ifndef _FLOWCONTROLEXAMPLE_SUBSCRIBER_H_
#define _FLOWCONTROLEXAMPLE_SUBSCRIBER_H_

#include <fastrtps/fastrtps_fwd.h>
#include <fastrtps/subscriber/SubscriberListener.h>
#include <fastrtps/subscriber/SampleInfo.h>
#include "FlowControlExamplePubSubTypes.h"

using namespace eprosima::fastrtps;

class FlowControlExampleSubscriber 
{
public:
	FlowControlExampleSubscriber();
	virtual ~FlowControlExampleSubscriber();
	bool init();
	void run();
private:
	Participant *mp_participant;
	Subscriber *mp_subscriber;
	
	class SubListener : public SubscriberListener
	{
	public:
		SubListener() : n_matched(0),n_msg(0){};
		~SubListener(){};
		void onSubscriptionMatched(Subscriber* sub,MatchingInfo& info);
		void onNewDataMessage(Subscriber* sub);
		SampleInfo_t m_info;
		int n_matched;
		int n_msg;
	} m_listener;
	FlowControlExamplePubSubType myType;
};

#endif // _FlowControlExample_SUBSCRIBER_H_