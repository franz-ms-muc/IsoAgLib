/*
  vtobjectrectangle_c.h

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
#ifndef VTOBJECTRECTANGLE_C_H
#define VTOBJECTRECTANGLE_C_H

#include <IsoAgLib/isoaglib_config.h>


#ifdef CONFIG_USE_VTOBJECT_rectangle

#include "vtobject_c.h"


namespace __IsoAgLib {

class vtObjectRectangle_c : public vtObject_c
{
private:
	// Internal implementation class
	struct iVtObjectRectangle_s;

	// Pointer to the internal implementation
	iVtObjectRectangle_s* vtObject_a;
	//TODO
	//std::unique_ptr<iVtObjectRectangle_s> vtObject_a;

public:
  int16_t stream(uint8_t* destMemory,
                 uint16_t maxBytes,
                 objRange_t sourceOffset);
  IsoAgLib::ObjectID getID() const;

  vtObjectRectangle_c(iVtObjectRectangle_s* vtObjectRectangleSROM , int ai_multitonInst);
  iVtObjectRectangle_s* get_vtObjectRectangle_a();
  uint32_t fitTerminal() const;
  void setLineAttributes(IsoAgLib::iVtObjectLineAttributes_c* newLineAttributes, bool b_updateObject=false, bool b_enableReplaceOfCmd=false);
  void setWidth(uint16_t newWidth, bool b_updateObject=false, bool b_enableReplaceOfCmd=false);
  void setHeight(uint16_t newHeight, bool b_updateObject=false, bool b_enableReplaceOfCmd=false);
  void setLineSuppression(uint8_t newLineSupressionValue, bool b_updateObject=false, bool b_enableReplaceOfCmd=false);
  void setFillAttributes(IsoAgLib::iVtObjectFillAttributes_c* newFillAttributes, bool b_updateObject=false, bool b_enableReplaceOfCmd=false);
  void setOriginSKM(bool b_SKM);
  void setSize(uint16_t newWidth, uint16_t newHeight, bool b_updateObject=false, bool b_enableReplaceOfCmd=false);
#ifdef CONFIG_USE_ISO_TERMINAL_GETATTRIBUTES
  // ///////////////////////// getter for attributes
  /** that attribute is in parentheses in the spec, so commented out here
  uint8_t updateObjectType() const { return 14; }
  */
  uint16_t updateLineAttributes(bool b_SendRequest=false);
  uint16_t updateWidth(bool b_SendRequest=false);
  uint16_t updateHeight(bool b_SendRequest=false);
  uint8_t updateLineSuppression(bool b_SendRequest=false);
  uint16_t updateFillAttributes(bool b_SendRequest=false);
  void saveReceivedAttribute (uint8_t attrID, uint8_t* pui8_attributeValue);
#endif
};

} // __IsoAgLib

#endif // CONFIG_USE_VTOBJECT_rectangle

#endif // VTOBJECTRECTANGLE_C_H
