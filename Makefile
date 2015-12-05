rwildcard = $(foreach d, $(wildcard $1*), $(filter $(subst *, %, $2), $d) $(call rwildcard, $d/, $2))
getSize = $(lastword $(shell arm-none-eabi-size -A --target=binary $1))

# This should be set externally
name ?= Cakes.dat
filepath ?=
dir_out ?= .

CC := arm-none-eabi-gcc
AS := arm-none-eabi-as
OC := arm-none-eabi-objcopy

dir_source := source
dir_build := build
dir_rop3ds := rop3ds

ARM9FLAGS := -mcpu=arm946e-s -march=armv5te
ARM11FLAGS := -mcpu=mpcore
ASFLAGS := -mlittle-endian
CFLAGS := -marm -mpic-data-is-text-relative $(ASFLAGS) -O2 -std=c11 -MMD -MP -fpic -fshort-wchar -Wall -Wextra -Wno-main -DLAUNCHER_PATH='"$(filepath)$(name)"'
LDFLAGS := -nostartfiles -flto -fwhole-program

get_objects = $(patsubst $(dir_source)/%.s, $(dir_build)/%.o, \
			  $(patsubst $(dir_source)/%.c, $(dir_build)/%.o, $1))

objects := $(call get_objects, $(wildcard $(dir_source)/*.s $(dir_source)/*.c))

objects_fw_ctr := $(dir_build)/firmcompat/ctr.o
objects_fw_ktr := $(dir_build)/firmcompat/ktr.o

objects_payload_table := $(dir_build)/payload/jump_table.o
objects_payload_arm9 := $(call get_objects, \
				   $(call rwildcard, $(dir_source)/payload/arm9, *.s *.c))

versions := mset_4x mset_4x_dg mset_4x_ndg mset_6x

rops := $(foreach ver, $(versions), $(dir_build)/$(ver)/rop.dat)

FW_CTR := $(dir_build)/firmcompat/ctr.bin
FW_KTR := $(dir_build)/firmcompat/ktr.bin
PAYLOAD_TABLE := $(dir_build)/payload/jump_table.bin

.SECONDARY:

.PHONY: all
all: launcher

.PHONY: launcher
launcher: PAYLOAD_PRIMARY := $(PAYLOAD)
launcher: $(dir_out)/$(name)

.PHONY: bigpayload
bigpayload: PAYLOAD_PRIMARY := $(dir_build)/payload/arm9/main.bin
bigpayload: $(dir_out)/$(name)
	dd if=$(PAYLOAD) of=$< seek=160 conv=notrunc

.PHONY: clean
clean:
	rm -rf $(dir_out)/$(name) $(dir_build)

# Throw everything together
$(dir_out)/$(name): $(rops) $(dir_build)/main.bin $(FW_CTR) $(FW_KTR)
	touch $@
	dd if=$(dir_build)/main.bin of=$@ bs=512 seek=0
	dd if=$(dir_build)/mset_4x/rop.dat of=$@ bs=512 seek=32
	dd if=$(dir_build)/mset_4x_dg/rop.dat of=$@ bs=512 seek=34
	dd if=$(dir_build)/mset_4x_ndg/rop.dat of=$@ bs=512 seek=36
	dd if=$(dir_build)/mset_6x/rop.dat of=$@ bs=512 seek=40
	dd if=$(FW_CTR) of=$@ bs=512 seek=53
	dd if=$(FW_KTR) of=$@ bs=512 seek=54
	dd if=$(PAYLOAD_TABLE) of=$@ bs=512 seek=144
	cat $(PAYLOAD_PRIMARY) >> $@


# Create bin from elf
$(dir_build)/%.bin: $(dir_build)/%.elf
	$(OC) -S -O binary $< $@

$(dir_build)/%.dat: $(dir_build)/%.elf
	$(OC) -S -O binary $< $@

# MSET ROPs
$(dir_build)/mset_%/rop.elf: $(dir_build)/mset_%/rop.o $(dir_build)/main.elf
	$(LINK.o) -Wl,-R$(dir_build)/main.elf $(OUTPUT_OPTION) $<

$(dir_build)/mset_%/rop.o: rop.S
	@mkdir -p "$(@D)"
	$(COMPILE.c) -DMSET_$(shell echo $* | tr a-z A-Z) $< -o $@

# firmcompat
$(dir_build)/firmcompat/ctr.elf: $(objects_fw_ctr)
	$(LINK.o) $(OUTPUT_OPTION) $^

$(dir_build)/firmcompat/ktr.elf: $(objects_fw_ktr)
	$(LINK.o) $(OUTPUT_OPTION) $^

# jump_table payload
$(dir_build)/payload/jump_table.elf: $(objects_payload_table)
	$(LINK.o) $(OUTPUT_OPTION) $^

# Different flags for different things
$(dir_build)/payload/arm9/main.elf: ASFLAGS := $(ARM9FLAGS) $(ASFLAGS)
$(dir_build)/payload/arm9/main.elf: CFLAGS := $(ARM9FLAGS) $(CFLAGS)
$(dir_build)/payload/arm9/main.elf: $(objects_payload_arm9)
	# FatFs requires libgcc for __aeabi_uidiv
	$(LINK.o) -T linker_payload.ld $(OUTPUT_OPTION) $^

# The arm11 payload
$(dir_build)/main.elf: $(objects)
	$(LINK.o) -T linker.ld $(OUTPUT_OPTION) $^

# Fatfs requires to be built in thumb
$(dir_build)/payload/arm9/fatfs/%.o: $(dir_source)/payload/arm9/fatfs/%.c
	@mkdir -p "$(@D)"
	$(COMPILE.c) -mthumb -mthumb-interwork -Wno-unused-function $(OUTPUT_OPTION) $<

$(dir_build)/payload/arm9/fatfs/%.o: $(dir_source)/payload/arm9/fatfs/%.s
	@mkdir -p "$(@D)"
	$(COMPILE.s) -mthumb -mthumb-interwork $(OUTPUT_OPTION) $<

$(dir_build)/payload/%.o: $(dir_source)/payload/%.c
	@mkdir -p "$(@D)"
	$(COMPILE.c) -flto $(OUTPUT_OPTION) $<

.SECONDEXPANSION:
$(dir_build)/payload/%.o: $(dir_source)/payload/%.s
	@mkdir -p "$(@D)"
	$(COMPILE.s) $(OUTPUT_OPTION) $<

$(dir_build)/firmcompat/%.o: $(dir_source)/firmcompat/%.c
	@mkdir -p "$(@D)"
	$(COMPILE.c) -flto $(OUTPUT_OPTION) $<

.SECONDEXPANSION:
$(dir_build)/%.o: $(dir_source)/$$(notdir $$*).c $(FW_CTR) $(FW_KTR) $(PAYLOAD_TABLE) $$(PAYLOAD_PRIMARY)
	@mkdir -p "$(@D)"
	$(COMPILE.c) -flto $(ARM11FLAGS) -DFW_CTR_SIZE=$(call getSize,$(FW_CTR)) -DFW_KTR_SIZE=$(call getSize,$(FW_KTR)) -DPAYLOAD_TABLE_SIZE=$(call getSize,$(PAYLOAD_TABLE)) -DPAYLOAD_ARM9_SIZE=$(call getSize,$(PAYLOAD_PRIMARY)) $(OUTPUT_OPTION) $<

.SECONDEXPANSION:
$(dir_build)/%.o: $(dir_source)/$$(notdir $$*).S
	@mkdir -p "$(@D)"
	$(COMPILE.c) $(ARM11FLAGS) $(OUTPUT_OPTION) $<

.SECONDEXPANSION:
$(dir_build)/%.o: $(dir_source)/$$(notdir $$*).s
	@mkdir -p "$(@D)"
	$(COMPILE.s) $(ARM11FLAGS) $(OUTPUT_OPTION) $<

include $(call rwildcard, $(dir_build), *.d)
