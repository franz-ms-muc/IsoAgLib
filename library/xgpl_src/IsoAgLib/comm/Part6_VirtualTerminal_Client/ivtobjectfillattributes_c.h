/*
  ivtobjectfillattributes_c.h

  (C) Copyright 2009 - 2012 by OSB AG and developing partners

  See the repository-log for details on the authors and file-history.
  (Repository information can be found at <http://isoaglib.com/download>)

  Use, modification and distribution are subject to the GNU General
  Public License with exceptions for ISOAgLib. (See accompanying
  file LICENSE.txt or copy at <http://isoaglib.com/download/license>)
*/
#ifndef IVTOBJECTFILLATTRIBUTES_C_H
#define IVTOBJECTFILLATTRIBUTES_C_H


// +X2C includes
#include "impl/vtobjectfillattributes_c.h"
#include "ivtobjectpicturegraphic_c.h"
// ~X2C

// Begin Namespace IsoAgLib
namespace IsoAgLib {


//  +X2C Class 167 : iVtObjectFillAttributes_c
//!  Stereotype: Klasse
class iVtObjectFillAttributes_c : public __IsoAgLib::vtObjectFillAttributes_c
{

public:

  /// Operation: init
  ///
  /// @param vtObjectFillAttributesSROM
  /// @param b_initPointer
  void init(const iVtObjectFillAttributes_s* vtObjectFillAttributesSROM MULTITON_INST_PARAMETER_DEF_WITH_COMMA) {
    vtObjectFillAttributes_c::init (vtObjectFillAttributesSROM MULTITON_INST_PARAMETER_USE_WITH_COMMA);
  }

  //  Operation: get_vtObjectFillAttributes_a
  const iVtObjectFillAttributes_s& get_vtObjectFillAttributes_a() { return *vtObjectFillAttributes_c::get_vtObjectFillAttributes_a(); }


  /// Operation: setFillType
  ///
  /// @param newFillType
  /// @param b_updateObject
  void setFillType(uint8_t newFillType, bool b_updateObject=false, bool b_enableReplaceOfCmd=false) {
    vtObjectFillAttributes_c::setFillType(newFillType, b_updateObject, b_enableReplaceOfCmd);
  }

  /// Operation: setFillColour
  ///
  /// @param newFillColour
  /// @param b_updateObject
  void setFillColour(uint8_t newFillColour, bool b_updateObject=false, bool b_enableReplaceOfCmd=false) {
    vtObjectFillAttributes_c::setFillColour(newFillColour, b_updateObject, b_enableReplaceOfCmd);
  }

  /// Operation: setFillPattern
  /// 
  /// @param newFillPatternObject
  /// @param b_updateObject
  void setFillPattern(iVtObjectPictureGraphic_c* newFillPatternObject, bool b_updateObject=false, bool b_enableReplaceOfCmd=false) {
    vtObjectFillAttributes_c::setFillPattern(newFillPatternObject, b_updateObject, b_enableReplaceOfCmd);
  }

  /// Operation: changeFillAttributes
  ///
  /// @param newFillType
  /// @param newFillColour
  /// @param newFillPattern
  /// @param b_updateObject
  void setFillAttributes(uint8_t newFillType, uint8_t newFillColour, iVtObjectPictureGraphic_c* newFillPattern, bool b_updateObject=false, bool b_enableReplaceOfCmd=false) {
    vtObjectFillAttributes_c::setFillAttributes(newFillType, newFillColour, newFillPattern, b_updateObject, b_enableReplaceOfCmd);
  }
#ifdef USE_ISO_TERMINAL_GETATTRIBUTES
  /** that attribute is in parentheses in the spec, so commented out here
  uint8_t updateObjectType() const { return vtObjectFillAttributes_c::updateObjectType(); }
  */

  uint8_t updateFillType(bool b_SendRequest=false) {
    return vtObjectFillAttributes_c::updateFillType(b_SendRequest);
  }

  uint8_t updateFillColour(bool b_SendRequest=false) {
    return vtObjectFillAttributes_c::updateFillColour(b_SendRequest);
  }

  uint16_t updateFillPattern(bool b_SendRequest=false) {
    return vtObjectFillAttributes_c::updateFillPattern(b_SendRequest);
  }
#endif
};

} // end namespace IsoAgLib

#endif
