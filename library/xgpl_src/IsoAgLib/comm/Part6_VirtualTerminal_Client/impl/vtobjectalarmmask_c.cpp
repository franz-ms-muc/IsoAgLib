/*
  vtobjectalarmmask_c.cpp

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

#include "vtobjectalarmmask_c.h"

#ifdef CONFIG_USE_VTOBJECT_alarmmask
#include "vtclient_c.h"
#include "../ivtobjectfontattributes_c.h"
#include "../ivtobjectmacro_c.h"


namespace __IsoAgLib {



enum vtObjectAlarmMask_c::AttributeID:uint8_t
{

	BackgroundColour = 1,
	SoftKeyMask      = 2,
	Priority         = 3,
	AcousticSignal   = 4,
};



struct vtObjectAlarmMask_c::iVtObjectAlarmMask_s : iVtObjectMask_s {
  IsoAgLib::Colour backgroundColour;
#ifdef CONFIG_USE_VTOBJECT_softkeymask
  IsoAgLib::iVtObjectSoftKeyMask_c* softKeyMask;
#endif
  uint8_t priority;
  uint8_t acousticSignal;
  explicit iVtObjectAlarmMask_s(
		    IsoAgLib::ObjectID ID
		  , IsoAgLib::Colour backgroundColour
#ifdef CONFIG_USE_VTOBJECT_softkeymask
		  , IsoAgLib::iVtObjectSoftKeyMask_c *softKeyMask
#endif
		  , uint8_t priority
          , uint8_t acousticSignal)
  : iVtObject_s(ID)
  , iVtObjectMask_s(ID)
  , backgroundColour(backgroundColour)
#ifdef CONFIG_USE_VTOBJECT_softkeymask
  , softKeyMask(softKeyMask)
#endif
  , priority(priority)
  , acousticSignal(acousticSignal)
  {}
};

int16_t
vtObjectAlarmMask_c::stream(uint8_t* destMemory,
                            uint16_t maxBytes,
                            objRange_t sourceOffset)
{
    uint16_t curBytes=0; /* current bytes written */;
    MACRO_scaleLocalVars;

    if (sourceOffset == 0) { // dump out constant sized stuff
      destMemory [0] = vtObject_a->ID & 0xFF;
      destMemory [1] = vtObject_a->ID >> 8;
      destMemory [2] = 2; // Object Type = Alarm Mask
      destMemory [3] = __IsoAgLib::getVtClientInstance4Comm().getClientByID (s_properties.clientId).getUserConvertedColor (vtObject_a->backgroundColour, this, IsoAgLib::BackgroundColour);
#ifdef CONFIG_USE_VTOBJECT_softkeymask
      if (vtObject_a->softKeyMask != NULL) {
          destMemory [4] = vtObject_a->softKeyMask->getID() & 0xFF;
          destMemory [5] = vtObject_a->softKeyMask->getID() >> 8;
      } else
#endif
      {
          destMemory [4] = 0xFF;
          destMemory [5] = 0xFF;
      }
      destMemory [6] = vtObject_a->priority;
      destMemory [7] = vtObject_a->acousticSignal;
      destMemory [8] = vtObject_a->numberOfObjectsToFollow;
      destMemory [9] = vtObject_a->numberOfMacrosToFollow;
      sourceOffset += 10;
      curBytes += 10;
    }

    MACRO_DAMstreamObjectXY(10);
    MACRO_streamEventMacro(10U+vtObject_a->numberOfObjectsToFollow*6U);
    return curBytes;
}



IsoAgLib::ObjectID vtObjectAlarmMask_c::getID() const {
	isoaglib_assert(vtObject_a);
	return vtObject_a->ID;
}


uint32_t
vtObjectAlarmMask_c::fitTerminal() const
{
	return 10 + vtObject_a->numberOfObjectsToFollow * 6	+ vtObject_a->numberOfMacrosToFollow * 2;
}

#ifdef CONFIG_USE_VTOBJECT_softkeymask
void
vtObjectAlarmMask_c::setSoftKeyMask(IsoAgLib::iVtObjectSoftKeyMask_c* newSoftKeyMask,
                                    bool b_updateObject, bool b_enableReplaceOfCmd)
{
  if (b_updateObject)
	  vtObject_a->softKeyMask = newSoftKeyMask;

  __IsoAgLib::getVtClientInstance4Comm().getClientByID (s_properties.clientId).commandHandler().sendCommandChangeSoftKeyMask(
    this, SoftKeyMask /* "Type: Alarm Mask" */, (newSoftKeyMask == NULL) ? 0xFFFF : newSoftKeyMask->getID(), b_enableReplaceOfCmd );
}
#endif


/// No cmdReplacing here, as it's a relative command!!
bool
vtObjectAlarmMask_c::moveChildLocation(IsoAgLib::iVtObject_c* apc_childObject, int8_t dx, int8_t dy, bool b_updateObject, bool b_enableReplaceOfCmd)
{
  return genericChangeChildLocation (apc_childObject, dx, dy, b_updateObject, vtObject_a->numberOfObjectsToFollow, vtObject_a->objectsToFollow);
}


bool
vtObjectAlarmMask_c::setChildPosition(IsoAgLib::iVtObject_c* apc_childObject, int16_t x, int16_t y, bool b_updateObject, bool b_enableReplaceOfCmd)
{
  return genericChangeChildPosition (apc_childObject, x, y, b_updateObject, vtObject_a->numberOfObjectsToFollow, vtObject_a->objectsToFollow, b_enableReplaceOfCmd, DataAlarmMaskOffset);
}

#ifdef CONFIG_USE_ISO_TERMINAL_GETATTRIBUTES
IsoAgLib::Colour
vtObjectAlarmMask_c::updateBackgroundColour (bool b_SendRequest)
{
  if (b_SendRequest)
    getAttribute(BackgroundColour);
  return vtObject_a->backgroundColour;
}

#ifdef CONFIG_USE_VTOBJECT_softkeymask
IsoAgLib::iVtObjectSoftKeyMask_c*
vtObjectAlarmMask_c::updateSoftKeyMask(bool b_SendRequest)
{
  if (b_SendRequest)
    getAttribute(SoftKeyMask);
  return vtObject_a->softKeyMask;
}
#endif

uint8_t
vtObjectAlarmMask_c::updatePriority (bool b_SendRequest)
{
  if (b_SendRequest)
    getAttribute(Priority);
  return vtObject_a->priority;
}

uint8_t
vtObjectAlarmMask_c::updateAcousticSignal(bool b_SendRequest)
{
  if (b_SendRequest)
    getAttribute(AcousticSignal);
  return vtObject_a->acousticSignal;
}

void
vtObjectAlarmMask_c::saveReceivedAttribute (uint8_t attrID, uint8_t* pui8_attributeValue)
{
  switch (attrID)
  {
    case BackgroundColour: vtObject_a->backgroundColour = convertLittleEndianStringColour(pui8_attributeValue); break;
    //case SoftKeyMask:      vtObject_a->softKeyMask      = convertLittleEndianStringUi16(pui8_attributeValue)); break; //TODO
    case Priority:         vtObject_a->priority         = convertLittleEndianStringUi8(pui8_attributeValue); break;
    case AcousticSignal:   vtObject_a->acousticSignal   = convertLittleEndianStringUi8(pui8_attributeValue); break;
    default: break;
  }
}
#endif



    void vtObjectAlarmMask_c::setBackgroundColour(IsoAgLib::Colour newValue, bool b_updateObject, bool b_enableReplaceOfCmd) {
    	if (b_updateObject)
    	    		vtObject_a->backgroundColour = newValue;
    	setAttribute ( BackgroundColour, __IsoAgLib::getVtClientInstance4Comm().getClientByID (s_properties.clientId).getUserConvertedColor (newValue, this, IsoAgLib::BackgroundColour), b_enableReplaceOfCmd);
    }

    void vtObjectAlarmMask_c::setPriority(uint8_t newValue, bool b_updateObject, bool b_enableReplaceOfCmd) {
    	if (b_updateObject)
    	    		vtObject_a->priority = newValue;
    	setAttribute ( Priority, newValue, b_enableReplaceOfCmd);
    }

    void vtObjectAlarmMask_c::setAcousticSignal(uint8_t newValue, bool b_updateObject, bool b_enableReplaceOfCmd) {
    	if (b_updateObject)
    	    		vtObject_a->acousticSignal = newValue;
    	setAttribute ( AcousticSignal, newValue, b_enableReplaceOfCmd);
    }



    vtObjectAlarmMask_c::vtObjectAlarmMask_c(
  		    int ai_multitonInst
  		  , IsoAgLib::ObjectID ID
  		  , IsoAgLib::Colour backgroundColour
#ifdef CONFIG_USE_VTOBJECT_softkeymask
  		  , IsoAgLib::iVtObjectSoftKeyMask_c *softKeyMask
#endif
  		  , uint8_t priority
  		  , uint8_t acousticSignal)
    :vtObjectAlarmMask_c(
    		new iVtObjectAlarmMask_s(
    		  		    ID
    		  		  , backgroundColour
#ifdef CONFIG_USE_VTOBJECT_softkeymask
    		  		  , softKeyMask
#endif
    		  		  , priority
    		  		  , acousticSignal
    				),
					ai_multitonInst
  		  )
    {

    }

    vtObjectAlarmMask_c::vtObjectAlarmMask_c(
    		vtObjectAlarmMask_c::iVtObjectAlarmMask_s *vtObjectAlarmMaskSROM,
            int ai_multitonInst)
            : iVtObjectMask_c((iVtObjectMask_s*) vtObjectAlarmMaskSROM, ai_multitonInst)
    		, vtObject_a(vtObjectAlarmMaskSROM)
    {}


    vtObjectAlarmMask_c::~vtObjectAlarmMask_c() = default;


} // end of namespace __IsoAgLib
#endif //CONFIG_USE_VTOBJECT_alarmmask
