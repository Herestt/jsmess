/***************************************************************************

        SAPI-1 driver by Miodrag Milanovic

        09/09/2008 Preliminary driver.

        07/12/2010 Added some code to allow sapizps3 to read its rom.
        With no available docs, the i/o ports are a guess. The ram
        allocation is based on the actions of the various bios roms.
        Port 25 is used as a jump vector. in a,(25); ld l,a; jp(hl).
        According to wikipedia, e800+ is the videoram area, and the
        number of columns is 64.

****************************************************************************/


#include "emu.h"
#include "cpu/i8085/i8085.h"
#include "cpu/z80/z80.h"
#include "includes/sapi1.h"
#include "devices/messram.h"

static UINT8 sapizps3_25;

/* switch out the rom shadow */
static WRITE8_HANDLER( sapizps3_00_w )
{
	memory_set_bank(space->machine, "bank1", 0);
}

/* to stop execution in random ram */
static READ8_HANDLER( sapizps3_25_r )
{
	return sapizps3_25;
}

static WRITE8_HANDLER( sapizps3_25_w )
{
	sapizps3_25 = data & 0xfc; //??
}



/* Address maps */
static ADDRESS_MAP_START(sapi1_mem, ADDRESS_SPACE_PROGRAM, 8)
	ADDRESS_MAP_UNMAP_HIGH
	AM_RANGE(0x0000, 0x0fff) AM_ROM
	AM_RANGE(0x1000, 0x1fff) AM_ROM // Extension ROM
	AM_RANGE(0x2000, 0x23ff) AM_RAM
	AM_RANGE(0x2400, 0x27ff) AM_READWRITE(sapi1_keyboard_r, sapi1_keyboard_w) // PORT 0 - keyboard
	//AM_RANGE(0x2800, 0x2bff) AM_NOP // PORT 1
	//AM_RANGE(0x2c00, 0x2fff) AM_NOP // PORT 2
	//AM_RANGE(0x3000, 0x33ff) AM_NOP // 3214
	AM_RANGE(0x3800, 0x3fff) AM_RAM AM_BASE_MEMBER(sapi1_state, sapi_video_ram) // AND-1 (video RAM)
	AM_RANGE(0x4000, 0x7fff) AM_RAM // REM-1
ADDRESS_MAP_END

static ADDRESS_MAP_START( sapi1_io, ADDRESS_SPACE_IO, 8 )
	ADDRESS_MAP_UNMAP_HIGH
ADDRESS_MAP_END

static ADDRESS_MAP_START(sapizps3_mem, ADDRESS_SPACE_PROGRAM, 8)
	ADDRESS_MAP_UNMAP_HIGH
	AM_RANGE(0x0000, 0x07ff) AM_RAM AM_RAMBANK("bank1")
	AM_RANGE(0x0800, 0xe7ff) AM_RAM
	AM_RANGE(0xe800, 0xefff) AM_RAM AM_BASE_MEMBER(sapi1_state, sapi_video_ram)
	AM_RANGE(0xf000, 0xf7ff) AM_RAM
	AM_RANGE(0xf800, 0xfdff) AM_ROM
	AM_RANGE(0xfe00, 0xffff) AM_RAM
ADDRESS_MAP_END

static ADDRESS_MAP_START( sapizps3_io, ADDRESS_SPACE_IO, 8 )
	ADDRESS_MAP_UNMAP_HIGH
	ADDRESS_MAP_GLOBAL_MASK(0xff)
	AM_RANGE(0x00, 0x00) AM_WRITE(sapizps3_00_w)
	AM_RANGE(0x25, 0x25) AM_READWRITE(sapizps3_25_r,sapizps3_25_w)
ADDRESS_MAP_END

/* Input ports */
static INPUT_PORTS_START( sapi1 )
	PORT_START("LINE0")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_V) PORT_CHAR('V')
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_G) PORT_CHAR('G')
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_T) PORT_CHAR('T')
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_5) PORT_CHAR('5') PORT_CHAR('~')
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_B) PORT_CHAR('B') PORT_CHAR(';')
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_H) PORT_CHAR('H') PORT_CHAR('+')
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_Y) PORT_CHAR('Y') PORT_CHAR('/')
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_6) PORT_CHAR('6') PORT_CHAR('\'')

	PORT_START("LINE1")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_C) PORT_CHAR('C')
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_F) PORT_CHAR('F')
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_R) PORT_CHAR('R')
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_4) PORT_CHAR('4') PORT_CHAR('\xA4')
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_N) PORT_CHAR('N') PORT_CHAR(',')
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_J) PORT_CHAR('J') PORT_CHAR('-')
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_U) PORT_CHAR('U') PORT_CHAR(':')
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_7) PORT_CHAR('7') PORT_CHAR('<')

	PORT_START("LINE2")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_X) PORT_CHAR('X')
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_D) PORT_CHAR('D')
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_E) PORT_CHAR('E')
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_3) PORT_CHAR('3') PORT_CHAR('"')
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_M) PORT_CHAR('M') PORT_CHAR('.')
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_K) PORT_CHAR('K') PORT_CHAR('*')
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_I) PORT_CHAR('I') PORT_CHAR('@')
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_8) PORT_CHAR('8') PORT_CHAR('>')

	PORT_START("LINE3")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_Z) PORT_CHAR('Z')
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_S) PORT_CHAR('S')
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_W) PORT_CHAR('W')
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_2) PORT_CHAR('2') PORT_CHAR('?')
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_SPACE) PORT_CHAR(' ')
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_L) PORT_CHAR('L') PORT_CHAR('=')
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_O) PORT_CHAR('O') PORT_CHAR('#')
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_9) PORT_CHAR('9') PORT_CHAR('(')

	PORT_START("LINE4")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Shift") PORT_CODE(KEYCODE_LSHIFT) PORT_CODE(KEYCODE_RSHIFT) PORT_CHAR(UCHAR_SHIFT_1)
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_A) PORT_CHAR('A')
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_Q) PORT_CHAR('Q')
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_1) PORT_CHAR('1') PORT_CHAR('!')
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Del") PORT_CODE(KEYCODE_BACKSPACE) PORT_CHAR(8)
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_ENTER) PORT_CHAR(13)
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_P) PORT_CHAR('P')
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_0) PORT_CHAR('0') PORT_CHAR(')')
INPUT_PORTS_END

/* Machine driver */
static MACHINE_CONFIG_START( sapi1, sapi1_state )
	/* basic machine hardware */
	MDRV_CPU_ADD("maincpu", I8080, 2000000)
	MDRV_CPU_PROGRAM_MAP(sapi1_mem)
	MDRV_CPU_IO_MAP(sapi1_io)

	MDRV_MACHINE_START( sapi1 )
	MDRV_MACHINE_RESET( sapi1 )

	/* video hardware */
	MDRV_SCREEN_ADD("screen", RASTER)
	MDRV_SCREEN_REFRESH_RATE(50)
	MDRV_SCREEN_VBLANK_TIME(ATTOSECONDS_IN_USEC(2500)) /* not accurate */
	MDRV_SCREEN_FORMAT(BITMAP_FORMAT_INDEXED16)
	MDRV_SCREEN_SIZE(40*6, 24*9)
	MDRV_SCREEN_VISIBLE_AREA(0, 40*6-1, 0, 24*9-1)

	MDRV_PALETTE_LENGTH(2)
	MDRV_PALETTE_INIT(black_and_white)

	MDRV_VIDEO_START(sapi1)
	MDRV_VIDEO_UPDATE(sapi1)

	/* internal ram */
	MDRV_RAM_ADD("messram")
	MDRV_RAM_DEFAULT_SIZE("64K")
MACHINE_CONFIG_END

static MACHINE_CONFIG_START( sapizps3, sapi1_state )
	/* basic machine hardware */
	MDRV_CPU_ADD("maincpu", Z80, 2000000)
	MDRV_CPU_PROGRAM_MAP(sapizps3_mem)
	MDRV_CPU_IO_MAP(sapizps3_io)

	MDRV_MACHINE_START( sapi1 )
	MDRV_MACHINE_RESET( sapizps3 )

	/* video hardware */
	MDRV_SCREEN_ADD("screen", RASTER)
	MDRV_SCREEN_REFRESH_RATE(50)
	MDRV_SCREEN_VBLANK_TIME(ATTOSECONDS_IN_USEC(2500)) /* not accurate */
	MDRV_SCREEN_FORMAT(BITMAP_FORMAT_INDEXED16)
	MDRV_SCREEN_SIZE(80*6, 24*9)
	MDRV_SCREEN_VISIBLE_AREA(0, 80*6-1, 0, 24*9-1)

	MDRV_PALETTE_LENGTH(2)
	MDRV_PALETTE_INIT(black_and_white)

	MDRV_VIDEO_START(sapizps3)
	MDRV_VIDEO_UPDATE(sapizps3)

	/* internal ram */
	MDRV_RAM_ADD("messram")
	MDRV_RAM_DEFAULT_SIZE("64K")
MACHINE_CONFIG_END

/* ROM definition */

ROM_START( sapi1 )
	ROM_REGION( 0x10000, "maincpu", ROMREGION_ERASEFF )
	ROM_SYSTEM_BIOS( 0, "mb1", "MB1" )
	ROMX_LOAD( "sapi1.rom", 0x0000, 0x1000, CRC(c6e85b01) SHA1(2a26668249c6161aef7215a1e2b92bfdf6fe3671), ROM_BIOS(1))
	ROM_SYSTEM_BIOS( 1, "mb2", "MB2 (ANK-1)" )
	ROMX_LOAD( "mb2_4.bin", 0x0000, 0x1000, CRC(a040b3e0) SHA1(586990a07a96323741679a11ff54ad0023da87bc), ROM_BIOS(2))
	ROM_SYSTEM_BIOS( 2, "mb3", "MB3 (Consul)" )
	ROMX_LOAD( "mb3_1.bin", 0x0000, 0x1000, CRC(be895f88) SHA1(7fc2a92f41d978a9f0ccd0e235ea3c6146adfb6f), ROM_BIOS(3))
ROM_END

ROM_START( sapizps2 )
	ROM_REGION( 0x10000, "maincpu", ROMREGION_ERASEFF )
	ROM_SYSTEM_BIOS( 0, "v4", "MIKOS 4" )
	ROMX_LOAD( "36.bin", 0x0000, 0x0800, CRC(a27f340a) SHA1(d07d208fcbe428897336c17197d3e8fb52181f38), ROM_BIOS(1))
	ROMX_LOAD( "37.bin", 0x0800, 0x0800, CRC(30daa708) SHA1(66e990c40788ee25cf6cabd4842a78daf4fcdddd), ROM_BIOS(1))
	ROM_SYSTEM_BIOS( 1, "v5", "MIKOS 5" )
	ROMX_LOAD( "mikos5_1.bin", 0x0000, 0x0800, CRC(c2a83ca3) SHA1(a3678253d7690c89945e791ea0f8e15b081c9126), ROM_BIOS(2))
	ROMX_LOAD( "mikos5_2.bin", 0x0800, 0x0800, CRC(c4458a04) SHA1(0cc909323f0e6507d95e57ea39e1deb8bd57bf89), ROM_BIOS(2))
	ROMX_LOAD( "mikos5_3.bin", 0x1000, 0x0800, CRC(efb499f3) SHA1(78f0ca3ff10d7af4ae94ab820723296beb035f8f), ROM_BIOS(2))
	ROMX_LOAD( "mikos5_4.bin", 0x1800, 0x0800, CRC(4d90e9be) SHA1(8ec554198697550a49432e8210d43700ef1d6a32), ROM_BIOS(2))
ROM_END

ROM_START( sapizps3 )
	ROM_REGION( 0x10000, "maincpu", ROMREGION_ERASEFF )
	ROM_SYSTEM_BIOS( 0, "default", "JPR-1A" )
	ROMX_LOAD( "jpr1a.bin", 	 0xf800, 0x0800, CRC(3ed89786) SHA1(dcc8657b4884bfe58d114c539b733b73d038ee30), ROM_BIOS(1))
	ROM_SYSTEM_BIOS( 1, "per", "Perina" )
	ROMX_LOAD( "perina_1988.bin",0xf800, 0x0800, CRC(d71e8d3a) SHA1(9b3a26ea7c2f2c8a1fb10b51c1c880acc9fd806d), ROM_BIOS(2))
	ROM_SYSTEM_BIOS( 2, "pkt1", "PKT 1" )
	ROMX_LOAD( "pkt1.bin",		 0xf800, 0x0800, CRC(ed5a2725) SHA1(3383c15f87f976400b8d0f31829e2a95236c4b6c), ROM_BIOS(3))
	ROM_SYSTEM_BIOS( 3, "1zmod", "JPR-1Zmod" )
	ROMX_LOAD( "jpr1zmod.bin",	 0xf800, 0x0800, CRC(69a29b07) SHA1(1cd31032954fcd7d10b1586be62db6f7597eb4f2), ROM_BIOS(4))
ROM_END
/* Driver */

/*    YEAR  NAME    PARENT  COMPAT  MACHINE     INPUT       INIT     COMPANY                  FULLNAME   FLAGS */
COMP( 1985, sapi1,	0,	0,	sapi1,		sapi1,	sapi1,	 "Tesla", "SAPI-1 ZPS 1",	 GAME_NO_SOUND)
COMP( 1985, sapizps2,sapi1,	0,	sapi1,		sapi1,	sapi1,	 "Tesla", "SAPI-1 ZPS 2",	 GAME_NOT_WORKING | GAME_NO_SOUND)
COMP( 1985, sapizps3,sapi1,	0,	sapizps3,	sapi1,	sapizps3, "Tesla", "SAPI-1 ZPS 3",	 GAME_NOT_WORKING | GAME_NO_SOUND)
