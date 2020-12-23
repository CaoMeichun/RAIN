#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>


int Round_128 = 36;
//unsigned char Tweakey_128[28][16];
//unsigned char Plaintext_128[16] = { 0x90, 0x9e, 0x00, 0x68, 0xfd, 0x88, 0xf5, 0xb0, 0xec, 0x9d, 0x4a, 0x33, 0x14, 0x4e, 0xfd, 0x0e };
//unsigned char Tweak_128[16] = { 0xf1, 0xb6, 0x09, 0x57, 0x09, 0xd0, 0xd2, 0xf8, 0x74, 0xe8, 0xc3, 0xbd, 0x9b, 0x4f, 0x36, 0xab };
//unsigned char Key[16] = { 0x40, 0x53, 0x94, 0x94, 0xbf, 0x6e, 0xbd, 0xe8, 0x93, 0xbe, 0xaa, 0xce, 0x1b, 0xb5, 0x51, 0x73 };

//unsigned char PlainKeySpace[256] = { 0x00 };
unsigned char PlainKeySpace[256] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf, 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef, 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff };
unsigned char Plaintext_128[16], Tweak_128[16], Key[16];
unsigned char Tweakey_128[36][16];

void PlainKeySelect_128()
{
	srand((unsigned)time(0));
	int x;
	printf("RAIN-128:\n");
	printf("PlainText:\n");
	for (int i = 0; i < 16; i++)
	{
		x = rand() % 256;
		Plaintext_128[i] = PlainKeySpace[x];
		printf("%02x", Plaintext_128[i]);
		if (i % 4 == 3)
			printf(" ");
	}
	printf("\n\n");
	printf("Key:\n");
	for (int i = 0; i < 16; i++)
	{
		x = rand() % 256;
		Key[i] = PlainKeySpace[x];
		printf("%02x", Key[i]);
		if (i % 4 == 3)
			printf(" ");
	}
	printf("\n");
	printf("Tweak:\n");
	for (int i = 0; i < 16; i++)
	{
		x = rand() % 256;
		Tweak_128[i] = PlainKeySpace[x];
		printf("%02x", Tweak_128[i]);
		if (i % 4 == 3)
			printf(" ");
	}
	printf("\n\n");
}

void prinState_128(unsigned char* state, char* name, int round)
{
	if (round < 10)
		printf("ENC - Round0%d - %-12s: %c = ", round, name, 'S');
	else
		printf("ENC - Round%d - %-12s: %c = ", round, name, 'S');
	for (int i = 0; i < 16; i++)
	{
		printf("%02x", state[i]);
		if (i % 4 == 3)
			printf(" ");
	}
	if (name[0] == 'A')
	{
		printf(" - %s%d = ", "Tweakey_", round);
		for (int i = 0; i < 16; i++)
		{
			printf("%02x", Tweakey_128[round][i]);
			if (i % 4 == 3)
				printf(" ");
		}
	}

	printf("\n");
}
void prinStateinv_128(unsigned char* state, char* name, int round)
{
	if (round < 10)
		printf("DEC - Round0%d - %-18s: %c = ", round, name, 'S');
	else
		printf("DEC - Round%d - %-18s: %c = ", round, name, 'S');
	for (int i = 0; i < 16; i++)
	{
		printf("%02x", state[i]);
		if (i % 4 == 3)
			printf(" ");
	}

	printf(" - %s%d = ", "Tweakey_", round);
	for (int i = 0; i < 16; i++)
	{
		printf("%02x", Tweakey_128[round][i]);
		if (i % 4 == 3)
			printf(" ");
	}

	printf("\n");
}

void prinRTK_128(unsigned char* state, char* name, int round)
{
	if (round < 10)
		printf("RTK - Round0%d - %-18s = ", round, name);
	else
		printf("RTK - Round%d - %-18s = ", round, name);
	for (int i = 0; i < 16; i++)
	{
		printf("%02x", state[i]);
		if (i % 4 == 3)
			printf(" ");
	}

	printf("\n");
}

void MC_128(unsigned char* state_out, unsigned char* state)
{
	unsigned char state_result[16];
	unsigned char tmp;

	tmp = state[0] ^ state[4] ^ state[8] ^ state[12];
	state_result[0] = tmp ^ state[0];
	state_result[4] = tmp ^ state[8];
	state_result[8] = tmp ^ state[4];
	state_result[12] = tmp ^ state[12];

	tmp = state[1] ^ state[5] ^ state[9] ^ state[13];
	state_result[1] = tmp ^ state[1];
	state_result[5] = tmp ^ state[9];
	state_result[9] = tmp ^ state[5];
	state_result[13] = tmp ^ state[13];

	tmp = state[2] ^ state[6] ^ state[10] ^ state[14];
	state_result[2] = tmp ^ state[2];
	state_result[6] = tmp ^ state[10];
	state_result[10] = tmp ^ state[6];
	state_result[14] = tmp ^ state[14];

	tmp = state[3] ^ state[7] ^ state[11] ^ state[15];
	state_result[3] = tmp ^ state[3];
	state_result[7] = tmp ^ state[11];
	state_result[11] = tmp ^ state[7];
	state_result[15] = tmp ^ state[15];

	for (int i = 0; i < 16; i++)
	{
		state_out[i] = state_result[i];
	}
}
void SC_128(unsigned char* state_out, unsigned char* state)
{
	unsigned char Sbox[16] = { 0x00, 0x09, 0x03, 0x02, 0x06, 0x05, 0x04, 0x0b, 0x0c, 0x01, 0x0a, 0x0d, 0x08, 0x0e, 0x07, 0x0f };
	unsigned char state_dec1, state_dec2;
	unsigned char state_tmp1[16] = { 0 }, state_tmp2[16] = { 0 };
	for (int i = 0; i < 16; i++)
	{
		state_dec1 = state[i] & 0x0f;//右边4bit查找S盒
		state_tmp1[i] = Sbox[state_dec1];

		state_dec2 = (state[i] >> 4);//左边4bit查找S盒
		state_tmp2[i] = Sbox[state_dec2];

		state_out[i] = ((state_tmp2[i] & 0x08) << 4)
			| ((state_tmp1[i] & 0x08) << 3)
			| ((state_tmp2[i] & 0x04) << 3)
			| ((state_tmp1[i] & 0x04) << 2)
			| ((state_tmp2[i] & 0x02) << 2)
			| ((state_tmp1[i] & 0x02) << 1)
			| ((state_tmp2[i] & 0x01) << 1)
			| ((state_tmp1[i] & 0x01));
	}
}
void SCinv_128(unsigned char* state_out, unsigned char* state)
{
	unsigned char Sbox_inv[16] = { 0x0, 0x9, 0x3, 0x2, 0x6, 0x5, 0x4, 0xe, 0xc, 0x1, 0xa, 0x7, 0x8, 0xb, 0xd, 0xf };
	unsigned char state_dec1;
	unsigned char state_dec2;

	for (int i = 0; i < 16; i++)
	{
		state_dec1 = ((state[i] & 0x80) >> 4)
			| ((state[i] & 0x20) >> 3)
			| ((state[i] & 0x08) >> 2)
			| ((state[i] & 0x02) >> 1);

		state_dec2 = ((state[i] & 0x40) >> 3)
			| ((state[i] & 0x10) >> 2)
			| ((state[i] & 0x04) >> 1)
			| ((state[i] & 0x01));


		state_out[i] = (Sbox_inv[state_dec1] << 4) ^ (Sbox_inv[state_dec2]);
	}
}

void AC_128(unsigned char* state_out, unsigned char* state, int round)
{
	unsigned char RC[36][4] = {
		{ 0x72, 0x74, 0x25, 0x8a }, { 0x45, 0xc5, 0x0f, 0x80 }, { 0x7d, 0xd0, 0x2a, 0xdd }, { 0xc4, 0x74, 0x0f, 0xaf },
		{ 0xd0, 0xcd, 0x8a, 0xfa }, { 0xc2, 0xdc, 0x85, 0xca }, { 0xf7, 0xd0, 0xc5, 0x2c }, { 0xaa, 0xcf, 0xc5, 0xcf },
		{ 0xf0, 0xc5, 0x47, 0xcd }, { 0x7a, 0x42, 0x0c, 0x05 }, { 0xdd, 0x80, 0x5d, 0xc8 }, { 0x57, 0x54, 0xca, 0x72 },
		{ 0x8c, 0x4c, 0x58, 0x02 }, { 0x5d, 0x7a, 0x45, 0x0f }, { 0x24, 0x4f, 0xc0, 0x47 }, { 0xf4, 0x7d, 0x5a, 0x08 },
		{ 0x8d, 0x80, 0xc5, 0xc4 }, { 0x24, 0xa7, 0x72, 0x42 }, { 0x7f, 0xc0, 0xff, 0xf5 }, { 0x8d, 0x52, 0x72, 0x54 },
		{ 0x44, 0xaa, 0x8f, 0x4c }, { 0x80, 0x88, 0xf4, 0xc8 }, { 0x8c, 0xff, 0xf8, 0x08 }, { 0x02, 0x28, 0x4c, 0xd4 },
		{ 0x0a, 0x08, 0xc2, 0x7c }, { 0x02, 0x0f, 0x88, 0xff }, { 0xc2, 0xa0, 0x8f, 0xc0 }, { 0x4c, 0x78, 0x57, 0x8f },
		{ 0xad, 0xa4, 0x02, 0x7c }, { 0x4d, 0x82, 0xc7, 0x2d }, { 0xa7, 0x0d, 0xdf, 0x2f }, { 0xda, 0x0f, 0x88, 0x45 },
		{ 0x4f, 0x45, 0x07, 0xd7 }, { 0x50, 0xdc, 0x27, 0x54 }, { 0x27, 0x80, 0xd5, 0xfc }, { 0xa4, 0xa0, 0x5a, 0x4c } };

	state_out[0] = state[0] ^ RC[round][0];
	state_out[4] = state[4] ^ RC[round][1];
	state_out[8] = state[8] ^ RC[round][2];
	state_out[12] = state[12] ^ RC[round][3];
	state_out[1] = state[1];
	state_out[2] = state[2];
	state_out[3] = state[3];
	state_out[5] = state[5];
	state_out[6] = state[6];
	state_out[7] = state[7];
	state_out[9] = state[9];
	state_out[10] = state[10];
	state_out[11] = state[11];
	state_out[13] = state[13];
	state_out[14] = state[14];
	state_out[15] = state[15];
}

void SR_128(unsigned char* state_out, unsigned char* state)
{
	state_out[0] = state[0];		state_out[1] = state[1];
	state_out[4] = state[5];		state_out[5] = state[6];
	state_out[8] = state[10];	    state_out[9] = state[11];
	state_out[12] = state[15];	    state_out[13] = state[12];

	state_out[2] = state[2];		state_out[3] = state[3];
	state_out[6] = state[7];		state_out[7] = state[4];
	state_out[10] = state[8];	    state_out[11] = state[9];
	state_out[14] = state[13];	    state_out[15] = state[14];
}
void SRinv_128(unsigned char* state_out, unsigned char* state)
{
	state_out[0] = state[0];		state_out[1] = state[1];
	state_out[4] = state[7];		state_out[5] = state[4];
	state_out[8] = state[10];	    state_out[9] = state[11];
	state_out[12] = state[13];	    state_out[13] = state[14];

	state_out[2] = state[2];		state_out[3] = state[3];
	state_out[6] = state[5];		state_out[7] = state[6];
	state_out[10] = state[8];	    state_out[11] = state[9];
	state_out[14] = state[15];	    state_out[15] = state[12];
}
void ATK_128(unsigned char* ATK_out, unsigned char* RTK, unsigned char* state)
{
	for (int i = 0; i < 16; i++)
	{
		ATK_out[i] = state[i] ^ RTK[i];
	}
}
void AK_128(unsigned char* AK_out, unsigned char* T, unsigned char* K)
{
	AK_out[0] = T[0] ^ K[0];
	AK_out[1] = T[1] ^ K[1];
	AK_out[2] = T[2] ^ K[2];
	AK_out[3] = T[3] ^ K[3];
	AK_out[4] = T[4] ^ K[4];
	AK_out[5] = T[5] ^ K[5];
	AK_out[6] = T[6] ^ K[6];
	AK_out[7] = T[7] ^ K[7];
	AK_out[8] = T[8] ^ K[8];
	AK_out[9] = T[9] ^ K[9];
	AK_out[10] = T[10] ^ K[10];
	AK_out[11] = T[11] ^ K[11];
	AK_out[12] = T[12] ^ K[12];
	AK_out[13] = T[13] ^ K[13];
	AK_out[14] = T[14] ^ K[14];
	AK_out[15] = T[15] ^ K[15];
}

void AB_128(unsigned char* state_out, unsigned char* state)
{
	unsigned char state_result[16];
	unsigned char tmp = 0;
	unsigned char tmp_bit = 0x0;
	for (int i = 0; i < 16; i++)
		state_result[i] = state[i];
	for (int i = 0; i < 16; i++)
		tmp_bit ^= state[i];

	if ((tmp_bit & 0x80) == 0x80)
	{
		for (int ii = 0; ii < 16; ii++)
			state_out[ii] = (state_result[ii] & 0x7f) ^ 0x80;
	}
	else if ((tmp_bit & 0x80) == 0)
	{
		for (int ii = 0; ii < 16; ii++)
			state_out[ii] = state_result[ii] & 0x7f;
	}
}

void KeySchdule_128(unsigned char* T, unsigned char* K)
{
	printf("Round Tweakey RTK schdule:\n\n");
	unsigned char AK_out[16], TSR_out[16], AC_out[16];

	AK_128(AK_out, Tweak_128, K); prinRTK_128(AK_out, "AK_out", 0);
	SR_128(TSR_out, AK_out); prinRTK_128(TSR_out, "TSR_out", 0);
	AC_128(AC_out, TSR_out, 0); prinRTK_128(AC_out, "AC_out", 0);
	AB_128(Tweakey_128[0], AC_out); prinRTK_128(Tweakey_128[0], "RTK", 0);
	
	for (int i = 1; i < Round_128; i++)
	{
		AK_128(AK_out, Tweakey_128[i - 1], K); prinRTK_128(AK_out, "AK_out", i);
		SR_128(TSR_out, AK_out); prinRTK_128(TSR_out, "TSR_out", i);
		AC_128(AC_out, TSR_out, i); prinRTK_128(AC_out, "AC_out", i);
		AB_128(Tweakey_128[i], AC_out); prinRTK_128(Tweakey_128[i], "RTK", i);
	}

	printf("\n\n\n");
}

void enc_128(unsigned char* C, unsigned char* P, unsigned char* T, unsigned char* K)//0, unsigned char* K1)
{
	unsigned char MC_out[16], SC_out[16], SR_out[16];

	for (int i = 0; i < 16; i++)
		C[i] = P[i] ^ K[i];

	for (int i = 0; i < Round_128; i++)
	{
		MC_128(MC_out, C); prinState_128(MC_out, "MC_output",i);
		SC_128(SC_out, MC_out); prinState_128(SC_out, "SC_output",i);		
		SR_128(SR_out, SC_out); prinState_128(SR_out, "SR_output",i);
		ATK_128(C, Tweakey_128[i], SR_out); prinState_128(C, "ATK_output",i);
	}

	printf("CipherText: ");
	for (int i = 0; i < 16; i++)
	{
		printf("%0x", C[i]);
		if (i % 4 == 3)
			printf(" ");
	}
	printf("\n");
}
void dec_128(unsigned char* P, unsigned char* C, unsigned char* T, unsigned char* K)
{
	unsigned char MCinv_out[16], SCinv_out[16], SRinv_out[16], ATKinv_out[16];

	for (int i = 0; i < 16; i++)
		MCinv_out[i] = C[i];

	for (int i = Round_128 - 1; i >= 0; i--)
	{
		ATK_128(ATKinv_out, Tweakey_128[i], MCinv_out); prinStateinv_128(ATKinv_out, "ATK_inv_output",i);
		SRinv_128(SRinv_out, ATKinv_out); prinStateinv_128(SRinv_out, "SR_inv_output",i);
		SCinv_128(SCinv_out, SRinv_out); prinStateinv_128(SCinv_out, "SC_inv_output",i);
		MC_128(MCinv_out, SCinv_out); prinStateinv_128(MCinv_out, "MC_inv_output", i);
	}

	for (int i = 0; i < 16; i++)
		P[i] = MCinv_out[i] ^ K[i];

	printf("CipherText_Decryption: ");
	for (int i = 0; i < 16; i++)
	{
		printf("%0x", P[i]);
		if (i % 4 == 3)
			printf(" ");
	}
	printf("\n");

}
void Test128()
{
	PlainKeySelect_128();
	KeySchdule_128(Tweak_128, Key);

	printf("\n\n\n\n");
	unsigned char C[16], P[16];

	enc_128(C, Plaintext_128, Tweak_128, Key);

	printf("\n\n\n\n");

	dec_128(P, C, Tweak_128, Key);

	if (memcmp(P, Plaintext_128, 16) != 0) {
		printf("解密失败 () test failed.\n");
		getchar();
	}
	printf("\n   解密成功 \n");
}

int main()
{

	printf("The cipher status is written into \"RAIN-128_output.txt\" in this directory.\n");

	FILE* stream1;
	freopen_s(&stream1, "RAIN-128_output.txt", "w", stdout);
	
	Test128();

	fclose(stdout);//关闭文件

	system("pause");
	return 0;
}
