﻿/*************************************************************************
 * Copyright (c) 2014 eProsima. All rights reserved.
 *
 * This copy of eProsima Fast RTPS is licensed to you under the terms described in the
 * FASTRTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/



#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <cstdint>

#include "fastrtps/utils/RTPSLog.h"



#include "ZMQThroughputPublisher.h"
#include "ZMQThroughputSubscriber.h"


using namespace std;


#if defined(__LITTLE_ENDIAN__)
const Endianness_t DEFAULT_ENDIAN = LITTLEEND;
#elif defined (__BIG_ENDIAN__)
const Endianness_t DEFAULT_ENDIAN = BIGEND;
#endif

#if defined(_WIN32)
#define COPYSTR strcpy_s
#else
#define COPYSTR strcpy
#endif


int main(int argc, char** argv){
	Log::setVerbosity(VERB_ERROR);
	cout << "Starting Throughput Test"<< endl;
	int type;
	uint32_t test_time_sec = 30;
	int demand = 0;
	int msg_size = 0;
	std::string IP;
	uint32_t PORTBASE = 10000;
	if(argc > 2)
	{
		if(strcmp(argv[1],"publisher")==0)
			type = 1;
		if(strcmp(argv[1],"subscriber")==0)
			type = 2;
		if(argc > 2)
		{
			std::istringstream iss( argv[2] );
			IP = iss.str();
		}
		if(argc > 3 && type == 1)
		{
			std::istringstream iss( argv[3] );
			if (!(iss >> test_time_sec))
			{
				cout << "Problem reading test time,using 30s as default value "<< endl;
				test_time_sec = 30;
			}
		}
		if (argc > 4 && type == 1)
		{
			std::istringstream iss_demand( argv[4] );
			if (!(iss_demand >> demand))
			{
				cout << "Problem reading demand,using default demand vector "<< endl;
				demand = 0;
			}
		}
		if (argc > 5 && type == 1)
		{
			std::istringstream iss_size( argv[5] );
			if (!(iss_size >> msg_size))
			{
				cout << "Problem reading msg size,using default size vector "<< endl;
				msg_size = 0;
			}
		}
	}
	else
	{
		cout << "Needs publisher OR subscriber argument and IP"<<endl;
		cout << "Usage: "<<endl;
		cout << "ZMQThroughput \"publisher\" subscriberIP [seconds] [demand] [msg_size]"<<endl;
		cout << "ZMQThroughput \"subscriber\" publisherIP "<<endl;
		return 0;
	}



	switch (type)
	{
	case 1:
	{
		ZMQThroughputPublisher tpub;
		if(tpub.init(IP,PORTBASE))
			tpub.run(test_time_sec,demand,msg_size);
		break;
	}
	case 2:
	{

		ZMQThroughputSubscriber tsub;
		if(tsub.init(IP,PORTBASE))
			tsub.run();
		break;
	}
	}




	return 0;
}



