/*************************************************************************
 * Copyright (c) 2014 eProsima. All rights reserved.
 *
 * This copy of eProsima Fast RTPS is licensed to you under the terms described in the
 * FASTRTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/**
 * @file ReaderQos.h
 *
 */

#ifndef READERQOS_H_
#define READERQOS_H_

#include "QosPolicies.h"

namespace eprosima {
namespace fastrtps {

/**
 * Class ReaderQos, contains all the possible Qos that can be set for a determined Subscriber.
 * Although these values can be set and are transmitted
 * during the Endpoint Discovery Protocol, not all of the behaviour associated with them has been implemented in the library.
 * Please consult each of them to check for implementation details and default values.
 * @ingroup FASTRTPS_ATTRIBUTES_MODULE
 */
class  ReaderQos{
public:
	RTPS_DllAPI ReaderQos(){};
	RTPS_DllAPI virtual ~ReaderQos(){};
	//!Durability Qos, implemented in the library.
	DurabilityQosPolicy m_durability;
	//!Deadline Qos, NOT implemented in the library.
	DeadlineQosPolicy m_deadline;
	//!Latency Budget Qos, NOT implemented in the library.
	LatencyBudgetQosPolicy m_latencyBudget;
	//!Liveliness Qos, implemented in the library.
	LivelinessQosPolicy m_liveliness;
	//!ReliabilityQos, implemented in the library.
	ReliabilityQosPolicy m_reliability;
	//!Ownership Qos, NOT implemented in the library.
	OwnershipQosPolicy m_ownership;
	//!Destinatio Order Qos, NOT implemented in the library.
	DestinationOrderQosPolicy m_destinationOrder;
	//!UserData Qos, NOT implemented in the library.
	UserDataQosPolicy m_userData;
	//!Time Based Filter Qos, NOT implemented in the library.
	TimeBasedFilterQosPolicy m_timeBasedFilter;
	//!Presentation Qos, NOT implemented in the library.
	PresentationQosPolicy m_presentation;
	//!Partition Qos, implemented in the library.
	PartitionQosPolicy m_partition;
	//!Topic Data Qos, NOT implemented in the library.
	TopicDataQosPolicy m_topicData;
	//!GroupData Qos, NOT implemented in the library.
	GroupDataQosPolicy m_groupData;
	//!Durability Service Qos, NOT implemented in the library.
	DurabilityServiceQosPolicy m_durabilityService;
	//!Lifespan Qos, NOT implemented in the library.
	LifespanQosPolicy m_lifespan;
	/**
	 * Set Qos from another class
	 * @param readerqos Reference from a ReaderQos object.
	 * @param first_time Boolean indicating whether is the first time (If not some parameters cannot be set).
	 */
	RTPS_DllAPI void setQos(ReaderQos& readerqos, bool first_time);
	/**
	 * Check if the Qos values are compatible between each other.
	 * @return True if correct.
	 */
	RTPS_DllAPI bool checkQos();
	/**
	 * Check if the Qos can be update with the values provided. This method DOES NOT update anything.
	 * @param qos Reference to the new qos.
	 * @return True if they can be updated.
	 */
	RTPS_DllAPI bool canQosBeUpdated(ReaderQos& qos);
};



} /* namespace  */
} /* namespace eprosima */

#endif /* READERQOS_H_ */
