##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=hydronic_controller_project
ConfigurationName      :=Release
WorkspacePath          := "/media/odroid/Odroid-C2_Development_Work/codelite_workspaces"
ProjectPath            := "/media/odroid/Odroid-C2_Development_Work/Projects/hydronic"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=root
Date                   :=09/04/17
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
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
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
CXXFLAGS :=  -O2 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/hydronic_startup.cpp$(ObjectSuffix) $(IntermediateDirectory)/AS5601_i2c.cpp$(ObjectSuffix) $(IntermediateDirectory)/LCD16x2.cpp$(ObjectSuffix) 



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
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/hydronic_startup.cpp$(ObjectSuffix): hydronic_startup.cpp $(IntermediateDirectory)/hydronic_startup.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/odroid/Odroid-C2_Development_Work/Projects/hydronic/hydronic_startup.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/hydronic_startup.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/hydronic_startup.cpp$(DependSuffix): hydronic_startup.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/hydronic_startup.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/hydronic_startup.cpp$(DependSuffix) -MM "hydronic_startup.cpp"

$(IntermediateDirectory)/hydronic_startup.cpp$(PreprocessSuffix): hydronic_startup.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/hydronic_startup.cpp$(PreprocessSuffix) "hydronic_startup.cpp"

$(IntermediateDirectory)/AS5601_i2c.cpp$(ObjectSuffix): AS5601_i2c.cpp $(IntermediateDirectory)/AS5601_i2c.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/odroid/Odroid-C2_Development_Work/Projects/hydronic/AS5601_i2c.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/AS5601_i2c.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/AS5601_i2c.cpp$(DependSuffix): AS5601_i2c.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/AS5601_i2c.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/AS5601_i2c.cpp$(DependSuffix) -MM "AS5601_i2c.cpp"

$(IntermediateDirectory)/AS5601_i2c.cpp$(PreprocessSuffix): AS5601_i2c.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/AS5601_i2c.cpp$(PreprocessSuffix) "AS5601_i2c.cpp"

$(IntermediateDirectory)/LCD16x2.cpp$(ObjectSuffix): LCD16x2.cpp $(IntermediateDirectory)/LCD16x2.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/odroid/Odroid-C2_Development_Work/Projects/hydronic/LCD16x2.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/LCD16x2.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/LCD16x2.cpp$(DependSuffix): LCD16x2.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/LCD16x2.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/LCD16x2.cpp$(DependSuffix) -MM "LCD16x2.cpp"

$(IntermediateDirectory)/LCD16x2.cpp$(PreprocessSuffix): LCD16x2.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/LCD16x2.cpp$(PreprocessSuffix) "LCD16x2.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


