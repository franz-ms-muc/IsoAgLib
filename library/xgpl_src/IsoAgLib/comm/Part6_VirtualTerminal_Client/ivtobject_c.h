/*
  ivtobject_c.h

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
#ifndef IVTOBJECT_C_H
#define IVTOBJECT_C_H

#include <stdint.h>
#include "ivttypes.h"
#include "iColour.h"
#include "iObjectID.h"
#include <IsoAgLib/isoaglib_config.h>
#include <IsoAgLib/util/impl/multiton.h>
#include <IsoAgLib/util/iassert.h>

const uint8_t OO_CAPACITY = 100;

namespace IsoAgLib {



class iVtObject_c : public ClientBase
{
public:

  struct iVtObject_s {
	ObjectID ID;
    static ObjectID nextID;
    explicit iVtObject_s(ObjectID ID = autoID){
        this->ID = ID == autoID ? nextID : ID;
        nextID = (ObjectID)((uint16_t)nextID + 1);
    }
    virtual ~iVtObject_s() = default;
  };

  // the "virtual" here is really important, avoid https://en.wikipedia.org/wiki/Multiple_inheritance#The_diamond_problem
  /** iVtObjectwMacro_s is a Object than contain Macros.
    */
  struct iVtObjectLanguages_s : virtual iVtObject_s {
	  uint8_t numberOfLanguagesToFollow_size;
	  uint8_t numberOfLanguagesToFollow;
	  const IsoAgLib::repeat_vtLanguage_s* languagesToFollow;
  explicit iVtObjectLanguages_s(
		ObjectID ID = autoID,
		uint8_t size = OO_CAPACITY);
  };

protected:

  // the "virtual" here is really important, avoid https://en.wikipedia.org/wiki/Multiple_inheritance#The_diamond_problem
  /** iVtObjectObject_s is a Object than contain other Objects.
    */
  struct iVtObjectObject_s : virtual iVtObject_s {
	uint8_t numberOfObjectsToFollow_size;
    uint8_t numberOfObjectsToFollow;
    repeat_iVtObject_x_y_iVtObjectFontAttributes_row_col_s* objectsToFollow;
    void Append(iVtObject_c* const vtObject, int16_t x, int16_t y);
    explicit iVtObjectObject_s(
    		ObjectID ID = autoID,
			uint8_t size = OO_CAPACITY);
  };

  // the "virtual" here is really important, avoid https://en.wikipedia.org/wiki/Multiple_inheritance#The_diamond_problem
  /** iVtObjectwMacro_s is a Object than contain Macros.
    */
  struct iVtObjectwMacro_s : virtual iVtObject_s {
		uint8_t numberOfMacrosToFollow_size;
	    uint8_t numberOfMacrosToFollow;
	    const repeat_event_iVtObjectMacro_s* macrosToFollow;
    explicit iVtObjectwMacro_s(
		ObjectID ID = autoID,
		uint8_t size = OO_CAPACITY);
  };




  struct iVtObjectString_s : virtual iVtObject_s {
	  explicit iVtObjectString_s(
		ObjectID ID = autoID)
	  :iVtObject_s(ID)
	  {}
  };



  struct iVtObjectMask_s : iVtObjectObject_s, iVtObjectwMacro_s {
	  explicit iVtObjectMask_s(
		ObjectID ID = autoID)
	  :iVtObjectObject_s(ID)
	  ,iVtObjectwMacro_s(ID)
	  {}
  };

protected:
  struct iVtObjectAlarmMask_s : iVtObjectMask_s {
    Colour backgroundColour;
    iVtObjectSoftKeyMask_c* softKeyMask;
    uint8_t priority;
    uint8_t acousticSignal;
    explicit iVtObjectAlarmMask_s(
    		ObjectID ID = autoID,
    		Colour backgroundColour = BLACK,
			iVtObjectSoftKeyMask_c *softKeyMask = nullptr,
			uint8_t priority = 0,
            uint8_t acousticSignal = 0)
    : iVtObjectMask_s(ID)
    , backgroundColour(backgroundColour)
    , softKeyMask(softKeyMask)
    , priority(priority)
    , acousticSignal(acousticSignal)
    {}
  };









  struct iVtObjectContainer_s : iVtObjectObject_s, iVtObjectwMacro_s {
    uint16_t width;
    uint16_t height;
    uint8_t hidden;
    iVtObjectContainer_s(
    		ObjectID ID = autoID,
    		uint16_t width = 100,
			uint16_t height = 100,
			uint8_t hidden = 0)
    : iVtObjectObject_s(ID)
    , iVtObjectwMacro_s(ID)
    , width(width)
    , height(height)
    , hidden(hidden)
    {}
  };





  struct iVtObjectFillAttributes_s : iVtObjectwMacro_s {
    uint8_t fillType;
    Colour fillColour;
    iVtObjectPictureGraphic_c* fillPatternObject;
    iVtObjectFillAttributes_s(
    		ObjectID ID = autoID,
    		uint8_t fillType = 0,
			Colour fillColour = BLACK,
			iVtObjectPictureGraphic_c *fillPatternObject = nullptr)
    : iVtObjectwMacro_s(ID)
    , fillType(fillType)
    , fillColour(fillColour)
    , fillPatternObject(fillPatternObject)
    {}
  };



  struct iVtObjectInputAttributes_s : iVtObjectwMacro_s {
    uint8_t validationType;
    uint8_t length;
    char* validationString;
    iVtObjectInputAttributes_s(
    		ObjectID ID = autoID,
    		uint8_t validationType = 0,
			uint8_t length = 0,
			char *validationString = nullptr)
    : iVtObjectwMacro_s(ID)
    , validationType(validationType)
    , length(length)
    , validationString(validationString)
    {}
  };

  struct iVtObjectInputBoolean_s : iVtObjectwMacro_s {
    Colour backgroundColour;
    uint16_t width;
    iVtObject_c* foregroundColour;
    iVtObject_c* variableReference;
    uint8_t value;
    uint8_t enabled;
    iVtObjectInputBoolean_s(
    		ObjectID ID = autoID,
    		Colour backgroundColour = WHITE,
			uint16_t width = 20,
			iVtObject_c *foregroundColour = nullptr,
			iVtObject_c *variableReference = nullptr,
			uint8_t value = 0,
			uint8_t enabled = 1)
    : iVtObjectwMacro_s(ID)
    , backgroundColour(backgroundColour)
    , width(width)
    , foregroundColour(foregroundColour)
    , variableReference(variableReference)
    , value(value)
    , enabled(enabled)
    {}
  };

  struct iVtObjectInputList_s : iVtObjectObject_s, iVtObjectwMacro_s {
    uint16_t width;
    uint16_t height;
    iVtObject_c* variableReference;
    uint8_t value;
    uint8_t options;
    iVtObjectInputList_s(
    		ObjectID ID = autoID,
    		uint16_t width = 150,
			uint16_t height = 30,
			iVtObject_c *variableReference = nullptr,
			uint8_t value = 0,
			uint8_t options = 0)
    : width(width)
    , height(height)
    , variableReference(variableReference)
    , value(value)
    , options(options)
    {}
  };

  struct iVtObjectInputNumber_s : iVtObjectwMacro_s {
      iVtObjectInputNumber_s(uint16_t width, uint16_t height, Colour backgroundColour, iVtObject_c *fontAttributes,
                             uint8_t options, iVtObject_c *variableReference, uint32_t value, uint32_t minValue,
                             uint32_t maxValue, int32_t offset, float scale, uint8_t numberOfDecimals, uint8_t format,
                             uint8_t horizontalJustification, uint8_t secondOptionsByte) : width(width), height(height),
                                                                                           backgroundColour(
                                                                                                   backgroundColour),
                                                                                           fontAttributes(
                                                                                                   fontAttributes),
                                                                                           options(options),
                                                                                           variableReference(
                                                                                                   variableReference),
                                                                                           value(value),
                                                                                           minValue(minValue),
                                                                                           maxValue(maxValue),
                                                                                           offset(offset), scale(scale),
                                                                                           numberOfDecimals(
                                                                                                   numberOfDecimals),
                                                                                           format(format),
                                                                                           horizontalJustification(
                                                                                                   horizontalJustification),
                                                                                           secondOptionsByte(
                                                                                                   secondOptionsByte) {}

      uint16_t width;
    uint16_t height;
    Colour backgroundColour;
    iVtObject_c* fontAttributes;
    uint8_t options;
    iVtObject_c* variableReference;
    uint32_t value;
    uint32_t minValue;
    uint32_t maxValue;
    int32_t offset;
    float scale;
    uint8_t numberOfDecimals;
    uint8_t format;
    uint8_t horizontalJustification;
    uint8_t secondOptionsByte;
  };




  struct iVtObjectInputString_s : iVtObjectString_s, iVtObjectwMacro_s {
      iVtObjectInputString_s(uint16_t width, uint16_t height, Colour backgroundColour,
                             iVtObjectFontAttributes_c *fontAttributes, iVtObjectInputAttributes_c *inputAttributes,
                             uint8_t options, iVtObjectStringVariable_c *variableReference,
                             uint8_t horizontalJustification, uint16_t length, char *value, uint8_t enabled) : width(
              width), height(height), backgroundColour(backgroundColour), fontAttributes(fontAttributes),
                                                                                                               inputAttributes(
                                                                                                                       inputAttributes),
                                                                                                               options(options),
                                                                                                               variableReference(
                                                                                                                       variableReference),
                                                                                                               horizontalJustification(
                                                                                                                       horizontalJustification),
                                                                                                               length(length),
                                                                                                               value(value),
                                                                                                               enabled(enabled) {}

      uint16_t width;
    uint16_t height;
    Colour backgroundColour;
    iVtObjectFontAttributes_c* fontAttributes;
    iVtObjectInputAttributes_c* inputAttributes;
    uint8_t options;
    iVtObjectStringVariable_c* variableReference;
    uint8_t horizontalJustification;
    uint16_t length;
    char* value;
    uint8_t enabled;
  };

  struct iVtObjectKey_s : iVtObjectObject_s, iVtObjectwMacro_s {
      iVtObjectKey_s(Colour backgroundColour, uint8_t keyCode) : backgroundColour(backgroundColour),
                                                                  keyCode(keyCode) {}

      Colour backgroundColour;
    uint8_t keyCode;
  };






  struct iVtObjectMacro_s : iVtObject_s {
      iVtObjectMacro_s(uint16_t numBytesToFollow, const uint8_t *commandsToFollow) : numBytesToFollow(numBytesToFollow),
                                                                                     commandsToFollow(
                                                                                             commandsToFollow) {}

      uint16_t numBytesToFollow;
    const uint8_t* commandsToFollow;
  };

  struct iVtObjectMeter_s : iVtObjectwMacro_s {
      iVtObjectMeter_s(uint16_t width, Colour needleColour, Colour borderColour, Colour arcAndTickColour,
                       uint8_t options, uint8_t numberOfTicks, uint8_t startAngle, uint8_t endAngle, uint16_t minValue,
                       uint16_t maxValue, iVtObject_c *variableReference, uint16_t value) : width(width),
                                                                                            needleColour(needleColour),
                                                                                            borderColour(borderColour),
                                                                                            arcAndTickColour(
                                                                                                    arcAndTickColour),
                                                                                            options(options),
                                                                                            numberOfTicks(
                                                                                                    numberOfTicks),
                                                                                            startAngle(startAngle),
                                                                                            endAngle(endAngle),
                                                                                            minValue(minValue),
                                                                                            maxValue(maxValue),
                                                                                            variableReference(
                                                                                                    variableReference),
                                                                                            value(value) {}

      uint16_t width;
    Colour needleColour;
    Colour borderColour;
    Colour arcAndTickColour;
    uint8_t options;
    uint8_t numberOfTicks;
    uint8_t startAngle;
    uint8_t endAngle;
    uint16_t minValue;
    uint16_t maxValue;
    iVtObject_c* variableReference;
    uint16_t value;
  };

  struct iVtObjectNumberVariable_s : iVtObject_s {
      iVtObjectNumberVariable_s(uint32_t value) : value(value) {}

      uint32_t value;
  };

  struct iVtObjectObjectPointer_s : iVtObject_s {
      iVtObjectObjectPointer_s(iVtObject_c *value) : value(value) {}

      iVtObject_c* value;
  };

  struct iVtObjectOutputList_s : iVtObjectObject_s, iVtObjectwMacro_s  {
      iVtObjectOutputList_s(uint16_t width, uint16_t height, iVtObject_c *variableReference, uint8_t value) : width(
              width), height(height), variableReference(variableReference), value(value) {}

      uint16_t width;
    uint16_t height;
    iVtObject_c* variableReference;
    uint8_t value;
  };

  struct iVtObjectOutputNumber_s : iVtObjectwMacro_s {
      iVtObjectOutputNumber_s(uint16_t width, uint16_t height, Colour backgroundColour,
                              iVtObjectFontAttributes_c *fontAttributes, uint8_t options,
                              iVtObject_c *variableReference, uint32_t value, int32_t offset, float scale,
                              uint8_t numberOfDecimals, uint8_t format, uint8_t horizontalJustification) : width(width),
                                                                                                           height(height),
                                                                                                           backgroundColour(
                                                                                                                   backgroundColour),
                                                                                                           fontAttributes(
                                                                                                                   fontAttributes),
                                                                                                           options(options),
                                                                                                           variableReference(
                                                                                                                   variableReference),
                                                                                                           value(value),
                                                                                                           offset(offset),
                                                                                                           scale(scale),
                                                                                                           numberOfDecimals(
                                                                                                                   numberOfDecimals),
                                                                                                           format(format),
                                                                                                           horizontalJustification(
                                                                                                                   horizontalJustification) {}

      uint16_t width;
    uint16_t height;
    Colour backgroundColour;
    iVtObjectFontAttributes_c* fontAttributes;
    uint8_t options;
    iVtObject_c* variableReference;
    uint32_t value;
    int32_t offset;
    float scale;
    uint8_t numberOfDecimals;
    uint8_t format;
    uint8_t horizontalJustification;
  };




  struct iVtObjectPictureGraphic_s : iVtObjectwMacro_s {
      iVtObjectPictureGraphic_s(uint16_t width, uint16_t actualWidth, uint16_t actualHeight, uint8_t format,
                                uint8_t options, Colour transparencyColour, uint32_t numberOfBytesInRawData0,
                                const uint8_t *rawData0, uint32_t numberOfBytesInRawData1, const uint8_t *rawData1,
                                uint32_t numberOfBytesInRawData2, const uint8_t *rawData2,
                                uint8_t numberOfFixedBitmapsToFollow,
                                const repeat_rawData_rawBytes_actWidth_actHeight_formatoptions_s *fixedBitmapsToFollow)
              : width(width), actualWidth(actualWidth), actualHeight(actualHeight), format(format), options(options),
                transparencyColour(transparencyColour), numberOfBytesInRawData0(numberOfBytesInRawData0),
                rawData0(rawData0), numberOfBytesInRawData1(numberOfBytesInRawData1), rawData1(rawData1),
                numberOfBytesInRawData2(numberOfBytesInRawData2), rawData2(rawData2),
                numberOfFixedBitmapsToFollow(numberOfFixedBitmapsToFollow),
                fixedBitmapsToFollow(fixedBitmapsToFollow) {}

      uint16_t width;
    uint16_t actualWidth;
    uint16_t actualHeight;
    uint8_t format;
    uint8_t options;
    Colour transparencyColour;
    uint32_t numberOfBytesInRawData0;
    const uint8_t* rawData0;
    uint32_t numberOfBytesInRawData1;
    const uint8_t* rawData1;
    uint32_t numberOfBytesInRawData2;
    const uint8_t* rawData2;
    uint8_t numberOfFixedBitmapsToFollow;
    const repeat_rawData_rawBytes_actWidth_actHeight_formatoptions_s* fixedBitmapsToFollow;
  };

  struct iVtObjectColourMap_s : iVtObject_s {
      iVtObjectColourMap_s(uint16_t numOfColourIdxToFollow, const uint8_t *colourMapArray) : numOfColourIdxToFollow(
              numOfColourIdxToFollow), colourMapArray(colourMapArray) {}

      uint16_t numOfColourIdxToFollow;
    const uint8_t* colourMapArray;
  };

  struct iVtObjectPolygon_s : iVtObjectwMacro_s {
      iVtObjectPolygon_s(uint16_t width, uint16_t height, iVtObjectLineAttributes_c *lineAttributes,
                         iVtObjectFillAttributes_c *fillAttributes, uint8_t polygonType, uint8_t numberOfPoints,
                         const repeat_x_y_s *pointsToFollow) : width(width), height(height),
                                                               lineAttributes(lineAttributes),
                                                               fillAttributes(fillAttributes), polygonType(polygonType),
                                                               numberOfPoints(numberOfPoints),
                                                               pointsToFollow(pointsToFollow) {}

      uint16_t width;
    uint16_t height;
    iVtObjectLineAttributes_c* lineAttributes;
    iVtObjectFillAttributes_c* fillAttributes;
    uint8_t polygonType;
    uint8_t numberOfPoints;
    const repeat_x_y_s* pointsToFollow;
  };

  struct iVtObjectRectangle_s : iVtObjectwMacro_s {
      iVtObjectRectangle_s(iVtObjectLineAttributes_c *lineAttributes, uint16_t width, uint16_t height,
                           uint8_t lineSuppression, iVtObjectFillAttributes_c *fillAttributes) : lineAttributes(
              lineAttributes), width(width), height(height), lineSuppression(lineSuppression), fillAttributes(
              fillAttributes) {}

      iVtObjectLineAttributes_c* lineAttributes;
    uint16_t width;
    uint16_t height;
    uint8_t lineSuppression;
    iVtObjectFillAttributes_c* fillAttributes;
  };

  struct iVtObjectSoftKeyMask_s : iVtObjectObject_s, iVtObjectwMacro_s  {
      iVtObjectSoftKeyMask_s(Colour backgroundColour) : backgroundColour(backgroundColour) {}

      Colour backgroundColour;
  };

  struct iVtObjectStringVariable_s : iVtObject_s {
      iVtObjectStringVariable_s(uint16_t length, char *value) : length(length), value(value) {}

      uint16_t length;
    char* value;
  };



  struct iVtObjectAuxiliaryInput_s : iVtObjectObject_s {
      iVtObjectAuxiliaryInput_s(Colour backgroundColour, uint8_t functionType, uint8_t inputId) : backgroundColour(
              backgroundColour), functionType(functionType), inputId(inputId) {}

      Colour backgroundColour;
    uint8_t functionType;
    uint8_t inputId;
  };

  struct iVtObjectAuxiliaryFunction_s : iVtObjectObject_s {
      iVtObjectAuxiliaryFunction_s(Colour backgroundColour, uint8_t functionType) : backgroundColour(backgroundColour),
                                                                                     functionType(functionType) {}

      Colour backgroundColour;
    uint8_t functionType;
  };

  struct iVtObjectGraphicsContext_s : iVtObject_s {
      iVtObjectGraphicsContext_s(uint16_t viewportWidth, uint16_t viewportHeight, int16_t viewportX, int16_t viewportY,
                                 uint16_t canvasWidth, uint16_t canvasHeight, float viewportZoom, int16_t cursorX,
                                 int16_t cursorY, uint8_t foregroundColour, Colour backgroundColour,
                                 iVtObjectFontAttributes_c *fontAttributes, iVtObjectLineAttributes_c *lineAttributes,
                                 iVtObjectFillAttributes_c *fillAttributes, uint8_t format, uint8_t options,
                                 Colour transparencyColour) : viewportWidth(viewportWidth),
                                                               viewportHeight(viewportHeight), viewportX(viewportX),
                                                               viewportY(viewportY), canvasWidth(canvasWidth),
                                                               canvasHeight(canvasHeight), viewportZoom(viewportZoom),
                                                               cursorX(cursorX), cursorY(cursorY),
                                                               foregroundColour(foregroundColour),
                                                               backgroundColour(backgroundColour),
                                                               fontAttributes(fontAttributes),
                                                               lineAttributes(lineAttributes),
                                                               fillAttributes(fillAttributes), format(format),
                                                               options(options),
                                                               transparencyColour(transparencyColour) {}

      uint16_t viewportWidth;
    uint16_t viewportHeight;
    int16_t  viewportX;       //!< Upper left corner of the viewport
    int16_t  viewportY;
    uint16_t canvasWidth;
    uint16_t canvasHeight;
    float    viewportZoom;    //!< Zoom value [-32.0F ... 32.0F]
    int16_t  cursorX;
    int16_t  cursorY;
    uint8_t  foregroundColour;
    uint8_t  backgroundColour;
    iVtObjectFontAttributes_c* fontAttributes;
    iVtObjectLineAttributes_c* lineAttributes;
    iVtObjectFillAttributes_c* fillAttributes;
    uint8_t  format;          //!< 0 => 1 bit/pixel, 1 => 4 bit/pixel, 2 => 8 bit/pixel
    uint8_t  options;         //!< Bit 0 transparent flag; Bit 1 line, font, fill colour usage
    uint8_t  transparencyColour;  //!< Colour to be shown transparent.
  };

  struct iVtObjectAuxiliaryInput2_s : iVtObjectObject_s {
      iVtObjectAuxiliaryInput2_s(Colour backgroundColour, uint8_t functionAttributes) : backgroundColour(
              backgroundColour), functionAttributes(functionAttributes) {}

      Colour backgroundColour;
    uint8_t functionAttributes;
  };

  struct iVtObjectAuxiliaryFunction2_s : iVtObjectObject_s {
      iVtObjectAuxiliaryFunction2_s(Colour backgroundColour, uint8_t functionAttributes) : backgroundColour(
              backgroundColour), functionAttributes(functionAttributes) {}

      Colour backgroundColour;
    uint8_t functionAttributes;
  };

  struct iVtObjectAuxiliaryControlDesignatorObjectPointer_s : iVtObject_s {
      iVtObjectAuxiliaryControlDesignatorObjectPointer_s(uint8_t pointerType, iVtObject_c *value) : pointerType(
              pointerType), value(value) {}

      uint8_t pointerType;
    iVtObject_c* value;
  };

// METHODS
public:
  // Constructor
  iVtObject_c();

  ~iVtObject_c() override = default;

  //  Operation: getID
  uint16_t getID() const;

  //! *** API-function ***
  //! Per default, all objects are uploaded.
  //! This function inhibts objects from being uploaded
  //! to the VT. Only use this function if you know what
  //! you're doing and if there's no other way.
  //! This can be useful for omitting e.g. AuxFunction
  //! objects that should not be available due to configuration.
  void omitFromUpload();

  virtual void setOriginSKM(bool b_SKM);
  virtual void setOriginBTN(iVtObjectButton_c* p_btn);

  void setClientID (uint8_t ui8_clientID);

  /** return object type as described in the standard.
      please note that the upper byte may be used for proprietary objects.
   */
  virtual uint16_t getObjectType() const = 0;

protected:
  iVtObject_s* vtObject_a; //TODO: remove this later !!!

  iVtObjectButton_c* p_parentButtonObject;

  struct {
    uint8_t flags:5;
    uint8_t clientId:3; // when changing, adapt the assertion in "setClientID(..)"!
  } s_properties;

private:
  // non-copy/assign-able
  iVtObject_c( const iVtObject_c& );
  iVtObject_c& operator=( const iVtObject_c& );
};

inline
void
iVtObject_c::omitFromUpload()
{
  s_properties.flags = uint8_t(s_properties.flags | FLAG_OMIT_OBJECT);
}


inline
void
iVtObject_c::setClientID( uint8_t ui8_clientID )
{
  isoaglib_header_assert( ui8_clientID < 8 ); // 3 bits only, see struct s_clientId
  s_properties.clientId = (ui8_clientID & 0x07); // "&" to avoid -Wconversion warning
}


} // IsoAgLib

#endif
