/*
  ivtobjectdatamask_c.h

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
#ifndef IVTOBJECTDATAMASK_C_H
#define IVTOBJECTDATAMASK_C_H

#include "impl/vtobjectdatamask_c.h"


namespace IsoAgLib {

class iVtObjectDataMask_c : public __IsoAgLib::vtObjectDataMask_c
{
public:
  static uint16_t objectType();

  iVtObjectDataMask_c(
		int ai_multitonInst,
		ObjectID ID = autoID,
  	    uint8_t backgroundColour = 0,
  	    iVtObjectSoftKeyMask_c* softKeyMask = nullptr);




  const iVtObjectDataMask_s& get_vtObjectDataMask_a();

  void setSoftKeyMask(iVtObjectSoftKeyMask_c* newSoftKeyMask, bool b_updateObject= false, bool b_enableReplaceOfCmd=false);

  void setBackgroundColour(uint8_t newValue, bool b_updateObject=false, bool b_enableReplaceOfCmd=false);

  bool moveChildLocation(iVtObject_c* apc_childObject, int8_t dx, int8_t dy, bool b_updateObject=false);

  bool setChildPosition(IsoAgLib::iVtObject_c* apc_childObject, int16_t dx, int16_t dy, bool b_updateObject=false, bool b_enableReplaceOfCmd=false);


#ifdef USE_ISO_TERMINAL_GETATTRIBUTES
  // ///////////////////////// getter for attributes
  /** that attribute is in parentheses in the spec, so commented out here
  uint8_t updateObjectType() const {
    return vtObjectDataMask_c::updateObjectType();
  }
  */

  uint8_t updateBackgroundColour(bool b_SendRequest=false) {
    return vtObjectDataMask_c::updateBackgroundColour(b_SendRequest);
  }

  uint16_t updateSoftKeyMask(bool b_SendRequest=false) {
    return vtObjectDataMask_c::updateSoftKeyMask(b_SendRequest);
  }
#endif

  virtual uint16_t getObjectType() const;
};

} // IsoAgLib

#endif
