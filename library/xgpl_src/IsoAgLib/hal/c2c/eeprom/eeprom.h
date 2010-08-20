/*
  eeprom.h: definition of HAL namesapce layer for C2C

  (C) Copyright 2009 - 2010 by OSB AG and developing partners

  See the repository-log for details on the authors and file-history.
  (Repository information can be found at <http://isoaglib.com/download>)

  Use, modification and distribution are subject to the GNU General
  Public License with exceptions for ISOAgLib. (See accompanying
  file LICENSE.txt or copy at <http://isoaglib.com/download/license>)
*/

/** \file IsoAgLib/hal/c2c/eeprom/eeprom.cpp
 * The header <i>\<target\>/\<device\>/\<device\>.h</i> performs a name
   mapping between platform specific BIOS / OS function names
   and the function names, the IsoAgLib uses for hardware access.
   In this header only the groups for error codes, global system
   functions and CAN must be adapted to a new platform.
   If a simple name mapping is not possible for a specific
   function, the module targetExtensions can be used to implement
   the needed activity. The implementation of the PC version
   can be used to derive the meaning of the specific function.
*/
/* ************************************************************ */

#include "../../hal_eeprom.h"

namespace __HAL {
  extern "C" {
    /** include the BIOS specific header into __HAL */
#include <commercial_BIOS/bios_c2c/c2c10osy.h>
  }
}

#ifndef __EEPROM_C2C_H__
#define __EEPROM_C2C_H__

/**
   namespace with layer of inline (cost NO overhead -> compiler replaces
   inline function with call to orig BIOS function)
   functions between all IsoAgLib calls for BIOS and the corresponding BIOS functions
   --> simply replace the call to the corresponding BIOS function in this header
       for adaptation to new platform
 */
namespace HAL {
  /* *************************** */
  /** \name EEPROM BIOS functions */
  /*@{*/

  /**
   deliver the EEPROM size in uint8_t -> mult C2C BIOS value with 1024
   @return EEPROM size in byte
  */
  inline int16_t getEepromSize( void ) {
    return ( 1024 * __HAL::get_eeprom_size() );
  };

  /**
   deliver the EEPROM segment size in kbyte
   @return EEPROM segment size in kbyte
  */
  // MSCHMIDT - I think this is actually supposed to say size in bytes instead
  // MSCHMIDT - of size in kbyte.  get_eeprom_segment_size() returns size in
  // MSCHMIDT - bytes.
  inline int16_t getEepromSegmentSize( void ) {
    return __HAL::get_eeprom_segment_size();
  };

  /**
    read amount of uint8_t in uint8_t string variable
    @param wAddress start adress to read
    @param wNumber amount of bytes to read
    @param pbByte pointer to uint8_t string, where data is inserted
    @return error state (C_NO_ERR == o.k.)
  */
  inline int16_t eepromRead( uint16_t wAddress,uint16_t wNumber,uint8_t *pbByte ) {
    return __HAL::eeprom_read( wAddress, wNumber, pbByte );
  };

  /**
    write amount of uint8_t from string into EEPROM from given start adress
    @param wAddress adress of first written uint8_t in EEPROM
    @param wNumber amount of written data
    @param pbData pointer to uint8_t string which should be written into EEPROM
    @return error state (C_NO_ERR == o.k.)
  */
  inline int16_t eepromWrite( uint16_t wAddress,uint16_t wNumber,const uint8_t *pbData ) {
    return __HAL::eeprom_write( wAddress, wNumber, const_cast<uint8_t *>( pbData ) );
  };

  /**
    set or unset set write protection of EEPROM, should be called before
    every write access
    @param bitMode sets write protection OFF or ON
    @return error state (C_NO_ERR == o.k.)
  */
  inline int16_t eepromWp( bool bitMode ) {
    return HAL_NO_ERR;
  };

  /**
    check if EEPROM is ready for actions
    @return EE_READY -> ready
  */
  inline int16_t eepromReady( void ) {
    return EE_READY;
  };
// MSCHMIDT - Should really implement a target extension for the c2c in eeprom_target_extensions.cc
// MSCHMIDT - (see C:\DEV\IsoAgLib\lgpl_src\IsoAgLib\hal\pc\eeprom\eeprom_target_extensions.cc)
// MSCHMIDT - /* get the status of eeprom*/
// MSCHMIDT - int16_t eepromReady(void){
// MSCHMIDT -   // printf("eeprom ready aufgerufen\n");
// MSCHMIDT -   return EE_READY;
// MSCHMIDT - }


  /*@}*/

#ifdef USE_CAN_EEPROM_EDITOR
  /* ********************************* */
  /** \name CAN EEPROM Editor functions */
  /*@{*/

  /**
    initialize the CAN EEPROM editor module
    @param bBus CAN BUS number to use for EEEditor
    @param iObjNrReceiveCan CAN Msg Obj number for receive of Editor msg
    @param iObjNrTransmitCan CAN Msg Obj number for send of Editor msg
    @param dwReceiveCanId CAN Ident_c to use for receive of Editor msg
    @param bUseExtendedCAN set to 0 for standard 11bit, to 1 for extended 29bit Ident
    @param iNumberMsgsReceive size of CAN receive buffer size
    @param iNumberMsgsTransmit size of CAN send buffer size
    @return HAL_NO_ERR if no error occured
  */
  inline int16_t InitEEEditor( uint8_t bBus,
                               int16_t iObjNrReceiveCan, int16_t iObjNrTransmitCan,
                               uint32_t dwReceiveCanId, uint8_t bUseExtendedCAN,
                               int16_t iNumberMsgsReceive, int16_t iNumberMsgsTransmit ) {
    return __HAL::iInitEEEditor( bBus, iObjNrReceiveCan, iObjNrTransmitCan,
                                 dwReceiveCanId, bUseExtendedCAN, iNumberMsgsReceive, iNumberMsgsTransmit );
  };

  /**
    periodic call to the CAN EEEditor, to process editor msg
    @return true -> EEPROM write msg recieved, and EEPROM values changed
  */
  inline int16_t ProcessCANEEEditorMsg() {
    return __HAL::iCallCanEEMonitor();
  };

  /*@}*/
#elif defined(USE_RS232_EEPROM_EDITOR)
  /* *********************************** */
  /** \name RS232 EEPROM Editor functions */
  /*@{*/

  /**
    periodic call to the RS232 EEEditor, to process editor msg
    @return true -> EEPROM write msg recieved, and EEPROM values changed
  */
  inline int16_t ProcessRS232EEEditorMsg() {
    return __HAL::iCallRs232EEMonitor();
  };
  /*@}*/
#endif

}

#endif //#define __EEPROM_C2C_H__
