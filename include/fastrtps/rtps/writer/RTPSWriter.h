/*************************************************************************
 * Copyright (c) 2014 eProsima. All rights reserved.
 *
 * This copy of eProsima Fast RTPS is licensed to you under the terms described in the
 * FASTRTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/**
 * @file RTPSWriter.h
 */


#ifndef RTPSWRITER_H_
#define RTPSWRITER_H_

#include "../Endpoint.h"
#include "../messages/RTPSMessageGroup.h"
#include "../attributes/WriterAttributes.h"



namespace eprosima {
namespace fastrtps{
namespace rtps {

class UnsentChangesNotEmptyEvent;
class WriterListener;
class WriterHistory;
struct CacheChange_t;


/**
 * Class RTPSWriter, manages the sending of data to the readers. Is always associated with a HistoryCache.
 * @ingroup WRITER_MODULE
 */
class RTPSWriter : public Endpoint
{
	friend class WriterHistory;
	friend class UnsentChangesNotEmptyEvent;
	friend class RTPSParticipantImpl;
	friend class RTPSMessageGroup;
protected:
	RTPSWriter(RTPSParticipantImpl*,GUID_t& guid,WriterAttributes& att,WriterHistory* hist,WriterListener* listen=nullptr);
	virtual ~RTPSWriter();
public:
	/**
	 * Create a new change based with the provided changeKind.
	 * @param changeKind The type of change.
	 * @param handle InstanceHandle to assign.
	 * @return Pointer to the CacheChange or nullptr if incorrect.
	 */
	RTPS_DllAPI CacheChange_t* new_change(ChangeKind_t changeKind, InstanceHandle_t handle = c_InstanceHandle_Unknown);
	/**
	 * Add a matched reader.
	 * @param ratt Pointer to the ReaderProxyData object added.
	 * @return True if added.
	 */
	RTPS_DllAPI virtual bool matched_reader_add(RemoteReaderAttributes& ratt) = 0;
	/**
	 * Remove a matched reader.
	 * @param ratt Pointer to the object to remove.
	 * @return True if removed.
	 */
	RTPS_DllAPI virtual bool matched_reader_remove(RemoteReaderAttributes& ratt) = 0;
	/**
	 * Tells us if a specific Reader is matched against this writer
	 * @param ratt Pointer to the ReaderProxyData object
	 * @return True if it was matched.
	 */
	RTPS_DllAPI virtual bool matched_reader_is_matched(RemoteReaderAttributes& ratt) = 0;
	/**
	 * Check if a specific change has been acknowledged by all Readers.
	 * Is only useful in reliable Writer. In BE Writers always returns true;
	 * @return True if acknowledged by all.
	 */
	RTPS_DllAPI virtual bool is_acked_by_all(CacheChange_t* a_change){ return true; }
	/**
	 * Update the Attributes of the Writer.
	 * @param att New attributes
	 */
	RTPS_DllAPI virtual void updateAttributes(WriterAttributes& att) = 0;
	/**
	 * This methods trigger the send operation for unsent changes.
	 */
	RTPS_DllAPI virtual void unsent_changes_not_empty() = 0;
	
	/**
	* Get Min Seq Num in History.
	* @return Minimum sequence number in history
	*/
	RTPS_DllAPI SequenceNumber_t get_seq_num_min();
	
	/**
	* Get Max Seq Num in History.
	* @return Maximum sequence number in history
	*/
	RTPS_DllAPI SequenceNumber_t get_seq_num_max();
	
	/**
	* Get maximum size of the serialized type
	* @return Maximum size of the serialized type
	*/
	RTPS_DllAPI uint32_t getTypeMaxSerialized();
	
	/**
	* Get listener
	* @return Listener
	*/
	RTPS_DllAPI inline WriterListener* getListener(){ return mp_listener; };
	 
	/**
	* Get the asserted liveliness
	* @return Asserted liveliness
	*/
	RTPS_DllAPI inline bool getLivelinessAsserted() { return m_livelinessAsserted; };
	
	/**
	* Get the asserted liveliness
	* @return asserted liveliness
	*/
	RTPS_DllAPI inline void setLivelinessAsserted(bool l){ m_livelinessAsserted = l; };
protected:

	//!Is the data sent directly or announced by HB and THEN send to the ones who ask for it?.
	bool m_pushMode;
	//!Group created to send messages more efficiently
	RTPSMessageGroup_t m_cdrmessages;
	//!INdicates if the liveliness has been asserted
	bool m_livelinessAsserted;
	//!Event that manages unsent changes
	UnsentChangesNotEmptyEvent* mp_unsetChangesNotEmpty;
	//!WriterHistory
	WriterHistory* mp_history;
	//!Listener
	WriterListener* mp_listener;
	/**
	 * Initialize the header of hte CDRMessages.
	 */
	void init_header();

	/**
	 * Add a change to the unsent list.
	 * @param change Pointer to the change to add.
	 */
	virtual void unsent_change_added_to_history(CacheChange_t* change)=0;
	/**
	 * Indicate the writer that a change has been removed by the history due to some HistoryQos requirement.
	 * @param a_change Pointer to the change that is going to be removed.
	 * @return True if removed correctly.
	 */
	virtual bool change_removed_by_history(CacheChange_t* a_change)=0;

	/**
	* Get RTPS participant
	* @return RTPS participant
	*/
	inline RTPSParticipantImpl* getRTPSParticipant() const {return mp_RTPSParticipant;}


};
}
} /* namespace rtps */
} /* namespace eprosima */

#endif /* RTPSWRITER_H_ */
