/*************************************************************************

    taiicdev.h

    Implementation of various Taito custom video & input ICs

**************************************************************************/

#include "devcb.h"

/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

typedef struct _pc080sn_interface pc080sn_interface;
struct _pc080sn_interface
{
	int                gfxnum;

	int                x_offset, y_offset;
	int                y_invert;
	int                dblwidth;
};


typedef struct _pc090oj_interface pc090oj_interface;
struct _pc090oj_interface
{
	int                gfxnum;

	int                x_offset, y_offset;
	int                use_buffer;
};


typedef struct _tc0080vco_interface tc0080vco_interface;
struct _tc0080vco_interface
{
	int                gfxnum;
	int                txnum;

	int                bg_xoffs, bg_yoffs;
	int                bg_flip_yoffs;

	int                has_fg0;	/* for debug */
};

typedef struct _tc0100scn_interface tc0100scn_interface;
struct _tc0100scn_interface
{
	const char         *screen;

	int                gfxnum;
	int                txnum;

	int                x_offset, y_offset;
	int                flip_xoffs, flip_yoffs;
	int                flip_text_xoffs, flip_text_yoffs;

	int                multiscrn_xoffs;
};


typedef struct _tc0280grd_interface tc0280grd_interface;
struct _tc0280grd_interface
{
	int                gfxnum;
};


typedef struct _tc0480scp_interface tc0480scp_interface;
struct _tc0480scp_interface
{
	int                gfxnum;
	int                txnum;

	int                pixels;

	int                x_offset, y_offset;
	int                text_xoffs, text_yoffs;
	int                flip_xoffs, flip_yoffs;

	int                col_base;
};


typedef struct _tc0150rod_interface tc0150rod_interface;
struct _tc0150rod_interface
{
	const char      *gfx_region;	/* gfx region for the road */
};


typedef struct _tc0110pcr_interface tc0110pcr_interface;
struct _tc0110pcr_interface
{
	int               pal_offs;
};


typedef struct _tc0220ioc_interface tc0220ioc_interface;
struct _tc0220ioc_interface
{
	devcb_read8 read_0;
	devcb_read8 read_1;
	devcb_read8 read_2;
	devcb_read8 read_3;
	devcb_read8 read_7;
};


typedef struct _tc0510nio_interface tc0510nio_interface;
struct _tc0510nio_interface
{
	devcb_read8 read_0;
	devcb_read8 read_1;
	devcb_read8 read_2;
	devcb_read8 read_3;
	devcb_read8 read_7;
};


typedef struct _tc0640fio_interface tc0640fio_interface;
struct _tc0640fio_interface
{
	devcb_read8 read_0;
	devcb_read8 read_1;
	devcb_read8 read_2;
	devcb_read8 read_3;
	devcb_read8 read_7;
};


/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/

DEVICE_GET_INFO( pc080sn );
DEVICE_GET_INFO( pc090oj );
DEVICE_GET_INFO( tc0080vco );
DEVICE_GET_INFO( tc0100scn );
DEVICE_GET_INFO( tc0280grd );
DEVICE_GET_INFO( tc0360pri );
DEVICE_GET_INFO( tc0480scp );
DEVICE_GET_INFO( tc0150rod );
DEVICE_GET_INFO( tc0110pcr );
DEVICE_GET_INFO( tc0220ioc );
DEVICE_GET_INFO( tc0510nio );
DEVICE_GET_INFO( tc0640fio );


/***************************************************************************
    DEVICE CONFIGURATION MACROS
***************************************************************************/

#define PC080SN DEVICE_GET_INFO_NAME( pc080sn )

#define MDRV_PC080SN_ADD(_tag, _interface) \
	MDRV_DEVICE_ADD(_tag, PC080SN, 0) \
	MDRV_DEVICE_CONFIG(_interface)

#define PC090OJ DEVICE_GET_INFO_NAME( pc090oj )

#define MDRV_PC090OJ_ADD(_tag, _interface) \
	MDRV_DEVICE_ADD(_tag, PC090OJ, 0) \
	MDRV_DEVICE_CONFIG(_interface)

#define TC0080VCO DEVICE_GET_INFO_NAME( tc0080vco )

#define MDRV_TC0080VCO_ADD(_tag, _interface) \
	MDRV_DEVICE_ADD(_tag, TC0080VCO, 0) \
	MDRV_DEVICE_CONFIG(_interface)

#define TC0100SCN DEVICE_GET_INFO_NAME( tc0100scn )

#define MDRV_TC0100SCN_ADD(_tag, _interface) \
	MDRV_DEVICE_ADD(_tag, TC0100SCN, 0) \
	MDRV_DEVICE_CONFIG(_interface)

#define TC0280GRD DEVICE_GET_INFO_NAME( tc0280grd )
#define TC0430GRW DEVICE_GET_INFO_NAME( tc0280grd )

#define MDRV_TC0280GRD_ADD(_tag, _interface) \
	MDRV_DEVICE_ADD(_tag, TC0280GRD, 0) \
	MDRV_DEVICE_CONFIG(_interface)

#define MDRV_TC0430GRW_ADD(_tag, _interface) \
	MDRV_DEVICE_ADD(_tag, TC0430GRW, 0) \
	MDRV_DEVICE_CONFIG(_interface)

#define TC0360PRI DEVICE_GET_INFO_NAME( tc0360pri )

#define MDRV_TC0360PRI_ADD(_tag) \
	MDRV_DEVICE_ADD(_tag, TC0360PRI, 0)

#define TC0150ROD DEVICE_GET_INFO_NAME( tc0150rod )

#define MDRV_TC0150ROD_ADD(_tag, _interface) \
	MDRV_DEVICE_ADD(_tag, TC0150ROD, 0) \
	MDRV_DEVICE_CONFIG(_interface)

#define TC0480SCP DEVICE_GET_INFO_NAME( tc0480scp )

#define MDRV_TC0480SCP_ADD(_tag, _interface) \
	MDRV_DEVICE_ADD(_tag, TC0480SCP, 0) \
	MDRV_DEVICE_CONFIG(_interface)

#define TC0110PCR DEVICE_GET_INFO_NAME( tc0110pcr )

#define MDRV_TC0110PCR_ADD(_tag, _interface) \
	MDRV_DEVICE_ADD(_tag, TC0110PCR, 0) \
	MDRV_DEVICE_CONFIG(_interface)

#define TC0220IOC DEVICE_GET_INFO_NAME( tc0220ioc )

#define MDRV_TC0220IOC_ADD(_tag, _interface) \
	MDRV_DEVICE_ADD(_tag, TC0220IOC, 0) \
	MDRV_DEVICE_CONFIG(_interface)

#define TC0510NIO DEVICE_GET_INFO_NAME( tc0510nio )

#define MDRV_TC0510NIO_ADD(_tag, _interface) \
	MDRV_DEVICE_ADD(_tag, TC0510NIO, 0) \
	MDRV_DEVICE_CONFIG(_interface)

#define TC0640FIO DEVICE_GET_INFO_NAME( tc0640fio )

#define MDRV_TC0640FIO_ADD(_tag, _interface) \
	MDRV_DEVICE_ADD(_tag, TC0640FIO, 0) \
	MDRV_DEVICE_CONFIG(_interface)


/***************************************************************************
    DEVICE I/O FUNCTIONS
***************************************************************************/

/**  PC080SN  **/
READ16_DEVICE_HANDLER( pc080sn_word_r );
WRITE16_DEVICE_HANDLER( pc080sn_word_w );
WRITE16_DEVICE_HANDLER( pc080sn_xscroll_word_w );
WRITE16_DEVICE_HANDLER( pc080sn_yscroll_word_w );
WRITE16_DEVICE_HANDLER( pc080sn_ctrl_word_w );

void pc080sn_set_scroll(const device_config *device, int tilemap_num, int scrollx, int scrolly);
void pc080sn_set_trans_pen(const device_config *device, int tilemap_num, int pen);
void pc080sn_tilemap_update(const device_config *device);
void pc080sn_tilemap_draw(const device_config *device, bitmap_t *bitmap, const rectangle *cliprect, int layer, int flags, UINT32 priority);
void pc080sn_tilemap_draw_offset(const device_config *device, bitmap_t *bitmap, const rectangle *cliprect, int layer, int flags, UINT32 priority, int xoffs, int yoffs);

/* For Topspeed */
void pc080sn_tilemap_draw_special(const device_config *device, bitmap_t *bitmap, const rectangle *cliprect, int layer, int flags, UINT32 priority, UINT16 *ram);


/**  PC090OJ  **/
READ16_DEVICE_HANDLER( pc090oj_word_r );
WRITE16_DEVICE_HANDLER( pc090oj_word_w );

void pc090oj_set_sprite_ctrl(const device_config *device, UINT16 sprctrl);
void pc090oj_eof_callback(const device_config *device);
void pc090oj_draw_sprites(const device_config *device, bitmap_t *bitmap, const rectangle *cliprect, int pri_type);


/** TC0080VCO **/
READ16_DEVICE_HANDLER( tc0080vco_word_r );
WRITE16_DEVICE_HANDLER( ct0080vco_word_w );

void tc0080vco_tilemap_update(const device_config *device);
void tc0080vco_tilemap_draw(const device_config *device, bitmap_t *bitmap, const rectangle *cliprect, int layer, int flags, UINT32 priority);

#if 0
extern UINT16	*TC0080VCO_chain_ram_0;
extern UINT16	*TC0080VCO_chain_ram_1;
extern UINT16	*TC0080VCO_spriteram;
extern UINT16	*TC0080VCO_scroll_ram;
extern int	TC0080VCO_flipscreen;
#endif


/** TC0100SCN **/

#define TC0100SCN_SINGLE_VDU    1024

/* Function to set separate color banks for the three tilemapped layers.
   To change from the default (0,0,0) use after calling TC0100SCN_vh_start */
void tc0100scn_set_colbanks(const device_config *device, int bg0, int bg1, int tx);

/* Function to set separate color banks for each TC0100SCN.
   To change from the default (0,0,0) use after calling TC0100SCN_vh_start */
void tc0100scn_set_colbank(const device_config *device, int colbank);

/* Function to set bg tilemask < 0xffff */
void tc0100scn_set_bg_tilemask(const device_config *device, int mask);

/* Function to for Mjnquest to select gfx bank */
WRITE16_DEVICE_HANDLER( tc0100scn_gfxbank_w );

READ16_DEVICE_HANDLER( tc0100scn_word_r );
WRITE16_DEVICE_HANDLER( tc0100scn_word_w );
READ16_DEVICE_HANDLER( tc0100scn_ctrl_word_r );
WRITE16_DEVICE_HANDLER( tc0100scn_ctrl_word_w );

/* Functions for use with 68020 (Under Fire) */
READ32_DEVICE_HANDLER( tc0100scn_long_r );
WRITE32_DEVICE_HANDLER( tc0100scn_long_w );
READ32_DEVICE_HANDLER( tc0100scn_ctrl_long_r );
WRITE32_DEVICE_HANDLER( tc0100scn_ctrl_long_w );

#if 0
/* Functions to write multiple TC0100SCNs with the same data */
WRITE16_DEVICE_HANDLER( TC0100SCN_dual_screen_w );
WRITE16_DEVICE_HANDLER( TC0100SCN_triple_screen_w );
#endif

void tc0100scn_tilemap_update(const device_config *device);
int tc0100scn_tilemap_draw(const device_config *device, bitmap_t *bitmap, const rectangle *cliprect, int layer, int flags, UINT32 priority);

/* returns 0 or 1 depending on the lowest priority tilemap set in the internal
   register. Use this function to draw tilemaps in the correct order. */
int tc0100scn_bottomlayer(const device_config *device);


/** TC0280GRD & TC0430GRW **/

READ16_DEVICE_HANDLER( tc0280grd_word_r );
WRITE16_DEVICE_HANDLER( tc0280grd_word_w );
WRITE16_DEVICE_HANDLER( tc0280grd_ctrl_word_w );
void tc0280grd_tilemap_update(const device_config *device, int base_color);
void tc0280grd_zoom_draw(const device_config *device, bitmap_t *bitmap, const rectangle *cliprect, int xoffset, int yoffset, UINT32 priority);

READ16_DEVICE_HANDLER( tc0430grw_word_r );
WRITE16_DEVICE_HANDLER( tc0430grw_word_w );
WRITE16_DEVICE_HANDLER( tc0430grw_ctrl_word_w );
void TC0430GRW_tilemap_update(const device_config *device, int base_color);
void TC0430GRW_zoom_draw(const device_config *device, bitmap_t *bitmap, const rectangle *cliprect, int xoffset, int yoffset, UINT32 priority);


/** TC0360PRI **/

WRITE8_DEVICE_HANDLER( tc0360pri_w );
READ8_DEVICE_HANDLER( tc0360pri_r );


/** TC0480SCP **/
/* When writing a driver, pass zero for the text and flip offsets initially:
   then tweak them once you have the 4 bg layer positions correct. Col_base
   may be needed when tilemaps use a palette area from sprites. */

READ16_DEVICE_HANDLER( tc0480scp_word_r );
WRITE16_DEVICE_HANDLER( tc0480scp_word_w );
READ16_DEVICE_HANDLER( tc0480scp_ctrl_word_r );
WRITE16_DEVICE_HANDLER( tc0480scp_ctrl_word_w );

/* Functions for use with 68020 (Super-Z system) */
READ32_DEVICE_HANDLER( tc0480scp_long_r );
WRITE32_DEVICE_HANDLER( tc0480scp_long_w );
READ32_DEVICE_HANDLER( tc0480scp_ctrl_long_r );
WRITE32_DEVICE_HANDLER( tc0480scp_ctrl_long_w );

void tc0480scp_tilemap_update(const device_config *device);
void tc0480scp_tilemap_draw(const device_config *device, bitmap_t *bitmap, const rectangle *cliprect, int layer, int flags, UINT32 priority);

/* Returns the priority order of the bg tilemaps set in the internal
   register. The order in which the four layers should be drawn is
   returned in the lowest four nibbles  (msn = bottom layer; lsn = top) */
int tc0480scp_get_bg_priority(const device_config *device);

/* Undrfire needs to read this for a sprite/tile priority hack */
//extern int TC0480SCP_pri_reg;



/** TC0150ROD **/
READ16_DEVICE_HANDLER( tc0150rod_word_r );
WRITE16_DEVICE_HANDLER( tc0150rod_word_w );
void tc0150rod_draw(const device_config *device, bitmap_t *bitmap, const rectangle *cliprect, int y_offs, int palette_offs, int type, int road_trans, UINT32 low_priority, UINT32 high_priority);


/** TC0110PCR **/
READ16_DEVICE_HANDLER( tc0110pcr_word_r );
WRITE16_DEVICE_HANDLER( tc0110pcr_word_w );	/* color index goes up in step of 2 */
WRITE16_DEVICE_HANDLER( tc0110pcr_step1_word_w );	/* color index goes up in step of 1 */
WRITE16_DEVICE_HANDLER( tc0110pcr_step1_rbswap_word_w );	/* swaps red and blue components */
WRITE16_DEVICE_HANDLER( tc0110pcr_step1_4bpg_word_w );	/* only 4 bits per color gun */



/* I/O chips, all extremely similar. The TC0220IOC was sometimes addressed through a port, typically on earlier games. */

/** TC0220IOC **/
READ8_DEVICE_HANDLER( tc0220ioc_r );
WRITE8_DEVICE_HANDLER( tc0220ioc_w );
READ8_DEVICE_HANDLER( tc0220ioc_port_r );
WRITE8_DEVICE_HANDLER( tc0220ioc_port_w );
READ8_DEVICE_HANDLER( tc0220ioc_portreg_r );
WRITE8_DEVICE_HANDLER( tc0220ioc_portreg_w );


/** TC0510NIO **/
READ8_DEVICE_HANDLER( tc0510nio_r );
WRITE8_DEVICE_HANDLER( tc0510nio_w );
READ16_DEVICE_HANDLER( tc0510nio_halfword_r );
WRITE16_DEVICE_HANDLER( tc0510nio_halfword_w );
READ16_DEVICE_HANDLER( tc0510nio_halfword_wordswap_r );
WRITE16_DEVICE_HANDLER( tc0510nio_halfword_wordswap_w );


/** TC0640FIO**/
READ8_DEVICE_HANDLER( tc0640fio_r );
WRITE8_DEVICE_HANDLER( tc0640fio_w );
READ16_DEVICE_HANDLER( tc0640fio_halfword_r );
WRITE16_DEVICE_HANDLER( tc0640fio_halfword_w );
READ16_DEVICE_HANDLER( tc0640fio_halfword_byteswap_r );
WRITE16_DEVICE_HANDLER( tc0640fio_halfword_byteswap_w );
