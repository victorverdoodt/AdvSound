// dsff.cpp : Defines the exported functions for the DLL application.
//

#define LUA_IRRK_VERSION	"1.0.1"

#define LUA_LIB
#define LUA_COMPAT_MODULE
extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
}

#include "stdio.h"
#include "irrKlang.h"


using namespace irrklang;
#pragma comment(lib, "irrKlang.lib")

#include <iostream>
using namespace std;
ISoundEngine* engine;
static int deleteSnd(lua_State *Lua)
{
	ISound* var = (ISound*)lua_touserdata(Lua,-1);
	if (var){
		var->stop();
		var->drop();
		var = NULL;
		lua_pushboolean(Lua,true);
	}else{
		lua_pushboolean(Lua,false);
	}
	return 1;
}

static int getSoundPlayPosition(lua_State *Lua)
{
	ISound* var = (ISound*)lua_touserdata(Lua,-1);
	if (var){
		lua_pushnumber(Lua,var->getPlayPosition());		
	 }
	 else
	 {
		lua_pushboolean(Lua,false);
	 }
 return 1;
}
static int getSoundPlayLen(lua_State *Lua)
{
	ISound* var = (ISound*)lua_touserdata(Lua,-1);
	if (var){     
		lua_pushnumber(Lua,var->getPlayLength());		
	 }
	 else
	 {
		lua_pushboolean(Lua,false);
	 }
 return 1;
}

static int setReverbEnabled(lua_State *Lua)
{    
	lua_pop(Lua, 1);
	int typ = lua_toboolean(Lua, 0);
	lua_pop(Lua, 1);
	ISound* var = (ISound*)lua_touserdata(Lua,0);
	ISoundEffectControl* fx = 0;
	fx = var->getSoundEffectControl();
	if (!fx)
			{
				lua_pushboolean(Lua,false);
				printf("This device or sound does not support sound effects.\n");
				return 0;
			}	
	if (var){
		if (typ == 1)
		{
			
		   fx->enableWavesReverbSoundEffect();
		}else{
	 	   fx->disableWavesReverbSoundEffect();
	     }
		lua_pushboolean(Lua,true);
	 }
	 else
	 {
		lua_pushboolean(Lua,false);
	 }
 return 1;
}

static int setEchoEnabled(lua_State *Lua)
{    
	lua_pop(Lua, 1);
	int typ = lua_toboolean(Lua, 0);
	lua_pop(Lua, 1);
	ISound* var = (ISound*)lua_touserdata(Lua,0);
	ISoundEffectControl* fx = 0;
	fx = var->getSoundEffectControl();
	if (!fx)
			{
				lua_pushboolean(Lua,false);
				printf("This device or sound does not support sound effects.\n");
				
				return 0;
			}	
	if (var){
		if (typ == 1)
		{
		   fx->enableEchoSoundEffect();
		}else{
	 	   fx->disableEchoSoundEffect();
	     }
		lua_pushboolean(Lua,true);
	 }
	 else
	 {
		lua_pushboolean(Lua,false);
	 }
 return 1;
}
static int setDistortionEnabled(lua_State *Lua)
{    
	lua_pop(Lua, 1);
	int typ = lua_toboolean(Lua, 0);
	lua_pop(Lua, 1);
	ISoundEffectControl* fx = 0;
	ISound* var = (ISound*)lua_touserdata(Lua,0);
	fx = var->getSoundEffectControl();
	if (!fx)
			{
				lua_pushboolean(Lua,false);
				printf("This device or sound does not support sound effects.\n");
				return 0;
			}	
	if (var){
		if (typ == 1)
		{
		   fx->enableDistortionSoundEffect();
		}else{
	 	   fx->disableDistortionSoundEffect();
	     }
		lua_pushboolean(Lua,true);
	 }
	 else
	 {
		lua_pushboolean(Lua,false);
	 }
 return 1;
}
static int setPaused(lua_State *Lua)
{    
	lua_pop(Lua, 1);
	int typ = lua_toboolean(Lua, 0);
	lua_pop(Lua, 1);
	ISound* var = (ISound*)lua_touserdata(Lua,0);
	
	if (var){
		if (typ == 1)
		{
		   var->setIsPaused(true);
		}else{
	 	   var->setIsPaused(false);
	     }
		lua_pushboolean(Lua,true);
	 }
	 else
	 {
		lua_pushboolean(Lua,false);
	 }
 return 1;
}

static int setVolume(lua_State *Lua)
{
	lua_pop(Lua, 1);
    float volt = (float)lua_tonumber(Lua,0);
	lua_pop(Lua, 1);
	ISound* var = (ISound*)lua_touserdata(Lua,0);
	if (var){
		var->setVolume(volt);
		lua_pushboolean(Lua,true);
	 }
	 else
	 {
		lua_pushboolean(Lua,false);
	 }
 return 1;
}
static int setSndPlayPos(lua_State *Lua)
{
	lua_pop(Lua, 1);
	irrklang::ik_u32 pos = (irrklang::ik_u32)lua_tonumber(Lua, 0);
	lua_pop(Lua, 1);
	ISound* var = (ISound*)lua_touserdata(Lua,0);
	if (var){
		var->setPlayPosition(pos);
		lua_pushboolean(Lua,true);
	}
	else
	{
		lua_pushboolean(Lua,false);
	}
 return 1;
}
static int setListenerPosition_(lua_State *Lua)
{
	lua_pop(Lua, 1);
	irrklang::ik_f32 z2 = (irrklang::ik_f32)lua_tonumber(Lua, 0);
	lua_pop(Lua, 1);	
	irrklang::ik_f32 y2 = (irrklang::ik_f32)lua_tonumber(Lua, 0);
	lua_pop(Lua, 1);
	irrklang::ik_f32 x2 = (irrklang::ik_f32)lua_tonumber(Lua, 0);
	lua_pop(Lua, 1);
	irrklang::ik_f32 z = (irrklang::ik_f32)lua_tonumber(Lua, 0);
	lua_pop(Lua, 1);
    irrklang::ik_f32 y = (irrklang::ik_f32)lua_tonumber(Lua, 0);
	lua_pop(Lua, 1);
	irrklang::ik_f32 x = (irrklang::ik_f32)lua_tonumber(Lua, 0);
	engine->setListenerPosition(vec3df(x, y,z), vec3df(x2, y2,z2));
	lua_pushboolean(Lua,true);
 return 1;
}
static int setmindis(lua_State *Lua)
{
	float x = (float)lua_tonumber(Lua, 0);
	lua_pop(Lua, 1);
	ISound* var = (ISound*)lua_touserdata(Lua,0);
 	 if (var)
	 {
		var->setMinDistance(x);
	 }
return 1;
}
static int setSndPos(lua_State *Lua)
{
	lua_pop(Lua, 1);
	float z = (float)lua_tonumber(Lua, 0);
	lua_pop(Lua, 1);
    float y = (float)lua_tonumber(Lua, 0);
	lua_pop(Lua, 1);
	float x = (float)lua_tonumber(Lua, 0);
	lua_pop(Lua, 1);
	ISound* var = (ISound*)lua_touserdata(Lua,0);
 	 if (var)
	 {
		//var->setMinDistance(5.0f);		
		var->setPosition(vec3df(x, y,z));		
		lua_pushboolean(Lua,true);
	 }
	 else
	 {
		lua_pushboolean(Lua,false);
	 }
 return 1;
}
static int getVolumeS(lua_State *Lua)
{
	ISound* var = (ISound*)lua_touserdata(Lua,1);
	if (var){	 
		lua_pushnumber(Lua,var->getVolume());	
	 }
	 else
	 {
		lua_pushboolean(Lua,false);
	 }
 return 1;
}

static int ispl9(lua_State *Lua){
	ISound* var = (ISound*)lua_touserdata(Lua,-1);	
	
	if (var->isFinished()){
		lua_pushboolean(Lua,true);
	}else{
		lua_pushboolean(Lua,false);
	}
		return 1;
}
static int ispl(lua_State *Lua){
	ISound* var = (ISound*)lua_touserdata(Lua,-1);	
	
	if (var->getIsPaused()){
		lua_pushboolean(Lua,true);
	}else{
		lua_pushboolean(Lua,false);
	}
		return 1;
}
static int getPaused(lua_State *Lua){
	ISound* var = (ISound*)lua_touserdata(Lua,-1);
	if (var){
		lua_pushboolean(Lua, var->getIsPaused() );
	
	}
	return 1;
}

static int play(lua_State *Lua)
{	
      lua_pop(Lua, 1);
	 int typ2 = lua_toboolean(Lua, 0);
	 lua_pop(Lua, 1);
	 int typ = lua_toboolean(Lua, 0);
	 lua_pop(Lua, 1);
	 const char *name = lua_tostring(Lua, 0);
	 irrklang::vec3df position(0,0,0);
	 bool loop = false;
	 bool paused = false;
	 if (typ == 1)
	 {
		 loop = true;
	 }
	 if (typ2 == 1)
	 {
		 paused = true;
	 }

		ISound* musice = engine->play3D(name,position,loop,paused,false,ESM_AUTO_DETECT,true);
		if (musice)
		{
		lua_pushlightuserdata(Lua,musice);
		musice = NULL;
	}else{		
		lua_pushboolean(Lua,false);
	}
    return 1 ;
}

static const struct luaL_Reg irrk_funcs[] = {
	{"isPlaying",ispl},	 
	{"isFinished",ispl9},
	{"getSoundPlayLen",getSoundPlayLen},
	{"getSoundPlayPosition",getSoundPlayPosition},
	{"setSndPlayPos",setSndPlayPos},	
	{"setSoundMinDistance",setmindis},
	{"setListenerPosition",setListenerPosition_},
	{"setSound3DPosition",setSndPos},
	{"setVolume",setVolume},
	{"getVolume",getVolumeS},
	{"setPaused",setPaused},
	{"isPaused",getPaused},
    {"playMusic",play},
	{"deleteSnd",deleteSnd},
	{"setReverbEnabled",setReverbEnabled},
	{"setEchoEnabled",setEchoEnabled},
	{"setDistortionEnabled",setDistortionEnabled},
  { NULL, NULL },
};



extern "C" int __declspec(dllexport) luaopen_irrklua(lua_State *L)
{
	engine = createIrrKlangDevice();
	luaL_register(L, "irrklua", irrk_funcs);
	return 1;
}

