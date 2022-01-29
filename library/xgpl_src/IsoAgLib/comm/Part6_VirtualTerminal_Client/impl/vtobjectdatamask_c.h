/*
  vtobjectdatamask_c.h

  (C) Copyright 2009 - 2019 by OSB AG

  See the repository-log for details on the authors and file-history.
  (Repository information can be found at <http://isoaglib.com/download>)

  Usage under Commercial License:
  Licensees with a valid commercial license may use this file
  according to their commercial license agreement. (To obtain a
  commercial license contact OSB AG via <http://isoaglib.com/en/contact>)

  Usage under GNU General Public License with exceptions for ISOAgLib:
  Alternatively (if not holding a valid commercial license)
  use, modification and distribution are subject to the GNU General
  Public License with exceptions for ISOAgLib. (See accompanying
  file LICENSE.txt or copy at <http://isoaglib.com/download/license>)
*/
#ifndef VTOBJECTDATAMASK_C_H
#define VTOBJECTDATAMASK_C_H

#include "../ivtobjectmask_c.h"
#include "../ivtobjectsoftkeymask_c.h"
#include "vtclient_c.h"

namespace __IsoAgLib {

class vtObjectDataMask_c : public IsoAgLib::iVtObjectMask_c
{
public:
  virtual ~vtObjectDataMask_c() {}

  int16_t stream(uint8_t* destMemory,
                 uint16_t maxBytes,
                 objRange_t sourceOffset);



  iVtObjectDataMask_s* get_vtObjectDataMask_a();

  vtObjectDataMask_c();
  vtObjectDataMask_c(const iVtObjectDataMask_s* vtObjectDataMaskSROM , int ai_multitonInst);

  void Append(iVtObject_c* const vtObject, int16_t x, int16_t y);

  uint32_t fitTerminal() const;

  void setSoftKeyMask(IsoAgLib::iVtObjectSoftKeyMask_c* newSoftKeyMask, bool b_updateObject= false, bool b_enableReplaceOfCmd=false);

  // //////////////////////////////////
  // All special Attribute-Set methods
  void setBackgroundColour(uint8_t newValue,  bool b_updateObject=false, bool b_enableReplaceOfCmd=false) {
    saveValue8SetAttribute ((b_updateObject) ? MACRO_getStructOffset(get_vtObjectDataMask_a(), backgroundColour) : 0, sizeof(iVtObjectDataMask_s), 1 /* "Background Colour" */, newValue, __IsoAgLib::getVtClientInstance4Comm().getClientByID (s_properties.clientId).getUserConvertedColor (newValue, this, IsoAgLib::BackgroundColour), b_enableReplaceOfCmd);
  }

  bool moveChildLocation(IsoAgLib::iVtObject_c* apc_childObject, int8_t dx, int8_t dy, bool b_updateObject=false, bool b_enableReplaceOfCmd=false);

  bool setChildPosition(IsoAgLib::iVtObject_c* apc_childObject, int16_t dx, int16_t dy, bool b_updateObject=false, bool b_enableReplaceOfCmd=false);

  bool lockUnlockMask( bool b_lockMask, uint16_t ui16_lockTimeOut );

#ifdef USE_ISO_TERMINAL_GETATTRIBUTES
  /** that attribute is in parentheses in the spec, so commented out here
  uint8_t updateObjectType() const { return 1; }
  */
  uint8_t updateBackgroundColour(bool b_SendRequest=false);
  uint16_t updateSoftKeyMask(bool b_SendRequest=false);

  void saveReceivedAttribute (uint8_t attrID, uint8_t* pui8_attributeValue);
#endif
};

} // __IsoAgLib

#endif
