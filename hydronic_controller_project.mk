##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=hydronic_controller_project
ConfigurationName      :=Debug
WorkspacePath          := "/media/odroid/Odroid-C2_Development_Work2/codelite_workspaces"
ProjectPath            := "/media/odroid/Odroid-C2_Development_Work2/Projects/hydronic"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=root
Date                   :=10/07/17
CodeLitePath           :="/home/odroid/.codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="hydronic_controller_project.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)wiringPi $(LibrarySwitch)wiringPiDev $(LibrarySwitch)pthread 
ArLibs                 :=  "wiringPi" "wiringPiDev" "pthread" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -std=c++14 -std=c++11 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/hydronic_startup.cpp$(ObjectSuffix) $(IntermediateDirectory)/AS5601_i2c.cpp$(ObjectSuffix) $(IntermediateDirectory)/user_interface.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/hydronic_startup.cpp$(ObjectSuffix): hydronic_startup.cpp $(IntermediateDirectory)/hydronic_startup.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/odroid/Odroid-C2_Development_Work2/Projects/hydronic/hydronic_startup.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/hydronic_startup.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/hydronic_startup.cpp$(DependSuffix): hydronic_startup.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/hydronic_startup.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/hydronic_startup.cpp$(DependSuffix) -MM "hydronic_startup.cpp"

$(IntermediateDirectory)/hydronic_startup.cpp$(PreprocessSuffix): hydronic_startup.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/hydronic_startup.cpp$(PreprocessSuffix) "hydronic_startup.cpp"

$(IntermediateDirectory)/AS5601_i2c.cpp$(ObjectSuffix): AS5601_i2c.cpp $(IntermediateDirectory)/AS5601_i2c.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/odroid/Odroid-C2_Development_Work2/Projects/hydronic/AS5601_i2c.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/AS5601_i2c.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/AS5601_i2c.cpp$(DependSuffix): AS5601_i2c.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/AS5601_i2c.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/AS5601_i2c.cpp$(DependSuffix) -MM "AS5601_i2c.cpp"

$(IntermediateDirectory)/AS5601_i2c.cpp$(PreprocessSuffix): AS5601_i2c.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/AS5601_i2c.cpp$(PreprocessSuffix) "AS5601_i2c.cpp"

$(IntermediateDirectory)/user_interface.cpp$(ObjectSuffix): user_interface.cpp $(IntermediateDirectory)/user_interface.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/odroid/Odroid-C2_Development_Work2/Projects/hydronic/user_interface.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/user_interface.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/user_interface.cpp$(DependSuffix): user_interface.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/user_interface.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/user_interface.cpp$(DependSuffix) -MM "user_interface.cpp"

$(IntermediateDirectory)/user_interface.cpp$(PreprocessSuffix): user_interface.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/user_interface.cpp$(PreprocessSuffix) "user_interface.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


