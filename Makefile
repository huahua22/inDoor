TARGET = inDoor

SRCDIRS   =  $(shell find . -maxdepth 3 -type d)
CC:=arm-openwrt-linux-gcc
STAGING_DIR=/home/xwr/tmp/target
INCLUDES	:=  $(foreach dir,$(SRCDIRS),-I$(dir))            \
		   -I$(STAGING_DIR)/usr/include/allwinner/include \
		   -I$(STAGING_DIR)/usr/include/allwinner \
			 -I$(STAGING_DIR)/usr/include/

SRCS			= $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c))
OBJS			= $(SRCS:.c=.o)

#LOCAL_LDFLAGS = -lminigui_ths -luapi -lts -ljpeg -lpng -lpthread -lmgi -lmgplus -lfreetype \
#    -lasound -ldl -lm -lz -luapi -lrt -lc -lcdx_common\
#		-ltrecorder -ltplayer -lxplayer -lcdc_vdecoder -ladecoder -lcdc_sdecoder -lcdc_base -lcdc_ve -lcdc_memory \
#		-lcdx_parser  -lcdx_playback -lcdx_stream -lcdx_base -lawrecorder -laencoder \
#		-lcdx_muxer -ljpegdecode  -ltmetadataretriever
LOCAL_LDFLAGS = -L$(STAGING_DIR)/usr/lib
LOCAL_LDFLAGS += -lminigui_ths -luapi -lts -ljpeg -lpng -lpthread -lmgi -lmgplus -lfreetype \
    -ldl -lm -lz -luapi -lrt -lc -luapi -lbz2 -ltplayer -lxplayer -lvdecoder -ladecoder -lsubdecoder -lcdc_base -lVE -lMemAdapter\
    -lcdx_parser -lcdx_playback -lcdx_stream -lcdx_base\
    -lasound -lvideoengine -lcdx_common 
%.o: %.c
	$(CC) $(INCLUDES) $(CFLAGS) $(LDFLAGS) $(LOCAL_CFLAGS) $(LOCAL_LDFLAGS) -c -o $@ $<

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(LDFLAGS) $(LOCAL_CFLAGS) $(LOCAL_LDFLAGS) /home/xwr/tmp/target/usr/liba/libtinyalsa.a /home/xwr/tmp/target/usr/liba/libspeexdsp.a

all:install

install:$(TARGET)
	@mkdir -p $(CONFIG_PREFIX)/bin
	@cp $(TARGET) $(CONFIG_PREFIX)/bin

clean:
	-rm -rf $(OBJS) $(TARGET)
.PHONY:all clean $(TARGET) install
