/*************************************************************************
 * Copyright (c) 2013 eProsima. All rights reserved.
 *
 * This copy of FastCdr is licensed to you under the terms described in the
 * EPROSIMARTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/*
 * rtps_messages.h
 *
 *  Created on: Feb 18, 2014
 *      Author: Gonzalo Rodriguez Canosa
 */

#ifndef RTPS_MESSAGES_H_
#define RTPS_MESSAGES_H_

#include <vector>



namespace eprosima{
namespace rtps{

//!@brief RTPS Header Structure
typedef struct Header_t{
			ProtocolVersion_t version;
			VendorId_t vendorId;;
			GuidPrefix_t guidPrefix;
			Header_t(){
				PROTOCOLVERSION(version);
				VENDORID_UNKNOWN(vendorId);
			}
			~Header_t(){
			}
}Header_t;

//!@brief Enumeration of the different Submessages types
#define	PAD 0x01
#define	ACKNACK 0x06
#define	HEARTBEAT 0x07
#define	GAP 0x08
#define	INFO_TS 0x09
#define	INFO_SRC 0x0c
#define	INFO_REPLY_IP4 0x0d
#define	INFO_DST 0x0e
#define	INFO_REPLY 0x0f
#define	NACK_FRAG 0x12
#define	HEARTBEAT_FRAG 0x13
#define	DATA 0x15
#define	DATA_FRAG 0x16


//!@brief RTPS SubmessageHeader Structure
typedef struct{
	octet submessageId;
	uint16_t submessageLength;
	SubmessageFlag flags;
}SubmessageHeader_t;

// SUBMESSAGE types definition

//!@brief RTPS Data Submessage
typedef struct SubmsgData_t{
	SubmessageHeader_t SubmessageHeader;
	bool endiannessFlag;
	bool inlineQosFlag;
	bool dataFlag;
	bool keyFlag;
	EntityId_t readerId;
	EntityId_t writerId;
	SequenceNumber_t writerSN;
	std::vector<Parameter_t> inlineQos;
	SerializedPayload_t serializedPayload;
}SubmsgData_t;

//!@brief RTPS Heartbeat Submessage
typedef struct{
	SubmessageHeader_t SubmessageHeader;
	bool endiannessFlag;
	bool finalFlag;
	bool livelinessFlag;
	EntityId_t readerId;
	EntityId_t writerId;
	SequenceNumber_t firstSN;
	SequenceNumber_t lastSN;
	Count_t count;
}SubmsgHeartbeat_t;

//!@brief RTPS AckNack Submessage
typedef struct{
	SubmessageHeader_t SubmessageHeader;
	bool endiannessFlag;
	bool finalFlag;
	EntityId_t readerId;
	EntityId_t writerId;
	SequenceNumberSet_t readerSNState;
	Count_t count;
}SubmsgAcknack_t;

//!@brief RTPS GAP Submessage
typedef struct{
	SubmessageHeader_t SubmessageHeader;
	bool endiannessFlag;
	EntityId_t readerId;
	EntityId_t writerId;
	SequenceNumber_t gapStart;
	SequenceNumberSet_t gapList;
}SubmsgGap_t;


//!@brief RTPS InfoTS Submessage
typedef struct{
	SubmessageHeader_t SubmessageHeader;
	Time_t timestamp;
}SubmsgInfoTS_t;



/**
 * @brief CDR Serialized Message Structure.
 */
typedef struct CDRMessage_t{
	CDRMessage_t(){
		pos = 0;
		buffer = NULL;
		max_size = RTPSMESSAGE_MAX_SIZE;

		msg_endian = BIGEND;
	}
	~CDRMessage_t(){
		if(buffer != NULL)
			free(buffer);
	}
	octet* buffer;
	uint16_t pos; //current w_pos in bytes
	uint16_t max_size; // max size of buffer in bytes
	uint16_t length;
	Endianness_t msg_endian;
}CDRMessage_t;



}
}



#endif /* RTPS_MESSAGES_H_ */