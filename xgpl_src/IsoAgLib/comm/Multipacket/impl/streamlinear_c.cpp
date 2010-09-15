/***************************************************************************
                          streamlinear_c.cpp -
                             -------------------
    class                : ::StreamLinear_c
    project              : IsoAgLib
    begin                : Tue Jan 25 17:39:57 2005
    copyright            : (C) 2005 by Achim Spangler (a.spangler@osb-ag.de)
    email                : a.spangler@osb-ag:de
    $Id: streamlinear_c.cpp 1089 2005-05-04 17:39:28Z wodok $

    $Log$
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 * This file is part of the "IsoAgLib", an object oriented program library *
 * to serve as a software layer between application specific program and   *
 * communication protocol details. By providing simple function calls for  *
 * jobs like starting a measuring program for a process data value on a    *
 * remote ECU, the main program has not to deal with single CAN telegram   *
 * formatting. This way communication problems between ECU's which use     *
 * this library should be prevented.                                       *
 * Everybody and every company is invited to use this library to make a    *
 * working plug and play standard out of the printed protocol standard.    *
 *                                                                         *
 * Copyright (C) 2000 - 2004 Dipl.-Inform. Achim Spangler                  *
 *                                                                         *
 * The IsoAgLib is free software; you can redistribute it and/or modify it *
 * under the terms of the GNU General Public License as published          *
 * by the Free Software Foundation; either version 2 of the License, or    *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This library is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU       *
 * General Public License for more details.                                *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with IsoAgLib; if not, write to the Free Software Foundation,     *
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA           *
 *                                                                         *
 * As a special exception, if other files instantiate templates or use     *
 * macros or inline functions from this file, or you compile this file and *
 * link it with other works to produce a work based on this file, this file*
 * does not by itself cause the resulting work to be covered by the GNU    *
 * General Public License. However the source code for this file must still*
 * be made available in accordance with section (3) of the                 *
 * GNU General Public License.                                             *
 *                                                                         *
 * This exception does not invalidate any other reasons why a work based on*
 * this file might be covered by the GNU General Public License.           *
 *                                                                         *
 * Alternative licenses for IsoAgLib may be arranged by contacting         *
 * the main author Achim Spangler by a.spangler@osb-ag:de                  *
 ***************************************************************************/

 /**************************************************************************
 *                                                                         *
 *     ###    !!!    ---    ===    IMPORTANT    ===    ---    !!!    ###   *
 * Each software module, which accesses directly elements of this file,    *
 * is considered to be an extension of IsoAgLib and is thus covered by the *
 * GPL license. Applications must use only the interface definition out-   *
 * side :impl: subdirectories. Never access direct elements of __IsoAgLib  *
 * and __HAL namespaces from applications which shouldnt be affected by    *
 * the license. Only access their interface counterparts in the IsoAgLib   *
 * and HAL namespaces. Contact a.spangler@osb-ag:de in case your applicat- *
 * ion really needs access to a part of an internal namespace, so that the *
 * interface might be extended if your request is accepted.                *
 *                                                                         *
 * Definition of direct access:                                            *
 * - Instantiation of a variable with a datatype from internal namespace   *
 * - Call of a (member-) function                                          *
 * Allowed is:                                                             *
 * - Instatiation of a variable with a datatype from interface namespace,  *
 *   even if this is derived from a base class inside an internal namespace*
 * - Call of member functions which are defined in the interface class     *
 *   definition ( header )                                                 *
 *                                                                         *
 * Pairing of internal and interface classes:                              *
 * - Internal implementation in an :impl: subdirectory                     *
 * - Interface in the parent directory of the corresponding internal class *
 * - Interface class name IsoAgLib::iFoo_c maps to the internal class      *
 *   __IsoAgLib::Foo_c                                                     *
 *                                                                         *
 * AS A RULE: Use only classes with names beginning with small letter :i:  *
 ***************************************************************************/

#include "streamlinear_c.h"
#include "chunk_c.h"



// Begin Namespace __IsoAgLib
namespace __IsoAgLib {



StreamLinear_c::StreamLinear_c (StreamType_t rt_streamType, const IsoAgLib::ReceiveStreamIdentifier_c& rc_rsi, uint32_t rui32_msgSize)
  : Stream_c (rt_streamType, rc_rsi, rui32_msgSize)
  , ui32_parsedCnt (0)
{
  vui8_buffer.reserve (rui32_msgSize); // as reactOnStreamStart told we have enough memory!
};

StreamLinear_c::~StreamLinear_c()
{
}


#ifdef NMEA_2000_FAST_PACKET
// //////////////////////////////// +X2C Operation : insert6Bytes
//! Parameter:
//! @param pui8_data: pointer to 6 bytes of data!
void
StreamLinear_c::insertFirst6Bytes(const uint8_t* pui8_data)
{
  vui8_buffer.push_back (pui8_data[0]);
  vui8_buffer.push_back (pui8_data[1]);
  vui8_buffer.push_back (pui8_data[2]);
  vui8_buffer.push_back (pui8_data[3]);
  vui8_buffer.push_back (pui8_data[4]);
  vui8_buffer.push_back (pui8_data[5]);
}
#endif

// //////////////////////////////// +X2C Operation : insert7Bytes
//! Parameter:
//! @param pui8_data: pointer to 7 bytes of data!
void
StreamLinear_c::insert7Bytes(const uint8_t* pui8_data)
{ // ~X2C
  vui8_buffer.push_back (pui8_data[0]);
  vui8_buffer.push_back (pui8_data[1]);
  vui8_buffer.push_back (pui8_data[2]);
  vui8_buffer.push_back (pui8_data[3]);
  vui8_buffer.push_back (pui8_data[4]);
  vui8_buffer.push_back (pui8_data[5]);
  vui8_buffer.push_back (pui8_data[6]);
  // as ui32_recCnt is vui8_buffer.size(), it is automatically increased!
} // -X2C



} // end namespace __IsoAgLib
