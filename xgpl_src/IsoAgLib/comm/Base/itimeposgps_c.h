/***************************************************************************
                itimeposgps_c.h  - working on Base Data Msg Type NMEA 200 GPS
                                  and Calendar; stores, updates  and
                                  delivers all base data informations
                                  from CANCustomer_c derived for CAN
                                  sending and receiving interaction;
                                  from ElementBase_c derived for
                                  interaction with other IsoAgLib objects
                             -------------------
    begin                 Fri Apr 07 2000
    copyright            : (C) 2000 - 2004 by Dipl.-Inform. Achim Spangler
    email                : a.spangler@osb-ag:de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 * This file is part of the "IsoAgLib", an object oriented program library *
 * to serve as a software layer between application specific program and   *
 * communication protocol details. By providing simple function calls for  *
 * jobs like starting a measuring program for a process data value on a    *
 * remote ECU, the main program has not to deal with single CAN telegram   *
 * formatting. This way communication problems between ECU's which use     *
 * this library should be prevented.                                       *
 * Everybody and every company is invited to use this library to make a    *
 * working plug and play standard out of the printed protocol standard.    *
 *                                                                         *
 * Copyright (C) 2000 - 2004 Dipl.-Inform. Achim Spangler                  *
 *                                                                         *
 * The IsoAgLib is free software; you can redistribute it and/or modify it *
 * under the terms of the GNU General Public License as published          *
 * by the Free Software Foundation; either version 2 of the License, or    *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This library is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU       *
 * General Public License for more details.                                *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with IsoAgLib; if not, write to the Free Software Foundation,     *
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA           *
 *                                                                         *
 * As a special exception, if other files instantiate templates or use     *
 * macros or inline functions from this file, or you compile this file and *
 * link it with other works to produce a work based on this file, this file*
 * does not by itself cause the resulting work to be covered by the GNU    *
 * General Public License. However the source code for this file must still*
 * be made available in accordance with section (3) of the                 *
 * GNU General Public License.                                             *
 *                                                                         *
 * This exception does not invalidate any other reasons why a work based on*
 * this file might be covered by the GNU General Public License.           *
 *                                                                         *
 * Alternative licenses for IsoAgLib may be arranged by contacting         *
 * the main author Achim Spangler by a.spangler@osb-ag:de                  *
 ***************************************************************************/
#ifndef ITIMEPOSGPS_C_H
#define ITIMEPOSGPS_C_H

/* *************************************** */
/* ********** include headers ************ */
/* *************************************** */
#include <IsoAgLib/util/idevkey_c.h>
#include "ibasetypes.h"
#include "impl/timeposgps_c.h"

// Begin Namespace IsoAgLib
namespace IsoAgLib {

/**
  working on Base Data Msg Type 1, 2 and Calendar;
  stores, updates  and delivers all base data informations;
  Derive from ElementBase_c to register in Scheduler_c for timeEvent trigger
  Derive from CANCustomer to register FilterBox'es in CANIO_c to receive CAN messages
  Derive from SINGLETON to create a Singleton which manages one global accessible singleton
   per IsoAgLib instance (if only one IsoAgLib instance is defined in application config, no overhead is produced).
  *@author Dipl.-Inform. Achim Spangler
*/
class iTimePosGPS_c : private __IsoAgLib::TimePosGPS_c {
public:
  // Public methods
  /**
      DEPRECATED CONFIG FUNCTION - PLEASE DO NOT USE ANY MORE AS THIS FUNCTION WILL BE REMOVED SOON
      config the Base_c object after init -> set pointer to devKey and
      config send/receive of different base msg types
      @param rpc_devKey pointer to the DEV_KEY variable of the responsible member instance (pointer enables automatic value update if var val is changed)
      @param rb_implementMode implement mode (true) or tractor mode (false)!!!
      @return true -> configuration was successfull
    */
  bool config(const iDevKey_c* rpc_devKey, bool rb_implementMode)
  {
    #if __GNUC__
    #warning "deprecated, use IsoAgLib::IdentMode_t as parameter instead of bool"
    #elif defined WIN32
    #pragma message ("deprecated, use IsoAgLib::IdentMode_t as parameter instead of bool")
    #endif
    return TimePosGPS_c::config(rpc_devKey, (rb_implementMode ? IsoAgLib::IdentModeImplement : IsoAgLib::IdentModeTractor));
  };

  /**
      config the Base_c object after init -> set pointer to devKey and
      config send/receive of different base msg types
      @param rpc_devKey pointer to the DEV_KEY variable of the responsible member instance (pointer enables automatic value update if var val is changed)
      @param rt_identMode set mode to either IsoAgLib::IdentModeImplement or IsoAgLib::IdentModeTractor
      @return true -> configuration was successfull
    */
  bool config(const iDevKey_c* rpc_devKey, IsoAgLib::IdentMode_t rt_identMode = IsoAgLib::IdentModeImplement)
  { return TimePosGPS_c::config(rpc_devKey, rt_identMode ); }

  #ifdef USE_ISO_11783
  /** config the Base_c object after init -> set pointer to devKey and
      config send/receive of different base msg types
      @param rpc_devKey pointer to the DEV_KEY variable of the ersponsible member instance (pointer enables automatic value update if var val is changed)
      @param rt_identModeGps either IsoAgLib::IdentModeImplement or IsoAgLib::IdentModeTractor
      @return true -> configuration was successfull
    */
  bool configGps(const iDevKey_c* rpc_devKey, IsoAgLib::IdentMode_t rt_identModeGps)
  {return TimePosGPS_c::configGps( rpc_devKey, rt_identModeGps);}
  /** config the Base_c object after init -> set pointer to devKey and
      config send/receive of different base msg types
      @param rpc_devKey pointer to the DEV_KEY variable of the ersponsible member instance (pointer enables automatic value update if var val is changed)
      @param rb_implementMode implement mode (true) or tractor mode (false)!!!
      @return true -> configuration was successfull
    */
  bool configGps(const iDevKey_c* rpc_devKey, bool rb_implementMode)
  {
    #if __GNUC__
    #warning "deprecated, use IsoAgLib::IdentMode_t as parameter instead of bool"
    #elif defined WIN32
    #pragma message ("deprecated, use IsoAgLib::IdentMode_t as parameter instead of bool")
    #endif
    return TimePosGPS_c::configGps(rpc_devKey, (rb_implementMode ? IsoAgLib::IdentModeImplement : IsoAgLib::IdentModeTractor));
  };
  /** Retrieve the last update time of the specified information type
   */
  int32_t lastedTimeSinceUpdateGps() const
    {return TimePosGPS_c::lastedTimeSinceUpdateGps();};
  /** Retrieve the time of last update */
  int32_t lastUpdateTimeGps() const
  {return TimePosGPS_c::lastUpdateTimeGps();};
/** Retrieve the last update time of the Heading and speed*/
	int32_t lastedTimeSinceUpdateGpsCourse() const	{ return TimePosGPS_c::lastedTimeSinceUpdateGpsCourse(); }
/** Retrieve the time of last Heading and speed */
	int32_t lastUpdateTimeGpsCourse() const	{ return TimePosGPS_c::lastUpdateTimeGpsCourse(); }
  /** return a sender which sends GPS commands as a tractor */
  iDevKey_c& getSenderDevKeyGps() {return static_cast<iDevKey_c&>(TimePosGPS_c::getSenderDevKeyGps());};
  /** return a sender which sends GPS commands as a tractor */
  const iDevKey_c& getSenderDevKeyGpsConst() const {return static_cast<const iDevKey_c&>(TimePosGPS_c::getSenderDevKeyGpsConst());};

  /** force a request for pgn for time/date information */
  bool sendRequestUpdateTimeDate() { return TimePosGPS_c::sendRequestUpdateTimeDate(); }

  /** @return TRUE => data source dev key is specified */
  bool checkDataSourceSpecified() { return TimePosGPS_c::getSelectedDataSourceDevKeyConst().isSpecified();};
  #endif

  /** get Devkey of data source (e.g. tractor, terminal) from which commands are send exclusively */
  const iDevKey_c& getSelectedDataSourceDevKeyConst() const {return static_cast<const iDevKey_c&>(TimePosGPS_c::getSelectedDataSourceDevKeyConst());};

  /* ******************************************* */
  /** \name Get Values */
  /*@{*/
  /** check if a calendar information was received since init */
  bool isCalendarReceived() const { return TimePosGPS_c::isCalendarReceived();};

  /** check if a calendar information was received since init */
  bool isCalendarDateValid() const { return TimePosGPS_c::isCalendarDateValid(); }

  /** get the calendar year value */
  int16_t yearLocal() { return TimePosGPS_c::yearLocal();};
  /** get the calendar year value */
  int16_t yearUtc(){ return TimePosGPS_c::yearUtc();};
  /** get the calendar month value */
  uint8_t monthLocal() { return TimePosGPS_c::monthLocal();};
  /** get the calendar month value */
  uint8_t monthUtc() { return TimePosGPS_c::monthUtc();};
  /** get the calendar day value */
  uint8_t dayLocal() { return TimePosGPS_c::dayLocal();};
  /** get the calendar day value */
  uint8_t dayUtc() { return TimePosGPS_c::dayUtc();};
  /** get the calendar hour value */
  uint8_t hourLocal() { return TimePosGPS_c::hourLocal();};
  /** get the calendar hour value */
  uint8_t hourUtc() { return TimePosGPS_c::hourUtc();};
  /** get the calendar minute value */
  uint8_t minuteLocal() { return TimePosGPS_c::minuteLocal();};
  /** get the calendar minute value */
  uint8_t minuteUtc() { return TimePosGPS_c::minuteUtc();};
  /** get the calendar second value */
  uint8_t second() { return TimePosGPS_c::second();};
  /** get the calendar millisecond value */
  uint16_t millisecond() const { return TimePosGPS_c::millisecond();};

  /** deliver UTC time in struct tm instead of separate calls to minuteUtc(), hourUtc(), ... to reduce load
    @return struct tm
  */
  struct CNAMESPACE::tm* currentUtcTm() { return TimePosGPS_c::currentUtcTm();};

  /** deliver raw GPS Latitude [degree] with scaling 10.0e-7 */
  int32_t getGpsLatitudeDegree10Minus7(void) const { return TimePosGPS_c::getGpsLatitudeDegree10Minus7();};
  /** deliver raw GPS Longitude [degree] with scaling 10.0e-7 */
  int32_t getGpsLongitudeDegree10Minus7(void) const { return TimePosGPS_c::getGpsLongitudeDegree10Minus7();};

  #if defined(USE_FLOAT_DATA_TYPE) || defined(USE_DIN_GPS)
  /** check if an NMEA2000 position signal was received */
  bool isPositionReceived() const { return TimePosGPS_c::isPositionReceived();};
  /** check if an NMEA2000 direction signal was received */
  bool isDirectionReceived() const { return TimePosGPS_c::isDirectionReceived(); }

  /** deliver Minute GPS Latitude */
  float getGpsLatitudeMinute(void) const { return TimePosGPS_c::getGpsLatitudeMinute();};
  /** deliver Minute GPS Longitude */
  float getGpsLongitudeMinute(void) const { return TimePosGPS_c::getGpsLongitudeMinute();};
  /** deliver Degree GPS Latitude */
  float getGpsLatitudeDegree(void) const { return TimePosGPS_c::getGpsLatitudeDegree();};
  /** deliver Degree GPS Longitude */
  float getGpsLongitudeDegree(void) const { return TimePosGPS_c::getGpsLongitudeDegree();};
  #endif // END of USE_FLOAT_DATA_TYPE and USE_DIN_GPS

  #ifdef NMEA_2000_FAST_PACKET
  /** get the GPS UTC hour value
      @return actual GPS UTC hour value
   */
  uint8_t hourUtcGps() const {return TimePosGPS_c::hourUtcGps();};
  /** get the GPS UTC minute value
      @return actual GPS UTC minute value
   */
  uint8_t minuteUtcGps() const {return TimePosGPS_c::minuteUtcGps();};
  /** get the GPS UTC second value
      @return actual GPS UTC second value
   */
  uint8_t secondUtcGps() const {return TimePosGPS_c::secondUtcGps();};
  /** get the GPS UTC millisecond value
      @return actual GPS UTC millisecond value
   */
  uint16_t millisecondUtcGps() const {return TimePosGPS_c::millisecondUtcGps();};
  /** deliver GPS altitude - [cm] */
  uint32_t getGpsAltitudeCm(void) const { return TimePosGPS_c::getGpsAltitudeCm();};
  /** deliver GPS receive qualitiy */
  IsoAgLib::IsoGnssMethod_t getGnssMode(void) const { return TimePosGPS_c::getGnssMode();};
  /** simply check for some sort of Differential signal */
  bool hasDifferentialPosition() const{ return TimePosGPS_c::hasDifferentialPosition();};
  /** deliver GNSS type ( e.g. GPS, GLONASS or SBAS ) */
  IsoAgLib::IsoGnssType_t getGnssType(void) const { return TimePosGPS_c::getGnssType();};
  /** deliver GPS speed as [cm/s] */
  uint16_t getGpsSpeedCmSec(void) const { return TimePosGPS_c::getGpsSpeedCmSec();};
  /** deliver GPS speed over ground as [cm/s] */
  uint16_t getSpeedOverGroundCmSec(void) const { return TimePosGPS_c::getSpeedOverGroundCmSec();};
  /** deliver GPS Heading [1x10E-4rad] */
  uint16_t getGpsHeadingRad10Minus4(void) const { return TimePosGPS_c::getGpsHeadingRad10Minus4();};
  /** deliver GPS CourceOverGround [1x10E-4rad] */
  uint16_t getGpsCourseOverGroundRad10Minus4(void) const { return TimePosGPS_c::getGpsCourseOverGroundRad10Minus4();};
  /** deliver number of received satellites */
  uint8_t satelliteCnt() const { return TimePosGPS_c::satelliteCnt();};
  /** deliver HDOP with scaling [1x10E-2] */
  int16_t hdop10Minus2() const { return TimePosGPS_c::hdop10Minus2();};
  /** PDOP with scaling [1x10E-2] */
  int16_t pdop10Minus2() const { return TimePosGPS_c::pdop10Minus2();};
  #endif // END NMEA_2000_FAST_PACKET

  #if defined(USE_ISO_11783)
  /** deliver age of last gps-update in milliseconds */
  uint16_t getGpsUpdateAge(void) const { return TimePosGPS_c::getGpsUpdateAge();};
  #endif

  /* ******************************************* */
  /** \name Set Values */
  /*@{*/

  /** set the calendar value */
  void setCalendarUtc(int16_t ri16_year, uint8_t rb_month, uint8_t rb_day, uint8_t rb_hour, uint8_t rb_minute, uint8_t rb_second, uint16_t rui16_msec = 0)
  { return TimePosGPS_c::setCalendarUtc(ri16_year, rb_month, rb_day, rb_hour, rb_minute, rb_second, rui16_msec);};
  /** set the calendar value as local time ( take local time offsets into account ) */
  void setCalendarLocal(int16_t ri16_year, uint8_t rb_month, uint8_t rb_day, uint8_t rb_hour, uint8_t rb_minute, uint8_t rb_second, uint16_t rui16_msec = 0)
  { return TimePosGPS_c::setCalendarLocal(ri16_year, rb_month, rb_day, rb_hour, rb_minute, rb_second, rui16_msec);};
  /** set the date in local timezone */
  void setDateLocal(int16_t ri16_year, uint8_t rb_month, uint8_t rb_day)
  { return TimePosGPS_c::setDateLocal(ri16_year, rb_month, rb_day);};
  /** set the date in UTC timezone */
  void setDateUtc(int16_t ri16_year, uint8_t rb_month, uint8_t rb_day)
  { return TimePosGPS_c::setDateUtc(ri16_year, rb_month, rb_day);};
  /** set the time in local timezone */
  void setTimeLocal(uint8_t rb_hour, uint8_t rb_minute, uint8_t rb_second, uint16_t rui16_msec = 0)
  { return TimePosGPS_c::setTimeLocal(rb_hour, rb_minute, rb_second, rui16_msec);};
  /** set the time in UTC timezone */
  void setTimeUtc(uint8_t rb_hour, uint8_t rb_minute, uint8_t rb_second, uint16_t rui16_msec = 0, bool b_updateDate = FALSE)
  { return TimePosGPS_c::setTimeUtc(rb_hour, rb_minute, rb_second, rui16_msec, b_updateDate);};
  /** set the actual calendar year value */
  void setYearUtc(uint16_t rui16_year)
  { return TimePosGPS_c::setYearUtc(rui16_year);};

  /** deliver raw GPS Latitude [degree] with scaling 10.0e-7 */
  void setGpsLatitudeDegree10Minus7( int32_t ri32_newVal )
  { return TimePosGPS_c::setGpsLatitudeDegree10Minus7(ri32_newVal);};
  /** deliver raw GPS Longitude [degree] with scaling 10.0e-7 */
  void setGpsLongitudeDegree10Minus7(int32_t ri32_newVal)
  { return TimePosGPS_c::setGpsLongitudeDegree10Minus7(ri32_newVal);};

  #if defined(NMEA_2000_FAST_PACKET)
  /** set the GPS time in UTC timezone.
   *  When no remote system is sending the 11783-7 PGN with date & time, the new UTC time is also set with
   *  setTimeUtc().
   *  In case another system is sending TIME_DATE_PGN, this time could be out-of-sync with GPS time.
   *  To avoid a jumping back and forth Non-GPS UTC time, those two UTC time sources are then not to be synced.
   */
  void setTimeUtcGps(uint8_t rb_hour, uint8_t rb_minute, uint8_t rb_second, uint16_t rui16_msec = 0)
    {TimePosGPS_c::setTimeUtcGps( rb_hour, rb_minute, rb_second, rui16_msec );};
  /** set the calendar hour value
   *  When no remote system is sending the 11783-7 PGN with date & time, the new UTC time is also set with
   *  setTimeUtc().
   *  In case another system is sending TIME_DATE_PGN, this time could be out-of-sync with GPS time.
   *  To avoid a jumping back and forth Non-GPS UTC time, those two UTC time sources are then not to be synced.
   *  @param rb_hour actual calendar hour value
   */
  void setHourUtcGps(uint8_t rb_hour) {TimePosGPS_c::setHourUtcGps( rb_hour );};
  /** set the calendar minute value
   *  When no remote system is sending the 11783-7 PGN with date & time, the new UTC time is also set with
   *  setTimeUtc().
   *  In case another system is sending TIME_DATE_PGN, this time could be out-of-sync with GPS time.
   *  To avoid a jumping back and forth Non-GPS UTC time, those two UTC time sources are then not to be synced.
   *  @param rb_minute actual calendar minute value
   */
  void setMinuteUtcGps(uint8_t rb_minute) {TimePosGPS_c::setMinuteUtcGps( rb_minute );};
  /** set the calendar second value
   *  When no remote system is sending the 11783-7 PGN with date & time, the new UTC time is also set with
   *  setTimeUtc().
   *  In case another system is sending TIME_DATE_PGN, this time could be out-of-sync with GPS time.
   *  To avoid a jumping back and forth Non-GPS UTC time, those two UTC time sources are then not to be synced.
   *  @param rb_second actual calendar second value
   */
  void setSecondUtcGps(uint8_t rb_second) {TimePosGPS_c::setSecondUtcGps( rb_second );};
  /** set the calendar millisecond value
   *  When no remote system is sending the 11783-7 PGN with date & time, the new UTC time is also set with
   *  setTimeUtc().
   *  In case another system is sending TIME_DATE_PGN, this time could be out-of-sync with GPS time.
   *  To avoid a jumping back and forth Non-GPS UTC time, those two UTC time sources are then not to be synced.
   *  @param rb_millisecond actual calendar second value
   */
  void setMillisecondUtcGps(uint16_t rui16_millisecond) {TimePosGPS_c::setMillisecondUtcGps( rui16_millisecond );};
  /** deliver GPS altitude - [cm] */
  void setGpsAltitudeCm( uint32_t rui32_newVal )
  { TimePosGPS_c::setGpsAltitudeCm(rui32_newVal);};
  /** deliver GPS receive qualitiy */
  void setGnssMode(IsoAgLib::IsoGnssMethod_t rt_newVal)
  { TimePosGPS_c::setGnssMode(rt_newVal);};
  /** deliver GNSS type ( e.g. GPS, GLONASS or SBAS ) */
  void setGnssType( IsoAgLib::IsoGnssType_t rt_newVal )
  { TimePosGPS_c::setGnssType(rt_newVal);};
  /** deliver GPS speed as [cm/s] */
  void setGpsSpeedCmSec(uint16_t rui16_newVal)
  { TimePosGPS_c::setGpsSpeedCmSec(rui16_newVal);};
  void setSpeedOverGroundCmSec(uint16_t rui16_newVal)
  { TimePosGPS_c::setSpeedOverGroundCmSec(rui16_newVal);};
  /** deliver GPS Heading [1x10E-4rad] */
  void setGpsHeadingRad10Minus4(uint16_t rui16_newVal)
  { TimePosGPS_c::setGpsHeadingRad10Minus4(rui16_newVal);};
  void setGpsCourseOverGroundRad10Minus4(uint16_t rui16_newVal)
  { TimePosGPS_c::setGpsCourseOverGroundRad10Minus4(rui16_newVal);};
  /** deliver number of received satellites */
  void setSatelliteCnt(uint8_t rui8_newVal)
  { TimePosGPS_c::setSatelliteCnt(rui8_newVal);};
  /** deliver HDOP with scaling [1x10E-2] */
  void setHdop10Minus2(uint16_t rui16_newVal)
  { TimePosGPS_c::setHdop10Minus2(rui16_newVal);};
  /** PDOP with scaling [1x10E-2] */
  void setPdop10Minus2(uint16_t rui16_newVal)
  { TimePosGPS_c::setPdop10Minus2(rui16_newVal);};
  #endif // END of NMEA_2000_FAST_PACKET

  /** set the calendar month value */
  void setMonthUtc(uint8_t rb_month)
  { TimePosGPS_c::setMonthUtc(rb_month);};
  /** set the calendar day value */
  void setDayUtc(uint8_t rb_day)
  { TimePosGPS_c::setDayUtc(rb_day);};
  /** set the calendar hour value */
  void setHourUtc(uint8_t rb_hour)
  { TimePosGPS_c::setHourUtc(rb_hour);};
  /** set the calendar minute value */
  void setMinuteUtc(uint8_t rb_minute)
  { TimePosGPS_c::setMinuteUtc(rb_minute);};
  /** set the calendar second value */
  void setSecond(uint8_t rb_second)
  { TimePosGPS_c::setSecond(rb_second);};
  /** set the calendar millisecond value */
  void setMillisecond(uint16_t rui16_millisecond)
  { TimePosGPS_c::setMillisecond(rui16_millisecond);};
  /** set the local time to UTC time offsets */
  void setLocalTimeOffsets(int16_t ri16_hourOffset, uint16_t rui16_minuteOffset)
  { TimePosGPS_c::setLocalTimeOffsets(ri16_hourOffset, rui16_minuteOffset);};


  /* ****************************************************** */
  /** \name Retrieve Values which are sent from other ECUs  */
  /*@{*/
 private:
  /** allow getITimePosGpsInstance() access to shielded TimePosGPS_c class.
    * otherwise __IsoAgLib::getTimePosGpsInstance() wouldn't be accepted by compiler
    */
  #if defined( PRT_INSTANCE_CNT ) && ( PRT_INSTANCE_CNT > 1 )
  friend iTimePosGPS_c& getITimePosGpsInstance( uint8_t rui8_instance );
  #else
  friend iTimePosGPS_c& getITimePosGpsInstance( void );
  #endif
};

#if defined( PRT_INSTANCE_CNT ) && ( PRT_INSTANCE_CNT > 1 )
  /** C-style function, to get access to the unique Base_c singleton instance
    * if more than one CAN BUS is used for IsoAgLib, an index must be given to select the wanted BUS
    */
  inline iTimePosGPS_c& getITimePosGpsInstance( uint8_t rui8_instance = 0 )
  { return static_cast<iTimePosGPS_c&>(__IsoAgLib::getTimePosGpsInstance(rui8_instance));};
#else
  /** C-style function, to get access to the unique Base_c singleton instance */
  inline iTimePosGPS_c& getITimePosGpsInstance( void )
  { return static_cast<iTimePosGPS_c&>(__IsoAgLib::getTimePosGpsInstance());};
#endif

}
#endif
