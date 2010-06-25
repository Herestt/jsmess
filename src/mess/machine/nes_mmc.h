#ifndef __MMC_H
#define __MMC_H

/* Boards */
enum
{
	STD_NROM = 0,
	STD_AXROM, STD_BXROM, STD_CNROM, STD_CPROM, 
	STD_DXROM, STD_EXROM, STD_FXROM, STD_GXROM, 
	STD_HKROM, STD_JXROM, STD_MXROM, STD_NXROM, 
	STD_PXROM, STD_SXROM, STD_TXROM, STD_TXSROM, 
	STD_TKROM, STD_TQROM, STD_TVROM, 
	STD_UN1ROM, STD_UXROM,
	HVC_FAMBASIC, NES_QJ, PAL_ZZ, UXROM_CC,
	STD_DRROM, STD_SXROM_A, STD_SOROM, STD_SOROM_A,
	/* Discrete components boards (by various manufacturer) */
	DIS_74X161X138, DIS_74X139X74, 
	DIS_74X377, DIS_74X161X161X32,
	/* Active Enterprises */
	ACTENT_ACT52,
	/* AGCI */
	AGCI_50282,
	/* AVE */
	AVE_NINA01, AVE_NINA06,
	/* Bandai */
	BANDAI_JUMP2, BANDAI_PT554,
	BANDAI_DATACH, BANDAI_KARAOKE, BANDAI_OEKAKIDS, 
	BANDAI_FCG, BANDAI_LZ93, BANDAI_LZ93EX,
	/* Caltron */
	CALTRON_6IN1,
	/* Camerica */
	CAMERICA_BF9093, CAMERICA_BF9097, CAMERICA_BF9096,
	CAMERICA_GOLDENFIVE, GG_NROM,
	/* Dreamtech */
	DREAMTECH_BOARD,
	/* Irem */
	IREM_G101, IREM_H3001, IREM_LROG017, 
	IREM_TAM_S1, IREM_HOLYDIV,
	/* Jaleco */
	JALECO_SS88006, JALECO_JF11, JALECO_JF13,
	JALECO_JF16, JALECO_JF17, JALECO_JF19,
	/* Konami */
	KONAMI_VRC1, KONAMI_VRC2, KONAMI_VRC3,
	KONAMI_VRC4, KONAMI_VRC6, KONAMI_VRC7,
	/* Namcot */
	NAMCOT_163, NAMCOT_3453,
	NAMCOT_3425, NAMCOT_34X3, NAMCOT_3446,
	/* NTDEC */
	NTDEC_ASDER, NTDEC_FIGHTINGHERO,
	/* Rex Soft */
	REXSOFT_SL1632, REXSOFT_DBZ5,
	/* Sachen */
	SACHEN_8259A, SACHEN_8259B, SACHEN_8259C,
	SACHEN_8259D, SACHEN_SA0036, SACHEN_SA0037,
	SACHEN_SA72007, SACHEN_SA72008, SACHEN_TCA01, 
	SACHEN_TCU01, SACHEN_TCU02, 
	SACHEN_74LS374, SACHEN_74LS374_A,
	/* Sunsoft */
	SUNSOFT_1, SUNSOFT_2, SUNSOFT_3, SUNSOFT_4, 
	SUNSOFT_DCS, SUNSOFT_5B, SUNSOFT_FME7,
	/* Taito */
	TAITO_TC0190FMC, TAITO_TC0190FMCP, 
	TAITO_X1_005, TAITO_X1_005_A, TAITO_X1_017,
	/* Tengen */
	TENGEN_800008, TENGEN_800032, TENGEN_800037,
	/* TXC */
	TXC_22211A, TXC_22211B, TXC_22211C, 
	TXC_MXMDHTWO, TXC_TW, TXC_STRIKEWOLF,
	/* Multigame Carts */
	BMC_64IN1NR, BMC_190IN1, BMC_A65AS, BMC_GS2004, BMC_GS2013,
	BMC_HIK8IN1, BMC_NOVELDIAMOND, BMC_S24IN1SC03, BMC_T262,
	BMC_WS, BMC_SUPERBIG_7IN1, BMC_SUPERHIK_4IN1, BMC_BALLGAMES_11IN1,
	BMC_MARIOPARTY_7IN1, BMC_SUPER_700IN1, BMC_FAMILY_4646B, 
	BMC_36IN1, BMC_21IN1, BMC_150IN1, BMC_35IN1, BMC_64IN1,
	BMC_15IN1, BMC_SUPERHIK_300IN1, BMC_9999999IN1, BMC_SUPERGUN_20IN1,
	BMC_GOLDENCARD_6IN1, BMC_72IN1, BMC_SUPER_42IN1, BMC_76IN1,
	BMC_1200IN1, BMC_31IN1, BMC_22GAMES, BMC_20IN1, BMC_110IN1, 
	BMC_GKA, BMC_GKB, BMC_VT5201, BMC_BENSHENG_BS5,
	/* Unlicensed */
	UNL_8237, UNL_CC21, UNL_AX5705, UNL_KOF97,
	UNL_N625092, UNL_SC127, UNL_SMB2J, UNL_T230,
	UNL_UXROM, UNL_MK2, UNL_XZY, UNL_KOF96,
	UNL_SUPERFIGHTER3, UNL_RACERMATE,
	/* Bootleg boards */
	BTL_SMB2A, BTL_MARIOBABY, BTL_AISENSHINICOL,
	BTL_SMB2B, BTL_SMB3, BTL_SUPERBROS11, BTL_DRAGONNINJA,
	/* Misc: these are needed to convert mappers to boards, I will sort them later */
	OPENCORP_DAOU306, HES_BOARD, HES6IN1_BOARD, RUMBLESTATION_BOARD,
	MAGICSERIES_MD, KASING_BOARD, FUTUREMEDIA_BOARD, SOMERITEAM_SL12,
	HENGEDIANZI_BOARD, HENGEDIANZI_XJZB, SUBOR_TYPE0, SUBOR_TYPE1, KAISER_KS7058, CONY_BOARD,
	CNE_DECATHLON, CNE_FSB, CNE_SHLZ, RCM_GS2015, RCM_TETRISFAMILY,
	WAIXING_TYPE_A, WAIXING_TYPE_B, WAIXING_TYPE_C, WAIXING_TYPE_D,
	WAIXING_TYPE_E, WAIXING_TYPE_F, WAIXING_TYPE_G, WAIXING_TYPE_H,
	WAIXING_SGZLZ, WAIXING_SGZ, WAIXING_ZS, WAIXING_SECURITY,
	WAIXING_DQ8, WAIXING_FFV, WAIXING_PS2, SUPERGAME_LIONKING, SUPERGAME_BOOGERMAN,
	KAY_PANDAPRINCE, HOSENKAN_BOARD, NITRA_TDA, GOUDER_37017, NANJING_BOARD,
	/* Unsupported (for place-holder boards, with no working emulation) & no-board (at init) */
	UNSUPPORTED_BOARD, NO_BOARD
};

//extern int MMC1_extended; /* 0 = normal MMC1 cart, 1 = 512k MMC1, 2 = 1024k MMC1 */

#define MMC5_VRAM

int nes_mapper_reset(running_machine *machine);
int nes_pcb_reset(running_machine *machine);

void mapper_handlers_setup(running_machine *machine);
void pcb_handlers_setup(running_machine *machine);
void unif_mapr_setup(running_machine *machine, const char *board);
int nes_get_pcb_id(running_machine *machine, const char *feature);

WRITE8_HANDLER( nes_low_mapper_w );
READ8_HANDLER( nes_low_mapper_r );
WRITE8_HANDLER( nes_chr_w );
READ8_HANDLER( nes_chr_r );
WRITE8_HANDLER( nes_nt_w );
READ8_HANDLER( nes_nt_r );

WRITE8_HANDLER( nes_mapper50_add_w );
WRITE8_HANDLER( smb2jb_extra_w );

//TEMPORARY PPU STUFF

/* mirroring types */
#define PPU_MIRROR_NONE		0
#define PPU_MIRROR_VERT		1
#define PPU_MIRROR_HORZ		2
#define PPU_MIRROR_HIGH		3
#define PPU_MIRROR_LOW		4
#define PPU_MIRROR_4SCREEN	5	// Same effect as NONE, but signals that we should never mirror

void set_nt_mirroring(running_machine *machine, int mirroring);


#endif
