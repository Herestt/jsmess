/*********************************************************************

    formats/comx35_comx.c

    Quickload code for COMX-35 comx files

*********************************************************************/

#include "emu.h"
#include "formats/comx35_comx.h"
#include "cpu/cdp1802/cdp1802.h"
#include "devices/messram.h"

/***************************************************************************
    PARAMETERS
***************************************************************************/

#define LOG 1

enum
{
	COMX_TYPE_BINARY = 1,
	COMX_TYPE_BASIC,
	COMX_TYPE_BASIC_FM,
	COMX_TYPE_RESERVED,
	COMX_TYPE_DATA
};

/***************************************************************************
    IMPLEMENTATION
***************************************************************************/

/*-------------------------------------------------
    image_fread_memory - read image to memory
-------------------------------------------------*/

static void image_fread_memory(running_device *image, UINT16 addr, UINT32 count)
{
	void *ptr = memory_get_write_ptr(cpu_get_address_space(image->machine->firstcpu, ADDRESS_SPACE_PROGRAM), addr);

	image_fread(image, ptr, count);
}

/*-------------------------------------------------
    QUICKLOAD_LOAD( comx35_comx )
-------------------------------------------------*/

QUICKLOAD_LOAD( comx35_comx )
{
	const address_space *program = cpu_get_address_space(image->machine->firstcpu, ADDRESS_SPACE_PROGRAM);

	UINT8 header[16] = {0};
	int size = image_length(image);

	if (size > messram_get_size(devtag_get_device(image->machine, "messram")))
	{
		return INIT_FAIL;
	}

	image_fread(image, header, 5);

	if (header[1] != 'C' || header[2] != 'O' || header[3] != 'M' || header[4] != 'X' )
	{
		return INIT_FAIL;
	}

	switch (header[0])
	{
	case COMX_TYPE_BINARY:
		/*

            Type 1: pure machine code (i.e. no basic)

            Byte 0 to 4: 1 - 'COMX'
            Byte 5 and 6: Start address (1802 way; see above)
            Byte 6 and 7: End address
            Byte 9 and 10: Execution address

            Byte 11 to Eof, should be stored in ram from start to end; execution address
            'xxxx' for the CALL (@xxxx) basic statement to actually run the code.

        */
		{
			UINT16 start_address, end_address, run_address;

			image_fread(image, header, 6);

			start_address = pick_integer_be(header, 0, 2);
			end_address = pick_integer_be(header, 2, 2);
			run_address = pick_integer_be(header, 4, 2);

			image_fread_memory(image, start_address, end_address - start_address);

			popmessage("Type CALL (@%04x) to start program", run_address);
		}
		break;

	case COMX_TYPE_BASIC:
		/*

            Type 2: Regular basic code or machine code followed by basic

            Byte 0 to 4: 2 - 'COMX'
            Byte 5 and 6: DEFUS value, to be stored on 0x4281 and 0x4282
            Byte 7 and 8: EOP value, to be stored on 0x4283 and 0x4284
            Byte 9 and 10: End array, start string to be stored on 0x4292 and 0x4293
            Byte 11 and 12: start array to be stored on 0x4294 and 0x4295
            Byte 13 and 14: EOD and end string to be stored on 0x4299 and 0x429A

            Byte 15 to Eof to be stored on 0x4400 and onwards

            Byte 0x4281-0x429A (or at least the ones above) should be set otherwise
            BASIC won't 'see' the code.

        */

		image_fread_memory(image, 0x4281, 4);
		image_fread_memory(image, 0x4292, 4);
		image_fread_memory(image, 0x4299, 2);
		image_fread_memory(image, 0x4400, size);
		break;

	case COMX_TYPE_BASIC_FM:
		/*

            Type 3: F&M basic load

            Not the most important! But we designed our own basic extension, you can
            find it in the F&M basic folder as F&M Basic.comx. When you run this all
            basic code should start at address 0x6700 instead of 0x4400 as from
            0x4400-0x6700 the F&M basic stuff is loaded. So format is identical to Type
            2 except Byte 15 to Eof should be stored on 0x6700 instead. .comx files of
            this format can also be found in the same folder as the F&M basic.comx file.

        */

		image_fread_memory(image, 0x4281, 4);
		image_fread_memory(image, 0x4292, 4);
		image_fread_memory(image, 0x4299, 2);
		image_fread_memory(image, 0x6700, size);
		break;

	case COMX_TYPE_RESERVED:
		/*

            Type 4: Incorrect DATA format, I suggest to forget this one as it won't work
            in most cases. Instead I left this one reserved and designed Type 5 instead.

        */
		break;

	case COMX_TYPE_DATA:
		/*

            Type 5: Data load

            Byte 0 to 4: 5 - 'COMX'
            Byte 5 and 6: Array length
            Byte 7 to Eof: Basic 'data'

            To load this first get the 'start array' from the running COMX, i.e. address
            0x4295/0x4296. Calculate the EOD as 'start array' + length of the data (i.e.
            file length - 7). Store the EOD back on 0x4299 and ox429A. Calculate the
            'Start String' as 'start array' + 'Array length' (Byte 5 and 6). Store the
            'Start String' on 0x4292/0x4293. Load byte 7 and onwards starting from the
            'start array' value fetched from 0x4295/0x4296.

        */
		{
			UINT16 start_array, end_array, start_string, array_length;

			image_fread(image, header, 2);

			array_length = pick_integer_be(header, 0, 2);
			start_array = (memory_read_byte(program, 0x4295) << 8) | memory_read_byte(program, 0x4296);
			end_array = start_array + (size - 7);

			memory_write_byte(program, 0x4299, end_array >> 8);
			memory_write_byte(program, 0x429a, end_array & 0xff);

			start_string = start_array + array_length;

			memory_write_byte(program, 0x4292, start_string >> 8);
			memory_write_byte(program, 0x4293, start_string & 0xff);

			image_fread_memory(image, start_array, size);
		}
		break;
	}

	return INIT_PASS;
}
