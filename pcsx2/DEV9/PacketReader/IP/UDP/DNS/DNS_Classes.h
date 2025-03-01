// SPDX-FileCopyrightText: 2002-2025 PCSX2 Dev Team
// SPDX-License-Identifier: GPL-3.0+

#pragma once

#include "common/Pcsx2Defs.h"

#include <string>
#include <vector>

namespace PacketReader::IP::UDP::DNS
{
	class DNS_QuestionEntry
	{
	public:
		std::string name;
		u16 entryType;
		u16 entryClass;

		DNS_QuestionEntry(const std::string& qName, u16 qType, u16 qClass);
		DNS_QuestionEntry(const u8* buffer, int* offset);

		virtual int GetLength() const;
		virtual void WriteBytes(u8* buffer, int* offset) const;

		virtual ~DNS_QuestionEntry(){};

	private:
		void ReadDNS_String(const u8* buffer, int* offset, std::string* value) const;
		void WriteDNS_String(u8* buffer, int* offset, const std::string& value) const;
	};

	class DNS_ResponseEntry : public DNS_QuestionEntry
	{
	public:
		u32 timeToLive;
		std::vector<u8> data;

		DNS_ResponseEntry(const std::string& rName, u16 rType, u16 rClass, const std::vector<u8>& rData, u32 rTTL);
		DNS_ResponseEntry(const u8* buffer, int* offset);

		virtual int GetLength() const;
		virtual void WriteBytes(u8* buffer, int* offset) const;

		virtual ~DNS_ResponseEntry(){};
	};
} // namespace PacketReader::IP::UDP::DNS