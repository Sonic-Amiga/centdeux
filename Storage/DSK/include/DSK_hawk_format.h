#pragma once
#include <stdint.h>
/*
 * (from Kromaine13 — 06/01/2022)
 * The sector address reg. if at 0xF141 MSB & 0xF142 LSB
 * format is
 * 	MSB:
 * 	N/A, 
 * 	N/A,
 * 	Cyl-256,
 * 	Cyl-128,
 * 	Cyl-64,
 * 	Cyl-32,
 * 	Cyl-16,
 * 	Cyl-8,
 *
 * 	LSB:
 * 	Cyl-4,
 * 	Cyl-2,
 * 	Cyl-1,
 * 	Head 0/1,
 * 	S8,
 * 	S4,
 * 	S2,
 * 	S1
 *
 * 	Max Cyl-405,
 * 	Max Tracks 810(two heads),
 * 	Max Sectors-16 (0xF)
 *
 * 	So if you are doing a 16 sector read is must start from sector zero on
 * 	given cylinder and at the end of a sector read if the DMA is not complete
 * 	the disk controller just adds (1) to the sector address reg. and keeps
 * 	reading (can not cause a new seek).   Any questions?   Regards,   Ken  R
 */

#define HAWK_BYTES_PER_SECTOR 0x190 // 400 Bytes per Sector;
#define HAWK_SECTORS_PER_TRACK 0x10 // 16 Sectors per Track
#define HAWK_BYTES_PER_TRACK ( HAWK_BYTES_PER_SECTOR * HAWK_SECTORS_PER_TRACK ) // 6400 Bytes per Track

#define HAWK_CYLS 0x195 // 405 Cylinders
#define HAWK_HEADS_PER_CYL 0x2 // 2 Heads
#define HAWK_TRACKS ( HAWK_CYLS * HAWK_HEADS_PER_CYL ) // 810 Tracks
#define HAWK_SECTORS ( HAWK_TRACKS * HAWK_SECTORS_PER_TRACK ) // 12960 Sectors
#define HAWK_BYTES ( HAWK_SECTORS * HAWK_BYTES_PER_SECTOR ) // 5184000 Bytes
 
#define HAWK_SECTOR_TO_CHS_C(sector) ( (sector>>5) & 0x01ff )
#define HAWK_SECTOR_TO_CHS_H(sector) ( (sector>>4) & 0x0001 )
#define HAWK_SECTOR_TO_CHS_S(sector) ( (sector>>4) & 0x000f )
#define HAWK_CHS_TO_SECTOR(c,h,s) ( (c<<5) | (h<<4) | (s<<0) )

#define HAWK_BYTE_POS_TO_SECTOR(byte) ( byte / HAWK_BYTES_PER_SECTOR )
#define HAWK_BYTE_POS_TO_SECTOR_BYTE_OFFSET(byte) ( byte % HAWK_BYTES_PER_SECTOR )

typedef union DSK_hawk_sector_address_t {
	uint16_t sector;
	struct {
		uint16_t LSB:8;
		uint16_t MSB:8;
	};
	struct {
		uint16_t S:4;
		uint16_t H:1;
		uint16_t C:9;
		uint16_t unused:2;
	};
} DSK_hawk_sector_address_t;


