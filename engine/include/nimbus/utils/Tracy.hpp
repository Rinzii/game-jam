#pragma once

#ifdef CONFIG_NIMBUS_PROFILER

#include <tracy/Tracy.hpp>

#define NIM_TracyNoop TracyNoop

#define NIM_ZoneNamed(x, y) ZoneNamed(x, y)
#define NIM_ZoneNamedN(x, y, z) ZoneNamedN(x, y, z)
#define NIM_ZoneNamedC(x, y, z) ZoneNamedC(x, y, z)
#define NIM_ZoneNamedNC(x, y, z, w) ZoneNamedNC(x, y, z, w)

#define NIM_ZoneTransient(x, y) ZoneTransient(x, y)
#define NIM_ZoneTransientN(x, y, z) ZoneTransientN(x, y, z)

#define NIM_ZoneScoped ZoneScoped
#define NIM_ZoneScopedN(x) ZoneScopedN(x)
#define NIM_ZoneScopedC(x) ZoneScopedC(x)
#define NIM_ZoneScopedNC(x, y) ZoneScopedNC(x, y)

#define NIM_ZoneText(x, y) ZoneText(x, y)
#define NIM_ZoneTextV(x, y, z) ZoneTextV(x, y, z)
#define NIM_ZoneTextF(x, ...) ZoneTextF(x, __VA_ARGS__)
#define NIM_ZoneTextVF(x, y, ...) ZoneTextVF(x, y, __VA_ARGS__)
#define NIM_ZoneName(x, y) ZoneName(x, y)
#define NIM_ZoneNameV(x, y, z) ZoneNameV(x, y, z)
#define NIM_ZoneNameF(x, ...) ZoneNameF(x, __VA_ARGS__)
#define NIM_ZoneNameVF(x, y, ...) ZoneNameVF(x, y, __VA_ARGS__)
#define NIM_ZoneColor(x) ZoneColor(x)
#define NIM_ZoneColorV(x, y) ZoneColorV(x, y)
#define NIM_ZoneValue(x) ZoneValue(x)
#define NIM_ZoneValueV(x, y) ZoneValueV(x, y)
#define NIM_ZoneIsActive ZoneIsActive
#define NIM_ZoneIsActiveV(x) ZoneIsActiveV(x)

#define NIM_FrameMark FrameMark
#define NIM_FrameMarkNamed(x) FrameMarkNamed(x)
#define NIM_FrameMarkStart(x) FrameMarkStart(x)
#define NIM_FrameMarkEnd(x) FrameMarkEnd(x)

#define NIM_FrameImage(x, y, z, w, a) FrameImage(x, y, z, w, a)

#define NIM_TracyLockable(type, varname) TracyLockable(type, varname)
#define NIM_TracyLockableN(type, varname, desc) TracyLockableN(type, varname, desc)
#define NIM_TracySharedLockable(type, varname) TracySharedLockable(type, varname)
#define NIM_TracySharedLockableN(type, varname, desc) TracySharedLockableN(type, varname, desc)
#define NIM_LockableBase(type) LockableBase(type)
#define NIM_SharedLockableBase(type) SharedLockableBase(type)
#define NIM_LockMark(x) LockMark(x)
#define NIM_LockableName(x, y, z) LockableName(x, y, z)

#define NIM_TracyPlot(x, y) TracyPlot(x, y)
#define NIM_TracyPlotConfig(x, y, z, w, a) TracyPlotConfig(x, y, z, w, a)

#define NIM_TracyMessage(x, y) TracyMessage(x, y)
#define NIM_TracyMessageL(x) TracyMessageL(x)
#define NIM_TracyMessageC(x, y, z) TracyMessageC(x, y, z)
#define NIM_TracyMessageLC(x, y) TracyMessageLC(x, y)
#define NIM_TracyAppInfo(x, y) TracyAppInfo(x, y)

#define NIM_TracyAlloc(x, y) TracyAlloc(x, y)
#define NIM_TracyFree(x) TracyFree(x)
#define NIM_TracyMemoryDiscard(x) TracyMemoryDiscard(x)
#define NIM_TracySecureAlloc(x, y) TracySecureAlloc(x, y)
#define NIM_TracySecureFree(x) TracySecureFree(x)
#define NIM_TracySecureMemoryDiscard(x) TracySecureMemoryDiscard(x)

#define NIM_TracyAllocN(x, y, z) TracyAllocN(x, y, z)
#define NIM_TracyFreeN(x, y) TracyFreeN(x, y)
#define NIM_TracySecureAllocN(x, y, z) TracySecureAllocN(x, y, z)
#define NIM_TracySecureFreeN(x, y) TracySecureFreeN(x, y)

#define NIM_ZoneNamedS(x, y, z) ZoneNamedS(x, y, z)
#define NIM_ZoneNamedNS(x, y, z, w) ZoneNamedNS(x, y, z, w)
#define NIM_ZoneNamedCS(x, y, z, w) ZoneNamedCS(x, y, z, w)
#define NIM_ZoneNamedNCS(x, y, z, w, a) ZoneNamedNCS(x, y, z, w, a)

#define NIM_ZoneTransientS(x, y, z) ZoneTransientS(x, y, z)
#define NIM_ZoneTransientNS(x, y, z, w) ZoneTransientNS(x, y, z, w)

#define NIM_ZoneScopedS(x) ZoneScopedS(x)
#define NIM_ZoneScopedNS(x, y) ZoneScopedNS(x, y)
#define NIM_ZoneScopedCS(x, y) ZoneScopedCS(x, y)
#define NIM_ZoneScopedNCS(x, y, z) ZoneScopedNCS(x, y, z)

#define NIM_TracyAllocS(x, y, z) TracyAllocS(x, y, z)
#define NIM_TracyFreeS(x, y) TracyFreeS(x, y)
#define NIM_TracyMemoryDiscardS(x, y) TracyMemoryDiscardS(x, y)
#define NIM_TracySecureAllocS(x, y, z) TracySecureAllocS(x, y, z)
#define NIM_TracySecureFreeS(x, y) TracySecureFreeS(x, y)
#define NIM_TracySecureMemoryDiscardS(x, y) TracySecureMemoryDiscardS(x, y)

#define NIM_TracyAllocNS(x, y, z, w) TracyAllocNS(x, y, z, w)
#define NIM_TracyFreeNS(x, y, z) TracyFreeNS(x, y, z)
#define NIM_TracySecureAllocNS(x, y, z, w) TracySecureAllocNS(x, y, z, w)
#define NIM_TracySecureFreeNS(x, y, z) TracySecureFreeNS(x, y, z)

#define NIM_TracyMessageS(x, y, z) TracyMessageS(x, y, z)
#define NIM_TracyMessageLS(x, y) TracyMessageLS(x, y)
#define NIM_TracyMessageCS(x, y, z, w) TracyMessageCS(x, y, z, w)
#define NIM_TracyMessageLCS(x, y, z) TracyMessageLCS(x, y, z)

#define NIM_TracySourceCallbackRegister(x, y) TracySourceCallbackRegister(x, y)
#define NIM_TracyParameterRegister(x, y) TracyParameterRegister(x, y)
#define NIM_TracyParameterSetup(x, y, z, w) TracyParameterSetup(x, y, z, w)
#define NIM_TracyIsConnected TracyIsConnected
#define NIM_TracyIsStarted TracyIsStarted
#define NIM_TracySetProgramName(x) TracySetProgramName(x)

#define NIM_TracyFiberEnter(x) TracyFiberEnter(x)
#define NIM_TracyFiberEnterHint(x, y) TracyFiberEnterHint(x, y)
#define NIM_TracyFiberLeave TracyFiberLeave

#else

#define NIM_ZoneNamed(x, y)
#define NIM_ZoneNamedN(x, y, z)
#define NIM_ZoneNamedC(x, y, z)
#define NIM_ZoneNamedNC(x, y, z, w)

#define NIM_ZoneTransient(x, y)
#define NIM_ZoneTransientN(x, y, z)

#define NIM_ZoneScoped
#define NIM_ZoneScopedN(x)
#define NIM_ZoneScopedC(x)
#define NIM_ZoneScopedNC(x, y)

#define NIM_ZoneText(x, y)
#define NIM_ZoneTextV(x, y, z)
#define NIM_ZoneTextF(x, ...)
#define NIM_ZoneTextVF(x, y, ...)
#define NIM_ZoneName(x, y)
#define NIM_ZoneNameV(x, y, z)
#define NIM_ZoneNameF(x, ...)
#define NIM_ZoneNameVF(x, y, ...)
#define NIM_ZoneColor(x)
#define NIM_ZoneColorV(x, y)
#define NIM_ZoneValue(x)
#define NIM_ZoneValueV(x, y)
#define NIM_ZoneIsActive false
#define NIM_ZoneIsActiveV(x) false

#define NIM_FrameMark
#define NIM_FrameMarkNamed(x)
#define NIM_FrameMarkStart(x)
#define NIM_FrameMarkEnd(x)

#define NIM_FrameImage(x, y, z, w, a)

#define NIM_TracyLockable(type, varname) type varname
#define NIM_TracyLockableN(type, varname, desc) type varname
#define NIM_TracySharedLockable(type, varname) type varname
#define NIM_TracySharedLockableN(type, varname, desc) type varname
#define NIM_LockableBase(type) type
#define NIM_SharedLockableBase(type) type
#define NIM_LockMark(x)
#define NIM_LockableName(x, y, z)

#define NIM_TracyPlot(x, y)
#define NIM_TracyPlotConfig(x, y, z, w, a)

#define NIM_TracyMessage(x, y)
#define NIM_TracyMessageL(x)
#define NIM_TracyMessageC(x, y, z)
#define NIM_TracyMessageLC(x, y)
#define NIM_TracyAppInfo(x, y)

#define NIM_TracyAlloc(x, y)
#define NIM_TracyFree(x)
#define NIM_TracyMemoryDiscard(x)
#define NIM_TracySecureAlloc(x, y)
#define NIM_TracySecureFree(x)
#define NIM_TracySecureMemoryDiscard(x)

#define NIM_TracyAllocN(x, y, z)
#define NIM_TracyFreeN(x, y)
#define NIM_TracySecureAllocN(x, y, z)
#define NIM_TracySecureFreeN(x, y)

#define NIM_ZoneNamedS(x, y, z)
#define NIM_ZoneNamedNS(x, y, z, w)
#define NIM_ZoneNamedCS(x, y, z, w)
#define NIM_ZoneNamedNCS(x, y, z, w, a)

#define NIM_ZoneTransientS(x, y, z)
#define NIM_ZoneTransientNS(x, y, z, w)

#define NIM_ZoneScopedS(x)
#define NIM_ZoneScopedNS(x, y)
#define NIM_ZoneScopedCS(x, y)
#define NIM_ZoneScopedNCS(x, y, z)

#define NIM_TracyAllocS(x, y, z)
#define NIM_TracyFreeS(x, y)
#define NIM_TracyMemoryDiscardS(x, y)
#define NIM_TracySecureAllocS(x, y, z)
#define NIM_TracySecureFreeS(x, y)
#define NIM_TracySecureMemoryDiscardS(x, y)

#define NIM_TracyAllocNS(x, y, z, w)
#define NIM_TracyFreeNS(x, y, z)
#define NIM_TracySecureAllocNS(x, y, z, w)
#define NIM_TracySecureFreeNS(x, y, z)

#define NIM_TracyMessageS(x, y, z)
#define NIM_TracyMessageLS(x, y)
#define NIM_TracyMessageCS(x, y, z, w)
#define NIM_TracyMessageLCS(x, y, z)

#define NIM_TracySourceCallbackRegister(x, y)
#define NIM_TracyParameterRegister(x, y)
#define NIM_TracyParameterSetup(x, y, z, w)
#define NIM_TracyIsConnected false
#define NIM_TracyIsStarted false
#define NIM_TracySetProgramName(x)

#define NIM_TracyFiberEnter(x)
#define NIM_TracyFiberEnterHint(x, y)
#define NIM_TracyFiberLeave

#endif