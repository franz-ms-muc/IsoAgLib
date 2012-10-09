/***************************************************************************
                          streamchunk_c.cpp -
                             -------------------
    class                : ::StreamChunk_c
    project              : IsoAgLib
    begin                : Tue Jan 25 17:39:57 2005
    copyright            : (C) 2005 by Achim Spangler (a.spangler@osb-ag.de)
    email                : a.spangler@osb-ag:de
    $Id: streamchunk_c.cpp 1089 2005-05-04 17:39:28Z wodok $

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

#include "streamchunk_c.h"
#include "chunk_c.h"
#include "stdio.h"



// Begin Namespace __IsoAgLib
namespace __IsoAgLib {



//! Constructor: initializes the list and local variables
//! create one <list> element including one Chunk,
//! init pc_iterWriteChunk, pc_iterParsedChunk, ui32_writeCnt, ui32_parsedCnt
StreamChunk_c::StreamChunk_c (StreamType_t rt_streamType,
                              const IsoAgLib::ReceiveStreamIdentifier_c& rc_rsi,
                              uint32_t rui32_msgSize,
                              bool rb_skipCtsAwait)
    : Stream_c (rt_streamType, rc_rsi, rui32_msgSize, rb_skipCtsAwait)
{
  /// Do NOTHING more here
  /// User HAS TO call "immediateInitAfterConstruction" **immediately** AFTER Construction!
};


StreamChunk_c::~StreamChunk_c()
{
  list_chunks.clear();
}


void
StreamChunk_c::immediateInitAfterConstruction()
{
  list_chunks.push_back( Chunk_c() );
  pc_iterWriteChunk  = list_chunks.begin();
  pc_iterParsedChunk = list_chunks.begin();
  ui32_writeCnt  = 0;
  ui32_parsedCnt = 0;

  pc_iterWriteChunk->init();
}



StreamChunk_c::StreamChunk_c( const StreamChunk_c& rrefc_src )
  : Stream_c( rrefc_src ),
    list_chunks( rrefc_src.list_chunks ),
    ui32_writeCnt ( rrefc_src.ui32_writeCnt ),
    ui32_parsedCnt( rrefc_src.ui32_parsedCnt )
{
  copyIterator (rrefc_src.list_chunks, rrefc_src.pc_iterWriteChunk,  list_chunks, pc_iterWriteChunk);
  copyIterator (rrefc_src.list_chunks, rrefc_src.pc_iterParsedChunk, list_chunks, pc_iterParsedChunk);
}



const StreamChunk_c& StreamChunk_c::operator=( const StreamChunk_c& rrefc_src )
{
  Stream_c::operator=( rrefc_src );

  list_chunks = rrefc_src.list_chunks;
  copyIterator (rrefc_src.list_chunks, rrefc_src.pc_iterWriteChunk,  list_chunks, pc_iterWriteChunk);
  copyIterator (rrefc_src.list_chunks, rrefc_src.pc_iterParsedChunk, list_chunks, pc_iterParsedChunk);
  ui32_writeCnt  = rrefc_src.ui32_writeCnt;
  ui32_parsedCnt = rrefc_src.ui32_parsedCnt;
  return rrefc_src;
}


#ifdef NMEA_2000_FAST_PACKET
//! use this function only for the first 6 bytes. this exception is for fast-packet protocol's FirstFrame
//! *** ATTENTION *** THIS FUNCTION ASSUMES TO BE CALLED ON A FRESH STREAM, SO NO OVERFLOW CHECKS ARE DONE!
void
StreamChunk_c::insertFirst6Bytes(const uint8_t* pui8_data)
{
  // write bytes into current chunk, assuming it's the first one so NO checks for full chunk are performed!!!!
  int nbr = 0;
  while (nbr < 6)
    if (pc_iterWriteChunk->insert( pui8_data[nbr++] ))
      ui32_writeCnt++;
}
#endif


// //////////////////////////////// +X2C Operation 772 : insert
//! Insert 7 Bytes into one or two chunks
//! if the current chunk is full the next one is selcted respectively created
//! Parameter:
//! @param pui8_data: pointer to 7 bytes of data!
void
StreamChunk_c::insert7Bytes(const uint8_t* pui8_data)
{ // ~X2C
  uint16_t nbr;
  std::list<Chunk_c>::iterator pc_iterTmpChunk = pc_iterWriteChunk;

  // 1) write bytes into current writeChunk
  nbr = pc_iterWriteChunk->insert7Bytes( pui8_data );
  ui32_writeCnt += nbr;

  // 2) if current writeChunk is full then check if the next one is free
  //    if the next is free then 'increment' the writeChunk
  //    otherwise insert a new Chunk after the current writeChunk
  if (pc_iterWriteChunk->full())
  {
    pc_iterTmpChunk++;
    if (pc_iterTmpChunk == list_chunks.end())
      pc_iterTmpChunk = list_chunks.begin();

    if (pc_iterTmpChunk->free())
    {
      pc_iterWriteChunk = pc_iterTmpChunk;
    }
    else
    {
      pc_iterWriteChunk++;
      pc_iterWriteChunk = list_chunks.insert( pc_iterWriteChunk, Chunk_c() );
      pc_iterWriteChunk->init();
    }
  }

  // 3) write remaining bytes into the next writeChunk if necessary
  while (nbr < 7)
    if (pc_iterWriteChunk->insert( pui8_data[nbr++] ))
      ui32_writeCnt++;

} // -X2C



// //////////////////////////////// +X2C Operation 838 : getNotParsedSize
//! Checks the number of unparsed bytes
//! Parameter:
//! @return number of unparsed bytes
uint32_t
StreamChunk_c::getNotParsedSize()
{ // ~X2C
  // if the buffer is larger than our totalMsgSize, clip at totalMsgSize.
  // this occurs as we always insert 7 bytes, even if the last 7byte packet should NOT been taken completely
  if (ui32_byteTotalSize < ui32_writeCnt)
    return (ui32_byteTotalSize - ui32_parsedCnt);
  else
    return (ui32_writeCnt - ui32_parsedCnt);
} // -X2C



// //////////////////////////////// +X2C Operation 783 : getNextNotParsed
uint8_t
//! Returns the next byte to be parsed
//! if the parsed-counter reached the chunk-end then the next one is selcted
//! Parameter:
//! @return next byte to be parsed or 0xff (parse-counter equals write-counter)
StreamChunk_c::getNextNotParsed()
{ // ~X2C
  uint16_t chunkLen = sui8_pkgBurst * 7;
  uint16_t chunkCnt = ui32_parsedCnt % chunkLen;
  uint8_t  chunkVal;

  if (ui32_parsedCnt >= ui32_writeCnt) return 0xff;

  // 1) get Chunk-Value
  chunkVal = pc_iterParsedChunk->getData( chunkCnt++ );
  ui32_parsedCnt++;

  // 2) if current parsed-Chunk has been completely parsed
  //    then set free the current Chunk and 'increment' the parsed-Chunk
  if (chunkCnt >= chunkLen)
  {
    pc_iterParsedChunk->setFree();
    pc_iterParsedChunk++;;
    if (pc_iterParsedChunk == list_chunks.end())
      pc_iterParsedChunk = list_chunks.begin();
  }

  return chunkVal;
} // -X2C



// //////////////////////////////// +X2C Operation : getNotParsed
//! Returns a byte to be checked by the parser
//! The 'address' is specified by the current parsed-counter and the given offset
//! The parsed-counter is not modified
//! Parameter:
//! @param ui16_notParsedRelativeOffset: address-offset for the parsed-counter
//! @return byte to be parsed or 0xff (if the address is out of range)
uint8_t
StreamChunk_c::getNotParsed (uint16_t ui16_notParsedRelativeOffset)
{
  std::list<Chunk_c>::iterator pc_iterTmpChunk = pc_iterParsedChunk;
  uint16_t chunkLen = sui8_pkgBurst * 7;
  uint16_t chunkCnt = ui32_parsedCnt % chunkLen;
  uint16_t chunkCntReq = chunkCnt + ui16_notParsedRelativeOffset;

  if ((ui32_parsedCnt + ui16_notParsedRelativeOffset) >= ui32_writeCnt) return 0xff;

  if (chunkCntReq >= chunkLen)
  {
    do
    {
      chunkCntReq -= chunkLen;
      pc_iterTmpChunk++;
      if (pc_iterTmpChunk == list_chunks.end())
        pc_iterTmpChunk = list_chunks.begin();
    } while (chunkCntReq >= chunkLen);
  }

  return pc_iterTmpChunk->getData( chunkCntReq );
}



// //////////////////////////////// +X2C Operation 2878 : eof
//! Checks if the stream has been completely parsed
//! @return True: stream has been completely parsed
bool
StreamChunk_c::eof() const
{ // ~X2C
  if (ui32_parsedCnt >= ui32_byteTotalSize)
    return true;
  else
    return false;
} // -X2C



#if 0
// for reactivation put this into the header!
  void testDisplay();
  bool testInsert(uint8_t ui8_data);

void
StreamChunk_c::testDisplay()
{
  uint16_t nbr, idx, iter=1;
  std::list<Chunk_c>::iterator pc_iterTmpChunk;

  printf( "-------------\n" );
  printf( "Write-Cnt: %d \n", ui32_writeCnt );
  printf( "Parse-Cnt: %d \n", ui32_parsedCnt );
  for (pc_iterTmpChunk=list_chunks.begin(); pc_iterTmpChunk != list_chunks.end(); pc_iterTmpChunk++)
  {
    printf( "%c ", ((pc_iterTmpChunk==pc_iterWriteChunk)?'W':' '));
    printf( "%c ", ((pc_iterTmpChunk==pc_iterParsedChunk)?'P':' '));
    printf( "Chunk %0.2d (%0.2d elements): ", iter++,
             Stream_c::sui8_pkgBurst * 7 - pc_iterTmpChunk->getFreeCnt() );
    idx=0;
    while ((nbr=pc_iterTmpChunk->getData(idx++)) != 0xffff)
      printf( "%d, ", nbr );
    printf( "\n" );
  }
}

// //////////////////////////////// +X2C Operation 772 : insert
bool
StreamChunk_c::testInsert(uint8_t ui8_data)
{
    if (pc_iterWriteChunk->insert( ui8_data ))
      ui32_writeCnt++;
    return true;
}

#endif

} // end namespace __IsoAgLib
