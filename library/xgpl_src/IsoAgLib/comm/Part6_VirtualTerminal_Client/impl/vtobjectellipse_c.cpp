/*
  vtobjectellipse_c.cpp

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

#include "vtobjectellipse_c.h"


#include "../ivtobjectlineattributes_c.h"
#include "../ivtobjectfillattributes_c.h"
#include "../ivtobjectbutton_c.h"
#include "../ivtobjectmacro_c.h"
#include "vtclient_c.h"


namespace __IsoAgLib {


struct vtObjectEllipse_c::iVtObjectEllipse_s : iVtObjectwMacro_s {
  IsoAgLib::iVtObjectLineAttributes_c* lineAttributes;
  uint16_t width;
  uint16_t height;
  uint8_t ellipseType;
  uint8_t startAngle;
  uint8_t endAngle;
  IsoAgLib::iVtObjectFillAttributes_c* fillAttributes;
  iVtObjectEllipse_s(
		IsoAgLib::ObjectID ID,
		IsoAgLib::iVtObjectLineAttributes_c *lineAttributes ,
		uint16_t width,
		uint16_t height,
		uint8_t ellipseType,
		uint8_t startAngle,
		uint8_t endAngle,
		IsoAgLib::iVtObjectFillAttributes_c *fillAttributes)
  : iVtObject_s(ID)
  , iVtObjectwMacro_s(ID)
  , lineAttributes(lineAttributes)
  , width(width)
  , height(height)
  , ellipseType(ellipseType)
  , startAngle(startAngle)
  , endAngle(endAngle)
  , fillAttributes(fillAttributes)
  {}
};




int16_t
vtObjectEllipse_c::stream(uint8_t* destMemory,
                          uint16_t maxBytes,
                          objRange_t sourceOffset)
{
    uint16_t curBytes=0; /* current bytes written */;
    MACRO_scaleLocalVars;
    MACRO_scaleSKLocalVars;

    uint32_t width  = (uint32_t)vtObject_a->width;
    uint32_t height = (uint32_t)vtObject_a->height;
    MACRO_scaleSizeI32(width, height);

    if (sourceOffset == 0) { // dump out constant sized stuff
      destMemory [0] = vtObject_a->ID & 0xFF;
      destMemory [1] = vtObject_a->ID >> 8;
      destMemory [2] = 15; // Object Type = Ellipse
      destMemory [3] = vtObject_a->lineAttributes->getID() & 0xFF;
      destMemory [4] = vtObject_a->lineAttributes->getID() >> 8;
      destMemory [5] = width & 0xFF;
      destMemory [6] = width >> 8;
      destMemory [7] = height & 0xFF;
      destMemory [8] = height >> 8;
      destMemory [9] = vtObject_a->ellipseType;
      destMemory [10] = vtObject_a->startAngle;
      destMemory [11] = vtObject_a->endAngle;

      if (vtObject_a->fillAttributes != NULL)
      {
        destMemory [12] = vtObject_a->fillAttributes->getID() & 0xFF;
        destMemory [13] = vtObject_a->fillAttributes->getID() >> 8;
      } else {
        destMemory [12] = 0xFF;
        destMemory [13] = 0xFF;
      }

      destMemory [14] = vtObject_a->numberOfMacrosToFollow;
      sourceOffset += 15;
      curBytes += 15;
    }

    MACRO_streamEventMacro(15);
    return curBytes;
}

IsoAgLib::ObjectID vtObjectEllipse_c::getID() const {
	isoaglib_assert(vtObject_a);
	return vtObject_a->ID;
}

uint32_t
vtObjectEllipse_c::fitTerminal() const
{
  return 15+vtObject_a->numberOfMacrosToFollow*2;
}


void
vtObjectEllipse_c::setOriginSKM(bool b_SKM)
{
  if (b_SKM) {
    s_properties.flags |= FLAG_ORIGIN_SKM;
    vtObject_a->lineAttributes->setOriginSKM (b_SKM);
  }
}

void
vtObjectEllipse_c::setSize(uint16_t newWidth, uint16_t newHeight, bool b_updateObject, bool b_enableReplaceOfCmd)
{
  if (b_updateObject) {
	  vtObject_a->width = newWidth;
	  vtObject_a->height = newHeight;
  }

  scaleSize( newWidth, newHeight );

  __IsoAgLib::getVtClientInstance4Comm().getClientByID (s_properties.clientId).commandHandler().sendCommandChangeSize(
    this, newWidth, newHeight, b_enableReplaceOfCmd );
}

#ifdef CONFIG_USE_ISO_TERMINAL_GETATTRIBUTES
uint16_t
vtObjectEllipse_c::updateLineAttributes(bool b_SendRequest)
{
  if (b_SendRequest)
    return getValue16GetAttribute(MACRO_getStructOffset(get_vtObjectEllipse_a(), lineAttributes), sizeof(iVtObjectEllipse_s), 1);
  else
    return getValue16(MACRO_getStructOffset(get_vtObjectEllipse_a(), lineAttributes), sizeof(iVtObjectEllipse_s));
}

uint16_t
vtObjectEllipse_c::updateWidth(bool b_SendRequest)
{
  if (b_SendRequest)
    return getValue16GetAttribute(MACRO_getStructOffset(get_vtObjectEllipse_a(), lineAttributes), sizeof(iVtObjectEllipse_s), 2);
  else
    return getValue16(MACRO_getStructOffset(get_vtObjectEllipse_a(), lineAttributes), sizeof(iVtObjectEllipse_s));
}

uint16_t
vtObjectEllipse_c::updateHeight(bool b_SendRequest)
{
  if (b_SendRequest)
    return getValue16GetAttribute(MACRO_getStructOffset(get_vtObjectEllipse_a(), height), sizeof(iVtObjectEllipse_s), 3);
  else
    return getValue16(MACRO_getStructOffset(get_vtObjectEllipse_a(), height), sizeof(iVtObjectEllipse_s));
}

uint8_t
vtObjectEllipse_c::updateEllipseType(bool b_SendRequest)
{
  if (b_SendRequest)
    return getValue8GetAttribute(MACRO_getStructOffset(get_vtObjectEllipse_a(), ellipseType), sizeof(iVtObjectEllipse_s), 4);
  else
    return getValue8(MACRO_getStructOffset(get_vtObjectEllipse_a(), ellipseType), sizeof(iVtObjectEllipse_s));
}

uint8_t
vtObjectEllipse_c::updateStartAngle(bool b_SendRequest)
{
  if (b_SendRequest)
    return getValue8GetAttribute(MACRO_getStructOffset(get_vtObjectEllipse_a(), startAngle), sizeof(iVtObjectEllipse_s), 5);
  else
    return getValue8(MACRO_getStructOffset(get_vtObjectEllipse_a(), startAngle), sizeof(iVtObjectEllipse_s));
}

uint8_t
vtObjectEllipse_c::updateEndAngle(bool b_SendRequest)
{
  if (b_SendRequest)
    return getValue8GetAttribute(MACRO_getStructOffset(get_vtObjectEllipse_a(), endAngle), sizeof(iVtObjectEllipse_s), 6);
  else
    return getValue8(MACRO_getStructOffset(get_vtObjectEllipse_a(), endAngle), sizeof(iVtObjectEllipse_s));
}

uint16_t
vtObjectEllipse_c::updateFillAttributes(bool b_SendRequest)
{
  if (b_SendRequest)
    return getValue16GetAttribute(MACRO_getStructOffset(get_vtObjectEllipse_a(), fillAttributes), sizeof(iVtObjectEllipse_s), 7);
  else
    return getValue16(MACRO_getStructOffset(get_vtObjectEllipse_a(), fillAttributes), sizeof(iVtObjectEllipse_s));
}


void
vtObjectEllipse_c::saveReceivedAttribute(uint8_t attrID, uint8_t* pui8_attributeValue)
{
  switch (attrID)
  {
    case 1: saveValue16(MACRO_getStructOffset(get_vtObjectEllipse_a(), lineAttributes), sizeof(iVtObjectEllipse_s), convertLittleEndianStringUi16(pui8_attributeValue)); break;
    case 2: saveValue16(MACRO_getStructOffset(get_vtObjectEllipse_a(), lineAttributes), sizeof(iVtObjectEllipse_s), convertLittleEndianStringUi16(pui8_attributeValue)); break;
    case 3: saveValue16(MACRO_getStructOffset(get_vtObjectEllipse_a(), height), sizeof(iVtObjectEllipse_s), convertLittleEndianStringUi16(pui8_attributeValue)); break;
    case 4: saveValue8(MACRO_getStructOffset(get_vtObjectEllipse_a(), ellipseType), sizeof(iVtObjectEllipse_s), convertLittleEndianStringUi8(pui8_attributeValue)); break;
    case 5: saveValue8(MACRO_getStructOffset(get_vtObjectEllipse_a(), startAngle), sizeof(iVtObjectEllipse_s), convertLittleEndianStringUi8(pui8_attributeValue)); break;
    case 6: saveValue8(MACRO_getStructOffset(get_vtObjectEllipse_a(), endAngle), sizeof(iVtObjectEllipse_s), convertLittleEndianStringUi8(pui8_attributeValue)); break;
    case 7: saveValue16(MACRO_getStructOffset(get_vtObjectEllipse_a(), fillAttributes), sizeof(iVtObjectEllipse_s), convertLittleEndianStringUi16(pui8_attributeValue)); break;
    default: break;
  }
}

#endif

	vtObjectEllipse_c::vtObjectEllipse_c(
			int ai_multitonInst,
			IsoAgLib::ObjectID ID,
			IsoAgLib::iVtObjectLineAttributes_c *lineAttributes,
			uint16_t width,
			uint16_t height,
			uint8_t ellipseType,
			uint8_t startAngle,
			uint8_t endAngle,
			IsoAgLib::iVtObjectFillAttributes_c *fillAttributes)
	:vtObjectEllipse_c(
			new iVtObjectEllipse_s(
					ID,
					lineAttributes,
					width,
					height,
					ellipseType,
					startAngle,
					endAngle,
					fillAttributes),
	ai_multitonInst)
{
}

    vtObjectEllipse_c::vtObjectEllipse_c(iVtObjectEllipse_s *vtObjectellipseSROM,
                                         int ai_multitonInst)
            : vtObject_c((iVtObject_s*) vtObjectellipseSROM , ai_multitonInst)
    		, vtObject_a(vtObjectellipseSROM)
    {}

	vtObjectEllipse_c::iVtObjectEllipse_s* vtObjectEllipse_c::get_vtObjectEllipse_a() {
		return vtObject_a;
	}

    void
    vtObjectEllipse_c::setLineAttributes(IsoAgLib::iVtObjectLineAttributes_c *newLineAttributes, bool b_updateObject,
                                         bool b_enableReplaceOfCmd) {
        saveValuePSetAttribute ((b_updateObject) ? MACRO_getStructOffset(get_vtObjectEllipse_a(), lineAttributes) : 0, sizeof(iVtObjectEllipse_s), 1 /* "Line Attributes" */, newLineAttributes, b_enableReplaceOfCmd);
    }

    void vtObjectEllipse_c::setWidth(uint16_t newWidth, bool b_updateObject, bool b_enableReplaceOfCmd) {
        saveValue16SetAttributeScaled ((b_updateObject) ? MACRO_getStructOffset(get_vtObjectEllipse_a(), width) : 0, sizeof(iVtObjectEllipse_s), 2 /* "Width" */, newWidth, b_enableReplaceOfCmd);
    }

    void vtObjectEllipse_c::setHeight(uint16_t newHeight, bool b_updateObject, bool b_enableReplaceOfCmd) {
        saveValue16SetAttributeScaled ((b_updateObject) ? MACRO_getStructOffset(get_vtObjectEllipse_a(), height) : 0, sizeof(iVtObjectEllipse_s), 3 /* "Height" */, newHeight, b_enableReplaceOfCmd);
    }

    void vtObjectEllipse_c::setEllipseType(uint8_t newEllipseType, bool b_updateObject, bool b_enableReplaceOfCmd) {
        saveValue8SetAttribute ((b_updateObject) ? MACRO_getStructOffset(get_vtObjectEllipse_a(), ellipseType) : 0, sizeof(iVtObjectEllipse_s), 4 /* "Ellipse Type" */, newEllipseType, newEllipseType, b_enableReplaceOfCmd);
    }

    void vtObjectEllipse_c::setStartAngle(uint8_t newStartAngle, bool b_updateObject, bool b_enableReplaceOfCmd) {
        saveValue8SetAttribute ((b_updateObject) ? MACRO_getStructOffset(get_vtObjectEllipse_a(), startAngle) : 0, sizeof(iVtObjectEllipse_s), 5 /* "Start Angle" */, newStartAngle, newStartAngle, b_enableReplaceOfCmd);
    }

    void vtObjectEllipse_c::setEndAngle(uint8_t newEndAngle, bool b_updateObject, bool b_enableReplaceOfCmd) {
        saveValue8SetAttribute ((b_updateObject) ? MACRO_getStructOffset(get_vtObjectEllipse_a(), endAngle) : 0, sizeof(iVtObjectEllipse_s), 6 /* "End Angle" */, newEndAngle, newEndAngle, b_enableReplaceOfCmd);
    }

    void
    vtObjectEllipse_c::setFillAttributes(IsoAgLib::iVtObjectFillAttributes_c *newFillAttributes, bool b_updateObject,
                                         bool b_enableReplaceOfCmd) {
        saveValuePSetAttribute ((b_updateObject) ? MACRO_getStructOffset(get_vtObjectEllipse_a(), fillAttributes) : 0, sizeof(iVtObjectEllipse_s), 7 /* "Fill Attributes" */, newFillAttributes, b_enableReplaceOfCmd);
    }



} // __IsoAgLib


