/***************************************************************************

    coco_pak.c

    Code for emulating standard CoCo cartridges

***************************************************************************/

#include "emu.h"
#include "coco_pak.h"
#include "imagedev/cartslot.h"

#define CARTSLOT_TAG			"cart"

/***************************************************************************
    IMPLEMENTATION
***************************************************************************/

static MACHINE_CONFIG_FRAGMENT(coco_pak)
	MCFG_CARTSLOT_ADD(CARTSLOT_TAG)
	MCFG_CARTSLOT_EXTENSION_LIST("ccc,rom")
	MCFG_CARTSLOT_NOT_MANDATORY
	MCFG_CARTSLOT_INTERFACE("coco_cart")

	/* Software lists */
	MCFG_SOFTWARE_LIST_ADD("cart_list","coco_cart")
MACHINE_CONFIG_END

ROM_START( coco_pak )
	ROM_REGION(0x8000,CARTSLOT_TAG,ROMREGION_ERASE00)
	ROM_CART_LOAD(CARTSLOT_TAG, 0x0000, 0x8000, ROM_OPTIONAL | ROM_MIRROR)
ROM_END

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

const device_type COCO_PAK = &device_creator<coco_pak_device>;

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  coco_pak_device - constructor
//-------------------------------------------------
coco_pak_device::coco_pak_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, type, name, tag, owner, clock),
	  device_cococart_interface( mconfig, *this ),
	  device_slot_card_interface(mconfig, *this)
{
}

coco_pak_device::coco_pak_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
      : device_t(mconfig, COCO_PAK, "CoCo Program PAK", tag, owner, clock),
		device_cococart_interface( mconfig, *this ),
		device_slot_card_interface(mconfig, *this)
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void coco_pak_device::device_start()
{
	m_cart = dynamic_cast<device_image_interface *>(subdevice(CARTSLOT_TAG));
	m_owner = dynamic_cast<cococart_slot_device *>(owner());
}

//-------------------------------------------------
//  device_config_complete - perform any
//  operations now that the configuration is
//  complete
//-------------------------------------------------

void coco_pak_device::device_config_complete()
{
	m_shortname = "cocopak";
}
//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor coco_pak_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( coco_pak );
}

//-------------------------------------------------
//  rom_region - device-specific ROM region
//-------------------------------------------------

const rom_entry *coco_pak_device::device_rom_region() const
{
	return ROM_NAME( coco_pak );
}

/*-------------------------------------------------
    device_reset - device-specific startup
-------------------------------------------------*/

void coco_pak_device::device_reset()
{
	if (m_cart->exists()) {
		cococart_line_value cart_line;

		cart_line = input_port_read_safe(machine(), "CARTAUTO", 0x01)
			? COCOCART_LINE_VALUE_Q
			: COCOCART_LINE_VALUE_CLEAR;

		/* normal CoCo PAKs tie their CART line to Q - the system clock */
		m_owner->cart_set_line(COCOCART_LINE_CART,cart_line);
	}
}

/*-------------------------------------------------
    get_cart_base
-------------------------------------------------*/

UINT8* coco_pak_device::get_cart_base()
{
	return subregion(CARTSLOT_TAG)->base();
}

/***************************************************************************
    BANKED CARTRIDGES
***************************************************************************/

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

const device_type COCO_PAK_BANKED = &device_creator<coco_pak_banked_device>;

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  coco_pak_device - constructor
//-------------------------------------------------

coco_pak_banked_device::coco_pak_banked_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
      : coco_pak_device(mconfig, COCO_PAK_BANKED, "CoCo Program PAK (Banked)", tag, owner, clock)
{
}

/*-------------------------------------------------
    device_reset - device-specific startup
-------------------------------------------------*/

void coco_pak_banked_device::device_reset()
{
	coco_pak_device::device_reset();

	banked_pak_set_bank(0);
}

/*-------------------------------------------------
    banked_pak_set_bank - function to set the bank
-------------------------------------------------*/

void coco_pak_banked_device::banked_pak_set_bank(UINT32 bank)
{
	UINT64 pos;
	UINT32 i;
	UINT8 *rom = subregion(CARTSLOT_TAG)->base();
	UINT32 rom_length = subregion(CARTSLOT_TAG)->bytes();

	pos = (bank * 0x4000) % m_cart->length();

	for (i = 0; i < rom_length / 0x4000; i++)
	{
		m_cart->fseek(pos, SEEK_SET);
		m_cart->fread(&rom[i * 0x4000], 0x4000);
	}
}

/*-------------------------------------------------
    write
-------------------------------------------------*/

WRITE8_MEMBER(coco_pak_banked_device::write)
{
	switch(offset)
	{
		case 0:
			/* set the bank */
			banked_pak_set_bank(data);
			break;
	}
}
