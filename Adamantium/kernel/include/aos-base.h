#ifndef _AOSBASE_H
#define _AOSBASE_H

#define MAKEBYTE(x)                 ((unsigned char)x) & 0xFF
#define MAKEWORD(x)                 ((unsigned short)x)	& 0xFFFF
#define MAKEDWORD(x)                ((unsigned long)x##L) & 0xFFFFFFFF

#define PASS_VALUE(x)	(x)

#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_OPS
#define F_OPEN			0x00
#define F_READ			0x01
#define F_WRITE			0x02
#define F_READWRITE		0x04
#define F_APPEND		0x08
#define F_CLOSE			0x10
#define F_SEEK			0x20
#define F_TRUNCATE		0x40
#define F_RENAME		0x80
#endif

#ifndef DIRECTORY_OPS
#define D_CREATE		0x00
#define D_DELETE		0x01
#define D_OPENDIR		0x02
#define D_CLOSEDIR		0x04
#define D_READDIR		0x08
#define D_RENAME		0x10
#define D_LINK			0x20
#define D_UNLINK		0x40
#endif

#ifdef __cplusplus
}
#endif

#endif
