##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Static-Release
ProjectName            :=SHIT
ConfigurationName      :=Static-Release
WorkspacePath          := "C:\Users\Spencer\Documents\CodeLiteProjects\SHIT"
ProjectPath            := "C:\Users\Spencer\Documents\CodeLiteProjects\SHIT"
IntermediateDirectory  :=./StaticRelease
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Spencer
Date                   :=04/03/15
CodeLitePath           :="C:\Program Files (x86)\CodeLite"
LinkerName             :=C:/MinGW-4.8.1/bin/g++.exe 
SharedObjectLinkerName :=C:/MinGW-4.8.1/bin/g++.exe -shared -fPIC
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
ObjectsFileList        :="SHIT.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := $(shell wx-config --rcflags)
RcCompilerName         :=C:/MinGW-4.8.1/bin/windres.exe 
LinkOptions            :=  $(shell wx-config --libs) -mwindows
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/MinGW-4.8.1/bin/ar.exe rcu
CXX      := C:/MinGW-4.8.1/bin/g++.exe 
CC       := C:/MinGW-4.8.1/bin/gcc.exe 
CXXFLAGS := -std=c++11 -O2 -Wall $(shell wx-config --cflags) $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/MinGW-4.8.1/bin/as.exe 


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files (x86)\CodeLite
UNIT_TEST_PP_SRC_DIR:=C:\UnitTest++-1.3
WXWIN:=C:\wx\wxWidgets-3.0.1-static
WXCFG:=gcc_lib\mswu
PATH:=C:\MinGW-4.8.1\bin;$PATH
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) $(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) $(IntermediateDirectory)/PlaneInfoHandler.cpp$(ObjectSuffix) $(IntermediateDirectory)/ImagePanel.cpp$(ObjectSuffix) $(IntermediateDirectory)/PipBar.cpp$(ObjectSuffix) $(IntermediateDirectory)/SaveManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/ResearchTree.cpp$(ObjectSuffix) $(IntermediateDirectory)/TreePanel.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/SpecialAircraftPanel.cpp$(ObjectSuffix) $(IntermediateDirectory)/SpecialAircraft.cpp$(ObjectSuffix) $(IntermediateDirectory)/ResearchTreeWindow.cpp$(ObjectSuffix) $(IntermediateDirectory)/SpecialAircraftWindow.cpp$(ObjectSuffix) $(IntermediateDirectory)/SpecialWeapon.cpp$(ObjectSuffix) $(IntermediateDirectory)/SpecialWeaponWindow.cpp$(ObjectSuffix) $(IntermediateDirectory)/SHITFrame.cpp$(ObjectSuffix) $(IntermediateDirectory)/SHITScrolledWindow.cpp$(ObjectSuffix) $(IntermediateDirectory)/SetBuilder.cpp$(ObjectSuffix) $(IntermediateDirectory)/SetPanel.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/win_resources.rc$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./StaticRelease"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix): MainFrame.cpp $(IntermediateDirectory)/MainFrame.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/MainFrame.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MainFrame.cpp$(DependSuffix): MainFrame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MainFrame.cpp$(DependSuffix) -MM "MainFrame.cpp"

$(IntermediateDirectory)/MainFrame.cpp$(PreprocessSuffix): MainFrame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MainFrame.cpp$(PreprocessSuffix) "MainFrame.cpp"

$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix): wxcrafter.cpp $(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/wxcrafter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix): wxcrafter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix) -MM "wxcrafter.cpp"

$(IntermediateDirectory)/wxcrafter.cpp$(PreprocessSuffix): wxcrafter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcrafter.cpp$(PreprocessSuffix) "wxcrafter.cpp"

$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix): wxcrafter_bitmaps.cpp $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/wxcrafter_bitmaps.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix): wxcrafter_bitmaps.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix) -MM "wxcrafter_bitmaps.cpp"

$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(PreprocessSuffix): wxcrafter_bitmaps.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(PreprocessSuffix) "wxcrafter_bitmaps.cpp"

$(IntermediateDirectory)/PlaneInfoHandler.cpp$(ObjectSuffix): PlaneInfoHandler.cpp $(IntermediateDirectory)/PlaneInfoHandler.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/PlaneInfoHandler.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PlaneInfoHandler.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PlaneInfoHandler.cpp$(DependSuffix): PlaneInfoHandler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PlaneInfoHandler.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PlaneInfoHandler.cpp$(DependSuffix) -MM "PlaneInfoHandler.cpp"

$(IntermediateDirectory)/PlaneInfoHandler.cpp$(PreprocessSuffix): PlaneInfoHandler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PlaneInfoHandler.cpp$(PreprocessSuffix) "PlaneInfoHandler.cpp"

$(IntermediateDirectory)/ImagePanel.cpp$(ObjectSuffix): ImagePanel.cpp $(IntermediateDirectory)/ImagePanel.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/ImagePanel.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ImagePanel.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ImagePanel.cpp$(DependSuffix): ImagePanel.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ImagePanel.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ImagePanel.cpp$(DependSuffix) -MM "ImagePanel.cpp"

$(IntermediateDirectory)/ImagePanel.cpp$(PreprocessSuffix): ImagePanel.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ImagePanel.cpp$(PreprocessSuffix) "ImagePanel.cpp"

$(IntermediateDirectory)/PipBar.cpp$(ObjectSuffix): PipBar.cpp $(IntermediateDirectory)/PipBar.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/PipBar.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PipBar.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PipBar.cpp$(DependSuffix): PipBar.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PipBar.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PipBar.cpp$(DependSuffix) -MM "PipBar.cpp"

$(IntermediateDirectory)/PipBar.cpp$(PreprocessSuffix): PipBar.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PipBar.cpp$(PreprocessSuffix) "PipBar.cpp"

$(IntermediateDirectory)/SaveManager.cpp$(ObjectSuffix): SaveManager.cpp $(IntermediateDirectory)/SaveManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/SaveManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SaveManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SaveManager.cpp$(DependSuffix): SaveManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SaveManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SaveManager.cpp$(DependSuffix) -MM "SaveManager.cpp"

$(IntermediateDirectory)/SaveManager.cpp$(PreprocessSuffix): SaveManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SaveManager.cpp$(PreprocessSuffix) "SaveManager.cpp"

$(IntermediateDirectory)/ResearchTree.cpp$(ObjectSuffix): ResearchTree.cpp $(IntermediateDirectory)/ResearchTree.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/ResearchTree.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ResearchTree.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ResearchTree.cpp$(DependSuffix): ResearchTree.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ResearchTree.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ResearchTree.cpp$(DependSuffix) -MM "ResearchTree.cpp"

$(IntermediateDirectory)/ResearchTree.cpp$(PreprocessSuffix): ResearchTree.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ResearchTree.cpp$(PreprocessSuffix) "ResearchTree.cpp"

$(IntermediateDirectory)/TreePanel.cpp$(ObjectSuffix): TreePanel.cpp $(IntermediateDirectory)/TreePanel.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/TreePanel.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TreePanel.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TreePanel.cpp$(DependSuffix): TreePanel.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TreePanel.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TreePanel.cpp$(DependSuffix) -MM "TreePanel.cpp"

$(IntermediateDirectory)/TreePanel.cpp$(PreprocessSuffix): TreePanel.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TreePanel.cpp$(PreprocessSuffix) "TreePanel.cpp"

$(IntermediateDirectory)/SpecialAircraftPanel.cpp$(ObjectSuffix): SpecialAircraftPanel.cpp $(IntermediateDirectory)/SpecialAircraftPanel.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/SpecialAircraftPanel.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SpecialAircraftPanel.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SpecialAircraftPanel.cpp$(DependSuffix): SpecialAircraftPanel.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SpecialAircraftPanel.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SpecialAircraftPanel.cpp$(DependSuffix) -MM "SpecialAircraftPanel.cpp"

$(IntermediateDirectory)/SpecialAircraftPanel.cpp$(PreprocessSuffix): SpecialAircraftPanel.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SpecialAircraftPanel.cpp$(PreprocessSuffix) "SpecialAircraftPanel.cpp"

$(IntermediateDirectory)/SpecialAircraft.cpp$(ObjectSuffix): SpecialAircraft.cpp $(IntermediateDirectory)/SpecialAircraft.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/SpecialAircraft.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SpecialAircraft.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SpecialAircraft.cpp$(DependSuffix): SpecialAircraft.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SpecialAircraft.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SpecialAircraft.cpp$(DependSuffix) -MM "SpecialAircraft.cpp"

$(IntermediateDirectory)/SpecialAircraft.cpp$(PreprocessSuffix): SpecialAircraft.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SpecialAircraft.cpp$(PreprocessSuffix) "SpecialAircraft.cpp"

$(IntermediateDirectory)/ResearchTreeWindow.cpp$(ObjectSuffix): ResearchTreeWindow.cpp $(IntermediateDirectory)/ResearchTreeWindow.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/ResearchTreeWindow.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ResearchTreeWindow.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ResearchTreeWindow.cpp$(DependSuffix): ResearchTreeWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ResearchTreeWindow.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ResearchTreeWindow.cpp$(DependSuffix) -MM "ResearchTreeWindow.cpp"

$(IntermediateDirectory)/ResearchTreeWindow.cpp$(PreprocessSuffix): ResearchTreeWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ResearchTreeWindow.cpp$(PreprocessSuffix) "ResearchTreeWindow.cpp"

$(IntermediateDirectory)/SpecialAircraftWindow.cpp$(ObjectSuffix): SpecialAircraftWindow.cpp $(IntermediateDirectory)/SpecialAircraftWindow.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/SpecialAircraftWindow.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SpecialAircraftWindow.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SpecialAircraftWindow.cpp$(DependSuffix): SpecialAircraftWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SpecialAircraftWindow.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SpecialAircraftWindow.cpp$(DependSuffix) -MM "SpecialAircraftWindow.cpp"

$(IntermediateDirectory)/SpecialAircraftWindow.cpp$(PreprocessSuffix): SpecialAircraftWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SpecialAircraftWindow.cpp$(PreprocessSuffix) "SpecialAircraftWindow.cpp"

$(IntermediateDirectory)/SpecialWeapon.cpp$(ObjectSuffix): SpecialWeapon.cpp $(IntermediateDirectory)/SpecialWeapon.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/SpecialWeapon.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SpecialWeapon.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SpecialWeapon.cpp$(DependSuffix): SpecialWeapon.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SpecialWeapon.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SpecialWeapon.cpp$(DependSuffix) -MM "SpecialWeapon.cpp"

$(IntermediateDirectory)/SpecialWeapon.cpp$(PreprocessSuffix): SpecialWeapon.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SpecialWeapon.cpp$(PreprocessSuffix) "SpecialWeapon.cpp"

$(IntermediateDirectory)/SpecialWeaponWindow.cpp$(ObjectSuffix): SpecialWeaponWindow.cpp $(IntermediateDirectory)/SpecialWeaponWindow.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/SpecialWeaponWindow.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SpecialWeaponWindow.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SpecialWeaponWindow.cpp$(DependSuffix): SpecialWeaponWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SpecialWeaponWindow.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SpecialWeaponWindow.cpp$(DependSuffix) -MM "SpecialWeaponWindow.cpp"

$(IntermediateDirectory)/SpecialWeaponWindow.cpp$(PreprocessSuffix): SpecialWeaponWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SpecialWeaponWindow.cpp$(PreprocessSuffix) "SpecialWeaponWindow.cpp"

$(IntermediateDirectory)/SHITFrame.cpp$(ObjectSuffix): SHITFrame.cpp $(IntermediateDirectory)/SHITFrame.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/SHITFrame.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SHITFrame.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SHITFrame.cpp$(DependSuffix): SHITFrame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SHITFrame.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SHITFrame.cpp$(DependSuffix) -MM "SHITFrame.cpp"

$(IntermediateDirectory)/SHITFrame.cpp$(PreprocessSuffix): SHITFrame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SHITFrame.cpp$(PreprocessSuffix) "SHITFrame.cpp"

$(IntermediateDirectory)/SHITScrolledWindow.cpp$(ObjectSuffix): SHITScrolledWindow.cpp $(IntermediateDirectory)/SHITScrolledWindow.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/SHITScrolledWindow.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SHITScrolledWindow.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SHITScrolledWindow.cpp$(DependSuffix): SHITScrolledWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SHITScrolledWindow.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SHITScrolledWindow.cpp$(DependSuffix) -MM "SHITScrolledWindow.cpp"

$(IntermediateDirectory)/SHITScrolledWindow.cpp$(PreprocessSuffix): SHITScrolledWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SHITScrolledWindow.cpp$(PreprocessSuffix) "SHITScrolledWindow.cpp"

$(IntermediateDirectory)/SetBuilder.cpp$(ObjectSuffix): SetBuilder.cpp $(IntermediateDirectory)/SetBuilder.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/SetBuilder.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SetBuilder.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SetBuilder.cpp$(DependSuffix): SetBuilder.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SetBuilder.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SetBuilder.cpp$(DependSuffix) -MM "SetBuilder.cpp"

$(IntermediateDirectory)/SetBuilder.cpp$(PreprocessSuffix): SetBuilder.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SetBuilder.cpp$(PreprocessSuffix) "SetBuilder.cpp"

$(IntermediateDirectory)/SetPanel.cpp$(ObjectSuffix): SetPanel.cpp $(IntermediateDirectory)/SetPanel.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/SetPanel.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SetPanel.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SetPanel.cpp$(DependSuffix): SetPanel.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SetPanel.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SetPanel.cpp$(DependSuffix) -MM "SetPanel.cpp"

$(IntermediateDirectory)/SetPanel.cpp$(PreprocessSuffix): SetPanel.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SetPanel.cpp$(PreprocessSuffix) "SetPanel.cpp"

$(IntermediateDirectory)/win_resources.rc$(ObjectSuffix): win_resources.rc
	$(RcCompilerName) -i "C:/Users/Spencer/Documents/CodeLiteProjects/SHIT/win_resources.rc" $(RcCmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/win_resources.rc$(ObjectSuffix) $(RcIncludePath)

-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./StaticRelease/


