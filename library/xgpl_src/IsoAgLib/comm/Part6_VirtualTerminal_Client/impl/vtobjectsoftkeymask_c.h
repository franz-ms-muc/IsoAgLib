/*
  vtobjectsoftkeymask_c.h

  (C) Copyright 2009 - 2012 by OSB AG and developing partners

  See the repository-log for details on the authors and file-history.
  (Repository information can be found at <http://isoaglib.com/download>)

  Use, modification and distribution are subject to the GNU General
  Public License with exceptions for ISOAgLib. (See accompanying
  file LICENSE.txt or copy at <http://isoaglib.com/download/license>)
*/
#ifndef VTOBJECTSOFTKEYMASK_C_H
#define VTOBJECTSOFTKEYMASK_C_H

#include "vtobject_c.h"
#include "isoterminal_c.h"
#include "vtclientservercommunication_c.h"

// Begin Namespace __IsoAgLib
namespace __IsoAgLib {

class vtObjectSoftKeyMask_c : public vtObject_c
{
public:
  /// Operation: stream
  /// @param destMemory
  /// @param maxBytes don't stream out more than that or you'll overrun the internal upload-buffer
  /// @param sourceOffset
  int16_t stream(uint8_t* destMemory,
                 uint16_t maxBytes,
                 objRange_t sourceOffset);

  /// Operation: init
  /// @param vtObjectSoftKeyMaskSROM
  /// @param b_initPointer
  void init(const iVtObjectSoftKeyMask_s* vtObjectSoftKeyMaskSROM MULTITON_INST_PARAMETER_DEF_WITH_COMMA)
  { vtObject_c::init ((iVtObject_s*) vtObjectSoftKeyMaskSROM MULTITON_INST_PARAMETER_USE_WITH_COMMA); }

  //  Operation: get_vtObjectSoftKeyMask_a
  iVtObjectSoftKeyMask_s* get_vtObjectSoftKeyMask_a() { return (iVtObjectSoftKeyMask_s *)&(get_vtObject_a()); }

  //  Operation: vtObjectSoftKeyMask_c
  vtObjectSoftKeyMask_c();

  virtual ~vtObjectSoftKeyMask_c() {}

  //  Operation: size
  uint32_t fitTerminal() const;

  //  Operation: setOriginSKM
  //! @param b_SKM:
  void setOriginSKM(bool b_SKM);

  // //////////////////////////////////
  // All special Attribute-Set methods
  void setBackgroundColour(uint8_t newValue, bool b_updateObject=false, bool b_enableReplaceOfCmd=false) {
    saveValue8SetAttribute ((b_updateObject) ? MACRO_getStructOffset(get_vtObjectSoftKeyMask_a(), backgroundColour) : 0, sizeof(iVtObjectSoftKeyMask_s), 1, newValue, __IsoAgLib::getIsoTerminalInstance4Comm().getClientByID(s_properties.clientId).getUserClippedColor (newValue, this, IsoAgLib::BackgroundColour), b_enableReplaceOfCmd);
  }
#ifdef USE_ISO_TERMINAL_GETATTRIBUTES
  // ///////////////////////// getter for attributes
  /** that attribute is in parentheses in the spec, so commented out here
  uint8_t updateObjectType() const { return 4; }
  */

  uint8_t updateBackgroundColour(bool b_SendRequest=false);

  void saveReceivedAttribute (uint8_t attrID, uint8_t* pui8_attributeValue);
#endif
};

} // end of namespace __IsoAgLib

#endif
