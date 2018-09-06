const byte numbers[12][5] PROGMEM = {            // a minimal 3x5 numeric font
	{ 0x0E, 0x0A, 0x0A, 0x0A, 0x0E }, // 0
	{ 0x04, 0x04, 0x04, 0x04, 0x04 }, // 1
	{ 0x0E, 0x02, 0x0E, 0x08, 0x0E }, // 2
	{ 0x0E, 0x02, 0x0E, 0x02, 0x0E }, // 3
	{ 0x0A, 0x0A, 0x0E, 0x02, 0x02 }, // 4
	{ 0x0E, 0x08, 0x0E, 0x02, 0x0E }, // 5
	{ 0x0E, 0x08, 0x0E, 0x0A, 0x0E }, // 6
	{ 0x0E, 0x02, 0x02, 0x02, 0x02 }, // 7
	{ 0x0E, 0x0A, 0x0E, 0x0A, 0x0E }, // 8
	{ 0x0E, 0x0A, 0x0E, 0x02, 0x0E }, // 9
	{ 0x00, 0x00, 0x0E, 0x00, 0x00 }, // -
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }  // (space)
};

const byte fonts[224][5] PROGMEM = {			  // default 5x7 font with cyrillic symbols
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 0x20 space
	{ 0x00, 0x00, 0x5F, 0x00, 0x00 }, // 0x21 !
	{ 0x00, 0x07, 0x00, 0x07, 0x00 }, // 0x22 "
	{ 0x14, 0x7F, 0x14, 0x7F, 0x14 }, // 0x23 #
	{ 0x24, 0x2A, 0x7F, 0x2A, 0x12 }, // 0x24 $
	{ 0x23, 0x13, 0x08, 0x64, 0x62 }, // 0x25 %
	{ 0x36, 0x49, 0x55, 0x22, 0x50 }, // 0x26 &
	{ 0x00, 0x05, 0x03, 0x00, 0x00 }, // 0x27 '
	{ 0x00, 0x1C, 0x22, 0x41, 0x00 }, // 0x28 (
	{ 0x00, 0x41, 0x22, 0x1C, 0x00 }, // 0x29 )
	{ 0x14, 0x08, 0x3E, 0x08, 0x14 }, // 0x2A *
	{ 0x08, 0x08, 0x3E, 0x08, 0x08 }, // 0x2B +
	{ 0x00, 0x50, 0x30, 0x00, 0x00 }, // 0x2C ,
	{ 0x10, 0x10, 0x10, 0x10, 0x10 }, // 0x2D -
	{ 0x00, 0x60, 0x60, 0x00, 0x00 }, // 0x2E .
	{ 0x20, 0x10, 0x08, 0x04, 0x02 }, // 0x2F '\'
	{ 0x3E, 0x51, 0x49, 0x45, 0x3E }, // 0x30 0
	{ 0x00, 0x42, 0x7F, 0x40, 0x00 }, // 0x31 1
	{ 0x42, 0x61, 0x51, 0x49, 0x46 }, // 0x32 2
	{ 0x21, 0x41, 0x45, 0x4B, 0x31 }, // 0x33 3
	{ 0x18, 0x14, 0x12, 0x7F, 0x10 }, // 0x34 4
	{ 0x27, 0x45, 0x45, 0x45, 0x39 }, // 0x35 5
	{ 0x3C, 0x4A, 0x49, 0x49, 0x30 }, // 0x36 6
	{ 0x01, 0x71, 0x09, 0x05, 0x03 }, // 0x37 7
	{ 0x36, 0x49, 0x49, 0x49, 0x36 }, // 0x38 8
	{ 0x06, 0x49, 0x49, 0x29, 0x1E }, // 0x39 9
	{ 0x00, 0x36, 0x36, 0x00, 0x00 }, // 0x3A :
	{ 0x00, 0x56, 0x36, 0x00, 0x00 }, // 0x3B ;
	{ 0x08, 0x14, 0x22, 0x41, 0x00 }, // 0x3C <
	{ 0x14, 0x14, 0x14, 0x14, 0x14 }, // 0x3D =
	{ 0x00, 0x41, 0x22, 0x14, 0x08 }, // 0x3E >
	{ 0x02, 0x01, 0x51, 0x09, 0x06 }, // 0x3F ?
	{ 0x32, 0x49, 0x79, 0x41, 0x3E }, // 0x40 @
	{ 0x7E, 0x11, 0x11, 0x11, 0x7E }, // 0x41 A
	{ 0x7F, 0x49, 0x49, 0x49, 0x36 }, // 0x42 B
	{ 0x3E, 0x41, 0x41, 0x41, 0x22 }, // 0x43 C
	{ 0x7F, 0x41, 0x41, 0x22, 0x1C }, // 0x44 D
	{ 0x7F, 0x49, 0x49, 0x49, 0x41 }, // 0x45 E
	{ 0x7F, 0x09, 0x09, 0x09, 0x01 }, // 0x46 F
	{ 0x3E, 0x41, 0x49, 0x49, 0x7A }, // 0x47 G
	{ 0x7F, 0x08, 0x08, 0x08, 0x7F }, // 0x48 H
	{ 0x00, 0x41, 0x7F, 0x41, 0x00 }, // 0x49 I
	{ 0x20, 0x40, 0x41, 0x3F, 0x01 }, // 0x4A J
	{ 0x7F, 0x08, 0x14, 0x22, 0x41 }, // 0x4B K
	{ 0x7F, 0x40, 0x40, 0x40, 0x40 }, // 0x4C L
	{ 0x7F, 0x02, 0x0C, 0x02, 0x7F }, // 0x4D M
	{ 0x7F, 0x04, 0x08, 0x10, 0x7F }, // 0x4E N
	{ 0x3E, 0x41, 0x41, 0x41, 0x3E }, // 0x4F O
	{ 0x7F, 0x09, 0x09, 0x09, 0x06 }, // 0x50 P
	{ 0x3E, 0x41, 0x51, 0x21, 0x5e }, // 0x51 Q
	{ 0x7F, 0x09, 0x19, 0x29, 0x46 }, // 0x52 R
	{ 0x46, 0x49, 0x49, 0x49, 0x31 }, // 0x53 S
	{ 0x01, 0x01, 0x7F, 0x01, 0x01 }, // 0x54 T
	{ 0x3F, 0x40, 0x40, 0x40, 0x3F }, // 0x55 U
	{ 0x1F, 0x20, 0x40, 0x20, 0x1F }, // 0x56 V
	{ 0x3F, 0x40, 0x38, 0x40, 0x3F }, // 0x57 W
	{ 0x63, 0x14, 0x08, 0x14, 0x63 }, // 0x58 X
	{ 0x07, 0x08, 0x70, 0x08, 0x07 }, // 0x59 Y
	{ 0x61, 0x51, 0x49, 0x45, 0x43 }, // 0x5A Z
	{ 0x00, 0x7F, 0x41, 0x41, 0x00 }, // 0x5B [
	{ 0x02, 0x04, 0x08, 0x10, 0x20 }, // 0x5C /
	{ 0x00, 0x41, 0x41, 0x7F, 0x00 }, // 0x5D ]
	{ 0x04, 0x02, 0x01, 0x02, 0x04 }, // 0x5E ^
	{ 0x40, 0x40, 0x40, 0x40, 0x40 }, // 0x5F _
	{ 0x00, 0x01, 0x02, 0x04, 0x00 }, // 0x60 `
	{ 0x20, 0x54, 0x54, 0x54, 0x78 }, // 0x61 a
	{ 0x7F, 0x48, 0x44, 0x44, 0x38 }, // 0x62 b
	{ 0x38, 0x44, 0x44, 0x44, 0x20 }, // 0x63 c
	{ 0x38, 0x44, 0x44, 0x48, 0x7F }, // 0x64 d
	{ 0x38, 0x54, 0x54, 0x54, 0x18 }, // 0x65 e
	{ 0x08, 0x7E, 0x09, 0x01, 0x02 }, // 0x66 f
	{ 0x0C, 0x52, 0x52, 0x52, 0x3E }, // 0x67 g
	{ 0x7F, 0x08, 0x04, 0x04, 0x78 }, // 0x68 h
	{ 0x00, 0x44, 0x7D, 0x40, 0x00 }, // 0x69 i
	{ 0x20, 0x40, 0x44, 0x3D, 0x00 }, // 0x6A j
	{ 0x7F, 0x10, 0x28, 0x44, 0x00 }, // 0x6B k
	{ 0x00, 0x41, 0x7F, 0x40, 0x00 }, // 0x6C l
	{ 0x7C, 0x04, 0x18, 0x04, 0x78 }, // 0x6D m
	{ 0x7C, 0x08, 0x04, 0x04, 0x78 }, // 0x6E n
	{ 0x38, 0x44, 0x44, 0x44, 0x38 }, // 0x6F o
	{ 0x7C, 0x14, 0x14, 0x14, 0x08 }, // 0x70 p
	{ 0x08, 0x14, 0x14, 0x18, 0x7C }, // 0x71 q
	{ 0x7C, 0x08, 0x04, 0x04, 0x08 }, // 0x72 r
	{ 0x48, 0x54, 0x54, 0x54, 0x20 }, // 0x73 s
	{ 0x04, 0x3F, 0x44, 0x40, 0x20 }, // 0x74 t
	{ 0x3C, 0x40, 0x40, 0x20, 0x7C }, // 0x75 u
	{ 0x1C, 0x20, 0x40, 0x20, 0x1C }, // 0x76 v
	{ 0x3C, 0x40, 0x30, 0x40, 0x3C }, // 0x77 w
	{ 0x44, 0x28, 0x10, 0x28, 0x44 }, // 0x78 x
	{ 0x0C, 0x50, 0x50, 0x50, 0x3C }, // 0x79 y
	{ 0x44, 0x64, 0x54, 0x4C, 0x44 }, // 0x7A z
	{ 0x00, 0x08, 0x36, 0x41, 0x00 }, // 0x7B {
	{ 0x00, 0x00, 0x7F, 0x00, 0x00 }, // 0x7C |
	{ 0x00, 0x41, 0x36, 0x08, 0x00 }, // 0x7D }
	{ 0x10, 0x08, 0x08, 0x10, 0x08 }, // 0x7E ~
	{ 0x7F, 0x41, 0x41, 0x41, 0x7F }, // 0x7F &brvbar
	{ 0x1E, 0xA1, 0xA1, 0x61, 0x12 }, // ASCII-128	0x80
	{ 0x3A, 0x40, 0x40, 0x20, 0x7A }, // ASCII-129	0x81
	{ 0x38, 0x54, 0x56, 0x55, 0x18 }, // ASCII-130	0x82
	{ 0x21, 0x55, 0x55, 0x55, 0x79 }, // ASCII-131	0x83
	{ 0x21, 0x54, 0x54, 0x54, 0x79 }, // ASCII-132	0x84
	{ 0x3C, 0x40, 0x43, 0x23, 0x7C }, // ASCII-133	0x85
	{ 0x20, 0x54, 0x55, 0x55, 0x78 }, // ASCII-134	0x86
	{ 0x0C, 0x1E, 0x52, 0x72, 0x12 }, // ASCII-135	0x87
	{ 0x39, 0x55, 0x55, 0x55, 0x59 }, // ASCII-136	0x88
	{ 0x39, 0x54, 0x54, 0x54, 0x59 }, // ASCII-137	0x89
	{ 0x39, 0x55, 0x54, 0x54, 0x58 }, // ASCII-138	0x8A
	{ 0x00, 0x00, 0x45, 0x7C, 0x41 }, // ASCII-139	0x8B
	{ 0x00, 0x02, 0x45, 0x7D, 0x42 }, // ASCII-140	0x8C
	{ 0x00, 0x01, 0x45, 0x7C, 0x40 }, // ASCII-141	0x8D
	{ 0x79, 0x14, 0x12, 0x14, 0x79 }, // ASCII-142	0x8E
	{ 0x78, 0x14, 0x15, 0x14, 0x78 }, // ASCII-143	0x8F
	{ 0x7C, 0x54, 0x56, 0x45, 0x44 }, // ASCII-144	0x90
	{ 0x20, 0x54, 0x54, 0x7C, 0x54 }, // ASCII-145	0x91
	{ 0x7C, 0x0A, 0x09, 0x7F, 0x49 }, // ASCII-146	0x92
	{ 0x32, 0x49, 0x49, 0x49, 0x32 }, // ASCII-147	0x93
	{ 0x32, 0x48, 0x48, 0x48, 0x32 }, // ASCII-148	0x94
	{ 0x32, 0x4A, 0x48, 0x48, 0x30 }, // ASCII-149	0x95
	{ 0x3A, 0x41, 0x41, 0x21, 0x7A }, // ASCII-150	0x96
	{ 0x3A, 0x42, 0x40, 0x20, 0x78 }, // ASCII-151	0x97
	{ 0x00, 0x9D, 0xA0, 0xA0, 0x7D }, // ASCII-152	0x98
	{ 0x39, 0x44, 0x44, 0x44, 0x39 }, // ASCII-153	0x99
	{ 0x3D, 0x40, 0x40, 0x40, 0x3D }, // ASCII-154	0x9A
	{ 0x04, 0x05, 0x7E, 0x05, 0x04 }, // ASCII-155	0x9B
	{ 0x04, 0x3F, 0x45, 0x42, 0x21 }, // ASCII-156	0x9C
	{ 0x2B, 0x2F, 0xFC, 0x2F, 0x2B }, // ASCII-157	0x9D
	{ 0xFF, 0x09, 0x29, 0xF6, 0x20 }, // ASCII-158	0x9E
	{ 0x30, 0x49, 0x4A, 0x49, 0x20 }, // ASCII-159	0x9F
	{ 0x20, 0x54, 0x56, 0x55, 0x78 }, // ASCII-160	0xA0
	{ 0x00, 0x44, 0x7E, 0x41, 0x00 }, // ASCII-161	0xA1
	{ 0x38, 0x44, 0x46, 0x45, 0x38 }, // ASCII-162	0xA2
	{ 0x3C, 0x40, 0x42, 0x21, 0x7C }, // ASCII-163	0xA3
	{ 0x00, 0x7A, 0x0A, 0x0A, 0x72 }, // ASCII-164	0xA4
	{ 0x7D, 0x0D, 0x19, 0x31, 0x7D }, // ASCII-165	0xA5
	{ 0x44, 0x65, 0x56, 0x4D, 0x44 }, // ASCII-166	0xA6
	{ 0x04, 0x65, 0x56, 0x4D, 0x40 }, // ASCII-167	0xA7
	{ 0x30, 0x48, 0x45, 0x40, 0x20 }, // ASCII-168	0xA8
	{ 0x38, 0x08, 0x08, 0x08, 0x08 }, // ASCII-169	0xA9
	{ 0x08, 0x08, 0x08, 0x08, 0x38 }, // ASCII-170	0xAA
	{ 0x2F, 0x10, 0xC8, 0xAC, 0xBA }, // ASCII-171	0xAB
	{ 0x38, 0x45, 0x46, 0x45, 0x44 }, // ASCII-172	0xAC
	{ 0x00, 0x00, 0x7B, 0x00, 0x00 }, // ASCII-173	0xAD
	{ 0x08, 0x14, 0x2A, 0x14, 0x22 }, // ASCII-174	0xAE
	{ 0x22, 0x14, 0x2A, 0x14, 0x08 }, // ASCII-175	0xAF
	{ 0xAA, 0x00, 0x55, 0x00, 0xAA }, // ASCII-176	0xB0
	{ 0xAA, 0x55, 0xAA, 0x55, 0xAA }, // ASCII-177	0xB1
	{ 0x55, 0xAA, 0x55, 0xAA, 0x55 }, // ASCII-178	0xB2
	{ 0x00, 0x00, 0x00, 0xFF, 0x00 }, // ASCII-179	0xB3
	{ 0x10, 0x10, 0x10, 0xFF, 0x00 }, // ASCII-180	0xB4
	{ 0x70, 0x28, 0x26, 0x29, 0x70 }, // ASCII-181	0xB5
	{ 0x10, 0x10, 0xFF, 0x00, 0xFF }, // ASCII-182	0xB6
	{ 0x7C, 0x55, 0x56, 0x45, 0x44 }, // ASCII-183	0xB7
	{ 0x14, 0x14, 0x14, 0xFC, 0x00 }, // ASCII-184	0xB8
	{ 0x14, 0x14, 0xF7, 0x00, 0xFF }, // ASCII-185	0xB9
	{ 0x00, 0x00, 0xFF, 0x00, 0xFF }, // ASCII-186	0xBA
	{ 0x14, 0x14, 0xF4, 0x04, 0xFC }, // ASCII-187	0xBB
	{ 0x14, 0x14, 0x17, 0x10, 0x1F }, // ASCII-188	0xBC
	{ 0x10, 0x10, 0x1F, 0x10, 0x1F }, // ASCII-189	0xBD
	{ 0x14, 0x14, 0x14, 0x1F, 0x00 }, // ASCII-190	0xBE
	{ 0x10, 0x10, 0x10, 0xF0, 0x00 }, // ASCII-191	0xBF
	{ 0x7E, 0x11, 0x11, 0x11, 0x7E }, // 0xC0 �
	{ 0x7F, 0x49, 0x49, 0x49, 0x33 }, // 0xC1 �
	{ 0x7F, 0x49, 0x49, 0x49, 0x36 }, // 0xC2 �
	{ 0x7F, 0x01, 0x01, 0x01, 0x03 }, // 0xC3 �
	{ 0x60, 0x10, 0x1F, 0x11, 0x7F }, // 0xC4 �
	{ 0x7F, 0x49, 0x49, 0x49, 0x49 }, // 0xC5 �
	{ 0x77, 0x08, 0x7F, 0x08, 0x77 }, // 0xC6 �
	{ 0x49, 0x49, 0x49, 0x49, 0x36 }, // 0xC7 �
	{ 0x7F, 0x10, 0x08, 0x04, 0x7F }, // 0xC8 �
	{ 0x7C, 0x21, 0x12, 0x09, 0x7C }, // 0xC9 �
	{ 0x7F, 0x08, 0x14, 0x22, 0x41 }, // 0xCA �
	{ 0x20, 0x41, 0x3F, 0x01, 0x7F }, // 0xCB �
	{ 0x7F, 0x02, 0x0C, 0x02, 0x7F }, // 0xCC �
	{ 0x7F, 0x08, 0x08, 0x08, 0x7F }, // 0xCD �
	{ 0x3E, 0x41, 0x41, 0x41, 0x3E }, // 0xCE �
	{ 0x7F, 0x01, 0x01, 0x01, 0x7F }, // 0xCF �
	{ 0x7F, 0x09, 0x09, 0x09, 0x06 }, // 0xD0 �
	{ 0x3E, 0x41, 0x41, 0x41, 0x22 }, // 0xD1 �
	{ 0x01, 0x01, 0x7F, 0x01, 0x01 }, // 0xD2 �
	{ 0x27, 0x48, 0x48, 0x48, 0x3F }, // 0xD3 �
	{ 0x1C, 0x22, 0x7F, 0x22, 0x1C }, // 0xD4 �
	{ 0x63, 0x14, 0x08, 0x14, 0x63 }, // 0xD5 �
	{ 0x3F, 0x20, 0x20, 0x3F, 0x60 }, // 0xD6 �
	{ 0x07, 0x08, 0x08, 0x08, 0x7F }, // 0xD7 �
	{ 0x7F, 0x40, 0x7F, 0x40, 0x7F }, // 0xD8 �
	{ 0x3F, 0x20, 0x3F, 0x20, 0x7F }, // 0xD9 �
	{ 0x01, 0x7F, 0x48, 0x48, 0x30 }, // 0xDA �
	{ 0x7F, 0x48, 0x30, 0x00, 0x7F }, // 0xDB �
	{ 0x7F, 0x48, 0x48, 0x30, 0x00 }, // 0xDC �
	{ 0x22, 0x41, 0x49, 0x49, 0x3E }, // 0xDD �
	{ 0x7F, 0x08, 0x3E, 0x41, 0x3E }, // 0xDE �
	{ 0x46, 0x29, 0x19, 0x09, 0x7F }, // 0xDF �
	{ 0x20, 0x54, 0x54, 0x54, 0x78 }, // 0xE0 �
	{ 0x3C, 0x4A, 0x4A, 0x49, 0x31 }, // 0xE1 �
	{ 0x7C, 0x54, 0x54, 0x28, 0x00 }, // 0xE2 �
	{ 0x7C, 0x04, 0x04, 0x04, 0x0C }, // 0xE3 �
	{ 0xE0, 0x54, 0x4C, 0x44, 0xFC }, // 0xE4 �
	{ 0x38, 0x54, 0x54, 0x54, 0x08 }, // 0xE5 �
	{ 0x6C, 0x10, 0x7C, 0x10, 0x6C }, // 0xE6 �
	{ 0x44, 0x44, 0x54, 0x54, 0x28 }, // 0xE7 �
	{ 0x7C, 0x20, 0x10, 0x08, 0x7C }, // 0xE8 �
	{ 0x78, 0x42, 0x24, 0x12, 0x78 }, // 0xE9 �
	{ 0x7C, 0x10, 0x28, 0x44, 0x00 }, // 0xEA �
	{ 0x20, 0x44, 0x3C, 0x04, 0x7C }, // 0xEB �
	{ 0x7C, 0x08, 0x10, 0x08, 0x7C }, // 0xEC �
	{ 0x7C, 0x10, 0x10, 0x10, 0x7C }, // 0xED �
	{ 0x38, 0x44, 0x44, 0x44, 0x38 }, // 0xEE �
	{ 0x7C, 0x04, 0x04, 0x04, 0x7C }, // 0xEF �
	{ 0x7C, 0x14, 0x14, 0x14, 0x08 }, // 0xF0 �
	{ 0x38, 0x44, 0x44, 0x44, 0x44 }, // 0xF1 �
	{ 0x04, 0x04, 0x7C, 0x04, 0x04 }, // 0xF2 �
	{ 0x0C, 0x50, 0x50, 0x50, 0x3C }, // 0xF3 �
	{ 0x18, 0x24, 0x7E, 0x24, 0x18 }, // 0xF4 �
	{ 0x44, 0x28, 0x10, 0x28, 0x44 }, // 0xF5 �
	{ 0x3C, 0x20, 0x20, 0x3C, 0x60 }, // 0xF6 �
	{ 0x0C, 0x10, 0x10, 0x10, 0x7C }, // 0xF7 �
	{ 0x7C, 0x40, 0x7C, 0x40, 0x7C }, // 0xF8 �
	{ 0x3C, 0x20, 0x3C, 0x20, 0x7C }, // 0xF9 �
	{ 0x04, 0x7C, 0x50, 0x50, 0x20 }, // 0xFA �
	{ 0x7C, 0x50, 0x20, 0x00, 0x7C }, // 0xFB �
	{ 0x7C, 0x50, 0x50, 0x20, 0x00 }, // 0xFC �
	{ 0x28, 0x44, 0x54, 0x54, 0x38 }, // 0xFD �
	{ 0x7C, 0x10, 0x38, 0x44, 0x38 }, // 0xFE �
	{ 0x08, 0x54, 0x34, 0x14, 0x7C }  // 0xFF �
};