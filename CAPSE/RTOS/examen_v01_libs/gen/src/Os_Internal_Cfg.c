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
/** \brief Alive stack */
#if ( x86 == ARCH )
uint8 StackTaskAlive[512 + TASK_STACK_ADDITIONAL_SIZE];
#else
uint8 StackTaskAlive[512];
#endif
/** \brief ReadReset stack */
#if ( x86 == ARCH )
uint8 StackTaskReadReset[512 + TASK_STACK_ADDITIONAL_SIZE];
#else
uint8 StackTaskReadReset[512];
#endif
/** \brief ReadPacket stack */
#if ( x86 == ARCH )
uint8 StackTaskReadPacket[512 + TASK_STACK_ADDITIONAL_SIZE];
#else
uint8 StackTaskReadPacket[512];
#endif
/** \brief Statistics stack */
#if ( x86 == ARCH )
uint8 StackTaskStatistics[512 + TASK_STACK_ADDITIONAL_SIZE];
#else
uint8 StackTaskStatistics[512];
#endif
/** \brief ShowGoodPacket stack */
#if ( x86 == ARCH )
uint8 StackTaskShowGoodPacket[512 + TASK_STACK_ADDITIONAL_SIZE];
#else
uint8 StackTaskShowGoodPacket[512];
#endif
/** \brief ShowBadPacket stack */
#if ( x86 == ARCH )
uint8 StackTaskShowBadPacket[512 + TASK_STACK_ADDITIONAL_SIZE];
#else
uint8 StackTaskShowBadPacket[512];
#endif

/** \brief Alive context */
TaskContextType ContextTaskAlive;
/** \brief ReadReset context */
TaskContextType ContextTaskReadReset;
/** \brief ReadPacket context */
TaskContextType ContextTaskReadPacket;
/** \brief Statistics context */
TaskContextType ContextTaskStatistics;
/** \brief ShowGoodPacket context */
TaskContextType ContextTaskShowGoodPacket;
/** \brief ShowBadPacket context */
TaskContextType ContextTaskShowBadPacket;

/** \brief Ready List for Priority 0 */
TaskType ReadyList0[6];

const AlarmType OSEK_ALARMLIST_HardwareCounter[6] = {
   ActivateAlive, /* this alarm has to be incremented with this counter */
   ActivateShowGoodPacket, /* this alarm has to be incremented with this counter */
   ActivateShowBadPacket, /* this alarm has to be incremented with this counter */
   ActivateReadReset, /* this alarm has to be incremented with this counter */
   ActivateReadPacket, /* this alarm has to be incremented with this counter */
   ShowStatistics, /* this alarm has to be incremented with this counter */
};


/*==================[external data definition]===============================*/
/* FreeOSEK to configured priority table
 *
 * This table show the relationship between the user selected
 * priorities and the OpenOSE priorities:
 *
 * User P.         Osek P.
 * 1               0
 */

const TaskConstType TasksConst[TASKS_COUNT] = {
   /* Task Alive */
   {
       OSEK_TASK_Alive,   /* task entry point */
       &ContextTaskAlive, /* pointer to task context */
       StackTaskAlive, /* pointer stack memory */
       sizeof(StackTaskAlive), /* stack size */
       0, /* task priority */
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
   /* Task ReadReset */
   {
       OSEK_TASK_ReadReset,   /* task entry point */
       &ContextTaskReadReset, /* pointer to task context */
       StackTaskReadReset, /* pointer stack memory */
       sizeof(StackTaskReadReset), /* stack size */
       0, /* task priority */
       1, /* task max activations */
       {
         1, /* extended task */
         0, /* non preemtive task */
         0
      }, /* task const flags */
      0 | EvtReset , /* events mask */
      0 ,/* resources mask */
      0 /* core */
   },
   /* Task ReadPacket */
   {
       OSEK_TASK_ReadPacket,   /* task entry point */
       &ContextTaskReadPacket, /* pointer to task context */
       StackTaskReadPacket, /* pointer stack memory */
       sizeof(StackTaskReadPacket), /* stack size */
       0, /* task priority */
       1, /* task max activations */
       {
         1, /* extended task */
         0, /* non preemtive task */
         0
      }, /* task const flags */
      0 | EvtError | EvtQok | EvtSok | EvtRok | EvtEok , /* events mask */
      0 ,/* resources mask */
      0 /* core */
   },
   /* Task Statistics */
   {
       OSEK_TASK_Statistics,   /* task entry point */
       &ContextTaskStatistics, /* pointer to task context */
       StackTaskStatistics, /* pointer stack memory */
       sizeof(StackTaskStatistics), /* stack size */
       0, /* task priority */
       1, /* task max activations */
       {
         1, /* extended task */
         0, /* non preemtive task */
         0
      }, /* task const flags */
      0 | EvtReset | EvtShow | EvtError | EvtQok | EvtSok | EvtRok | EvtEok , /* events mask */
      0 ,/* resources mask */
      0 /* core */
   },
   /* Task ShowGoodPacket */
   {
       OSEK_TASK_ShowGoodPacket,   /* task entry point */
       &ContextTaskShowGoodPacket, /* pointer to task context */
       StackTaskShowGoodPacket, /* pointer stack memory */
       sizeof(StackTaskShowGoodPacket), /* stack size */
       0, /* task priority */
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
   /* Task ShowBadPacket */
   {
       OSEK_TASK_ShowBadPacket,   /* task entry point */
       &ContextTaskShowBadPacket, /* pointer to task context */
       StackTaskShowBadPacket, /* pointer stack memory */
       sizeof(StackTaskShowBadPacket), /* stack size */
       0, /* task priority */
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
   Statistics
};
/** \brief AutoStart Array */
const AutoStartType AutoStart[1]  = {
   /* Application Mode AppMode1 */
   {
      1, /* Total Auto Start Tasks in this Application Mode */
      (TaskRefType)TasksAppModeAppMode1 /* Pointer to the list of Auto Start Stacks on this Application Mode */
   }
};

const ReadyConstType ReadyConst[1] = { 
   {
      6, /* Length of this ready list */
      ReadyList0 /* Pointer to the Ready List */
   }
};

/** TODO replace next line with: 
 ** ReadyVarType ReadyVar[1] ; */
ReadyVarType ReadyVar[1];

/** \brief Resources Priorities */
const TaskPriorityType ResourcesPriority[0]  = {

};
/** TODO replace next line with: 
 ** AlarmVarType AlarmsVar[6]; */
AlarmVarType AlarmsVar[6];

const AlarmConstType AlarmsConst[6]  = {
   {
      OSEK_COUNTER_HardwareCounter, /* Counter */
      ACTIVATETASK, /* Alarm action */
      {
         NULL, /* no callback */
         Alive, /* TaskID */
         0, /* no event */
         0 /* no counter */
      },
   },
   {
      OSEK_COUNTER_HardwareCounter, /* Counter */
      ACTIVATETASK, /* Alarm action */
      {
         NULL, /* no callback */
         ShowGoodPacket, /* TaskID */
         0, /* no event */
         0 /* no counter */
      },
   },
   {
      OSEK_COUNTER_HardwareCounter, /* Counter */
      ACTIVATETASK, /* Alarm action */
      {
         NULL, /* no callback */
         ShowBadPacket, /* TaskID */
         0, /* no event */
         0 /* no counter */
      },
   },
   {
      OSEK_COUNTER_HardwareCounter, /* Counter */
      ACTIVATETASK, /* Alarm action */
      {
         NULL, /* no callback */
         ReadReset, /* TaskID */
         0, /* no event */
         0 /* no counter */
      },
   },
   {
      OSEK_COUNTER_HardwareCounter, /* Counter */
      ACTIVATETASK, /* Alarm action */
      {
         NULL, /* no callback */
         ReadPacket, /* TaskID */
         0, /* no event */
         0 /* no counter */
      },
   },
   {
      OSEK_COUNTER_HardwareCounter, /* Counter */
      SETEVENT, /* Alarm action */
      {
         NULL, /* no callback */
         Statistics, /* TaskID */
         EvtShow, /* no event */
         0 /* no counter */
      },
   }
};

const AutoStartAlarmType AutoStartAlarm[ALARM_AUTOSTART_COUNT] = {
  {
      AppMode1, /* Application Mode */
      ActivateAlive, /* Alarms */
      1000, /* Alarm Time */
      1000 /* Alarm Time */
   },
  {
      AppMode1, /* Application Mode */
      ActivateReadReset, /* Alarms */
      50, /* Alarm Time */
      40 /* Alarm Time */
   },
  {
      AppMode1, /* Application Mode */
      ActivateReadPacket, /* Alarms */
      50, /* Alarm Time */
      40 /* Alarm Time */
   },
  {
      AppMode1, /* Application Mode */
      ShowStatistics, /* Alarms */
      2000, /* Alarm Time */
      2000 /* Alarm Time */
   }
};

CounterVarType CountersVar[1];

const CounterConstType CountersConst[1] = {
   {
      6, /* quantity of alarms for this counter */
      (AlarmType*)OSEK_ALARMLIST_HardwareCounter, /* alarms list */
      8000, /* max allowed value */
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

