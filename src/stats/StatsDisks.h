/*
 *  Copyright 2016 Bjango Pty Ltd. All rights reserved.
 *  Copyright 2010 William Tisäter. All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *    1.  Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *
 *    2.  Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *
 *    3.  The name of the copyright holder may not be used to endorse or promote
 *        products derived from this software without specific prior written
 *        permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER ``AS IS'' AND ANY
 *  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL WILLIAM TISÄTER BE LIABLE FOR ANY
 *  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "StatBase.h"

#ifndef _STATSDISKS_H
#define _STATSDISKS_H

class disk_info
{
	public:
		bool active;
		bool is_new;
		unsigned int id;
		std::string uuid;
		std::string label;
		std::string name;
		std::string key;
		std::string displayName;
		double last_update;
		std::deque<disk_data> samples[8];
};
class StatsDisks : public StatsBase
{
	public:
		int useMountPaths;
		int disableFiltering;
		void update(long long sampleID);
		int sensorType(int type);
		void prepareUpdate();
		void init();
		std::vector<disk_info> _items;
		void createDisk(std::string key);
		void processDisk(char *name, char *mount, char *type);
		int get_sizes(const char *dev, struct disk_data *data);
		int should_ignore_type(char *type);
		int should_ignore_mount(char *mount);
		std::vector<std::string> customNames;

		void loadHistoryForDisk(disk_info *disk);
		#ifdef USE_SQLITE
		void updateHistory();
		disk_data historyItemAtIndex(int index, disk_info item);
		void loadPreviousSamples();
		void loadPreviousSamplesAtIndex(int index);
		#endif

	   	std::deque<sample_data> samples[8];
	};
#endif
