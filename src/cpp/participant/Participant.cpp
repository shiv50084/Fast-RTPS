/*************************************************************************
 * Copyright (c) 2014 eProsima. All rights reserved.
 *
 * This copy of eProsima Fast RTPS is licensed to you under the terms described in the
 * FASTRTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/**
 * @file Participant.cpp
 *
 */

#include <fastrtps/participant/Participant.h>

#include "ParticipantImpl.h"

namespace eprosima {
namespace fastrtps {

Participant::Participant():
		mp_impl(nullptr)
{

}

Participant::~Participant() {
	// TODO Auto-generated destructor stub
}

const GUID_t& Participant::getGuid() const
{
	return mp_impl->getGuid();
}

const ParticipantAttributes& Participant::getAttributes()
{
	return mp_impl->getAttributes();
}

bool Participant::newRemoteEndpointDiscovered(const GUID_t& partguid, uint16_t endpointId,
	EndpointKind_t kind)
{
	return mp_impl->newRemoteEndpointDiscovered(partguid, endpointId, kind);
}


} /* namespace pubsub */
} /* namespace eprosima */
