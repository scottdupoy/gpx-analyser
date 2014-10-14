TARGET = GpxAnalyser
TARGET_TYPE = exe
PROJECTS = $(TARGET)

BIN_DIR = bin

BUILD_TARGETS = $(foreach project,$(PROJECTS),$(project)_build)
CLEAN_TARGETS = $(foreach project,$(PROJECTS),$(project)_clean)

LOCAL_TARGET = $(BIN_DIR)/$(TARGET).$(TARGET_TYPE)

all : build

build : $(BIN_DIR) $(BUILD_TARGETS) copy_local

clean : $(CLEAN_TARGETS) clean_local

rebuild : clean build

%_build :
	$(eval PROJECT := $(patsubst %_build,%,$@))
	@make --no-print-directory -C projects/$(PROJECT) build

%_clean :
	$(eval PROJECT := $(patsubst %_clean,%,$@))
	@make --no-print-directory -C projects/$(PROJECT) clean

$(BIN_DIR) :
	@mkdir $(BIN_DIR)
	
clean_local :
	@echo Deleting directory: ./$(BIN_DIR)
	@rm -rf $(BIN_DIR)
	
copy_local :
	@echo Copying any updated $(TARGET) files to $(BIN_DIR)/
	@rsync -ur projects/$(TARGET)/$(BIN_DIR)/ $(BIN_DIR)/
