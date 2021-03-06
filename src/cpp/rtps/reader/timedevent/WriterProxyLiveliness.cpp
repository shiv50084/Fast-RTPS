/*************************************************************************
 * Copyright (c) 2014 eProsima. All rights reserved.
 *
 * This copy of eProsima Fast RTPS is licensed to you under the terms described in the
 * FASTRTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/**
 * @file WriterProxyLiveliness.cpp
 *
 */

#include <fastrtps/rtps/reader/timedevent/WriterProxyLiveliness.h>
#include <fastrtps/rtps/common/MatchingInfo.h>
#include <fastrtps/rtps/reader/StatefulReader.h>
#include <fastrtps/rtps/reader/ReaderListener.h>
#include <fastrtps/rtps/reader/WriterProxy.h>

#include "../../participant/RTPSParticipantImpl.h"

#include <fastrtps/utils/RTPSLog.h>



namespace eprosima {
namespace fastrtps{
namespace rtps {

static const char* const CLASS_NAME = "WriterProxyLiveliness";

WriterProxyLiveliness::WriterProxyLiveliness(WriterProxy* p_WP,double interval):
		TimedEvent(p_WP->mp_SFR->getRTPSParticipant()->getIOService(),interval),
				mp_WP(p_WP)
{

}

WriterProxyLiveliness::~WriterProxyLiveliness()
{
	stop_timer();
}

void WriterProxyLiveliness::event(EventCode code, const char* msg)
{
	const char* const METHOD_NAME = "event";
	if(code == EVENT_SUCCESS)
	{
	
		logInfo(RTPS_LIVELINESS,"Deleting Writer: "<<mp_WP->m_att.guid,C_MAGENTA);
//		if(!mp_WP->isAlive())
//		{
			//logWarning(RTPS_LIVELINESS,"Liveliness failed, leaseDuration was "<< this->getIntervalMilliSec()<< " ms",C_MAGENTA);
			if(mp_WP->mp_SFR->matched_writer_remove(mp_WP->m_att,false))
			{
				if(mp_WP->mp_SFR->getListener()!=nullptr)
				{
					MatchingInfo info(REMOVED_MATCHING,mp_WP->m_att.guid);
					mp_WP->mp_SFR->getListener()->onReaderMatched((RTPSReader*)mp_WP->mp_SFR,info);
				}
			}
			//NOW WE DELETE THE OBJECTS
			mp_WP->mp_writerProxyLiveliness = nullptr;
			delete(mp_WP);
			delete(this);
			return;
//		}
//		mp_WP->setNotAlive();
//		this->restart_timer();
	}
	else if(code == EVENT_ABORT)
	{
		this->stopSemaphorePost();
	}
	else
	{
		logInfo(RTPS_LIVELINESS,"boost message: " <<msg);
	}
}


}
} /* namespace rtps */
} /* namespace eprosima */
