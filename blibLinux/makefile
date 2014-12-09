#----------------------------------------------------------------------------------------------------
# makefile for linux blib implementation. 
# date 21-11-2014
# programmer: bolke
#----------------------------------------------------------------------------------------------------

GPP=g++ -std=c++0x -D LINUX
GPP_COMPILE=$(GPP) -c
GPP_CORE_LIB= -Wl,--no-as-needed  -lrt -lpthread
AR_STATIC_LIB=ar rvcs
MKDIR_SAVE=mkdir -p
CP_SAVE=cp -fu
RM_SAVE=rm -f
MV_SAVE=mv -f
ECHO=echo
ECHO_NO_NL=echo -n
BUILD_DATE=`date +'%y.%m.%d'`

OBJ_DIR=./obj/
LOG_DIR=./log/
BUILD_DIR=./build/
LIB_DIR=./lib/
INC_DIR=./inc/
SRC_DIR=../blib/

CORE_EXT=core/
CORE_OBJ_DIR=$(OBJ_DIR)$(CORE_EXT)
CORE_LOG_DIR=$(LOG_DIR)$(CORE_EXT)
CORE_BUILD_DIR=$(BUILD_DIR)$(CORE_EXT)
CORE_LIB_DIR=$(LIB_DIR)$(CORE_EXT)
CORE_INC_DIR=$(INC_DIR)$(CORE_EXT)
CORE_SRC_DIR=$(SRC_DIR)
CORE_INCLUDE=-I$(CORE_INC_DIR)
CORE_MODULES=core_Basis core_Threading core_Devices

BLIB_EXT=blib/
BLIB_OBJ_DIR=$(OBJ_DIR)$(BLIB_EXT)
BLIB_LOG_DIR=$(LOG_DIR)$(BLIB_EXT)
BLIB_BUILD_DIR=$(BUILD_DIR)$(BLIB_EXT)
BLIB_LIB_DIR=$(LIB_DIR)$(BLIB_EXT)
BLIB_INC_DIR=$(INC_DIR)$(BLIB_EXT)
BLIB_SRC_DIR=$(SRC_DIR)
BLIB_INCLUDE=-I$(BLIB_INC_DIR)
BLIB_SYSTEM_HEADER=$(BLIB_INC_DIR)BlibHeaders.h
BLIB_MODULES=blib_Messages blib_Network blib_FileIO blib_Security blib_Serial blib_Xml
#blib_Sql and blib_Webserving not compiled

all: core_lib blib_lib

clean: .core_clean .blib_clean

#----------------------------------------------------------------------------------------------------
# core starts here, three seperate parts, basis, devices and threading. Together they form, Captain 
# Pla ... uhm, core.
#----------------------------------------------------------------------------------------------------

.core_clean:
	$(RM_SAVE) $(CORE_OBJ_DIR)*.*
	$(RM_SAVE) $(CORE_LOG_DIR)*.*
	$(RM_SAVE) $(CORE_BUILD_DIR)*.*
	$(RM_SAVE) $(CORE_LIB_DIR)*.*
	$(RM_SAVE) $(CORE_BUILD_DIR)inc/*.*
	$(RM_SAVE) $(CORE_INC_DIR)*.*

.core_prep:
	$(MKDIR_SAVE) $(CORE_OBJ_DIR)
	$(MKDIR_SAVE) $(CORE_LOG_DIR)
	$(MKDIR_SAVE) $(CORE_BUILD_DIR)
	$(MKDIR_SAVE) $(CORE_BUILD_DIR)inc/
	$(MKDIR_SAVE) $(CORE_LIB_DIR)
	$(MKDIR_SAVE) $(CORE_INC_DIR)

core_lib: .core_clean $(CORE_MODULES) core_Core
	$(AR_STATIC_LIB) $(CORE_LIB_DIR)Core.a $(CORE_OBJ_DIR)*.o >> $(CORE_LOG_DIR)lib.log 2>>$(CORE_LOG_DIR)lib.err
	$(CP_SAVE) $(CORE_INC_DIR)*.h $(CORE_BUILD_DIR)inc/
	$(CP_SAVE) $(CORE_LIB_DIR)Core.a $(CORE_BUILD_DIR)

core_%:
	$(eval TARGET=$(subst core_,,$@))
	$(MAKE) .core_prep
	$(CP_SAVE) $(CORE_SRC_DIR)$(TARGET)/*.h $(CORE_INC_DIR)
	$(GPP_COMPILE) $(CORE_SRC_DIR)$(TARGET)/*.cpp $(CORE_INCLUDE) $(GPP_CORE_LIB) > $(CORE_LOG_DIR)$(TARGET).log 2>$(CORE_LOG_DIR)$(TARGET).err 
	$(MV_SAVE) *.o $(CORE_OBJ_DIR) >> $(CORE_LOG_DIR)$(TARGET).log 2>$(CORE_LOG_DIR)$(TARGET).err

#----------------------------------------------------------------------------------------------------
# blib starts here, core should have been build. if not, use build all, which builds core and blib.
#----------------------------------------------------------------------------------------------------

.blib_clean:
	$(RM_SAVE) $(BLIB_OBJ_DIR)*.*
	$(RM_SAVE) $(BLIB_LOG_DIR)*.*
	$(RM_SAVE) $(BLIB_BUILD_DIR)*.*
	$(RM_SAVE) $(BLIB_LIB_DIR)*.*
	$(RM_SAVE) $(BLIB_BUILD_DIR)inc/*.*
	$(RM_SAVE) $(BLIB_INC_DIR)*.*

.blib_prep:
	$(MKDIR_SAVE) $(BLIB_OBJ_DIR)
	$(MKDIR_SAVE) $(BLIB_LOG_DIR)
	$(MKDIR_SAVE) $(BLIB_BUILD_DIR)
	$(MKDIR_SAVE) $(BLIB_BUILD_DIR)inc/
	$(MKDIR_SAVE) $(BLIB_LIB_DIR)
	$(MKDIR_SAVE) $(BLIB_INC_DIR)

blib_lib: .blib_clean .blib_headers $(BLIB_MODULES) blib_static_lib

blib_%:
	$(eval TARGET=$(subst blib_,,$@))
	$(MAKE) .blib_prep
	$(CP_SAVE) $(BLIB_SRC_DIR)$(TARGET)/*.h $(BLIB_INC_DIR)
	$(GPP_COMPILE) $(BLIB_SRC_DIR)$(TARGET)/*.cpp $(BLIB_INCLUDE) > $(BLIB_LOG_DIR)$(TARGET).log 2>$(BLIB_LOG_DIR)$(TARGET).err
	$(MV_SAVE) *.o $(BLIB_OBJ_DIR) >> $(BLIB_LOG_DIR)$(TARGET).log 2>>$(BLIB_LOG_DIR)$(TARGET).err
	$(ECHO) '#include "$(TARGET).h"' >> $(BLIB_SYSTEM_HEADER)

.blib_headers: .blib_prep
	$(CP_SAVE) $(CORE_INC_DIR)*.h $(BLIB_INC_DIR)
	$(CP_SAVE) $(BLIB_SRC_DIR)Blib.h $(BLIB_INC_DIR)

blib_static_lib:
	$(AR_STATIC_LIB) $(BLIB_LIB_DIR)Blib.a $(BLIB_OBJ_DIR)*.o $(CORE_OBJ_DIR)*.o > $(BLIB_LOG_DIR)blib.log 2>$(BLIB_LOG_DIR)blib.err
	$(CP_SAVE) $(BLIB_LIB_DIR)Blib.a $(BLIB_BUILD_DIR)
	$(CP_SAVE) $(BLIB_INC_DIR)*.h $(BLIB_BUILD_DIR)inc/
