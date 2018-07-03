TARGET = ltracer.mot
SOURCE_C = src/main.c src/timer.c src/lcd.c
SOURCE_ASM = 


#	ram : RAM上で実行	rom : ROM化
ON_RAM = ram

#	ext：RAM化→プログラムとスタックは外部RAMを使用
#	     ROM化→スタックは外部RAM
#	int：RAM化→プログラムとスタックは内部RAMを使用
#	     ROM化→スタックは内部RAM
#	指定なし：RAM化→プログラムは外部RAM、スタック変更なし
#		  ROM化→スタックは外部RAM
RAM_CAP = ext

CMD_PATH = /usr/local/bin
LIB_PATH = ./src/scripts

CC = $(CMD_PATH)/h8300-hms-gcc
LD = $(CMD_PATH)/h8300-hms-ld
OBJCOPY = $(CMD_PATH)/h8300-hms-objcopy
SIZE = $(CMD_PATH)/h8300-hms-size

TARGET_COFF = $(TARGET:.mot=.coff)
MAP_FILE = $(TARGET:.mot=.map)

# binary : binary, srec : Motorola S record, ihex : Intel Hex
OUTPUT_FORMAT = -O srec --srec-forceS3

INCLUDES = -I. -Iinclude

#	-mh：H8/300Hシリーズ指定
#	-mrelax：条件分岐コードの最適化
#	-mint32：int型変数のビット数指定
#	-O2：gccの最適化レベルの指定
#	-Wall：コンパイル時の警告メッセージの選択(全て)
CFLAGS = -mh -mrelax -mint32 -O2 $(INCLUDES) -Wall

LDSCRIPT = $(LIB_PATH)/h8-3069-ram.x
STARTUP = $(LIB_PATH)/ramcrt-ext.s

# リンク時のコンパイラオプションの指定
#	-T filename：リンカスクリプトファイルの指定
#	-nostartfiles：標準のスタートアップを使用しない
#	-Wl,パラメータ,…：リンカに渡すパラメータ指定
#		-Map mapfilename：メモリマップをmapfilenameに出力
LDFLAGS = -T $(LDSCRIPT) -nostartfiles -Wl,-Map,$(MAP_FILE)

OBJ = $(STARTUP:.s=.o) $(SOURCE_C:.c=.o) $(SOURCE_ASM:.s=.o)

$(TARGET) : $(TARGET_COFF)
	$(OBJCOPY) -v $(OUTPUT_FORMAT) $(TARGET_COFF) $(TARGET)

$(TARGET_COFF) : $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $(TARGET_COFF)
	$(SIZE) -Ax $(TARGET_COFF)

clean :
	rm -f $(shell find . -name '*.o') $(TARGET) $(TARGET_COFF) $(MAP_FILE)

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<
.s.o:
	$(CC) -c $(CFLAGS) -o $@ $<
