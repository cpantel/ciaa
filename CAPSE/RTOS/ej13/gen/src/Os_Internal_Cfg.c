/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/* Copyright 2008, 2009, 2014, 2015 Mariano Cerdeiro
 * Copyright 2014, ACSE & CADIEEL
 *      ACSE: http://www.sase.com.ar/asociacion-civil-sistemas-embebidos/ciaa/
 *      CADIEEL: http://www.cadieel.org.ar
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief FreeOSEK Os Generated Internal Configuration Implementation File
 **
 ** \file Os_Internal_Cfg.c
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 * JuCe         Juan Cecconi
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20150619 v0.1.4 MaCe fix issue #279
 * 20141125 v0.1.3 JuCe additional stack for x86 ARCH
 * 20090719 v0.1.2 MaCe rename file to Os_
 * 20090128 v0.1.1 MaCe add OSEK_MEMMAP check
 * 20080713 v0.1.0 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "Os_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
/** \brief Display stack */
#if ( x86 == ARCH )
uint8 StackTaskDisplay[512 + TASK_STACK_ADDITIONAL_SIZE];
#else
uint8 StackTaskDisplay[512];
#endif
/** \brief BlinkLed1 stack */
#if ( x86 == ARCH )
uint8 StackTaskBlinkLed1[512 + TASK_STACK_ADDITIONAL_SIZE];
#else
uint8 StackTaskBlinkLed1[512];
#endif
/** \brief ReadTec stack */
#if ( x86 == ARCH )
uint8 StackTaskReadTec[512 + TASK_STACK_ADDITIONAL_SIZE];
#else
uint8 StackTaskReadTec[512];
#endif

/** \brief Display context */
TaskContextType ContextTaskDisplay;
/** \brief BlinkLed1 context */
TaskContextType ContextTaskBlinkLed1;
/** \brief ReadTec context */
TaskContextType ContextTaskReadTec;

/** \brief Ready List for Priority 1 */
TaskType ReadyList1[2];

/** \brief Ready List for Priority 0 */
TaskType ReadyList0[1];

const AlarmType OSEK_ALARMLIST_HardwareCounter[3] = {
   ActivateDisplay, /* this alarm has to be incremented with this counter */
   ActivateBlinkLed1, /* this alarm has to be incremented with this counter */
   ActivateReadTec, /* this alarm has to be incremented with this counter */
};


/*==================[external data definition]===============================*/
/* FreeOSEK to configured priority table
 *
 * This table show the relationship between the user selected
 * priorities and the OpenOSE priorities:
 *
 * User P.         Osek P.
 * 2               1
 * 1               0
 */

const TaskConstType TasksConst[TASKS_COUNT] = {
   /* Task Display */
   {
       OSEK_TASK_Display,   /* task entry point */
       &ContextTaskDisplay, /* pointer to task context */
       StackTaskDisplay, /* pointer stack memory */
       sizeof(StackTaskDisplay), /* stack size */
       0, /* task priority */
       1, /* task max activations */
       {
         1, /* extended task */
         0, /* non preemtive task */
         0
      }, /* task const flags */
      0 | Asterisk | EvtTec1 | EvtTec2 | EvtTec3 | EvtTec4 , /* events mask */
      0 ,/* resources mask */
      0 /* core */
   },
   /* Task BlinkLed1 */
   {
       OSEK_TASK_BlinkLed1,   /* task entry point */
       &ContextTaskBlinkLed1, /* pointer to task context */
       StackTaskBlinkLed1, /* pointer stack memory */
       sizeof(StackTaskBlinkLed1), /* stack size */
       1, /* task priority */
       1, /* task max activations */
       {
         0, /* basic task */
         0, /* non preemtive task */
         0
      }, /* task const flags */
      0 , /* events mask */
      0 ,/* resources mask */
      0 /* core */
   },
   /* Task ReadTec */
   {
       OSEK_TASK_ReadTec,   /* task entry point */
       &ContextTaskReadTec, /* pointer to task context */
       StackTaskReadTec, /* pointer stack memory */
       sizeof(StackTaskReadTec), /* stack size */
       1, /* task priority */
       1, /* task max activations */
       {
         0, /* basic task */
         0, /* non preemtive task */
         0
      }, /* task const flags */
      0 , /* events mask */
      0 ,/* resources mask */
      0 /* core */
   }
};

/** \brief RemoteTaskCore Array */
const TaskCoreType RemoteTasksCore[REMOTE_TASKS_COUNT] = {};

/** \brief TaskVar Array */
TaskVariableType TasksVar[TASKS_COUNT];

/** \brief List of Auto Start Tasks in Application Mode AppMode1 */
const TaskType TasksAppModeAppMode1[1]  = {
   Display
};
/** \brief AutoStart Array */
const AutoStartType AutoStart[1]  = {
   /* Application Mode AppMode1 */
   {
      1, /* Total Auto Start Tasks in this Application Mode */
      (TaskRefType)TasksAppModeAppMode1 /* Pointer to the list of Auto Start Stacks on this Application Mode */
   }
};

const ReadyConstType ReadyConst[2] = { 
   {
      2, /* Length of this ready list */
      ReadyList1 /* Pointer to the Ready List */
   },
   {
      1, /* Length of this ready list */
      ReadyList0 /* Pointer to the Ready List */
   }
};

/** TODO replace next line with: 
 ** ReadyVarType ReadyVar[2] ; */
ReadyVarType ReadyVar[2];

/** \brief Resources Priorities */
const TaskPriorityType ResourcesPriority[0]  = {

};
/** TODO replace next line with: 
 ** AlarmVarType AlarmsVar[3]; */
AlarmVarType AlarmsVar[3];

const AlarmConstType AlarmsConst[3]  = {
   {
      OSEK_COUNTER_HardwareCounter, /* Counter */
      SETEVENT, /* Alarm action */
      {
         NULL, /* no callback */
         Display, /* TaskID */
         Asterisk, /* no event */
         0 /* no counter */
      },
   },
   {
      OSEK_COUNTER_HardwareCounter, /* Counter */
      ACTIVATETASK, /* Alarm action */
      {
         NULL, /* no callback */
         BlinkLed1, /* TaskID */
         0, /* no event */
         0 /* no counter */
      },
   },
   {
      OSEK_COUNTER_HardwareCounter, /* Counter */
      ACTIVATETASK, /* Alarm action */
      {
         NULL, /* no callback */
         ReadTec, /* TaskID */
         0, /* no event */
         0 /* no counter */
      },
   }
};

const AutoStartAlarmType AutoStartAlarm[ALARM_AUTOSTART_COUNT] = {
  {
      AppMode1, /* Application Mode */
      ActivateDisplay, /* Alarms */
      2000, /* Alarm Time */
      5000 /* Alarm Time */
   },
  {
      AppMode1, /* Application Mode */
      ActivateBlinkLed1, /* Alarms */
      0, /* Alarm Time */
      500 /* Alarm Time */
   },
  {
      AppMode1, /* Application Mode */
      ActivateReadTec, /* Alarms */
      0, /* Alarm Time */
      50 /* Alarm Time */
   }
};

CounterVarType CountersVar[1];

const CounterConstType CountersConst[1] = {
   {
      3, /* quantity of alarms for this counter */
      (AlarmType*)OSEK_ALARMLIST_HardwareCounter, /* alarms list */
      10000, /* max allowed value */
      1, /* min cycle */
      1 /* ticks per base */
   }
};


/** TODO replace the next line with
 ** uint8 ApplicationMode; */
uint8 ApplicationMode;

/** TODO replace the next line with
 ** uint8 ErrorHookRunning; */
uint8 ErrorHookRunning;

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
