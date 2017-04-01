#ifndef __ZERO_H__
#define __ZERO_H__

#include "CDevice.h"
#include "CFpsController.h"
#include "CGame.h"
#include "Config.h"
#include "CState.h"
#include "CStateManagement.h"
#include "CViewController.h"
#include "CVSView.h"
#include "SGameConfig.h"
#include "CSprite.h"

#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
#	pragma comment(lib, "zero.lib")
#endif

using namespace GameTutor;

#endif