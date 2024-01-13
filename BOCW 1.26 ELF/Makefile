LFILE = ./Linker

CC		:=	gcc
AS		:=	gcc
OBJCOPY	:=	objcopy
ODIR	:=	build
SDIR	:=	source
IDIRS	:=	-I. -Iinclude
LDIRS	:=	-L. -Llib
CFLAGS	:=	$(IDIRS) $(LDIRS) -O3 -g -w -std=gnu++11 -fno-builtin -fno-inline-small-functions -fno-exceptions -fno-asynchronous-unwind-tables -nostartfiles -nostdlib -w -masm=intel -march=btver2 -mtune=btver2 -m64 -mabi=sysv -mcmodel=small -mstackrealign -fPIE
SFLAGS	:=	-nostartfiles -nostdlib -masm=intel -march=btver2 -mtune=btver2 -m64 -mabi=sysv -mcmodel=small
LFLAGS	:=	-Xlinker -T $(LFILE) -Wl,--build-id=none -mstackrealign -pie
CFILES	:=	$(wildcard *.cpp)
SFILES	:=	$(wildcard $(SDIR)/*.s)
OBJS	:=	$(patsubst %.cpp, $(ODIR)/%.o, $(CFILES)) $(patsubst $(SDIR)/%.s, $(ODIR)/%.o, $(SFILES))

TARGET = BOCW_0126_PS5.elf

$(TARGET): $(ODIR) $(OBJS)
	$(CC) crt0.s $(ODIR)/*.o -o $(TARGET) $(CFLAGS) $(LFLAGS)
	
$(ODIR)/%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(ODIR)/%.o: $(SDIR)/%.s
	$(AS) -c -o $@ $< $(SFLAGS)

$(ODIR):
	@mkdir $@

.PHONY: clean

clean:
	rm -f $(TARGET) $(ODIR)/*.o