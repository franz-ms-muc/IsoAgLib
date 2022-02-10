/*
  vtobjectinputboolean_c.h

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
#ifndef VTOBJECTINPUTBOOLEAN_C_H
#define VTOBJECTINPUTBOOLEAN_C_H

#include <IsoAgLib/isoaglib_config.h>


#ifdef CONFIG_USE_VTOBJECT_inputboolean

#include "vtobject_c.h"
#include "vtclient_c.h"


namespace __IsoAgLib {

class vtObjectInputBoolean_c : public vtObject_c
{
private:
	// Internal implementation class
	struct iVtObjectInputBoolean_s;

	// Pointer to the internal implementation
	std::unique_ptr<iVtObjectInputBoolean_s> vtObject_a;


public:
  int16_t stream(uint8_t* destMemory,
                 uint16_t maxBytes,
                 objRange_t sourceOffset);
  IsoAgLib::ObjectID getID() const;

  vtObjectInputBoolean_c(iVtObjectInputBoolean_s* vtObjectInputBooleanSROM , int ai_multitonInst);

  iVtObjectInputBoolean_s* get_vtObjectInputBoolean_a();



  uint32_t fitTerminal() const;

  void setValue(bool newValue, bool b_updateObject=false, bool b_enableReplaceOfCmd=true);
  // //////////////////////////////////
  // All special Attribute-Set methods
  void setBackgroundColour(IsoAgLib::Colour newValue, bool b_updateObject=false, bool b_enableReplaceOfCmd=false);
  void setWidth(uint16_t newValue, bool b_updateObject=false, bool b_enableReplaceOfCmd=false);
  void setForegroundColour(IsoAgLib::iVtObject_c* newValue, bool b_updateObject=false, bool b_enableReplaceOfCmd=false);
  void setVariableReference(IsoAgLib::iVtObject_c* newValue, bool b_updateObject=false, bool b_enableReplaceOfCmd=false);

#ifdef CONFIG_USE_ISO_TERMINAL_GETATTRIBUTES
  // ///////////////////////// getter for attributes
  /** that attribute is in parentheses in the spec, so commented out here
  uint8_t updateObjectType() const { return 7; }
  */

  uint8_t updateBackgroundColour(bool b_SendRequest=false);
  uint16_t updateWidth(bool b_SendRequest=false);
  uint16_t updateForegroundColour(bool b_SendRequest=false);
  uint16_t updateVariableReference(bool b_SendRequest=false);

  /** these attributes are in parentheses in the spec, so commented out here
  uint8_t updateValue(bool b_SendRequest=false);

  uint8_t updateEnabled(bool b_SendRequest=false);
  */

  void saveReceivedAttribute (uint8_t attrID, uint8_t* pui8_attributeValue);
#endif
private:
  void updateEnable(uint8_t aui8_enOrDis);
};

} // __IsoAgLib

#endif //CONFIG_USE_VTOBJECT_inputboolean
#endif //VTOBJECTINPUTBOOLEAN_C_H
