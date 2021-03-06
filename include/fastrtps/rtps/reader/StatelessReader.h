/*************************************************************************
 * Copyright (c) 2014 eProsima. All rights reserved.
 *
 * This copy of eProsima Fast RTPS is licensed to you under the terms described in the
 * FASTRTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/**
 * @file StatelessReader.h
 */


#ifndef STATELESSREADER_H_
#define STATELESSREADER_H_
#ifndef DOXYGEN_SHOULD_SKIP_THIS_PUBLIC

#include "RTPSReader.h"


namespace eprosima {
namespace fastrtps{
namespace rtps {

/**
 * Class StatelessReader, specialization of the RTPSReader for Best Effort Readers.
 * @ingroup READER_MODULE
 */
class StatelessReader: public RTPSReader {
	friend class RTPSParticipantImpl;
public:
	virtual ~StatelessReader();
private:
	StatelessReader(RTPSParticipantImpl*,GUID_t& guid,
			ReaderAttributes& att,ReaderHistory* hist,ReaderListener* listen=nullptr);
public:
	/**
	 * Add a matched writer represented by a WriterProxyData object.
	 * @param wdata Pointer to the WPD object to add.
	 * @return True if correctly added.
	 */
	bool matched_writer_add(RemoteWriterAttributes& wdata);
	/**
	 * Remove a WriterProxyData from the matached writers.
	 * @param wdata Pointer to the WPD object.
	 * @return True if correct.
	 */
	bool matched_writer_remove(RemoteWriterAttributes& wdata);

	/**
	 * Tells us if a specific Writer is matched against this reader
	 * @param wdata Pointer to the WriterProxyData object
	 * @return True if it is matched.
	 */
	bool matched_writer_is_matched(RemoteWriterAttributes& wdata);

	/**
	 * Method to indicate the reader that some change has been removed due to HistoryQos requirements.
	 * @param change Pointer to the CacheChange_t.
	 * @param prox Pointer to the WriterProxy.
	 * @return True if correctly removed.
	 */
	bool change_removed_by_history(CacheChange_t*,WriterProxy* prox = nullptr);

	/**
	 * Check if the reader accepts messages from a writer with a specific GUID_t.
	 *
	 * @param entityGUID GUID to check
	 * @param wp Pointer to pointer of the WriterProxy. Since we already look for it wee return the pointer
	 * so the execution can run faster.
	 * @return true if the reader accepts messages from the writer with GUID_t entityGUID.
	 */
	bool acceptMsgFrom(GUID_t& entityId,WriterProxy**wp=nullptr);

	/**
	 * This method is called when a new change is received. This method calls the received_change of the History
	 * and depending on the implementation performs different actions.
	 * @param a_change Pointer of the change to add.
	 * @param prox Pointer to the WriterProxy that adds the Change.
	 * @return True if added.
	 */
	bool change_received(CacheChange_t* a_change,WriterProxy* prox = nullptr);

	/**
	 * Read the next unread CacheChange_t from the history
	 * @param change POinter to pointer of CacheChange_t
	 * @return True if read.
	 */
	bool nextUnreadCache(CacheChange_t** change,WriterProxy** wpout=nullptr);
	/**
	 * Take the next CacheChange_t from the history;
	 * @param change Pointer to pointer of CacheChange_t
	 * @return True if read.
	 */
	bool nextUntakenCache(CacheChange_t** change,WriterProxy** wpout=nullptr);

	/**
	 * Get the number of matched writers
	 * @return Number of matched writers
	 */
	inline size_t getMatchedWritersSize() const {return m_matched_writers.size();};

private:
	//!List of GUID_t os matched writers.
	//!Is only used in the Discovery, to correctly notify the user using SubscriptionListener::onSubscriptionMatched();
	std::vector<RemoteWriterAttributes> m_matched_writers;

};

}
} /* namespace rtps */
} /* namespace eprosima */
#endif
#endif /* STATELESSREADER_H_ */
